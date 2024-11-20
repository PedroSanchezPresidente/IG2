#pragma once
#include "Character.h"

class Heroe : public Character
{
protected:
	std::vector<string> anims;

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual bool keyReleased(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);

public:
	Heroe(Vector3 v, SceneNode* node, SceneManager* mSM, String mesh, Labyrinth* Lab, int TileWidth) : Character(v, node, mSM, mesh, Lab, TileWidth) {
		// Set scale of Sinbad
		setScale(Vector3(10, 10, 10));
		anims = { "Dance", "RunBase", "RunTop"};
		AnimationState* animationState = entity->getAnimationState("RunBase"); //entity se construye sobre una malla
		animationState->setEnabled(true);
		animationState->setLoop(true);
		animationState = entity->getAnimationState("RunTop"); //entity se construye sobre una malla
		animationState->setEnabled(true);
		animationState->setLoop(true);
	}

	void addPoints(int p);
	
	virtual void restart() { 
		setPosition(iniPos); 
		dir = newDir = Vector3::ZERO;
		Quaternion q = getOrientation().getRotationTo(Vector3(0, 0, 1));
		mNode->rotate(q);
		distance = 0;
	};
};

