#include <Wire.h>
#include <SoftwareSerial.h>
//#include <String.h>
SoftwareSerial mySerial(2, 3);  

int BH1750_address = 0x23; // i2c 
byte buff[2];


#include "DHT.h"

#define DHTPIN1 5     // pinos dos dht
#define DHTPIN2 6 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

int valuee;
int valuee1;
int valuee2;
int valuee3;
int valuee4;
int valuee5;
int valuee6;
int x;

double deficitpressaovapor, pressaovaporsaturacao, umidadeabsoluta, calculo0, calculo1, calculo2, calculo3, calculo4, calculo5, calculo6, calculo7;

float dpv1, dpv2;


String token = "xxxx";             //token para enviar os valores "senha"

String idvariable1 = "56f1bc4c7625427d51bf36ac";       //ID temp1
String idvariable2 = "56f1bc607625427f5e08ce91";       //ID UR1
String idvariable3 = "56f1bc777625427f9c18d7ec";       //ID DPV1

String idvariable4 = "56f1bc557625427edc3bd258";       //ID temp2
String idvariable5 = "56f1bc6c7625427dd4ac1f73";       //ID UR2
String idvariable6 = "56f1bc807625427f6e0d5912";       //ID DPV2

String idvariable7 = "56f1bc897625427f36ff9490";       //ID lux
     


void setup(){
  
  Wire.begin();
  BH1750_Init(BH1750_address);
  
  delay(200);

    dht1.begin();
    dht2.begin();
    delay(1000);
   pinMode(8, OUTPUT); //liga o shield
   pinMode(13, OUTPUT); //liga o led, so para sinalizar
  digitalWrite(8, LOW);
   digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(8, HIGH);
   digitalWrite(13, HIGH);;
  delay(2000);
   digitalWrite(13, LOW);
  digitalWrite(8, LOW);
  delay(3000);

     mySerial.begin(19200);  
  Serial.begin(19200);
}

void loop(){
  float lux=0;
  float valf=0;

  if(BH1750_Read(BH1750_address)==2){
    
    valf=((buff[0]<<8)|buff[1])/1.2;
    
    if(valf<0)Serial.print("> 65535");
    else Serial.print((int)valf,DEC); //converte o valor em lux

    lux=valf,DEC;
    
    Serial.println(" lx"); 
  }



  
  delay(1000);





  

//   dht 1
 
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h1 = dht1.readHumidity();
  // Read temperature as Celsius (the default)
  float t1 = dht1.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f1 = dht1.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h1) || isnan(t1) || isnan(f1)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }



  Serial.print("Humidity: ");
  Serial.print(h1);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t1);
  Serial.print(" *C ");
  Serial.print(f1);
  Serial.println(" *F\t");


//resolve o dpv1


  calculo7 = 273.15 + t1; //resolve o denominador da fração em baixo 
Serial.println("calculo7      ");
Serial.println(calculo7);
Serial.println(" ");

calculo6 = 2.1674 * h1; //multiplica umidade relativa por 2,1674 
Serial.println("calculo6   ");
Serial.print(calculo6);
Serial.println(" ");

calculo5 = 17.67 * t1;   
Serial.println("calculo5     ");
Serial.print(calculo5);

calculo4 = t1 + 243.5;   
Serial.println("calculo4           ");
Serial.print(calculo4);
Serial.println(" ");

calculo3 = calculo5 / calculo4;
Serial.println("calculo3           ");
Serial.print(calculo3);
Serial.println(" ");

calculo2 = exp (calculo3);
Serial.println("calculo2         ");
Serial.println(calculo2);
Serial.println(" ");

calculo1= 6.112 * calculo2;
Serial.println("calculo1        ");
Serial.println(calculo1);
Serial.println(" ");

calculo0= calculo1 * calculo6;

Serial.println("calculo0        ");
Serial.println(calculo0);
Serial.println(" ");

umidadeabsoluta = calculo0 / calculo7;

pressaovaporsaturacao = (umidadeabsoluta * 100) / h1;
dpv1 = pressaovaporsaturacao - umidadeabsoluta;










// dht 2
// Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h2 = dht2.readHumidity();
  // Read temperature as Celsius (the default)
  float t2 = dht2.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f2 = dht2.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h2) || isnan(t2) || isnan(f2)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }



  Serial.print("Humidity: ");
  Serial.print(h2);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t2);
  Serial.print(" *C ");
  Serial.print(f2);
  Serial.println(" *F\t");


//resolve o dpv2

  calculo7 = 273.15 + t2; //resolve o denominador da fração em baixo 
Serial.println("calculo7      ");
Serial.println(calculo7);
Serial.println(" ");

