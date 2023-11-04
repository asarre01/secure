#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adresse LCD et dimensions (16x2)

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  const char* menu[] = {
    "Menu:",
    "1. Code",
    "2. Empreinte",
    "3. Admin"
  };
  
  char* message[] ={
    "Posez votre",
    "Empreinte sur",
    "le scanner"
  };
  affichage(message, 3);
}

void loop() {
  // La boucle loop() est vide car le texte est géré dans la fonction d'affichage.
}

void affichage(const char* lignes[], int nombreDeLignes) {
  const int displayDelay = 750;  // Délai d'affichage entre les lignes (en millisecondes)

  while (true) {
    for (int i = 0; i < nombreDeLignes; i++) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(lignes[i]);
      delay(displayDelay);
    }
  }
}
