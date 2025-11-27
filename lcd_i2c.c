/* lcd_i2c.c */
#include "lcd_i2c.h"
#include <string.h>
#include <stdio.h>

static I2C_HandleTypeDef *lcd_i2c;

// Private functions
static void LCD_SendCmd(uint8_t cmd);
static void LCD_SendData(uint8_t data);
static void LCD_SendInternal(uint8_t data, uint8_t flags);
static void LCD_Write4Bits(uint8_t data);

void LCD_Init(I2C_HandleTypeDef *hi2c) {
    lcd_i2c = hi2c;

    HAL_Delay(50);

    // 4-bit initialization sequence
    LCD_Write4Bits(0x03 << 4);
    HAL_Delay(5);
    LCD_Write4Bits(0x03 << 4);
    HAL_Delay(5);
    LCD_Write4Bits(0x03 << 4);
    HAL_Delay(1);
    LCD_Write4Bits(0x02 << 4);

    // Function set: 4-bit, 2 lines, 5x8 dots
    LCD_SendCmd(LCD_FUNCTION_SET | LCD_4BIT_MODE | LCD_2LINE | LCD_5x8DOTS);

    // Display control: display on, cursor off, blink off
    LCD_SendCmd(LCD_DISPLAY_CTRL | LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINK_OFF);

    // Clear display
    LCD_Clear();

    // Entry mode: increment, no shift
    LCD_SendCmd(LCD_ENTRY_MODE | LCD_ENTRY_LEFT | LCD_ENTRY_SHIFT_DECREMENT);

    HAL_Delay(2);
}

void LCD_Clear(void) {
    LCD_SendCmd(LCD_CLEAR);
    HAL_Delay(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    if (row > 1) row = 1;
    LCD_SendCmd(LCD_SETDDRAM_ADDR | (col + row_offsets[row]));
}

void LCD_Print(char *str) {
    while(*str) {
        LCD_SendData(*str++);
    }
}

void LCD_PrintNum(int number) {
    char buffer[16];
    sprintf(buffer, "%d", number);
    LCD_Print(buffer);
}

static void LCD_SendCmd(uint8_t cmd) {
    LCD_SendInternal(cmd, 0);
}

static void LCD_SendData(uint8_t data) {
    LCD_SendInternal(data, Rs);
}

static void LCD_SendInternal(uint8_t data, uint8_t flags) {
    uint8_t high_nibble = data & 0xF0;
    uint8_t low_nibble = (data << 4) & 0xF0;

    uint8_t data_arr[4];
    data_arr[0] = high_nibble | flags | En | LCD_BACKLIGHT;
    data_arr[1] = high_nibble | flags | LCD_BACKLIGHT;
    data_arr[2] = low_nibble | flags | En | LCD_BACKLIGHT;
    data_arr[3] = low_nibble | flags | LCD_BACKLIGHT;

    HAL_I2C_Master_Transmit(lcd_i2c, LCD_ADDR, data_arr, 4, 100);
}

static void LCD_Write4Bits(uint8_t data) {
    uint8_t data_arr[2];
    data_arr[0] = data | En | LCD_BACKLIGHT;
    data_arr[1] = data | LCD_BACKLIGHT;
    HAL_I2C_Master_Transmit(lcd_i2c, LCD_ADDR, data_arr, 2, 100);
}
