/*----------------------------------------DAFTAR LIBRARY---------------------------------------------------*/
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <RFID.h>
#include <WiFi.h>
#include <ThingESP.h>

/*--------------------------SETUP WIFI--------------------------------------------------------------------*/
const char* ssid = "skripsifajar";
const char* password = "12345678";

/*----------------------RELAY TERHUBUNG KE POMPA----------------------------------------------------------*/
#define pinRelay 4
/*----------------------------------------DEFINISIKAN RESET PIN-------------------------------------------*/
#define pinButton 2
#define button digitalRead(pinButton)

/*----------------------------------------OBJEK THINGSESP32----------------------------------------------*/
ThingESP32 thing("evolutiontechnologyindonesia", "skripsifajar", "skripsifajar1234");

/*----------------------------------------OBJEK LCD I2C--------------------------------------------------*/
LiquidCrystal_I2C lcd(0x27, 20, 4);//objek lcd 20 kolom 4 baris

/*----------------------------------------DEFINISIKAN PIN RFID-------------------------------------------*/
#define CS_RFID 5
#define RST_RFID 17
RFID rfid(CS_RFID, RST_RFID);
String SN0, SN1, SN2, SN3, SN4, SN;
//DAFTAR ANGGOTA KOS UNTUK AKSES RFID
String ID_fajar = "218541516669";
String ID_Irma = "2441591276880";
String ID_Julita = "213242197080";
String ID_Tsaniya = "18142624";
String ID_Reni = "197661470207";
String ID_Maria = "733019719884";
String ID_Novia = "197104770236";
String ID_Gita = "249237961981";
String ID_Elisa = "197407870229";
String ID_Aulia = "1351161397450";
String ID_Azibatul = "197792447056";
String ID_Anisa = "18149193171";
String ID_Indah = "66217761214";
String ID_Shita = "251451789096";
String ID_Afifatul = "194157322125";
String ID_Citra = "1973710970203";
String ID_Avinda = "822242151100";
String ID_Isnaini = "738013219891";
String ID_Dian = "98193193199";
String ID_Lilis = "13022445178";

