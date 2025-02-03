# Use an official Ubuntu runtime as a parent image
FROM ubuntu:20.04

# Set the working directory in the container
WORKDIR /app

# Install system dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    make

# Copy the current directory contents into the container at /app
COPY . /app

# Build the application
RUN mkdir build && cd build && \
    cmake .. && \
    make

# Run the binary when the container launches
CMD ["./build/processor_simulator"]
