#pragma once
#include "StaticEntity.h"
#include <memory>

class DownBlock : public StaticEntity {
public:
    DownBlock(int x, int y, shared_ptr<Handler> handler) : StaticEntity(x, y, handler) {}
    ~DownBlock() {}

    void onCollision(shared_ptr<DynamicEntity> e) {
        moveDown(e,5);
    }

    int moveDown(shared_ptr<DynamicEntity> e, int time) {
        if (time == 0) {
            return 0;
        } else {
            e->setY(e->getY() + 1);
            return 1 + moveDown(e, time - 1);
        }
    }
};