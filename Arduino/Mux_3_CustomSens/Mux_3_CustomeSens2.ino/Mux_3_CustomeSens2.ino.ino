#include <Capacitor.h>

const int mux1SelectPins[] = {2, 3, 4, 5};
const int mux1OutPin = A0;
const int mux2SelectPins[] = {8, 9, 10, 11};
const int mux2OutPin = A2;
Capacitor capSensorMux1(mux1OutPin, mux2OutPin);
void sendCap(float capacitance,int Mux1Channel, int Mux2Channel){
  Serial.print("CC:");
  Serial.print(Mux1Channel);
  Serial.print(",");
  Serial.print(Mux2Channel);
  Serial.print(",");
  Serial.println(capacitance);
}
void setup() {
  Serial.begin(115200);
  
  for (int i = 0; i < 4; i++) {
    pinMode(mux1SelectPins[i], OUTPUT);
    pinMode(mux2SelectPins[i], OUTPUT);
  }
  capSensorMux1.ShowDebug(true);
}

void loop() {
  unsigned long startTime = millis();
  for (int Mux1Channel = 0; Mux1Channel < 4; Mux1Channel++) {
    for (int Mux2Channel = 0; Mux2Channel < 4; Mux2Channel++) {
      for (int i = 0; i < 4; i++) {
        digitalWrite(mux1SelectPins[i], bitRead(Mux1Channel, i));
        digitalWrite(mux2SelectPins[i], bitRead(Mux2Channel, i));
      }
      float capacitanceMux1 = capSensorMux1.Measure();
      sendCap(capacitanceMux1, Mux1Channel , Mux2Channel);
      Serial.print("Mux1[");
      Serial.print(Mux1Channel);
      Serial.print("] Mux2[");
      Serial.print(Mux2Channel);
      Serial.print("]: Measured Capacitance = ");
      Serial.print(capacitanceMux1, 2);
      Serial.println(" pF");
      delay(100);
    }
  }
  unsigned long endTime = millis();
  float frequency = 1000.0/(endTime - startTime);
  Serial.print("| Frequency = ");
    Serial.print(frequency);
    Serial.println(" Hz");
}
