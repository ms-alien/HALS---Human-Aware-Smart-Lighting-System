#include <Arduino.h>

const int sensor_pin = 8;
const int led_pin = 7;

bool motionDetected = false;

void setup()
{
    pinMode(sensor_pin, INPUT);
    pinMode(led_pin, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    int sensor_value = digitalRead(sensor_pin);

    if (sensor_value == HIGH && !motionDetected)
    {
        motionDetected = true;
        Serial.println("Move detected!");

        digitalWrite(led_pin, HIGH);
        delay(2000);
        digitalWrite(led_pin, LOW);
    }

    if (sensor_value == LOW)
    {
        motionDetected = false; // prêt pour le prochain mouvement
    }
}
