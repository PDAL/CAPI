FROM pdal/alpine:1.7.1
MAINTAINER Jaime Soto <docker@simverge.com>

RUN \
	echo "http://dl-cdn.alpinelinux.org/alpine/edge/testing" >> /etc/apk/repositories; \
	echo "@edgecommunity http://dl-cdn.alpinelinux.org/alpine/edge/community" >> /etc/apk/repositories; \
	apk update; \
	apk add --no-cache \
		libc6-compat \
		gcc \
		g++ \
		lcov \
		make \
		cmake \
		curl
