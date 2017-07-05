// WDAHeader.h: interface for the WDAHeader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WDAHEADER_H__12543A83_192F_4354_A9B5_6C0DCD435D52__INCLUDED_)
#define AFX_WDAHEADER_H__12543A83_192F_4354_A9B5_6C0DCD435D52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class WDAFile;
class WDAHeader  
{
public:
	WDAHeader();
	virtual ~WDAHeader();

    void SaveTo( WDAFile &wdaFile, bool isReadOnly );
    bool CreateFrom( WDAFile &wdaFile );

    bool IsReadOnly(){
        return m_ReadOnly;
    }

    bool IsVersionOK();

private:
    bool  m_ReadOnly;
    WORD  m_Version;
};

#endif // !defined(AFX_WDAHEADER_H__12543A83_192F_4354_A9B5_6C0DCD435D52__INCLUDED_)
