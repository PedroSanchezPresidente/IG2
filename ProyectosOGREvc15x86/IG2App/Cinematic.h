#pragma once
#include "IG2Object.h"
#include <list>

class Cinematic : public OgreBites::InputListener {
private:
	IG2Object* heroe;
	IG2Object* enemigo;
	SceneNode* node = nullptr;
	Light* light;
	SceneNode* mLightNode;
	SceneNode* floorNode;
	std::vector<string> animsName = {"Dance", "RunBase", "RunTop"};

	enum animation_id {
		_DANCE = 0, 
		_RUN_BASE,
		_RUN_TOP,
		_NONE
	};

#pragma region Walking Parameters

	int moveLength = 50;
	Real duration = 16.0;
	Vector3 keyframePos = { 0, 0, 0 };
	Real durStep = duration / 4.0;

#pragma endregion


	virtual void frameRendered(const Ogre::FrameEvent& evt);

	void addKeyframe(NodeAnimationTrack* nodeAnimationTrack, Real time, Quaternion* giro, Vector3 posicion, Vector3 scale);

public:
	Cinematic(SceneManager* mSM);

	~Cinematic() {
		delete heroe;
		delete enemigo;
	}

	void setVisible(bool b) {
		heroe->setVisible(b);
		enemigo->setVisible(b);
		mLightNode->setVisible(b);
		floorNode->setVisible(b);
	}

	void resetCamera(SceneNode* camNode) {
		camNode->setPosition(0, 10, 30);
		camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	}

	Animation* createAnimation(SceneManager* mSM, string name, Real duration);
};