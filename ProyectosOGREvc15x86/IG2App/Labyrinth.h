#pragma once
#include <vector>
#include "Heroe.h"
#include "Enemigo.h"
#include "Tile.h"
#include "Perla.h"
#include "InfoBox.h"
#include "Muro.h"
#include "Enemigo.h"
#include "FollowingLight.h"
#include <cmath>
#include <list>
#include "CaminoMasCorto.h"

using namespace std;

class Labyrinth {
private:
	std::vector<std::vector<Tile*>> map;
    Grafo* g; //prueba
    CaminoMasCorto* camino;
    const Vector3 ENEMY_SCALE = { 0.6, 0.6, 0.6 };
    const float ENEMY_Y_OFFSET = 10.0f;
    SceneNode* node = nullptr;
    SceneNode* floorNode = nullptr;
    Vector3 center;

    int tileHeight = 100, tileWidth = 100;
    int r, c;
    int typeLight;

    Heroe* heroe;
    FollowingLight* heroeLight;
    std::list<FollowingLight* > enemiesLights;
    std::vector<Enemigo*> enemigos;
    InfoBox* ib;

    std::string floorMat, pearlMat, wallMat, bodyMat1, bodyMat2, helMat;

    void createFloor(SceneManager* mSM) {
       floorNode = mSM->getRootSceneNode()->createChildSceneNode("floor");
       Ogre::MeshManager::getSingleton().createPlane("Floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Vector3::UNIT_Y, -50), r * tileWidth - tileWidth, c * tileHeight - tileHeight, 100, 80, true, 1, r, c, Vector3::UNIT_Z);
       Ogre::Entity* plane = mSM->createEntity("Floor");
       plane->setMaterialName(floorMat);
       floorNode->attachObject(plane); 
       floorNode->setPosition(center);
    }

public:

    Labyrinth(string routeName, SceneManager* mSM, OgreBites::TrayManager* tM);


    ~Labyrinth() {
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                delete map[i][j]; // Eliminar cada Tile
            }
            map[i].clear();
        }
        map.clear();

        for (Enemigo* e : enemigos) {
            delete e; 
        }
        enemigos.clear();

        for (FollowingLight* light : enemiesLights) {
            delete light; 
        }
        enemiesLights.clear();

        delete heroe;

        delete heroeLight;

        delete ib;

        delete g;
    }

    void setup() {
        for (Enemigo* e : enemigos)
            e->startEnemie();
    }

    Tile* getTile(Vector3 pos) {
        return map[pos.z / tileWidth][pos.x / tileHeight];
    }

    Tile* getTile(int pos) {
        return map[pos / c][pos % c];
    }

    Heroe* getHeroe() {
        return heroe;
    }

    const std::vector<Enemigo*>& getEnemigos() {
        return enemigos;
    }

    void addPoints(int p) {
        ib->addPoints(p);
    }

    void resetCamera(SceneNode* camNode) {
        camNode->setPosition(center.x, 2300, center.z + 1000);
        camNode->lookAt(center, Ogre::Node::TS_WORLD);
    }

    Vector3 getDistance(Vector3 s);

    void gameOver();

    void restart();

    void setVisible(bool b);
};
