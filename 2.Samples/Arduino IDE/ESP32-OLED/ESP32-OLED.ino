
#include <Arduino.h>
#include <U8g2lib.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>

U8G2_SSD1306_128X80_NONAME_F_HW_I2C u8g2(U8G2_R3, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 22, /* data=*/21);


// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az, gx, gy, gz;
// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO
// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
//#define OUTPUT_BINARY_ACCELGYRO
#define LED_PIN 27
bool blinkState = false;


void setup(void)
{
    u8g2.begin();
    u8g2.enableUTF8Print();        // enable UTF8 support for the Arduino print() function

    u8g2.setFont(u8g2_font_unifont_t_chinese2);  // use chinese2 for all the glyphs of "你好世界"
    u8g2.setFontDirection(0);
    u8g2.clearBuffer();
    u8g2.setCursor(0, 15);
    u8g2.print("Initializing...");

    
    u8g2.setCursor(0, 40);
    u8g2.print("I2C devices...");
    u8g2.sendBuffer();

    Wire.begin(32, 33);
    //Wire.setClock(400000);
    // initialize serial communication
    Serial.begin(115200);
    // initialize device
    Serial.println("Initializing I2C devices... ");
    accelgyro.initialize();
    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
    Serial.printf("%d\n", accelgyro.testConnection());

    // configure Arduino LED pin for output
    pinMode(LED_PIN, OUTPUT);
}

void loop(void)
{
    u8g2.setFont(u8g2_font_unifont_t_chinese2);  // use chinese2 for all the glyphs of "你好世界"
    u8g2.setFontDirection(0);
    u8g2.clearBuffer();
    u8g2.setCursor(0, 15);
    u8g2.print("Hello World!");
    u8g2.setCursor(0, 40);
    u8g2.print("你好世界");        // Chinese "Hello World"
    /*
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    u8g2.setCursor(0, 60);
    u8g2.print("a/g:\t");
    u8g2.print(ax);
    u8g2.print("\t");
    u8g2.print(ay);
    u8g2.print("\t");
    u8g2.print(az);
    u8g2.print("\t");
    u8g2.print(gx);
    u8g2.print("\t");
    u8g2.print(gy);
    u8g2.print("\t");
    u8g2.print(gz);
    */
    u8g2.sendBuffer();
    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
    delay(500);
}
