#pragma once

#include "Animation.h"
#include "Link.h"
#include "Tektike.h"
#include "MapBuilder.h"
#include "State.h"
#include <memory>
#include "SwordItem.h"

class GameState : public State {

private:
    shared_ptr<Map> currentMap;
    shared_ptr<Map> overWorldMap;
    shared_ptr<Map> oldManCaveMap;
    shared_ptr<Map> dungeon;
    unique_ptr<MapBuilder> mapBuilder;
    shared_ptr<SwordItem> swordItem;
    shared_ptr<Link> link;
   
public:
    GameState(shared_ptr<Handler> handler) : State(handler) { this->reset(); }
    void update();
    void draw();
    void reset();
    void keyPressed(int key);
    void keyReleased(int key);
    bool swordCollected = false;
    bool swordInInvetory= false;
    ofImage menuHUD;
    bool paused;
    int hudY;
    int hudH;
    int hudHeight;
    int changeState;

    shared_ptr<Tektike> createTektike();
    shared_ptr<NewEnemy> createNewEnemy();
    shared_ptr<NewEnemy> enemy0;

};