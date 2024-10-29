Voici la table des matières mise à jour, avec l'encodeur en premier suivi de l'ADC :

# Table des Matières

1. **Introduction**
   - 1.1. Présentation du Projet
   - 1.2. Objectifs

2. **Documentation de l'Encodeur**
   - 2.1. Introduction à l'Encodeur
   - 2.2. Description du Code
      - 2.2.1. Fonction `MyEncoder_Base_Init`
      - 2.2.2. Fonction `Get_MyEncoder`
      - 2.2.3. Fonction `Get_MyEncoder_In_Deg`
      - 2.2.4. Fonction `Reset_MyEncoder`
   - 2.3. Utilisation de l'Encodeur
      - 2.3.1. Initialisation de l'Encodeur
      - 2.3.2. Obtention de la Valeur de l'Encodeur
      - 2.3.3. Réinitialisation de l'Encodeur
   - 2.4. Conclusion de l'Encodeur

3. **Documentation de l'ADC**
   - 3.1. Introduction à l'ADC
   - 3.2. Description du Code
      - 3.2.1. Fonction `MyADC_Init`
      - 3.2.2. Fonction `MyADC_StartConv`
      - 3.2.3. Fonction `MyADC_Read`
      - 3.2.4. Gestion des Interruptions avec `ADC1_2_IRQHandler`
   - 3.3. Utilisation de l'ADC
      - 3.3.1. Initialisation de l'ADC
      - 3.3.2. Démarrage de la Conversion
      - 3.3.3. Lecture des Résultats
   - 3.4. Conclusion de l'ADC

---
# Introduction 
	blablalbla

# Documentation de l'Encodeur

## Introduction aux Encodeurs

Un encodeur est un dispositif utilisé pour mesurer la position, la vitesse ou la direction d'un objet en mouvement. Dans les systèmes embarqués, les encodeurs sont souvent utilisés pour contrôler des moteurs et d'autres dispositifs de mouvement. Les encodeurs peuvent être de différents types, mais les encodeurs incrémentaux sont couramment utilisés pour leur simplicité et leur efficacité.

### Caractéristiques des Encodeurs Incrémentaux

- **Résolution** : Le nombre de pulses par tour. Cela définit la précision de la mesure.
- **Direction** : L'encodeur peut détecter la direction du mouvement en comparant les signaux des deux canaux.
- **Position** : L'encodeur peut donner une position relative à partir d'un point de départ.

### Caractéristiques particulière dans notre cas d'utilisation

Dans notre cas nous utilisons la fonctionnalité encodeur des timer, c'est à dire que le compteur du timer va réagir aux front montant et descendant de notre encodeur, permettant une mesure instantané de sa valeur. 

## Description du Code

### Fichiers Inclus

```c
#include "stm32f10x.h"
#include "MyEncoder.h"
```

Ces fichiers incluent les définitions et déclarations nécessaires pour travailler avec la bibliothèque STM32 et votre propre bibliothèque d'encodeurs.

### Fonction `MyEncoder_Base_Init`

```c
void MyEncoder_Base_Init(TIM_TypeDef * Timer, unsigned short ARR);
```

**Paramètres** :
- `TIM_TypeDef * Timer`: Pointeur vers l'instance du timer (TIM1, TIM2, TIM3 ou TIM4) utilisé pour lire les signaux de l'encodeur.
- `unsigned short ARR`: Valeur du registre d'auto-rechargement (ARR) pour définir la période du timer.

**Fonctionnement** :
1. **Activation de l'Horloge** :
   - L'horloge pour le timer spécifié est activée via les registres RCC (Reset and Clock Control).

2. **Configuration des Broches GPIO** :
   - Les broches PA0 et PA1 sont configurées comme entrées flottantes pour recevoir les signaux d'encodeur.
   - PA2 est également configurée pour être utilisée avec une interruption EXTI (External Interrupt) lorsque Z passe à 1.

