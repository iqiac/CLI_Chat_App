FROM ubuntu:latest as base

FROM base as builder

RUN apt update && apt install -y \
  vim \
  build-essential \
  cmake \
  ccache

RUN apt upgrade -y && rm -rf /var/lib/apt/lists/*

FROM builder as dev

RUN apt update && apt install -y \
  tree \
  gdb \
  clang-format \
  cppcheck \
  git

RUN apt upgrade -y && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
