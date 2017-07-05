
#ifndef __TFCSERVERGP_H
#define __TFCSERVERGP_H

//#include <eh.h>
#include "TFCException.h"
//#include "WatchdogNotificator.h"

//////////////////////////////////////////////////////////////////////////////////////////
void ExceptionFunction(unsigned int u, EXCEPTION_POINTERS* pExp);
BOOL LockGP( BOOL boTry );

#ifndef DISABLE_GP
//#define SETUP_GP    _set_se_translator( ExceptionFunction );
#else
//#define SETUP_GP
#endif

/*#define LOCK_GP     CWatchdogNotificator::GetInstance()->ReportServerCrash();\
                    LockGP( FALSE );*/
#define LOCK_GP		LockGP( FALSE );
#define TRYLOCK_GP  LockGP( TRUE )

//#define REPORT_FUNC_PROTOTYPE   CFile csGP, TFCException *e

//typedef void ( *REPORT_FUNC )( REPORT_FUNC_PROTOTYPE );

// Report an exception.
void ReportGP( TFCException *e, CString csThreadNameID );

// Add an extra reporting function which will output debug data before the GP.
//void RegisterReportFunction( REPORT_FUNC lpReportFunc );

#endif
