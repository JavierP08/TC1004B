#include "DHT.h" 
#include <ESP8266WiFi.h>

#define ssid "Javi_iPhone"
#define password "123456789"

char server[] = "8080-javierp08-tc1004b-rwg7w0p4whp.ws-us77.gitpod.io";
//URLS
String url_1 = "/sensor1_distancia=";
String url_2 = "/sensor2_humedadTemp=";
String url_3 = "/sensor3_nivelLuz=";

bool iterar = true;

const int trigPin = 12;
const int echoPin = 14;

const int LDR = A0;

DHT dht2(2,DHT11);

#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm, hum, temp;
int valor;
WiFiClientSecure client;

void setup() {
  Serial.begin(115200); // Starts the serial communication

  dht2.begin();  

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
  Serial.print(".");
  delay(250);
  }
  Serial.print("\nConectado al Wi-Fi");
  Serial.println();
  Serial.println("Connecting to server...");
  Serial.println(server);

  return;
}

void loop() {
  // ------------------ Sensor movimiento -------------------------------
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_VELOCITY/2;
  String distancia = String(distanceCm);
  // --------------------------------------------------------------------

  //-------------------- Sensor Temperatura / Humedad -------------------
  hum = dht2.readHumidity();
  temp = dht2.readTemperature();

  String humedad = String(hum);
  String temperatura = String(temp);
  // --------------------------------------------------------------------
  
  //-------------------- Sensor De Luz ----------------------------------
  int a = analogRead(LDR);
  valor = map(a, 0, 15, 0, 100); 
  String val = String(valor);
  // --------------------------------------------------------------------

  Serial.print("Requesting URL: ");
  Serial.println(url_1);
  Serial.print("Requesting URL: ");
  Serial.println(url_2);
  Serial.print("Requesting URL: ");
  Serial.println(url_3);

  //----------------------------- Subida de valores ---------------------
  client.setInsecure();
  const int httpPort = 443;
  if (!client.connect(server, httpPort)) {
  Serial.println("connection failed");
  }
  client.println(String("GET ") + url_1 + distancia + " HTTP/1.1\r\n" +
  "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");

  if (!client.connect(server, httpPort)) {
  Serial.println("connection failed");
  }
  client.println(String("GET ") + url_2 + humedad + ";" + temperatura + " HTTP/1.1\r\n" +
  "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");

  if (!client.connect(server, httpPort)) {
  Serial.println("connection failed");
  }
  client.println(String("GET ") + url_3 + val + " HTTP/1.1\r\n" +
  "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");
  //---------------------------------------------------------------------
  
  // Prints 
  
  delay(5000);
}