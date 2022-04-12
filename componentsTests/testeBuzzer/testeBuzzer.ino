int buzzer_pin      = 15;
int channel         = 0;
int frequence       = 2000;
int resolution      = 10;
unsigned long timer = millis();

TaskHandle_t dobitaobyte;
eTaskState statusOf;

void justAmessage(void *pvParameters){
  while(true){
      Serial.println("cuco...");
      delay(1000);
  }
}

void sirene(void *pvParameters){
    float sinVal;
    int   toneVal;
    for (byte t = 0; t<10;t++){
        for (byte x=0;x<180;x++){
            //converte graus em radianos
            sinVal = (sin(x*(3.1412/180)));
            //agora gera uma frequencia
            toneVal = 2000+(int(sinVal*100));
            //toca o valor no buzzer
            ledcWriteTone(channel,toneVal);
            //Serial.print("*");
            //atraso de 2ms e gera novo tom
            delay(4);
        }
    }
    ledcWriteTone(channel, 0);
    vTaskDelete(NULL);
}

void setup() {
  ledcSetup(channel, frequence, resolution);
  ledcAttachPin(buzzer_pin, channel);
  timer = millis();
  Serial.begin(115200);
  xTaskCreatePinnedToCore(sirene,     "sirene", 10000, NULL, 1, &dobitaobyte,0);
  xTaskCreatePinnedToCore(justAmessage,"cuco",  10000, NULL, 1, NULL,        0);
}

void loop() {
  if (millis()-timer >10000){
    statusOf = eTaskGetState(dobitaobyte);
    if (statusOf == eReady){
      timer = millis();
      xTaskCreatePinnedToCore(justAmessage,"cuco", 10000, NULL, 1, NULL,0);
    }
    
  }
  Serial.println("executando livremente...");
  delay(1000);
}
