#ifndef CC_WEBSERVER_THRIFTHANDLER_H
#define CC_WEBSERVER_THRIFTHANDLER_H

#include <stdio.h>

#include <boost/shared_ptr.hpp>
#include <boost/log/trivial.hpp>

#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/THttpServer.h>
#include <thrift/transport/TTransport.h>
#include <thrift/protocol/TJSONProtocol.h>

#include "mongoose.h"

/**
 * Returns the demangled name of the type described by the given type info.
 *
 * @param info_ a type info.
 * @return the pretty name of the type.
 */
inline std::string getTypeName(const std::type_info& info_)
{
  int status = 0;
  std::unique_ptr<char[], void (*)(void*)> result(
    abi::__cxa_demangle(info_.name(), 0, 0, &status), std::free);

  return result.get() ? std::string(result.get()) : "##error##";
}

/**
 * Returns the template argument's demangled name.
 *
 * @return the pretty name of the T type.
 */
template <typename T>
inline std::string getTypeName()
{
  return getTypeName(typeid(T));
}

namespace cc
{
namespace webserver
{

template<class Processor>
class ThriftHandler : public RequestHandler
{
protected:
  /**
   * Calling context for thrift process calls.
   */
  struct CallContext
  {
    /**
     * Mongoose connection.
     */
    struct mg_connection* connection;

    /**
     * A pointer for the real call context (for dispatch call).
     */
    void* nextCtx;
  };

  class LoggingProcessor : public Processor
  {
  public:
    template <typename IFaceType>
    LoggingProcessor(
      boost::shared_ptr<IFaceType> handler_,
      const std::string workspaceName_) :
        Processor(handler_),
        _workspaceName(workspaceName_),
        _serviceName(getTypeName(typeid(*handler_.get())))
    {
    }

  protected:
    virtual bool dispatchCall(
      apache::thrift::protocol::TProtocol* in_,
      apache::thrift::protocol::TProtocol* out_,
      const std::string& fname_,
      std::int32_t seqid_,
      void* callContext_) override
    {
      CallContext& ctx = *reinterpret_cast<CallContext*>(callContext_);

      return Processor::dispatchCall(in_, out_, fname_, seqid_, ctx.nextCtx);
    }

  private:
    std::string _workspaceName;
    std::string _serviceName;
  };

public:
  template<class Handler>
  ThriftHandler(Handler *handler_, const std::string& workspaceName_)
    : _processor(::boost::shared_ptr<Handler>(handler_), workspaceName_)
  {
  }

  template<class Handler>
  ThriftHandler(Handler handler_, const std::string& workspaceName_)
    : _processor(handler_, workspaceName_)
  {
  }

  std::string key() const
  {
    return "ThriftHandler";
  }

  int beginRequest(struct mg_connection *conn_) override
  {
    using namespace ::apache::thrift;
    using namespace ::apache::thrift::transport;
    using namespace ::apache::thrift::protocol;
    
    try
    {
      std::string content = getContent(conn_);
      
      BOOST_LOG_TRIVIAL(debug) << "Request content:\n" << content;

      boost::shared_ptr<TTransport> inputBuffer(
        new TMemoryBuffer((std::uint8_t*)content.c_str(), content.length()));

      boost::shared_ptr<TTransport> outputBuffer(new TMemoryBuffer(4096));

      boost::shared_ptr<TProtocol> inputProtocol(new TJSONProtocol(inputBuffer));
      boost::shared_ptr<TProtocol> outputProtocol(new TJSONProtocol(outputBuffer));

      CallContext ctx{conn_, nullptr};
      _processor.process(inputProtocol, outputProtocol, &ctx);

      TMemoryBuffer *mBuffer = dynamic_cast<TMemoryBuffer*>(outputBuffer.get());

      std::string response = mBuffer->getBufferAsString();

      BOOST_LOG_TRIVIAL(debug)
        << "Response:\n" << response.c_str() << std::endl;
      
      // Send HTTP reply to the client
      // create headers
      mg_send_header(conn_, "Content-Type", "application/x-thrift");
      mg_send_header(conn_, "Content-Length", std::to_string(response.length()).c_str());

      // terminate headers
      mg_write(conn_, "\r\n", 2);

      // send content
      mg_write(conn_, response.c_str(), response.length());
    }
    catch (const std::exception& ex)
    {
      BOOST_LOG_TRIVIAL(warning) << ex.what();
    }
    catch (...)
    {
      BOOST_LOG_TRIVIAL(warning) << "Unknown exception has been caught";
    }

    // Returning non-zero tells mongoose that our function has replied to
    // the client, and mongoose should not send client any more data.
    return MG_TRUE;
  }

private:
  std::string getContent(mg_connection* conn_)
  {
    return std::string(conn_->content, conn_->content + conn_->content_len);
  }

  LoggingProcessor _processor;
};

} // mongoose
} // cc

#endif // CC_WEBSERVER_THRIFTHANDLER_H
