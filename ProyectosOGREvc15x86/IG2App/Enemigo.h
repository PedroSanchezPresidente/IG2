#pragma once
#include "IG2Object.h"
#include "Helix.h"

class Labyrinth;

class Enemigo : public IG2Object
{
protected:
	Labyrinth* lab;
	int tileWidth;
	int distance;
	Vector3 dir = Vector3(0, 0, 0);
	Vector3 newDir = Vector3(0, 0, 0);
	Vector2 actualPos;
	int speed = 10;

	Helix* helix = nullptr;

	virtual void frameRendered(const Ogre::FrameEvent& evt);

public:
	Enemigo(Vector2 initPos, SceneNode* node, SceneManager* mSM, Labyrinth* Lab, int TileWidth) : IG2Object(Vector3(initPos.y* TileWidth, 0, initPos.x* TileWidth), node, mSM), lab(Lab), tileWidth(TileWidth), actualPos(initPos), distance(0) {
		// Set scale of Sinbad
		setScale(Vector3(10, 10, 10));
	}

	void buildVillano(SceneNode* vNode) {

	}

};

