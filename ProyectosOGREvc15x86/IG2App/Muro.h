#pragma once
#include "Tile.h"
#include "IG2Object.h"
class Muro : public Tile, public IG2Object 
{
public:

	Muro(Vector3 v, SceneNode* n, SceneManager* mSM, bool traspasable = false, const Vector3& scale = Vector3(1, 1, 1)) 
		: IG2Object(v, n, mSM, "cube.mesh") {
		//Inicializar la textura etc
		setScale(scale);
		traspasable_ = traspasable;
	}

	Muro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, bool traspasable = false, const Vector3& scale = Vector3(1, 1, 1)) 
		:
		IG2Object(initPos, node, sceneMng, mesh) 
	{
		//Inicializar la textura etc
		setScale(scale);
		traspasable_ = traspasable;
	}
	virtual void interact(Heroe* h) {}
};

