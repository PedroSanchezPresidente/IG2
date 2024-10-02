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
    IG2Object* floor = nullptr;
    Vector3 center;
    int tileHeight = 100, tileWidth = 100;
    Heroe* heroe;

    void createFloor(SceneManager* mSM) {
       floorNode = mSM->getRootSceneNode()->createChildSceneNode("floor");
       floor = new IG2Object(Vector3(center.x, -tileHeight / 2, center.z), floorNode, mSM, "cube.mesh");
       floor->setScale(Vector3(map.size(), 0.01, map[0].size()));
       
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

        int h, w;
        node = mSM->getRootSceneNode()->createChildSceneNode("map");
        file >> h >> w;
        map.resize(h);

        for (int i = 0; i < h; i++) {
            map[i].resize(w);
            for (int j = 0; j < w; j++) {
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

        floor->setVisible(false);
        
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