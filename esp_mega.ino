#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>

#define SSID "Hi"
#define PASSWORD "1234567890"
#define MQTT_SERVER "1.1.1.1"
#define MSG_BUFFER_SIZE 50

WiFiClient espClient;
PubSubClient client(espClient);
SoftwareSerial mySerial(D1, D2); // RX, TX

char msg[MSG_BUFFER_SIZE];

void setup_wifi() {
  delay(10);
  Serial.begin(115200);
  mySerial.begin(115200); 
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("MQTT connection");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe("202008059/adcValue");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retry");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_SERVER, 1883);
  client.setCallback(callback);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("not wifi");
    setup_wifi();
  } else if (!client.connected()) {
    Serial.println("not mqtt");
    reconnect();
  } else {
    client.loop();

    if (mySerial.available()) {
      String message = mySerial.readStringUntil('\n');
      message.trim(); // 메시지에서 공백 제거
      message.toCharArray(msg, MSG_BUFFER_SIZE);
      Serial.print("Arduino: ");
      Serial.println(msg);

     
      client.publish("202008059/adcValue", msg);
      Serial.print("MQTT: ");
      Serial.println(msg);
    }
  }

  delay(1000); 
}
