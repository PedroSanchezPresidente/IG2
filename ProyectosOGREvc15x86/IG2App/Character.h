#pragma once
#include "IG2Object.h"
class Labyrinth;

class Character : public IG2Object
{
protected:
	Vector3 iniPos;
	Labyrinth* lab;
	int tileWidth;
	int distance;
	Vector3 dir = Vector3(0, 0, 0);
	Vector3 newDir = Vector3(0, 0, 0);
	int speed = 2;
	bool _active = true;

public:
	Character(Vector3 v, SceneNode* node, SceneManager* mSM, Labyrinth* Lab, int TileWidth) : IG2Object(v, node, mSM), lab(Lab), tileWidth(TileWidth), distance(0), iniPos(v) {};
	Character(Vector3 v, SceneNode* node, SceneManager* mSM, String mesh, Labyrinth* Lab, int TileWidth) : IG2Object(v, node, mSM, mesh), lab(Lab), tileWidth(TileWidth), distance(0), iniPos(v) {};

	virtual void frameRendered(const Ogre::FrameEvent& evt);

	virtual void restart() {};

	void setActive(bool b) { _active = b; };
};

