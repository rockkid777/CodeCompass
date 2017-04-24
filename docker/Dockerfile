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

# RUN apt-get install --yes npm
# RUN npm install -g semver
# RUN curl -sL https://deb.nodesource.com/setup_6.x | bash - && \
# 	apt-get update && apt-get install -y nodejs && \
# 	npm install npm@latest -g
# RUN npm set strict-ssl false

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

# RUN wget http://releases.llvm.org/3.8.0/clang+llvm-3.8.0-x86_64-linux-gnu-ubuntu-16.04.tar.xz -O /tmp/clang+llvm.tar.xz
# RUN mkdir -p /opt/local/clang+llvm
# RUN tar -xf /tmp/clang+llvm.tar.xz -C /opt/local/clang+llvm

RUN cd /tmp/ && \
    svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm
RUN cd /tmp/llvm/tools && \
    svn co http://llvm.org/svn/llvm-project/cfe/trunk clang
RUN cd /tmp/llvm/tools/clang/tools && \
    svn co http://llvm.org/svn/llvm-project/clang-tools-extra/trunk extra
RUN cd /tmp/llvm/projects && \
    svn co http://llvm.org/svn/llvm-project/compiler-rt/trunk compiler-rt
RUN cd /tmp/llvm/projects && \
    svn svn co http://llvm.org/svn/llvm-project/libcxx/trunk libcxx
RUN export REQUIRES_RTTI=1
RUN mkdir /tmp/build && \
    cd /tmp/llvm/build && \
    cmake -G "Unix Makefiles" -DLLVM_ENABLE_RTTI=ON ../llvm

# RUN rm -rf /tmp/thrift*
# RUN rm -rf /tmp/llvm
# RUN rm -rf /tmp/build

# apt-get install -y build-essential && \
# apt-get install -y llvm && \
# apt-get install -y clang-3.8 && \
# apt-get install -y cmake
