# Setup du projet – HALS  

Ce document explique comment installer, configurer et lancer le projet.

---

## 1. Prérequis

### Matériel
- Carte microcontrôleur : Arduino Uno (ou compatible)
- Capteur de mouvement : HC-SR501 (PIR)
- Capteur de luminosité : LDR (CDS)
- Relais 5V (commande lampe 220V AC)
- LED témoin
- Lampe (220V AC)
- Résistance 10 kΩ (pont diviseur LDR)
- Résistance 220 Ω (protection LED)
- Breadboard
- Fils Dupont
- Câble USB (alimentation et programmation)
- Câble secteur (alimentation lampe)

Voir le détail complet dans [hardware/BOM.md](hardware/BOM.md).

### Logiciel
- Visual Studio Code
- Extension PlatformIO IDE
- Pilote USB (CH340 si clone Arduino)

---

## 2. Installation de l’environnement

1. Installer **Visual Studio Code**
2. Installer l’extension **PlatformIO IDE**
3. Redémarrer VS Code

---

## 3. Cloner le projet

```bash
git clone https://github.com/ms-alien/HALS---Human-Aware-Smart-Lighting-System.git
cd Station_Meteo_Arduino
```
- Ouvrir le dossier avec VS Code.
---

## 4. Configuration PlatformIO

Le projet est déjà configuré via le fichier platformio.ini.

Vérifier :
board = uno
monitor_speed = 9600
Aucune modification n’est nécessaire par défaut.

---

## 5. Câblage du matériel

Suivre le schéma de câblage :

Image : hardware/wiring.png

Schéma électronique : hardware/schematic.pdf

Résumé des connexions principales :
| Élément             | Pin Arduino   |
| ------------------- | ------------- |
| HC-SR501 (OUT)      | D8            |
| LDR (pont diviseur) | A0            |
| LED témoin          | D7 (via 220Ω) |
| Relais              | D5            |
| Alimentation relais | 5V / GND      |

⚠️ Attention 220V AC
Le relais commute une charge secteur. Manipuler hors tension et avec isolation correcte.

---

## 6. Compilation et téléversement

Brancher la carte en USB

Cliquer sur Upload dans PlatformIO

Ouvrir le Serial Monitor (9600 bauds) pour debug

## 7. Vérification du fonctionnement

- Le système mesure en continu la luminosité ambiante (LDR)
- Un filtre exponentiel est appliqué pour stabiliser la mesure
- Si la luminosité est inférieure au seuil défini ET
- qu’un mouvement est détecté par le PIR :

➡️ La LED témoin et la lampe s’allument
➡️ Un timer de 60 secondes est lancé
➡️ Tout nouveau mouvement réinitialise le timer

Après expiration sans mouvement :
- LED et lampe s’éteignent automatiquement

## 8. Dépannage rapide
Lampe ne s’allume pas
- Vérifier le seuil LDR_THRESHOLD
- Tester le PIR seul
- Vérifier le type de relais (actif HIGH / LOW)

Allumage intempestif
- Ajuster la sensibilité du HC-SR501
- Augmenter le filtrage LDR (alpha)

Téléversement impossible
- Vérifier le port COM
- Installer le pilote CH340

---

## 9. Notes
Le capteur Big Sound a été testé puis abandonné car sensibilité trop faible pour une détection fiable en environnement réel

Le projet reste modulaire pour ajout futur (Bluetooth, RTC, réglages dynamiques)