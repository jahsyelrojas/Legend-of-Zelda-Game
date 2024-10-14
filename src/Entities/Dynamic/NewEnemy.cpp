#include "NewEnemy.h"
#include "Link.h"
#include "Map.h"
#include "GameState.h"
#include "ImageManager.h"
#include <memory>

void NewEnemy::update(){
    
    counter++;

    // It is time to stop moving
    if (movingDir[UP] || movingDir[DOWN] || movingDir[LEFT] || movingDir[RIGHT]){
        if (counter == MOVEMENT_TIME){
            movingDir[UP] = false;
            movingDir[DOWN] = false;
            movingDir[LEFT] = false;
            movingDir[RIGHT] = false;
            counter = 0;
        }
    }

    else{
        // Time to move in a random direction
        if (counter == WAITING_TIME){
            movingDir[UP] = false;
            movingDir[DOWN] = false;
            movingDir[LEFT] = false;
            movingDir[RIGHT] = false;
            Direction direction = static_cast<Direction>(directionToLink);
            movingDir[direction] = true;
            counter = 0;
        }
    }

    DynamicEntity::update();
}

void NewEnemy::damage(int damage){
    if (dead) return;
    // Play the damage sound if we're about to take damage
    if (invincibilityFrames == 0)
        handler->getSoundEffectManager()->playSoundEffect("enemy_hurt");
        
    DynamicEntity::damage(damage);
}

void NewEnemy::onDeath(){
    handler->getSoundEffectManager()->playSoundEffect("enemy_death");
}

void NewEnemy::onCollision(shared_ptr<DynamicEntity> entity) {
    shared_ptr<Link> link = dynamic_pointer_cast<Link>(entity);
    if(link){
        entity->damage(20);
    }
}