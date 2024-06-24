# gameEngine2d


Core
- Events
- Graphics
- Input
- Physics
- Sounds

(Tutoriel bancal encore en cours)
Pour exécuter sur WSL 2 vous devez : 
- installer https://sourceforge.net/projects/xming/
- exécuter xlaunch
- multiple windows - ensuite appuyez sur suivant
- dans la taskbar clic droit sur xming, regardez l'adresse ip dans les logs de xming

Sur WSL : 
- sudo nano .bashrc
- export DISPLAY=$(ip route show to 0.0.0.0/0 | awk '{ print $3 }'):0
- export XDG_RUNTIME_DIR=$(ip route show to 0.0.0.0/0 | awk '{ print $3 }'):0
- sauvegarder et exit
- source ~/.bashrc