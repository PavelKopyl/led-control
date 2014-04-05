#ifndef __ICMD_DISPATCHER__
#define __ICMD_DISPATCHER__

#include <string> 
#include <vector>

class ICmdDispatcher {
public:	
	virtual std::string dispatch( std::string & ) = 0;
};

#endif
