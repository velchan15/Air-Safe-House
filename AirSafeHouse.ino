#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD I2C dengan alamat default (0x27 atau 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int Sensor_gas = A0; // Pin sensor gas
const int LED_HIJAU = 2;   // LED hijau
const int LED_MERAH = 3;   // LED merah
const int buzzer = 4;      // Buzzer
const int ISD_PLAY = 5;
bool alarmActive = false;

int sensorThres = 450;     // Ambang batas sensor

void setup() {
  pinMode(Sensor_gas, INPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ISD_PLAY, OUTPUT);
  digitalWrite (ISD_PLAY, LOW);


  lcd.init();              // Inisialisasi LCD
  lcd.backlight();         // Nyalakan lampu latar LCD
  lcd.clear();

  Serial.begin(9600);      // Untuk debugging
}

void playVoiceAlert(){
  digitalWrite (ISD_PLAY, HIGH);
  delay(100);
  digitalWrite (ISD_PLAY, LOW);
}

void loop() {
  int analogsensor = analogRead(Sensor_gas); // Baca nilai sensor
  Serial.print("Nilai Sensor: ");            // Debugging nilai sensor
  Serial.println(analogsensor);

  if (analogsensor > sensorThres) {

    if (!alarmActive) {
      playVoiceAlert();
      alarmActive = true;
    }
    lcd.setCursor(0, 0);
    lcd.print("Kondisi Bahaya"); // Ganti teks sesuai kondisi
    lcd.setCursor(0, 1);
    lcd.print("Terdeteksi Gas");
    // Jangan gunakan lcd.clear() di sini

    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_HIJAU, LOW);
    tone(buzzer, 1000); // Bunyikan buzzer
  } else {
     
      alarmActive = false;
    lcd.setCursor(0, 0);
    lcd.print("Kondisi Aman  ");
    lcd.setCursor(0, 1);
    lcd.print("Tidak Ada gas");
    // Jangan gunakan lcd.clear() di sini

    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_HIJAU, HIGH);
    noTone(buzzer); // Matikan buzzer
  }

  delay(1000); // Tunggu 1 detik
}