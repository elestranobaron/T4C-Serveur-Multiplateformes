// *******************************************************************************************
// ***                                                                                     ***
//      File Name: Format.h
//      Plateform: Any
//      Creation:  18/2/1999
//      Author:    Francois Leblanc (FL)
// ***                                                                                     ***
// *******************************************************************************************
// ***                                                                                     ***
//      Change History
//
//         Date            Ver.      Author         Purpose
//         18/2/1999       1.0       FL             Initial developpement
//
//      Description
//          This file contains several classes that are used as wrappers over the 
//      conventional sprintf functions. ASCII, unicode and TCHAR (Microsoft specific)
//      versions of the class are listed here.
//
//      WARNING
//          This class is *not* thread safe. Its instances are intended to be used as 
//      stack-based objects (stacks are thread dependent). The objects cannot be copied, 
//      passed to functions or instantiated on the heap.
//
//      USAGE
//          Three classes are provided:
//             TFormat   ASCII version
//             TFormatW  Unicode version
//             TFormatT  TCHAR version (Microsoft specific).
//
//          Use these classes as functors (refer to the knowledge base for information 
//          about functors).
//
//          You can set the internal size of the formatting buffer using the template
//          versions:
//             Format < buffersize >
//             FormatW< buffersize >
//             FormatT< buffersize >
//          Where 'buffersize' is the internal buffer size in bytes
//          
// ***                                                                                      ***
//	*******************************************************************************************
// ***                Copyright (c) 1997-1999 Vircom. All rights reserved.                  ***

#ifndef FORMAT_H_DEFINITION
#define FORMAT_H_DEFINITION

// Vircom library namespace.
namespace vir{

// The class is a template, allowing compile-time knowledge of the sprintf buffer size.
// Knowing the size at compile-time allows stack-based format objects to be
// extremely fast.
template< unsigned int nBufferSize = 2048 >
class Format{
public:
    // Constructor, default to 0 length string buffer.
    Format( void ){ lpBuffer[ 0 ] = 0; };

    // Conversion operator(). Allows the class to be
    // used as a functor.
    // Ex.:  Format<>()( "Number %u", 1 );
    char *operator () ( const char *szTemplate, ... ){
        // Formats the template string and its arguments.
        va_list argp;

	    va_start( argp, szTemplate );
	    vsprintf( lpBuffer, szTemplate, argp );
	    va_end( argp );

        // Return the buffer.
        return lpBuffer;
    }

private:
    // Private copy constructor, disallows auto-assignement.
    Format( Format &cFormat ){};
    // Disable direct assignment.
    void operator = ( Format &cFormat ){};
    // Disable heap based instances of Format.
    void *operator new( size_t tSize ){ return 0; };

    // The format buffer has the scope of the object, as long as the format object
    // is accessible, the buffer is available.
    char lpBuffer[ nBufferSize ];
};


// Template buffer size.
template< unsigned int nBufferSize = 2048 >
// Unicode class instance,
class FormatW{
public:
    // Constructor, default to 0 length string buffer.
    FormatW( void ){ lpBuffer[ 0 ] = 0; };
    
    // Functor operator () for wide char strings.
    unsigned short *operator() ( const wchar_t *szTemplate, ... ){
        va_list argp;

	    va_start( argp, szTemplate );
	    vswprintf( lpBuffer, szTemplate, argp );
	    va_end( argp );

        return lpBuffer;
    }

private:
    // Disable assignemts of these objects
    FormatW( FormatW &cFormat ){};
    void operator = ( FormatW &cFormat ){};
    // Disable heap based FormatW objects.
    void *operator new( size_t tSize ){ return 0; };

    // The format buffer has the scope of the object, as long as the format object
    // is accessible, the buffer is available.
    wchar_t lpBuffer[ nBufferSize ];
};

// If the TCHAR sprintf function was defined
#ifdef _vstprintf

// Template buffer size.
template< unsigned int nBufferSize = 2048 >
// TCHAR class definition
class FormatT{
    // Constructor, default to 0 length string buffer.
    FormatT( void ){ lpBuffer[ 0 ] = 0; };

    // Functor operator () for tchars.
    TCHAR *operator() ( const TCHAR *szTemplate, ... ){
        va_list argp;

	    va_start( argp, szTemplate );
	    _vstprintf( lpBuffer, szTemplate, argp );
	    va_end( argp );

        return lpBuffer;
    }

private:
    // Disable assignemts of these objects
    FormatT( FormatW &cFormat ){};
    void operator = ( FormatT &cFormat ){};
    // Disable heap based FormatW objects.
    void *operator new( size_t tSize ){ return 0; };

    // The format buffer has the scope of the object, as long as the format object
    // is accessible, the buffer is available.
    TCHAR lpBuffer[ nBufferSize ];
};

// Typedef for default buffer size.
typedef FormatT<> TFormatT;

#endif // #ifdef _vstprintf

// Typedef for default buffer size.
typedef Format<>  TFormat;
typedef FormatW<> TFormatW;


}; // End of namespace vir

#endif // FORMAT_H_DEFINITION