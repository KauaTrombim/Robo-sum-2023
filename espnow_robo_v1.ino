#include <esp_now.h>
#include <WiFi.h>

int upData;
int downData;

typedef struct struct_message {
    int textData;
    int numberData;
} struct_message;

struct_message datas;


void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&datas, incomingData, sizeof(datas));
  Serial.println();
  Serial.println("<<<<< Receive Data:");
  Serial.print("Bytes received: ");
  Serial.println(len);
  upData = datas.textData;
  downData = datas.numberData;
  Serial.println("Receive Data: ");
  Serial.println(upData);
  Serial.println(downData);
  Serial.println("<<<<<");
}


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); 

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
}


void loop() {
  if(upData == 'F'){
    digitalWrite(2, HIGH);
  }
  else {
    digitalWrite(2, LOW);
  }
}
