#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include "utils.h"
#include "secrets.h"
#include "wifi_manager.h"
#define TIME_ZONE -3
 
const int RELAY_1 = 16;
const int RELAY_2 = 5;
const int RELAY_3 = 4;
const int RELAY_4 = 14;

#define AWS_IOT_SUBSCRIBE_TOPIC "$aws/things/pool-green2b/shadow/update" // "pool-green2B/command"
#define AWS_IOT_PUBLISH_TOPIC "$aws/things/pool-green2b/shadow/update"     // "pool-green2B/return"

WiFiClientSecure net;
 
BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);
 
PubSubClient client(net);
 
time_t now;
time_t nowish = 1510592825;

void NTPConnect(void)
{
  Serial.print("Setting time using SNTP");
  configTime(TIME_ZONE * 3600, 0 * 3600, "pool.ntp.org", "time.nist.gov");
  now = time(nullptr);
  while (now < nowish)
  {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("done!");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
}
 

void pushRelay(int id)
{
  digitalWrite(id, LOW);
  delay(500);
  digitalWrite(id, HIGH);
} 
void messageReceived(char *topic, byte *payload, unsigned int length)
{
  StaticJsonDocument<400> doc;
  deserializeJson(doc, payload);
  serializeJsonPretty(doc, Serial);
  
  // Serial.println((String)doc["state"]);
  // //print received message
  // Serial.print("Received [");
  // Serial.print(topic);
  // Serial.println("]: ");
  // for (int i = 0; i < length; i++){Serial.print((char)payload[i]);}

  if (!doc.as<JsonObject>()["state"].containsKey("desired"))return;

  
  if(doc["state"]["desired"]["pin1"] == "x"){pushRelay(RELAY_1);}
  if(doc["state"]["desired"]["pin2"] == "x"){pushRelay(RELAY_2);}
  if(doc["state"]["desired"]["pin3"] == "x"){pushRelay(RELAY_3);}
  if(doc["state"]["desired"]["pin4"] == "x"){pushRelay(RELAY_4);}

  JsonObject crew = doc["state"];
  doc["state"]["reported"] = doc["state"]["desired"];
  crew.remove("desired");

  char jsonBuffer[256];
  serializeJson(doc, jsonBuffer); // print to client
  client.publish((const char *)AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}
 
void connectAWS()
{
  blinkLed(LED, 1000, 0, 4);

  // delay(3000);
 
 
  NTPConnect();
 
  net.setTrustAnchors(&cert);
  net.setClientRSACert(&client_crt, &key);
 
  client.setServer(MQTT_HOST, 8883);
  client.setCallback(messageReceived);
 
 
  Serial.println("Connecting to AWS IOT ...");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(1000);
  }
 
  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
  Serial.println("AWS IoT Connected!");
  blinkLed(LED, 2000, 0, 4);

}
 

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(RELAY_1, OUTPUT);
  digitalWrite(RELAY_1, HIGH);
  pinMode(RELAY_2, OUTPUT);
  digitalWrite(RELAY_2, HIGH);
  pinMode(RELAY_3, OUTPUT);
  digitalWrite(RELAY_3, HIGH);
  pinMode(RELAY_4, OUTPUT);
  digitalWrite(RELAY_4, HIGH);
  
  Serial.begin(9600);

  blinkLed(LED, 1000, 0, 4);
  setupWM();
  connectAWS();
 
}
 
void loop()
{

  if (!WiFi.isConnected())
  {
    blinkLed(LED, 100, 0, 1);
  }
  else
  {
    blinkLed(LED, 1000, 0, 4);
    if (!client.connected())
    {
      Serial.println("Client not connected! Connecting...");
      connectAWS();
    }
    client.loop();
    loopWM();
  }

}