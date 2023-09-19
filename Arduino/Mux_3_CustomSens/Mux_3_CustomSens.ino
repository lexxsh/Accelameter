#include <Capacitor.h>

const int mux1SelectPins[] = {2, 3, 4, 5};
const int mux1OutPin = A0;
const int mux2SelectPins[] = {8, 9, 10, 11};
const int mux2OutPin = A2;
Capacitor capSensorMux1(mux1OutPin, mux2OutPin);
const int delayValue = 10;
void sendCap(float capacitance,int channel){
  Serial.print("CC:");
  Serial.print(channel);
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
  for (int Channel = 0; Channel < 4; Channel++) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(mux1SelectPins[i], bitRead(Channel, i));
      digitalWrite(mux2SelectPins[i], bitRead(Channel, i));
    }
    float capacitanceMux1 = capSensorMux1.Measure();
    int index = Channel;

    sendCap(capacitanceMux1,Channel);
    Serial.print("Channel ");
    Serial.print(Channel);
    Serial.print(": MeasuredCapacitance = ");
    Serial.print(capacitanceMux1, 2);
    Serial.println(" pF");
    delay(1000);
  }
  unsigned long endTime = millis();
  float frequency = 1000.0/(endTime - startTime);
  Serial.print("| Frequency = ");
    Serial.print(frequency);
    Serial.println(" Hz");
}
