#include "spi.h"
#include "cc1101_registers.h"
#include <stdio.h>
#include <iostream>
#include <string>

SPI::SPI()
{
  BlackLib::BlackSPI spi_core(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 800000);
  BlackLib::BlackGPIO GDO0(BlackLib::GPIO_48, BlackLib::input);

  const unsigned char PA_LEN = 1;
  uint8_t byte1[2]  = { IOCFG0, 0x06 };
  uint8_t byte2[2]  = { IOCFG2, 0x06 };
  uint8_t byte3[2]  = { FIFOTHR, 0x47 };
  uint8_t byte4[2]  = { PKTCTRL0, 0x05 };
  uint8_t byte5[2]  = { FSCTRL1, 0x06 };
  uint8_t byte6[2]  = { FREQ2, 0x23 };
  uint8_t byte7[2]  = { FREQ1, 0x31 };
  uint8_t byte8[2]  = { FREQ0, 0x3B };
  uint8_t byte9[2]  = { MDMCFG4, 0xF5 };
  uint8_t byte10[2] = { MDMCFG3, 0x83 };
  uint8_t byte11[2] = { MDMCFG2, 0x1B };
  uint8_t byte12[2] = { MDMCFG1, 0x22 };
  uint8_t byte13[2] = { DEVIATN, 0x31 };
  uint8_t byte14[2] = { MCSM0, 0x18 };
  uint8_t byte15[2] = { FOCCFG, 0x16 };
  uint8_t byte16[2] = { WORCTRL, 0xFB };
  uint8_t byte17[2] = { FSCAL3, 0xE9 };
  uint8_t byte18[2] = { FSCAL2, 0x2A };
  uint8_t byte19[2] = { FSCAL1, 0x00 };
  uint8_t byte20[2] = { FSCAL0, 0x1F };
  uint8_t byte21[2] = { TEST2, 0x81 };
  uint8_t byte22[2] = { TEST1, 0x35 };
  uint8_t byte23[2] = { TEST0, 0x09 };
  uint8_t byte24[3] = { PATABLE, 0x8E, PA_LEN };

  bool isOpened = spi_core.open(BlackLib::ReadWrite|BlackLib::NonBlock);

  if (!isOpened) {
    std::cout << "SPI DEVICE CAN\'T OPEN.;" << std::endl;
    exit(1);
  }
  
  uint8_t readBytes[2];

  spi_core.transfer(byte1, readBytes, sizeof(byte1), 0);
  spi_core.transfer(byte2, readBytes, sizeof(byte2), 0);
  spi_core.transfer(byte3, readBytes, sizeof(byte3), 0);
  spi_core.transfer(byte4, readBytes, sizeof(byte4), 0);
  spi_core.transfer(byte5, readBytes, sizeof(byte5), 0);
  spi_core.transfer(byte6, readBytes, sizeof(byte6), 0);
  spi_core.transfer(byte7, readBytes, sizeof(byte7), 0);
  spi_core.transfer(byte8, readBytes, sizeof(byte8), 0);
  spi_core.transfer(byte9, readBytes, sizeof(byte9), 0);
  spi_core.transfer(byte10, readBytes, sizeof(byte10), 0);
  spi_core.transfer(byte11, readBytes, sizeof(byte11), 0);
  spi_core.transfer(byte12, readBytes, sizeof(byte12), 0);
  spi_core.transfer(byte13, readBytes, sizeof(byte13), 0);
  spi_core.transfer(byte14, readBytes, sizeof(byte14), 0);
  spi_core.transfer(byte15, readBytes, sizeof(byte15), 0);
  spi_core.transfer(byte16, readBytes, sizeof(byte16), 0);
  spi_core.transfer(byte17, readBytes, sizeof(byte17), 0);
  spi_core.transfer(byte18, readBytes, sizeof(byte18), 0);
  spi_core.transfer(byte19, readBytes, sizeof(byte19), 0);
  spi_core.transfer(byte20, readBytes, sizeof(byte20), 0);
  spi_core.transfer(byte21, readBytes, sizeof(byte21), 0);
  spi_core.transfer(byte22, readBytes, sizeof(byte22), 0);
  spi_core.transfer(byte23, readBytes, sizeof(byte23), 0);
  spi_core.transfer(byte24, readBytes, sizeof(byte24), 0);

  //while (spi_core.isOpen() == true);
  uint8_t rx_fifo[1] = { RXFIFO|READ_BURST };
  uint8_t set_idle[1] = { SIDLE };
  uint8_t set_rx[1] = { SRX };
  std::string testValue = "1";
  while (true) {
    std::string gdoValue;
    gdoValue = GDO0.getValue();

    //std::cout << gdoValue << std::endl;
    while (gdoValue.compare(testValue) != 0);

    //Set idle
    spi_core.transfer(SIDLE, 10);

    // Poll RX I guess
    //usleep(1000);
    uint8_t preamble[2];
    uint8_t status[2];
    uint8_t packet_length[1];
    uint8_t rx_buffer[4];

    spi_core.transfer(rx_fifo, packet_length, sizeof(packet_length));

    // Dummy write
    spi_core.transfer(0x00, 10);
    spi_core.transfer(rx_fifo, preamble, sizeof(preamble), 0);

    // Dummy write
    spi_core.transfer(0x00, 10);
    spi_core.transfer(rx_fifo, rx_buffer, sizeof(rx_buffer), 0);

    // Dummy write
    spi_core.transfer(0x00, 10);
    spi_core.transfer(rx_fifo, status, sizeof(status), 0);

    // Set RX
    spi_core.transfer(SRX, 10);
  }
   

  /*
  std::cout << std::endl;
  std::cout << "Device Path   : " << spi_core.getPortName() << std::endl;
  std::cout << "Max Speed(Hz) : " << spi_core.getMaximumSpeed() << std::endl;
  std::cout << "Bits Per Word : " << (int)spi_core.getBitsPerWord() << std::endl;
  std::cout << "Mode          : " << (int)spi_core.getMode() << std::endl << std::endl;
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
