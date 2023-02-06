#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <RFID.h>

#define CS_RFID 5
#define RST_RFID 17
RFID rfid(CS_RFID, RST_RFID);
String SN0, SN1, SN2, SN3, SN4, SN;

LiquidCrystal_I2C lcd(0x27, 20, 4);//objek lcd 20 kolom 4 baris

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.init();
  lcd.init(); //inisialisasi lcd
  lcd.backlight();//mengaktifkan lampu lcd

}

void loop() {
  if(rfid.isCard()) {
    if (rfid.readCardSerial()) {
      SN0 = String(rfid.serNum[0]);
      SN1 = String(rfid.serNum[1]);
      SN2 = String(rfid.serNum[2]);
      SN3 = String(rfid.serNum[3]);
      SN4 = String(rfid.serNum[4]);
      SN = SN0 + SN1 + SN2 + SN3 + SN4;
      Serial.println(SN);
    }
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ID: "+String(SN));
  delay(1000);
}
