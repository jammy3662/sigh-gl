#pragma once

#include "camera.h"
#include "weapon.h"

struct Player
{
	uint8 active = true;
	
	vec3 position;
	vec3 velocity;
	
	float height = 0.5;
	
	float walkspeed = 0.05;
	
	void move(vec3 delta)
	{
		// TODO: add physics code here
		// to prevent stuff like clipping,
		// gravity, and others
		position = Vector3Add(position, delta);
	}
	
	void init() override
	{
		position = {0,0,0};
		velocity = {0,0,0};
		
		Camera::init();
		orbit = false;
		orbitDist = 1;
	}
	
	void update() override
	{
		if (!process) return;
		
		vec2 dir = {0,0};
		
		if (IsKeyPressed(ktab))
		{
			orbit = !orbit;
		}
		
		if (IsKeyDown(knorth))
		{
			dir.y = 1;
		}
		else if (IsKeyDown(ksouth))
		{
			dir.y = -1;
		}
		
		if (IsKeyDown(keast))
		{
			dir.x = -1;
		}
		else if (IsKeyDown(kwest))
		{
			dir.x = 1;
		}
		
		if (IsKeyDown(kjump))
		{
			move({0,walkspeed,0});
		}
		else if (IsKeyDown(kctrl))
		{
			move({0,-walkspeed,0});
		}
		
		dir = Vector2Rotate(dir, 2*M_PI - yaw);
		dir = Vector2Normalize(dir);
		dir = Vector2Scale(dir, walkspeed);
		
		move({dir.x, 0, dir.y});
		
		anchor = {position.x, position.y + height, position.z};
		Camera::update();
		Camera::refresh();
	}
	
	void render() override
	{
		if (orbit)
		{
			
		}
	}
};