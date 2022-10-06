#!/bin/bash

TIMEFORMAT=%R

echo ""

echo "Compiling textures..."
TIMEA=$(date +%s%N)
clang++ -Wno-everything -c res/TEXTURE.c -DHL_COMPILE_RES -o bin/TEXTURE.o
TIMEB=$(($(date +%s%N)-$TIMEA))
TIME=$((TIMEB/1000000))
echo -e "Done compiling textures in ${TIME} ms.\n"

echo "Compiling shaders..."
TIMEA=$(date +%s%N)
clang++ -Wno-everything -c res/SHADER.c -DHL_COMPILE_RES -o bin/SHADER.o
TIMEB=$(($(date +%s%N)-$TIMEA))
TIME=$((TIMEB/1000000))
echo -e "Done compiling shaders in ${TIME} ms.\n"

echo "Done."