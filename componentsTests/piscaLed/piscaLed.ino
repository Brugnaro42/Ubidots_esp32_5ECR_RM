int ONBOARD_LED = 2;


void setup() {
  pinMode(ONBOARD_LED,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  digitalWrite(ONBOARD_LED,HIGH);
  delay(100);
  digitalWrite(ONBOARD_LED,LOW);
}
