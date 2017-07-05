
#ifndef STRINGHLP_DEFINITION
#define STRINGHLP_DEFINITION


// Format using a supplied buffer. Similar to sprintf but returns a pointer instead of an int.
char *format( char *lpBuffer, const char *szTemplate, ... ){
	va_list argp;

	va_start( argp, szTemplate );
	vsprintf( lpBuffer, szTemplate, argp );
	va_end( argp );

    return lpBuffer;
};

// Format for STL's string.
#ifdef _STRING_

class tstring : public string{
public:
    tstring( char *lpBuffer ) : string( lpBuffer ){};

    operator const char *(void){
        return c_str();
    }    
};

tstring &format( const char *szTemplate, ... ){
	char lpBuffer[ 2048 ];
    
    va_list argp;

	va_start( argp, szTemplate );
	vsprintf( lpBuffer, szTemplate, argp );
	va_end( argp );

    tstring tStr( lpBuffer );
    return tStr;
}

#endif



// Format for single thread. Uses a static buffer
char *formatst( const char *szTemplate, ... ){
	static char lpBuffer[ 2048 ];
    
    va_list argp;

	va_start( argp, szTemplate );
	vsprintf( lpBuffer, szTemplate, argp );
	va_end( argp );
    
    return lpBuffer;
}

#endif