#include "core/defs.h"

// header containing named char*'s to shader code
#include "../res/SHADER.c"
// header containing pre-populated Image structs
#include "../res/TEXTURE.c"

#include <libhl/hl.h>
#include "core/global.h"

//#include <game/game.h>

int8 running = true;

int main(int argc, char** argv)
{	
	init();
	setFrame(1920, 1080);
	setWindow(1080, 720);
	openWindow("sigh " VERSION " " PLATFORM);
	setFramerate(60);
	setup();
	
	Shader paintShader = createShader(basevsShaderCode, painttestfsShaderCode);
	paintShader.setName("paintShader");
	
	Texture paintNoise = createTexture(&paintnoiseImg);
	
	Texture paintBump = createTexture(&paintnoiseImg);
	
	Model stage = createModel("res/mesh/underpass.glb");
	
	Frame testbuffer = createFrame(1, 0, hl.fwidth, hl.fheight);
	
	while (running)
	{
		if (glfwWindowShouldClose(hl.window)) break;
		
		if (!shouldRender()) continue;
		
		clearTextures();
		
		enableFrame(&testbuffer);
		clearFrame(0.1, 0.1, 0.1, 1);
		
		useShader(&paintShader);
		paintShader.setTexture("paintnoise", paintNoise);
		paintShader.setTexture("paintbump", paintBump);
		
		stage.draw();
		
		defaultFrame();
		
		//
		// draw final screen quad;
		// this is where post-processing
		// and scaling and stuff happens
		//
		
		clearFrame(0,0,0.2,1);
		//drawRect(0,0, fwidth, fheight, {0.5,0,1,1});
		drawTexture(testbuffer.color, 0, 0, fwidth/2, fheight/2, {1,1,1,1});
		
		presentFrame();
	}
	
	deinit();
	return 0;
}