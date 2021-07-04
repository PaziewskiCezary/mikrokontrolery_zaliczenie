# Projekt zaliczeniowy na programowanie mikrokontrolerów

Ptosta gra 2D wykorzystująca joystick i wyświetlacz znakowy LCD. Zadaniem gracza jest zebrać wszystkie kwiatki z labiryntu zanim skończy się czas.

## Układ
Sprzęt:
* Teansy LC
* LCD hd44780 2×16 z konwerterem na I2C
* Joystick analogowy

Biblioteki:
 * LCD_I2C 2.2.1 by Blackhack
 * EEPROM

Połączenie:
* Joystick:
  * GND - GND
  * +5V - 3.3V (ADC Teensy LC obsługuje napięcia do 3.3V) 
  * VRy - Analog 1
  * VRy - Analog 0
  * SW  - Analog
* LCD:
  * GND - GND
  * VCC - 5V
  * SDA - Pin 18
  * SCL - Pin 19
