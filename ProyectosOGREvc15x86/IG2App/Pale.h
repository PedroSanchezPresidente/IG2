#pragma once
#include "IG2Object.h"

const Vector3 PALE_SCALE = { 5, 0.3, 1 };

class Pale : public IG2Object {
public:
	Pale(Vector3 initPos, SceneManager* sM, SceneNode* parentNode, int index) 
		: IG2Object(initPos, parentNode->createChildSceneNode("pale" + to_string(index) + "_" + parentNode->getName()), sM, "cube.mesh")
	{
		setScale(PALE_SCALE);
	}
};