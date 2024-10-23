#pragma once
#include "Tile.h"
#include "IG2Object.h"
class Perla : public Tile, public IG2Object
{
public :

	Perla(Vector3 v, SceneNode* n, SceneManager* mSM,std::string mat ,int points = 0, bool active = true, bool traspasable = true, const Vector3& scale = Vector3(1, 1, 1))
		:
		IG2Object(v, n, mSM, "sphere.mesh")
	{
		//Inicializar la textura etc
		setScale(scale);
		if(!active)
			setMaterialName(mat);
		traspasable_ = traspasable;
		active_ = active;
		setEntityVisible(active);
		points_ = points;
	}
	virtual void  interact(Heroe* h) override{
		if (active_) {
			if (getAABB().intersects(h->getAABB())) {
				setEntityVisible(false);
				h->addPoints(points_);
				active_ = false;
			}
		}
	}
private:
	bool active_;
	int points_;
	
};

