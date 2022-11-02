#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define bg_height   128
#define bg_width    64
#define bitmap_height   128
#define bitmap_width    64
String cardPick = "";
// 'istockphoto-92135269-612x612', 128x64px
static const unsigned char PROGMEM bg[] = {
	0xff, 0xf0, 0x00, 0x06, 0x80, 0x00, 0x3e, 0x01, 0xfe, 0x00, 0x07, 0xff, 0xf0, 0x1e, 0x00, 0x00, 
	0xfe, 0x80, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x01, 0xff, 0x00, 0x03, 0xff, 0xf8, 0x7c, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x02, 0x20, 0x01, 0xf8, 0x00, 0x07, 0x00, 0x10, 0xff, 0xe4, 0x38, 0x00, 0x00, 
	0xf8, 0x04, 0x00, 0x77, 0x38, 0x01, 0xc0, 0x00, 0x02, 0x00, 0x04, 0x7f, 0xe2, 0x20, 0x00, 0x00, 
	0xfd, 0x60, 0x00, 0x73, 0x38, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x3f, 0xc2, 0x00, 0x00, 0x00, 
	0xfc, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x1f, 0x80, 0x80, 0x10, 0x00, 
	0xfc, 0x02, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0xe0, 0x0f, 0x00, 0x00, 0x3c, 0x00, 
	0xf8, 0x00, 0x00, 0x03, 0x83, 0x80, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x07, 0x00, 0x00, 0x1c, 0x00, 
	0xf8, 0x00, 0x60, 0x03, 0x83, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x0c, 0x00, 
	0xf8, 0x00, 0x08, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x10, 0x00, 0x00, 
	0xf8, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x40, 0x00, 0x00, 
	0xf8, 0x00, 0x01, 0x80, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xf8, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x18, 0x00, 
	0xf8, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 
	0xf8, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xfe, 0x00, 
	0xf8, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 
	0x78, 0x00, 0xe0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x03, 0xff, 0xc0, 
	0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x07, 0xff, 0xe0, 
	0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x1b, 0x8f, 0xff, 0xf0, 
	0x00, 0x01, 0x81, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x03, 0x9f, 0xff, 0xf8, 
	0x00, 0x06, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x3f, 0xff, 0xf8, 
	0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x7f, 0xff, 0xf0, 
	0x80, 0x04, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0xff, 0xff, 0xe0, 
	0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc1, 0xff, 0xff, 0xc0, 
	0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc3, 0x1f, 0xff, 0xc0, 
	0x00, 0x30, 0x1c, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x0f, 0xff, 0x00, 
	0x00, 0x38, 0x1c, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x00, 
	0x00, 0x1e, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfc, 0x01, 
	0x00, 0x0f, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x03, 
	0x00, 0x03, 0x80, 0x00, 0x3f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x07, 
	0x00, 0x01, 0xc0, 0x00, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0f, 
	0x00, 0x00, 0x00, 0x03, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 
	0x00, 0x00, 0x00, 0x0f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 
	0x00, 0x00, 0x00, 0x0f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 
	0x00, 0x00, 0x00, 0x07, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 
	0x00, 0x00, 0x00, 0x83, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 
	0x00, 0x00, 0x00, 0x81, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0xe0, 0x00, 
	0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 
	0x00, 0x00, 0x00, 0x60, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xe0, 0x00, 
	0x00, 0x00, 0x00, 0x70, 0x7f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x63, 0x80, 
	0x00, 0x00, 0x00, 0x30, 0x3f, 0xf8, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x6f, 0x03, 0xc0, 
	0x00, 0x00, 0x00, 0x38, 0x3f, 0xe0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x03, 0xc0, 
	0x00, 0x00, 0x00, 0x18, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x03, 0xc0, 
	0x00, 0x00, 0x00, 0x18, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x02, 0x00, 
	0x00, 0x00, 0x00, 0x06, 0x1c, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x02, 0x00, 
	0x00, 0x00, 0x00, 0x06, 0x1c, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x1f, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0x1c, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x81, 0x00, 
	0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0xff, 0xc0, 0xe0, 
	0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x78, 0x00, 0x7f, 0xff, 0xc0, 0xe0, 
	0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x10, 0x1c, 0x00, 0x03, 0xf8, 0x00, 0x7f, 0xff, 0xe0, 0x70, 
	0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x10, 0x1f, 0xe0, 0x0f, 0xf8, 0x00, 0x7f, 0xff, 0xe0, 0x70
};

