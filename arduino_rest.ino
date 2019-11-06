/*
  Simple POST client for ArduinoHttpClient library
  Connects to server once every 30 seconds, sends a POST request
  and a request body

  created 14 Feb 2016
  modified 22 Jan 2019
  by Tom Igoe
 
  this example is in the public domain

  Modified to work against httpbin.org. The equivalent POST using curl is:
 
  curl --data "arg1=value1&arg2=value2" --verbose http://httpbin.org/post

  The response body contains JSON showing the values and headers received by the httpbin
  server. Example follows.
 
making POST request
Status code: 200
Response: {
  "args": {},
  "data": "",
  "files": {},
  "form": {
    "arg1": "value1",
    "arg2": "value2"
  },
  "headers": {
    "Content-Length": "23",
    "Content-Type": "application/x-www-form-urlencoded",
    "Host": "httpbin.org",
    "User-Agent": "Arduino/2.2.0"
  },
  "json": null,
  "url": "https://httpbin.org/post"
}
 */
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
//#include "arduino_secrets.h"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
/////// Wifi Settings ///////

char ssid[] = "Uncle 3";
char pass[] = "212224236";

const char serverName[] = "httpbin.org";  // server name
int port = 80;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverName, port);
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(115200);
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
  Serial.println("making POST request");
  String contentType = "application/x-www-form-urlencoded";
  String postData = "sensor_name=TESTSENSOR&sensor_temp=50.5";

  client.post("/post", contentType, postData);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  Serial.print("Status code: ");
  Serial.println(statusCode);
  String response = client.responseBody();
  Serial.print("Response: ");
  Serial.println(response);

  Serial.println("Wait 30 seconds");
  delay(3000);
}
