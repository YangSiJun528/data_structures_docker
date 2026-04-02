FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive \
    TZ=Asia/Seoul \
    LANG=ko_KR.UTF-8 \
    LANGUAGE=ko_KR.UTF-8 \
    LC_ALL=ko_KR.UTF-8

RUN apt-get update && apt-get install -y \
    bash-completion \
    build-essential \
    ca-certificates \
    cmake \
    curl \
    gdb \
    git \
    gcc \
    iproute2 \
    locales \
    make \
    net-tools \
    procps \
    python3 \
    sudo \
    telnet \
    tzdata \
    unzip \
    valgrind \
    vim \
    wget \
    libfreetype6 \
    libxi6 \
    libxext6 \
    libxrender1 \
    libxtst6 \
    && locale-gen ko_KR.UTF-8 \
    && update-locale LANG=ko_KR.UTF-8 LANGUAGE=ko_KR.UTF-8 LC_ALL=ko_KR.UTF-8 \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m -s /bin/bash jungle \
    && usermod -aG sudo jungle \
    && echo "jungle:jungle" | chpasswd \
    && echo "jungle ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/jungle \
    && chmod 0440 /etc/sudoers.d/jungle

USER jungle
WORKDIR /workspaces