calculo6 = 2.1674 * h2; //multiplica umidade relativa por 2,1674 
Serial.println("calculo6   ");
Serial.print(calculo6);
Serial.println(" ");

calculo5 = 17.67 * t2;   
Serial.println("calculo5     ");
Serial.print(calculo5);

calculo4 = t2 + 243.5;   
Serial.println("calculo4           ");
Serial.print(calculo4);
Serial.println(" ");

calculo3 = calculo5 / calculo4;
Serial.println("calculo3           ");
Serial.print(calculo3);
Serial.println(" ");

calculo2 = exp (calculo3);
Serial.println("calculo2         ");
Serial.println(calculo2);
Serial.println(" ");

calculo1= 6.112 * calculo2;
Serial.println("calculo1        ");
Serial.println(calculo1);
Serial.println(" ");

calculo0= calculo1 * calculo6;

Serial.println("calculo0        ");
Serial.println(calculo0);
Serial.println(" ");

umidadeabsoluta = calculo0 / calculo7;

pressaovaporsaturacao = (umidadeabsoluta * 100) / h2;
dpv2 = pressaovaporsaturacao - umidadeabsoluta;
  



String valor1, valor2, valor3, valor4, valor5, valor6, valor7;
valor1 = t1;
valor2 = h1;
valor3 = dpv1;
valor4 = t2;
valor5 = h2;
valor6 = dpv2;
valor7 = lux;



  int num;
  String le;
  String var;


 //string1

  var = "{\"value\":"+ valor1 + "}";
  num = var.length();
  le = String(num);
  for(int i = 0;i<7;i++)
  {
    mySerial.println("AT+CGATT?");               //this is made repeatedly because it is unstable  Não mudei
    delay(2000);
    ShowSerialData();
  }
  mySerial.println("AT+CSTT=\"zap.vivo.com.br\"");           // TIM
  delay(1000);
  ShowSerialData();
  mySerial.println("AT+CIICR");                                                      //bring up wireless connection  Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIFSR");                                                      //get local IP adress  Não mudei
  delay(2000);
  ShowSerialData();
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSTART=\"tcp\",\"things.ubidots.com\",\"80\"");             //start up the connection Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSEND");                                                    //begin send data to remote server Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.print("POST /api/v1.6/variables/"+idvariable1);
  delay(100);
  ShowSerialData();
  mySerial.println("/values HTTP/1.1");
  delay(100);
  ShowSerialData();
  mySerial.println("Content-Type: application/json");
  delay(100);
  
  ShowSerialData();
  mySerial.println("Content-Length: "+le);
  delay(100);
  ShowSerialData();
  mySerial.print("X-Auth-Token: ");
  delay(100);
  ShowSerialData();
  mySerial.println(token);
  delay(100);
  ShowSerialData();
  mySerial.println("Host: things.ubidots.com");       
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println(var);
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println((char)26);
  delay(7000);
  mySerial.println();
  ShowSerialData();
  mySerial.println("AT+CIPCLOSE");                                                //close the communication Não mudei
  delay(1000);
  ShowSerialData();
    
    
    if (mySerial.available())
    Serial.write(mySerial.read());

delay(100);




 // string2
 

  var = "{\"value\":"+ valor2 + "}";
  num = var.length();
  le = String(num);
  for(int i = 0;i<7;i++)
  {
    mySerial.println("AT+CGATT?");               //this is made repeatedly because it is unstable  Não mudei
    delay(2000);
    ShowSerialData();
  }
  mySerial.println("AT+CSTT=\"zap.vivo.com.br\"");           // TIM
  delay(1000);
  ShowSerialData();
  mySerial.println("AT+CIICR");                                                      //bring up wireless connection  Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIFSR");                                                      //get local IP adress  Não mudei
  delay(2000);
  ShowSerialData();
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSTART=\"tcp\",\"things.ubidots.com\",\"80\"");             //start up the connection Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSEND");                                                    //begin send data to remote server Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.print("POST /api/v1.6/variables/"+idvariable2);
  delay(100);
  ShowSerialData();
  mySerial.println("/values HTTP/1.1");
  delay(100);
  ShowSerialData();
  mySerial.println("Content-Type: application/json");
  delay(100);
  
  ShowSerialData();
  mySerial.println("Content-Length: "+le);
  delay(100);
  ShowSerialData();
  mySerial.print("X-Auth-Token: ");
  delay(100);
  ShowSerialData();
  mySerial.println(token);
  delay(100);
  ShowSerialData();
  mySerial.println("Host: things.ubidots.com");       
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println(var);
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println((char)26);
  delay(7000);
  mySerial.println();
  ShowSerialData();
  mySerial.println("AT+CIPCLOSE");                                                //close the communication Não mudei
  delay(1000);
  ShowSerialData();
    
    
    if (mySerial.available())
    Serial.write(mySerial.read());

