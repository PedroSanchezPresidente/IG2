#pragma once
#include <vector>
#include "Tile.h"

using namespace std;

class Labyrinth {
private:
	std::vector<std::vector<IG2Object*>> map;
    SceneNode* node = nullptr;
    int tileHeight = 100, tileWidth = 100;

public:
    Labyrinth() {};

    Labyrinth(string routeName, SceneManager* mSM) {
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
                    //map[i][j]->setMaterialName("egyptrockyfull");  ------ NO SE PUEDE SIN PONER EL .material y no está creado
                }
                else if (c == 'o') {
                    map[i][j] = new Tile(Vector3(j* tileWidth, 0, i* tileHeight), n, mSM, "sphere.mesh", true, Vector3(0.1, 0.1, 0.1));
                }
            }
        }
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

    IG2Object* getTile(int i, int j) {
        return map[i][j];
    }
};