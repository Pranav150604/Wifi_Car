#include <ESP8266WiFi.h>

WiFiClient client;                     //hosting a web server
WiFiServer server(80);

const char* ssid = "POCO M4 Pro 5G";    //userid and password of the respective network your nodemcu is connecting to
const char* password = "pppppppp";

String  data =""; 

void setup() 
{
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
 
  Serial.begin(115200);
  connect_wifi();
  server.begin();

  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
}

void loop() 
{
 
  client = server.available();
  if (!client) return; 
  data = getclientdata ();

  if (data == "F")                      //use the forward and back buttons on the app to turn the onboard LED ON/OFF
    { 
      analogWrite(D6,255);
      analogWrite(D5,255);
      digitalWrite(D4, HIGH);
      digitalWrite(D0, HIGH);   //ACTIVE LOW OPERATION
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);   //ACTIVE LOW OPERATION
    }
  if (data == "B") 
    {
      analogWrite(D5,255);
      analogWrite(D6,255);
      digitalWrite(D4, LOW);
      digitalWrite(D0, LOW);   //ACTIVE LOW OPERATION
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
    }
  if (data == "L") 
    { 
      analogWrite(D6,255);
      digitalWrite(D4, HIGH);
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
    }
  if (data == "R") 
    {
      analogWrite(D5,255);
      digitalWrite(D4, LOW);
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
    }
  if (data == "G") 
    {
      
      analogWrite(D5,255/3);
      analogWrite(D6,255);
      digitalWrite(D4, HIGH);
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
    }
  if (data == "H") 
    {
      
      analogWrite(D5,255/3);
      analogWrite(D6,255);
      digitalWrite(D4, LOW);
      digitalWrite(D0, LOW);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
    }
    if (data == "I") 
    {
      
      analogWrite(D6,255/3);
      analogWrite(D5,255);
      digitalWrite(D4, HIGH);
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
    }
          if (data == "J") 
    {
      
      analogWrite(D6,255/3);
      analogWrite(D5,255);
      digitalWrite(D4, LOW);
      digitalWrite(D0, LOW);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
    }
   if (data == "S") 
    {
      digitalWrite(D4, LOW);
      digitalWrite(D0, LOW);   //ACTIVE LOW OPERATION
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
    } 
}

void connect_wifi()
{
  WiFi.begin(ssid, password);
  Serial.println("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  
  Serial.println("\n\n");
  Serial.println("WiFi connected");
  Serial.print("NodeMCU Local IP: ");         //dynamically assigned IP over which your server is hosted
  Serial.println((WiFi.localIP()));
}

String getclientdata (void)
{
  while(!client.available())                  //wait till client is avaliable
  {
    delay(1); 
  }
                                                  //read the data from client
  String data = client.readStringUntil('\r');
  Serial.println("");
  Serial.print("INCOMING DATA: ");                //recognising the structure of incoming data
  Serial.println(data);
  Serial.print("length: ");
  Serial.println(data.length());
  Serial.println("END OF DATA");

  data.remove(0,12);                              //parse the input data to obtain only the required attributes
  data.remove(1,9);

  Serial.print("Parsed data:");
  Serial.println(data);
  
  Serial.print("parsed data length: ");
  Serial.println(data.length());
  
  return data;
}
