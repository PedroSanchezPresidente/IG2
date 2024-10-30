#pragma once
#include "Tile.h"
#include "IG2Object.h"
class Muro : public Tile 
{
public:

	Muro(Vector3 v, SceneNode* n, SceneManager* mSM, std::string mat,bool traspasable = false, const Vector3& scale = Vector3(1, 1, 1)) 
		: Tile(v, n, mSM, "cube.mesh") {
		//Inicializar la textura etc
		setScale(scale);
		traspasable_ = traspasable;
		setMaterialName(mat);
	}
	virtual void interact(Heroe* h) {}
};

