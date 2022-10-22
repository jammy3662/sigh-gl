#pragma once

#define PATH_DELIMETER '/'

#ifdef _WIN32
	#include <windows.h>
	#include <stdio.h>
	#include <tchar.h>

	#define DIV 1048576 
	#define WIDTH 7
	#define PATH_DELIMER '\'
#endif

#ifdef linux
	#include <unistd.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
#endif