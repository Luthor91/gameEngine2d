#include "../Core/Utilities/include/core.h"

void Event_Space_Pressed(void* object, SDL_Event* event, void* entry, void* returned) {
    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_SPACE) {
        printf("Pressed\n");
        ImpulseManager* manager = (ImpulseManager*)object;
        ImpulseManager_Add(manager, Impulse_Init(10.0f, DIRECTION_SOUTH, 1.0f));
    }
}

int main(int argc, char* argv[]) {
    // Initialisation des composants du programme.
    if (Init_All() != 0) return 1;

    // Création et initialisation des composants graphiques.
    Window* window = DEFAULT_WINDOW;
    Sprite* sprite_1 = DEFAULT_SPRITE;
    Sprite* sprite_2 = DEFAULT_SPRITE;
    Sprite* sprite_3 = DEFAULT_SPRITE;
    Sprite* ground = DEFAULT_SPRITE;
    Sprite_Set(sprite_1, "position:20%,5%;");
    Sprite_Set(sprite_2, "position:50%,5%;");
    Sprite_Set(sprite_3, "position:80%,5%;");
    Sprite_Set(ground, "size:w100%,w10%;position:left,bottom;");
    //ground->transform->position = Point2D_Init(0, DEFAULT_WINDOW_HEIGHT - (DEFAULT_WINDOW_HEIGHT*0.1));
    //ground->transform->size = Size2D_Init(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT*0.1);

    RigidBody* r_body1 = RigidBody_Init(sprite_1->transform, NULL);
    r_body1->physics->material = MATERIAL_WOOD;
    RigidBody* r_body2 = RigidBody_Init(sprite_2->transform, NULL);
    r_body2->physics->material = MATERIAL_STEEL;
    RigidBody* r_body3 = RigidBody_Init(sprite_3->transform, NULL);
    r_body3->physics->material = MATERIAL_RUBBER;
    StaticBody* s_body = StaticBody_Init(ground->transform, NULL);

    // Initialisation des gestionnaires de rendu et d'événements.
    RendererManager* r_manager = DEFAULT_RENDERER;
    CharacterBodyManager* cb_manager = DEFAULT_CHARACTERBODY;
    StaticBodyManager* sb_manager = DEFAULT_STATICBODY;
    RigidBodyManager* rb_manager = DEFAULT_RIGIDBODY;
    PhysicsBodies* p_bodies = PhysicBodies_Init(cb_manager, rb_manager, sb_manager);
    EventManager* evt_manager = DEFAULT_EVENT;

    // Création et initialisation des renderers pour chaque composant.
    Renderer* r_window = Renderer_Init(Renderer_Window, window, 0);
    Renderer* r_sprite_1 = Renderer_Init(Renderer_Sprite, sprite_1, 2);
    Renderer* r_sprite_2 = Renderer_Init(Renderer_Sprite, sprite_2, 2);
    Renderer* r_sprite_3 = Renderer_Init(Renderer_Sprite, sprite_3, 2);
    Renderer* r_ground = Renderer_Init(Renderer_Sprite, ground, 1);

    Event* evt_space1 = Event_Init(r_body1->physics->impulses, Event_Space_Pressed, NULL, NULL);
    Event* evt_space2 = Event_Init(r_body2->physics->impulses, Event_Space_Pressed, NULL, NULL);
    Event* evt_space3 = Event_Init(r_body3->physics->impulses, Event_Space_Pressed, NULL, NULL);
    
    // Ajout des renderers et des événements aux gestionnaires respectifs.
    RendererManager_Add(r_manager, r_window, r_sprite_1, r_sprite_2, r_sprite_3, r_ground, NULL);
    RigidBodyManager_Add(rb_manager, r_body1, r_body2, r_body3, NULL);
    CharacterBodyManager_Add(cb_manager, NULL);
    StaticBodyManager_Add(sb_manager, s_body, NULL);
    EventManager_Add(evt_manager, evt_space1, evt_space2, evt_space3, NULL);

    ForceManager_Add(r_body1->physics->forces, FORCE_GRAVITY);
    ForceManager_Add(r_body2->physics->forces, FORCE_GRAVITY);
    ForceManager_Add(r_body3->physics->forces, FORCE_GRAVITY);

    // Tri des renderers dans le gestionnaire de rendu.
    RendererManager_Sort(r_manager);

    // Boucle principale du programme.
    while (!sdl_quit_flag) {
        // Gestion des événements.
        EventManager_HandleEvents(evt_manager, &sdl_quit_flag);
        Collision_HandleAll(p_bodies);
        PhysicBodies_Update(p_bodies, Time_GetDelta());

        // Ici, vous pouvez ajouter des fonctionnalités supplémentaires si nécessaire.

        RendererManager_Render(r_manager);
        Time_SetFPSLimit(DEFAULT_FPS_AVERAGE);
    }

    // Nettoyage et fermeture de tous les composants.
    Exit_All(window);

    return 0;
}