/*----------------------------------------KEYPAD---------------------------------------------------------*/
const byte BARIS = 4; //baris
const byte KOLOM = 4; //kolom
char keypad4x4[BARIS][KOLOM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
byte pinBaris[BARIS] = {32, 33, 25, 26}; //pin baris
byte pinKolom[KOLOM] = {27, 14, 12, 13}; //pin kolom
Keypad keypad = Keypad( makeKeymap(keypad4x4), pinBaris, pinKolom, BARIS, KOLOM );
String kode;
int pinKode;
//DAFTAR ANGGOTA KOS UNTUK AKSES SANDI KEYPAD
int saveKodefajar = 3005;
int saveKodeIrma = 2143;
int saveKodeJulita = 3254;
int saveKodeTsaniya = 4365;
int saveKodeReni = 5476;
int saveKodeMaria = 6587;
int saveKodeNovia = 7698;
int saveKodeGita = 8709;
int saveKodeElisa = 9078;
int saveKodeAulia = 8967;
int saveKodeAzibatul = 7856;
int saveKodeAnisa = 6745;
int saveKodeIndah = 5634;
int saveKodeShita = 4523;
int saveKodeAfifatul = 1221;
int saveKodeCitra = 1331;
int saveKodeAvinda = 1441;
int saveKodeIsnaini = 1441;
int saveKodeDian = 1551;
int saveKodeLilis = 1661;

char tekanKeypad;
/*----------------------------------------PENDANDA--------------------------------------------------------*/
int tanda;
int dis;

int counter;
int gagalRfid = 0;
int gagalKeypad = 0;

void setup() {
  Serial.begin(115200);
  lcd.init(); //inisialisasi lcd
  lcd.backlight();//mengaktifkan lampu lcd
  SPI.begin();//set komunikasi SPI
  rfid.init();//inisialisasi RFID

  //konfigurasi pin
  pinMode(pinRelay, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  //interface awal
  lcd.setCursor(1, 0);
  lcd.print("SKRIPSI UNDIP 2022");
  lcd.setCursor(3, 1);
  lcd.print("fajar  gemilang");
  lcd.setCursor(3, 2);
  lcd.print("24040118120050");
  lcd.setCursor(4, 3);
  lcd.print("PRODI FISIKA");

  //connect thingesp
  thing.SetWiFi(ssid, password);
  thing.initDevice();
  tanda = 0;
  dis = 0;
  delay(3000);
  lcd.clear();
}

void loop() {
  //Jika push button restart ditekan, maka Mikrokontroler Akan restar
  if (button == LOW) {
    ESP.restart();
  }

  fungsiRFID();//fungsi untuk pembacaan RFID
  fungsiKeypad();//Fungsi untuk pembacaan keypad
  thing.Handle();//Fungsi untuk pembacaan WA
}

void fungsiRFID() {
  if (dis == 0) {
    digitalWrite(pinRelay, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Silahkan scan ID");
    while (rfid.isCard()) {
      if (rfid.readCardSerial()) {
        SN0 = String(rfid.serNum[0]);
        SN1 = String(rfid.serNum[1]);
        SN2 = String(rfid.serNum[2]);
        SN3 = String(rfid.serNum[3]);
        SN4 = String(rfid.serNum[4]);
        SN = SN0 + SN1 + SN2 + SN3 + SN4;
        Serial.println(SN);
        if (SN == ID_fajar) {
          lcd.clear();
          gagalRfid = 0;
          String msg_fajar = "ID: 218541516669, Nama: fajar gemilang";
          thing.sendMsg("+6283145064679", msg_fajar);
          dis = 1;
        } else if (SN == ID_Irma) {
          lcd.clear();
          gagalRfid = 0;
          dis = 2;
        } else if (SN == ID_Julita) {
          lcd.clear();
          gagalRfid = 0;
          dis = 3;
        } else if (SN == ID_Tsaniya) {
          lcd.clear();
          gagalRfid = 0;
          dis = 4;
        } else if (SN == ID_Reni) {
          lcd.clear();
          gagalRfid = 0;
          dis = 5;
        } else if (SN == ID_Maria) {
          lcd.clear();
          gagalRfid = 0;
          dis = 6;
        } else if (SN == ID_Novia) {
          lcd.clear();
          gagalRfid = 0;
          dis = 7;
        } else if (SN == ID_Gita) {
          lcd.clear();
          gagalRfid = 0;
          dis = 8;
        } else if (SN == ID_Elisa) {
          lcd.clear();
          gagalRfid = 0;
          dis = 9;
        } else if (SN == ID_Aulia) {
          lcd.clear();
          gagalRfid = 0;
          dis = 10;
        } else if (SN == ID_Azibatul) {
          lcd.clear();
          gagalRfid = 0;
          dis = 11;
        } else if (SN == ID_Anisa) {
          lcd.clear();
          gagalRfid = 0;
          dis = 12;
        } else if (SN == ID_Indah) {
          lcd.clear();
          gagalRfid = 0;
          dis = 13;
        } else if (SN == ID_Shita) {
          lcd.clear();
          gagalRfid = 0;
          dis = 14;
        } else if (SN == ID_Afifatul) {
          lcd.clear();
          gagalRfid = 0;
          dis = 15;
        } else if (SN == ID_Citra) {
          lcd.clear();
          gagalRfid = 0;
          dis = 16;
        } else if (SN == ID_Avinda) {
          lcd.clear();
          gagalRfid = 0;
          dis = 17;
        } else if (SN == ID_Isnaini) {
          lcd.clear();
          gagalRfid = 0;
          dis = 18;
        } else if (SN == ID_Dian) {
          lcd.clear();
          gagalRfid = 0;
          dis = 19;
        } else if (SN == ID_Lilis) {
          lcd.clear();
          gagalRfid = 0;
          dis = 20;
        } else {
          lcd.clear();
          gagalRfid++;
          if (gagalRfid >= 3) {
            lcd.clear();
            dis = 22;
          } else {
            lcd.clear();
            dis = 21;
          }
        }
      }
    }
  }
  if (dis == 1) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_fajar));
    lcd.setCursor(0, 2);
    lcd.print("Nama: fajar K");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 1");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 2) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Irma));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Irma S");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 2");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 3) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Julita));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Julita Arga");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 3");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 4) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Tsaniya));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Tsaniya F");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 4");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 5) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Reni));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Reni A");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 5");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 6) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Maria));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Maria F");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 6");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 7) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Novia));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Novia W");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 7");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 8) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Gita));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Gita S");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 8");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 9) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Elisa));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Elisa N");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 9");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 10) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Aulia));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Aulia K P");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 10");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 11) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Azibatul));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Azibatul H");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 11");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 12) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Anisa));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Anisa S");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 12");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 13) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Indah));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Indah J");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 13");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 14) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Shita));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Shita A");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 14");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 15) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Afifatul));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Afifatul K");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 15");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 16) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Citra));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Citra N");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 16");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 17) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Avinda));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Avinda A");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 17");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 18) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Isnaini));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Isnaini N");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 18");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 19) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Dian));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Dian F");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 19");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 20) {
    digitalWrite(pinRelay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Data Pengguna");
    lcd.setCursor(0, 1);
    lcd.print("ID: " + String(ID_Lilis));
    lcd.setCursor(0, 2);
    lcd.print("Nama: Lilis S");
    lcd.setCursor(0, 3);
    lcd.print("Kamar No: 20");
    delay(10000);
    digitalWrite(pinRelay, LOW);
    lcd.clear();
    kode = ' ';
    dis = 0;
  }
  if (dis == 21) {
    lcd.setCursor(0, 0);
    lcd.print("ID Salah");
    lcd.setCursor(0, 1);
    lcd.print("Coba kembali!");
    delay(3000);
    lcd.clear();
    dis = 0;
  }

  if (dis == 22) {
    lcd.setCursor(0, 0);
    lcd.print("Gagal sebanyak 3X");
    lcd.setCursor(0, 1);
    lcd.print("Masukan password");
    delay(3000);
    lcd.clear();
    dis = 4;
    gagalRfid = 0;
  }
}

