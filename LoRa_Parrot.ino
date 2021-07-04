#include <stdio.h>
#include <string.h>
//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*Frequency setup*/
// 433E6 for Asia
// 866E6 for Europe
// 915E6 for North America
// 433775000 for Ham Radio
#define BAND 433775000



/*Board setup for LoRa and OLED Pins, comment out the boards you dont use*/
//#define LORA32-V1
  #define LORA32-V2.1
//#define LORA32-T-BAEM

#ifdef LORA32-V1
//Board: LoRa32-V1
//LoRa and OLED Pins
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26
//OLED pins
#define OLED_SDA 4
#define OLED_SCL 15 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#endif


#ifdef LORA32-V2.1
//Board: LoRa32-V2.1
//LoRa and OLED Pins
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 23
#define DIO0 26
#define DIO1 33  // GPIO 33
#define DIO2 32  // GPIO 32
//OLED pins
#define OLED_SDA 21
#define OLED_SCL 22 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#endif


#ifdef LORA32-T-BEAM
//Board: LoRa32-T-Beam
//LoRa and OLED Pins
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26
#define DIO1 33  // GPIO 33
#define DIO2 32  // GPIO 32
//OLED pins
#define OLED_SDA 21
#define OLED_SCL 22 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#endif




Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

String LoRaData;
String message;
String ParrotID = "URCALL_1"; //use URCALL_1 as SSID / ID for the Parrot

void setup() {

  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);
  
  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("LoRa-Parrot by DM5LG");
  display.display();

  Serial.println("LoRa Receiver Test");
  
  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {         //433775000 or BAND
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
  display.setCursor(0,10);
  display.setTextSize(1);
  display.println("Version 0.1 Beta");
  display.display(); 
  //LoRa settings
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(125000);
  LoRa.setCodingRate4(5);
  LoRa.enableCrc();
  LoRa.setTxPower(20);
  delay(2000);
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("LORA RX");
  display.setCursor(0,20);
  display.print("Add >> to your transmision in order to be repaeted");
  display.display(); 
  delay(1000);
  
}


void loop() {
 

//try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    //received a packet
    //Serial.print("Received packet ");

    //read packet
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }

    //print RSSI of packet
    int rssi = LoRa.packetRssi();
    float snr = LoRa.packetSnr();
    Serial.print(" with RSSI ");    
    Serial.println(rssi);
   
  int okcall = strstr(LoRaData.c_str(),ParrotID.c_str()) != NULL;
  int ok = strstr(LoRaData.c_str(),">>") != NULL;
  

  if (!okcall && ok) {
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("LORA Repeater TX");
  display.display();
  
  LoRa.beginPacket();
  LoRa.print("(Parrot: " + ParrotID + ") " + LoRaData); 
  LoRa.endPacket();
  
  
  
    
   // Dsiplay information
   display.clearDisplay();
   display.setCursor(0,0);
   display.print("Last repeated packet:");
   display.setCursor(0,10);
   display.print("RSSI: " );
   display.setCursor(30,10);
   display.print(rssi);
   display.setCursor(0,20);
   display.print(LoRaData);
   
   
   //display.setCursor(40,50);
   //display.print("SNR: ");
   //display.setCursor(45,50);
   //display.print(snr);
   display.display();  
   
  }
  }
}
