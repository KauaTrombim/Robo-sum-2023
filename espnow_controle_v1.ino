#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0xB0, 0xB2, 0x1C, 0xA7, 0xB4, 0x38};

int buttonUpValue;
int buttonDownValue;
String success;

typedef struct struct_message {
    int textData;
    int numberData;
} struct_message;

struct_message datas;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
  Serial.println(">>>>>");
}

void setup() {
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); 

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
   
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  pinMode(2, INPUT);
  pinMode(4, INPUT);
}


void loop() {
  buttonUpValue = digitalRead(2);
  buttonDownValue = digitalRead(4);
  datas.textData = buttonUpValue;
  datas.numberData = buttonDownValue;
  
  Serial.println();
  Serial.print(">>>>> ");
  Serial.println("Send data");
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &datas, sizeof(datas));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  
  delay(300);
}
