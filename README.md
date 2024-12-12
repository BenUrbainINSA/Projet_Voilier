# Voilier Automatisé

## Table des Matières

1. [Introduction](#introduction)
2. [Fonctionnalités du Voilier](#fonctionnalités-du-voilier)
3. [Architecture Logicielle](#architecture-logicielle)
4. [Drivers](#drivers)
   - 4.1 [GPIO](#gpio)
   - 4.2 [ADC](#adc)
   - 4.3 [Encodeur](#encodeur)
   - 4.4 [Timer](#timer)
   - 4.5 [Servo](#servo)
   - 4.6 [USART](#usart)
5. [Services](#services)
   - 5.1 [Gestion des Voiles](#gestion-des-voiles)
   - 5.2 [Gestion de la Batterie](#gestion-de-la-batterie)
   - 5.3 [Gestion de la Transmission](#gestion-de-la-transmission)
   - 5.4 [Module Anti-Chavirage](#module-anti-chavirage)
   - 5.5 [Module Plateau](#module-plateau)
6. [Utilisation](#utilisation)

---

## Introduction

Ce projet consiste à développer un voilier automatisé capable de naviguer de manière autonome. Le voilier dispose de plusieurs fonctions, comme le bordage automatique en fonction du vent, un système de sécurité pour limiter les risques de chavirage, et une gouverne contrôlable à distance via une télécommande.

Le système transmet régulièrement des informations essentielles à la télécommande, notamment l'angle des voiles et l'état de la batterie, pour permettre un suivi efficace.

---

## Fonctionnalités du Voilier

### 1. Bordage Automatique

- Ajuste automatiquement l'angle des voiles en fonction de la direction du vent.

### 2. Sécurité Anti-Chavirage

- Réduit le bordage au minimum si une instabilité critique est détectée.

### 3. Gouverne Contrôlable

- Permet de contrôler la direction du voilier à l'aide d'une télécommande.

### 4. Transmission de Données

- Envoie les informations suivantes toutes les 3 secondes :
  - Angle des voiles.
  - Tension de la batterie.

---

## Architecture Logicielle

Le projet est basé sur une architecture modulaire permettant une gestion claire des différents sous-systèmes. Les principaux modules incluent :

- Gestion des encodeurs pour la mesure des angles.
- Gestion de l'ADC pour surveiller les paramètres analogiques, comme la tension de la batterie.
- Système anti-chavirage.
- Module de gestion des voiles.
- Module de transmission pour communiquer avec la télécommande.

---

## Drivers

### GPIO

Ce driver permet de configurer et d'utiliser les ports GPIO du microcontrôleur STM32, avec des fonctionnalités telles que la configuration des pins, la lecture et l'écriture sur les pins, ainsi que la gestion des interruptions externes.

## Fonctions Principales

### 1. `MyGPIO_Init(GPIO_TypeDef *GPIO, char GPIO_Pin, char GPIO_Conf, char type, int Pull)`
#### Description
Cette fonction initialise un pin GPIO sur le STM32, configure son mode (entrée ou sortie), et définit sa configuration (analogique, flottant, pull-up, pull-down).

#### Paramètres
- `GPIO` : Le port GPIO à configurer (ex. `GPIOA`, `GPIOB`, `GPIOC`, etc.).
- `GPIO_Pin` : Le numéro du pin à configurer (0-15).
- `GPIO_Conf` : La configuration du pin (voir tableau ci-dessous pour les options).
- `type` : Le type de configuration (entrée ou sortie) :
  - `0` : Entrée
  - `1` : Sortie 10 MHz
  - `2` : Sortie 2 MHz
  - `3` : Sortie 50 MHz
- `Pull` : La configuration de résistance de pull :
  - `1` : Pull-up
  - `-1` : Pull-down
  - `0` : Aucune résistance de pull

#### Détails de la Configuration
La fonction configure le pin spécifié pour qu'il soit soit en entrée (flottant, analogique, ou avec résistance de pull), soit en sortie avec des options de vitesse et d'activation.

### 2. `MyGPIO_Read(GPIO_TypeDef *GPIO, char GPIO_Pin)`
#### Description
Cette fonction permet de lire l'état (haut ou bas) d'un pin GPIO.

#### Paramètres
- `GPIO` : Le port GPIO du pin à lire (ex. `GPIOA`, `GPIOB`, etc.).
- `GPIO_Pin` : Le numéro du pin à lire (0-15).

#### Retour
Retourne `1` si le pin est à l'état haut, sinon retourne `0`.

### 3. `MyGPIO_Set(GPIO_TypeDef *GPIO, char GPIO_Pin)`
#### Description
Cette fonction permet de définir l'état d'un pin GPIO à l'état haut (logique `1`).

#### Paramètres
- `GPIO` : Le port GPIO du pin à modifier (ex. `GPIOA`, `GPIOB`, etc.).
- `GPIO_Pin` : Le numéro du pin à définir à `1` (haut).

### 4. `MyGPIO_Reset(GPIO_TypeDef *GPIO, char GPIO_Pin)`
#### Description
Cette fonction permet de définir l'état d'un pin GPIO à l'état bas (logique `0`).

#### Paramètres
- `GPIO` : Le port GPIO du pin à modifier (ex. `GPIOA`, `GPIOB`, etc.).
- `GPIO_Pin` : Le numéro du pin à définir à `0` (bas).

### 5. `MyGPIO_Toggle(GPIO_TypeDef *GPIO, char GPIO_Pin)`
#### Description
Cette fonction permet de basculer l'état du pin GPIO : si le pin est à l'état haut, il sera mis à l'état bas, et vice versa.

#### Paramètres
- `GPIO` : Le port GPIO du pin à modifier (ex. `GPIOA`, `GPIOB`, etc.).
- `GPIO_Pin` : Le numéro du pin à basculer.

### 6. `MyGPIO_Active_EXTI3_IT(char Prio, void(*IT_function)(TIM_TypeDef * Timer))`
#### Description
Cette fonction permet d'activer une interruption externe sur le pin GPIO spécifié, en utilisant un front montant. Elle configure l'EXTI (External Interrupt) pour le pin et appelle une fonction de rappel (callback) lors de l'interruption.

#### Paramètres
- `Prio` : La priorité de l'interruption (de 0 à 15, où 0 est la plus haute priorité).
- `IT_function` : Le pointeur vers la fonction de rappel à appeler lors de l'interruption. Cette fonction doit prendre un argument de type `TIM_TypeDef*` (ex. `TIM2`).

### 7. `EXTI4_IRQHandler(void)`
#### Description
Cette fonction est le gestionnaire d'interruption pour l'EXTI4, qui sera appelé lorsqu'une interruption externe (sur le pin configuré) se produit. Elle appelle la fonction de rappel définie par l'utilisateur (via `MyGPIO_Active_EXTI3_IT`) si une telle fonction est définie.

#### Fonctionnement
- Lorsque l'interruption est déclenchée, cette fonction abaisse le flag d'interruption et appelle la fonction de rappel (si définie) en passant le timer (`TIM2`).

## Table de Configuration des Pins GPIO

| GPIO_Conf (bits 3:2) | Mode de Fonctionnement | Description |
|----------------------|------------------------|-------------|
| `00`                 | Analogique             | Le pin est en mode analogique. |
| `01`                 | Flottant               | Le pin est configuré en entrée flottante (pas de résistance de pull). |
| `10`                 | Push-Pull              | Le pin est configuré en sortie à faible vitesse. |
| `11`                 | Open Drain             | Le pin est configuré en sortie à faible vitesse avec une résistance externe si nécessaire. |

## Remarques

- Le mode `MyGPIO_Init` configure aussi bien les entrées que les sorties, et peut inclure une résistance de pull si nécessaire.
- L'interruption EXTI est configurée pour réagir sur un front montant, mais cela peut être ajusté selon les besoins spécifiques.
- L'utilisation de `EXTI4_IRQHandler` nécessite d'avoir correctement configuré la gestion des interruptions dans le système d'exploitation (NVIC).


### ADC

Ce driver permet de configurer et d'utiliser l'ADC (Analog-to-Digital Converter) des microcontrôleurs STM32, spécifiquement pour des conversions en mode **single (non-continu)**. Il fournit des fonctions pour l'initialisation de l'ADC, le lancement des conversions, et la lecture des résultats.

## Fonctions Principales

### 1. `MyADC_Init(ADC_TypeDef *ADC, char channel, char Te, char mode)`
#### Description
Cette fonction initialise l'ADC pour effectuer des conversions sur un canal spécifié. Elle configure le pré-diviseur de l'horloge de l'ADC, l'activation du canal, et les paramètres de la conversion.

#### Paramètres
- `ADC` : Le périphérique ADC à initialiser (ex. `ADC1`, `ADC2`).
- `channel` : Le numéro du canal à configurer (0-15). Ce canal sera utilisé pour la conversion.
- `Te` : Le temps d'échantillonnage pour le canal, spécifié en fonction de la vitesse de conversion (voir la documentation STM32 pour les valeurs possibles).
- `mode` : Le mode de fonctionnement de l'ADC :
  - `Single_Not_Cont` : Mode conversion unique (non-continue).

#### Fonctionnement
- Active les horloges pour le périphérique ADC spécifié.
- Configure le pré-diviseur d'horloge de l'ADC à une valeur de 6.
- Initialise le canal pour la conversion unique.
- Configure le temps d'échantillonnage pour le canal.
- Active le mode non-continu et configure le trigger externe pour démarrer la conversion.

### 2. `MyADC_StartConv(ADC_TypeDef *ADC)`
#### Description
Cette fonction démarre une conversion ADC en activant le bit de démarrage dans le registre de contrôle (CR2).

#### Paramètres
- `ADC` : Le périphérique ADC à utiliser (ex. `ADC1`, `ADC2`).

#### Fonctionnement
- La conversion est démarrée en activant le bit `ADC_CR2_SWSTART` dans le registre de contrôle de l'ADC.

### 3. `MyADC_Read(ADC_TypeDef *ADC)`
#### Description
Cette fonction permet de lire le résultat d'une conversion ADC. Elle attend la fin de la conversion, puis récupère la valeur numérique convertie.

#### Paramètres
- `ADC` : Le périphérique ADC à lire (ex. `ADC1`, `ADC2`).

#### Retour
Retourne la valeur numérique résultante de la conversion (valeur sur 16 bits).

#### Fonctionnement
- Attend que la conversion soit terminée (vérification du bit `ADC_SR_EOC`).
- Lit la valeur convertie dans le registre de données de l'ADC (`ADC_DR`).
- Efface le flag `EOC` (End of Conversion) pour indiquer que la conversion a été traitée.

## Détails du Mode de Fonctionnement

- **Mode non-continu (Single_Not_Cont)** :
  - Le mode de conversion est configuré pour réaliser une seule conversion lorsque le trigger est activé. Après la conversion, le périphérique ADC revient à un état d'attente et ne continue pas à convertir en boucle.

## Notes

- **Temps d'échantillonnage (Te)** : 
  - Le temps d'échantillonnage est paramétré par le registre `SMPR1` ou `SMPR2` en fonction du canal sélectionné (canaux 0-9 ou 10-15). Ce paramètre définit combien de temps le convertisseur doit échantillonner la tension sur le canal avant de commencer la conversion.
  
- **Calibration** :
  - La calibration de l'ADC est effectuée lors de l'initialisation pour s'assurer que les conversions sont précises.

### Encodeur

Ce driver permet de configurer et d'utiliser un encodeur rotatif avec les timers de la famille STM32. Il fournit des fonctions pour initialiser le timer pour lire les impulsions de l'encodeur, obtenir la position de l'encodeur sous forme de valeur brute ou en degrés, et réinitialiser la position de l'encodeur.

## Fonctions Principales

### 1. `MyEncoder_Base_Init(TIM_TypeDef *Timer, unsigned short ARR)`
#### Description
Cette fonction initialise le timer pour utiliser un encodeur en mode "compteur quadratique" (compte les impulsions sur les deux canaux de capture). Elle configure également les GPIO nécessaires pour lire les signaux de l'encodeur.

#### Paramètres
- `Timer` : Le timer à utiliser pour lire les impulsions de l'encodeur (ex. `TIM1`, `TIM2`, `TIM3`, `TIM4`).
- `ARR` : La valeur de l'Auto-Reload Register (ARR), qui définit la valeur maximale du compteur du timer avant qu'il ne se réinitialise.

#### Fonctionnement
- Active l'horloge pour le timer spécifié.
- Configure les broches GPIO nécessaires pour l'encodeur :
  - PA0 et PA1 sont configurées comme entrées flottantes pour recevoir les signaux de l'encodeur (par exemple, quadrature).
  - PB4 est configurée pour une interruption EXTI (External Interrupt) si nécessaire.
- Configure le timer pour le mode "compteur quadratique" :
  - Le timer compte sur les deux canaux de capture (TI1 et TI2).
  - Le registre `ARR` est ajusté en fonction de la valeur fournie.
  - Le mode de capture est configuré avec les filtres d'entrée définis sur zéro (pas de filtrage).
  - Le compteur du timer est activé.

### 2. `Get_MyEncoder(TIM_TypeDef *Timer)`
#### Description
Cette fonction retourne la valeur brute du compteur du timer, ce qui correspond à la position actuelle de l'encodeur.

#### Paramètres
- `Timer` : Le timer à lire pour obtenir la valeur de l'encodeur (ex. `TIM1`, `TIM2`, `TIM3`, `TIM4`).

#### Retour
- Retourne la valeur actuelle du compteur du timer (`CNT`), qui correspond à la position de l'encodeur.

#### Fonctionnement
- La fonction lit directement le registre `CNT` du timer pour obtenir la valeur actuelle du compteur.

### 3. `Get_MyEncoder_In_Deg(TIM_TypeDef *Timer)`
#### Description
Cette fonction retourne la position de l'encodeur en degrés, après conversion de la valeur du compteur.

#### Paramètres
- `Timer` : Le timer à lire pour obtenir la position de l'encodeur (ex. `TIM1`, `TIM2`, `TIM3`, `TIM4`).

#### Retour
- Retourne la position de l'encodeur en degrés, après une conversion de la valeur du compteur.

#### Fonctionnement
- Lit la valeur du compteur du timer.
- Divise cette valeur par 4 (en fonction de la résolution de l'encodeur et des configurations spécifiques).
- Applique un offset à la valeur pour obtenir un résultat en degrés, puis renvoie la valeur absolue.

### 4. `Reset_MyEncoder(TIM_TypeDef *Timer)`
#### Description
Cette fonction réinitialise la position de l'encodeur à zéro.

#### Paramètres
- `Timer` : Le timer à réinitialiser (ex. `TIM1`, `TIM2`, `TIM3`, `TIM4`).

#### Fonctionnement
- Réinitialise la valeur du compteur du timer (`CNT`) à zéro.

## Détails du Mode de Fonctionnement

### Mode Compteur Quadratique
- Les timers sont configurés pour utiliser les canaux de capture TI1 et TI2 en mode quadratique. Cela permet de détecter les signaux d'encodeur quadrature, qui sont typiquement envoyés sur deux lignes.
- Le registre `SMCR` (Slave Mode Control Register) est configuré en mode `011`, ce qui permet au timer de compter en fonction des entrées des canaux TI1 et TI2.
  
### Calcul de la Position
- La position de l'encodeur est lue directement à partir du compteur du timer (`CNT`).
- La conversion en degrés est réalisée en divisant la valeur du compteur par 4 (ce facteur peut être ajusté en fonction de la résolution de l'encodeur) et en appliquant un offset (`OFFSET_ENCODER`), qui peut être défini selon les besoins.

### Réinitialisation de l'Encodeur
- La fonction `Reset_MyEncoder` permet de réinitialiser la position de l'encodeur à zéro en modifiant la valeur du compteur du timer.

## Notes
  
- **Offset** : Un offset (`OFFSET_ENCODER`) est appliqué lors de la conversion en degrés. Cet offset peut être ajusté pour tenir compte de l'orientation initiale de l'encodeur.

- **Configuration du Timer** : Le registre `ARR` définit la limite du compteur. Assurez-vous que cette valeur est correctement ajustée en fonction de la résolution de l'encodeur et du nombre d'impulsions par tour.


### Timer

Ce driver permet de configurer et d'utiliser les timers STM32 pour différentes applications, comme la génération de signaux PWM, l'activation d'interruptions sur des événements de timer, et la gestion de la fréquence d'horloge des timers. Il offre également la possibilité d'activer des interruptions pour exécuter des fonctions spécifiques à chaque débordement de timer.

## Fonctions Principales

### 1. `MyTimer_Base_Init(TIM_TypeDef *Timer, unsigned short ARR, unsigned short PSC, char Type)`
#### Description
Cette fonction initialise un timer avec une fréquence de comptage déterminée par les paramètres `ARR` et `PSC`. Elle permet également de configurer le mode de l'alignement du timer.

#### Paramètres
- `Timer` : Le timer à initialiser (ex. `TIM1`, `TIM2`, `TIM3`, `TIM4`).
- `ARR` : La valeur de l'Auto-Reload Register (ARR), définissant la période du timer.
- `PSC` : La valeur du prescaler, qui détermine la fréquence d'horloge du timer.
- `Type` : Détermine l'alignement du timer. Si `Type == 0x1`, le timer est configuré en mode "edge-aligned" (alignement sur le front montant).

#### Fonctionnement
- Active l'horloge pour le timer spécifié.
- Configure la valeur du prescaler (`PSC`) et du registre `ARR` pour définir la période de comptage.
- Configure l'alignement du timer en fonction du paramètre `Type` :
  - Si `Type == 0x1`, le mode d'alignement est défini sur "edge-aligned".
  - Sinon, le mode "center-aligned" est activé.

### 2. `MyTimer_ActiveIT(TIM_TypeDef *Timer, char Prio, void(*IT_function)(void))`
#### Description
Cette fonction permet d'activer une interruption pour un timer donné et de lier une fonction spécifique qui sera appelée lors d'un événement d'interruption.

#### Paramètres
- `Timer` : Le timer pour lequel l'interruption doit être activée (ex. `TIM1`, `TIM2`, `TIM3`, `TIM4`).
- `Prio` : La priorité de l'interruption (plus faible valeur = plus haute priorité).
- `IT_function` : Pointeur vers la fonction à exécuter lors de l'interruption du timer.

#### Fonctionnement
- Active l'interruption pour le timer spécifié en utilisant le registre `DIER`.
- Configure la priorité de l'interruption via le contrôleur NVIC.
- Associe la fonction `IT_function` au vecteur d'interruption, qui sera appelée lors du débordement du timer.

### 3. `MyTimer_PWM(TIM_TypeDef *Timer, char Channel, char mode)`
#### Description
Cette fonction configure un canal de PWM (modulation de largeur d'impulsion) pour un timer donné, en choisissant le mode de fonctionnement du PWM.

#### Paramètres
- `Timer` : Le timer à utiliser (ex. `TIM1`, `TIM2`, `TIM3`, `TIM4`).
- `Channel` : Le canal du timer à configurer pour le PWM (1 à 4).
- `mode` : Le mode du PWM à utiliser. Si `mode == 0x6`, un mode de PWM "centre-aligned" est activé ; sinon, un mode "edge-aligned" est utilisé.

#### Fonctionnement
- Configure les registres du timer pour générer un signal PWM sur le canal spécifié.
- Le mode du PWM peut être défini comme "edge-aligned" ou "centre-aligned" en fonction du paramètre `mode`.

### 4. `Set_PWM_Duty_Cycle(TIM_TypeDef *Timer, float valeur, char channel)`
#### Description
Cette fonction permet de régler le rapport cyclique (duty cycle) d'un signal PWM sur un canal spécifique d'un timer.

#### Paramètres
- `Timer` : Le timer utilisé pour générer le signal PWM (ex. `TIM1`, `TIM2`, `TIM3`, `TIM4`).
- `valeur` : Le rapport cyclique à définir, exprimé en pourcentage (0 à 100%).
- `channel` : Le canal PWM (1 à 4).

#### Fonctionnement
- Calcule la valeur du registre `CCR` en fonction du rapport cyclique demandé (`valeur`).
- Met à jour le registre `CCR` correspondant au canal spécifié, ajustant ainsi la largeur de l'impulsion PWM.

### 5. Interruptions du Timer

Les interruptions suivantes sont disponibles pour les timers :

- `TIM2_IRQHandler` : Gère les interruptions pour `TIM2`.
- `TIM3_IRQHandler` : Gère les interruptions pour `TIM3`.
- `TIM4_IRQHandler` : Gère les interruptions pour `TIM4`.
- `TIM1_UP_IRQHandler` : Gère les interruptions pour `TIM1` (au niveau du "update").

#### Fonctionnement des Handlers
- Lorsqu'une interruption est déclenchée (par exemple, un débordement du timer), le flag `UIF` dans le registre `SR` est effacé.
- Si une fonction d'interruption (`IT_function`) est définie, elle est appelée dans le handler d'interruption pour traiter l'événement.


### Servo

- Contrôle les servomoteurs pour ajuster la direction des voiles.
- Utilise des signaux PWM pour positionner les servos à des angles spécifiques.
- **Fonctions principales :**
  - `MyServo_init` : Initialise le contrôle du servomoteur.
  - `MyServo_set` : Définit un angle précis pour le servomoteur.

### USART

Ce driver permet d'initialiser et de gérer les communications série via les périphériques USART du STM32. Il supporte l'envoi et la réception de données via les interfaces USART1, USART2 et USART3. L'implémentation inclut la configuration des broches correspondantes pour les signaux TX (Transmission) et RX (Réception), ainsi que la gestion des interruptions pour la réception des données.

## Fonctions Principales

### 1. `MyUSART_Init(USART_TypeDef *USART, int BaudRate)`
#### Description
Cette fonction initialise le périphérique USART pour la communication série avec un baud rate spécifié. Elle configure également les broches nécessaires pour la communication série, ainsi que les interruptions de réception pour chaque USART.

#### Paramètres
- `USART` : L'instance de l'USART à configurer. Peut être `USART1`, `USART2` ou `USART3`.
- `BaudRate` : Le taux de transmission des données en bauds (bps). Exemple : `9600`, `115200`.

#### Fonctionnement
1. **Activation de l'horloge du périphérique USART** : La fonction active l'horloge pour l'USART choisi (via `RCC->APB1ENR` ou `RCC->APB2ENR` selon le périphérique).
2. **Configuration des broches TX et RX** : 
   - `USART1` utilise `PA9` pour TX et `PA10` pour RX.
   - `USART2` utilise `PA2` pour TX et `PA3` pour RX.
   - `USART3` utilise `PB10` pour TX et `PA11` pour RX.
   - Les broches sont configurées en mode "Alternative Push-Pull" pour TX et "Floating Input" pour RX.
3. **Calcul du BaudRate** : Le `BRR` (Baud Rate Register) est configuré en fonction du fréquence de l'horloge (`Fclk`) et du `BaudRate` spécifié.
4. **Configuration des interruptions** : La fonction configure les interruptions pour la réception de données (RXNE - "Received Data Ready") via les NVIC (vecteurs d'interruption).
5. **Activation du périphérique USART** : L'USART est activé avec les bits `UE`, `TE`, `RE`, et `RXNEIE` pour permettre la transmission, la réception et l'interruption lors de la réception de données.

### 2. `MyUSART_Send(USART_TypeDef *USART, char *message)`
#### Description
Cette fonction permet d'envoyer un message via l'USART spécifié. Le message est transmis caractère par caractère jusqu'à ce que tous les caractères soient envoyés.

#### Paramètres
- `USART` : L'instance de l'USART à utiliser pour l'envoi du message. Peut être `USART1`, `USART2`, ou `USART3`.
- `message` : Le pointeur vers une chaîne de caractères à envoyer via l'USART.

#### Fonctionnement
- La fonction lit chaque caractère de la chaîne de message et l'envoie via le registre `DR` (Data Register) de l'USART.
- La transmission continue jusqu'à ce que tous les caractères soient envoyés.
- La fonction attend que le bit `TXE` dans le registre `SR` soit activé, ce qui indique que le registre de transmission est prêt à accepter de nouvelles données.

### 3. Interruptions USART

#### Description
Les fonctions d'interruption permettent de gérer la réception des données via les périphériques USART. Lorsqu'un caractère est reçu, l'interruption est déclenchée et le caractère est lu depuis le registre `DR` de l'USART.

##### Gestionnaire d'Interruption `USART1_IRQHandler`
- Cette fonction est appelée lorsque des données sont reçues sur `USART1`.
- Les données reçues sont lues et stockées dans la variable `USART1data`.
- Le caractère reçu est renvoyé à l'émetteur via la fonction `MyUSART_Send`, ce qui permet de tester la réception en renvoyant ce qui est reçu.

##### Gestionnaire d'Interruption `USART2_IRQHandler`
- Cette fonction est appelée lorsque des données sont reçues sur `USART2`.
- Le caractère reçu est stocké dans la variable `USART2data`.
- Le caractère est renvoyé via `MyUSART_Send`.

##### Gestionnaire d'Interruption `USART3_IRQHandler`
- Cette fonction est appelée lorsque des données sont reçues sur `USART3`.
- Le caractère reçu est stocké dans la variable `USART3data`.
- Le caractère est renvoyé via `MyUSART_Send`.

## Services

### Gestion des Voiles

- Ajuste dynamiquement l'orientation des voiles en fonction de la direction du vent et du risque de chavirage.
- **Fonctions principales :**
  - `GestionVoile_Init` : Configure les ressources nécessaires au contrôle des voiles.
  - `GestionVoile_Direction` : Calcule l’angle optimal à partir des données d’encodeur et de chavirage.

### Gestion de la Batterie

- Mesure l’état de la batterie via l’ADC.
- **Fonctions principales :**
  - `GestionBatterie_Init` : Configure l'ADC pour surveiller la tension de la batterie.
  - `GestionBatterie_Read` : Récupère les données de tension à transmet via USART.

### Gestion de la Transmission

- Utilise le module USART pour communiquer avec la télécommande.
- **Fonctions principales :**
  - `GestionTransmission_Init` : Initialise la communication série.
  - `GestionTransmission_Trans` : Envoie des informations clés, comme l’angle des voiles et la tension de la batterie.

### Module Anti-Chavirage

- Détecte une situation de chavirage grâce à un capteur d'inclinaison.
- **Fonctions principales :**
  - `ModuleChavirer_Init` : Initialise les capteurs SPI.
  - `ModuleChavirer_Run` : Évalue les données des capteurs et détecte les risques de chavirage.

### Module Plateau

- Gère la rotation du plateau pour compenser les mouvements du voilier en navigation.
- **Fonctions principales :**
  - `ModulePlateau_Init` : Initilaise le modul de control du plateau.
  - `ModulePlateau_Tourner` : Ajuste le moteur dans la direction et la vitesse requise, envoyé via la télécomande.

---

## Utilisation

1. **Initialisation**

   - Appeler `App_Init` pour configurer tous les modules.

2. **Exécution en boucle**

   - Appeler `App_Run` dans la boucle principale pour exécuter les fonctions périodiques.

3. **Transmission des données**

   - Les messages sont automatiquement envoyés toutes les 3 secondes.

