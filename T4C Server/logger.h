// ********************************************************************************************
// ***                                                                                      ***
//      File Name: Logger.h
//      Project:   Vircom Lib
//      Creation:  29 January 1999
//      Author:    Thomas (TH)
// ***                                                                                      ***
// ********************************************************************************************
// ***                                                                                      ***
//      Change History
//
//         Date            Ver.	  Author	     Purpose
//         01-29-1999      1.0    TH             Initial development
//		   01-30-1999	   1.1	  FL             AutoLock class added.
//		   02-11-1999	   1.2    TH             Added comment.
//         02-17-1999      1.2    FL             Changed namespace to 'vir'
//         03-05-1999      1.3    FL             Added DL_ALL debugging level.
//
//      Description
//         Provide an Interface for the logger.
// ***                                                                                      ***
//	********************************************************************************************
// *** Copyright (c) 1998-1999 Vircom. All rights reserved.                                 ***

// The following prevent the Logger to be included multiple time in a single cpp file. I used
// the following: VIRCOMLIB to identify the library, LOGGER for the name of the object, TH for
// my name and 07:22:16 is the time, 01/29/99 the date.
#ifndef VIRCOMLIB_LOGGER_TH072216012999
#define VIRCOMLIB_LOGGER_TH072216012999

// The namespace (ref: Francois E-Mail) is use to prevent the "polution" of the global namespace
// If you want to be able to use the following object in your code, just add the following line
// 
// using namespace VircomLib; 
//
// in your cpp files.
namespace vir {

// Debug Level will be use to set the debug level of the logging. It currently contain 32 bit field
// but could be expanded if someone is crazy enough to write a class for it.
typedef unsigned long		DEBUG_LEVEL;

// The next few consts are Reserved Debug Level, you can start your own custom Debug Level starting
// at number 0x0020.
// This Debug Level is used to log Debugging Information.
const DEBUG_LEVEL DL_DEBUG   = 0x0001; 
// This Debug Level is used to explain in detail errors that occurs with the use of your class.
const DEBUG_LEVEL DL_ERROR   = 0x0002; 
// This Debug Level is used to warn about at non-fatal mis-use of your class.
const DEBUG_LEVEL DL_WARNING = 0x0004;
// This debug level is used for informational purposes.
const DEBUG_LEVEL DL_INFO    = 0x0008;
// This sets all bits to 1, enabling all logs to trigger.
const DEBUG_LEVEL DL_ALL     = static_cast< DEBUG_LEVEL >( -1 );

// Here are 2 object function use to convert Ansi to Unicode, and Unicode to Ansi. The syntax of a
// object function is the following: 
//
// AnsiToUnicode()(PARAM); 
//
// AnsiToUnicode() create an unamed object (more effecient for the compiler to optimize the code. 
// This temporary object will call the operator () function with the specified PARAM. After the call
// the temprary object is automatically destroyed.

class AnsiToUnicode {
// This class transform Ansi String to Unicode String.

	public:
		
		wchar_t *operator() ( const char *const s, wchar_t ws[] ) { 
		// Transform Ansi string to Unicode string.
			int l  = strlen( s );       // Lenght of the Ansi String.
			int wl = sizeof( ws ) >> 1; // Lenght of the Unicode Buffer.
			
			if ( wl < (l+1) )
			// Set the Ansi String Lenght to the maximum of the Unicode Buffer Lenght.
				l = wl - 1;
			
			// Copy the buffer.
			for (int i = 0; i < l; i++) 
				ws[i] = s[i];
			
			// End the buffer.
			ws[l] = NULL;

			return ws;
		} 
}; // End of Class AnsiToUnicode.

class UnicodeToAnsi {
// This class transform Unicode String to Ansi String.

	public:

		char *operator () ( const wchar_t *const ws, char s[] ) {
		// Transfrom Unicode string to Ansi string.

			// Converstion.
			WideCharToMultiByte( CP_ACP, NULL, ws, -1, s, sizeof( s ), NULL, NULL );

			return s;
		}
}; // End of Class UnicodeToAnsi.

// Here come the fun part. This is the base Logger class. Because it contains pure virtual function
// (function with this syntax: virtual void func(void) = 0;) it cannot be instantiate, that means,
// you can only make pointers of Logger. The reason behind that is that the compiler cannot find
// any body for the member function void func(void);

class Logger {
// This class is the base logger class. It containt all base function for any derived 
// Logger class. 

