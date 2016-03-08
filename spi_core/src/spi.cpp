#include "spi.h"
#include <stdio.h>

SPI::SPI()
{
  BlackLib::BlackSPI spi_core(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 800000);

  uint8_t writeByte = 0xb1;
  uint8_t readByte;
  uint8_t writeBytes[4] = { 0x55, 0xaa, 0xf0, 0x0c };
  uint8_t readBytes[4];

  bool isOpened = spi_core.open(BlackLib::ReadWrite|BlackLib::NonBlock);

  if (!isOpened) {
    std::cout << "SPI DEVICE CAN\'T OPEN.;" << std::endl;
    exit(1);
  }
  /*
  std::cout << std::endl;
  std::cout << "Device Path   : " << spi_core.getPortName() << std::endl;
  std::cout << "Max Speed(Hz) : " << spi_core.getMaximumSpeed() << std::endl;
  std::cout << "Bits Per Word : " << (int)spi_core.getBitsPerWord() << std::endl;
  std::cout << "Mode          : " << (int)spi_core.getMode() << std::endl << std::endl;

  spi_core.transfer(writeBytes, readBytes, sizeof(writeBytes), 0);
  printf("This a test bitch\n");
  */

}

SPI::~SPI()
{

}

void SPI::write()
{
  printf("Fuck tard");
}

void SPI::write_burst()
{

}

void SPI::read()
{

}

void SPI::read_burst()
{

}
