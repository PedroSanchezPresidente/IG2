#pragma once
#include "IG2Object.h"

const struct pale_params {
	float x = 50.0f;
	float y = 3.0f;
	float z = 15.0f;
};

const float PALE_HEIGHT = 4.5f;

class Pale : public IG2Object {
public:
	Pale(Vector3 initPos, SceneManager* sM, SceneNode* parentNode, int index) 
		: IG2Object(initPos, parentNode->createChildSceneNode("pale" + to_string(index)), sM, "cube.mesh")
	{
		setScale(Vector3(5, 0.3, 1));
	}
};