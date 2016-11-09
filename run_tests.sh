#!/bin/bash

set -e

# Docker image with needed tools. This one will be published
docker build -t danielcr86/newsclustering `pwd`/docker/base

# Docker image based on the previous, with user specific info (uid)
docker build --build-arg uid=`id -u` -t newsclustering_user `pwd`/docker/user_specific

# build and run the test in the user specific image, to avoid
# getting files owned by root in the host
docker run \
  -v `pwd`:/NewsClustering \
  -w /NewsClustering \
  newsclustering_user:latest \
  ash -c "mkdir -p build && \
          cd build && \
          cmake .. && \
          make NewsClusteringTest && \
          bin/NewsClusteringTest --gtest_output=xml"
