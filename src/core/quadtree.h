#pragma once 

#include "render.h"

/*

Data structure for writing to and reading from
GPU-compatible quadtree structure (in an RGBA format?)

We use Color as the data type so we can pass the octree
to and from the GPU through shaders. This enables
hardware acceleration (blazingly fast =P)

*/

struct Quadtree
{
	
};