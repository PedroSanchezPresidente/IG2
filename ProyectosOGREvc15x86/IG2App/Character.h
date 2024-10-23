#pragma once
#include "IG2Object.h"
class Labyrinth;

class Character : public IG2Object
{
protected:
	Labyrinth* lab;
	int tileWidth;
	int distance;
	Vector3 dir = Vector3(0, 0, 0);
	Vector3 newDir = Vector3(0, 0, 0);
	int speed = 2;

public:
	Character(Vector3 v, SceneNode* node, SceneManager* mSM, Labyrinth* Lab, int TileWidth) : IG2Object(v, node, mSM), lab(Lab), tileWidth(TileWidth), distance(0) {};
	Character(Vector3 v, SceneNode* node, SceneManager* mSM, String mesh, Labyrinth* Lab, int TileWidth) : IG2Object(v, node, mSM, mesh), lab(Lab), tileWidth(TileWidth), distance(0) {};

	virtual void frameRendered(const Ogre::FrameEvent& evt);
};