3. **Configuration du Timer** :
   - Le registre ARR du timer est configuré pour définir la période du timer (ici le nombre de pas de l'encodeur).
   - Les modes de comptage sont configurés pour utiliser les entrées TI1 et TI2.
   - Les canaux de capture de comparaison sont configurés pour lire les signaux d'encodeur (CC1S et CC2S).
   - Les filtres de capture d'entrée (IC1F et IC2F) sont désactivés car il ne semble pas y avoir de pb de bruit.
   - Le timer est activé en mettant le bit CEN (Counter Enable) à 1.

### Fonction `Get_MyEncoder`

```c
int16_t Get_MyEncoder(TIM_TypeDef * Timer);
```

**Paramètres** :
- `TIM_TypeDef * Timer`: Pointeur vers l'instance du timer configuré.

**Fonctionnement** :
- Cette fonction retourne la valeur actuelle du compteur d'encodeur (CNT) sous forme d'un entier signé (`int16_t`). Cela donne une indication de la position de l'encodeur.

### Fonction `Get_MyEncoder_In_Deg`

```c
float Get_MyEncoder_In_Deg(TIM_TypeDef * Timer);
```

**Paramètres** :
- `TIM_TypeDef * Timer`: Pointeur vers l'instance du timer configuré.

**Fonctionnement** :
- Cette fonction calcule la position de l'encodeur en degrés en fonction de la valeur du compteur (`CNT`) et de la valeur d'auto-rechargement (`ARR`).
- La formule utilisée est : 
  \[
  \text{Position en degrés} = \left(\frac{\text{Valeur de l'encodeur} \times \text{ARR}}{\text{RESOLUTION de l'encodeur}}\right)
  \]

### Fonction `Reset_MyEncoder`

```c
void Reset_MyEncoder(TIM_TypeDef * Timer);
```

**Paramètres** :
- `TIM_TypeDef * Timer`: Pointeur vers l'instance du timer configuré.

**Fonctionnement** :
- Cette fonction réinitialise le compteur d'encodeur à zéro en écrivant 0 dans le registre CNT.

### Utilisation de l'Encodeur

1. **Initialisation** :
   - Appeler `MyEncoder_Base_Init` pour configurer l'encodeur avec les paramètres souhaités (timer et valeur ARR).

2. **Obtenir la Valeur de l'Encodeur** :
   - Utiliser `Get_MyEncoder` pour lire la position actuelle de l'encodeur.

3. **Obtenir la Position en Degrés** :
   - Appeler `Get_MyEncoder_In_Deg` pour convertir la valeur de l'encodeur en une position angulaire en degrés.

4. **Réinitialiser l'Encodeur** :
   - Appeler `Reset_MyEncoder` pour réinitialiser le compteur de l'encodeur.

### Conclusion

Ce code permet de configurer et d'utiliser efficacement un encodeur incrémental dans un microcontrôleur STM32. Il fournit des fonctions pour l'initialisation, la lecture de la position et la réinitialisation du compteur d'encodeur, facilitant ainsi le contrôle de la position et de la direction des systèmes de mouvement.

---

# Documentation de l'ADC

## Introduction au Convertisseur Analogique-Numérique (ADC)

Le convertisseur analogique-numérique (ADC) est un composant essentiel dans de nombreux systèmes embarqués. Il permet de convertir une tension analogique (continue) en une valeur numérique (discrète) que le microcontrôleur peut traiter. Les principales caractéristiques d'un ADC incluent :

- **Résolution** : Détermine le nombre de valeurs numériques différentes que l'ADC peut produire, généralement exprimée en bits. Par exemple, un ADC 12 bits peut produire 4096 valeurs différentes (0 à 4095).
- **Temps d'échantillonnage** : Le temps nécessaire pour échantillonner une entrée analogique avant la conversion.
- **Fréquence d'échantillonnage** : Le nombre d'échantillons pris par seconde.

## Description du Code

### Fichiers Inclus

```c
#include "stm32f10x.h"
#include "MyADC.h"
```

Ces fichiers incluent les définitions et les déclarations nécessaires pour travailler avec la bibliothèque STM32 et la bibliothèque ADC.

### Fonction `MyADC_Init`

```c
void MyADC_Init(ADC_TypeDef * ADC, char channel, char Te, TIM_TypeDef * Timer, char mode);
```

**Paramètres** :
- `ADC_TypeDef * ADC`: Pointeur vers l'instance de l'ADC (ADC1 ou ADC2).
- `char channel`: Numéro du canal à configurer (0 à 15).
- `char Te`: Temps d'échantillonnage (à définir selon la vitesse d'échantillonnage désirée).
- `TIM_TypeDef * Timer`: Pointeur vers l'instance du timer utilisé pour le trigger.
- `char mode`: Mode de conversion (ici, `Single_Not_Cont` pour une conversion unique non continue).

