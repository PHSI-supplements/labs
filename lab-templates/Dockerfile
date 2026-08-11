FROM ubuntu:26.04

RUN apt-get update && apt-get install -y \
    build-essential \
    binutils \
    gdb \
    cmake \
    git \
    vim \
    curl \
    python3 \
    python3-venv \
    python3-setuptools \
    python3-wheel \
    libffi-dev \
    libssl-dev \
    libicu-dev \
    && rm -rf /var/lib/apt/lists/*

RUN python3 -m venv /opt/platformio \
    && /opt/platformio/bin/pip install --no-cache-dir --upgrade pip \
    && /opt/platformio/bin/pip install --no-cache-dir platformio

ENV PATH="/opt/platformio/bin:${PATH}"

