#include "Protocol.h"
#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include <sys/stat.h> 
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include <sstream>

Protocol::Protocol( const std::string & fifo ) : server_fifo_( fifo ) {
	umask( 0 );
	if ( mkfifo( server_fifo_.c_str(), S_IRUSR | S_IWUSR | S_IWGRP ) == -1
		&& errno != EEXIST)
	{
		perror("mkfifo");
		exit( EXIT_FAILURE );
	}
	server_fd_ = open( server_fifo_.c_str(), O_RDONLY );
	if ( server_fd_ == -1 ) {
		perror("open");
		exit( EXIT_FAILURE );
	}
	dummy_fd_ = open( server_fifo_.c_str(), O_WRONLY );
	if ( dummy_fd_ == -1 ) {
		perror("open");
		exit( EXIT_FAILURE );
	}

	if ( signal( SIGPIPE, SIG_IGN ) == SIG_ERR ) {
        perror("signal");
		exit( EXIT_FAILURE );
	}
}

void Protocol::do_processing( ICmdDispatcher & cmd_disp ) {
	std::string in_str, cmd_string, client_fifo, c_pid, s_res;
	int count, n_bytes, client_fd;
	char symb;

	for( ; ; ) {
		in_str.clear();
		for ( count = 0; count < PIPE_BUF; ) {
			n_bytes = read( server_fd_, &symb, sizeof( char ) );		
			if ( n_bytes == 0 || symb == '\n' )
		       	break;
			count += n_bytes;
			in_str += symb;
		}
		if ( n_bytes == 0 || count >= PIPE_BUF )
			continue;		

		std::size_t lpos = 0, rpos = 0;
		lpos = in_str.find_first_not_of( ' ', rpos );
		rpos = in_str.find_first_of( ' ', lpos );
		if ( lpos != std::string::npos ) {
			c_pid = in_str.substr( lpos, rpos - lpos );
			if ( rpos != std::string::npos ) {
				cmd_string = in_str.substr( rpos );
			} else {
				continue;
			}
		} else {
			continue;
		}

		client_fifo = "/tmp/led_client_fifo." + c_pid;
		
		/* Open client FIFO (previously created by client) */
		client_fd = open( client_fifo.c_str(), O_WRONLY );
        if ( client_fd == -1) {           
            std::cout << "Can`t open clinet fifo " << client_fifo << "\n";
            continue;
        }

		/* Send response and close FIFO */	
		s_res = cmd_disp.dispatch( cmd_string ) ;
		if ( write( client_fd, s_res.data(), s_res.size() ) == -1 ) {
        	perror("write");       		
		}
		if ( close( client_fd ) == -1 )
            perror("close");
	}
}

Protocol::~Protocol() {
	if ( close( server_fd_ ) == -1 || close( dummy_fd_ ) == -1 ) {
		 perror("close");
	}
}
