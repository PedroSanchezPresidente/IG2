#pragma once
#include "IG2Object.h"
#include "Helix.h"
#include "Body.h"
#include "Wheels.h"

class Labyrinth;

const float WHEELS_ROT = 1.0f;
const float BODY_ROT = -2.0f;
const float HELIX_ROT = 1.0f;

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
	Wheels* wheels = nullptr;
	Body* body = nullptr;

	virtual void frameRendered(const Ogre::FrameEvent& evt);

public:
	Enemigo(Vector2 initPos, SceneNode* node, SceneManager* mSM, Labyrinth* Lab = nullptr, int TileWidth = 1) : IG2Object(Vector3(initPos.y* TileWidth, 0, initPos.x* TileWidth), node, mSM), lab(Lab), tileWidth(TileWidth), actualPos(initPos), distance(0) {
		buildVillano();
	}

	void buildVillano() {
		helix = new Helix(Vector3(0, 0, 0), mSM, mNode, 5, "helice1", HELIX_ROT);
		body = new Body(Vector3(0, -(PALE_HEIGHT + BODYPART_HEIGHT + BODYPART_HEIGHT / 2), 0), mSM, mNode, "body", BODY_ROT);
		wheels = new Wheels(Vector3(0, -(PALE_HEIGHT + 1.5 * BODYPART_HEIGHT), 0), mSM, mNode, 4, "wheels", WHEELS_ROT);
	}

};

