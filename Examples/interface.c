#include "../Core/Utilities/include/core.h"

/**
 * @brief Programme d'exemple pour afficher une fenêtre et un panel avec les assets de base.
 * 
 * Ce programme initialise tous les composants nécessaires pour créer une fenêtre SDL,
 * configure un gestionnaire de rendu pour afficher le contenu, et entre dans une boucle
 * principale où il rend le contenu à chaque frame tout en vérifiant les événements.
 * La boucle principale continue jusqu'à ce que l'utilisateur déclenche une action de sortie.
 * 
 * Chaque ajout de composant affichable dans le code se fait de la manière suivante :
 *  - Initialisation de l'élément
 *  - Initialisation de son renderer
 *  - Ajout du renderer dans le gestionnaire de rendu
 * 
 */

void Test_Button_Clicked(void* data) {
    printf("Doing something\n");
}

int main(int argc, char* argv[]) {
    // Initialisation de tous les composants nécessaires pour le programme.
    if (Init_All() != 0) return 1;

    // Initialisation des composants graphiques
    Window* window = Window_Init(NULL, NULL, NULL);
    Panel* panel = Panel_Init(NULL, NULL);
    Sprite* sprite = Sprite_Init(NULL, NULL);
    Sprite* sprite_colored = Sprite_Init(NULL, NULL);
    Label* label = Label_Init(NULL, NULL, NULL, "Henlo Henlo Henlo");
    InputField* input_field = InputField_Init(NULL, NULL, NULL);
    Button* button = Button_Init(NULL, NULL, Test_Button_Clicked, NULL);
    Widget* widget = Widget_Init(NULL, NULL);
    Tooltip* tooltip = Tooltip_Init(NULL, NULL, NULL, NULL, NULL);

    Sprite_Set(sprite_colored, 
        "size:50%,128; \
        position:center,center;     \
        backgroundcolor:GREEN;"
    );
/*
    Widget_Set(widget,"position:212,-1;");

    Button_Set(button,"position:350,0;");
    Tooltip_Set(tooltip,"position:150,100;");

    InputField_Set(input_field, 
        "position:0,150;    \
        textcolor:BLUE;      \
        backgroundcolor:RED;\
        textsize:22;          \
        size:100,100;"
    );
    Label_Set(label, 
        "position:0,300;    \
        textcolor:255,0,0,255;       \
        backgroundcolor:BLUE;\
        textsize:22;          \
        size:100,100;"
    );
*/
    // Initialisation du gestionnaire de rendu avec la taille maximale des objets à rendre.
    RendererManager* manager = RendererManager_Init(NULL, DEFAULT_MAX_RENDERER);
    EventManager* event_manager = EventManager_Init(DEFAULT_MAX_EVENT);

    // Création et initialisation des renderers
    Renderer* renderer_window = Renderer_Init(Renderer_Window, window, 0);
    Renderer* renderer_panel = Renderer_Init(Renderer_Panel, panel, 1);
    Renderer* renderer_sprite = Renderer_Init(Renderer_Sprite, sprite, 2);
    Renderer* renderer_sprite_colored = Renderer_Init(Renderer_Sprite, sprite_colored, 3);
    Renderer* renderer_input = Renderer_Init(Renderer_InputField, input_field, 4);
    Renderer* renderer_label = Renderer_Init(Renderer_Label, label, 5);
    Renderer* renderer_button = Renderer_Init(Renderer_Button, button, 6);
    Renderer* renderer_widget = Renderer_Init(Renderer_Widget, widget, 3);
    Renderer* renderer_tooltip = Renderer_Init(Renderer_Tooltip, tooltip, 3);

    Event* event_input_field = Event_Init(input_field, Event_InputField);
    Event* event_button_clicked = Event_Init(button, Event_Button_Clicked);
    Event* event_widget_dragged = Event_Init(widget, Event_Widget_Dragged);
    Event* event_tooltip = Event_Init(tooltip, Event_Tooltip_Hovered);

    // Ajout des renderers au gestionnaire de rendu.
    RendererManager_Add(manager, renderer_window, renderer_panel, renderer_sprite, renderer_sprite_colored, renderer_input, renderer_label, renderer_button, renderer_widget, renderer_tooltip, NULL);
    EventManager_Add(event_manager, event_input_field, event_button_clicked, event_widget_dragged, event_tooltip, NULL);

    RendererManager_Sort(manager);

    // Boucle principale du programme.
    while (!sdl_quit_flag) {
        EventManager_HandleEvents(event_manager, &sdl_quit_flag);

        /**
         *  Si vous voulez ajouter des fonctionnalités
         *  Idéalement le code devrait se situer à la place de ce commentaire
         */

        RendererManager_Render(manager); // Rend le contenu à afficher en utilisant le gestionnaire de rendu.

        Time_SetFPSLimit(DEFAULT_FPS_AVERAGE); // Définit la limite de frames par seconde (FPS) pour contrôler la vitesse de rafraîchissement.
    }

    Exit_All(window); // Nettoie et ferme tous les composants

    return 0;
}
