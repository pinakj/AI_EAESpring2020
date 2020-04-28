#pragma once
#include "ofMain.h"
#include "ofApp.h"
#include <math.h>
class Boid
{
public:
	int radius;
	int distancetoTip;

	Boid(float,float,int,int);

public:

	struct Kinematic
	{
		ofDefaultVec2 pos;
		float orientation;
		ofVec2f vel;
		float rot;
		string curDirection;
		ofDefaultVec2 linear;
		float angular;
		float maxSpeed;
		float mass;

		Kinematic()
		{
			pos = ofDefaultVec2(0, 0);
			orientation = 0.0f;
			vel = ofVec2f(0, 0);
			rot = 0.0f;
			maxSpeed = 0.0f;
			mass = 15.0f;
		}
		void update(float time)
		{
			pos += vel * time + linear * 0.5f * (pow(time,2));
			orientation += rot * time;

			vel += linear * time;
			rot += angular * time;

			if (vel.length() > maxSpeed)
			{
				vel.normalize();
				vel *= maxSpeed;
			}
		}
		float getnewOrientation(float currentOrientation, ofDefaultVec2 vel)
		{
			if (vel.x > 0 || vel.y > 0)
			{
				return atan2(vel.y, vel.x);
			}
			else
			{
				return currentOrientation;
			}
		}
		
	}*kinematic;

public:

	struct breadCrumb
	{
		ofVec2f bCumbPos;
	};
	void makeBoid(string dir);
	void update(float dt);
	std::vector<breadCrumb> breadCrumbs;

private:
	void dropCrumbs(float deltaTime);
	void clearCrumbs();

	float rateCrumbDrop;
	float maxCrumbDrop;
};





