#pragma once
#include "IG2Object.h"

class Labyrinth;

class Heroe : public IG2Object
{
protected:
	Labyrinth* lab; 
	int tileWidth;
	int distance;
	Vector3 dir = Vector3(0,0,0);
	Vector3 newDir = Vector3(0, 0, 0);
	int speed = 2;

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);

public:
	Heroe(Vector3 v, SceneNode* node, SceneManager* mSM, String mesh, Labyrinth* Lab, int TileWidth) : IG2Object(v, node, mSM, mesh), lab(Lab), tileWidth(TileWidth), distance(0) {
		// Set scale of Sinbad
		setScale(Vector3(10, 10, 10));
	}

	void addPoints(int p);
	
};

