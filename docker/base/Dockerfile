FROM alpine:latest

RUN apk update
RUN apk add gcc g++ cmake make git python

RUN git clone https://github.com/google/googletest
WORKDIR /googletest
RUN cmake .
RUN make install

#RUN adduser newsclusterdev
