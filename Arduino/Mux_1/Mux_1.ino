#include <Capacitor.h>

const int muxSelectPins[] = {2, 3, 4, 5};

struct CapacitorMapping {
  int outPin;
  int inPin;
};

CapacitorMapping capacitorMappings[] = {
  {A0, A8}, // C0
  {A0, A9}, // C1
  {A0, A10}, // C2
  {A0, A11}  // C3
};

Capacitor capSensors[] = {
  Capacitor(capacitorMappings[0].outPin, capacitorMappings[0].inPin),
  Capacitor(capacitorMappings[1].outPin, capacitorMappings[1].inPin),
  Capacitor(capacitorMappings[2].outPin, capacitorMappings[2].inPin),
  Capacitor(capacitorMappings[3].outPin, capacitorMappings[3].inPin)
};

void setup() {
  Serial.begin(115200);
  
  for (int i = 0; i < 4; i++) {
    pinMode(muxSelectPins[i], OUTPUT);
    capSensors[i].ShowDebug(true);
  }
}

void loop() {
    
    for (int i = 0; i < 4; i++) {
      float capacitance = capSensors[i].Measure();
      Serial.print(" - Capacitor ");
      Serial.print(i);
      Serial.print(": Capacitance = ");
      Serial.print(capacitance, 2);
      Serial.println(" pF");
    delay(1000);
  }
}
