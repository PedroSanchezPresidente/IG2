#pragma once
#include "IG2Object.h"
class Tile : public IG2Object {
public:
	SceneNode* tileNode = nullptr;

	Tile(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, bool traspasable, const Vector3& scale = Vector3(1,1,1)) : IG2Object(initPos, node, sceneMng, mesh), traspasable_(traspasable) {
		//Inicializar la textura etc
		setScale(scale);
	}

	bool isTraspasable() { return traspasable_; }
private:
	bool traspasable_; 
};

