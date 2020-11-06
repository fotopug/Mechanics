//instantiate strings as bytes for comparison to cards
char *RFIDstringA = "velmontball";
char *RFIDstringB = "velmontring";
char *RFIDstringC = "velmontgold";

//output pins
int audioPin = 4;
int lockmagnet1 = 5;
int lockmagnet2 = 6;

//input pins
int codeswitch1 = 8;
int codeswitch2 = 9;
int codeswitch3 = 10;

//store values for inputs
int codeswitch1state = 0;
int codeswitch2state = 0;
int codeswitch3state = 0;

//story solve states
bool code1solved = false;
bool code2solved = false;
bool code3solved = false;
bool fullysolved = false;

//audio playback state
bool audioplayed = false;

/**************************************************************************/
/*! 
    @file     readMifare.pde
    @author   Adafruit Industries
	@license  BSD (see license.txt)

    This example will wait for any ISO14443A card or tag, and
    depending on the size of the UID will attempt to read from it.
   
    If the card has a 4-byte UID it is probably a Mifare
    Classic card, and the following steps are taken:
   
    - Authenticate block 4 (the first block of Sector 1) using
      the default KEYA of 0XFF 0XFF 0XFF 0XFF 0XFF 0XFF
    - If authentication succeeds, we can then read any of the
      4 blocks in that sector (though only block 4 is read here)
	 
    If the card has a 7-byte UID it is probably a Mifare
    Ultralight card, and the 4 byte pages can be read directly.
    Page 4 is read by default since this is the first 'general-
    purpose' page on the tags.


This is an example sketch for the Adafruit PN532 NFC/RFID breakout boards
This library works with the Adafruit NFC breakout 
  ----> https://www.adafruit.com/products/364
 
Check out the links above for our tutorials and wiring diagrams 
These chips use SPI or I2C to communicate.

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

*/
/**************************************************************************/
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>

// If using the breakout with SPI, define the pins for SPI communication.
#define PN532_SCK  (2)
#define PN532_MOSI (3)
#define PN532_SS   (4)
#define PN532_MISO (5)

// If using the breakout or shield with I2C, define just the pins connected
// to the IRQ and reset lines.  Use the values below (2, 3) for the shield!
#define PN532_IRQ   (2)
#define PN532_RESET (3)  // Not connected by default on the NFC Shield

// Uncomment just _one_ line below depending on how your breakout or shield
// is connected to the Arduino:

// Use this line for a breakout with a software SPI connection (recommended):
//Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

// Use this line for a breakout with a hardware SPI connection.  Note that
// the PN532 SCK, MOSI, and MISO pins need to be connected to the Arduino's
// hardware SPI SCK, MOSI, and MISO pins.  On an Arduino Uno these are
// SCK = 13, MOSI = 11, MISO = 12.  The SS line can be any digital IO pin.
//Adafruit_PN532 nfc(PN532_SS);

// Or use this line for a breakout or shield with an I2C connection:
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
// also change #define in Adafruit_PN532.cpp library file
   #define Serial SerialUSB
#endif

void setup(void) {
  //set pinmode for outputs
  pinMode(audioPin, OUTPUT);
  pinMode(lockmagnet1, OUTPUT);
  pinMode(lockmagnet2, OUTPUT);
  //set pinmode for inputs
  pinMode(codeswitch1, INPUT);
  pinMode(codeswitch2, INPUT);
  pinMode(codeswitch3, INPUT);

  #ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
  #endif
  Serial.begin(115200);
  Serial.println("Hello!");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // configure board to read RFID tags
  nfc.SAMConfig();
  
  Serial.println("Waiting for an ISO14443A Card ...");
}

