#pragma once

#include "DynamicEntity.h"

class NewEnemy : public DynamicEntity
{
    private:
        int counter;
        const int WAITING_TIME = 1;
        const int MOVEMENT_TIME = 1;

    public: 
        NewEnemy(int x, int y, shared_ptr<Handler> handler, shared_ptr<DynamicEntityAnimations> animations) : DynamicEntity(x, y, handler, animations) 
        {
            this->x=x;
            this->y=y;
            this->MAX_HEALTH = 1;
            this->health = MAX_HEALTH;
            this->counter = 0;
        };

        Direction directionToLink = UP;
        int getOrangeX(){return x;}
        int getOrangeY(){return y;}
        void update();
        void damage(int damage);
        void onDeath();
        void onCollision(shared_ptr<DynamicEntity> entity);

};