delay(100);





 // string3
 

  var = "{\"value\":"+ valor3 + "}";
  num = var.length();
  le = String(num);
  for(int i = 0;i<7;i++)
  {
    mySerial.println("AT+CGATT?");               //this is made repeatedly because it is unstable  Não mudei
    delay(2000);
    ShowSerialData();
  }
  mySerial.println("AT+CSTT=\"zap.vivo.com.br\"");           // TIM
  delay(1000);
  ShowSerialData();
  mySerial.println("AT+CIICR");                                                      //bring up wireless connection  Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIFSR");                                                      //get local IP adress  Não mudei
  delay(2000);
  ShowSerialData();
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSTART=\"tcp\",\"things.ubidots.com\",\"80\"");             //start up the connection Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSEND");                                                    //begin send data to remote server Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.print("POST /api/v1.6/variables/"+idvariable3);
  delay(100);
  ShowSerialData();
  mySerial.println("/values HTTP/1.1");
  delay(100);
  ShowSerialData();
  mySerial.println("Content-Type: application/json");
  delay(100);
  
  ShowSerialData();
  mySerial.println("Content-Length: "+le);
  delay(100);
  ShowSerialData();
  mySerial.print("X-Auth-Token: ");
  delay(100);
  ShowSerialData();
  mySerial.println(token);
  delay(100);
  ShowSerialData();
  mySerial.println("Host: things.ubidots.com");       
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println(var);
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println((char)26);
  delay(7000);
  mySerial.println();
  ShowSerialData();
  mySerial.println("AT+CIPCLOSE");                                                //close the communication Não mudei
  delay(1000);
  ShowSerialData();
    
    
    if (mySerial.available())
    Serial.write(mySerial.read());

delay(100);





 // string4
 

  var = "{\"value\":"+ valor4 + "}";
  num = var.length();
  le = String(num);
  for(int i = 0;i<7;i++)
  {
    mySerial.println("AT+CGATT?");               //this is made repeatedly because it is unstable  Não mudei
    delay(2000);
    ShowSerialData();
  }
  mySerial.println("AT+CSTT=\"zap.vivo.com.br\"");           // TIM
  delay(1000);
  ShowSerialData();
  mySerial.println("AT+CIICR");                                                      //bring up wireless connection  Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIFSR");                                                      //get local IP adress  Não mudei
  delay(2000);
  ShowSerialData();
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSTART=\"tcp\",\"things.ubidots.com\",\"80\"");             //start up the connection Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSEND");                                                    //begin send data to remote server Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.print("POST /api/v1.6/variables/"+idvariable4);
  delay(100);
  ShowSerialData();
  mySerial.println("/values HTTP/1.1");
  delay(100);
  ShowSerialData();
  mySerial.println("Content-Type: application/json");
  delay(100);
  
  ShowSerialData();
  mySerial.println("Content-Length: "+le);
  delay(100);
  ShowSerialData();
  mySerial.print("X-Auth-Token: ");
  delay(100);
  ShowSerialData();
  mySerial.println(token);
  delay(100);
  ShowSerialData();
  mySerial.println("Host: things.ubidots.com");       
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println(var);
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println((char)26);
  delay(7000);
  mySerial.println();
  ShowSerialData();
  mySerial.println("AT+CIPCLOSE");                                                //close the communication Não mudei
  delay(1000);
  ShowSerialData();
    
    
    if (mySerial.available())
    Serial.write(mySerial.read());

delay(100);






 // string5
 

  var = "{\"value\":"+ valor5 + "}";
  num = var.length();
  le = String(num);
  for(int i = 0;i<7;i++)
  {
    mySerial.println("AT+CGATT?");               //this is made repeatedly because it is unstable  Não mudei
    delay(2000);
    ShowSerialData();
  }
  mySerial.println("AT+CSTT=\"zap.vivo.com.br\"");           // TIM
  delay(1000);
  ShowSerialData();
  mySerial.println("AT+CIICR");                                                      //bring up wireless connection  Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIFSR");                                                      //get local IP adress  Não mudei
  delay(2000);
  ShowSerialData();
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSTART=\"tcp\",\"things.ubidots.com\",\"80\"");             //start up the connection Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSEND");                                                    //begin send data to remote server Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.print("POST /api/v1.6/variables/"+idvariable5);
  delay(100);
  ShowSerialData();
  mySerial.println("/values HTTP/1.1");
  delay(100);
  ShowSerialData();
  mySerial.println("Content-Type: application/json");
  delay(100);
  
  ShowSerialData();
  mySerial.println("Content-Length: "+le);
  delay(100);
  ShowSerialData();
  mySerial.print("X-Auth-Token: ");
  delay(100);
  ShowSerialData();
  mySerial.println(token);
  delay(100);
  ShowSerialData();
  mySerial.println("Host: things.ubidots.com");       
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println(var);
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println((char)26);
  delay(7000);
  mySerial.println();
  ShowSerialData();
  mySerial.println("AT+CIPCLOSE");                                                //close the communication Não mudei
  delay(1000);
  ShowSerialData();
    
    
    if (mySerial.available())
    Serial.write(mySerial.read());

