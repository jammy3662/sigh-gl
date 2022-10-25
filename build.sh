#!/bin/bash

source ~/.bashalias # some helper functions
# (need this for 'contains' command)

IN="src/main.cc"
OUT="sigh"

VERSION=$(date +%-y.%-m.%-d)
PLATFORM=$(uname -m)

FLAGS="-Wno-write-strings -g3 -fno-caret-diagnostics -ferror-limit=150"
LINK="-L~/lib -Llib -lassimp -lstb -lglad -lGL -lglfw -lm -lpthread -ldl -lrt -lX11 -lenet"

clear

./buildRes.sh s

# compile code
clang++ -c $IN -o bin/main.o -isystem src -isystem inc -isystem ~/include $FLAGS -DVERSION="\"$VERSION\"" -DPLATFORM="\"$PLATFORM\"" -DDEBUG
SUCCESS=$?

# compile program with resource binary
clang++ bin/main.o bin/SHADER.o bin/TEXTURE.o -o "$OUT" -isystem src -isystem inc -isystem ~/include $FLAGS $LINK -DVERSION="\"$VERSION\"" -DPLATFORM="\"$PLATFORM\"" -DDEBUG

exit $SUCCESS
