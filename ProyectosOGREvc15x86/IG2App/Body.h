#pragma once
#include "IG2Object.h"

const float BODYPART_HEIGHT = 50.0f;
class Body{
private:
	SceneNode* bNode = nullptr;

	IG2Object* top = nullptr;
	IG2Object* mid = nullptr;
	IG2Object* bot = nullptr;

	const float heightFact = 0.5;
	const Vector3 columnScale = {2.8, (Ogre::Real)(0.23 * heightFact), 2.8};

	Ogre::Degree rotation_fact;
	
public:
	Body(Vector3 midPos, SceneManager* sm, SceneNode* parentNode, string nodeName, float rot) {

		bNode = parentNode->createChildSceneNode(nodeName);
		rotation_fact = Ogre::Degree(rot);
		top = new IG2Object(midPos + Vector3(0, BODYPART_HEIGHT - (BODYPART_HEIGHT / 4), -BODYPART_HEIGHT / 2), bNode->createChildSceneNode("bodytop"), sm, "column.mesh");
		top->setScale(columnScale);
		mid = new IG2Object(midPos, bNode->createChildSceneNode("bodymid"), sm, "cube.mesh");
		mid->setScale(Vector3(1, heightFact, 1));
		bot = new IG2Object(midPos - Vector3(0, BODYPART_HEIGHT + (BODYPART_HEIGHT / 4), +BODYPART_HEIGHT / 2), bNode->createChildSceneNode("bodybot"), sm, "column.mesh");
		bot->setScale(columnScale);
	}

	~Body() {
		delete top;
		delete mid;
		delete bot;
		delete bNode;
		top = nullptr;
		mid = nullptr;
		bot = nullptr;
		bNode = nullptr;
	}

	void update() {
		mid->yaw(rotation_fact);
	}
};