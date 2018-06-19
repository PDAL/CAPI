FROM pdal/ubuntu
MAINTAINER Jaime Soto <docker@simverge.com>

RUN \
apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    lcov \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*
