#pragma once
#include "ofApp.h"

class Boid;

class Algorithm
{
public:

	struct SteeringOutput
	{
	public:
		ofVec2f linear;
		float angular;

		SteeringOutput()
		{
			angular = 0.0f;
			linear = ofDefaultVec2(0, 0);
		}
	}steering;

	static void basicMotion(Boid *kinematic);

	static void snapToDirection(Boid *boid);

	static Algorithm::SteeringOutput *dynamicSeek(Boid* character, Boid* target, float maxLinear);

	static Algorithm::SteeringOutput* dynamicAlign(Boid * character, Boid* target, float targetRadius, float slowRadius, float maxAngular, float maxRotation);

	static Algorithm::SteeringOutput* faceTarget(Boid* character, Boid* target, float targetRadius, float slowRadius, float maxAngular, float maxRotation);

	static Algorithm::SteeringOutput* dynamicWander(Boid* character, float& wanderOrientation, float wanderOffset, float wanderRadius, float wanderRate, float maxAngular, float maxLinear);

	static Algorithm::SteeringOutput* separation(Boid* character, std::vector<Boid*> targets, float threshold, float decayCoeff, float linear);

	static Algorithm::SteeringOutput* velocityMatch(Boid* character, Boid* target, float maxLinear);

	static Algorithm::SteeringOutput* lookWhereYouAreGoing(Boid * character, float targetRadius, float slowRadius, float maxAngular, float maxRotation);

	static Algorithm::SteeringOutput* DynamicArrive(Boid * character, Boid* target, float targetRadius, float slowRadius, float maxLinear);

};

