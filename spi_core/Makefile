#####################################################################
########                                                #############
########                 Gregory Perrin                 #############
########                    SIN Core                    #############
########                   7 Feb 2016                   #############
########                                                #############
########        Makefile to build SIN Core Modules      #############
########                                                #############
#####################################################################

CXX           = g++
DEFINES       = -D__GXX_EXPERIMENTAL_CXX0X__ -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8
CXXFLAGS      = -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -pthread $(DEFINES)
INCPATH       =  -I./inc -I./lib/v3_0 -I./lib/v3_0/BlackSPI 
LINK          = g++
LFLAGS        =
LIBS          = -L./lib -L./lib/v3_0 -L./lib/v3_0/BlackSPI -L./src
DEL_FILE      = rm -f

####### Files
SOURCES       = lib/v3_0/BlackCore.cpp lib/v3_0/BlackSPI/BlackSPI.cpp main.cpp src/spi.cpp
OBJECTS       = $(SOURCES:.cpp=.o)
DESTDIR       =
TARGET        = core

first: all

####### Implicit rules
.SUFFIXES: .cpp

.cpp.o:
			$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules
all:  $(TARGET)

$(TARGET):  $(OBJECTS)
			$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

clean:
			-$(DEL_FILE) $(OBJECTS)

distclean: clean
			-$(DEL_FILE) $(TARGET)
