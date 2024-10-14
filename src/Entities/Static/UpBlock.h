#pragma once
#include "StaticEntity.h"
#include <memory>

class UpBlock : public StaticEntity {
public:
    UpBlock(int x, int y, shared_ptr<Handler> handler) : StaticEntity(x, y, handler) {}
    ~UpBlock() {}

    void onCollision(shared_ptr<DynamicEntity> e) {
        moveUp(e,5);
    }

    int moveUp(shared_ptr<DynamicEntity> e, int time) {
        if (time == 0) {
            return 0;
        } else {
            e->setY(e->getY() - 1);
            return 1 + moveUp(e, time - 1);
        }
    }
};