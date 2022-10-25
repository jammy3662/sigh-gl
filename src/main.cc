#include "core/defs.h"

#include <libhl/hl.h>
#include "core/global.h"

// header containing named char*'s to shader code
#include "../res/SHADER.c"
// header containing pre-populated Image structs
#include "../res/TEXTURE.c"

//#include <game/game.h>

int8 running = true;

int main(int argc, char** argv)
{	
	init();
	setFrame(1920, 1080);
	setWindow(1080, 720);
	openWindow("sigh " VERSION " " PLATFORM);
	setFramerate(60);
	
	Shader paintShader = createShader(basevsShaderCode, painttestfsShaderCode);
	paintShader.setName("paintShader");
	
	Texture paintNoise = createTexture(paintnoiseImg);
	uploadTexture(paintNoise);
	
	Texture paintBump = createTexture(paintnoiseImg);
	uploadTexture(paintBump);
	
	Model stage = createModel("res/mesh/gltest.glb");
	
	Frame testbuffer = createFrame(1, 0, hl.fwidth, hl.fheight);
	
	while (running)
	{
		if (glfwWindowShouldClose(hl.window)) break;
		
		if (!shouldRender()) continue;
		
		enableFrame(testbuffer);
		clearFrame(0.1, 0.1, 0.1, 1);
		
		useShader(&paintShader);
		paintShader.setTexture("paintnoise", paintNoise);
		paintShader.setTexture("paintbump", paintBump);
		
		stage.draw();
		
		defaultFrame();
		
		// TODO:
		// draw final screen quad;
		// this is where post-processing
		// and scaling and stuff happens
		
		presentFrame();
	}
	
	deinit();
	return 0;
}