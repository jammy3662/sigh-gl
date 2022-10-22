#!/bin/bash

IN="src/main.cc"
OUT="sigh"

VERSION=$(date +%-y.%-m.%-d)
PLATFORM=$(uname -m)

FLAGS="-Wno-write-strings -g3 -fno-caret-diagnostics -ferror-limit=150"
LINK="-L~/lib -Llib -lassimp -lstb -lglad -lGL -lglfw -lm -lpthread -ldl -lrt -lX11 -lenet"

RUN_ON_BUILD=0
[ -z $1 ] && RUN_ON_BUILD=1

clear

clang++ -c $IN -o bin/main.o -isystem src -isystem inc -isystem ~/include $FLAGS -DVERSION="\"$VERSION\"" -DPLATFORM="\"$PLATFORM\"" -DDEBUG
SUCCESS=$?

clang++ bin/main.o bin/SHADER.o bin/TEXTURE.o -o "$OUT" -isystem src -isystem inc -isystem ~/include $FLAGS $LINK -DVERSION="\"$VERSION\"" -DPLATFORM="\"$PLATFORM\"" -DDEBUG

if [ $RUN_ON_BUILD = 0 ] && [ ! $SUCCESS -ne 0 ]; then
	"./$OUT"
fi

exit $SUCCESS
