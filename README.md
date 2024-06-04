# 2024_camera_Oswin
![image](https://github.com/Oswin243/2024_camera_Oswin/assets/166718391/ee703e5f-3518-406a-b32f-7055061311c4) [lien EasyEDA](https://oshwlab.com/oswin03/sch-ma-cam-ra) 

- [Introduction](#introduction)
- [Le schéma bloc](#schéma-bloc) 
- [Les caractéristiques](#Les-caractéristiques)
  - [Schéma de principe de la caméra](#schéma-de-principe-de-la-caméra)
  - [Schéma de principe du PCB](#Schéma-de-principe-du-PCB)
- [Bibliothèques nécessaires](#bibliothèques-nécessaires)  
- [Partie électrique](#partie-mécanique)
   - [Schéma de principe de la caméra](#schéma-de-principe-de-la-caméra)
   - [Schéma de principe du PCB](#schéma-de-principe-du-PCB)
   - [Sérigraphie du PCB](#Sérigraphie-du-PCB)


## Introduction

Pour le cadre de mon projet de fin d’études, j’ai décidé de concevoir une caméra de surveillance connectée, une idée qui m’est venue après avoir visionné des vidéos sur la chaîne [YouTube de Max Imagination](https://www.youtube.com/watch?v=Ul0h5Maeoeg&t=4s). Cette caméra sera en mesure de se déplacer de haut en bas et de droite à gauche avec à des servomoteurs, de filmer tout ce qui se trouve dans son champ de vision. Elle sera également capable de détecter une intrusion avec à des capteurs infrarouges. De plus, la caméra pourra réagir aux mouvements dans son champ de vision, de jour comme de nuit, grâce à des LED infrarouges.
Ce projet représente ma passion pour la technologie et mon engagement envers ce domaine. 
J’ai choisi ce projet par passion pour la technologie de surveillance et les robots.
Ce projet reflète ma passion pour la technologie de surveillance, les robots, et la mécanique, ainsi que mon engagement envers ces domaines. Tout au long de mon parcours scolaire, j’ai acquis des connaissances solides dans ces domaines et j’ai su démontrer ma capacité à résoudre des problèmes.
C’est avec plaisir que je choisis ce projet, car il représente pour moi la fin d’un long parcours scolaire.


## Le schéma bloc

![image](https://github.com/Oswin243/2024_camera_Oswin/assets/166718391/252e9367-89a1-4cfe-adb6-858941e33dae)


Explication du schéma bloc 

Alimentation : l’alimentation est l’élément vital de l’ensemble du projet, fournissant l’énergie nécessaire à son fonctionnement.

Capteur infrarouge, gauche, droite : capte les mouvements dans son champ d’action, à gauche et à droite.

PCF8574 : Apporte des entrées supplémentaires. 

ESP32 : le « cerveau » du système, l’ESP32 traite, transmet et reçoit toutes les informations nécessaires au fonctionnement du programme.

Smartphone : permets de visualiser le flux vidéo grâce à une connexion Wi-Fi.

PCA9685 : Apporte des sorties supplémentaire et genre nativement du PWM.

LED rouge : indique l’activité de la caméra, signalant ainsi son fonctionnement.

LED infrarouge, gauche, droite : émettre des infrarouges pour voir dans l’obscurité.

Servomoteur x, y : ils permettent d’effectuer des rotations de haut en bas et de gauche à droite, contrôlant ainsi la direction de la caméra

## Les caractéristiques

Caractéristique générale   

•	M5Stack ESP32 Timer Camera 
•	Capteur infrarouge
•	Servomoteurs   
•	LED infrarouge 
•	Resistance 
•	Condensateur 
•	LED 
•	Interrupteur 
•	Transistor
•	Porte fusible   
  
Caractéristique électrique

•	Alimentation : sur secteur  
•	Consommation : pas vérifié  
 
Caractéristique mécanique 

•	Dimension : 218 mm x  238,99 mm  
•	Poids : 851 g 
•	Matériau : PLA (acide polylactique) 


## Schéma de principe de la caméra

![image](https://github.com/Oswin243/2024_camera_Oswin/assets/166718391/22fe538d-27cd-4880-be23-c74240a38d34)

M5stack timer-caméra/ Transistor BS170 /Servomoteur MG996r/ PCF8574/ PCA9685


##







