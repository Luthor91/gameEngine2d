#include "../include/physicsbodies.h"

PhysicsBodies* PhysicBodies_Init(CharacterBodyManager* cb_manager, RigidBodyManager* rb_manager, StaticBodyManager* sb_manager) {
    PhysicsBodies* physics_bodies = (PhysicsBodies*)malloc(sizeof(PhysicsBodies));
    if (physics_bodies == NULL) {
        return NULL;
    }

    physics_bodies->cb_manager = cb_manager;
    physics_bodies->rb_manager = rb_manager;
    physics_bodies->sb_manager = sb_manager; 

    return physics_bodies;
}


void PhysicBodies_Update(PhysicsBodies* physics_bodies, float deltaTime) {
    if (physics_bodies->rb_manager && physics_bodies->rb_manager->index > 0) {
        RigidBodyManager_Update(physics_bodies->rb_manager, deltaTime);
    }
    if (physics_bodies->cb_manager && physics_bodies->cb_manager->index > 0) {
        CharacterBodyManager_Update(physics_bodies->cb_manager, deltaTime);
    }      
}
