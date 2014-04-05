#ifndef __PROTOCOL__
#define __PROTOCOL__

#include <string>
#include "ICmdDispatcher.h"

class Protocol {
public:
	Protocol( const std::string & fifo );
	~Protocol();
	void do_processing( ICmdDispatcher & );
	
private:
	const std::string server_fifo_;
	int server_fd_, dummy_fd_;
};


#endif //
