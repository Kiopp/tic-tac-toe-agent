#!/usr/bin/env fish

# 1. Create a build directory
mkdir build

# 2. Navigate into the build directory
cd build

# 3. Configure the project using CMake
# The '..' tells CMake where the CMakeLists.txt file is (one directory up)
cmake ..

# 4. Build the executable
make

# 5. Run the game!
./TicTacToe