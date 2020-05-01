#include "Algorithm.h"
#include "ofApp.h"
#include "Boid.h"

Algorithm::Algorithm()
{
	nextMovementIndex = 1;
}

void Algorithm::basicMotion(Boid *boid)
{
	ofVec2f curVel;
	if (int(boid->kinematic->pos.x) >= 50 && int(boid->kinematic->pos.y) <= 50)
	{
		if (int(boid->kinematic->pos.x) >= 1850)
		{
			curVel.set(0.0, 150.0f);
			boid->kinematic->curDirection = "down";
		}
		else
		{
			curVel.set(150.0f, 0.0f);
			boid->kinematic->curDirection = "none";
		}
	}
	else if (int(boid->kinematic->pos.x) >= 1850 && int(boid->kinematic->pos.y) <= 1020)
	{
		if ((int)boid->kinematic->pos.y > 1020)
		{
			curVel.set(-150.0f, 0.0f);
			boid->kinematic->curDirection = "left";
		}
		else
		{
			curVel.set(0.0, 150.0f);
			boid->kinematic->curDirection = "down";
		}

	}
	else if (int(boid->kinematic->pos.y) > 1020 && int(boid->kinematic->pos.x) > 50)
	{
		if (int(boid->kinematic->pos.x) <= 55)
		{
			curVel.set(0.0, -150.0f);
			boid->kinematic->curDirection = "up";
		}
		else
		{
			curVel.set(-150.0f, 0.0f);
			boid->kinematic->curDirection = "left";
		}
	}
	else
	{
		curVel.set(0.0, -150.0f);
		boid->kinematic->curDirection = "up";

	}

	boid->kinematic->vel = ofDefaultVec2(curVel.x, curVel.y);
}

void Algorithm::snapToDirection(Boid* boid)
{
	boid->kinematic->orientation = atan2(boid->kinematic->vel.y, boid->kinematic->vel.x);
}

Algorithm::SteeringOutput * Algorithm::dynamicSeek(Boid * character, Boid * target, float maxLinear)
{
	Algorithm::SteeringOutput *steering = new Algorithm::SteeringOutput();
	steering->linear = target->kinematic->pos - character->kinematic->pos;
	steering->linear = steering->linear.normalize();
	steering->linear *= maxLinear;

	steering->angular = 0;
	return steering;
}

Algorithm::SteeringOutput * Algorithm::dynamicAlign(Boid * character, Boid * target, float targetRadius, float slowRadius, float maxAngular, float maxRotation)
{
	Algorithm::SteeringOutput *steering = new Algorithm::SteeringOutput();

	float rotation = target->kinematic->orientation - character->kinematic->orientation;

	//Mapping to range
	while (rotation > PI || rotation < -PI)
	{
		if (rotation > PI)
		{
			rotation = rotation - 2 * PI;
		}
		else
		{
			rotation = rotation + 2 * PI;
		}
	}

	float rotationSize = abs(rotation);

	float targetRotation = 0;

	if (rotationSize > slowRadius)
	{
		targetRotation = maxRotation;
	}
	else if (rotationSize < targetRadius)
	{
		targetRotation = 0.0f;
	}
	else
	{
		targetRotation = maxRotation * rotationSize / slowRadius;
	}
	targetRotation *= rotation / rotationSize;

	steering->angular = targetRotation - character->kinematic->rot;
	steering->angular /= 0.1f;

	float angularAcceleration = abs(steering->angular);

	if (angularAcceleration > maxAngular)
	{
		steering->angular /= angularAcceleration;
		steering->angular *= maxAngular;
	}

	steering->linear = ofVec2f(0.0f, 0.0f);

	return steering;
}

Algorithm::SteeringOutput * Algorithm::faceTarget(Boid * character, Boid * target, float targetRadius, float slowRadius, float maxAngular, float maxRotation)
{
	Algorithm::SteeringOutput* temp = new Algorithm::SteeringOutput();
	ofVec2f dir = target->kinematic->pos - character->kinematic->pos;
	if (dir.length() != 0)
	{
		target->kinematic->orientation = atan2(dir.y, dir.x);

		return Algorithm::dynamicAlign(character, target, targetRadius, slowRadius, maxAngular, maxRotation);
	}
	else
	{
		return new Algorithm::SteeringOutput();
	}
}

