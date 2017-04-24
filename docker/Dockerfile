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

RUN wget http://releases.llvm.org/3.8.0/clang+llvm-3.8.0-x86_64-linux-gnu-ubuntu-16.04.tar.xz -O /tmp/clang+llvm.tar.xz
RUN apt-get install --yes xz-utils
RUN mkdir -p /opt/local/clang+llvm
RUN tar -xf /tmp/clang+llvm.tar.xz -C /opt/local/clang+llvm

# RUN rm -rf /tmp/thrift*

# apt-get install -y build-essential && \
# apt-get install -y llvm && \
# apt-get install -y clang-3.8 && \
# apt-get install -y cmake
