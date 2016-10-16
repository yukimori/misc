.PHONY: all clean

CC       =g++
CFLAGS   =-Wall -ansi -pedantic
TARGET   =test_libgtest
SRC      =test_libgtest.cpp
HEADERS  =
INCLUDES =
LDFLAGS  =
LIBS     =-pthread -lgtest

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS) Makefile
  $(CC) -o $@ $(CFLAGS) $(SRC) $(INCLUDES) $(LDFLAGS) $(LIBS)

clean:
  rm -f $(TARGET)
