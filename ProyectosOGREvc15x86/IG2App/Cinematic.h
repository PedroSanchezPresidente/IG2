#pragma once
#include <OgreTimer.h>
#include "IG2Object.h"
#include "OgreParticleSystem.h"
#include <list>

class Cinematic : public OgreBites::InputListener {
private:
	bool _active = true;

	IG2Object* heroe;
	IG2Object* enemigo;
	SceneNode* node = nullptr;
	Light* light;
	SceneNode* mLightNode;
	SceneNode* floorNode;
	std::vector<string> animsName = {"Dance", "RunBase", "RunTop"};
	AnimationState* animationStateHeroe;
	AnimationState* animationStateEnemigo;
	Entity* swordR;
	Entity* swordL;
	ParticleSystem* smokeParticles;
	std::vector<ParticleSystem*> fireParticles;

	enum animation_id {
		_DANCE = 0, 
		_RUN_BASE,
		_RUN_TOP,
		_NONE
	};

	enum animation_state {
		_DANCE_S = 0,
		_RUN_S,
		_SHOW_SWORDS_S,
		_HIDE_SWORDS_S,
		_NONE_S
	};

#pragma region Walking Parameters

	int moveLength = 10;
	Real duration = 5.0;
	Vector3 keyframePos = { 0, 0, 0 };
	Real durStep = duration / 5;
	float anim_speed = 2.5;
	Vector3 heroeScale = {1,1,1};
	Vector3 enemigoScale = { 0.15, 0.15, 0.15 };
	Ogre::Timer* timer = new Ogre::Timer();
	std::vector<int> nextTimer = { 2500, 2000, 3900};
	int curr_anim_state = _DANCE_S;

#pragma endregion


	virtual void frameRendered(const Ogre::FrameEvent& evt);

	void addKeyframe(NodeAnimationTrack* nodeAnimationTrack, Real time, Quaternion giro, Vector3 posicion, Vector3 scale);

	Animation* createAnimationHeroe(SceneManager* mSM, string name, Real duration);

	Animation* createAnimationEnemigo(SceneManager* mSM, string name, Real duration);

	void changeAnimation(int state);

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

		smokeParticles->setEmitting(b);
		smokeParticles->clear();

		for (ParticleSystem* p : fireParticles) {
			p->setEmitting(b);
			p->clear();
		}
		_active = b;
	}

	void resetCamera(SceneNode* camNode) {
		camNode->setPosition(0, 10, 30);
		camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	}

	void restartAnim() {
		animationStateHeroe->setTimePosition(0);
		animationStateEnemigo->setTimePosition(0);
		timer->reset();
		curr_anim_state = _DANCE_S;
		changeAnimation(_HIDE_SWORDS_S);
		changeAnimation(curr_anim_state);

		for(string s : animsName)
			heroe->getAnimationState(s)->setTimePosition(0);
	}
};