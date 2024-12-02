#include "Cinematic.h"
#include "OgreAnimation.h"
#include "OgreAnimationTrack.h"
#include "OgreKeyFrame.h"

Cinematic::Cinematic(SceneManager* mSM) {
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

	AnimationState* animationState = heroe->getAnimationState(animsName[_DANCE]); //entity se construye sobre una malla
	animationState->setEnabled(true);
	animationState->setLoop(true);

	n = node->createChildSceneNode();
	enemigo = new IG2Object(Vector3(10, 0, 0), n, mSM, "ogrehead.mesh");
	enemigo->setScale(Vector3(0.2, 0.2, 0.2));


	floorNode = mSM->getRootSceneNode()->createChildSceneNode("floorC");
	Ogre::MeshManager::getSingleton().createPlane("FloorC", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Vector3::UNIT_Y, -5), 100, 40, 100, 80, true, 1, 20, 8, Vector3::UNIT_Z);
	Ogre::Entity* plane = mSM->createEntity("FloorC");
	plane->setMaterialName("FloorMaterial");
	floorNode->attachObject(plane);

	createAnimation(mSM, "Intro", duration);

	animationState2 = mSM->createAnimationState("Intro");
	animationState2->setLoop(true);
	animationState2->setEnabled(true);
}

void Cinematic::frameRendered(const Ogre::FrameEvent& evt) {
	//heroe->getAnimationState(animsName[_DANCE])->addTime(evt.timeSinceLastEvent);
	animationState2->addTime(evt.timeSinceLastEvent);
}

void Cinematic::addKeyframe(NodeAnimationTrack* track, Real time, Quaternion giro, Vector3 posicion, Vector3 scale)
{
	TransformKeyFrame* kf = track->createNodeKeyFrame(time);
	kf->setTranslate(posicion);
	kf->setRotation(giro);
	kf->setScale(scale);
}

Animation*  Cinematic::createAnimation(SceneManager* mSM ,string name, Real duration) {
	Animation* animation = mSM->createAnimation(name, duration);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(heroe->getSceneNode());

	// KF 0
	addKeyframe(track, durStep * 0, Quaternion::IDENTITY, keyframePos, Vector3(1,1,1));

	// KF 1
	addKeyframe(track, durStep * 1, Quaternion(Ogre::Degree(90), Vector3::UNIT_Y), { keyframePos.x + moveLength, 0, 0 }, Vector3(1, 1, 1));

	return animation;
}