static const unsigned char PROGMEM bitmap[] =
{ 0xff, 0xff, 0xe0, 0x06, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xf1, 0x08, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 
	0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 
	0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 
	0xff, 0xff, 0xff, 0xff, 0xf4, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf8, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1d, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 
	0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x11, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0xe4, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 
	0xff, 0xff, 0xff, 0xff, 0xf7, 0xe0, 0xe5, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4f, 0xe0, 
	0xff, 0xff, 0xff, 0xff, 0xf7, 0xc0, 0x65, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xef, 0xf0, 
	0xff, 0xff, 0xff, 0xdf, 0xf7, 0xc7, 0xf5, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0x07, 0xdf, 0xef, 0xf8, 
	0xff, 0xff, 0xff, 0xbf, 0xf7, 0xdf, 0xfd, 0xe0, 0x00, 0x00, 0x00, 0xa8, 0x07, 0xdf, 0xcf, 0xfc, 
	0xff, 0xff, 0xff, 0xbf, 0xf7, 0xdf, 0xe7, 0xf0, 0x00, 0x00, 0x00, 0xe8, 0x47, 0x9f, 0xcf, 0xfc, 
	0xff, 0xff, 0xff, 0xff, 0xf7, 0xfe, 0x6f, 0xf0, 0x00, 0x00, 0x00, 0xc9, 0xc7, 0x1f, 0xcf, 0xfd, 
	0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0x5b, 0xf1, 0xe0, 0x00, 0x02, 0xf8, 0x0e, 0xdf, 0xdf, 0xfd, 
	0xff, 0xff, 0xff, 0xff, 0xf7, 0xf7, 0xd3, 0xff, 0xf8, 0x00, 0x02, 0xf8, 0x4f, 0xdf, 0xdf, 0xfd, 
	0xff, 0xff, 0xff, 0xff, 0xf5, 0xf7, 0xf3, 0xf8, 0xfc, 0x00, 0x02, 0xc8, 0x4f, 0xdf, 0xdf, 0xf9, 
	0xff, 0xff, 0xf0, 0xff, 0xf0, 0xf7, 0xf7, 0x80, 0xfc, 0x00, 0x02, 0xc8, 0xcf, 0xdf, 0xff, 0xf9, 
	0xff, 0xff, 0xf0, 0xfb, 0x70, 0xf7, 0xf7, 0xd1, 0xf8, 0x00, 0x06, 0xe8, 0xcf, 0xdf, 0xdf, 0xf9, 
	0xff, 0xff, 0xf0, 0xfa, 0x30, 0xf7, 0xff, 0x80, 0xf0, 0x00, 0x06, 0xf8, 0xcf, 0xdf, 0xdf, 0xf9, 
	0xff, 0xff, 0xf0, 0xfe, 0x00, 0xf7, 0xff, 0xf9, 0xe0, 0x00, 0x02, 0xc8, 0x4f, 0xdf, 0xdf, 0xf8, 
	0xff, 0xff, 0xf0, 0xe3, 0x02, 0xc7, 0xff, 0xff, 0xe3, 0x80, 0x06, 0xc8, 0x4f, 0xdf, 0xdf, 0xf8, 
	0xff, 0xff, 0xf0, 0x67, 0x01, 0x97, 0xff, 0xff, 0xe3, 0xc0, 0x06, 0xc8, 0x4f, 0xdf, 0xdf, 0xf0, 
	0xef, 0xff, 0xf0, 0x70, 0x06, 0x1f, 0xff, 0xff, 0xe3, 0xf0, 0x06, 0x48, 0x0f, 0x9f, 0xdf, 0xf8, 
	0xff, 0xff, 0xf0, 0xfa, 0x10, 0x9f, 0xff, 0xff, 0xe3, 0xf0, 0x06, 0x58, 0x0f, 0x9f, 0xc7, 0xf0, 
	0xbf, 0xff, 0xf8, 0xfe, 0x21, 0xbf, 0xff, 0xff, 0xe1, 0xf0, 0x06, 0x48, 0x0f, 0x9f, 0x87, 0xf0, 
	0xff, 0xff, 0xf8, 0xe3, 0x30, 0x7f, 0xf7, 0xff, 0xe0, 0xe0, 0x06, 0x48, 0x07, 0x8f, 0x87, 0xe0, 
	0xdf, 0xff, 0xf8, 0xfe, 0x00, 0x1f, 0xe7, 0xdf, 0x80, 0xe0, 0x02, 0x08, 0x03, 0x9f, 0xc7, 0xe4, 
	0x1f, 0xff, 0xf8, 0xfe, 0x00, 0x2f, 0xe7, 0xbf, 0xc0, 0xe1, 0x02, 0x0c, 0x1b, 0x9f, 0x07, 0xf8, 
	0xbf, 0xff, 0xf8, 0xfc, 0x00, 0x01, 0xe7, 0xff, 0xf0, 0xc7, 0x00, 0x01, 0xf9, 0x9f, 0x07, 0xf4, 
	0xff, 0xff, 0xf8, 0xfc, 0x00, 0x07, 0xff, 0xf8, 0x00, 0xc7, 0x00, 0x21, 0xf8, 0x1e, 0x07, 0xfe, 
	0x1f, 0xff, 0xf8, 0xd8, 0x00, 0x05, 0xff, 0xff, 0xc0, 0xc7, 0x80, 0x01, 0xf8, 0x38, 0x01, 0xfe, 
	0x1f, 0xff, 0xf8, 0x30, 0x00, 0x3f, 0xdf, 0xff, 0xc1, 0x8f, 0xc0, 0x06, 0xb0, 0x30, 0xe0, 0x04, 
	0x0f, 0xff, 0xf8, 0xf0, 0x00, 0x3f, 0x67, 0xff, 0xe7, 0x1f, 0xd8, 0x8b, 0x20, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xf8, 0x60, 0x00, 0x3c, 0xcf, 0xff, 0xfe, 0x1f, 0x3f, 0x63, 0x20, 0x00, 0x00, 0x08, 
	0xff, 0xff, 0xf8, 0xe0, 0x00, 0x3b, 0xf7, 0xff, 0xf0, 0x3e, 0x7c, 0x55, 0xf0, 0x00, 0x08, 0x38, 
	0xff, 0xff, 0xf8, 0x40, 0x00, 0x3f, 0xef, 0xff, 0xf0, 0x3f, 0xf0, 0x73, 0x80, 0x00, 0x18, 0x44, 
	0xff, 0xff, 0xf8, 0x60, 0x00, 0x7f, 0x9f, 0xff, 0xe0, 0x3f, 0x91, 0xcb, 0xa0, 0x00, 0x78, 0x44, 
	0xff, 0xff, 0xf8, 0x60, 0x00, 0x78, 0x0f, 0xf8, 0x00, 0x7f, 0xfe, 0xe4, 0xf0, 0x06, 0x70, 0x06, 
	0xff, 0xff, 0xf8, 0x60, 0x00, 0x40, 0x0f, 0xfc, 0x00, 0x7f, 0xfb, 0x03, 0xff, 0xff, 0x70, 0x07, 
	0xff, 0xff, 0xf8, 0x20, 0x00, 0x00, 0x0f, 0xff, 0x80, 0x3f, 0xff, 0x05, 0xff, 0xf1, 0x70, 0x03, 
	0xff, 0xff, 0xf8, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x0f, 0xf6, 0x01, 0xff, 0xe8, 0x70, 0x01, 
	0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x03, 0xf4, 0x41, 0xff, 0xf8, 0x70, 0x01, 
	0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x03, 0xff, 0x80, 0x01, 0xf6, 0x00, 0x7d, 0xf8, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0x90, 0x00, 0x00, 0x00, 0xff, 0x80, 0x00, 0x34, 0x00, 0x7f, 0xfe, 0x00, 0x00, 
	0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xd0, 0x00, 0x02, 0x00, 0x1f, 0x40, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x01, 0x00, 0x07, 0xe0, 0x00, 0x03, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x0f, 
	0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x01, 
	0x1f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x01, 
	0x1f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x61, 
	0x1f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x40, 
	0xdf, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x00, 0xc0, 
	0x7f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x00, 0xe0, 
	0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x00, 0xa1, 
	0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x70, 0x01, 0xa0, 
	0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x70, 0x00, 0xa1 };

