/* Copyright (C) 2018 Arribada
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _BSP_H_
#define _BSP_H_

#include "stm32f0xx_hal.h"

// Logical device mappings to physical devices
#define GPS_UART        UART_1
#define PRINTF_UART     UART_2 // This is used by debug.c/h
#define I2C_AXL         I2C_2
#define I2C_BATTERY     I2C_2
#define I2C_PRESSURE    I2C_1
#define SPI_BLE         SPI_1
#define SPI_FLASH       SPI_2

///////////////////////////////// GPIO definitions ////////////////////////////////
typedef enum
{
    GPIO_SPARE_GPIO,
    GPIO_1PPS,
    GPIO_1,
    GPIO_2,
    GPIO_3,
    GPIO_VUSB,
    GPIO_SWS,
    GPIO_REED_SW,
    GPIO_SPI1_CS_BT,
    GPIO_SPI2_CS_ARG,
    GPIO_SPI2_CS_FLASH,
    GPIO_GPOUT,
    GPIO_BT_GPIO,
    GPIO_USB_ID,
    GPIO_AUX_EN,
    GPIO_LED1_GREEN,
    GPIO_LED2_RED,
    GPIO_DRDY_M,
    GPIO_INT_M,
    GPIO_DEN_AG,
    GPIO_INT1_AG,
    GPIO_INT2_AG,
    GPIO_UART1_TX,
    GPIO_UART1_RX,
    GPIO_UART2_TX,
    GPIO_UART3_TX,
    GPIO_UART3_RX,
    GPIO_UART3_RTS,
    GPIO_UART3_CTS,
    GPIO_I2C1_SCL,
    GPIO_I2C1_SDA,
    GPIO_I2C2_SCL,
    GPIO_I2C2_SDA,
    GPIO_SPI1_SCK,
    GPIO_SPI1_MISO,
    GPIO_SPI1_MOSI,
    GPIO_SPI2_SCK,
    GPIO_SPI2_MISO,
    GPIO_SPI2_MOSI,
    GPIO_TOTAL_NUMBER
} GPIO_Pins_t;

// Merge port number and init structure
typedef struct
{
    GPIO_TypeDef * Port;
    GPIO_InitTypeDef Init;
} GPIO_InitTypeDefAndPort_t;

extern GPIO_InitTypeDefAndPort_t GPIO_Inits[GPIO_TOTAL_NUMBER];

///////////////////////////////// SPI definitions /////////////////////////////////
#define SPI_TIMEOUT 1000

typedef enum
{
    SPI_1,
    SPI_2,
    SPI_TOTAL_NUMBER
} SPI_t;

typedef struct
{
    SPI_TypeDef * Instance;
    SPI_InitTypeDef Init;
} SPI_InitTypeDefAndInst_t;

extern const SPI_InitTypeDefAndInst_t SPI_Inits[SPI_TOTAL_NUMBER];

///////////////////////////////// I2C definitions /////////////////////////////////
#define I2C_TIMEOUT 1000

typedef enum
{
    I2C_1,
    I2C_2,
    I2C_TOTAL_NUMBER
} I2C_t;

typedef struct
{
    I2C_TypeDef * Instance;
    I2C_InitTypeDef Init;
} I2C_InitTypeDefAndInst_t;

extern const I2C_InitTypeDefAndInst_t I2C_Inits[I2C_TOTAL_NUMBER];

///////////////////////////////// UART definitions ////////////////////////////////
#define UART_TIMEOUT 1000

#define UART_RX_BUF_SIZE 128

#define UART_1_DESTRUCTIVE_INSERT // DO overwrite values we've received if the rx buffer overflows
#define UART_2_SAFE_INSERT // do NOT overwrite values we've received if the rx buffer overflows
#define UART_3_SAFE_INSERT // do NOT overwrite values we've received if the rx buffer overflows

typedef enum
{
    UART_1,
    UART_2,
    UART_3,
    UART_TOTAL_NUMBER
} UART_t;

typedef struct
{
    USART_TypeDef * Instance;
    UART_InitTypeDef Init;
} UART_InitTypeDefAndInst_t;

extern const UART_InitTypeDefAndInst_t UART_Inits[UART_TOTAL_NUMBER];

extern IWDG_HandleTypeDef IWDG_Init;

///////////////////////////////// USB definitions /////////////////////////////////


//////////////////////////////// FLASH definitions ////////////////////////////////
#define FS_DEVICE (0)

#endif /* _BSP_H_ */
