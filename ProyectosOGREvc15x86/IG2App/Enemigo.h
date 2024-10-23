#pragma once
#include "IG2Object.h"
#include "Helix.h"
#include "Body.h"
#include "Wheels.h"

class Labyrinth;

const float WHEELS_ROT = 1.0f;
const float BODY_ROT = -2.0f;
const float HELIX_ROT = 3.0f;

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
	Enemigo(Vector2 initPos, SceneNode* node, SceneManager* mSM, std::string bMat1, std::string bMat2, std::string hMat,Labyrinth* Lab = nullptr, int TileWidth = 1) : IG2Object(Vector3(initPos.y* TileWidth, 0, initPos.x* TileWidth), node, mSM), lab(Lab), tileWidth(TileWidth), actualPos(initPos), distance(0) {
		buildVillano(bMat1, bMat2, hMat);
	}

	void buildVillano(std::string bodyMat1, std::string bodyMat2, std::string hMat) {
		Vector3 pos = getPosition();
		Vector3 bodyMid(0, (CUBE_SIZE * MID_SCALE.y)  / 2 + CUBE_SIZE * TOP_SCALE.y / 2, 0);
		Vector3 bP = pos + bodyMid ;
		Vector3 hP = bP + bodyMid +  Vector3(0 ,CUBE_SIZE * MID_SCALE.y +  CUBE_SIZE * PALE_SCALE.y * HELIX_SCALE.y, 0);

		helix = new Helix(hP, mSM, mNode, 5, "helice1", HELIX_ROT, hMat);
		body = new Body(bP, mSM, mNode, "body", BODY_ROT, bodyMat1, bodyMat2);
		wheels = new Wheels(pos , mSM, mNode, 4, "wheels", WHEELS_ROT);
	}

	void debugPositions() {
		auto pos = wheels->getPosition();
		cout << "POSICION RUEDAS: " << pos.x << ", " << pos.y << ", " << pos.z << endl;
		wheels->showBoundingBox(true);
		auto pos1 = body->getPosition();
		cout << "POSICION CUERPO: " << pos1.x << ", " << pos1.y << ", " << pos1.z << endl;
		body->showBoundingBox(true);
		auto pos2 = helix->getPosition();
		cout << "POSICION HELICES: " << pos2.x << ", " << pos2.y << ", " << pos2.z << endl;
		helix->showBoundingBox(true);

	}
};

