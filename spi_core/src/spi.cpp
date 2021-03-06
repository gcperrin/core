#include "spi.h"
#include "cc1101_registers.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

SPI::SPI(BlackLib::BlackSPI spi_core)
{
  this->is_up = true;
  if (!this->redis_cli.Initialize("127.0.0.1", 6379, 2, 10)) {
    std::cout << "connect to redis failed" << std::endl;
  } else {
    std::cout << "Redis connected" << std::endl;
  }

  //BlackLib::BlackGPIO GDO0(BlackLib::GPIO_48, BlackLib::input);

  const unsigned char PA_LEN = 1;
  uint8_t byte1[2]  = { IOCFG0, 0x06 };
  uint8_t byte2[2]  = { IOCFG2, 0x07 };
  uint8_t byte3[2]  = { FIFOTHR, 0x47 };
  uint8_t byte4[2]  = { PKTCTRL0, 0x05 };
  uint8_t byte5[2]  = { FSCTRL1, 0x06 };
  uint8_t byte6[2]  = { FREQ2, 0x23 };
  uint8_t byte7[2]  = { FREQ1, 0x31 };
  uint8_t byte8[2]  = { FREQ0, 0x3B };
  uint8_t byte9[2]  = { MDMCFG4, 0xF5 };
  uint8_t byte10[2] = { MDMCFG3, 0x83 };
  uint8_t byte11[2] = { MDMCFG2, 0x13 };
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
  uint8_t byte24[3] = { PATABLE, 0xC0, PA_LEN };

  bool isOpened = spi_core.open(BlackLib::ReadWrite);

  if (!isOpened) {
    std::cout << "SPI DEVICE CAN\'T OPEN.;" << std::endl;
    exit(1);
  }
  
  uint8_t readBytes[2];

  spi_core.transfer(byte1, readBytes, sizeof(byte1), 1);
  spi_core.transfer(byte2, readBytes, sizeof(byte2), 1);
  spi_core.transfer(byte3, readBytes, sizeof(byte3), 1);
  spi_core.transfer(byte4, readBytes, sizeof(byte4), 1);
  spi_core.transfer(byte5, readBytes, sizeof(byte5), 1);
  spi_core.transfer(byte6, readBytes, sizeof(byte6), 1);
  spi_core.transfer(byte7, readBytes, sizeof(byte7), 1);
  spi_core.transfer(byte8, readBytes, sizeof(byte8), 1);
  spi_core.transfer(byte9, readBytes, sizeof(byte9), 1);
  spi_core.transfer(byte10, readBytes, sizeof(byte10), 1);
  spi_core.transfer(byte11, readBytes, sizeof(byte11), 1);
  spi_core.transfer(byte12, readBytes, sizeof(byte12), 1);
  spi_core.transfer(byte13, readBytes, sizeof(byte13), 1);
  spi_core.transfer(byte14, readBytes, sizeof(byte14), 1);
  spi_core.transfer(byte15, readBytes, sizeof(byte15), 1);
  spi_core.transfer(byte16, readBytes, sizeof(byte16), 1);
  spi_core.transfer(byte17, readBytes, sizeof(byte17), 1);
  spi_core.transfer(byte18, readBytes, sizeof(byte18), 1);
  spi_core.transfer(byte19, readBytes, sizeof(byte19), 1);
  spi_core.transfer(byte20, readBytes, sizeof(byte20), 1);
  spi_core.transfer(byte21, readBytes, sizeof(byte21), 1);
  spi_core.transfer(byte22, readBytes, sizeof(byte22), 1);
  spi_core.transfer(byte23, readBytes, sizeof(byte23), 1);
  spi_core.transfer(byte24, readBytes, sizeof(byte24), 1);

  this->is_up = false;

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

void SPI::set_rx(BlackLib::BlackSPI* spi_core) 
{
  bool isOpened = spi_core->open(BlackLib::ReadWrite);
  spi_core->transfer(SRX);
  spi_core->close();
}

void SPI::flush_rx(BlackLib::BlackSPI* spi_core) 
{
  bool isOpened = spi_core->open(BlackLib::ReadWrite);
  spi_core->transfer(SFRX);
  spi_core->close();
}

void SPI::getData(BlackLib::BlackSPI* spi_core,
		      BlackLib::BlackGPIO* GDO0)
{
  
  bool isOpened = spi_core->open(BlackLib::ReadWrite);
  spi_core->transfer(SIDLE);
  char len = 3;
  uint8_t tx_fifo[1] = { TXFIFO|WRITE_BURST };
  uint8_t writeArr[3] = {TXFIFO|WRITE_BURST, 0x01,
			 0xDA};
  uint8_t readArr[4];

  spi_core->transfer(writeArr, readArr, sizeof(writeArr), 0);
  spi_core->transfer(STX);
  while (GDO0->getValue() != "1") { std::cout << GDO0->getValue() << std::endl; };
  while (GDO0->getValue() != "0") { std::cout << GDO0->getValue() << std::endl; };
  spi_core->transfer(SRX);
  spi_core->close();
  if (this->status_counter >= 3) {
    std::string strKey = "bDA_status";
    std::string strStatus = "down";
    if (this->redis_cli.Set(strKey, strStatus) == RC_SUCCESS) {
      std::cout << "Board down" << std::endl;
    } else {
      std::cout << "fuck you bitch" << std::endl;
    }
  }
  this->status_counter++;
}

/*
 * Read incoming packet off the SPI bus
 */
void SPI::readData(BlackLib::BlackSPI* spi_core)
{
  this->status_counter = 0;
  std::string statusKey = "bDA_status";
  std::string status = "up";
  if (this->redis_cli.Set(statusKey, status) == RC_SUCCESS) {
    std::cout << "RX_STATUS" << std::endl;
  } else {
    std::cout << "fuck you bitch" << std::endl;
  }
  bool isOpened = spi_core->open(BlackLib::ReadWrite);
  spi_core->transfer(SIDLE);
  uint8_t rx_fifo[1] = { RXFIFO|READ_BURST };
  uint8_t packet_length[1];
  uint8_t rx_buffer[17];

  spi_core->transfer(0x00, 10);
  spi_core->transfer(rx_fifo, rx_buffer, 17, 0);
  std::cout << sizeof(rx_buffer) << std::endl;
  std::stringstream ss;
  for (int i=0; i<17; i++) {    
    ss << rx_buffer[i];
  }

  std::string data_arr = ss.str();
  std::cout << data_arr << std::endl;
  std::string strKey = "bDA_data";
  if (this->redis_cli.Set(strKey, data_arr) == RC_SUCCESS) {
    std::cout << "RX_DATA" << std::endl;
  } else {
    std::cout << "fuck you bitch" << std::endl;
  }
  spi_core->transfer(SRX);
  spi_core->close();
}
