#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>

using namespace Ogre;

class FollowingLight
{
private:
	Light* mLight;
	SceneNode* mNode;

public:
	FollowingLight(SceneNode* parentNode, SceneManager* sm, int type, std::string name , Ogre::ColourValue color = Ogre::ColourValue::White, Vector3 offset = Vector3::ZERO);
	~FollowingLight() {
		delete mLight;
		delete mNode;
		mLight = nullptr;
		mNode = nullptr;
	}

};