Algorithm::SteeringOutput * Algorithm::dynamicWander(Boid * character, float & wanderOrientation, float wanderOffset, float wanderRadius, float wanderRate, float maxAngular, float maxLinear)
{
	Algorithm::SteeringOutput* temp = new Algorithm::SteeringOutput();

	Boid* target = new Boid(0, 0, 0, 0);

	float randomBinomial = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	wanderOrientation += randomBinomial * wanderRate;

	float targetOrientation = wanderOrientation + character->kinematic->orientation;

	target->kinematic->pos = character->kinematic->pos + wanderOffset * (ofVec2f(cos(character->kinematic->orientation), sin(character->kinematic->orientation)));
	target->kinematic->pos = target->kinematic->pos + wanderOffset * (ofVec2f(cos(target->kinematic->orientation), sin(target->kinematic->orientation)));

	temp = Algorithm::faceTarget(character, target, 0.069f, 0.069f*100.0f, maxAngular, 2 * PI);

	temp->linear = maxLinear * ofVec2f(cos(character->kinematic->orientation), sin(character->kinematic->orientation));

	return temp;
}

Algorithm::SteeringOutput * Algorithm::separation(Boid * character, std::vector<Boid*> targets, float threshold, float decayCoeff, float linear)
{
	Algorithm::SteeringOutput* temp = new Algorithm::SteeringOutput();

	for (Boid* target : targets)
	{
		if (target != character)
		{
			ofVec2f dir = character->kinematic->pos - target->kinematic->pos;
			float dist = dir.length();

			if (dist <= threshold)
			{
				float str = MIN(decayCoeff / (pow(dist, 2)), linear);
				dir = dir.normalize();
				temp->linear += str * dir;
			}
		}
	}

	return temp;
}

Algorithm::SteeringOutput * Algorithm::velocityMatch(Boid * character, Boid * target, float maxLinear)
{
	float timeToTarget = 0.1f;

	Algorithm::SteeringOutput* temp = new Algorithm::SteeringOutput();

	temp->linear = target->kinematic->linear - character->kinematic->vel;
	temp->linear /= timeToTarget;

	if (temp->linear.length() > maxLinear)
	{
		temp->linear = temp->linear.normalize();
		temp->linear *= maxLinear;
	}

	temp->angular = 0.0f;

	return temp;
}

Algorithm::SteeringOutput * Algorithm::lookWhereYouAreGoing(Boid * character, float targetRadius, float slowRadius, float maxAngular, float maxRotation)
{
	Boid *target = new Boid(0, 0, 0, 0);

	ofVec2f charVel = character->kinematic->vel;

	if (charVel.length() == 0)
	{
		return new Algorithm::SteeringOutput();
	}
	target->kinematic->orientation = atan2(charVel.y, charVel.x);

	return Algorithm::dynamicAlign(character, target, targetRadius, slowRadius, maxAngular, maxRotation);
}

Algorithm::SteeringOutput * Algorithm::DynamicArrive(Boid * character, Boid * target, float targetRadius, float slowRadius, float maxLinear)
{
	Algorithm::SteeringOutput* temp = new Algorithm::SteeringOutput();

	ofVec2f dir = target->kinematic->pos - character->kinematic->pos;
	float dist = dir.length();
	float targetSpeed = 0.0f;
	ofVec2f targetVel;

	if (dist > slowRadius)
	{
		targetSpeed = character->kinematic->maxSpeed;
	}
	else if (dist < targetRadius)
	{
		targetSpeed = 0.0f;
	}
	else
	{
		targetSpeed = character->kinematic->maxSpeed * (dist / slowRadius);
	}

	targetVel = dir;
	targetVel = targetVel.normalize();
	targetVel *= targetSpeed;

	temp->linear = targetVel - character->kinematic->vel;
	temp->linear /= 0.1f;

	if (temp->linear.length() > maxLinear)
	{
		temp->linear = temp->linear.normalize();
		temp->linear *= maxLinear;
	}

	temp->angular = 0.0f;

	return temp;
}






