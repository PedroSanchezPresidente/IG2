#include "FollowingLight.h"

FollowingLight::FollowingLight(SceneNode* parentNode, SceneManager* sm, int type, std::string name,  Ogre::ColourValue color, Vector3 offset)
{
	mLight = sm->createLight(name);
	mLight->setType((Light::LightTypes)type);
	auto lType = mLight->getType();
	mNode = parentNode->createChildSceneNode(name + "Node");
	mNode->setDirection(Vector3(0, -1, 0));
	
	switch (lType)
	{
	case Light::LightTypes::LT_POINT:
		mNode->setPosition(Vector3(0, 10, 0) + offset);
		break;
	case Light::LightTypes::LT_DIRECTIONAL:
		break;
	case Light::LightTypes::LT_SPOTLIGHT: 
		mNode->setPosition(Vector3(0, 70, 0) + offset);
		mLight->setSpotlightRange(Ogre::Degree(5.0f), Ogre::Degree(45.0f));
		break;
	default:
		break;
	}
	mLight->setDiffuseColour(color);
	sm->setShadowTechnique(Ogre::SHADOWDETAILTYPE_TEXTURE);
	mLight->setCastShadows(true);
	mNode->attachObject(mLight);
}
