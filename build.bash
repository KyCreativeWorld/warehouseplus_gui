#!/bin/bash

# Set the app name
APP_NAME="WarehousePlusGUI"

rm -f $APP_NAME

# Print a message indicating the build process has started
echo "Building $APP_NAME..."

g++ main.cpp -o main

clang++ -std=c++17 *.cpp \
    -I./include \
    -I/opt/homebrew/include \
    -L/opt/homebrew/lib \
    -lraylib \
    -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
    -o $APP_NAME

if [ $? -eq 0 ]; then
    ./$APP_NAME
fi