void loop(void) {
  //set all the relays low so they don't trip
  digitalWrite(audioPin, LOW);
  digitalWrite(lockmagnet1, LOW);
  digitalWrite(lockmagnet2, LOW);
  //start listening for voltages from the switches
  codeswitch1state = digitalRead(codeswitch1);
  codeswitch2state = digitalRead(codeswitch2);
  codeswitch3state = digitalRead(codeswitch3);
  //Serial.println(codeswitch3state);
  //determine order of locks and whether they've been unlocked or not
  //code1 solution
  //if the voltage on the first solution is high and I haven't been solved yet
  if (codeswitch1state == HIGH && code1solved == false) {
    //I set myself to solved
    code1solved = true;
    //I log that I have been unlocked
    Serial.println("lock 1 unlocked");
    //I push voltage to the magnetic system
    digitalWrite(lockmagnet1, HIGH);
    //I wait for a second because mechanical failures are possible and I can't determine my own state
    delay(1000);
  }
  //code2 solution
  //if the voltage on the second solution is high and the first lock was previously unlocked successfully
  if (codeswitch2state == HIGH && code1solved == true) {
    //I set myself to solved
    code2solved = true;
    //I log that I have been unlocked
    Serial.println("lock 2 unlocked");
    //I push voltage to the magnetic system
    digitalWrite(lockmagnet2, HIGH);
    //I wait for five seconds because this mechanical system fails frequently and I can't determine my own state
    delay(5000);
  }
  //code3 solution
  //if the voltage on the third solution is high and the RFID systems haven't been solved yet and the finale
  //audio sequence hasn't been initiated
  if (codeswitch3state == HIGH && code2solved == true && audioplayed == false && fullysolved == true) {
    //I set myself to solved
    code3solved = true;
    //I set the audio state to true even though I haven't pushed voltage yet because I want to guard
    audioplayed = true;
    //I push a voltage to the pin
    digitalWrite(audioPin, HIGH);
    //I wait for five seconds because it's async and the receiving card can't talk back
    delay(5000);
    //I log that I'm unlocked
    Serial.println("lock 3 unlocked");
  }

//rfid
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  
  if (success) {
    // Display some basic information about the card
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("  UID Value: ");
    nfc.PrintHex(uid, uidLength);
    Serial.println("");
    if (uidLength == 4)
    {
      // We probably have a Mifare Classic card ... 
      Serial.println("Seems to be a Mifare Classic card (4 byte UID)");
	  
      // Now we need to try to authenticate it for read/write access
      // Try with the factory default KeyA: 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF
      Serial.println("Trying to authenticate block 4 with default KEYA value");
      uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	  
	  // Start with block 4 (the first block of sector 1) since sector 0
	  // contains the manufacturer data and it's probably better just
	  // to leave it alone unless you know what you're doing
      success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 4, 0, keya);
	  
      if (success)
      {
        Serial.println("Sector 1 (Blocks 4..7) has been authenticated");
        uint8_t data[16];
		
// If you want to write something to block 4 to test with, uncomment
// the following line and this text should be read back in a minute
//        memcpy(data, (const uint8_t[]){ 'v', 'e', 'l', 'm', 'o', 'n', 't', 'b', 'a', 'l', 'l', 0, 0, 0, 0, 0 }, sizeof data);
//        success = nfc.mifareclassic_WriteDataBlock (4, data);

        // Try to read the contents of block 4
        success = nfc.mifareclassic_ReadDataBlock(4, data);
		
        if (success)
        {
          // Data seems to have been read ... spit it out
          Serial.println("Reading Block 4:");
          nfc.PrintHexChar(data, 16);
          //compare the data to the expected string - this may not be the correct approach
          if (strcmp(data,RFIDstringA) == 0) {
            //if it matches, send a voltage to the relay to trigger winning audio
            Serial.println("Some encoded card read");
            fullysolved = true;
            delay(3000);
            //clear the data cache
            *data = 0;
          } else {
            digitalWrite(audioPin, LOW);
          }
          Serial.println("");
		  
          // Wait a bit before reading the card again
          delay(1000);
        }
        else
        {
          Serial.println("Ooops ... unable to read the requested block.  Try another key?");
        }
      }
      else
      {
        Serial.println("Ooops ... authentication failed: Try another key?");
      }
    }
    
    if (uidLength == 7)
    {
      // We probably have a Mifare Ultralight card ...
      Serial.println("Seems to be a Mifare Ultralight tag (7 byte UID)");
	  
      // Try to read the first general-purpose user page (#4)
      Serial.println("Reading page 4");
      uint8_t data[32];
      success = nfc.mifareultralight_ReadPage (4, data);
      if (success)
      {
        // Data seems to have been read ... spit it out
        nfc.PrintHexChar(data, 4);
        Serial.println("");
		
        // Wait a bit before reading the card again
        delay(1000);
      }
      else
      {
        Serial.println("Ooops ... unable to read the requested page!?");
      }
    }
  }
}