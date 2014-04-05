#ifndef __LED__
#define __LED__

#include "ILED.h"
#include <memory>

class LED : public ILED {
public:
	virtual int get_state() const;
	virtual bool set_state( LED_STATE );
	virtual int get_color() const;
	virtual bool set_color( LED_COLOR );
	virtual int get_rate() const;
	virtual bool set_rate( int );
	LED();
	~LED () {}	
private:
	class LED_Impl;
	const std::auto_ptr< LED_Impl > pImpl;
	LED( const LED & );
	LED & operator=( const LED & );
};

#endif //__LED__
