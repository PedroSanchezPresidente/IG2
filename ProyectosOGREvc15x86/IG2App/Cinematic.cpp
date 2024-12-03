#include "Cinematic.h"
#include "OgreAnimation.h"
#include "OgreAnimationTrack.h"
#include "OgreKeyFrame.h"
#include "OgreParticleSystem.h"

Cinematic::Cinematic(SceneManager* mSM) {
	node = mSM->getRootSceneNode()->createChildSceneNode("cinematic");

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.75, 0.75, 0.75);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);
	mLightNode->setDirection(Ogre::Vector3(0, -1, 0));

	SceneNode* n = node->createChildSceneNode();
	heroe = new IG2Object(Vector3(0, 0, 0), n, mSM, "Sinbad.mesh");


	n = node->createChildSceneNode();
	enemigo = new IG2Object(Vector3(10, 0, 0), n, mSM, "ogrehead.mesh");
	enemigo->setScale(enemigoScale);


	floorNode = mSM->getRootSceneNode()->createChildSceneNode("floorC");
	Ogre::MeshManager::getSingleton().createPlane("FloorC", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Vector3::UNIT_Y, -5), 100, 40, 100, 80, true, 1, 20, 8, Vector3::UNIT_Z);
	Ogre::Entity* plane = mSM->createEntity("FloorC");
	plane->setMaterialName("FloorMaterial");
	floorNode->attachObject(plane);

	createAnimationHeroe(mSM, "Intro_Hero", duration);
	createAnimationEnemigo(mSM, "Intro_Foe", duration);

	animationStateHeroe = mSM->createAnimationState("Intro_Hero");
	animationStateHeroe->setLoop(true);
	animationStateHeroe->setEnabled(true);

	animationStateEnemigo = mSM->createAnimationState("Intro_Foe");
	animationStateEnemigo->setLoop(true);
	animationStateEnemigo->setEnabled(true);

	changeAnimation(curr_anim_state);

	AnimationStateSet* aux = heroe->getAllAnimationStates();
	auto it = aux->getAnimationStateIterator().begin();
	while (it != aux->getAnimationStateIterator().end()) {
		auto s = it->first;
		++it;
		cout << "Animation name: " << s << endl;
	}

	swordR = mSM->createEntity("Sword.mesh");
	swordL = mSM->createEntity("Sword.mesh");
	timer->reset();

	smokeParticles = mSM->createParticleSystem("psSmoke", "SmokeParticle");
	smokeParticles->setEmitting(true);
	enemigo->getSceneNode()->attachObject(smokeParticles);
	
	int distFirePart = 3;
	for (int i = 0; i < 15; i++) {
		fireParticles.push_back(mSM->createParticleSystem("psFire" + to_string(i), "FireParticle"));
		fireParticles[i]->setEmitting(true);
		n = node->createChildSceneNode();
		n->setPosition({ -20.f + i* distFirePart,0,-10 });
		n->attachObject(fireParticles[i]);
	}
}

void Cinematic::frameRendered(const Ogre::FrameEvent& evt) {

	if (nextTimer[curr_anim_state] <= timer->getMilliseconds()) {
		curr_anim_state++;
		changeAnimation(curr_anim_state);
		timer->reset();
		if (curr_anim_state == _HIDE_SWORDS_S) {
			curr_anim_state = _DANCE_S;
			changeAnimation(curr_anim_state);
		}
	}

	animationStateHeroe->addTime(anim_speed * evt.timeSinceLastEvent);
	animationStateEnemigo->addTime(anim_speed * evt.timeSinceLastEvent);
	if(curr_anim_state == _DANCE_S)
		heroe->getAnimationState(animsName[_DANCE])->addTime(anim_speed * evt.timeSinceLastEvent);
	else {
		heroe->getAnimationState(animsName[_RUN_BASE])->addTime(anim_speed * evt.timeSinceLastEvent);
		heroe->getAnimationState(animsName[_RUN_TOP])->addTime(anim_speed * evt.timeSinceLastEvent);
	}

}

