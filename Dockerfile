FROM buildpack-deps:bullseye

RUN apt update; \
    DEBIAN_FRONTEND=noninteractive apt install -y gcc make git binutils libc6-dev clang-format-11
