IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=obj

LIBS=-lboost_program_options

_DEPS = header.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ= brokermain.o broker.o brokerfactory.o config.o connectMessage.o simplebroker.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

brokermain: $(OBJ)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