void Cinematic::changeAnimation(int state) {
	switch (state) {
	case _DANCE_S:
		heroe->getAnimationState(animsName[_RUN_TOP])->setEnabled(false);
		heroe->getAnimationState(animsName[_RUN_BASE])->setEnabled(false);
		heroe->getAnimationState(animsName[_DANCE])->setEnabled(true);
		heroe->getAnimationState(animsName[_DANCE])->setLoop(true);
		break;
	case _RUN_S:
		heroe->getAnimationState(animsName[_RUN_TOP])->setEnabled(true);
		heroe->getAnimationState(animsName[_RUN_BASE])->setEnabled(true);
		heroe->getAnimationState(animsName[_RUN_TOP])->setLoop(true);
		heroe->getAnimationState(animsName[_RUN_BASE])->setLoop(true);
		heroe->getAnimationState(animsName[_DANCE])->setEnabled(false);
		break;
	case _SHOW_SWORDS_S:
		heroe->attachObjectToBone("Handle.R", swordR);
		heroe->attachObjectToBone("Handle.L", swordL);
		break;
	case _HIDE_SWORDS_S:
		heroe->detachObjectFromBone(swordR);
		heroe->detachObjectFromBone(swordL);
		break;
	}
}

void Cinematic::addKeyframe(NodeAnimationTrack* track, Real time, Quaternion giro, Vector3 posicion, Vector3 scale)
{
	TransformKeyFrame* kf = track->createNodeKeyFrame(time);
	kf->setTranslate(posicion);
	kf->setRotation(giro);
	kf->setScale(scale);
}

Animation*  Cinematic::createAnimationHeroe(SceneManager* mSM ,string name, Real duration) {
	Animation* animation = mSM->createAnimation(name, duration);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(heroe->getSceneNode());

	keyframePos = { 0,0,0 };
	// KF 0
	addKeyframe(track, durStep * 1, Quaternion::IDENTITY, keyframePos, heroeScale);

	// KF 1
	addKeyframe(track, durStep * 1 + durStep / 5, heroe->getOrientation().getRotationTo({1,0,0}), keyframePos, heroeScale);

	keyframePos.x += 10;
	// KF 2
	addKeyframe(track, durStep * 2, heroe->getOrientation().getRotationTo({ 1,0,0 }), keyframePos, heroeScale);

	// KF 3
	addKeyframe(track, durStep * 2 + durStep / 5, heroe->getOrientation().getRotationTo({ -1,0,0 }), keyframePos, heroeScale);

	keyframePos.x += -10;
	// KF 4
	addKeyframe(track, durStep * 3, heroe->getOrientation().getRotationTo({ -1,0,0 }), keyframePos, heroeScale);

	keyframePos.x += -10;
	// KF 5
	addKeyframe(track, durStep * 4, heroe->getOrientation().getRotationTo({ -1,0,0 }), keyframePos, heroeScale);

	// KF 6
	addKeyframe(track, durStep * 4 + durStep / 5, heroe->getOrientation().getRotationTo({ 1,0,0 }), keyframePos, heroeScale);

	keyframePos.x += 10;
	// KF 7
	addKeyframe(track, durStep * 5 - durStep / 5, heroe->getOrientation().getRotationTo({ 1,0,0 }), keyframePos, heroeScale);

	// KF 8
	addKeyframe(track, durStep * 5, heroe->getOrientation().getRotationTo({ 0,0,1 }), keyframePos, heroeScale);

	return animation;
}

Animation* Cinematic::createAnimationEnemigo(SceneManager* mSM, string name, Real duration) {
	Animation* animation = mSM->createAnimation(name, duration);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(enemigo->getSceneNode());

	keyframePos = { -20,0,0 };
	// KF 0
	addKeyframe(track, durStep * 0, enemigo->getOrientation().getRotationTo({ 1,0,0 }), keyframePos, enemigoScale);

	keyframePos.x += 10;
	// KF 1
	addKeyframe(track, durStep * 1, enemigo->getOrientation().getRotationTo({ 1,0,0 }), keyframePos, enemigoScale);

	keyframePos.x += 10;
	// KF 2
	addKeyframe(track, durStep * 2, enemigo->getOrientation().getRotationTo({ 1,0,0 }), keyframePos, enemigoScale);

	// KF 3
	addKeyframe(track, durStep * 2 + durStep / 5, enemigo->getOrientation().getRotationTo({ -1,0,0 }), keyframePos, enemigoScale);

	keyframePos.x += -10;
	// KF 4
	addKeyframe(track, durStep * 3, enemigo->getOrientation().getRotationTo({ -1,0,0 }), keyframePos, enemigoScale);

	keyframePos.x += -10;
	// KF 5
	addKeyframe(track, durStep * 4, enemigo->getOrientation().getRotationTo({ -1,0,0 }), keyframePos, enemigoScale);

	// KF 6
	addKeyframe(track, durStep * 4.0 + durStep / 5, enemigo->getOrientation().getRotationTo({ 1,0,0 }), keyframePos, enemigoScale);

	keyframePos.x += +10;
	// KF 7
	addKeyframe(track, durStep * 5, enemigo->getOrientation().getRotationTo({ 1,0,0 }), keyframePos, {0,0,0});

	return animation;
}
