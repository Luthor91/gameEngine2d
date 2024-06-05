#include <stdio.h>
#include "../../Core/Physics/include/physics.h"

#define MAX_RIGID_BODIES 10
#define MAX_CHARACTER_BODIES 1
#define MAX_STATIC_BODIES 5

int main() {
    PhysicsManager* manager = PhysicsManager_Init(MAX_RIGID_BODIES, MAX_CHARACTER_BODIES, MAX_STATIC_BODIES);

    // Initialize your bodies here
    for (int i = 0; i < MAX_RIGID_BODIES; i++) {
        manager->rigidBodyManager->rigidBodies[i] = (RigidBody){{i * 10.0f, i * 10.0f}, {0, 0}, {0, 0}, 1.0f};
    }
    for (int i = 0; i < MAX_CHARACTER_BODIES; i++) {
        manager->characterBodyManager->characterBodies[i] = (CharacterBody){{i * 10.0f, i * 10.0f}, {0, 0}, 0, 1.0f};
    }
    for (int i = 0; i < MAX_STATIC_BODIES; i++) {
        manager->staticBodyManager->staticBodies[i] = (StaticBody){{i * 20.0f, i * 20.0f}};
    }

    float deltaTime = 0.016f; // Simulated time step (60 FPS)
    
    // Main game loop
    for (int i = 0; i < 100; i++) {
        PhysicsManager_Update(manager, deltaTime);
        
        // Print positions for debugging
        printf("RigidBody Position: (%f, %f)\n", manager->rigidBodyManager->rigidBodies[0].position.x, manager->rigidBodyManager->rigidBodies[0].position.y);
        printf("CharacterBody Position: (%f, %f)\n", manager->characterBodyManager->characterBodies[0].position.x, manager->characterBodyManager->characterBodies[0].position.y);
    }

    PhysicsManager_Destroy(manager);
    
    return 0;
}
