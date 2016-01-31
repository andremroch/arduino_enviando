//usei este codigo de exemplo


/*
 Basic sketch for GPRS shield sim900

 This is a basic example to post a value on Ubidots with a simple
 function "save_value".

 You'll need:
 * An Arduino Uno
 * A GPRS shield

 created 20 Aug. 2014
 by Mateo Velez - Metavix - for Ubidots Inc.

 This example code is in the public domain.

*/

//--------------------------------------------------------------
//------------------------------Libraries-----------------------
//--------------------------------------------------------------
#include <SoftwareSerial.h>
//#include <String.h>
SoftwareSerial mySerial(2, 3);                                                      //your pins to serial communication
int value;
//-------------------------------------------------------------
//---------------------Ubidots Configuration-------------------
//-------------------------------------------------------------



String token = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";             //token para enviar os valores "senha"




String idvariable = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";       //ID da variavel




void setup()
{

  mySerial.begin(19200);                                                            //the GPRS baud rate
  Serial.begin(19200);                                                              //the serial communication baud rate
  delay(10000);
}

void loop()
{
    int value = analogRead(A0);          //Valor do LDR
    save_value(String(value));                                                      //call the save_value function
    if (mySerial.available())
    Serial.write(mySerial.read());
}
//this function is to send the sensor data to Ubidots, you should see the new value in Ubidots after executing this function
void save_value(String value)
{
  int num;
  String le;
  String var;
  var = "{\"value\":"+ value + "}";
  num = var.length();
  le = String(num);
  for(int i = 0;i<7;i++)
  {
    mySerial.println("AT+CGATT?");               //this is made repeatedly because it is unstable
    delay(2000);
    ShowSerialData();
  }
  mySerial.println("AT+CSTT=\"tim.br\"");           //replace with your providers' APN
  delay(1000);
  ShowSerialData();
  mySerial.println("AT+CIICR");                                                      //bring up wireless connection
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIFSR");                                                      //get local IP adress
  delay(2000);
  ShowSerialData();
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSTART=\"tcp\",\"things.ubidots.com\",\"80\"");             //start up the connection
  delay(3000);
  ShowSerialData();
  mySerial.println("AT+CIPSEND");                                                    //begin send data to remote server
  delay(3000);
  ShowSerialData();
  mySerial.print("POST /api/v1.6/variables/"+idvariable);
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
  mySerial.println("AT+CIPCLOSE");                                                //close the communication
  delay(1000);
  ShowSerialData();
}

void ShowSerialData()
{
  while(mySerial.available()!=0)
  Serial.write(mySerial.read());
}

