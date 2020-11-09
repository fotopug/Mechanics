# Motion Control for RI Riddle Room
This repo is an archive of scripts used to control various mechanicals in the Riddle Room. It's currently being overhauled and probably won't ever have applicability beyond the Riddle Room. On the upside, you can probably infer how to unlock some of the puzzles if you can make your way through a mess of terrible C++ written years ago.
## What hardware does it run on?
There are three key pieces of hardware in use. Logic is generally executed on Arduinos, mostly Unos, but anything that will compile C++ and provide access to digital and analog signals will suffice with some small adaptation. RFID tag reading is handled by the Adafruit PN532. Audio playback and various signal processing is handled by the Adafruit Audio FX Mini. 
* [Compatible Arduino](https://www.adafruit.com/product/2488)
* [Adafruit PN532](https://www.adafruit.com/products/364)
* [Adafruit FX Mini](https://www.adafruit.com/product/2342?gclid=Cj0KCQiA7qP9BRCLARIsABDaZzhx8V7Z2GiWsN3IG1_DQwii2y_w0vHyXuFGCV_JCUsUciLl_GqJUi0aAvfIEALw_wcB)
## Build Instructions
1. Download the files as appropriate for the device you wish to write to
2. Compile it, most dependencies are currently included in the script monolithicly or standard libs
3. ???
4. Party
## Where can I see this in action?
Check out the [RI Riddle Room](https://www.ririddleroom.com) and try the Vanishing at the Velmont.