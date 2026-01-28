# HALS  
Human-Aware Smart Lighting System

Système d’éclairage intelligent basé sur Arduino, capable d’allumer automatiquement une lampe uniquement lorsqu’une présence est détectée dans un environnement sombre.

---

## 🎯 Objectif du projet

HALS vise à optimiser la consommation énergétique en combinant :
- la détection de mouvement (présence humaine),
- la mesure de la luminosité ambiante.

La lampe ne s’allume **que si nécessaire**, évitant tout gaspillage inutile en plein jour ou en absence de mouvement.

Ce projet est conçu comme :
- un démonstrateur fonctionnel de systèmes embarqués,
- une base extensible pour des applications domotiques intelligentes.

---

## ⚙️ Technologies utilisées

- Microcontrôleur : Arduino Uno
- Langage : C / C++
- Environnement : VS Code + PlatformIO
- Capteurs :
  - HC-SR501 (PIR)
  - LDR (capteur de luminosité)
- Actionneurs :
  - Relais 5V
  - Lampe 220V AC
- Indicateur :
  - LED témoin

---

## 🧠 Principe de fonctionnement

1. Lecture continue de la luminosité ambiante
2. Filtrage logiciel pour éviter les variations brusques
3. Détection de mouvement via PIR
4. Si **obscurité + mouvement** :
   - allumage lampe et LED
   - lancement d’un timer
5. Chaque nouveau mouvement prolonge l’allumage
6. Extinction automatique après temporisation

Le système est entièrement non bloquant et fonctionne en boucle continue.

---

## 🔌 Matériel nécessaire

Voir le fichier [hardware/BOM.md](hardware/BOM.md)

## Schéma de câblage
Voir [hardware/wiring.png](hardware/wiring.png).

---

## 🔧 Installation et configuration
1. Installer VS Code
2. Installer l’extension PlatformIO
3. Cloner le dépôt :
   ```bash
   git clone https://github.com/ms-alien/HALS---Human-Aware-Smart-Lighting-System.git
4. Ouvrir le projet avec PlatformIO
5. Compiler et téléverser sur la carte
6. Les détails sont disponibles dans [docs/setup.md](docs/setup.md).

## Fonctionnement
HALS repose sur deux informations clés :
- la présence humaine (capteur PIR HC-SR501),
- la luminosité ambiante (LDR).

Le programme fonctionne en boucle continue et suit la logique suivante :

1. Le capteur LDR mesure la luminosité ambiante.
   - La valeur brute est filtrée par un filtre exponentiel afin d’éliminer les variations rapides dues au bruit ou aux changements brusques de lumière.
   - Une variable `isDark` est calculée en comparant la luminosité filtrée à un seuil prédéfini (`LDR_THRESHOLD`).

2. Le capteur PIR surveille la présence humaine.
   - Lorsqu’un mouvement est détecté, un état interne `motionDetected` passe à vrai.
   - Un minuteur est réinitialisé à chaque nouvelle détection.

3. Si et seulement si :
   - un mouvement est détecté,
   - ET que l’environnement est sombre,

   alors :
   - la LED témoin s’allume,
   - le relais est activé,
   - la lampe s’allume.

4. Tant que des mouvements sont détectés avant la fin du délai :
   - le minuteur est relancé,
   - la lampe reste allumée.

5. En l’absence de mouvement pendant la durée définie (`ledOnTime`) :
   - la LED témoin s’éteint,
   - le relais est désactivé,
   - la lampe s’éteint automatiquement.

Ce comportement garantit que l’éclairage ne fonctionne que lorsque cela est réellement nécessaire, réduisant ainsi la consommation énergétique.

---

## 📷 Illustrations

Images et demonstration disponibles dans [assets/](assets/).

## 🚀 Améliorations futures

Réglage dynamique du seuil de luminosité

Communication Bluetooth / Wi-Fi

Interface mobile

Détection multi-zones

Mode économie avancé

---

# 👤 Auteur

Ali Diarra

Projet développé dans le cadre d’un portfolio en systèmes embarqués.

## 📄 Licence
Ce projet est sous licence MIT.
