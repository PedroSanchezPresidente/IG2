#pragma once
#include "IG2Object.h"

const float CUBE_SIZE = 100.0f;
const Vector3 TOP_SCALE = { 1, 0.5, 1 };
const Vector3 MID_SCALE = { 1, 0.25, 1 };

class Body : public IG2Object {
private:

	IG2Object* top = nullptr;
	IG2Object* mid = nullptr;
	IG2Object* bot = nullptr;

	const float heightFact = 0.5;

	Ogre::Degree rotation_fact;
	
public:
	Body(Vector3 midPos, SceneManager* sm, SceneNode* parentNode, string nodeName, float rot) :
	IG2Object(midPos, parentNode->createChildSceneNode("nodeName"), sm)
	{
		rotation_fact = Ogre::Degree(rot);
		float mid_size = CUBE_SIZE * MID_SCALE.y; 
		float top_size = CUBE_SIZE * TOP_SCALE.y; 
		Vector3 offset(0, mid_size / 2 + top_size / 2, 0);

		top = new IG2Object(midPos + offset, mNode->createChildSceneNode("bodytop"), sm, "cube.mesh");
		top->setScale(TOP_SCALE);
		mid = new IG2Object(midPos, mNode->createChildSceneNode("bodymid"), sm, "cube.mesh");
		mid->setScale(MID_SCALE);
		bot = new IG2Object(midPos - offset, mNode->createChildSceneNode("bodybot"), sm, "cube.mesh");
		bot->setScale(TOP_SCALE);
	}

	~Body() {
		if (top != nullptr && mid != nullptr && bot != nullptr) {
			delete top;
			delete mid;
			delete bot;
			top = nullptr;
			mid = nullptr;
			bot = nullptr;
		}
	}

	void update() {
		mid->yaw(rotation_fact);
	}
};