#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adresse LCD et dimensions (16x2)

char numero[4] = {'0', '0', '0', '0'};
const char code[4] = {'2', '0', 'A', '3'};
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; // Connectez les broches ROW du keypad aux broches 9, 8, 7, et 6
byte colPins[COLS] = {5, 4, 3, 2}; // Connectez les broches COL du keypad aux broches 5, 4, 3, et 2

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const char *menu[] = {
    "Menu:",
    "1. Code",
    "2. Empreinte",
    "3. Admin"};

void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
    affichage(menu, 4);
    char choix = recupererNumero();
    afficherNumero(choix, 0);

    switch (choix)
    {
    case '1':
        initialisationCode();
        break;

    case '2':
        // Gérer la saisie de l'empreinte
        break;

    case '3':
        // Gérer l'administration
        break;
    }
}

void loop()
{
    // La boucle loop() est vide car vous traitez les actions dans setup() et les fonctions appelées.
}

void affichage(const char *lignes[], int nombreDeLignes)
{
    const int displayDelay = 750; // Délai d'affichage entre les lignes (en millisecondes)
    lcd.clear();

    for (int i = 0; i < nombreDeLignes; i++)
    {
        lcd.setCursor(0, 0);
        lcd.print(lignes[i]);
        delay(displayDelay);
    }
}

#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialisation de l'écran LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adresse LCD et dimensions (16x2)

// Définition du clavier
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Broches du clavier
byte rowPins[ROWS] = {9, 8, 7, 6}; // Connectez les broches ROW du keypad aux broches 9, 8, 7, et 6
byte colPins[COLS] = {5, 4, 3, 2}; // Connectez les broches COL du keypad aux broches 5, 4, 3, et 2

// Initialisation du clavier
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Tableau pour stocker le code de l'utilisateur
char numero[4] = {'0', '0', '0', '0'};

// Code d'accès autorisé
const char code[4] = {'2', '0', 'A', '3'};

// Fonction pour afficher le menu et récupérer le choix de l'utilisateur
char afficherMenu()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();

    const char *menu[] = {
        "Menu:",
        "1. Code",
        "2. Empreinte",
        "3. Admin"};

    int nombreDeLignes = sizeof(menu) / sizeof(menu[0]);

    while (true)
    {
        for (int i = 0; i < nombreDeLignes; i++)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(menu[i]);

            char key = recupererNumero();
            if (key != '\0')
            {
                return key;
            }

            delay(500); // Délai d'affichage entre les lignes (en millisecondes)
        }
    }
}

// Fonction pour récupérer un numéro du clavier
char recupererNumero()
{
    char key = keypad.getKey();
    return key;
}

// Fonction pour saisir un caractère dans le tableau du code
void saisirCaractere(char key, int &i)
{
    if (key != '\0')
    {
        if (key == '#')
        {
            effacerEcran();
            i = 0;
        }
        else
        {
            numero[i] = key;
            afficherNumero(numero, i);
            i++;
        }
    }
}

// Fonction pour afficher le caractère saisi à l'écran
void afficherNumero(char numero[4], int i)
{
    lcd.setCursor(i, 1); // Seconde ligne de l'écran LCD, colonne i
    lcd.print(numero[i]);
}

// Fonction pour effacer l'écran et réinitialiser le tableau du code
void effacerEcran()
{
    lcd.clear();
    for (int i = 0; i < 4; i++)
    {
        numero[i] = '0';
    }
}

// Fonction pour valider la saisie du code
bool validerSaisie(char numero[4])
{
    for (int i = 0; i < 4; i++)
    {
        if (code[i] != numero[i])
        {
            return true;
        }
    }
    return false;
}

// Fonction pour l'initialisation du code
void initialisationCode()
{
    lcd.clear();
    int i = 0;

    while (i <= 4)
    {
        lcd.setCursor(0, 0);
        lcd.print("Saisir le code:");
        char key = recupererNumero();
        saisirCaractere(key, i);

        if (i == 4)
        {
            int valid = validerSaisie(numero);
            lcd.setCursor(0, 1);

            if (valid == 0)
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Code correct");
                lcd.setCursor(0, 1);
                lcd.print("Porte ouverte");
                delay(5000); // Affichage du message pendant 5 secondes
                break;
            }
            else
            {
                lcd.print("Erreur");
                delay(2000); // Attendre 2 secondes pour que l'utilisateur voie le message d'erreur
                effacerEcran();
                i = 0;
            }
        }
    }
}

void setup()
{
    char choix = afficherMenu();
    while (true)
    {
        switch (choix)
        {
        case '1':
            lcd.clear();
            initialisationCode();
            lcd.clear();
            choix = afficherMenu();
            break;

        case '2':
            lcd.clear();
            lcd.print("EMPREINTE");
            choix = afficherMenu();
            break;

        case '3':
            lcd.clear();
            lcd.print("ADMIN");
            choix = afficherMenu();
            break;
        }
    }
}

void loop()
{
    // La boucle loop() est vide car les actions sont traitées dans setup() et les fonctions appelées.
}

