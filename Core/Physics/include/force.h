#ifndef FORCE_H
#define FORCE_H

typedef struct Force {
    float x;
    float y;
} Force;

Force* Force_Init(float x, float y);
void Force_Destroy(Force* force);

#endif // FORCE_H
