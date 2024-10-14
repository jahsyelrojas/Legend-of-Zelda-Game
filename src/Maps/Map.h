#pragma once

#include "ofMain.h"
#include "BoundBlock.h"
#include "DoorBlock.h"
#include "Fire.h"
#include "Handler.h"
#include "Link.h"
#include "NewEnemy.h"
#include "Section.h"
#include <memory>

class Map{
private:

    int currentSectionX;
    int currentSectionY;
    int mapX;
    int mapY;

    // Grid of Sections (NxM)
    shared_ptr<Link> link;
    vector<vector<shared_ptr<Section>>> sections;
    shared_ptr<NewEnemy> newenemy;

    // Visual Map Stuffy
    ofImage background;

    //Next Map
    bool finished = false;
    MapName nextMap;
    bool transitioning = false;
    Direction move;
    int pixelsMoved = 0;
    void transition(Direction);
    void checkTransition();

    // Pickup item stuffy
    int pickupTimer = 0;
    int PICKUP_TIME = 60;

    const int TRANSITION_SPEED = Handler::PIXEL_SCALE * 2;
    void checkCollision();



public:

    Map(int x, int y, ofImage background, shared_ptr<Link> link, vector<vector<shared_ptr<Section>>> sections) {
        this->currentSectionX = x;
        this->currentSectionY = y;
        this->mapX = x * Handler::SECTION_WIDTH;
        this->mapY = y * Handler::SECTION_HEIGHT;
        this->background = background;
        this->link = link;
        this->sections = sections;
    };
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);

    void moveMap(int deltaX, int deltaY);
    void moveSection(Direction d);
    shared_ptr<Section> addSectionToPosition(int x, int y, shared_ptr<Section> s) { return sections[y][x] = s; }

    const shared_ptr<Section> getSection(int x, int y) { return sections[y][x]; }
    vector<vector<shared_ptr<Section>>> getSections() { return sections; }
    const shared_ptr<Section> getCurrentSection() { return getSection(currentSectionX,currentSectionY); }
    void setCurrentSection(int x, int y)
    {
        this->currentSectionX = x;
        this->currentSectionY = y;
        this->mapX = x * Handler::SECTION_WIDTH;
        this->mapY = y * Handler::SECTION_HEIGHT;
    }

    int getCurrentSectionX() {return currentSectionX;};
    int getCurrentSectionY() {return currentSectionY;};

    shared_ptr<Link> getPlayer() { return link; }
    void setPlayer(shared_ptr<Link> l) { this->link = l; }

    bool isFinished() {return finished;}
    void setFinished(bool finished) {this->finished = finished;}

    MapName getWhereTo() { return nextMap; }
    void setWhereTo(MapName nextMap) { this->nextMap = nextMap;}

};
