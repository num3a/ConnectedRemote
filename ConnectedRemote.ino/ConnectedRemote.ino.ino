#include <SoftwareSerial.h>
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

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothRx, bluetoothTx); // RX, TX

int led = 13;
int buttonPin1 = 7;
int button1State = 0;


#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();
  delay(1000);
  display.clearDisplay();

  //bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$");  // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  pinMode(led, OUTPUT);
  pinMode(buttonPin1, INPUT);

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
    digitalWrite(led, LOW);
    bluetooth.println("AT+NAME=TEST");

    
    while(true){
      delay(300);
       drawTextScreen(batt,ble, drawn, charged, speed);
      display.display();
  
      batt--;
      drawn++;
      charged++;
      speed++;
      digitalWrite(led,HIGH);
    }

     if (bluetooth.available()) {
        Serial.write(bluetooth.read());
    }
    if (Serial.available()) {
        bluetooth.write(Serial.read());
    }

}
