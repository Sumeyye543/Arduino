#include <LiquidCrystal.h>
#include <Keypad.h>
const int yangin = 6; // yangin sensörü giriş pin
int buzzercikis = 9; // buzzer pin
int cikis = 0; //kontrol değişkeni
const int hareketsensoru = 8; // hareket sensörü giriş pini
int tetik = 7; // led için çıkış pini
boolean hareketcikis = 0; // kontrol değişkeni
float degisken; // derece bulma degiskeni
const int sicaklik = A0; // sicaklik giris pini
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // led pinleri

const byte Satirlar = 4; // Kaç satır olduğu
const byte Sutunlar = 3; //Kaç sütun olduğu

char anahtarlar[Satirlar][Sutunlar] = { // anahtarlar
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte Satirpinleri[Satirlar] = {36, 37, 38, 39};
byte Sutunpinleri[Sutunlar] = {40, 41, 42}; 
String sifre="1234";

Keypad keypad = Keypad( makeKeymap(anahtarlar), Satirpinleri, Sutunpinleri, Satirlar, Sutunlar );

int kirmiziisik = 14;
int yesilisik = 15;
boolean kontrol = false;
String sifre4harfli;
int sayi = 0;




void setup() {
  pinMode(buzzercikis, OUTPUT);
  pinMode(yangin, INPUT);
  pinMode(hareketsensoru, INPUT);
  pinMode(tetik, OUTPUT);
  pinMode(sicaklik, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(kirmiziisik, OUTPUT);
  pinMode(yesilisik, OUTPUT);



}

void loop() {

  cikis = digitalRead(yangin);
  hareketcikis = digitalRead(hareketsensoru);

  if (cikis == 1) {
    digitalWrite(buzzercikis, HIGH);
  }
  else if(cikis==0) {
    digitalWrite(buzzercikis, LOW);
  }
  if (hareketcikis == 1) {
    digitalWrite(tetik, HIGH);

  } else if(hareketcikis==0) {
    digitalWrite(tetik, LOW);
  }
  degisken = analogRead(sicaklik);
  float voltu = ( degisken / 1023)*5000;
  float derece = voltu/10;
  lcd.setCursor(0, 0);
  lcd.print("Sicaklik:");
  lcd.print(derece);
  lcd.print("C");

  if (derece > 30) {
    lcd.setCursor(0, 1);
    lcd.print("sicaklikyukseldi");
  }
  else if (derece < 20) {
    lcd.setCursor(0, 1);
    lcd.print("sicaklikdustu");
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("                ");


  }
      char basilan = keypad.getKey();

    if (basilan != NO_KEY)
    {
    sifre4harfli=sifre4harfli+basilan;
      if (sifre4harfli.length()==4)
      {

        if (sifre4harfli[0] == sifre[0] && sifre4harfli[1] == sifre[1] && sifre4harfli[2] == sifre[2] && sifre4harfli[3] == sifre[3]) { 
          
       
          digitalWrite(yesilisik, HIGH);
          digitalWrite(kirmiziisik, LOW);
          delay(60);
          digitalWrite(yesilisik, LOW);
          sifre4harfli=""; 
        }
        else if(sifre4harfli[0] != sifre[0] || sifre4harfli[1] != sifre[1] || sifre4harfli[2] != sifre[2] || sifre4harfli[3] != sifre[3])
        {
          
          digitalWrite(kirmiziisik, HIGH);
          digitalWrite(yesilisik, LOW);
          delay(60);
          digitalWrite(kirmiziisik, LOW);
          sifre4harfli="";


        }
      }
    
    }

}
