#ifndef __cAPA102_H__
#define __cAPA102_H__
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define BOFFSET 1
#define GOFFSET 2
#define ROFFSET 3

#define BITRATE 32000000

/* Beware: you may need to change the formate here */
#define SPI_DEVICE "/dev/spidev%d.%d"

typedef struct{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}cAPA102_RGB;

typedef struct{
    uint8_t number;
    uint8_t spi_bus;
    uint8_t spi_dev;
    int     fd_spi;
    uint8_t *pixels;
    uint8_t brightness;
}cAPA102_LEDs;

/**
 * @brief Initialise a set of apa102 leds
 *
 * @param[in] num Number of leds (0-255)
 * @param[in] spi_bus SPI bus number (0-255)
 * @param[in] spi_dev SPI device number (0-255)
 * @param[in] brightness Initial brightness (0-31)
 *
 * @returns boolean
 *
 */
uint8_t cAPA102_Init(uint8_t num, uint8_t spi_bus, uint8_t spi_dev, uint8_t brightness);

/**
 * @brief Change the brightness and fresh
 *
 * @param[in] brightness Initial brightness
 */
void cAPA102_Change_Brightness(uint8_t brightness);

/**
 * @brief Change the brightness and fresh
 *
 * @return current brightness value (0-31)
 */
uint8_t cAPA102_Get_Brightness(void);

/**
 * @brief Set color for a specific pixel
 *
 * @param[in] index Index of the target led (0-255)
 * @param[in] red Intensity of red colour (0-255)
 * @param[in] green Intensity of green colour (0-255)
 * @param[in] blue Intensity of blue colour (0-255)
 *
 */
void cAPA102_Set_Pixel_RGB(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief Get colour form a specific pixel
 *
 * @param[in] index Index of the target led (0-255)
 *
 * @return RGB_colour structure with rgb colour value
 */
cAPA102_RGB* cAPA102_Get_Pixel_RGB(uint8_t index);

/**
 * @brief Set color for a specific pixel by using 4byte date
 *
 * @param[in] index Index of the target led (0-255)
 * @param[in] red Intensity of red colour (0-255)
 * @param[in] green Intensity of green colour (0-255)
 * @param[in] blue Intensity of blue colour (0-255)
 *
 */
void cAPA102_Set_Pixel_4byte(uint8_t index, uint32_t colour);

/**
 * @brief Get colour form a specific pixel
 *
 * @param[in] index Index of the target led (0-255)
 *
 * @return 32 bits colour data
 */
uint32_t cAPA102_Get_Pixel_4byte(uint8_t index);

/**
 * @brief Clear all the pixels
 *
 */
void cAPA102_Clear_All(void);

/**
 * @brief Refresh display (After modifing pixel colour or changing brightness)
 *
 */
void cAPA102_Refresh(void);

/**
 * @brief Close SPI file, release memory
 *
 */
void cAPA102_Close(void);

#endif