# 스마트 쓰레기통 - 초음파 센서와 MQTT 연동 및 Node-RED 대시보드

## 프로젝트 개요
스마트 쓰레기통은 초음파 센서를 활용하여 쓰레기통의 채움 상태를 측정하고, MQTT 프로토콜을 통해 데이터를 전송하며, Node-RED 대시보드를 통해 실시간 상태를 시각화하는 IoT 시스템입니다. 이 프로젝트는 자동화된 쓰레기 관리와 원격 모니터링을 통해 효율성을 높이고 사용자의 편의성을 극대화합니다.

---

## 주요 기능
- **쓰레기통 상태 감지**: 초음파 센서를 사용해 쓰레기통 내부의 남은 공간을 측정하고 채움 상태를 %로 계산.
- **쓰레기 압축 기능**: 특정 채움 상태에 도달하면 모터를 통해 쓰레기를 자동으로 압축.
- **실시간 데이터 전송**: ESP8266을 통해 MQTT 브로커로 데이터를 전송.
- **Node-RED 대시보드 시각화**: 실시간 채움 상태 및 데이터를 대시보드에서 시각적으로 확인.

---

## Node-RED 대시보드 구성

### 대시보드 예시
1. **실시간 게이지**  
   쓰레기통의 채움 상태를 %로 표시.  
   ![게이지 예시](https://github.com/qlanfr/capstone/blob/main/node.JPG)

2. **데이터 로그**  
   MQTT로 수신된 데이터를 시간별로 기록.  
   ![MQTT 데이터 로그 예시](https://github.com/qlanfr/capstone/blob/main/mqtt.JPG)

---

## 설치 및 실행 방법

### 1. Arduino 및 ESP8266 설정
1. Arduino IDE에서 제공된 코드를 업로드.
2. 초음파 센서, 모터 드라이버, 충격 센서를 Arduino 핀에 연결.
3. ESP8266 모듈을 Arduino 직렬 통신 핀(D1, D2)으로 연결.

### 2. Node-RED 설정
1. **Node-RED 설치**:
   npm install -g node-red
대시보드 플러그인 설치:
   npm install node-red-dashboard


### MQTT 노드 설정:
   MQTT 브로커 정보를 입력하여 데이터를 수신하는 mqtt in 노드와 연결.

### 게이지 및 텍스트 노드 설정:
   mqtt in 노드에서 수신한 데이터를 게이지 및 텍스트 노드로 연결.
### Node-RED 실행:
   node-red
### 웹 대시보드 접속
http://<Node-RED-서버-IP>:1880/ui

------
### 주요 변수 및 핀 설정
## Arduino 핀 설정


   핀 이름	          용도

   
trigPin1 (22)	      초음파 센서 1 트리거 핀


echoPin1 (23)	      초음파 센서 1 에코 핀


trigPin2 (13)	      초음파 센서 2 트리거 핀


echoPin2 (12)	      초음파 센서 2 에코 핀


extraMotorPin1 (10)	추가 모터 드라이버 IN1 핀


extraMotorPin2 (11)	추가 모터 드라이버 IN2 핀


motorPin1 (6)	      모터 드라이버 IN1 핀


motorPin2 (7)	      모터 드라이버 IN2 핀


shockSensorPin (A0)	충격 감지 센서 핀

----------

### 테스트 결과


1. MQTT 연결 상태


MQTT 브로커와 ESP8266 모듈 간 데이터 전송이 성공적으로 이루어짐.


수신 주제(topic): 202008059/adcValue


예시 수신 데이터: 30 (%)


2. Node-RED 대시보드 상태

   
게이지에서 쓰레기통의 채움 상태가 **30%**로 표시.


데이터 로그에 수신된 데이터가 시간별로 기록.


3. 시스템 시연


초음파 센서를 통해 쓰레기 높이를 측정.


측정 데이터를 MQTT를 통해 Node-RED 대시보드로 전송.


채움 상태가 임계값을 초과하면 모터로 쓰레기를 자동으로 압축.

-------------

 파일 구조

/ 프로젝트 폴더
├── ArduinoCode.ino        # Arduino 메인 코드
├── ESP8266Code.ino        # ESP8266 메인 코드
├── Node-RED-Flow.json     # Node-RED 대시보드 구성 JSON
└── README.md              # 프로젝트 설명 파일

------------

### 결과
MQTT와 Node-RED 연동 성공: 실시간 쓰레기통 상태 모니터링 구현.
대시보드 시각화: 사용자 친화적인 인터페이스로 채움 상태 확인 및 관리 가능.
쓰레기 관리 자동화: 자동 압축 기능을 통해 쓰레기통의 공간 효율 극대화.
