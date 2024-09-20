#include <math.h> 

#define MSG_BUFFER_SIZE 50

const int trigPin1 = 22;    // 1번 초음파 센서 트리거 핀
const int echoPin1 = 23;    // 1번 초음파 센서 에코 핀
const int trigPin2 = 13;    // 2번 초음파 센서 트리거 핀
const int echoPin2 = 12;    // 2번 초음파 센서 에코 핀

const int extraMotorPin1 = 10;  // 추가 모터 드라이버 IN1 핀
const int extraMotorPin2 = 11;  // 추가 모터 드라이버 IN2 핀

const int motorPin1 = 6;   // 모터 드라이버 IN1 핀
const int motorPin2 = 7;   // 모터 드라이버 IN2 핀
const int shockSensorPin = A0; // 충격 감지 센서 핀

unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];
float fillPercentage = 0.0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200); 

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  pinMode(extraMotorPin1, OUTPUT);
  pinMode(extraMotorPin2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Setup");
}

void loop() {
  

  float distance1 = getDistance(trigPin1, echoPin1);

  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.println(" cm");

  if (distance1 < 10.0) {
    Serial.println("compression");
    digitalWrite(extraMotorPin1, HIGH);
    digitalWrite(extraMotorPin2, LOW);
    delay(1000);
    digitalWrite(extraMotorPin1, LOW);
    digitalWrite(extraMotorPin2, HIGH);
    delay(1000);
    digitalWrite(extraMotorPin1, LOW);
    digitalWrite(extraMotorPin2, LOW);

    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    delay(3000);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);

    float sum = 0;
    for (int i = 0; i < 4; i++) {
      digitalWrite(trigPin2, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin2, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin2, LOW);
      long duration2 = pulseIn(echoPin2, HIGH);
      sum += (duration2 / 2.0) * 0.0343;
    }
    float distance2 = sum / 4;

    Serial.print("Distance 2: ");
    Serial.print(distance2);
    Serial.println(" cm");

    float fillHeight = 100.0 - distance2;
    fillPercentage = (fillHeight / 80.0) * 100.0;
    fillPercentage = fmax(0, fmin(100, fillPercentage));
    Serial.print("Fill Percentage: ");
    Serial.print(fillPercentage);
    Serial.println(" %");

    unsigned long now = millis();
    if (now - lastMsg > 2000) {
      lastMsg = now;
      dtostrf(fillPercentage, 6, 2, msg); 
      Serial.print("Send msg: ");
      Serial.println(msg);
      Serial1.print(msg); 
      Serial1.print("\n"); 
    }

    if (Serial1.available()) {
      String response = Serial1.readStringUntil('\n');
      Serial.println(response);
    }

    Serial.println("up");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    delay(1000);

    while (analogRead(shockSensorPin) > 300) {
    }
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);

  }

  delay(1000); 

}

float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration / 2.0) * 0.0343;
  return distance;
}
