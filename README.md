#RPiLCD
###Raspberry Pi + LCD

![image](http://h78563.s06.test-hf.su/images/RPiLCD.jpg)

#####In this work have been implemented:
+ Connection LCD display controllers are based on KS0066U to Raspberry PI;
+ Create a client server application. Raspberry Pi has received information from the client and prints it on the LCD screen.



#####Info for work with server
 - For write string you should write:
  - str:"your_str"
 - To send a command for LCD write:
  - com:"YOUR_COMMAND"
 - Available commands:
  - LINE_1 -set line one to write text
  - LINE_2 -set line two to write text
  - CLEAR -clear lcd
  - SET_LINE_1 -set one line mode
  - SET_LINE_2 -set two line mode


#####Info for work with raspberry pi
 - For compile programm:
  - gcc -o NAME_DIR NAME_FILE.c -lrt -lbcm2835
 - For run programm:
  - sudo ./NAME
 - For change keyboard layout:
  - setxkbmap COUNTRY_CODE
