#include <stdio.h>
#include "spi.h"

int main(void)
{
  SPI* cc1101_spi = new SPI();
  cc1101_spi->write();
  //while(true);
  return 0;
}
