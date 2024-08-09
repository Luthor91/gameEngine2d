#include "../Core/Utilities/include/core.h"

/**
 * @brief Exemple de programme pour afficher une fenêtre, un panneau, et d'autres composants avec SDL.
 * 
 * Ce programme démontre comment initialiser et gérer une application SDL en configurant et rendant divers éléments graphiques. 
 * Il se compose des étapes suivantes :
 * 
 * 1. **Initialisation des composants** :
 *    - Configure les éléments de base comme la fenêtre et le panneau.
 *    - Crée et initialise divers composants graphiques comme les sprites, les labels, les champs de saisie, les boutons, etc.
 * 
 * 2. **Configuration des paramètres** :
 *    - Définie les propriétés des composants graphiques (position, taille, couleur, etc.) en utilisant des chaînes de paramètres.
 * 
 * 3. **Gestion des événements** :
 *    - Associe des actions spécifiques (comme le clic sur un bouton) à des gestionnaires d'événements.
 * 
 * 4. **Initialisation des gestionnaires de rendu et d'événements** :
 *    - Prépare les gestionnaires pour le rendu des composants et la gestion des événements.
 * 
 * 5. **Boucle principale** :
 *    - Traite les événements.
 *    - Rend les composants à l'écran à chaque frame.
 *    - Contrôle le taux de rafraîchissement de l'écran.
 * 
 * 6. **Nettoyage** :
 *    - Libère toutes les ressources avant de fermer l'application.
 * 
 * Chaque ajout ou configuration de composant suit cette méthodologie :
 *  - **Initialisation de l'élément** : Crée et configure le composant.
 *  - **Initialisation de son renderer** : Configure le renderer pour le composant.
 *  - **Ajout du renderer dans le gestionnaire de rendu** : Ajoute le renderer au gestionnaire pour le rendu à l'écran.
 */

void Test_Button_Clicked(void* data) {
    // Fonction de rappel pour le clic sur le bouton.
    // Incrémente la valeur de la ProgressBar associée et affiche la nouvelle valeur.
    ProgressBar* progress_bar = (ProgressBar*)data;
    ProgressBar_SetValue(progress_bar, progress_bar->current_value + 10);
    printf("Increment : %lf\n", progress_bar->current_value);
}

int main(int argc, char* argv[]) {
    // Initialisation des composants du programme.
    if (Init_All() != 0) return 1;

    // Création et initialisation des composants graphiques.
    Window* window = DEFAULT_WINDOW;
    Panel* panel = DEFAULT_PANEL;
    Sprite* sprite = DEFAULT_SPRITE;
    Sprite* sprite_colored = DEFAULT_SPRITE;
    Label* label = DEFAULT_LABEL;
    InputField* input_field = DEFAULT_INPUTFIELD;
    Button* button = DEFAULT_BUTTON;
    Widget* widget = DEFAULT_WIDGET;
    Tooltip* tooltip = DEFAULT_TOOLTIP;
    ProgressBar* progress_bar = DEFAULT_PROGRESSBAR;

    // Associe la ProgressBar au bouton pour que la ProgressBar soit mise à jour lorsque le bouton est cliqué.
    Button_SetOnClick(button, Test_Button_Clicked, progress_bar);

    // Configuration des propriétés des composants à l'aide de chaînes de paramètres.
    InputField_Set(input_field,         
        "position:left+10,33%;textcolor:BLUE;backgroundcolor:RED;textsize:22;size:100,100;"
    );
    Label_Set(label, 
        "position:left,60%;textcolor:255,0,0,255;backgroundcolor:BLUE;textsize:12;size:100,100;"
    );
    Sprite_Set(sprite_colored, 
        "position:center,20%-10; size:&90%+10%,&90%;backgroundcolor:GREEN;textsize:32;"
    );

    Widget_Set(widget, "position:212,;");
    Button_Set(button, "position:350,0;");
    Tooltip_Set(tooltip, "position:150,100;");
    ProgressBar_Set(progress_bar, "position:right,bottom;");

    // Initialisation des gestionnaires de rendu et d'événements.
    RendererManager* manager = DEFAULT_RENDERER;
    EventManager* event_manager = DEFAULT_EVENT;

    // Création et initialisation des renderers pour chaque composant.
    Renderer* renderer_window = Renderer_Init(Renderer_Window, window, 0);
    Renderer* renderer_panel = Renderer_Init(Renderer_Panel, panel, 1);
    Renderer* renderer_sprite = Renderer_Init(Renderer_Sprite, sprite, 2);
    Renderer* renderer_sprite_colored = Renderer_Init(Renderer_Sprite, sprite_colored, 3);
    Renderer* renderer_input = Renderer_Init(Renderer_InputField, input_field, 4);
    Renderer* renderer_label = Renderer_Init(Renderer_Label, label, 5);
    Renderer* renderer_button = Renderer_Init(Renderer_Button, button, 6);
    Renderer* renderer_widget = Renderer_Init(Renderer_Widget, widget, 3);
    Renderer* renderer_tooltip = Renderer_Init(Renderer_Tooltip, tooltip, 3);
    Renderer* renderer_progress_bar = Renderer_Init(Renderer_ProgressBar, progress_bar, 3);

    // Création et initialisation des événements pour chaque composant.
    Event* event_input_field = Event_Init(input_field, Event_InputField, NULL, NULL);
    Event* event_button_clicked = Event_Init(button, Event_Button_Clicked, NULL, NULL);
    Event* event_widget_dragged = Event_Init(widget, Event_Widget_Dragged, NULL, NULL);
    Event* event_tooltip = Event_Init(tooltip, Event_Tooltip_Hovered, NULL, NULL);

    // Ajout des renderers et des événements aux gestionnaires respectifs.
    RendererManager_Add(manager, 
        renderer_window, renderer_panel, renderer_button, renderer_sprite, renderer_sprite_colored, 
        renderer_input, renderer_panel, renderer_label, renderer_widget, renderer_tooltip,
        renderer_progress_bar, NULL
    );

    EventManager_Add(event_manager, 
        event_input_field, event_button_clicked, event_widget_dragged, event_tooltip,
        NULL
    );

    // Tri des renderers dans le gestionnaire de rendu.
    RendererManager_Sort(manager);

    // Boucle principale du programme.
    while (!sdl_quit_flag) {
        EventManager_HandleEvents(event_manager);

        // Ici, vous pouvez ajouter des fonctionnalités supplémentaires si nécessaire.

        RendererManager_Render(manager);

        Time_SetFPSLimit(DEFAULT_FPS_AVERAGE);
    }
    
    Exit_All(window);

    return 0;
}
