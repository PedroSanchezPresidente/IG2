#pragma once
#include "Tile.h"
#include "IG2Object.h"
class Perla : public Tile, public IG2Object
{
public :

	Perla(Vector3 initPos, SceneNode* node, SceneManager* sceneMng,int points, bool active = true, bool traspasable = true, const Vector3& scale = Vector3(1, 1, 1))
		: IG2Object(initPos, node, sceneMng) {
		//Inicializar la textura etc
		setScale(scale);
		traspasable_ = traspasable;
		active_ = active;
		points_ = points;
	}
	Perla(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, int points, bool active = true, bool traspasable = true, const Vector3& scale = Vector3(1, 1, 1))
		:
		IG2Object(initPos, node, sceneMng, mesh)
	{
		//Inicializar la textura etc
		setScale(scale);
		traspasable_ = traspasable;
		active_ = active;
		points_ = points;
	}
	virtual void  interact(Heroe* h) override{
		if (active_) {
			setEntityVisible(false);
			h->addPoints(points_);
			active_ = false;
		}
	}
private:
	bool active_;
	int points_;
	
};

