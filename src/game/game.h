#pragma once

#include "player.h"

const uint8 MAX_PLAYERS = 20;

struct Game
{
	Tween tween;
	
	Camera* curCamera;
	Player players[MAX_PLAYERS];
	Player& player = players[0];
	
	char* stageResPath;
	Model stage;
	
	Texture paintNoise;
	Texture paintBump;
	Texture reflectionMap; // cubemap
	
	RenderTexture shadowMap;
	
	Shader depthShader;
	Shader paintShader;
	
	Camera sun;
	Color sunColor;
	
	void update()
	{
		
	}
};

Game gameNew()
{
	Game ret;
	
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		ret.players[i].active = false;
	}
	
	ret.paintNoise = GetTexture("paintnoise.png");
	ret.paintBump = GetTexture("paintbump.png");
	ret.reflectionMap = LoadCubemap(
		GetTexture("landscape-top.png"),
		GetTexture("landscape-bottom.png"),
		GetTexture("landscape-north.png"),
		GetTexture("landscape-south.png"),
		GetTexture("landscape-east.png"),
		GetTexture("landscape-west.png"),
	);
	
	ret.shadowMap = LoadRenderTexture(fwidth, fheight);
	
	ret.stage = GenerateStage(GetModel(ret.stageResPath));
	
	ret.light.fov = 90;
	ret.light.nearClip = 0.1;
	ret.light.farClip = 100;
	ret.light.upVector = {1,0,0};
	ret.light.projection = PROJECT_ORTHO;
	
	return ret;
}

void gameUpdate()
{
	dummyRefresh(dummies);
	
	playerUpdate(player);
}

void update()
{
	UpdateDummies(dummies);
	UpdatePlayer(player;
}


















//==============================================
/*

const int8 MAX_PLAYERS = 20;

enum
{
	GM_FFA = 1,
	GM_TURF,
	GM_TDM,
	GM_CTF,
	GM_HARPOON,
	GM_ORB,
	GM_RING,
	GM_TOWER,
	GM_MINES,
};

struct Scene
{
	Player player;
	Dummy players[MAX_PLAYERS];
	
	Model stage;
	
	int8 gameMode;
};

*/