#include "LED.h"
#include "Protocol.h"
#include "CmdDispatcher.h"
//#include <iostream>
#include <sstream>

std::string state_to_str( int s ) {
	if ( s == OFF ) { 
		return "OFF";
	} else if ( s == ON ) { 
		return "ON";
	} 
	return "UNKNOWN_STATE";
}

std::string color_to_str( int c ) {
	if ( c == RED ) { 
		return "RED";
	} else if ( c == GREEN ) { 
		return "GREEN";
	} else if ( c == BLUE ) {
		return "BLUE";
	}
	return "UNKNOWN_COLOR";
}

std::string rate_to_str( int r ) {
	std::stringstream ss;
	if ( r >= 0 ) { 
		ss << r;
		return ss.str();
	}
	return "UNKNOWN_RATE";
}

int main( int argc, char* argv [] ) {

	LED led;
	CmdDispatcher cmd_disp( &led );
	Protocol protocol( "/tmp/led_server_fifo" );
	protocol.do_processing( cmd_disp );
	
	return 0;
}
