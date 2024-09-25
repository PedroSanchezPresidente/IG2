#pragma once
#include "IG2Object.h"
 
class Muro : public IG2Object
{
public: 

	Muro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : IG2Object(initPos, node, sceneMng, mesh) {
		// Setea textura de muro
		setScale(Vector3(1, 1, 1));

	}

};

