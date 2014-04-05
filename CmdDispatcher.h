#ifndef __CMD_DISPATCHER__
#define __CMD_DISPATCHER__

#include "ICmdDispatcher.h"
#include "ILED.h"
#include <map> 

class CmdDispatcher : public ICmdDispatcher {
	typedef std::string ( CmdDispatcher::* cmd_type ) ( std::vector< std::string > & );
	typedef std::map< std::string, cmd_type > cmd_map_type;
public:	
	CmdDispatcher( ILED * );
	virtual std::string dispatch( std::string & );
private:	
	std::string set_color( std::vector< std::string > & );
	std::string get_color( std::vector< std::string > & );
	std::string set_state( std::vector< std::string > & );
	std::string get_state( std::vector< std::string > & );
	std::string set_rate( std::vector< std::string > & );
	std::string get_rate( std::vector< std::string > & );

	ILED *pLED_;
	cmd_map_type cmd_map_;
};

#endif
