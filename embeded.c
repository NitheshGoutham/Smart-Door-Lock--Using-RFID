#include <SPI.h> 
#include <MFRC522.h> 
#include <Servo.h> 
#define RST_PIN 9 
#define SS_PIN 10 
#define SERVO_PIN 3 
#define LED_ALLOW 7 
#define LED_NEUTRAL 4 
#define LED_DENY 5 
#define BUZZER 8 
Servo myservo; 
MFRC522 mfrc522(SS_PIN, RST_PIN); 
String tagID = ""; 
String allowID1 = "1B5B5644"; 
String allowID2 = "B05E9A25"; 
void setup() { 
 Serial.begin(9600); 
 while (!Serial); 
 SPI.begin(); 
 mfrc522.PCD_Init(); 
 
 delay(4); 
 mfrc522.PCD_DumpVersionToSerial(); 
 myservo.attach(SERVO_PIN); 
 pinMode(LED_ALLOW, OUTPUT); 
 pinMode(LED_NEUTRAL, OUTPUT); 
 pinMode(LED_DENY, OUTPUT); 
 myservo.write(0); 
 pinMode(BUZZER, OUTPUT); 
} 
void loop() { 
 digitalWrite(LED_NEUTRAL, HIGH); 
 digitalWrite(LED_ALLOW, LOW); 
 digitalWrite(LED_DENY, LOW); 
 Serial.println("out"); 
 tagID = ""; 
 Serial.println(mfrc522.PICC_IsNewCardPresent()); 
 Serial.println(mfrc522.PICC_ReadCardSerial()); 
 
 if ( ! mfrc522.PICC_IsNewCardPresent()) { 
 return; 
 } 
 Serial.println(tagID); 
 
 if ( ! mfrc522.PICC_ReadCardSerial()) { 
 return; 
 } 
 Serial.println(tagID); 
 
 for(uint8_t i = 0; i < 4; i++){ 
 tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); 
 } 
 Serial.println(tagID); 
 tagID.toUpperCase(); 
 mfrc522.PICC_HaltA(); 
 if(tagID == allowID1 || tagID == allowID2){ 
 Serial.print(tagID); 
 digitalWrite(LED_NEUTRAL, LOW); 
 digitalWrite(LED_ALLOW, HIGH); 
 digitalWrite(LED_DENY, LOW); 
 Serial.print(" Allowed Access\n"); 
 myservo.write(180); 
 digitalWrite(BUZZER, HIGH); 
 delay(1000); 
 digitalWrite(BUZZER, LOW); 
 delay(9000); 
 myservo.write(0); 
 }else{ 
 digitalWrite(LED_NEUTRAL, LOW); 
 digitalWrite(LED_ALLOW, LOW); 
 digitalWrite(LED_DENY, HIGH); 
 Serial.print(tagID); 
 digitalWrite(BUZZER, HIGH); 
 delay(1000); 
 digitalWrite(BUZZER, LOW); 
 delay(500); 
 digitalWrite(BUZZER, HIGH); 
 delay(1000); 
 digitalWrite(BUZZER, LOW); 
 Serial.print(" Access Denied\n"); 
 delay(1000); 
 } 
}