/*
SET UP FOR BLACKJACK: ADJUST FOR POKER
*/
int currCard = 2;
int playerdisplay = 1;
int total1 = 0;
int total2 = 0;
int total3 = 0;
int total4 = 0;
int suitval = 0;
int currentPlayerTotal = 0;
int currentPlayer = 1;
String suits[4] = {" Clubs", " Diamonds", " Hearts", " Spades"};
String cards[4][13] = {
  {"1" + suits[0], "2" + suits[0], "3" + suits[0], "4" + suits[0], "5" + suits[0], "6" + suits[0], "7" + suits[0], "8" + suits[0], "9" + suits[0], "10" + suits[0], "11" + suits[0], "12" + suits[0], "13" + suits[0]},
  {"1" + suits[1], "2" + suits[1], "3" + suits[1], "4" + suits[1], "5" + suits[1], "6" + suits[1], "7" + suits[1], "8" + suits[1], "9" + suits[1], "11" + suits[1], "11" + suits[1], "12" + suits[1], "13" + suits[1]},
  {"1" + suits[2], "2" + suits[2], "3" + suits[2], "4" + suits[2], "5" + suits[2], "6" + suits[2], "7" + suits[2], "8" + suits[2], "9" + suits[2], "12" + suits[2], "11" + suits[2], "12" + suits[2], "13" + suits[2]},
  {"1" + suits[3], "2" + suits[3], "3" + suits[3], "4" + suits[3], "5" + suits[3], "6" + suits[3], "7" + suits[3], "8" + suits[3], "9" + suits[3], "13" + suits[3], "11" + suits[3], "12" + suits[3], "13" + suits[3]}
};
int checker[4][13] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0}
};
int drawCard(){
  bool badDraw = true;
  while(badDraw == true){
      suitval = 0 + (rand() % static_cast<int>(3 - 0 + 1));
int cardval = 0 + (rand() % static_cast<int>(12 - 0 + 1));
if(checker[suitval][cardval] == 0){
Serial.println(cards[suitval][cardval]);
checker[suitval][cardval] = 1;
badDraw = false;
if(cardval > 9){
  if(cardval == 10){
    cardPick = "J";
  }
   if(cardval == 11){
    cardPick = "Q";
  }
   if(cardval == 12){
    cardPick = "K";
  }
  return 10;
}
else if(cardval> 0){
  cardPick = cardval + 1;
  return cardval += 1;
}
else{
  cardPick = "A";
  return 21;
}
}
  continue;
}
}
int turn = 0;
const int hitButtonPin = 2;
int hitButtonState = 0;
const int standButtonPin = 3;
int standButtonState = 0;
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display2.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  srand(analogRead(0));
  pinMode(hitButtonPin, INPUT);
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display2.clearDisplay();

    display.drawBitmap(0, 0, bitmap, bitmap_height, bitmap_width, WHITE);
    display2.drawBitmap(0, 0, bitmap, bitmap_height, bitmap_width, WHITE);
  display.display();
  display2.display();
  delay(2000);
  display.clearDisplay();
  display2.clearDisplay();
  for(int x=1; x<=2; x++){
    playerdisplay = x;
  int playertotal = drawTwo(x);
  display.display();
  display2.display();
  Serial.print("PLAYER ");
  Serial.print(x);
  Serial.print(" TOTAL:");
  Serial.println(playertotal);
  if(x == 1){
  total1 = playertotal;
  }
  if(x == 2){
  total2 = playertotal;
  }
  if(x == 3){
  total3 = playertotal;
  }
  if(x == 4){
  total4 = playertotal;
  }
   Serial.println("-------------------------------------");
  }
  playerdisplay = 1;
}
int standButtonPressed = 0;
int hitButtonPressed = 0;
bool inPlay = false;
void loop(){
if(currentPlayer == 1 && inPlay == false){
  currentPlayerTotal = total1;
}
if(currentPlayer == 2 && inPlay == false){
  currentPlayerTotal = total2;
}
if(currentPlayer == 1 && inPlay == true){
  total1  = currentPlayerTotal;
}
if(currentPlayer == 2 && inPlay == true){
  total2  = currentPlayerTotal;
}
hitButtonState = digitalRead(hitButtonPin);
if(hitButtonState == HIGH && hitButtonPressed == 0){
  hitButtonPressed = 1; 
  int nTotal = hit(currentPlayerTotal);
  currentPlayerTotal = nTotal;
  inPlay = true;
}
if(hitButtonState == LOW && hitButtonPressed == 1){
  hitButtonPressed = 0;
}
standButtonState = digitalRead(standButtonPin);
if(standButtonState == HIGH && standButtonPressed == 0){
  standButtonPressed = 1; 
  stand(currentPlayerTotal);
}
if(standButtonState == LOW && standButtonPressed == 1){
  standButtonPressed = 0;
}

if(currentPlayer < 3){
bust(currentPlayerTotal);
}

}

