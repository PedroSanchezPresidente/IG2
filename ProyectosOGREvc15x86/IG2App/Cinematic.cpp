#include "Cinematic.h"
#include "OgreAnimation.h"
#include "OgreAnimationTrack.h"
#include "OgreKeyFrame.h"

Cinematic::Cinematic(SceneManager* mSM) {
	node = mSM->getRootSceneNode()->createChildSceneNode("cinematic");

	// Creamos luz
	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.75, 0.75, 0.75);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);
	mLightNode->setDirection(Ogre::Vector3(0, -1, 0));

	// Creamos al heroe
	SceneNode* n = node->createChildSceneNode();
	heroe = new IG2Object(Vector3(0, 0, 0), n, mSM, "Sinbad.mesh");

	// Creamos cabeza
	n = node->createChildSceneNode();
	enemigo = new IG2Object(Vector3(10, 0, 0), n, mSM, "ogrehead.mesh");
	enemigo->setScale(enemigoScale);

	// Creamos suelo
	floorNode = mSM->getRootSceneNode()->createChildSceneNode("floorC");
	Ogre::MeshManager::getSingleton().createPlane("FloorC", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Vector3::UNIT_Y, -5), 100, 40, 100, 80, true, 1, 20, 8, Vector3::UNIT_Z);
	Ogre::Entity* plane = mSM->createEntity("FloorC");
	plane->setMaterialName("FloorMaterial");
	floorNode->attachObject(plane);

	// Creamos animaciones de heroe y cabeza
	createAnimationHeroe(mSM, "Intro_Hero", duration);
	createAnimationEnemigo(mSM, "Intro_Foe", duration);

	// Creamos los estados de animacion
	animationStateHeroe = mSM->createAnimationState("Intro_Hero");
	animationStateHeroe->setLoop(true);
	animationStateHeroe->setEnabled(true);

	animationStateEnemigo = mSM->createAnimationState("Intro_Foe");
	animationStateEnemigo->setLoop(true);
	animationStateEnemigo->setEnabled(true);

	changeAnimation(curr_anim_state);

	swordR = mSM->createEntity("Sword.mesh");
	swordL = mSM->createEntity("Sword.mesh");

	timer->reset();

	//Ponemos particulas de humo
	smokeParticles = mSM->createParticleSystem("psSmoke", "SmokeParticle");
	smokeParticles->setEmitting(true);
	enemigo->getSceneNode()->attachObject(smokeParticles);
	
	//Ponemos particulas de fuego
	for (int i = 0; i < num_fire; i++) {
		fireParticles.push_back(mSM->createParticleSystem("psFire" + to_string(i), "FireParticle"));
		fireParticles[i]->setEmitting(true);
		n = node->createChildSceneNode();
		n->setPosition({ -20.f + i * dist_fire ,0,-10 });
		n->attachObject(fireParticles[i]);
	}
}

