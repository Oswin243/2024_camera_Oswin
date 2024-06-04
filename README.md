# 2024_camera_Oswin
![image](https://github.com/Oswin243/2024_camera_Oswin/assets/166718391/ee703e5f-3518-406a-b32f-7055061311c4) [lien EasyEDA](https://oshwlab.com/oswin03/sch-ma-cam-ra) 

- [Introduction](#Introduction)
- [Le schéma bloc](#Le-schéma-bloc) 
- [Les caractéristiques](#Les-caractéristiques)
- [Le schéma de principe de la caméra](#Le-schéma-de-principe-de-la-caméra)
  - [Le routage et sérigraphie du PCB](#Le-routage-et-sérigraphie-du-PCB)
- [Bibliothèques nécessaires](#Bibliothèques-nécessaires)  
- [Partie mécanique](#Partie-mécanique)
- 



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


## Le schéma de principe de la caméra

![image](https://github.com/Oswin243/2024_camera_Oswin/assets/166718391/22fe538d-27cd-4880-be23-c74240a38d34)

M5stack timer-caméra/ Transistor BS170 /Servomoteur MG996r/ PCF8574/ PCA9685


## Le routage et sérigraphie du PCB

![image](https://github.com/Oswin243/2024_camera_Oswin/assets/166718391/7ec2256c-1516-42ba-8925-051054e7fa40)   ![image](https://github.com/Oswin243/2024_camera_Oswin/assets/166718391/172b47bf-f02c-4a56-b8aa-73f446364606)

[Lien du schéma vers EasyEDA](https://oshwlab.com/oswin03/sch-ma-cam-ra) 

60 mm x 60 mm

## Bibliothèques nécessaires 

Bibliothèques nécessaires pour intégrer les cartes : 
https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json ,   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json 

## Partie mécanique

![image](https://github.com/Oswin243/2024_camera_Oswin/assets/166718391/6ecee9cc-4031-4a01-9e86-9090dd8af188)
![image](https://github.com/Oswin243/2024_camera_Oswin/assets/166718391/1d2abec6-7861-4c47-b956-27963fa86319)
![image](https://github.com/Oswin243/2024_camera_Oswin/assets/166718391/fec9397c-c882-4702-96ce-81da2da3684b)










