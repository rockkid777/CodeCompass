FROM ubuntu:16.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update
RUN apt-get install --yes apt-utils
RUN apt-get install --yes xz-utils
RUN apt-get install --yes git
RUN apt-get install --yes cmake
RUN apt-get install --yes g++
RUN apt-get install --yes libboost-all-dev
RUN apt-get install --yes openjdk-8-jdk
RUN apt-get install --yes libssl-dev
RUN apt-get install --yes libsqlite3-dev
RUN apt-get install --yes libgraphviz-dev
RUN apt-get install --yes libmagic-dev
RUN apt-get install --yes libgit2-dev
RUN apt-get install --yes ctags
RUN apt-get install --yes wget
RUN apt-get install --yes curl

RUN wget http://xenia.sote.hu/ftp/mirrors/www.apache.org/thrift/0.10.0/thrift-0.10.0.tar.gz -O /tmp/thrift.tar.gz && \
mkdir /tmp/thrift && \
tar -xvf /tmp/thrift.tar.gz -C /tmp/ && \
cd /tmp/thrift-0.10.0 && \
./configure --prefix=/opt/local/thrift && \
make install && \
export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:/opt/local/thrift && \
export PATH=/opt/local/thrift/bin:$PATH

RUN curl -sL https://deb.nodesource.com/setup_6.x | bash -
RUN apt-get update
RUN apt-get install --yes nodejs
RUN npm install npm@latest -g

#move this line up!
RUN apt-get install --yes subversion

RUN cd /tmp/ && \
    svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm
RUN cd /tmp/llvm/tools && \
    svn co http://llvm.org/svn/llvm-project/cfe/trunk clang
RUN cd /tmp/llvm/tools/clang/tools && \
    svn co http://llvm.org/svn/llvm-project/clang-tools-extra/trunk extra
RUN cd /tmp/llvm/projects && \
    svn co http://llvm.org/svn/llvm-project/compiler-rt/trunk compiler-rt
RUN export REQUIRES_RTTI=1
RUN mkdir /tmp/build && \
    cd /tmp/build && \
    cmake -G "Unix Makefiles" -DLLVM_ENABLE_RTTI=ON ../llvm && \
    make

RUN cd /tmp/ && \
    wget http://www.codesynthesis.com/download/odb/2.4/libodb-2.4.0.tar.gz && \
    tar -xvf libodb-2.4.0.tar.gz
RUN cd /tmp/libodb-2.4.0 && \
    ./configure --prefix=/opt/odb && \
    make install
RUN apt-get install --yes gcc-5-plugin-dev
RUN apt-get install --yes libcutl-dev
RUN cd /tmp/ && \
    wget http://www.codesynthesis.com/download/odb/2.4/libodb-pgsql-2.4.0.tar.gz && \
    tar -xvf libodb-pgsql-2.4.0.tar.gz && \
    cd libodb-pgsql-2.4.0
    ./configure --prefix=/opt/odb && \
    make install

RUN cd /tmp/ && \
    wget http://www.codesynthesis.com/download/odb/2.4/odb-2.4.0.tar.gz && \
    tar -xvf odb-2.4.0.tar.gz && \
    cd odb-2.4.0 && \
    ./configure --prefix=/opt/odb && \
    make install

RUN export CMAKE_PREFIX_PATH=/opt/odb:$CMAKE_PREFIX_PATH

# RUN rm -rf /tmp/thrift*
# RUN rm -rf /tmp/llvm
# RUN rm -rf /tmp/build