int drawTwo(int player){
  int total = 0;
  Serial.print("PLAYER ");
  Serial.print(player);
  Serial.println(" HAND:");
  for(int x=0; x<2; x++){
  int draw = drawCard();
  giveCard(x);
  total += draw;
}
if(total > 21){
  total -= 20;
  if(total == 11){
    total = 21;
  }
}

 return total;
}
void tableDraw(){
  
    for(int x=0; x<3; x++){
    drawCard();
    }
if(turn == 1){
  for(int x=0; x<2; x++){
    int badDraw = drawCard();
    if(badDraw > 0){
      x -= 1;
    }
  }
}
if(turn == 2){
  for(int x=0; x<2; x++){
    int badDraw = drawCard();
    if(badDraw > 0){
      x -= 1;
    }
  }
}
}
void bust(int total){
  if(playerdisplay == 1){
if(total > 21){
  Serial.print("Bust! You broke now. ¯\_(ツ)_/¯");
  currentPlayer += 1;
  playerdisplay += 1;
  currCard = 2;
  inPlay = false;
  display.clearDisplay();
  display.drawBitmap(0, 0, bg, bg_height, bg_width, WHITE);
  display.setCursor(55, 35);
  display.print("BUST"); 
  display.display();
  return;
}
} 
if(playerdisplay == 2){
  if(total > 21){
  Serial.print("Bust! You broke now. ¯\_(ツ)_/¯");
  currentPlayer += 1;
  playerdisplay += 1;
  currCard = 2;
  inPlay = false;
  display2.clearDisplay();
  display2.drawBitmap(0, 0, bg, bg_height, bg_width, WHITE);
  display2.setCursor(55, 35);
  display2.print("BUST"); 
  display2.display();
  return;
}
}
}
int hit(int total){
  if(total != 21){
    int hitCard = drawCard();
    if(hitCard == 21){
      if((total + 11) > 21){
        hitCard = 1;
      }
      else{
        hitCard = 11;
      }
    }
    Serial.print("HIT: CARD DRAWN ");
    Serial.println(hitCard);
    total += hitCard;
    Serial.print("NEW TOTAL: ");
    Serial.println(total);
    drawNewCard(currCard);
    currCard += 1;
    return total;
  }
}
void drawNewCard(int card){
  if(playerdisplay == 1){
  int x = card * 32;
  display.drawRoundRect(0 + x, 20, 30, 40, 5, WHITE);
  if(suitval == 0){
    card1ClubD1(x);
  }
  if(suitval == 1){
    card1DiamondD1(x);
  }
  if(suitval == 2){
    card1HeartD1(x);
  }
  if(suitval == 3){
    card1SpadeD1(x);
  }
  c1ValD1(x);

  display.display();
   }
   if(playerdisplay == 2){
  int x = card * 32;
  display2.drawRoundRect(0 + x, 20, 30, 40, 5, WHITE);
  if(suitval == 0){
    card1ClubD2(x);
  }
  if(suitval == 1){
    card1DiamondD2(x);
  }
  if(suitval == 2){
    card1HeartD2(x);
  }
  if(suitval == 3){
    card1SpadeD2(x);
  }
  c1ValD2(x);
  display2.display();
}
}
void stand(int total){
  if(playerdisplay == 1){
  if(total < 22){
  Serial.print("STAND: PLAYER ");
  Serial.print(currentPlayer);
  Serial.print(" FINAL TOTAL:");
  Serial.print(total);
  display.clearDisplay();
  display.drawBitmap(0, 0, bg, bg_height, bg_width, WHITE);
   display.setTextSize(3); 
  display.setCursor(55, 35);
  display.print(total);
   display.setTextSize(1); 
    display.setCursor(43, 15);
    display.write("STAND:");
     display.setTextSize(2); 
  display.display();
  playerdisplay += 1;
  currentPlayer += 1;
  currCard = 2;
  inPlay = false;
  return;
  }
}
  if(playerdisplay == 2){
  if(total < 22){
  Serial.print("STAND: PLAYER ");
  Serial.print(currentPlayer);
  Serial.print(" FINAL TOTAL:");
  Serial.print(total);
  display2.clearDisplay();
  display2.drawBitmap(0, 0, bg, bg_height, bg_width, WHITE);
   display2.setTextSize(3); 
  display2.setCursor(55, 35);
  display2.print(total);
   display2.setTextSize(1); 
    display2.setCursor(43, 15);
    display2.write("STAND:");
     display2.setTextSize(2); 
  display2.display();
  playerdisplay += 1;
  currentPlayer += 1;
  currCard = 2;
  inPlay = false;
  return;
  }
}
}
void compareToHouse(){
  
}
void testdrawchar(void) {
  display.clearDisplay();

  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 30);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  // for(int16_t i=0; i<256; i++) {
  //   if(i == '\n') display.write(' ');
  //   else          display.write(i);
  // }
  display.write("HOLY MOLY GUACAMOLE");
  display.display();
  delay(2000);
}

