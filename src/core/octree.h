#pragma once 

#include "render.h"

/*

Data structure for writing to and reading from
GPU-compatible octree structure (in an RGBA format?)

We use Color as the data type so we can pass the octree
to and from the GPU through shaders. This enables
hardware acceleration (blazingly fast =P)

*/

struct Octree
{	
	Color* buffer = 0;
	Texture3D handle;
	
	// returns zero/false if creation failed
	// possibly due to lack of memory
	int8 create(int16 width, int16 height, int16 depth)
	{
		if (buffer)
		{
			fprintf(stderr, "Octree duplicate creation at %p\n", this);
		}
		
		buffer = talloc(width * height * depth, Color);
		
		if (!buffer)
		{
			fprintf(stderr, "Octree buffer creation failed at %p\n", this);
			return false;
		}
		
		handle = LoadTexture3D(width, height, depth, &buffer->r);
		printf("Octree created with id %i at octree %p\n", handle.id, this);
		
		return true;
	}
	
	void destroy()
	{
		if (buffer) free(buffer);
	}
	
	#ifdef DEBUG
	// lets make sure we avoid these
	// kinds of easy-to-prevent memory leaks
	int8 validate()
	{
		if (!buffer)
		{
			fprintf(stderr, "Octree use before creation at %p\n", this);
			return false;
		}
		return true;
	}
	#endif
	
	void addleaf(Color leaf, vec3 point)
	{
		if (!validate()) return;
		
		
	}
	
	// Search the octree recursively
	// for _point_, return the Color
	// stored at that leaf
	Color getleaf(vec3 point)
	{
		if (!validate())
		{
			errcode = 1;
			return {0,0,0,0};
		}
		
		Color ret;
		
		// how about you write code to get the color here, huh?
		
		//buffer[0]
		
		return ret;
	}
};