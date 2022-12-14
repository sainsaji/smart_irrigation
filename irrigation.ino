
#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11


DHT dht(DHTPIN, DHTTYPE);
int moistval;


void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  pinMode(1,OUTPUT);
  dht.begin();
}

int readmoist()
{
  int val = analogRead(A0);
  return val;
}

void startpump()
{
  Serial.println("pumpstart");
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C "));
  Serial.print(f);
  
  moistval=readmoist();
  Serial.println("Soil MOisture:");// sensor Aout pin connected to A0 pin of Ardiuno
  Serial.println(moistval);        // print the value in serial monitor
  if(moistval<760)
  {
    startpump();
  }
}
