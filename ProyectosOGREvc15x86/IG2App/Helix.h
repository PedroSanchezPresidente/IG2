#pragma once
#include "IG2Object.h"
#include "Pale.h"
#include "OgreMath.h"
#include <vector>
class Helix : public IG2Object {
private:
	// Numero de palas
	int num;
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

			// Crear la pala y ajustarla
			Pale* pale = new Pale(palePos, sm, mNode, i);
			Quaternion rotation;
			rotation.FromAngleAxis(Radian(angle), Vector3::UNIT_Y); // Rotar alrededor del eje Y
			// Si se les quiere dar una rotacion especial tipo shuriken
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
	Helix(Vector3 initPos, SceneManager* sM, SceneNode* parentNode, int numPales, string nodeName)
		: IG2Object(initPos, parentNode->createChildSceneNode(nodeName), sM), 
		num(numPales), pList(numPales, nullptr) {

		if (numPales <= 0) {
			throw std::invalid_argument("El número de palas debe ser mayor que cero.");
		}
		createPales(sM);
	}
};
