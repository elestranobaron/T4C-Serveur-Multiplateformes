// DebugLogger.h: interface for the DebugLogger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEBUGLOGGER_H__8D89B71E_024E_11D3_84F6_00E02922FA40__INCLUDED_)
#define AFX_DEBUGLOGGER_H__8D89B71E_024E_11D3_84F6_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <string>
#include <deque>
#include "Lock.h"

#pragma warning( disable : 4786 )

class DebugLogger : public CLock
{
public:	
	~DebugLogger();

    static DebugLogger &GetInstance();

    void LogString( std::string csString, bool boLogTime = false );

    void Flush( void );

    void AdjustMaxLogSize( unsigned long dwNewSize );

private:
    unsigned long GetStepBackSize( void );

    unsigned long dwMaxLogSize;

    // Singleton
    DebugLogger();

    std::deque< CString > qStrings;
};
  
#endif
