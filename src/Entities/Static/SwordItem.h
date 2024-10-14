#pragma once

#include "Item.h"
#include "Link.h"
#include <memory>

class SwordItem : public Item {

    protected:
        bool isCollected = false;


    public:
        SwordItem(int x, int y, shared_ptr<Handler> handler, ofImage sprite) : Item(x, y, handler,sprite) {
            this->currentSprite = sprite;
            isCollected = false;
        }
        ~SwordItem(){};
        void onCollision(shared_ptr<DynamicEntity> e) override {};
        virtual void applyEffect(shared_ptr<Link> link) override { isCollected =true;};
        bool getIsCollected(){return isCollected;}
        void setIsCollected(bool bValue){isCollected = bValue; }

};
