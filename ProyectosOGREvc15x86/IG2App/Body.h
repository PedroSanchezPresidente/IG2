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
	Body(Vector3 midPos, SceneManager* sm, SceneNode* parentNode, string nodeName, float rot, std::string mat1, std::string mat2) :
	IG2Object(midPos, parentNode->createChildSceneNode(nodeName), sm)
	{
		rotation_fact = Ogre::Degree(rot);
		float mid_size = CUBE_SIZE * MID_SCALE.y; 
		float top_size = CUBE_SIZE * TOP_SCALE.y; 
		Vector3 offset(0, mid_size / 2 + top_size / 2, 0);

		top = new IG2Object(midPos + offset, mNode->createChildSceneNode("bodytop_"+ nodeName), sm, "cube.mesh");
		top->setScale(TOP_SCALE);
		top->setMaterialName(mat1);
		mid = new IG2Object(midPos, mNode->createChildSceneNode("bodymid_"+ nodeName), sm, "cube.mesh");
		mid->setScale(MID_SCALE); 
		mid->setMaterialName(mat2);
		bot = new IG2Object(midPos - offset, mNode->createChildSceneNode("bodybot_" + nodeName), sm, "cube.mesh");
		bot->setScale(TOP_SCALE);
		bot->setMaterialName(mat1);
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