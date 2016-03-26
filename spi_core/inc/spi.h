#ifndef SPI_H
#define SPI_H

#include "BlackGPIO.h"
#include "BlackSPI.h"

class SPI
{
 public:
  SPI(BlackLib::BlackSPI spi_core);
  virtual ~SPI();
  void write();
  void write_burst();
  void read();
  void read_burst();
  bool is_up;

};

#endif

