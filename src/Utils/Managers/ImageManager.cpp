#include "ImageManager.h"
#include <memory>

ImageManager::ImageManager() {

    ofImage entitySpriteSheet = ofImage("images/SpriteSheets/entitySprites_transparent.png");
    entitySprites = loadSpritesFromSheet(entitySpriteSheet, PIXELS_PER_TILE, PIXELS_PER_TILE, 1);

    ofImage mapSpriteSheet = ofImage("images/SpriteSheets/mapSprites.png");
    mapSprites = loadSpritesFromSheet(mapSpriteSheet, PIXELS_PER_TILE, PIXELS_PER_TILE, 1);

    // ofImage dungeonSpritesSheet = ofImage("images/SpriteSheets/mapSprites.png");
    // dungeonTiles = loadSpritesFromSheet(dungeonSpritesSheet, PIXELS_PER_TILE, PIXELS_PER_TILE,1);

    overWorldPixelMap = ofImage("images/Maps/overWorldPixelMap.png");
    oldMansCavePixelMap = ofImage("images/Maps/oldMansCavePixelMap.png");
    dungeonPixelMap = ofImage("images/Maps/dungeonpixelmap.png");
    basicSword = entitySprites[74];
    fullHeart = entitySprites[126];
    halfHeart = entitySprites[127];
    emptyHeart = entitySprites[128];

    createLinkAnimations();
    createTitleScreenAnimation();
    gameOverScreen = ofImage("images/GameOverScreen/GameOver_1.png");
    gameOverScreenWithOptions = ofImage("images/GameOverScreen/GameOver_2.png");
    heart = getSpriteFromEntitySheetAt(0, 7);
    HUD = ofImage("images//HUD/HUD.png");
}

// Returns an animation from a list of indices
template <typename... Indices>
shared_ptr<Animation> ImageManager::getAnimationFromIndices(Indices... indices) {
    vector<ofImage> frames{entitySprites[indices]...};
    return make_shared<Animation>(10, frames);
}

void ImageManager::createLinkAnimations() {
    // Movement
    DirectionalAnimations movement;
    movement.down = getAnimationFromIndices(0, 1);
    movement.right = getAnimationFromIndices(2, 3);
    movement.left = getAnimationFromIndices(4, 5);
    movement.up = getAnimationFromIndices(6, 7);

    // Attacking
    DirectionalAnimations attacking;
    attacking.down = getAnimationFromIndices(18, 19, 20, 21);
    attacking.right = getAnimationFromIndices(22, 23, 24, 25);
    attacking.left = getAnimationFromIndices(26, 27, 28, 29);
    attacking.up = getAnimationFromIndices(30, 31, 32, 33);

    linkAnimations = make_shared<LinkAnimations>();

    // Misc
    linkAnimations->damage = getAnimationFromIndices(36, 37, 38, 39, 40, 41);
    linkAnimations->death = getAnimationFromIndices(0, 2, 6, 4); // Down, Right, Up, Left
    linkAnimations->pickup = getAnimationFromIndices(9);

    // Assign to LinkAnimations
    linkAnimations->attacking = attacking;
    linkAnimations->movement = movement;

    // Remove loops from attacking animations
    linkAnimations->attacking.down->setLoop(false);
    linkAnimations->attacking.right->setLoop(false);
    linkAnimations->attacking.left->setLoop(false);
    linkAnimations->attacking.up->setLoop(false);

    // Speed up the attacking animations
    linkAnimations->attacking.down->setSpeed(5);
    linkAnimations->attacking.right->setSpeed(5);
    linkAnimations->attacking.left->setSpeed(5);
    linkAnimations->attacking.up->setSpeed(5);
    

}

shared_ptr<DynamicEntityAnimations> ImageManager::getTektikeAnimations(){
    DirectionalAnimations movement;
    
    // Tektike's movement animation is the same for all directions
    movement.down = getAnimationFromIndices(123,124);
    movement.right = movement.down;
    movement.left = movement.down;
    movement.up = movement.down;

    tektikeAnimations = make_shared<DynamicEntityAnimations>();

    tektikeAnimations->movement = movement;

    // No attacking animation for Tektike
    tektikeAnimations->attacking = movement;

    tektikeAnimations->damage = getAnimationFromIndices(87, 88);

    return tektikeAnimations;

}

shared_ptr<DynamicEntityAnimations>ImageManager::getNewEnemyAnimations(){
    DirectionalAnimations movement;

    //Enemy's movement animation 
    movement.down = getAnimationFromIndices(50,51);
    movement.right = getAnimationFromIndices(48,49);
    movement.left = getAnimationFromIndices(52,53);
    movement.up = getAnimationFromIndices(16,34);

    newenemyAnimations = make_shared<DynamicEntityAnimations>();
    newenemyAnimations->movement=movement;
    newenemyAnimations->attacking=movement;
    newenemyAnimations->damage = getAnimationFromIndices(59, 59);

    return newenemyAnimations;
}

void ImageManager::createTitleScreenAnimation() {
    // Read from data/images/TitleScreenFrames
    vector<ofImage> frames;
    for (int i = 0; i < 16; i++) {
        ofImage frame = ofImage("images/TitleScreenFrames/frame" + to_string(i) + ".png");
        frames.push_back(frame);
    }
    titleScreenAnimation = make_shared<Animation>(5, frames);
}

vector<ofImage> ImageManager::loadSpritesFromSheet(ofImage sheet, int spriteWidth, int spriteHeight, int borderSize) {
    vector<ofImage> sprites;
    for (int y = borderSize; y + spriteHeight < sheet.getHeight(); y += spriteHeight + borderSize) {
        for (int x = borderSize; x + spriteWidth < sheet.getWidth(); x += spriteWidth + borderSize) {
            ofImage sprite;
            sprite.cropFrom(sheet, x, y, spriteWidth, spriteHeight);
            sprites.push_back(sprite);
        }
    }
    return sprites;
}

ofImage ImageManager::getSpriteFromEntitySheetAt(int column, int row) {
    // 18 tiles per row (y)
    // index = 18y + x
    return entitySprites[(row * 18) + column];
}
ofImage ImageManager::getSpriteFromMapSheetAt(int column, int row) {
    // 32 tiles per row (y)
    // index = 32y + x
    return mapSprites[(row * 32) + column];
}
