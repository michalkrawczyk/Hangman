cmake_minimum_required(VERSION 3.13)
project(Hangman)

set(CMAKE_CXX_STANDARD 14)

add_executable(Hangman main.cpp
        includes/Arena.cpp includes/Arena.h
        includes/Configuration.cpp includes/Configuration.h
        includes/Game.cpp includes/Game.h
        includes/Statistics.cpp includes/Statistics.h
        sources/Utils.cpp sources/Utils.h
        sources/Menu.cpp sources/Menu.h)