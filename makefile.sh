#!/bin/bash

export DYLD_LIBRARY_PATH=/usr/local/lib
g++ -std=c++20 ./src/*.cpp -o sfml-app -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system &&  ./sfml-app
