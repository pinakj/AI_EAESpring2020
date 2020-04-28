#include "Boid.h"

Boid::Boid(float tempX, float tempY, int tempRadius, int tempDistancetoTip)
{
	radius = tempRadius;
	distancetoTip = tempDistancetoTip;

	kinematic = new Kinematic();

	kinematic->pos = ofDefaultVec2(tempX, tempY);
	kinematic->linear = ofDefaultVec2(0.0, 0.0);
	kinematic->vel = ofDefaultVec2(0.0f, 0);
	kinematic->orientation = 0.0f;
	kinematic->rot = 0.0f;

	maxCrumbDrop = 0.25f;
	rateCrumbDrop = 0.0f;

	//std::vector<breadCrumb> breadCrumbs = new std::vector<breadCrumb>();
	breadCrumb temp;
	temp.bCumbPos = ofVec2f(kinematic->pos);
	breadCrumbs.push_back(temp);

}

void Boid::makeBoid(string dir)
{
	ofSetColor(0, 0, 0);

	ofPoint tempPoint;
	tempPoint.x = kinematic->pos.x;
	tempPoint.y = kinematic->pos.y;

	ofDrawCircle(tempPoint, radius);

	ofPoint trianglePoint1;
	ofPoint trianglePoint2;
	ofPoint triangePoint3;

	if (dir == "none")
	{
		trianglePoint1.x = tempPoint.x;
		trianglePoint1.y = tempPoint.y + radius;

		trianglePoint2.x = tempPoint.x;
		trianglePoint2.y = tempPoint.y - radius;

		triangePoint3.x = tempPoint.x + distancetoTip;
		triangePoint3.y = tempPoint.y;
	}

	if (dir == "down")
	{
		trianglePoint1.x = tempPoint.x - radius;
		trianglePoint1.y = tempPoint.y;

		trianglePoint2.x = tempPoint.x + radius;
		trianglePoint2.y = tempPoint.y;

		triangePoint3.x = tempPoint.x;
		triangePoint3.y = tempPoint.y + distancetoTip;
	}

	else if (dir == "left")
	{
		trianglePoint1.x = tempPoint.x;
		trianglePoint1.y = tempPoint.y + radius;

		trianglePoint2.x = tempPoint.x;
		trianglePoint2.y = tempPoint.y - radius;

		triangePoint3.x = tempPoint.x - distancetoTip;
		triangePoint3.y = tempPoint.y;
	}
	else if (dir == "up")
	{
		trianglePoint1.x = tempPoint.x - radius;
		trianglePoint1.y = tempPoint.y;

		trianglePoint2.x = tempPoint.x + radius;
		trianglePoint2.y = tempPoint.y;

		triangePoint3.x = tempPoint.x;
		triangePoint3.y = tempPoint.y - distancetoTip;
	}
	ofDrawTriangle(trianglePoint1, trianglePoint2, triangePoint3);
}

void Boid::dropCrumbs(float deltaTime)
{
	if (rateCrumbDrop >= maxCrumbDrop)
	{
		rateCrumbDrop = 0.0f;

		if (breadCrumbs[breadCrumbs.size() - 1].bCumbPos != kinematic->pos)
		{
			breadCrumb crumb;
			crumb.bCumbPos = ofVec2f(kinematic->pos);
			breadCrumbs.push_back(crumb);
		}
	}
	else
	{
		rateCrumbDrop = rateCrumbDrop + deltaTime;
	}
}

void Boid::update(float dt)
{
	kinematic->update(dt);
	dropCrumbs(dt);
}

void Boid::clearCrumbs()
{
	breadCrumbs.clear();
}
