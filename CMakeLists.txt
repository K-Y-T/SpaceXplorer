cmake_minimum_required(VERSION 3.30)
project(SpaceXplorer C)

set(CMAKE_C_STANDARD 99)

add_executable(SpaceXplorer main.c
        world.c
        gameobjects.h
        world.h
        gameobjects.c
        spaceship.c
        spaceship.h)
