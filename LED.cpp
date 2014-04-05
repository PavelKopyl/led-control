#include "LED.h"
#include <iostream>

class LED::LED_Impl {
public:
	LED_Impl() : state_( OFF ), color_( -1 ), rate_( -1 ) {
		std::cout << "LED STATE: " << state_to_str( state_ ) << std::endl;
		std::cout << "LED COLOR: " << color_to_str( color_ ) << std::endl;
		std::cout << "LED RATE: " << rate_to_str( rate_ ) << std::endl;
	}
	bool set_state( LED_STATE );
	bool set_color( LED_COLOR );
	bool set_rate( int );

	int get_state() {
		return state_;
	}
	int get_color() {
		return color_;
	}
	int get_rate() {
		return rate_;
	}
	~LED_Impl() {}

private:
	int state_;
	int color_;
	int rate_;
};

bool LED::LED_Impl::set_state( LED_STATE s ) {
	if ( s == OFF ) {
		color_ = -1;
		rate_ = -1;
	} else {
		if ( state_ == OFF ) {
			color_ = RED;
			rate_ = 0;
		}
	}
	state_ = s;
	std::cout << "LED STATE: " << state_to_str( state_ ) << std::endl;
	std::cout << "LED COLOR: " << color_to_str( color_ ) << std::endl;
	std::cout << "LED RATE: " << rate_to_str( rate_ ) << std::endl;
	return true;
}

bool LED::LED_Impl::set_color( LED_COLOR c ) { 
	if ( state_ == OFF ) {
		return false;
	}
	color_ = c;
	std::cout << "LED COLOR: " << color_to_str( c ) << std::endl;
	return true;
}

bool LED::LED_Impl::set_rate( int r ) {
	if ( state_ == OFF || r < 0 || r > 5 ) {
		return false;
	}
	rate_ = r;
	std::cout << "LED RATE: " << rate_to_str( r ) << std::endl;
	return true;
}

LED::LED() : pImpl( new LED_Impl ) {}

int LED::get_state() const {
	return pImpl->get_state();
}
bool LED::set_state( LED_STATE s ) {
	return pImpl->set_state( s );
}

int LED::get_color() const {
	return pImpl->get_color();
}
bool LED::set_color( LED_COLOR c ) {
	return pImpl->set_color( c );
}

int LED::get_rate() const {
	return pImpl->get_rate();
}
bool LED::set_rate( int r ) {
	return pImpl->set_rate( r );
}





