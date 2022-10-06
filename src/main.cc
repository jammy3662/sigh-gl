#include <core/defs.h>

#include <libhl/hl.h>
using namespace HL;
#include <core/global.h>

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
	
	Texture paintNoise, paintBump;
	paintNoise.img.loadFile("res/texture/paintnoise.png");
	//paintNoise.img.load(
	paintNoise.load();
	paintBump.img.loadFile("res/texture/paintbump.png");
	paintBump.load();
	
	while (running)
	{
		if (glfwWindowShouldClose(hl.window)) break;
		
		// limit frame rate and track frame duration
		calculateDelta();
		if (!frameStep()) continue;
		
		Shader::clear();
		
		paintShader.use();
		paintShader.setTexture("paintnoise", paintNoise);
		paintShader.setTexture("paintbump", paintBump);
		
		glfwSwapBuffers(hl.window);
		glfwPollEvents();
	}
	
	deinit();
	return 0;
}