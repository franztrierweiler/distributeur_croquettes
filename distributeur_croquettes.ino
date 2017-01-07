// Projet de distributeur de croquettes à base d'Arduino et d'éléments Fischertechnik.
// Fichier: distributeur_croquettes.ino
// Conception et codage démarrés en décembre 2016 suite à l'achat d'une carte Funduino.
// https://github.com/franztrierweiler/distributeur_croquettes
//
// Créé et maintenu par:
// - Sixtine Trierweiler
// - Franz Trierweiler
// 
// Code source sous licence GPL

// Affectation des broches de l'ATMEGA 2560
// Définir des étiquettes permet de changer plus facilement les broches dans le programme
#define PIN_FIN_COURSE_ARRIERE  23
#define PIN_FIN_COURSE_AVANT    25
#define PIN_LED_ARDUINO         13

//
// Variables globales en mémoire RAM
//

// Indique si le distributeur est actif ou inactif
// Valeur modifiée par appui sur un bouton
boolean distributeur_actif = true;

// Initialisation de l'Arduino
// Cette fonction est appellée une seule fois au démarrage de l'Arduino
void setup()
{
  pinMode(PIN_FIN_COURSE_ARRIERE, INPUT); // Pull-down => 0 si actionneur ouvert
  pinMode(PIN_FIN_COURSE_AVANT, INPUT);   // Pull-down => 0 si actionneur ouvert
  pinMode(PIN_LED_ARDUINO, OUTPUT);       // LED de la carte Arduino, utile pour le debug
}

void loop()
{
  // Code de démo pour bon chargement
  digitalWrite(PIN_LED_ARDUINO, HIGH);
  delay(200);
  digitalWrite(PIN_LED_ARDUINO, LOW);
  delay(200);
}
