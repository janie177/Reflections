#include "TexturedEntity.h"

using namespace reflections;

reflections::TexturedEntity::TexturedEntity(int x, int y, World & world, EntityType type, double speed, int width, int height, int textureID) : Entity(x, y, world, type, speed, width, height), Textured(textureID) {

}