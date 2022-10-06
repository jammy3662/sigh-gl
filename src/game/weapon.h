#pragma once

#include <global.h>
#include <bullet.h>

enum MainWeaponClass
{
	MAIN_SHOOTER,
	MAIN_SEMI,
	MAIN_GATLING,
	MAIN_BLASTER,
	MAIN_CHARGER,
	MAIN_BRUSH,
	MAIN_ROLLER,
	MAIN_BUCKET,
};

// static data for each weapon class
union MainWeaponClassData
{
	struct
	{
		uint16 shotTime; // frames per shot
	}
	shooter;
	
	struct
	{
		uint16 shotTime; // frames per shot
		uint16 shotCount; // bullets per shot
		uint16 fireTime; // frames of continuous shots
	}
	semi;
	
	struct
	{
		uint16 shotTime; // frames per shot
		uint16 shotCount; // bullets per shot
		uint16 chargeBase, chargeMax; // frames of charge
	}
	gatling;
	
	struct
	{
		uint16 shotTime; // frames per shot
		float splashDamage, splashRadius;
		float chipDamage, chipRadius;
	}
	blaster;
	
	struct
	{
		uint8 isScoped;
		uint8 isStorable;
		uint16 chargeMax; // frames of charge
		uint16 storeTime; // frames of held charge
		float scopeFov; // zoom value in fov (degrees)
	}
	charger;
	
	struct
	{
		float width; // width of painted surface when rolling
		uint16 shotCount;
		float rollSpeedFac; // multiplier of base speed for rolling
	}
	brush;
	
	struct
	{
		float width; // width of painted surface when rolling
		uint16 flickShotCount, flingShotCount;
		float flingSpread, flingRange;
		float rollSpeedFac; // multiplier of base speed for rolling 
	}
	roller;
	
	struct
	{
		uint16 shotCount;
	}
	bucket;
};

// static data of main weapon
// used to pull stats
struct MainWeaponData
{
	uint16 type; // weapon class
	uint16 weight; // weight class
	uint16 delay; // frames between trigger press and action
	uint16 release; // frames between trigger release and action
	uint16 buffer; // frames between trigger release and tank refill
	
	float cost; // tank units consumed per shot fired
	
	float spreadAngle; // maximum horizontal angle of deviation of shots
	uint32 spreadInterval; // interval after which deviation multiplies
	float spreadFactor; // multiplier of deviation per interval
	
	MainWeaponClassData classData;
	
	Bullet bullet;
};

// in-game data pertaining to weapon state
// manipulated in real time with player inputs
// (pointer fields are for shared data between weapon class and player class)
struct MainWeapon
{
	uint16 delay; // frames between trigger press and action
	uint16 release; // frames between trigger release and action
	uint16 buffer; // frames between trigger release and tank refill
	
	float tank; // amount of paint in tank (0 - 100)
	
	uint16 shotTime; // frames since last shot
	uint16 fireTime; // frames since first shot of fire period
	uint16 charge; // frames of charge stored in weapon
	uint16 chargeHoldTime; // frames of held charge remaining
	
	uint8 triggerHeld = false;
	
	/*
		when rolling, a shield is formed by the roller
		in front of the player, which absorbs a certain
		amount of damage before forcing the roller out of
		the rolling state, with a cooldown before rolling again
	*/
	float rollerHp;
	uint16 rollerCooldown; // time in frames
	
	MainWeaponData stats;
};

// contains relevant fields for in-game
// manipulation and game-loop stuff
struct MainWeaponNode: public virtual MainWeapon
{
	vec3 position;
	Model model;
};

void UpdateShooter(MainWeaponNode& weapon, Array<Bullet*> bullets)
{
	if (weapon.triggerHeld)
	{
		if (weapon.delay--) return;
		
		if (weapon.shotTime)
		{
			weapon.shotTime--;
			return;
		}
		
		Bullet* bullet = talloc(1, Bullet);
		*bullet = weapon.stats.bullet;
		bullet->rainFramesElapsed = 0;
		bullet->distanceTravelled = 0;
		bullets.append(bullet);
		
		weapon.shotTime = weapon.stats.classData.shooter.shotTime;
	}
	else
	{
		if (weapon.release) weapon.release--;
		else
		{
			weapon.delay = weapon.stats.delay;
			weapon.shotTime = 0; // fire immediately after delay
		}
		
		if (weapon.buffer) weapon.buffer--;
	}
}

void UpdateMainWeapon(MainWeapon& weapon, Array<Bullet> bullets)
{
	switch (weapon.stats.type)
	{
		case MAIN_SHOOTER:
			if (weapon.delay--)
			{
				weapon.shotTime = weapon.stats.classData.shooter.shotTime;
				break;
			}
			if (weapon.shotTime)
			{
				weapon.shotTime--;
				break;
			}
			break;
	}
}

float calculateSpread(uint32 interval, float factor, float angle)
{
	uint32 iter = (rand() % 1000) % interval;
}

//void fireShooter(MainWeapon weapon)
