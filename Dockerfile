FROM ubuntu:latest AS base

FROM base AS builder

RUN apt update && apt install -y \
  vim \
  build-essential \
  cmake \
  ccache

RUN apt upgrade -y && rm -rf /var/lib/apt/lists/*

FROM builder AS dev

RUN apt update && apt install -y \
  tree \
  gdb \
  clang-format \
  clang-tidy \
  cppcheck \
  git

RUN apt upgrade -y && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
