#pragma once
#include "StaticEntity.h"
#include <memory>

class LeftBlock : public StaticEntity{
    public:

    LeftBlock(int x, int y, shared_ptr<Handler> handler) : StaticEntity(x,y,handler){}
    ~LeftBlock(){};

    void onCollision(shared_ptr<DynamicEntity> e) {
        moveR(e,5);
    }

    int moveR(shared_ptr<DynamicEntity> e, int time){
        if(time ==0){
            return  0;
        }
        else{
            e->setX(e->getX() - 1);
            return 1+moveR(e, time-1);
        }
    }

};