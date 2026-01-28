#include <Arduino.h>

const int LDR_PIN = A0; // Pin connected to the LDR
const float alpha = 0.5;
float ldrFiltered = 0.0;
const int LED_PIN = 7;

void setup()
{
    Serial.begin(9600); // Initialize serial communication at 9600 bps
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    int ldrValue = analogRead(LDR_PIN); // Read the value from the LDR
    ldrFiltered = alpha * ldrValue + (1.0 - alpha) * ldrFiltered;

    if (ldrFiltered < 200)
    {
        digitalWrite(LED_PIN, HIGH); // Turn LED on
    }
    else
    {
        digitalWrite(LED_PIN, LOW); // Turn LED off
    }
    Serial.print("LDR Value: "); // Print label
    Serial.println(ldrFiltered); // Print the LDR value
    delay(100);                  // Wait for 0.1 second before the next reading
}