**Fonctionnement** :
1. **Activation de l'Horloge** :
   - L'horloge de l'ADC est activée en écrivant dans les registres RCC (Reset and Clock Control).

2. **Paramétrage du Canal** :
   - Le canal sélectionné est configuré dans le registre de séquence d'échantillonnage (SQR3 ici car on veut travailler sur un seul et unique canal a la fois).
   - Le temps d'échantillonnage est configuré dans les registres SMPR2 ou SMPR1 en fonction du canal.

3. **Mode Non Continu** :
   - L'ADC est configuré pour fonctionner en mode Single non continu (conversion unique).

4. **Configuration du Trigger Externe** :
   - Un timer (TIM1, TIM2, TIM3, ou TIM4) est initialisé pour générer un signal PWM qui servira de trigger pour l'ADC.
   - Le trigger externe de l'ADC est paramétré sur : CC1 pour TIM1, CC2 pour TIM2, TRGO pour TIM3 et CC4 pour TIM4 .

5. **Activation de l'Interruption sur EOC** :
   - L'ADC est configuré pour générer une interruption à la fin de la conversion (End of Conversion - EOC).
   - L'interruption est activée dans le NVIC (Nested Vector Interrupt Controller) pour permettre le traitement de l'interruption.

6. **Activation de l'ADC** :
   - Le bit ADON dans le registre CR2 est activé pour allumer l'ADC.

### Fonction `MyADC_StartConv`

```c
void MyADC_StartConv(ADC_TypeDef * ADC);
```

**Fonctionnement** :
- Cette fonction démarre la conversion analogique en écrivant dans le registre CR2 (SWSTART). Cela déclenche la conversion en utilisant le signal de trigger configuré.

### Fonction `MyADC_Read`

```c
uint16_t MyADC_Read(ADC_TypeDef * ADC);
```

**Fonctionnement** :
- Cette fonction lit la valeur convertie dans le registre DR (Data Register) de l'ADC. Elle ne retourne la valeur que si le bit EOC est in-actif (la conversion est terminée et aquité par l'interruption).

### Fonction `ADC1_2_IRQHandler`

```c
void ADC1_2_IRQHandler(void);
```

**Fonctionnement** :
- Cette fonction est le gestionnaire d'interruption pour les ADC1 et ADC2. Lorsqu'une interruption EOC est déclenchée, elle efface le flag EOC dans le registre de statut (SR) pour permettre de traiter les futures conversions.

### Utilisation de l'ADC

1. **Initialisation** :
   - Appeler `MyADC_Init` pour configurer l'ADC avec les paramètres souhaités (canal, temps d'échantillonnage, timer, mode).

2. **Démarrer la Conversion** :
   - Utiliser `MyADC_StartConv` pour commencer la conversion.

3. **Lire la Valeur Convertie** :
   - Appeler `MyADC_Read` pour récupérer la valeur convertie après que la conversion soit terminée.

### Conclusion

Ce code permet de configurer et d'utiliser efficacement un ADC dans un microcontrôleur STM32. Il fournit des fonctions pour l'initialisation, le démarrage de la conversion et la lecture des valeurs, tout en gérant les interruptions pour une conversion non continue.

