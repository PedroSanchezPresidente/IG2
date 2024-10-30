#pragma once
#include "Heroe.h"
class Tile : public IG2Object {
public:
	Tile(Vector3 v, SceneNode* n, SceneManager* mSM, std::string mat) : IG2Object(v, n, mSM, mat) {};
	Tile(bool traspasable = true) : traspasable_(traspasable){};

	bool isTraspasable() { return traspasable_; }
	virtual void interact(Heroe* h) {};
	virtual void restart() {};
protected:
	bool traspasable_; 
};

