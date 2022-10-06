#pragma once

#include <ext.h>
#include "global.h"

typedef void(* callback )();

#define WORLD  0 // 3d space
#define SCREEN 1 // 2d space

// node interface
struct Node
{	
	int8 active = true; // if unset, skips both update() and draw()
	int8 process = true; // if unset, skips update()
	int8 visible = true; // if unset, skips draw()

	virtual void init() {} // set initial state
	virtual void deinit() {} // deallocate and clean state
	virtual void update() {} // update state
	virtual void render() {} // render frame
};

/*
int8 active = true; // if unset, skips both update() and draw()
int8 process = true; // if unset, skips update()
int8 visible = true; // if unset, skips draw()
*/

