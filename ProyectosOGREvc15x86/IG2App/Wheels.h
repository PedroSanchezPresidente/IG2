#pragma once
#include "IG2Object.h"

const float WHEEL_SIZE = 20;
const Vector3 WHEEL_SCALE = { 0.2, 0.2, 0.2 };
class Wheels : public IG2Object {
private:
	int num; 
	std::vector<IG2Object* > wList;
	Ogre::Degree rotation_fact;

	void createWheels(SceneManager* sm) {
		auto angle_offset = Math::TWO_PI / static_cast<Ogre::Real>(num);
		Vector3 center = getPosition(); // Obtener la posición inicial
		float offset = 50.0f; // Distancia desde el centro a cada pala

		for (int i = 0; i < num; ++i) {
			auto angle = angle_offset * i; // Calcular el ángulo para la pala
			Vector3 wPos = {
				center.x + offset * Math::Sin(angle) ,
				center.y,
				center.z + offset * Math::Cos(angle)
			};

			IG2Object* wheel = new IG2Object(wPos, mNode->createChildSceneNode("wheel_" + to_string(i) + "_" + mNode->getName()), sm, "sphere.mesh");
			wheel->setScale(WHEEL_SCALE);
			wList.push_back(wheel);
		}
	}
public: 
	Wheels(Vector3 initPos, SceneManager* sM, SceneNode* parentNode, int numWheels, string nodeName, float rot)
		: IG2Object(initPos, parentNode->createChildSceneNode(nodeName), sM),
		num(numWheels), wList(numWheels, nullptr), rotation_fact(Ogre::Degree(rot)) {

		if (numWheels <= 0) {
			throw std::invalid_argument("El numero de ruedas debe ser mayor que cero.");
		}
		createWheels(sM);
	}
	~Wheels() {
		for (auto w : wList) {
			delete w;
			w = nullptr;
		}
	}

	void update() {
		mNode->yaw(rotation_fact);
	}
};