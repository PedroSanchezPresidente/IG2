#pragma once
#include "IG2Object.h"
#include "Pale.h"
#include "OgreMath.h"
#include <vector>

const Vector3 HELIX_SCALE = { 0.3, 0.3, 0.3 };

class Helix : public IG2Object {
private:
	// Numero de palas
	int num;
	Ogre::Degree rotation_fact;
	// Vector que almacena las palas que se necesitan
	std::vector<Pale*> pList;
	
	void createPales(SceneManager* sm) {
		auto angle_offset = Math::TWO_PI / static_cast<Ogre::Real>(num);
		Vector3 center = getPosition(); // Obtener la posición inicial
		float offset = 200.0f; // Distancia desde el centro a cada pala

		for (int i = 0; i < num; ++i) {
			auto angle = angle_offset * i; // Calcular el ángulo para la pala
			Vector3 palePos = {
				center.x + offset * Math::Sin(angle) ,
				center.y,
				center.z + offset * Math::Cos(angle) 
			};

			
			Pale* pale = new Pale(palePos, sm, mNode, i);
			Quaternion rotation;
			rotation.FromAngleAxis(Radian(angle), Vector3::UNIT_Y);
			rotation = rotation * Quaternion(Radian(-90), Vector3::UNIT_Y);
			pale->rotate(rotation); 

			pList.push_back(pale);
		}
	}

public:
	/**
	* @param initPos
	* @param sM
	* @param parentNode
	* @param numPales
	* @param nodeName
	*/
	Helix(Vector3 initPos, SceneManager* sM, SceneNode* parentNode, int numPales, string nodeName, float rot)
		: IG2Object(initPos, parentNode->createChildSceneNode(nodeName), sM), 
		num(numPales), pList(numPales, nullptr), rotation_fact(Ogre::Degree(rot)) {

		if (numPales <= 0) {
			throw std::invalid_argument("El número de palas debe ser mayor que cero.");
		}
		createPales(sM);

		setScale(HELIX_SCALE);
	}
	~Helix() {
		for (auto p : pList) {
			delete p;
			p = nullptr;
		}
	}

	void update() {
		mNode->yaw(rotation_fact);
	}
};
