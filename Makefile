objects = main.o LED.o CmdDispatcher.o Protocol.o

led_server: $(objects)
	g++ -o led_server $(objects) -Wall

main.o: LED.h Protocol.h CmdDispatcher.h
LED.o: ILED.h
CmdDispatcher.o: CmdDispatcher.h ILED.h
Protocol.o: Protocol.h CmdDispatcher.h

.PHONY : clean
clean :
	-rm led_server $(objects)
