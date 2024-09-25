#pragma once
#include "IG2Object.h"
class Hueco : public IG2Object {
public:
	SceneNode* pearlNode = nullptr;

	Hueco(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : IG2Object(initPos, node, sceneMng, mesh) {
		//Inicializar la textura etc
		setScale(Vector3(0.1, 0.1, 0.1));
	}

};