void card1HeartD1(int x){  //THIS HEART SUCKS BUT I CANT DO ANY BETTER RN
   display.fillCircle(43 - 32 + x, 28, 4, WHITE);
  display.fillCircle(52 - 32 + x, 28, 4, WHITE);
  display.fillTriangle(39 - 32 + x, 30, 56 - 32 + x, 30, 47 - 32 + x, 39, WHITE);
}
void card1DiamondD1(int x){
display.fillTriangle(45 - 32 + x, 30, 55 - 32 + x, 30, 50 - 32 + x, 38, WHITE);
display.fillTriangle(45 - 32 + x, 29, 55 - 32 + x, 29, 50 - 32 + x, 22, WHITE);
}
void card2DiamondD1(){
display.fillTriangle(85, 30, 95, 30, 90, 38, WHITE);
display.fillTriangle(85, 29, 95, 29, 90, 22, WHITE);
}
void card1ClubD1(int x){
	display.fillCircle(50 - 32 + x, 24, 3, WHITE);
	display.fillCircle(46 - 32 + x, 30, 3, WHITE);
	display.fillCircle(54 - 32 + x, 30, 3, WHITE);
	display.fillTriangle(48 - 32 + x, 37, 52 - 32 + x, 37, 50 - 32 + x, 26, WHITE);
}
// void card2ClubD1(){
// 	display.fillCircle(90, 24, 3, WHITE);
// 	display.fillCircle(86, 30, 3, WHITE);
// 	display.fillCircle(94, 30, 3, WHITE);
// 	display.fillTriangle(88, 37, 92, 37, 90, 26, WHITE);
// }
void card1SpadeD1(int x){
	display.fillTriangle(48 - 32 + x, 37, 52 - 32 + x, 37, 50 - 32 + x, 26, WHITE);
	display.fillTriangle(44 - 32 + x, 30, 56 - 32 + x, 30, 50 - 32 + x, 22, WHITE);
	display.fillCircle(46 - 32 + x, 30, 3, WHITE);
	display.fillCircle(54 - 32 + x, 30, 3, WHITE);
}
// void card2SpadeD1(){
// 	display.fillTriangle(88, 37, 92, 37, 90, 26, WHITE);
// 	display.fillTriangle(84, 30, 96, 30, 90, 22, WHITE);
// 	display.fillCircle(86, 30, 3, WHITE);
// 	display.fillCircle(94, 30, 3, WHITE);
// }
// void card2HeartD1(){  //THIS HEART SUCKS BUT I CANT DO ANY BETTER RN
//    display.fillCircle(83, 28, 4, WHITE);
//   display.fillCircle(92, 28, 4, WHITE);
//   display.fillTriangle(79, 30, 96, 30, 87, 39, WHITE);
// }

