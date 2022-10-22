#!/bin/bash

TIMEFORMAT=%R

say()
{
	echo -e "$@"
}

say ""

say "Updating textures..."
TEXTURES=""
for i in res/texture/*.png
do
	TEXTURES="$TEXTURES $i"
done
tcomp res/TEXTURE.c $TEXTURES
say "Done updating textures.\n"

say "Updating shaders..."
SHADERS=""
for i in res/shader/*.fs
do
	SHADERS="$SHADERS $i"
done
for i in res/shader/*.vs
do
	SHADERS="$SHADERS $i"
done
scomp res/SHADER.c $SHADERS
say "Done updating shaders.\n"

say "Compiling textures..."
TIMEA=$(date +%s%N)
clang++ -Wno-everything -c res/TEXTURE.c -DHL_COMPILE_RES -o bin/TEXTURE.o
TIMEB=$(($(date +%s%N)-$TIMEA))
TIME=$((TIMEB/1000000))
say "Done compiling textures in ${TIME} ms.\n"

say "Compiling shaders..."
TIMEA=$(date +%s%N)
clang++ -Wno-everything -c res/SHADER.c -DHL_COMPILE_RES -o bin/SHADER.o
TIMEB=$(($(date +%s%N)-$TIMEA))
TIME=$((TIMEB/1000000))
say "Done compiling shaders in ${TIME} ms.\n"

say "Done."