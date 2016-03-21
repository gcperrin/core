#ifndef SPI_H
#define SPI_H

//#include "BlackCore.h"
#include "BlackGPIO.h"
#include "BlackSPI.h"

class SPI
{
 public:
  //BlackLib::spiName spi_name;
  SPI();
  virtual ~SPI();
  void write();
  void write_burst();
  void read();
  void read_burst();

 private:
  //BlackLib::spiName spi_name;
  //BlackLib::BlackSPI spi_core(BlackLib::SPI0_0);

};

#endif

