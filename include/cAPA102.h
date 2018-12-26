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

typedef struct{
    uint8_t number;
    uint8_t spi_bus;
    uint8_t spi_dev;
    int     fd_spi;
    uint8_t *pixels;
    uint8_t brightness;
}APA102;

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
void cAPA102_change_brightness(uint8_t brightness);

/**
 * @brief Set color for a specific pixel
 *
 * @param[in] index Index of the target led (0-255)
 * @param[in] red Intensity of red colour (0-255)
 * @param[in] green Intensity of green colour (0-255)
 * @param[in] blue Intensity of blue colour (0-255)
 *
 */
void cAPA102_set_pixel_rgb(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief Set color for a specific pixel by using 4byte date
 *
 * @param[in] index Index of the target led (0-255)
 * @param[in] red Intensity of red colour (0-255)
 * @param[in] green Intensity of green colour (0-255)
 * @param[in] blue Intensity of blue colour (0-255)
 *
 */
void cAPA102_set_pixel_4byte(uint8_t index, uint32_t colour);

/**
 * @brief Clear all the pixels
 *
 */
void cAPA102_clear_all(void);

/**
 * @brief Refresh display (After modifing pixel colour or changing brightness)
 *
 */
void cAPA102_refresh(void);

/**
 * @brief Close SPI file, release memory
 *
 */
void cAPA102_close(void);

#endif