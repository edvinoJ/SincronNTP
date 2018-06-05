SOURCES = PaqueteDatagrama.cpp SocketDatagrama.cpp 
OBJECTS = PaqueteDatagrama.o SocketDatagrama.o 
LIB = -L/usr/X11R6/lib -lX11 -lm
SLIB = -I/usr/X11R6/include

all: Cliente.o Servidor.o
	g++ Cliente.o $(OBJECTS) Solicitud.o gfxModified.o -o Cliente $(LIB)
	g++ Servidor.o $(OBJECTS) Respuesta.o gfxModified.o -o Servidor $(LIB)
Cliente.o: $(OBJECTS) Solicitud.o Respuesta.o gfxModified.o
	g++ -std=c++11 Cliente.cpp $(SLIB) -c
Servidor.o: 
	g++ -std=c++11 Servidor.cpp $(SLIB) -c
$(OBJECTS):
	g++ -c $(SOURCES)
Solicitud.o:
	g++ -c -std=c++11 Solicitud.cpp
Respuesta.o:
	g++ -c -std=c++11 Respuesta.cpp
gfxModified.o: gfxModified.c gfxModified.h 
	gcc gfxModified.c -c $(SLIB)
clean:
	rm *.o 
