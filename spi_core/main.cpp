#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <glib.h>
#include <iostream>
#include <boost/asio.hpp>
#include "spi.h"
using namespace std;

BlackLib::BlackSPI spi_core(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
//BlackLib::BlackGPIO GDO0(BlackLib::GPIO_48, BlackLib::input);
SPI* cc1101_spi = new SPI(spi_core);

/*
 * RX ISR: ISR generated when a packet is recieved, SPI needs to be read
 */
static gboolean onRecieve(GIOChannel *channel,
			   GIOCondition condition,
			   gpointer user_data)
{
  cerr << "onButtonEvent" << endl;
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
  cerr << "rc:" << rc << "  data:" << buffer << endl;
  return 1;
}

static gboolean dataRequest(void* data)
{
  // Will need to ask redis queue for all board to query
  cout << "Requesting data..." << endl;
  cc1101_spi->getData(spi_core);
}

int main(int argc, char** argv)
{
  //BlackLib::BlackSPI spi_core(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 800000);
  //BlackLib::BlackGPIO GDO0(BlackLib::GPIO_48, BlackLib::input);
  //SPI* cc1101_spi = new SPI(spi_core);
  //while(cc1101_spi->is_up) { cout << "not yet" << endl;};
  GMainLoop* loop = g_main_loop_new(0, 0);
  int fd = open("/sys/class/gpio/gpio7/value", O_RDONLY | O_NONBLOCK);
  GIOChannel* channel = g_io_channel_unix_new(fd);
  GIOCondition cond = GIOCondition(G_IO_PRI);
  guint id = g_io_add_watch(channel, cond, onRecieve, 0);    

  GSList* List;
  g_timeout_add_seconds(5, dataRequest, List);

  g_main_loop_run(loop);

}


