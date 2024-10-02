#pragma once
#include "IG2Object.h"
#include "IG2ApplicationContext.h"
class Heroe : public IG2Object, public OgreBites::InputListener
{
public:
	Heroe(Vector3 initPos, SceneNode* node, SceneManager* mSM, String mesh) : IG2Object(initPos, node, mSM, mesh){
		// Set scale of Sinbad
		setScale(Vector3(10, 10, 10));
	}
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	
};

