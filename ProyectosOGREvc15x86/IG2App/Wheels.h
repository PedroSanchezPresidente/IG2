#pragma once
#include "IG2Object.h"
class Wheels : public IG2Object {
private:
	int num; 
	std::vector<IG2Object* > wList;

	void createWheels(SceneManager* sm) {
		auto angle_offset = Math::TWO_PI / static_cast<Ogre::Real>(num);
		Vector3 center = getPosition(); // Obtener la posición inicial
		float offset = 200.0f; // Distancia desde el centro a cada pala

		for (int i = 0; i < num; ++i) {
			auto angle = angle_offset * i; // Calcular el ángulo para la pala
			Vector3 wPos = {
				center.x + offset * Math::Sin(angle) ,
				center.y,
				center.z + offset * Math::Cos(angle)
			};

			IG2Object* wheel = new IG2Object(wPos, mNode->createChildSceneNode("wheel_" + to_string(num)), sm, "sphere.mesh");
			wList.push_back(wheel);
		}
	}
public: 
	Wheels(Vector3 initPos, SceneManager* sM, SceneNode* parentNode, int numWheels, string nodeName)
		: IG2Object(initPos, parentNode->createChildSceneNode(nodeName), sM),
		num(numWheels), wList(numWheels, nullptr) {

		if (numWheels <= 0) {
			throw std::invalid_argument("El numero de ruedas debe ser mayor que cero.");
		}

	}
};