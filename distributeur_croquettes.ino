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
#define PIN_FIN_COURSE_ARRIERE  25
#define PIN_FIN_COURSE_AVANT    23
#define PIN_COMMANDE_RELAIS     6
#define PIN_LED_ARDUINO         13
#define PIN_LED_PRESENCE        9
#define PIN_TRIGGER             8
#define PIN_ECHO                7
#define PIN_BUZZER              10

// Temporisation (en ms)
#define TEMPS_IMPULSION_MOTEUR  10000

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
  pinMode(PIN_COMMANDE_RELAIS, OUTPUT);   // Etat bas => le relais se ferme
  pinMode(PIN_LED_ARDUINO, OUTPUT);       // LED de la carte Arduino, utile pour le debug
  pinMode(PIN_LED_PRESENCE, OUTPUT);      // LED indiquant qu'une présence a été détectée
  pinMode(PIN_TRIGGER, OUTPUT);          // sortie pour piloter le détecteur de proximité
  pinMode(PIN_ECHO, INPUT);               // Entrée pour lire la réponse du capteur
  pinMode(PIN_BUZZER, OUTPUT); 

  // Initialisation de la ligne série pour le debug
  Serial.begin(9600);

  // Couper le moteur (après configruation la sortie est à LOW, ce qui ferme le relais)
  digitalWrite(PIN_COMMANDE_RELAIS, HIGH);
} 

// Fonction d'avance du moteur
void avance_moteur()
{
  digitalWrite(PIN_COMMANDE_RELAIS, LOW);
  delay(TEMPS_IMPULSION_MOTEUR);
  digitalWrite(PIN_COMMANDE_RELAIS, HIGH);
}

// Fonction de détection de présence
// Retourne TRUE si une présence est détectée
// Retourne FALSE si aucun présence n'est détectée
boolean detecte_presence()
{
  int duree_echo;
  int distance;
  
  digitalWrite (PIN_TRIGGER,HIGH);  // Demander au SR04 d'effectuer une mesure de distance
  delayMicroseconds(10); // attendre 10 microsecondes 
  digitalWrite (PIN_TRIGGER, LOW);  // Faire baisser le signal
  
  // Lire la réponse du SR04
  duree_echo = pulseIn(PIN_ECHO, HIGH);
  distance = duree_echo / 58;
  
  // Convertir la distance en centimètres
  distance = duree_echo / 58;
  Serial.print("Distance (cm) : "); 
  Serial.println(distance); 

  if (distance > 10) 
    return false;
  else
    return true;
    
}

// Test du distributeur
void test_distributeur()
{
  // Test du buzzer
  digitalWrite(PIN_BUZZER, HIGH);
  delay(500);
  digitalWrite(PIN_BUZZER, LOW);

  delay(1000);

  // Test du moteur
  avance_moteur();
}

// Boucle principale de l'Arduino
void loop()
{
  int a, b;
  boolean presence_chat;
  boolean anomalie;

  // Test
  //for (;;)
  //{
  //  test_distributeur();
  //  delay(5000);
  //}

  anomalie = false;
  digitalWrite(PIN_LED_ARDUINO, LOW);

  a = digitalRead(PIN_FIN_COURSE_ARRIERE);
  if (a == HIGH)
  {
    digitalWrite(PIN_LED_ARDUINO, HIGH);
    digitalWrite(PIN_BUZZER, HIGH);
    delay(500);
    digitalWrite(PIN_BUZZER, LOW); 
    anomalie = true;
  }
  
  b = digitalRead(PIN_FIN_COURSE_AVANT);
  if (b == HIGH)
  {
    digitalWrite(PIN_LED_ARDUINO, HIGH);
    digitalWrite(PIN_BUZZER, HIGH);
    delay(500);
    digitalWrite(PIN_BUZZER, LOW);
    anomalie = true;
  }

  presence_chat = detecte_presence();
  if (presence_chat == true && anomalie !=true)
  {
    Serial.println("Chat !!!"); 
    digitalWrite(PIN_LED_PRESENCE, HIGH);
    digitalWrite(PIN_BUZZER, HIGH);
    delay(1000);
    digitalWrite(PIN_LED_PRESENCE, LOW);
    digitalWrite(PIN_BUZZER, LOW);

    // Distribuer une croquette
    avance_moteur();
  }
  
  delay(1000);

}
