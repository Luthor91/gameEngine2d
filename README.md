# GameEngine2D

Moteur actuellement en cours de développement.
Moteur actuellement inutilisable.

## Description
GameEngine2D est un moteur de jeu 2D simple conçu pour être utilisé comme une bibliothèque. Il se concentre sur la gestion des entités, des composants et des systèmes pour créer des jeux en 2D avec des événements et des particules.

Pour l'instant, il est disponible uniquement pour Linux, avec une compatibilité Windows prévue à long terme.

## Fonctionnalités
- **Entités et Composants** : Gestion des entités avec des composants modulaires (position, sprite, taille, hitbox, etc.).
- **Système d'Événements** : Support d'événements personnalisés pour interagir avec les entités et les composants.
- **Timers et Émissions d'Événements** : Gestion de timers pour déclencher des événements dans le temps.
- **Gestion de Particules** : Support pour la création et le contrôle de systèmes de particules.
- **Intégration SDL2** : Utilisation de SDL2 pour la gestion des graphismes et de la fenêtre.
- **Système extensible** : Facilité pour ajouter des composants et des systèmes personnalisés.

## Installation

### Prérequis
- **Make** : Assurez-vous que `make` est installé sur votre système.

### Linux
1. Clonez le dépôt ou téléchargez les sources.
2. Exécutez la commande suivante dans le répertoire du projet :
   ```sh
   make linstall
   ```
   
### Arch Linux

1. Clonez le dépôt ou téléchargez les sources.
2. Exécutez la commande suivante :
   ```sh
   make ainstall
   ```

## Compatibilité

- Linux : Compatible et testé.
- Windows : Prévu à long terme, mais pas encore supporté.

## Utilisation

Incluez simplement GameEngine2D comme une bibliothèque dans votre projet. Utilisez les systèmes d'entités, de composants et d'événements pour créer et gérer vos objets de jeu.

GameEngine2D vise à être un moteur léger et simple d'utilisation, adapté à des projets 2D.
