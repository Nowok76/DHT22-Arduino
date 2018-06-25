#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <math.h>

#include <Wire.h>
#include <Adafruit_MPL115A2.h>   //biblioteka z czujnika ciśnienia

#define DHTPIN 2          // numer pinu sygnałowego
#define DHTTYPE DHT22     // typ czujnika (DHT11). Jesli posiadamy DHT22 wybieramy DHT22
int nRainIn = A1;         // pin czujnika opadów
 
DHT dht(DHTPIN, DHTTYPE); // definicja czujnika
Adafruit_MPL115A2 mpl115a2;  //czujnik ciśnienia 
  
void setup() {
  
  Serial.begin(9600);     // otworzenie portu szeregowego
  dht.begin();// inicjalizacja czujnika dht
  mpl115a2.begin(); //inicjacja ciśnienia
  //analogReference(EXTERNAL);
  //analogReference(INTERNAL1V1);
}
     
void loop()
{
  analogReference(DEFAULT);
  int nRainVal = analogRead(nRainIn);  //opady
  float pressureKPA = 0;
  pressureKPA = mpl115a2.getPressure() *10; 
  
  analogReference(INTERNAL1V1);
  float sensorValue = analogRead(A0); //Peltier
 
   
 // Odczyt temperatury,wilgotności,punktu rosy i chmury
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float d = pow(h/100,0.125) * (112.0 + (0.9 * t)) + (0.1 * t) - 112.0; //wzór na punkt rosy
 


      // Sprawdzamy czy są odczytane wartości
  if (isnan(t) || isnan(h))
  {
    // Jeśli nie, wyświetlamy informację o błędzie
    Serial.println("Blad odczytu danych z czujnika");
  } else
  {
    // Jeśli tak, wyświetlamy wyniki pomiaru
    Serial.print(t); 
    Serial.print(";");
    Serial.print(h);
    Serial.print(";");
    Serial.print(d);  
    Serial.print(";");
    Serial.print(sensorValue);
    Serial.print(";");
    Serial.print(nRainVal);
    Serial.print(";");
    Serial.println(pressureKPA, 2);
    
    
    delay(600000);
    
  }
}

