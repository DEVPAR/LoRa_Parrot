# LoRa_Parrot


## Its a proof of concept to realize a LoRa Repeater/Parrot on ESP32 LoRa Boards.

## Installation

**Using Arduino IDE:**
- Install ESP32 Boards on Arduino IDE 
  - [Install instructions for the ESP32 Board](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
- Install OLED Libraries
  - Sketch -> Include Library -> Manage Libraries
  - Search for "SSD1306" from Adafruit in Library Manager -> Install
  - Search for "GFX Library" from Adafruit in Library Manager -> Install
- Install LoRa Library for Semtech SX1276/77/78/79
  - Sketch -> Include Library -> Manage Libraries
  - Search for "LoRa" (LoRa by Sandeep Mistry) -> Install
- After installing the libraries copy and paste the LoRa_TRX.ino file into your Adurino IDE
- Before flashing the firmware set the right frequency config in line 17, "URCALL" or ID in line 90 and the right borad config in line 21 - 24.
  - Currently supported boads: TTGO T-Beam V1, TTGO LoRa32 V1, TTGO LoRa32 V2.1 
- Compile it and upload to the board


## Usage


- The parrot repeats everything that has ">>" in the message. Without ">>" the packet will be ignored
- You have to assign an ID / CALL to the parrot (before compiling and flashing). 
- The parrot adds "(Parrot: URCALL_1 / ID)" to the retransmitted package.
- The parrot (with same ID / CALL) cannot retransmit itself to prevent loops.


## LoRa_TRX

- You may be also interested in my other project:[LoRa_TRX](https://github.com/DEVPAR/LoRa_TRX)




## Screenshots

![Parrot](https://github.com/DEVPAR/LoRa_Parrot/blob/main/photo_2021-07-04_20-55-49.jpg)


![Parrot](https://github.com/DEVPAR/LoRa_Parrot/blob/main/photo_2021-07-04_21-04-59.jpg)


![Parrot](https://github.com/DEVPAR/LoRa_Parrot/blob/main/photo_2021-07-04_21-12-34.jpg)
