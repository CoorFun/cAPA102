# cAPA102

[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/CoorFun/cAPA102/blob/master/LICENSE)

cAPA102 is a lightweight hardware SPI based APA102 library, fast and easy to use.

This library is targeting to Raspberry Pi, ReSpeaker Core V2, Beaglebone such platforms.

## APIs

#### ```int cAPA102_Init(uint32_t led_num, uint8_t spi_bus, uint8_t spi_dev, uint8_t brightness);```

```
@brief: Initialise a set of apa102 LEDs

@param[in] led_num: Number of LEDs (0-255)
@param[in] spi_bus: SPI bus number (0-255)
@param[in] spi_dev: SPI device number (0-255)
@param[in] brightness: Global brightness (0-31)

@returns:  0\ Success
          -1\ Error
```

#### ```void cAPA102_Change_Brightness(uint8_t brightness);```

```
@brief: Change the global brightness and fresh

@param[in] brightness: New brightness value
```

#### ```int cAPA102_Get_Brightness(void);```

```
@brief: Get the brightness

@return current brightness value (0-31)
```

#### ```void cAPA102_Set_Pixel_RGB(uint32_t index, uint8_t red, uint8_t green, uint8_t blue);```

```
@brief: Set color for a specific pixel by giving R, G and B value separately

@param[in] index: Index of the target led (0-255)
@param[in] red: Intensity of red colour (0-255)
@param[in] green: Intensity of green colour (0-255)
@param[in] blue: Intensity of blue colour (0-255)
```

#### ```void cAPA102_Get_Pixel_RGB(uint32_t index, uint8_t *red, uint8_t *green, uint8_t *blue);```

```
@brief: Get colour form a specific pixel for R, G and B separately

@param[in] index: Index of the target led (0-255)
@param[out] red: Intensity of red colour (0-255)
@param[out] green: Intensity of green colour (0-255)
@param[out] blue: Intensity of blue colour (0-255)
```

#### ```void cAPA102_Set_Pixel_4byte(uint32_t index, uint32_t colour);```

```
@brief: Set color for a specific pixel by using 4byte date

@param[in] index: Index of the target led (0-255)
@param[in] red: Intensity of red colour (0-255)
@param[in] green: Intensity of green colour (0-255)
@param[in] blue: Intensity of blue colour (0-255)

@example: cAPA102_Get_Pixel_RGB(1, 0xFF0000) sets the 1st LED to red colour
```

#### ```uint32_t cAPA102_Get_Pixel_4byte(uint32_t index);```

```
@brief: Get colour form a specific pixel

@param[in] index: Index of the target led (0-255)

@returns: 32 bits colour data
```

#### ```void cAPA102_Clear_All(void);```

```
@brief: Clear all the pixels
```

#### ```void cAPA102_Refresh(void);```

```
@brief: Refresh display (After modifying pixel colour)
```

#### ```void cAPA102_Close(void);```

```
@brief: Close SPI file, release memory
```

## Usage example

The following is an example of using this APA102 library with 12 LEDs.

**1.** Copy the `cAPA102.h` and `cAPA102.c` to your project folder.

**2.** Include the head file from where you would use this library.

```c
#include "cAPA102.h"
```

**3.** Call `cAPA102_Init(12, 0, 0, 31)` function with the led_num is 12, spi0.0 and largest brightness to initialise the LED set.

```c
cAPA102_Init(12, 0, 0, 31);
```

**4.** Call `cAPA102_Set_Pixel_4byte()` function to set the first 8 LEDs where the first 4 LEDs are red and the following 4 LEDs are green. Call `cAPA102_Set_Pixel_RGB()` function to set the second 8 LEDs where the first 4 LEDs are blue and the following 4 LEDs are cyan.

```c
int i;
for ( i = 0; i < 3; i++)
    cAPA102_Set_Pixel_4byte(i, 0xFF0000);

for ( i = 3; i < 6; i++)
    cAPA102_Set_Pixel_4byte(i, 0x00FF00);

for ( i = 6; i < 9; i++)
    cAPA102_Set_Pixel_RGB(i, 0, 0, 255);

for ( i = 9; i < 12; i++)
    cAPA102_Set_Pixel_RGB(i, 255, 255, 0);
```

**5.** Call `cAPA102_Refresh()` function to refresh the LEDs.

```c
cAPA102_Refresh();
```

**6. [Important] Call `cAPA102_Close()` function to properly close SPI device file and release pixel memory**

```c
cAPA102_Close();
```

> *(All the pixels data are save by dynamically allocating memory space, without calling this function, your program will cause a memory leakage)*

## How to Contribute

Contributions are welcome! Not familiar with the codebase yet? No problem!

There are many ways to contribute to open source projects: reporting bugs, helping with the documentation, spreading the word and of course, adding new features and patches.

### Getting Started

- Make sure you have a GitHub account.
- Open a [new issue](https://github.com/CoorFun/cAPA102/issues), assuming one does not already exist.
- Clearly describe the issue including steps to reproduce when it is a bug.

### Making Changes

- Fork this repository.
- Create a feature branch from where you want to base your work.
- Make commits of logical units (if needed rebase your feature branch before submitting it).
- Check for unnecessary whitespace with `git diff --check` before committing.
- Make sure your commit messages are well formatted.
- If your commit fixes an open issue, reference it in the commit message (f.e. `#15`).
- Run all the tests (if existing) to assure nothing else was accidentally broken.

These guidelines also apply when helping with documentation.

### Submitting Changes

- Push your changes to a feature branch in your fork of the repository.
- Submit a `Pull Request`.
- Wait for maintainer feedback.