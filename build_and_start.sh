#!/bin/bash

# make and build
cmake . -B build
cmake --build build
./build/example_glfw_vulkan