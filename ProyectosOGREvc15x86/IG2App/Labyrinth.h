#pragma once
#include <vector>
#include "Heroe.h"
#include "Tile.h"
#include "Perla.h"
#include "InfoBox.h"
#include "Muro.h"
#include "Enemigo.h"
#include <cmath>

using namespace std;

class Labyrinth {
private:
	std::vector<std::vector<Tile*>> map;
    std::vector<Enemigo* > enemigos;
    SceneNode* node = nullptr;
    SceneNode* floorNode = nullptr;
    Vector3 center;
    int tileHeight = 100, tileWidth = 100; 
    int r, c;
    Heroe* heroe;
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

    void setCameraPosition(SceneNode* camNode) {
        camNode->setPosition(center.x, 2300, center.z + 1000);
        camNode->lookAt(center, Ogre::Node::TS_WORLD);
    }
public:
    Labyrinth() {};

    Labyrinth(string routeName, SceneManager* mSM, OgreBites::TrayManager* tM, SceneNode* camNode) {
        ifstream file(routeName);
        if (!file)
            cout << "no se pudo abrir el archivo\n";

        node = mSM->getRootSceneNode()->createChildSceneNode("map");
        file >> r >> c;
        file >> floorMat >> pearlMat >> wallMat >> bodyMat1 >> bodyMat2 >> helMat;
        map.resize(r);

        for (int i = 0; i < r; i++) {
            map[i].resize(c);
            for (int j = 0; j < c; j++) {
                char c;
                file >> c;

                SceneNode* n = node->createChildSceneNode();

                int x, z;
                x = j * tileWidth + tileWidth / 2;
                z = i * tileHeight + tileHeight / 2;

                if (c == 'x') {
                    map[i][j] = new Muro(Vector3(x, 0, z), n, mSM, wallMat ,false);
                }
                else if (c == 'o') {
                    map[i][j] = new Perla(Vector3(x, 0, z), n, mSM, pearlMat,10, true, true, Vector3(0.1, 0.1, 0.1));
                }
                else if (c == 'h') {
                   map[i][j] = new Perla(Vector3(x, 0, z), n, mSM, pearlMat,0,false, true);
                   n = node->createChildSceneNode();
                   heroe = new Heroe(Vector3(x, 0, z), n, mSM, "Sinbad.mesh", this, tileWidth);
                }
            }
        }

        center = Vector3((map.size() * tileHeight) / 2 - tileHeight / 2, 0 , (map[0].size() * tileWidth) / 2 - tileWidth / 2);

        createFloor(mSM);
        
        setCameraPosition(camNode);

        heroe->showBoundingBox(true);

        enemigos.push_back(new Enemigo(Vector2(0, 0), mSM->getRootSceneNode()->createChildSceneNode("enemigo1"), mSM, bodyMat1, bodyMat2, helMat));

        ib = new InfoBox(tM);
    }

    ~Labyrinth() {
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; map[i].size(); j++) {
                delete map[i][j];
            }
            map[i].clear();
        }

        map.clear();
    }

    Tile* getTile(Vector3 pos) {
        return map[pos.z / tileWidth][pos.x / tileHeight];
    }

    Heroe* getHeroe() {
        return heroe;
    }

    void addPoints(int p) {
        ib->addPoints(p);
    }

    const std::vector<Enemigo*>& getEnemyList() const {
        return enemigos;
    }
 };