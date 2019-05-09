FROM pdal/pdal:1.8
MAINTAINER Jaime Soto <docker@simverge.com>

RUN \
apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    lcov \
    wget \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*
