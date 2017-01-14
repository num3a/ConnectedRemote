
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
#define SSD1306_LCDHEIGHT 64
#define SSD1306_LCDWIDTH 128

static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("BLE:OK  Batt: 100%");
  display.println("D: 399Wh C: 100Wh");

  display.setTextSize(2);
  display.print(" 25 km/h ");
  display.display();
  delay(2000);
  display.clearDisplay();

  // miniature bitmap display


  // draw a bitmap icon and 'animate' movement

  loop();
}

void drawTextScreen(int batteryPercentage, boolean bleIsConnected, int drawnWattPerHour, int chargedWattPerHour, int currentSpeed){

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  String bluetoothStatus = bleIsConnected ? "OK" : "KO";

  display.println("BLE:" + bluetoothStatus + "  Batt: " + String(batteryPercentage) +"%");
  display.println("D: " + String(drawnWattPerHour) + "Wh C: " + String(chargedWattPerHour) + "Wh");

  display.setTextSize(2);
  display.print(" " + String(currentSpeed) + " km/h ");
  display.display();
}


void loop() {
    int i = 0;
    int batt = 100;
    bool ble = true;
    int drawn = 100;
    int charged = 100;

    int speed = 0;

    while(true){
    delay(300);
     drawTextScreen(batt,ble, drawn, charged, speed);
    display.display();

    batt--;
    drawn++;
    charged++;
    speed++;
    }

}