void fungsiKeypad() {
  tekanKeypad = keypad.getKey();
  if (tekanKeypad) {
    if (tekanKeypad == 'A') {
      lcd.clear();
      dis = 23;
    }
  }

  if (dis == 23) {
    lcd.setCursor(0, 0);
    lcd.print("Masukkan Password!");
    lcd.setCursor(0, 1);
    lcd.print(kode);
    tekanKeypad = keypad.getKey();
    if (tekanKeypad) {
      kode = kode + tekanKeypad;
      pinKode = kode.toInt();
    }
    if (tekanKeypad == 'D') {
      if (pinKode == saveKodefajar) {
        lcd.clear();
        String msg_fajar = "ID: 218541516669, Nama: fajar gemilang";
        thing.sendMsg("+6283145064679", msg_fajar);
        gagalKeypad = 0;
        dis = 1;
      } else if (pinKode == saveKodeIrma) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 2;
      } else if (pinKode == saveKodeJulita) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 3;
      } else if (pinKode == saveKodeTsaniya) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 4;
      } else if (pinKode == saveKodeReni) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 5;
      } else if (pinKode == saveKodeMaria) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 6;
      } else if (pinKode == saveKodeNovia) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 7;
      } else if (pinKode == saveKodeGita) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 8;
      } else if (pinKode == saveKodeElisa) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 9;
      } else if (pinKode == saveKodeAulia) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 10;
      } else if (pinKode == saveKodeAzibatul) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 11;
      } else if (pinKode == saveKodeAnisa) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 12;
      } else if (pinKode == saveKodeIndah) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 13;
      } else if (pinKode == saveKodeShita) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 14;
      } else if (pinKode == saveKodeAfifatul) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 15;
      } else if (pinKode == saveKodeCitra) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 16;
      } else if (pinKode == saveKodeAvinda) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 17;
      } else if (pinKode == saveKodeIsnaini) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 18;
      } else if (pinKode == saveKodeDian) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 19;
      } else if (pinKode == saveKodeLilis) {
        lcd.clear();
        gagalKeypad = 0;
        dis = 20;
      } else {
        gagalKeypad++;
        if (gagalKeypad >= 3) {
          lcd.clear();
          dis = 24;
        } else {
          digitalWrite(pinRelay, LOW);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Kode Salah");
          lcd.setCursor(0, 1);
          lcd.print("Silahkan Ulangi!");
          delay(3000);
          kode = ' ';
          lcd.clear();
          dis = 23;
        }
      }
    }
  }
  if (dis == 24) {
    lcd.setCursor(0, 0);
    lcd.print("Password Salah");
    lcd.setCursor(0, 1);
    lcd.print("Dilarang Masuk");
    delay(100000);
    lcd.clear();
    dis = 0;
  }
}

String HandleResponse(String query) {
  if (query == "buka fajar") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh fajar gemilang";
  } else if (query == "buka irma") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Irma Safira";
  } else if (query == "buka julita") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Julita Arga";
  } else if (query == "buka tsaniya") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Tsaniya Falihatin";
  } else if (query == "buka reni") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Reni Asinta";
  } else if (query == "buka maria") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Maria Fajriatun";
  } else if (query == "buka novia") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Novia Wulandari";
  } else if (query == "buka gita") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Gita Safitri";
  } else if (query == "buka elisa") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Elisa Nababan";
  } else if (query == "buka aulia") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Aulia fajara P";
  } else if (query == "buka azibatul") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Azibatul H";
  } else if (query == "buka anisa") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Anisa Salsabila";
  } else if (query == "buka indah") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Indah Jasmita";
  } else if (query == "buka shita") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Shita Adibtia";
  } else if (query == "buka afifatul") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Afifatul K";
  } else if (query == "buka citra") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Citra Ningrum";
  } else if (query == "buka avinda") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Avinda Arnis";
  } else if (query == "buka isnaini") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Isnaini Nurmia";
  } else if (query == "buka dian") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Dian Fatmawati";
  } else if (query == "buka lilis") {
    digitalWrite(pinRelay, HIGH);
    delay(10000);
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Terbuka oleh Lilis Setyawati";
  } else if (query == "tutup") {
    digitalWrite(pinRelay, LOW);
    return"Done: Pintu Tertutup";
  } else if (query == "status pintu") {
    return digitalRead(pinRelay) ? "Pintu Terbuka" : "Pintu Tertutup";
  } else {
    return "Pesan salah";
  }
}
