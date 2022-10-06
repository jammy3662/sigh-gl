#pragma once

#include <global.h>

enum BulletType: uint8
{
	BULLET_STREAM,
	BULLET_SPHERE,
	BULLET_SPLASH,
};

struct Bullet
{
	float radius; // hitbox radius
	float splashRadius;
	float chipRadius;
	
	float range; // how far shots travel before gravity takes effect
	float speed; // units per frame
	float gravity; // change per frame in downward velocity
	float gravityMax; // maximum downward velocity
	
	float damage; // damage dealt on direct hit
	float splashDamage;
	float chipDamage;
	
	float paintRadius; // radius of painted area
	uint16 rainFrames; // frames per rain drop
	
	float distanceTravelled;
	uint16 rainFramesElapsed;
	
	vec3 position;
	vec3 direction; // must be normalized!
	int8 falling = false;
	
	// determines how the bullet is rendered
	BulletType type;
};

void UpdateBullets(Array<Bullet*> bullets)
{
	for (int i = 0; i < bullets.size; i++)
	{
		Bullet& bullet = *bullets[i];
		
		if (bullet.falling)
		{
			bullet.direction.y -= bullet.gravity;
			bullet.direction.y = max(-bullet.gravityMax, bullet.direction.y);
		}
		
		// TODO:
		// implement physics checks
		// and rain droplets
		
		bullet.position = Vector3Add(
			bullet.position,
			Vector3Scale(bullet.direction, bullet.speed));
		bullet.distanceTravelled += bullet.speed;
		if (bullet.distanceTravelled >= bullet.range) bullet.falling = true;
		
		if (bullet.position.y < -10)
		{
			bullets.remove(i);
			free(&bullet);
		}
	}
}

void RenderBullets(Camera3D camera, Array<Bullet*> bullets)
{
	for (int i = 0; i < bullets.size; i++)
	{
		Bullet& bullet = *bullets[i];
		Vector2 screenPos = GetWorldToScreen(bullet.position, camera);
		DrawCircle(screenPos.x, screenPos.y, 1, {255,255,255,255});
	}
}