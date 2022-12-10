# ATmegaGameConsole
Repository contains my engineering degree project which theme was **`Portable pocket game`**. the device allows you to program simple games and applications. The device has the following **capabilities**:

1. Communication with the **[Waveshare LCD 2.4 inch 320x230 display module](https://www.waveshare.com/wiki/2.4inch_LCD_Module)**. The display control with the ILI9341 driver was written by me based on the documentation, manufacturer's examples and the book "[Mikrokontrolery AVR i ARM. Sterowanie wyświetlaczami LCD](https://helion.pl/ksiazki/mikrokontrolery-avr-i-arm-sterowanie-wyswietlaczami-lcd-tomasz-francuz,miklcd.htm#format/e)". Communication uses **USART in MSPI** Mode. The [ILI9341_FAST](https://github.com/cbm80amiga/ILI9341_Fast) repository was also a helpful source of knowledge. The device allows you to draw: 
   * pixel, 
   * line, 
   * rectangle, 
   * strings, 
   * bitmaps.
2. Communication with the **RTC DS1307** chip. The device provides the functions of reading/writing the date to the integrated circuit.
3.  Read different button states (**BUTTON_PRESSED, BUTTON_FALLING_EDGE, BUTTON_RISING_EDGE**),
4.  Sound generation with buzzer

# Games and applications

The repository contains examples showing the capabilities of the device in the **`Demo`** and **`Games`** folders. Current programs:
* **Tetris**,
* demoFillDisplayWithBitmaps();
* demoText(),
* demoLines(),
* demoDynamicText(),
* demoRTC(uint8_t setCompileTime),
* demoPlaySounds(),

# Hardware

### Microcontroller connections

| WS 2.4 inch ILI9341  | ATmega328  |
|---|---|
| VCC   | VCC  |
| GND   | GND  |
| DIN   | PD1  |
| CLK   | PD4  |
| CS    | PD2  |
| DC    | PD5  |
| RST   | PD6  |
| BL    | PD3  |

---

| DS1307  | ATmega328  |
|---|---|
| VCC       | VCC  |
| GND       | GND  |
| X1        | -  |
| X2        | -  |
| VBAT      | -  |
| SQW/OUT   | -  |
| SCL       | PC5  |
| SDA       | PC4  |

---

| Switch  | ATmega328  |
|---|---|
| Button up         | PC0 |
| Button down       | PC1 |
| Button left       | PC2 |
| Button right      | PC3 |
| Button start      | PB0 |
| Button select     | PB2 |

---

| Buzzer  | ATmega328  |
|---|---|
| + | PB1 |

### Schematic and PCB

The PCB design and the electronic schematic can be found in the resources folder.

![](/resources/PCB/smd_top_preview.PNG)