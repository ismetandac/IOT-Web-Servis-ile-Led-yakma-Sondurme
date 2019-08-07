#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#define DHTTYPE DHT11  

/*Put your SSID & Password*/
const char* ssid = "Choo";  // Enter SSID here
const char* password = "bagarius07";  //Enter Password here
String host = "http://ledapi.iotcihazim.site/api";
String deviceKey = String(ESP.getChipId());

ESP8266WebServer server(80);

// DHT Sensor
uint8_t LEDPin = D1; 
               

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(LEDPin, OUTPUT);          

  Serial.println("Connecting to ");
  Serial.println(ssid);
  Serial.println("Key:"+deviceKey);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());


  server.begin();
  Serial.println("HTTP server started");

}
void loop() {

  
  server.handleClient();
  readleddata();
  delay(2000);
  
}
void readleddata()
{
  String  js= GetJson("/Data?Key="+deviceKey);
  Serial.println(js);
  if(js=="true")
  {
    digitalWrite(LEDPin, HIGH);  
  }else {
      digitalWrite(LEDPin, LOW);
  }

  Serial.println("Geldi");
}


//POST Metodu
void PostJson(String Url, String PostData)
{
  //USE_SERIAL.println(PostData);
  HTTPClient http;
  http.setTimeout(2500);
  Serial.println(host + Url);
  http.begin(host + Url);
  http.addHeader("Content-Type", "application/json");
  http.POST(PostData);
  http.writeToStream(&Serial);
  //USE_SERIAL.println(http.getString());
  //USE_SERIAL.println(host + Url);
  String payload = http.getString();                  //Get the response payload
  delay(100);
  //PrintLog(PostData);   //Print HTTP return code
  // PrintLog(payload);    //Print request response payload
  http.end();
}

String GetJson(String Url)
{
  String payload;
  HTTPClient http;      // HTTPClient istegi oluşturma

  String lnk = host + Url;
  http.begin(lnk);        //istegin yapılacagı yer
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.GET(); //istek gönderme
  if (httpCode > 0) { //Check the returning code
    payload = http.getString();   //istek yanıtının sonucu
  }
  http.end();   //isteği sonlandırır

  return payload;
}