void Cinematic::frameRendered(const Ogre::FrameEvent& evt) {
	if (_active) {
		if (nextTimer[curr_anim_state] / anim_speed <= timer->getMilliseconds()) {
			curr_anim_state++;
			changeAnimation(curr_anim_state);
			timer->reset();
			if (curr_anim_state == _END_S) {
				restartAnim();
				curr_anim_state = _DANCE_S;
				changeAnimation(curr_anim_state); 
				heroe->getAnimationState(animsName[_DANCE])->setTimePosition(0);
			}
		}

		animationStateHeroe->addTime(anim_speed * evt.timeSinceLastEvent);
		animationStateEnemigo->addTime(anim_speed * evt.timeSinceLastEvent);
		if (curr_anim_state == _DANCE_S)
			heroe->getAnimationState(animsName[_DANCE])->addTime(anim_speed * evt.timeSinceLastEvent);
		else if(curr_anim_state == _RUN_HIDE_S || curr_anim_state == _RUN_SHOW_S){
			heroe->getAnimationState(animsName[_RUN_BASE])->addTime(anim_speed * evt.timeSinceLastEvent);
			heroe->getAnimationState(animsName[_RUN_TOP])->addTime(anim_speed * evt.timeSinceLastEvent);
		}
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
	case _RUN_HIDE_S:
		heroe->getAnimationState(animsName[_RUN_TOP])->setEnabled(true);
		heroe->getAnimationState(animsName[_RUN_BASE])->setEnabled(true);
		heroe->getAnimationState(animsName[_RUN_TOP])->setLoop(true);
		heroe->getAnimationState(animsName[_RUN_BASE])->setLoop(true);
		heroe->getAnimationState(animsName[_DANCE])->setEnabled(false);
		break;
	case _RUN_SHOW_S:
		heroe->attachObjectToBone("Handle.R", swordR);
		heroe->attachObjectToBone("Handle.L", swordL);
		break;
	case _END_S:
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

	// KF 1 - giro
	addKeyframe(track, durStep * 1 + turn_vel, heroe->getOrientation().getRotationTo({1,0,0}), keyframePos, heroeScale);

	keyframePos.x += moveLength;

	// KF 2 - derecha
	addKeyframe(track, durStep * 2, heroe->getOrientation().getRotationTo({ 1,0,0 }), keyframePos, heroeScale);

	// KF 3 - giro 
	addKeyframe(track, durStep * 2 + turn_vel , heroe->getOrientation().getRotationTo({ -1,0,0 }), keyframePos, heroeScale);

	keyframePos.x += -moveLength;
	// KF 4 - centro
	addKeyframe(track, durStep * 3, heroe->getOrientation().getRotationTo({ -1,0,0 }), keyframePos, heroeScale);

	keyframePos.x += -moveLength;
	// KF 5 - izquierda
	addKeyframe(track, durStep * 4, heroe->getOrientation().getRotationTo({ -1,0,0 }), keyframePos, heroeScale);

	// KF 6 - giro
	addKeyframe(track, durStep * 4 + turn_vel , heroe->getOrientation().getRotationTo({ 1,0,0 }), keyframePos, heroeScale);

	keyframePos.x += moveLength;
	// KF 7 - centro
	addKeyframe(track, durStep * 5 , heroe->getOrientation().getRotationTo({ 1,0,0 }), keyframePos, heroeScale);

	// KF 8 - giro
	addKeyframe(track, durStep * 5,  heroe->getOrientation().getRotationTo({ 0,0,1 }), keyframePos, heroeScale);

	return animation;
}

Animation* Cinematic::createAnimationEnemigo(SceneManager* mSM, string name, Real duration) {
	Animation* animation = mSM->createAnimation(name, duration);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(enemigo->getSceneNode());
	Vector3 headPos = { -20, 0, 0 };

	// KF 0 - derecha
	addKeyframe(track, durStep * 0, enemigo->getOrientation().getRotationTo({ 1,0,0 }), headPos, enemigoScale);

	headPos.x += 20;
	// KF 1 - centro
	addKeyframe(track, durStep * 2, enemigo->getOrientation().getRotationTo({ 1,0,0 }), headPos, enemigoScale);

	// KF 2 - giro
	addKeyframe(track, durStep * 2 + 0.01, enemigo->getOrientation().getRotationTo({ -1,0,0 }), headPos, enemigoScale);

	headPos.x += -20;
	// KF 3 - izquierda
	addKeyframe(track, durStep * 4, enemigo->getOrientation().getRotationTo({ -1,0,0 }), headPos, enemigoScale);

	// KF 4	- giro
	addKeyframe(track, durStep * 4 , enemigo->getOrientation().getRotationTo({ 1,0,0 }), headPos, enemigoScale);

	headPos.x += 20;
	// KF 5 - centro y se hace pequeño
	addKeyframe(track, durStep * 5, enemigo->getOrientation().getRotationTo({ 1,0,0 }), headPos, {0,0,0});

	return animation;
}
