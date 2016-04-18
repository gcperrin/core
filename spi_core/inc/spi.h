#ifndef SPI_H
#define SPI_H

#include "BlackGPIO.h"
#include "BlackSPI.h"
#include "RedisClient.h"

class SPI
{
 public:
  SPI(BlackLib::BlackSPI spi_core);
  virtual ~SPI();
  void write();
  void write_burst();
  void read();
  void read_burst();
  void getData(BlackLib::BlackSPI* spi_core,
	       BlackLib::BlackGPIO* GDO0);
  void readData(BlackLib::BlackSPI* spi_core);
  void set_rx(BlackLib::BlackSPI* spi_core);
  void flush_rx(BlackLib::BlackSPI* spi_core);
  bool is_up;
  int status_counter;

 private:
  CRedisClient redis_cli;

};

#endif

