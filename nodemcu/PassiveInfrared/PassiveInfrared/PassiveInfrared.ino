
#define pinPassiveInfrared D4
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pinPassiveInfrared,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int digitalPassiveInfrared = digitalRead(pinPassiveInfrared);
  Serial.println(digitalPassiveInfrared);
}
