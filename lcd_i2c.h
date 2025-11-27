/* lcd_i2c.h */
#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "stm32f4xx_hal.h"

// LCD I2C address (usually 0x27 or 0x3F, shifted left)
#define LCD_ADDR (0x27 << 1)

// Commands
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_ENTRY_MODE 0x04
#define LCD_DISPLAY_CTRL 0x08
#define LCD_CURSOR_SHIFT 0x10
#define LCD_FUNCTION_SET 0x20
#define LCD_SETCGRAM_ADDR 0x40
#define LCD_SETDDRAM_ADDR 0x80

// Flags for display entry mode
#define LCD_ENTRY_RIGHT 0x00
#define LCD_ENTRY_LEFT 0x02
#define LCD_ENTRY_SHIFT_INCREMENT 0x01
#define LCD_ENTRY_SHIFT_DECREMENT 0x00

// Flags for display on/off control
#define LCD_DISPLAY_ON 0x04
#define LCD_DISPLAY_OFF 0x00
#define LCD_CURSOR_ON 0x02
#define LCD_CURSOR_OFF 0x00
#define LCD_BLINK_ON 0x01
#define LCD_BLINK_OFF 0x00

// Flags for function set
#define LCD_8BIT_MODE 0x10
#define LCD_4BIT_MODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// Backlight
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

// Enable bit
#define En 0x04
#define Rw 0x02
#define Rs 0x01

// Function prototypes
void LCD_Init(I2C_HandleTypeDef *hi2c);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Print(char *str);
void LCD_PrintNum(int number);

#endif /* LCD_I2C_H */
