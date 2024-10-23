#include "Enemigo.h"
#include "Labyrinth.h"

void Enemigo::buildVillano(std::string bodyMat1, std::string bodyMat2, std::string hMat) {
	Vector3 pos = getPosition();
	Vector3 bodyMid(0, (CUBE_SIZE * MID_SCALE.y) / 2 + CUBE_SIZE * TOP_SCALE.y / 2, 0);
	Vector3 bP = pos + bodyMid;
	Vector3 hP = bP + bodyMid + Vector3(0, CUBE_SIZE * MID_SCALE.y + CUBE_SIZE * PALE_SCALE.y * HELIX_SCALE.y, 0);

	helix = new Helix(hP, mSM, mNode, 5, "helice1", HELIX_ROT, hMat);
	body = new Body(bP, mSM, mNode, "body", BODY_ROT, bodyMat1, bodyMat2);
	wheels = new Wheels(pos, mSM, mNode, 4, "wheels", WHEELS_ROT);
}

void Enemigo::startEnemie(){
	dir = lab->getDistance(getPosition());
}

void Enemigo::frameRendered(const Ogre::FrameEvent& evt)
{
	Vector3 posLat = { dir.z, 0 ,dir.x };
	posLat *= tileWidth;
	if (lab->getTile(getPosition() + posLat)->isTraspasable() || lab->getTile(getPosition() - posLat)->isTraspasable()) {
		lab->getDistance(getPosition());
	}
	if (dir == Vector3::ZERO)
		newDir = -dir;
	helix->update();
	body->update();
	wheels->update();
}
