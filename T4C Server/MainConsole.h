// MainConsole.h: interface for the MainConsole class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINCONSOLE_H__056C8101_0631_11D3_84FA_00E02922FA40__INCLUDED_)
#define AFX_MAINCONSOLE_H__056C8101_0631_11D3_84FA_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class MainConsole  
{
public:	
	virtual ~MainConsole();

    static MainConsole &GetInstance();

    void TakeControl( void );
    void Terminate( void );

private:
    MainConsole();

    static unsigned int PipeThread( void *lpInstance );

};

#endif // !defined(AFX_MAINCONSOLE_H__056C8101_0631_11D3_84FA_00E02922FA40__INCLUDED_)
