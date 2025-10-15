# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(TicTacToe C)

# Set the C standard (optional, but good practice for modern C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add an executable target
# TicTacToe is the target name (and the final executable name)
add_executable(TicTacToe
    main.c 
    agent.c
)