void c1ValD1(int x){
   display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(35 - 32 + x, 42);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.print(cardPick);
}
// void c2ValD1(){
//    display.setTextSize(2);      // Normal 1:1 pixel scale
//   display.setTextColor(WHITE); // Draw white text
//   display.setCursor(75, 42);     // Start at top-left corner
//   display.cp437(true);         // Use full 256 char 'Code Page 437' font
//   display.print(cardPick);
// }
void card1HeartD2(int x){  //THIS HEART SUCKS BUT I CANT DO ANY BETTER RN
   display2.fillCircle(43 - 32 + x, 28, 4, WHITE);
  display2.fillCircle(52 - 32 + x, 28, 4, WHITE);
  display2.fillTriangle(39 - 32 + x, 30, 56 - 32 + x, 30, 47 - 32 + x, 39, WHITE);
}
void card1DiamondD2(int x){
display2.fillTriangle(45 - 32 + x, 30, 55 - 32 + x, 30, 50 - 32 + x, 38, WHITE);
display2.fillTriangle(45 - 32 + x, 29, 55 - 32 + x, 29, 50 - 32 + x, 22, WHITE);
}
// void card2DiamondD2(){
// display2.fillTriangle(85, 30, 95, 30, 90, 38, WHITE);
// display2.fillTriangle(85, 29, 95, 29, 90, 22, WHITE);
// }
void card1ClubD2(int x){
	display2.fillCircle(50 - 32 + x, 24, 3, WHITE);
	display2.fillCircle(46 - 32 + x, 30, 3, WHITE);
	display2.fillCircle(54 - 32 + x, 30, 3, WHITE);
	display2.fillTriangle(48 - 32 + x, 37, 52 - 32 + x, 37, 50 - 32 + x, 26, WHITE);
}
// void card2ClubD2(){
// 	display2.fillCircle(90, 24, 3, WHITE);
// 	display2.fillCircle(86, 30, 3, WHITE);
// 	display2.fillCircle(94, 30, 3, WHITE);
// 	display2.fillTriangle(88, 37, 92, 37, 90, 26, WHITE);
// }
void card1SpadeD2(int x){
	display2.fillTriangle(48 - 32 + x, 37, 52 - 32 + x, 37, 50 - 32 + x, 26, WHITE);
	display2.fillTriangle(44 - 32 + x, 30, 56 - 32 + x, 30, 50 - 32 + x, 22, WHITE);
	display2.fillCircle(46 - 32 + x, 30, 3, WHITE);
	display2.fillCircle(54 - 32 + x, 30, 3, WHITE);
}
// void card2SpadeD2(){
// 	display2.fillTriangle(88, 37, 92, 37, 90, 26, WHITE);
// 	display2.fillTriangle(84, 30, 96, 30, 90, 22, WHITE);
// 	display2.fillCircle(86, 30, 3, WHITE);
// 	display2.fillCircle(94, 30, 3, WHITE);
// }
// void card2HeartD2(){  //THIS HEART SUCKS BUT I CANT DO ANY BETTER RN
//    display2.fillCircle(83, 28, 4, WHITE);
//   display2.fillCircle(92, 28, 4, WHITE);
//   display2.fillTriangle(79, 30, 96, 30, 87, 39, WHITE);
// }

