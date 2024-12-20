#pragma once
#include "Character.h"
#include "Helix.h"
#include "Body.h"
#include "Wheels.h"

const float WHEELS_ROT = 1.0f;
const float BODY_ROT = -2.0f;
const float HELIX_ROT = 3.0f;

class Enemigo : public Character
{
protected:
	int id;
	Helix* helix = nullptr;
	Wheels* wheels = nullptr;
	Body* body = nullptr;

	

	virtual void frameRendered(const Ogre::FrameEvent& evt);

public:
	Enemigo(Vector3 initPos, SceneNode* node, SceneManager* mSM, int id ,std::string bMat1, std::string bMat2, std::string hMat, Labyrinth* Lab = nullptr, int TileWidth = 1) : Character(initPos, node, mSM, Lab, TileWidth), id(id) {
		buildVillano(bMat1, bMat2, hMat);
	}

	void buildVillano(std::string bodyMat1, std::string bodyMat2, std::string hMat);

	void startEnemie();

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

	virtual void restart();
};

