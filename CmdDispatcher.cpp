#include "CmdDispatcher.h"
#include <stdio.h>
#include <sstream> 

CmdDispatcher::CmdDispatcher( ILED *led ) : pLED_( led ) {
	cmd_map_["set-led-state"] = &CmdDispatcher::set_state;
	cmd_map_["get-led-state"] = &CmdDispatcher::get_state;
	cmd_map_["set-led-color"] = &CmdDispatcher::set_color;
	cmd_map_["get-led-color"] = &CmdDispatcher::get_color;
	cmd_map_["set-led-rate"] = &CmdDispatcher::set_rate;
	cmd_map_["get-led-rate"] = &CmdDispatcher::get_rate;
}

std::string CmdDispatcher::set_state( std::vector< std::string > & prm ) {
	std::string status;
	LED_STATE state;
	bool bad_prm = false;

	if ( prm.size() != 2 )
		return "BAD COMMAND";

	if ( std::string::npos != prm[1].find( "on" ) ) {
		state = ON;
	} else if ( std::string::npos != prm[1].find( "off" ) ) {
		state = OFF;
	} else {
		status = "FAILED";
		bad_prm = true;
	}
	if ( !bad_prm && pLED_->set_state( state ) ) {
		status = "OK";
	} else {
		status = "FAILED";
	}
	return status;
}

std::string CmdDispatcher::get_state( std::vector< std::string > & prm ) {
	std::string status, res;
	int state = pLED_->get_state();
	if ( state < 0 ) {
		status = "FAILED";
	} else {
		status = "OK";
		if ( state == OFF ) {
			res = "off";
		} else if ( state == ON ) {
			res = "on";
		}
	}
	return std::string( status + " " + res );
}

std::string CmdDispatcher::set_color( std::vector< std::string > & prm ) {
	std::string status;
	LED_COLOR color;
	bool bad_prm = false;

	if ( prm.size() != 2 )
		return "BAD COMMAND";

	if ( prm[1] == "red" ) {
		color = RED;
	} else if ( prm[1] == "green" ) {
		color = GREEN;
	} else if ( prm[1] == "blue" ) {
		color = BLUE;
	} else {
		status = "FAILED";
		bad_prm = true;
	}
	if ( !bad_prm && pLED_->set_color( color ) ) {
		status = "OK";
	} else {
		status = "FAILED";
	}
	return status;
}


std::string CmdDispatcher::get_color( std::vector< std::string > & prm ) {
	std::string status, res;
	int color = pLED_->get_color();
	if ( color < 0 ) {
		status = "FAILED";
	} else {
		status = "OK";
		if ( color == RED ) {
			res = "red";
		} else if ( color == GREEN ) {
			res = "green";
		} else if ( color == BLUE ) {
			res = "blue";
		}
	}
	return std::string( status + " " + res );
}


std::string CmdDispatcher::set_rate( std::vector< std::string > & prm ) {
	std::string status;
	int rate;

	if ( prm.size() != 2 )
		return "BAD COMMAND";

	sscanf( prm[1].c_str(), "%d", &rate );
	if ( pLED_->set_rate( rate ) ) {
		status = "OK";
	} else {
		status = "FAILED";
	}
	return status;
}

std::string CmdDispatcher::get_rate( std::vector< std::string > & prm ) {
	std::string status, res;
	int rate = pLED_->get_rate();
	std::stringstream ss;
	ss << rate;
	if ( rate < 0 ) {
		status = "FAILED";
	} else {
		status = "OK";
		res = ss.str();
	}
	return std::string( status + " " + res );
}

std::string CmdDispatcher::dispatch( std::string & cmd ) {
	std::vector< std::string > cmd_parts;
	std::size_t lpos = 0, rpos = 0;

	while ( rpos != std::string::npos ) {
		lpos = cmd.find_first_not_of( ' ', rpos );
		rpos = cmd.find_first_of( ' ', lpos );
		if ( lpos != std::string::npos ) {
			cmd_parts.push_back( cmd.substr( lpos, rpos - lpos ) );
		}
	}
	if ( cmd_parts.size() == 0 || cmd_map_[ cmd_parts[ 0 ] ] == NULL )
		return "UNKNOWN COMMAND";	

	return ( this->*cmd_map_[ cmd_parts[ 0 ] ] ) ( cmd_parts );
}