void c1ValD2(int x){
   display2.setTextSize(2);      // Normal 1:1 pixel scale
  display2.setTextColor(WHITE); // Draw white text
  display2.setCursor(35 - 32 + x, 42);     // Start at top-left corner
  display2.cp437(true);         // Use full 256 char 'Code Page 437' font
  display2.print(cardPick);
}
// void c2ValD2(){
//    display2.setTextSize(2);      // Normal 1:1 pixel scale
//   display2.setTextColor(WHITE); // Draw white text
//   display2.setCursor(75, 42);     // Start at top-left corner
//   display2.cp437(true);         // Use full 256 char 'Code Page 437' font
//   display2.print(cardPick);
// }
void giveCard(int drawn){
  if(playerdisplay == 1){
    int x = drawn * 32;
  display.drawRoundRect(0 + x, 20, 30, 40, 5, WHITE);
  if(suitval == 0){
    card1ClubD1(x);
  }
  if(suitval == 1){
    card1DiamondD1(x);
  }
  if(suitval == 2){
    card1HeartD1(x);
  }
  if(suitval == 3){
    card1SpadeD1(x);
  }
  c1ValD1(x);
}
if (playerdisplay == 2){
    int x = drawn * 32;
  display2.drawRoundRect(0 + x, 20, 30, 40, 5, WHITE);
  if(suitval == 0){
    card1ClubD2(x);
  }
  if(suitval == 1){
    card1DiamondD2(x);
  }
  if(suitval == 2){
    card1HeartD2(x);
  }
  if(suitval == 3){
    card1SpadeD2(x);
  }
  c1ValD2(x);
}
}
#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2

