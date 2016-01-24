// exemplo de como utilizar um Arduino Uno, um DHT11 e um ethernet shield w5100
// Utilizei como exemplo inicial codigo que encontrei no site da sparkfun



/*****************************************************************
Phant_Ethernet.ino
Post data to SparkFun's data stream server system (phant) using
an Arduino and an Ethernet Shield.
Jim Lindblom @ SparkFun Electronics
Original Creation Date: July 3, 2014
This sketch uses an Arduino Uno to POST sensor readings to 
SparkFun's data logging streams (http://data.sparkfun.com). A post
will be initiated whenever pin 3 is connected to ground.

Before uploading this sketch, there are a number of global vars
that need adjusting:
1. Ethernet Stuff: Fill in your desired MAC and a static IP, even
   if you're planning on having DCHP fill your IP in for you.
   The static IP is only used as a fallback, if DHCP doesn't work.
2. Phant Stuff: Fill in your data stream's public, private, and 
data keys before uploading!

Hardware Hookup:
  * These components are connected to the Arduino's I/O pins:
    * D3 - Active-low momentary button (pulled high internally)
    * A0 - Photoresistor (which is combined with a 10k resistor
           to form a voltage divider output to the Arduino).
    * D5 - SPDT switch to select either 5V or 0V to this pin.
  * A CC3000 Shield sitting comfortable on top of your Arduino.

Development environment specifics:
    IDE: Arduino 1.0.5
    Hardware Platform: RedBoard & PoEthernet Shield

This code is beerware; if you see me (or any other SparkFun 
employee) at the local, and you've found our code helpful, please 
buy us a round!

Much of this code is largely based on David Mellis' WebClient
example in the Ethernet library.

Distributed as-is; no warranty is given.
*****************************************************************/







#include <SPI.h> // Precisa
#include <Ethernet.h> // Precisa


//  não usei          #include <Progmem.h>  //Allows us to sacrifice flash for DRAM





#include "DHT.h"      // DHT 11
#define DHTPIN 8     // pino do dht DHT 11
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);   // DHT 11






///////////////////////
// Ethernet Settings //
///////////////////////



//deixei tudo igual





// coloque qualquer mac 



byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF };

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(54,86,132,254);  // numeric IP for data.sparkfun.com


char server[] = "data.sparkfun.com";    // name address for data.sparkFun (using DNS)

// Set the static IP address to use if the DHCP fails to assign

IPAddress ip(192,168,0,177);

//tudo igual estava
EthernetClient client;





/////////////////
// Phant Stuff //
/////////////////

const String publicKey = "COLOQUE_SUA_CHAVE_PUBLICA_AQUI";     //minha chave publica, "endereço"
const String privateKey = "COLOQUE_SUA_CHAVE_PRIVADA_AQUI";     //minha chave privada, "senha"
const byte NUM_FIELDS = 2;  //quantidade de campos
const String fieldNames[NUM_FIELDS] = {"umidade" , "temperatura"};  //o nome dos campos que serão publicados
String fieldData[NUM_FIELDS];










//roda uma vez


void setup()
{
  Serial.begin(115200);  // deixei como estava










setupEthernet();     // chama o void setupEthernet() para configuragar as coisas.




  Serial.println(F("Agora vai!"));
 
 
}












//roda em loop


void loop()
{
  {


// DHT11, deixei como estava o exemplo


  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  delay(100);
}
































  
  // aqui é feita a leitura do dht para o envio
 
    
    delay(60000);    // envia a cada 60 segundos
    
    //Gather data:

    
    fieldData[0] = String(dht.readHumidity());   //são dois campos, este 0
    fieldData[1] = String(dht.readTemperature()); //são dois campos, este 1
    
    Serial.println("Enviando");
    
    postData(); // the postData() function does all the work, 
                // o postData() resolve.

    
 

} //acaba o void loop






//esse aqui que envia para o data.sparkfun.com

//não modifiquei nada


void postData()  
{
  // Make a TCP connection to remote host
  if (client.connect(server, 80))
  {
    // Post the data! Request should look a little something like:
    // GET /input/publicKey?private_key=privateKey&light=1024&switch=0&name=Jim HTTP/1.1\n
    // Host: data.sparkfun.com\n
    // Connection: close\n
    // \n
    client.print("GET /input/");
    client.print(publicKey);
    client.print("?private_key=");
    client.print(privateKey);
    for (int i=0; i<NUM_FIELDS; i++)
    {
      client.print("&");
      client.print(fieldNames[i]);
      client.print("=");
      client.print(fieldData[i]);
    }
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
  }
  else
  {
    Serial.println(F("Connection failed"));
  } 

  // Check for a response from the server, and route it
  // out the serial port.
  while (client.connected())
  {
    if ( client.available() )
    {
      char c = client.read();
      Serial.print(c);
    }      
  }
  Serial.println();
  client.stop();
}






//esse aqui configura é para o ethernet



void setupEthernet()
{
  Serial.println("Setting up Ethernet...");
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("Failed to configure Ethernet using DHCP"));
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  // give the Ethernet shield a second to initialize:
  delay(1000);
}
