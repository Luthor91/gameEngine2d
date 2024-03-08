FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
        build-essential \
        cmake \
        libsdl2-dev \
        libsdl2-image-dev \
        && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy source code
COPY . .

# Build the project
RUN cmake -B build -S . && \
    cmake --build build

# Run the project
CMD ["/app/build/gameEngine"]