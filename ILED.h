#ifndef __ILED__
#define __ILED__

#include <string>

enum LED_STATE {
	 OFF = 0,
	 ON = 1
};

enum LED_COLOR {
	RED = 0,
	GREEN = 1,
	BLUE = 2
};

std::string state_to_str( int );
std::string color_to_str( int );
std::string rate_to_str( int );

class ILED {
public:
	virtual int get_state() const = 0;
	virtual bool set_state( LED_STATE ) = 0;
	virtual int get_color() const = 0;
	virtual bool set_color( LED_COLOR ) = 0;
	virtual int get_rate() const = 0;
	virtual bool set_rate( int ) = 0;
};

#endif //__LED__
