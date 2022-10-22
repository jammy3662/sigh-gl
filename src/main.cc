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
	openWindow(wwidth, wheight, fwidth, fheight, "sigh " VERSION " " PLATFORM);
	setFramerate(60);
	
	Shader baseShader;
	baseShader.setName("baseShader");
	//baseShader.load(basefsShaderCode, basevsShaderCode);
	
	Shader paintShader;
	paintShader.setName("paintShader");
	paintShader.load(painttestvsShaderCode, painttestfsShaderCode);
	
	Texture paintNoise;
	paintNoise.loadImage(paintnoiseImg);
	paintNoise.load();
	
	Texture paintBump;
	paintBump.loadImage(paintbumpImg);
	paintBump.load();
	
	Model stage;
	stage.loadFile("res/mesh/underpass.glb");
	
	while (running)
	{
		if (glfwWindowShouldClose(hl.window)) break;
		
		// limit frame rate and track frame duration
		calculateDelta();
		if (!frameStep()) continue;
		
		clearFrame(0.1, 0.1, 0.1, 1);
		
		useShader(&paintShader);
		paintShader.setTexture("paintnoise", paintNoise);
		paintShader.setTexture("paintbump", paintBump);
		
		stage.draw();
		
		presentFrame();
	}
	
	deinit();
	return 0;
}