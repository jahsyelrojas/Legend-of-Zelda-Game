#pragma once

#include "BoundBlock.h"
#include "DoorBlock.h"
#include "Item.h"
#include "Handler.h"
#include "Link.h"
#include "ImageManager.h"
#include "NewEnemy.h"
#include "ofMain.h"

class Section {
private:
    // Grids of blocks/items per section
    // Max # of elements per grid: 176 tiles
    vector<shared_ptr<DynamicEntity>> enemies;
    vector<vector<shared_ptr<StaticEntity>>> blocks;
    vector<vector<shared_ptr<Item>>> items;
    shared_ptr<NewEnemy> newenemy;
    bool transtioning = false;

public:
    Section();

    void addEnemy(shared_ptr<DynamicEntity> e) { enemies.push_back(e); };
    void addEnemyToTile(int x, int y, shared_ptr<DynamicEntity> e){
        e->setX(x * Handler::TILE_WIDTH);
        e->setY(y * Handler::TILE_HEIGHT + Handler::GAME_SCREEN.y);
        enemies.push_back(e);
    };
    void addBlockToPosition(int x, int y, shared_ptr<StaticEntity> entity) { blocks[y][x] = entity; }
    void addItemToPosition(int x, int y, shared_ptr<Item> item) { items[y][x] = item; }
    void addItemToTile(int x, int y, shared_ptr<Item> item){
            item->setX(x * Handler::TILE_WIDTH);
            item->setY(y * Handler::TILE_HEIGHT + Handler::GAME_SCREEN.y);
            addItemToPosition(x, y, item);
        };
    void removeItemFromTile(int x, int y, shared_ptr<Item> item) {items[y][x] = nullptr;}
   

    vector<shared_ptr<DynamicEntity>> getEnemies() { return enemies; }
    vector<vector<shared_ptr<StaticEntity>>> getBlocks() { return blocks; }
    vector<vector<shared_ptr<Item>>> getItems() { return items; }

    void setTranstioning(bool b){this->transtioning = b;}
    void update();
    void draw();
    void respawnEnemies();

    // To store the position of the door in said section, if it exists
    int doorXPos = 0;
    int doorYPos = 0;
};