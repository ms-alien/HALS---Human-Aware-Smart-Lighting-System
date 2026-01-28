#include <Arduino.h>

// --- Pins ---
const int sr501_pin = 8;      // PIR HC-SR501
const int LDR_PIN = A0;       // LDR
const int led_pin = 7;        // LED témoin
const int relay_pin = 5;      // Relais pour lampe

// --- LDR filtre ---
const float alpha = 0.5;      // Filtre exponentiel
float ldrFiltered = 0.0;
const int LDR_THRESHOLD = 400; // Ajuste selon luminosité du couloir

// --- Détection mouvement ---
bool motionDetected = false;
unsigned long ledTimer = 0;
const unsigned long ledOnTime = 20000; // LED/lampe reste allumée 1 minute après dernier mouvement

void setup() {
  pinMode(sr501_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(relay_pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // --- Lecture capteurs ---
  int sr501_value = digitalRead(sr501_pin);
  int ldrValue = analogRead(LDR_PIN);
  
  // Filtre pour éviter les variations brusques
  ldrFiltered = alpha * ldrValue + (1 - alpha) * ldrFiltered;
  bool isDark = (ldrFiltered < LDR_THRESHOLD);

  Serial.print("LDR: ");
  Serial.print(ldrFiltered);
  Serial.print(" | PIR: ");
  Serial.println(sr501_value);

  // --- Détection mouvement ---
  if (sr501_value == HIGH) {
    motionDetected = true;
    ledTimer = millis(); // réinitialise le timer
    Serial.println("Mouvement détecté !");
  }

  // --- Gestion LED témoin et relais lampe ---
  if (motionDetected && isDark) {
    digitalWrite(led_pin, HIGH); // LED allumée
    digitalWrite(relay_pin, HIGH); // Lampe allumée
  } else if (!motionDetected) {
    digitalWrite(led_pin, LOW); // LED éteinte
    digitalWrite(relay_pin, LOW);  // Lampe éteinte
  }

  // --- Extinction automatique après temps défini ---
  if (motionDetected && (millis() - ledTimer > ledOnTime)) {
    motionDetected = false;
    Serial.println("LED et lampe éteintes après temporisation.");
  }

  delay(100); // lecture toutes les 0,1s
}
