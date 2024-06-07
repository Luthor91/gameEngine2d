#ifndef FORCE_H
#define FORCE_H

#include <math.h>

typedef struct Force {
    float magnitude;
    float direction;
} Force;

typedef struct ForceManager {
    Force** forces;
    int max_force;
    int index;
} ForceManager;


Force* Force_Init(float magnitude, float direction);
void Force_Destroy(Force* force);

ForceManager* ForceManager_Init(int max_force);
void ForceManager_AddForce(ForceManager* manager, Force* force);
Force* ForceManager_CalculateNetForce(ForceManager* manager);

#endif // FORCE_H
