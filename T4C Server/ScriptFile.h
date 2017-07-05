// ScriptFile.h: interface for the ScriptFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRIPTFILE_H__1C5D1070_77F3_4C92_B3FE_143F922CF337__INCLUDED_)
#define AFX_SCRIPTFILE_H__1C5D1070_77F3_4C92_B3FE_143F922CF337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
//using namespace std;

class ScriptFile  
{
public:
	static ScriptFile &GetInstance();

	unsigned int GetThreadId() { return nScriptThreadId; };
	HANDLE GetThreadHandle() { return hScriptThread; };

	int RunScript( char* szScriptPath );

private:
	ScriptFile();

	void ThreadFunc( void );

	static unsigned int CALLBACK ScriptThread( void *pParam );

	std::string OpenScript( char* szFile );
	void TranslateScript( std::string strCmd );

	void TraceExecution( const char* msg, ... );
	void InitTrace( void );

    HANDLE hScriptThread;
    unsigned int nScriptThreadId;

    bool boScriptThreadDone;

	bool boTraceExecution;
	bool boSafeMode;
	bool boScriptIsRunning;
	bool boStopScriptExecution;
	bool boKeepScript;

	std::string strGodCharacter;
	
	std::string strScriptFilename;

};

#endif // !defined(AFX_SCRIPTFILE_H__1C5D1070_77F3_4C92_B3FE_143F922CF337__INCLUDED_)
