#pragma once
#include <vector>
#include "Heroe.h"
#include "Tile.h"

using namespace std;

class Labyrinth {
private:
	std::vector<std::vector<Tile*>> map;
    SceneNode* node = nullptr;
    SceneNode* floorNode = nullptr;
    Vector3 center;
    int tileHeight = 100, tileWidth = 100;
    int r, c;
    Heroe* heroe;

    void createFloor(SceneManager* mSM) {
       floorNode = mSM->getRootSceneNode()->createChildSceneNode("floor");
       Ogre::MeshManager::getSingleton().createPlane("Floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Vector3::UNIT_Y, -50), r * tileWidth, c * tileHeight, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
       Ogre::Entity* plane = mSM->createEntity("Floor");
       floorNode->attachObject(plane);
       floorNode->setPosition(center);
    }

    void setCameraPosition(SceneNode* camNode) {
        camNode->setPosition(center.x, 2300, center.z + 1000);
        camNode->lookAt(center, Ogre::Node::TS_WORLD);
    }
public:
    Labyrinth() {};

    Labyrinth(string routeName, SceneManager* mSM, SceneNode* camNode) {
        ifstream file(routeName);
        if (!file)
            cout << "no se pudo abrir el archivo\n";

        node = mSM->getRootSceneNode()->createChildSceneNode("map");
        file >> r >> c;
        map.resize(r);

        for (int i = 0; i < r; i++) {
            map[i].resize(c);
            for (int j = 0; j < c; j++) {
                char c;
                file >> c;

                SceneNode* n = node->createChildSceneNode();

                if (c == 'x') {
                    map[i][j] = new Tile(Vector3(j * tileWidth, 0, i * tileHeight), n, mSM, "cube.mesh", false);
                    //map[i][j]->setMaterialName("egyptrockyfull");  ------ NO SE PUEDE SIN PONER EL .material y no est� creado
                }
                else if (c == 'o') {
                    map[i][j] = new Tile(Vector3(j* tileWidth, 0, i* tileHeight), n, mSM, "sphere.mesh", true, Vector3(0.1, 0.1, 0.1));
                }
                else if (c == 'h') {
                   map[i][j] = new Tile(Vector3(j * tileWidth, 0, i * tileHeight), n, mSM, true);
                    heroe = new Heroe(Vector2(i, j), n, mSM, "Sinbad.mesh", this, tileWidth);
                }
            }
        }

        center = Vector3((map.size() * tileHeight) / 2 - tileHeight / 2, 0 , (map[0].size() * tileWidth) / 2 - tileWidth / 2);

        createFloor(mSM);

        floorNode->setVisible(false);
        
        setCameraPosition(camNode);

        heroe->showBoundingBox(true);
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

    Tile* getTile(int i, int j) {
        return map[i][j];
    }

    Heroe* getHeroe() {
        return heroe;
    }
};