#pragma once
#include "StaticEntity.h"
#include <memory>

class RightBlock : public StaticEntity {
public:
    RightBlock(int x, int y, shared_ptr<Handler> handler) : StaticEntity(x, y, handler) {}
    ~RightBlock() {}

    void onCollision(shared_ptr<DynamicEntity> e) {
        moveRight(e, 5);
    }

    int moveRight(shared_ptr<DynamicEntity> e, int time) {
        if (time == 0) {
            return 0;
        } else {
            e->setX(e->getX() + 1);
            return 1 + moveRight(e, time - 1);
        }
    }
};
