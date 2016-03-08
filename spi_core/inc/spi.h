#ifndef SPI_H
#define SPI_H

//#include "BlackCore.h"
#include "BlackSPI.h"

class SPI
{
 public:
  BlackLib::spiName spi_name;
  SPI();
  virtual ~SPI();
  void write();
  void write_burst();
  void read();
  void read_burst();

 private:
  BlackLib::BlackSPI spi_core(spi_name[0]);

};

#endif

