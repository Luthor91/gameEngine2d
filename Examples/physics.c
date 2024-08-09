#include "../Core/Utilities/include/core.h"

void Event_Space_Pressed(void* object, SDL_Event* event, void* entry, void* returned) {
    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_SPACE) {
        ImpulseManager* manager = (ImpulseManager*)object;
        ImpulseManager_Add(manager, Impulse_Init(10.0f, DIRECTION_SOUTH, 1.0f));
    }
}

int main(int argc, char* argv[]) {
    // Initialisation des composants du programme.
    if (Init_All() == 0) return 1;

    Sprite* sprite_1 = DEFAULT_SPRITE;
    Sprite* sprite_2 = DEFAULT_SPRITE;
    Sprite* sprite_3 = DEFAULT_SPRITE;
    Sprite* ground = DEFAULT_SPRITE;

    RigidBody* r_body1 = RigidBody_Init(sprite_1->transform, NULL, NULL);
    RigidBody* r_body2 = RigidBody_Init(sprite_2->transform, NULL, NULL);
    RigidBody* r_body3 = RigidBody_Init(sprite_3->transform, NULL, NULL);
    StaticBody* s_body = StaticBody_Init(ground->transform, NULL, NULL);

    r_body1->physics->material = MATERIAL_WOOD;
    r_body2->physics->material = MATERIAL_STEEL;
    r_body3->physics->material = MATERIAL_RUBBER;

    Sprite_Set(sprite_1, "position:20%,5%;");
    Sprite_Set(sprite_2, "position:50%,5%;");
    Sprite_Set(sprite_3, "position:80%,5%;");
    Sprite_Set(ground, "size:w100%,w10%;position:left,bottom;");

    // Création et initialisation des renderers pour chaque composant.
    Renderer* r_window = Renderer_Init(Renderer_Window, CURRENT_WINDOW, 0);
    Renderer* r_sprite_1 = Renderer_Init(Renderer_Sprite, sprite_1, 2);
    Renderer* r_sprite_2 = Renderer_Init(Renderer_Sprite, sprite_2, 2);
    Renderer* r_sprite_3 = Renderer_Init(Renderer_Sprite, sprite_3, 2);
    Renderer* r_ground = Renderer_Init(Renderer_Sprite, ground, 1);

    Event* evt_space1 = Event_Init(r_body1->physics->impulses, Event_Space_Pressed, NULL, NULL);
    Event* evt_space2 = Event_Init(r_body2->physics->impulses, Event_Space_Pressed, NULL, NULL);
    Event* evt_space3 = Event_Init(r_body3->physics->impulses, Event_Space_Pressed, NULL, NULL);
    
    // Ajout des renderers et des événements aux gestionnaires respectifs.
    RendererManager_Add(RENDERER_MANAGER, r_window, r_sprite_1, r_sprite_2, r_sprite_3, r_ground, NULL);
    RigidBodyManager_Add(RIGIDBODY_MANAGER, r_body1, r_body2, r_body3, NULL);
    CharacterBodyManager_Add(CHARACTERBODY_MANAGER, NULL);
    StaticBodyManager_Add(STATICBODY_MANAGER, s_body, NULL);
    EventManager_Add(EVENT_MANAGER, evt_space1, evt_space2, evt_space3, NULL);

    // Tri des renderers dans le gestionnaire de rendu.
    RendererManager_Sort(RENDERER_MANAGER);

    // Boucle principale du programme.
    while (!sdl_quit_flag) {
        // Gestion des événements.
        EventManager_HandleEvents(EVENT_MANAGER);
        Collision_HandleAll(PHYSICSBODIES_MANAGER);
        PhysicBodies_Update(PHYSICSBODIES_MANAGER, TIME_DELTA);
        TimerManager_Update(TIMER_MANAGER);

        // Ici, vous pouvez ajouter des fonctionnalités supplémentaires si nécessaire.

        RendererManager_Render(RENDERER_MANAGER);
        Time_SetFPSLimit(DEFAULT_FPS_AVERAGE);
    }

    // Nettoyage et fermeture de tous les composants.
    Exit_All(CURRENT_WINDOW);

    return 0;
}
