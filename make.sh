#!/bin/env bash
set -xe

CFLAGS="-Wall -Wextra -Isrc/"
LIBS="-lGL -lglfw"
DIRBUILD="./build"

gcc $CFLAGS $LIBS -o $DIRBUILD/main src/gl.c src/main.c
