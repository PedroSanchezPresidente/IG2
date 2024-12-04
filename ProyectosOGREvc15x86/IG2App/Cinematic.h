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
	IG2Object* moon;
	SceneNode* node = nullptr;

	Light* light;
	SceneNode* mLightNode;

	SceneNode* floorNode;

	AnimationState* animationStateHeroe;
	AnimationState* animationStateEnemigo;

	Entity* swordR;
	Entity* swordL;

	ParticleSystem* smokeParticles;
	std::vector<ParticleSystem*> fireParticles;
	const int dist_fire = 3;
	const int num_fire = 15;

	std::vector<string> animsName = {
		"Dance",
		"RunBase",
		"RunTop"
	};

	enum animation_id {
		_DANCE = 0, 
		_RUN_BASE,
		_RUN_TOP,
		_NONE
	};

	enum animation_state {
		_DANCE_S = 0,
		_RUN_HIDE_S,
		_RUN_SHOW_S,
		_END_S,
		_NONE_S
	};


#pragma region Walking Parameters

	int moveLength = 10;
	//Duracion de la animacion
	Real duration = 21;
	Real turn_vel = 0.2;
	//Poscion del heroe
	Vector3 keyframePos = { 0, 0, 0 };
	Real durStep = duration / 5;
	Real anim_speed = 1;
	Vector3 heroeScale = {1,1,1};
	Vector3 enemigoScale = { 0.15, 0.15, 0.15 };
	Ogre::Timer* timer = new Ogre::Timer();


	// Lista de tiempos entre animaciones
	// Bailar - caminar
	// Sin espadas - con espadas
	// con espadas - fin cinematica
	std::vector<int> nextTimer = {(int)durStep * 1000, (int)durStep * 1000, (int)(duration - durStep * 2) * 1000};

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
		moon->setVisible(b);
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
		changeAnimation(curr_anim_state);

		for(string s : animsName)
			heroe->getAnimationState(s)->setTimePosition(0);
	}
};