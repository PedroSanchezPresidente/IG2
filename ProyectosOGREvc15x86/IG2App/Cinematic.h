#pragma once
#include "IG2Object.h"

class Cinematic {
private:
	IG2Object* heroe;
	IG2Object* enemigo;
	SceneNode* node = nullptr;
	Light* light;
	SceneNode* mLightNode;
public:
	Cinematic(SceneManager* mSM) {
		node = mSM->getRootSceneNode()->createChildSceneNode("cinematic");

		Light* luz = mSM->createLight("Luz");
		luz->setType(Ogre::Light::LT_DIRECTIONAL);
		luz->setDiffuseColour(0.75, 0.75, 0.75);

		mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
		//mLightNode = mCamNode->createChildSceneNode("nLuz");
		mLightNode->attachObject(luz);
		mLightNode->setDirection(Ogre::Vector3(0, -1, 0));

		SceneNode* n = node->createChildSceneNode();
		heroe = new IG2Object(Vector3(0, 0, 0), n, mSM, "Sinbad.mesh");
		n = node->createChildSceneNode();
		enemigo = new IG2Object(Vector3(10, 0, 0), n, mSM, "ogrehead.mesh");
		enemigo->setScale(Vector3(0.2,0.2,0.2));
	}

	~Cinematic() {
		delete heroe;
		delete enemigo;
	}

	void setVisible(bool b) {
		heroe->setVisible(b);
		enemigo->setVisible(b);
		mLightNode->setVisible(b);
	}

	void resetCamera(SceneNode* camNode) {
		camNode->setPosition(0, 10, 30);
		camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	}
};