	public:
	// The following function are public. If someone thing one of this function should be
	// put protected or private, please let-me know.

		// Constructor.
		Logger( void ) { 
		// By default, the Logger won't log anything.
			dlDebugLevel = 0; 
		} 
		
		// Thread safety function. I didn't put them pure virtual, so by default, they 
		// simply do nothing.
//		virtual void Lock    ( void ) { };
//		virtual void Unlock  ( void ) { };
//		virtual bool PickLock( void ) { Lock(); return true; }

		// User Logging Functions.
		virtual void Log( DEBUG_LEVEL dl, char *s ) {
		// Ansi Version. Here we use the autolock class instead of the Lock/Unlock function call.
		// What we did is put a this->Lock call in the constructor of AutoLock, called when the an
		// AutoLock object is first instantiated, and a call to this->Unlock in the destructor, called 
		// when the AutoLock object goes out of scope. The AutoLock syntax is better than the normal
		// Lock/Unlock call because it will ALWAYS call unlock, even if LogAnsi throw an exception.
		// Another way to write the following 2 lines of code would have been:
		//
		// Lock();
		// try {
		//		LogAnsi( dl, s );
		//		Unlock();
		// } catch (...) {
		//		Unlock();
		//		throw;
		// }
			AutoLock al( this );
			LogAnsi( dl, s );
		}
		virtual void Log( DEBUG_LEVEL dl, wchar_t *ws ) {
		// Unicode Version. Same explanation as the Ansi version.
			AutoLock al( this );
			LogUnicode( dl, ws );
		}

		// Utilities Functions.
		virtual bool QueryDebugLevel( DEBUG_LEVEL dl ) { 
		// The default implementation of QueryDebugLevel return true if the queryied debug level
		// was set to true by the user. (hmmm... I think the code is more clear than this comment.)
			return (dl & dlDebugLevel) ? true : false; 
		}

	protected:
	// The following function are protected. Here is an explanation why all those function are 
	// protected. The AutoLock class is not public because we don't want the client of your Logger
	// to be able to call it, instead, it should use the lock/unlock function. Also, I didn't put 
	// it protected because you may need it in your own implementation of your logger. The 
	// SetLogLevel function is also protected, because I didn't want any client of your Logger 
	// to be able to change the Log Setting. LogAnsi and LogUnicode are sub function use by the 
	// public function LOG. Also, LogAnsi and LogUnicode should stay protected in your own 
	// derived logger.

		class AutoLock{
		// Lock-safety class. Automatically manages unlocking on object's destruction. The explanation
		// of this type of class is giving in the comment of the Log function.
			public:
				AutoLock( Logger *lpLogger ){
				// Constructor, locking the lpLogger class.
					lpLoggerInstance = lpLogger;
//					lpLoggerInstance->Lock();
				}

				~AutoLock(){
				// Destructor, unlocking the lpLogger class.
//					lpLoggerInstance->Unlock();
				}
			private:
				Logger *lpLoggerInstance; // The lpLoggerInstance, needed by the destructor.
		};
		
		DEBUG_LEVEL dlDebugLevel;			// Debug Level Value (32 BitFields).
		
		// Utilities Functions.
		virtual void SetLogLevel( DEBUG_LEVEL dl ) = 0;
		// There is no default behavior for SetLogLevel. This function should be public in your
		// derived logger.

		// Internal Logging Functions.
		// There is no default implementation of LogAnsi and LogUnicode. An example can be fond
		// in my TraceLogger class.
		virtual void LogAnsi   ( DEBUG_LEVEL dl, char *s  )   = 0;
		virtual void LogUnicode( DEBUG_LEVEL dl, wchar_t *s ) = 0;
}; // End of class Logger

} // End of namespace vir

#endif // VIRCOMLIB_LOGGER_TH072216012899