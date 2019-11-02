#include <WiFiNINA.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT22   // DHT 22  (AM2302)

char ssid[] = "Uncle Engineer(2.4GHz)";
char pass[] = "212224236";

int status = WL_IDLE_STATUS;

char server[] = "www.cons-robotics.com";

String postData;
String postVariable = "temp=";

WiFiClient client;


DHT dht = DHT(DHTPIN, DHTTYPE);


void setup() {

  Serial.begin(9600);

  dht.begin();

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
  //int reading = analogRead(sensorPin);

  float reading = dht.readTemperature();
  
  

  postData = postVariable + reading;

  if (client.connect(server, 80)) {
    client.println("POST /API/arduino/post.php HTTP/1.1");
    client.println("Host: www.cons-robotics.com");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();
    client.print(postData);
  }

  if (client.connected()) {
    client.stop();
  }
  Serial.println(postData);

  delay(3000);
}
