FROM ubuntu:16.04

ENV DEBIAN_FRONTEND noninteractive
ENV REQUIRES_RTTI 1
ENV JAVA_TOOL_OPTIONS -Dfile.encoding=UTF8

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
    ./configure && \
    make install

RUN cd /tmp/ && \
    wget http://releases.llvm.org/3.8.0/llvm-3.8.0.src.tar.xz && \
    wget http://releases.llvm.org/3.8.0/cfe-3.8.0.src.tar.xz && \
    wget http://releases.llvm.org/3.8.0/compiler-rt-3.8.0.src.tar.xz
RUN cd /tmp/ && \
    tar -xf llvm-3.8.0.src.tar.xz && \
    tar -xf cfe-3.8.0.src.tar.xz && \
    tar -xf compiler-rt-3.8.0.src.tar.xz
RUN mv /tmp/llvm-3.8.0.src /tmp/llvm && \
    mv /tmp/cfe-3.8.0.src /tmp/llvm/tools/clang && \
    mv /tmp/compiler-rt-3.8.0.src /tmp/llvm/projects/compiler-rt
RUN mkdir /tmp/build && \
    cd /tmp/build && \
    cmake -G "Unix Makefiles" -DLLVM_ENABLE_RTTI=ON ../llvm && \
    make -j 8 install

RUN rm -rf /tmp/llvm
RUN rm -rf /tmp/build

RUN cd /tmp/ && \
    wget http://www.codesynthesis.com/download/odb/2.4/libodb-2.4.0.tar.gz && \
    tar -xvf libodb-2.4.0.tar.gz
RUN cd /tmp/libodb-2.4.0 && \
    ./configure && \
    make install
RUN apt-get install --yes gcc-5-plugin-dev
RUN apt-get install --yes libcutl-dev
RUN apt-get install --yes postgresql-server-dev-9.5
RUN cd /tmp/ && \
    wget http://www.codesynthesis.com/download/odb/2.4/libodb-pgsql-2.4.0.tar.gz && \
    tar -xvf libodb-pgsql-2.4.0.tar.gz && \
    cd libodb-pgsql-2.4.0 && \
    ./configure && \
    make install

RUN cd /tmp/ && \
    wget http://www.codesynthesis.com/download/odb/2.4/odb-2.4.0.tar.gz && \
    tar -xvf odb-2.4.0.tar.gz && \
    cd odb-2.4.0 && \
    ./configure && \
    make install

RUN apt-get install --yes npm
