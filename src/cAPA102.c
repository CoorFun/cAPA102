#include "cAPA102.h"

static cAPA102_LEDs cAPA012_BUF = {0, 0, 0, -1, NULL, 31};

/**
 * @brief: Try to open the SPI device by given times
 *
 * @param[in] retry_times
 * @param[in] retry_gap_sec:
 *
 * @returns: \The file descriptor of SPI device or \-1 error
 *
 */
static int cAPA102_Try_Open_SPI_Dev(uint8_t retry_times, uint8_t retry_gap_sec);

/**
 * @brief Open the SPI device file
 *
 * @returns \The file descriptor of SPI device or \-1 error
 *
 */
static int cAPA102_Open_SPI_Dev(void);

int cAPA102_Init(uint32_t led_num, uint8_t spi_bus, uint8_t spi_dev, uint8_t brightness){
    cAPA012_BUF.number = led_num;
    cAPA012_BUF.spi_bus = spi_bus;
    cAPA012_BUF.spi_dev = spi_dev;
    cAPA012_BUF.brightness = brightness;
    cAPA012_BUF.pixels = (uint8_t *)malloc(cAPA012_BUF.number * 4);
    cAPA012_BUF.fd_spi = cAPA102_Try_Open_SPI_Dev(RETRY_TIMES, RETRY_GAP_SEC);
    cAPA102_Clear_All();
}

void cAPA102_Change_Brightness(uint8_t brightness){
    cAPA012_BUF.brightness = brightness;
}

int cAPA102_Get_Brightness(void){
    return cAPA012_BUF.brightness;
}

void cAPA102_Set_Pixel_RGB(uint32_t index, uint8_t red, uint8_t green, uint8_t blue){
    if (index < cAPA012_BUF.number) {
        uint8_t *ptr = &cAPA012_BUF.pixels[index * 4];
        ptr[R_OFF_SET] = red;
        ptr[G_OFF_SET] = green;
        ptr[B_OFF_SET] = blue;
    }
}


void cAPA102_Get_Pixel_RGB(uint32_t index, uint8_t *red, uint8_t *green, uint8_t *blue){
    if (index < cAPA012_BUF.number) {
        uint8_t *ptr = &cAPA012_BUF.pixels[index * 4];
        red = ptr + R_OFF_SET; //ptr[R_OFF_SET];
        green = ptr + G_OFF_SET; //ptr[G_OFF_SET];
        blue = ptr + B_OFF_SET; //ptr[B_OFF_SET];
    }
}

void cAPA102_Set_Pixel_4byte(uint32_t index, uint32_t colour){
    uint8_t  r, g, b, br;
    r = colour >> 16;
    g = colour >> 8;
    b = colour;

    cAPA102_Set_Pixel_RGB(index, r, g, b);

    // if(index < cAPA012_BUF.numLEDs) {
    //     uint8_t *ptr = &cAPA012_BUF.pixels[index * 4];
    //     // ptr[ROFFSET] = (uint8_t)(r * br / 255);
    //     // ptr[GOFFSET] = (uint8_t)(g * br / 255);
    //     // ptr[BOFFSET] = (uint8_t)(b * br / 255);
    // }
}

uint32_t cAPA102_Get_Pixel_4byte(uint32_t index){
    uint8_t r, g, b;
    uint32_t colour = 0;
    cAPA102_Get_Pixel_RGB(index, &r, &g, &b);
    r <<= 16;
    g <<= 8;
    colour = r | g | b;
    return colour;
}

void cAPA102_Clear_All(void){

}

void cAPA102_Refresh(void){

}

void cAPA102_Close(void){
    cAPA102_Clear_All();
    if (cAPA012_BUF.fd_spi != -1)
        close(cAPA012_BUF.fd_spi);
    if (cAPA012_BUF.pixels)
        free(cAPA012_BUF.pixels);
}

static int cAPA102_Try_Open_SPI_Dev(uint8_t retry_times, uint8_t retry_gap_sec){
    int i,res;
    i = 0;
    do{
        res = cAPA102_Open_SPI_Dev();
        if (-1 != res)
          return res;
        i++;
        if(i > retry_times)
          break;
        fprintf(stderr, "[Error] Failed to open SPI! Retry [%d] in %d seconds. \n", i, retry_gap_sec);
    	   sleep(retry_gap_sec);
    }while(res);
    return -1;
}

static int cAPA102_Open_SPI_Dev(void){
    char spi_file_buff[50];
    int fd_temp;
    sprintf(spi_file_buff, SPI_DEVICE, leds.spi_bus, leds.spi_dev);
    fd_temp = open(spi_file_buff, O_RDWR);
    if(-1 == fd_temp) {
        fprintf(stderr, "[Error] Can't open %s (try 'sudo')", spi_file_buff);
        return -1;
    }
    ioctl(fd_temp, SPI_IOC_WR_MODE, SPI_MODE_0 | SPI_NO_CS);
    ioctl(fd_temp, SPI_IOC_WR_MAX_SPEED_HZ, BITRATE);
    return fd_temp;
}