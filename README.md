

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

