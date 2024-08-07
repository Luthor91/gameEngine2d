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


void PhysicBodies_Update(PhysicsBodies* p_bodies, float deltaTime) {
    if (p_bodies->rb_manager) {
        RigidBodyManager_Update(p_bodies->rb_manager, deltaTime);
    }
    if (p_bodies->cb_manager) {
        CharacterBodyManager_Update(p_bodies->cb_manager, deltaTime);
    }  
       
}
