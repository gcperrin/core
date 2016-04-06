#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <glib.h>
#include <iostream>
#include <boost/asio.hpp>
#include "spi.h"
using namespace std;

BlackLib::BlackSPI spi_core(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 800000);
BlackLib::BlackSPI* spi_core2 = new BlackLib::BlackSPI(BlackLib::SPI0_0,
						       8,
						       BlackLib::SpiDefault,
						       800000);
BlackLib::BlackGPIO* GDO0 = new BlackLib::BlackGPIO(BlackLib::GPIO_48,
						    BlackLib::input);
SPI* cc1101_spi = new SPI(spi_core);
int global_des;
/*
 * RX ISR: ISR generated when a packet is recieved, SPI needs to be read
 */
static gboolean onRecieve(GIOChannel *channel,
			  GIOCondition condition,
			  gpointer user_data)
{
  cerr << "Packet recieved" << endl;
  GError *error = 0;
  gsize bytes_read = 0; 
  const int buffer_size = 1024;
  gchar buffer[buffer_size] = {};
  g_io_channel_seek_position(channel, 0, G_SEEK_SET, 0);
  GIOStatus rc = g_io_channel_read_chars(channel,
					 buffer, 
					 buffer_size - 1,
					 &bytes_read,
					 &error);
  cc1101_spi->readData(spi_core2);
  cc1101_spi->flush_rx(spi_core2);
  return 1;
}

static gboolean dataRequest(void* data)
{
  // Will need to ask redis queue for all board to query
  cout << "Requesting data..." << endl;
  cc1101_spi->getData(spi_core2, GDO0);
  // Settings to recieve
  cout << "Setting RX..." << endl;
  cc1101_spi->set_rx(spi_core2);
}

int main(int argc, char** argv)
{
  // RX Interrupt setup
  GMainLoop* loop = g_main_loop_new(0, 0);
  int fd = open("/sys/class/gpio/gpio49/value", O_RDONLY | O_NONBLOCK);
  GIOChannel* channel = g_io_channel_unix_new(fd);
  GIOCondition cond = GIOCondition(G_IO_PRI);
  guint id = g_io_add_watch(channel, cond, onRecieve, 0);    

  // Data request timer & callback function
  GSList* List;
  g_timeout_add_seconds(10, dataRequest, List);

  // Run gLib loop
  g_main_loop_run(loop);
}


