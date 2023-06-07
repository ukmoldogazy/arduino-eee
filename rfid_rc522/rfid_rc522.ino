#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 6
Servo myservo;
int pos = 0;
int In1 = 7;
int In2 = 8;
int ENA = 5;
int SPEED = 210;
const int buttonPin = 4;
int buttonState = 0;
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);         // Инициализация порта серийной связи
  SPI.begin();                // Инициализация шины SPI
  rfid.PCD_Init();            // Инициализация модуля RFID
  myservo.attach(SERVO_PIN);  // Подключение серво мотора
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  // Попытка считывания UID карточки
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    Serial.print("Карточка с UID: ");
    for (byte i = 0; i < 4; i++) {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
      Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();

    // Проверка совпадения UID карточки
    if (rfid.uid.uidByte[0] == 0xB3 && rfid.uid.uidByte[1] == 0x0C && rfid.uid.uidByte[2] == 0x4B && rfid.uid.uidByte[3] == 0x4D) {
      Serial.println("Карточка совпадает!");
      // for (pos = 0; pos <= 90; pos += 1)
      myservo.write(0);
      delay(1000);
      digitalWrite(In1, HIGH);
      digitalWrite(In2, LOW);
      analogWrite(ENA, SPEED);
      delay(1000);
      digitalWrite(In1, LOW);
      digitalWrite(In2, LOW);
      delay(5000);
      digitalWrite(In2, HIGH);
      digitalWrite(In1, LOW);

    } else if (rfid.uid.uidByte[0] == 0x63 && rfid.uid.uidByte[1] == 0x0B && rfid.uid.uidByte[2] == 0x3B && rfid.uid.uidByte[3] == 0xC5) {
      Serial.println("Карточка совпадает!");
      // for (pos = 0; pos <= 90; pos += 1)

      myservo.write(0);
      delay(1000);
      digitalWrite(In1, HIGH);
      digitalWrite(In2, LOW);
      analogWrite(ENA, SPEED);
      delay(1000);
      digitalWrite(In1, LOW);
      digitalWrite(In2, LOW);
      delay(5000);
      digitalWrite(In2, HIGH);
      digitalWrite(In1, LOW);
    }

    else if (rfid.uid.uidByte[0] == 0x92 && rfid.uid.uidByte[1] == 0x01 && rfid.uid.uidByte[2] == 0x10 && rfid.uid.uidByte[3] == 0x2D) {
      Serial.println("Карточка совпадает!");

      // for (pos = 0; pos <= 90; pos += 1)
      myservo.write(0);
      delay(1000);
      digitalWrite(In1, HIGH);
      digitalWrite(In2, LOW);
      analogWrite(ENA, SPEED);
      delay(1000);
      digitalWrite(In1, LOW);
      digitalWrite(In2, LOW);
      delay(5000);
      digitalWrite(In2, HIGH);
      digitalWrite(In1, LOW);

    }

    else if (rfid.uid.uidByte[0] == 0x89 && rfid.uid.uidByte[1] == 0xEA && rfid.uid.uidByte[2] == 0x03 && rfid.uid.uidByte[3] == 0xBA) {
      Serial.println("Карточка совпадает!");
      // for (pos = 0; pos <= 90; pos += 1)
      myservo.write(0);
      delay(1000);
      digitalWrite(In1, HIGH);
      digitalWrite(In2, LOW);
      analogWrite(ENA, SPEED);
      delay(1000);
      digitalWrite(In1, LOW);
      digitalWrite(In2, LOW);
      delay(5000);
      digitalWrite(In2, HIGH);
      digitalWrite(In1, LOW);
    }

    else {
      Serial.println("Карточка не совпадает!");
    }
    delay(1000);
    rfid.PICC_HaltA();       // Остановка чтения карты
    rfid.PCD_StopCrypto1();  // Остановка обмена данными с картой
  }
  if (buttonState == HIGH) {
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);  // tell servo to go to position in variable 'pos'
    delay(1000);
    myservo.write(180);
  }
}