delay(100);






 // string6
 

  var = "{\"value\":"+ valor6 + "}";
  num = var.length();
  le = String(num);
  for(int i = 0;i<7;i++)
  {
    mySerial.println("AT+CGATT?");               //this is made repeatedly because it is unstable  Não mudei
    delay(2000);
    ShowSerialData();
  }
  mySerial.println("AT+CSTT=\"zap.vivo.com.br\"");           // TIM
  delay(1000);
  ShowSerialData();
  mySerial.println("AT+CIICR");                                                      //bring up wireless connection  Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIFSR");                                                      //get local IP adress  Não mudei
  delay(2000);
  ShowSerialData();
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSTART=\"tcp\",\"things.ubidots.com\",\"80\"");             //start up the connection Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSEND");                                                    //begin send data to remote server Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.print("POST /api/v1.6/variables/"+idvariable6);
  delay(100);
  ShowSerialData();
  mySerial.println("/values HTTP/1.1");
  delay(100);
  ShowSerialData();
  mySerial.println("Content-Type: application/json");
  delay(100);
  
  ShowSerialData();
  mySerial.println("Content-Length: "+le);
  delay(100);
  ShowSerialData();
  mySerial.print("X-Auth-Token: ");
  delay(100);
  ShowSerialData();
  mySerial.println(token);
  delay(100);
  ShowSerialData();
  mySerial.println("Host: things.ubidots.com");       
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println(var);
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println((char)26);
  delay(7000);
  mySerial.println();
  ShowSerialData();
  mySerial.println("AT+CIPCLOSE");                                                //close the communication Não mudei
  delay(1000);
  ShowSerialData();
    
    
    if (mySerial.available())
    Serial.write(mySerial.read());

delay(100);







 // string7
 

  var = "{\"value\":"+ valor7 + "}";
  num = var.length();
  le = String(num);
  for(int i = 0;i<7;i++)
  {
    mySerial.println("AT+CGATT?");               //this is made repeatedly because it is unstable  Não mudei
    delay(2000);
    ShowSerialData();
  }
  mySerial.println("AT+CSTT=\"zap.vivo.com.br\"");           // TIM
  delay(1000);
  ShowSerialData();
  mySerial.println("AT+CIICR");                                                      //bring up wireless connection  Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIFSR");                                                      //get local IP adress  Não mudei
  delay(2000);
  ShowSerialData();
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSTART=\"tcp\",\"things.ubidots.com\",\"80\"");             //start up the connection Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSEND");                                                    //begin send data to remote server Não mudei
  delay(3000);
  ShowSerialData();
  mySerial.print("POST /api/v1.6/variables/"+idvariable7);
  delay(100);
  ShowSerialData();
  mySerial.println("/values HTTP/1.1");
  delay(100);
  ShowSerialData();
  mySerial.println("Content-Type: application/json");
  delay(100);
  
  ShowSerialData();
  mySerial.println("Content-Length: "+le);
  delay(100);
  ShowSerialData();
  mySerial.print("X-Auth-Token: ");
  delay(100);
  ShowSerialData();
  mySerial.println(token);
  delay(100);
  ShowSerialData();
  mySerial.println("Host: things.ubidots.com");       
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println(var);
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println((char)26);
  delay(7000);
  mySerial.println();
  ShowSerialData();
  mySerial.println("AT+CIPCLOSE");                                                //close the communication Não mudei
  delay(1000);
  ShowSerialData();
    
    
    if (mySerial.available())
    Serial.write(mySerial.read());

delay(100);
  

  
}







//luximetro
void BH1750_Init(int address){
  
  Wire.beginTransmission(address);
  Wire.write(0x10); // 1 [lux] aufloesung
  Wire.endTransmission();
}

byte BH1750_Read(int address){
  
  byte i=0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while(Wire.available()){
    buff[i] = Wire.read(); 
    i++;
  }
  Wire.endTransmission();  
  return i;
}







//gprs
void ShowSerialData()
{
  while(mySerial.available()!=0)
  Serial.write(mySerial.read());
}
