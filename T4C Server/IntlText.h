// IntlText.h: interface for the IntlText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTLTEXT_H__46FDF684_11B4_11D2_836E_00E02922FA40__INCLUDED_)
#define AFX_INTLTEXT_H__46FDF684_11B4_11D2_836E_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Unit.h"
#include "GenRef.h"
#include "Random.h"

#define NB_SUPPORTED_LNG    7

#define LNG_ENGLISH         0
#define LNG_ITALIAN         1
#define LNG_FRENCH          2
#define LNG_PORTUGESE       3
#define LNG_SPANISH         4
#define LNG_GERMAN          5
#define LNG_KOREAN          6

class EXPORT IntlText  
{
public:        
    ~IntlText( void ){
        IntlText::Destroy();
    }
    
    static void LoadLngDB( CString csFile );
    static BOOL IsLngOK( void );            // Determines if at least one language is loaded!    
    
    // Returns a string given its ID and a language.
    static CString &GetString( DWORD dwID, WORD wLanguage, CString &csSource );
    static CString &AppendString( DWORD dwID, WORD wLanguage, CString &csSource );

    // Returns a string given its ID and a language.
    static const char *GetString( DWORD dwID, WORD wLanguage, const char *szDefault = "" );

    static WORD GetDefaultLng( void );

    static void SendPlayerMessage( Unit *lpUnit, DWORD dwID );

    // Parses an 'intlstring' (ie: [id]default ) and returns a valid string.    
    static const char *ParseString( const char *szString, WORD wLanguage );

private:
    IntlText( void ){
        IntlText::Create();
    };

    static void Create( void );
    static void Destroy( void );            // Frees the language resources.

    struct STR_ID{
        CString csString;
        DWORD dwStringID;
    };
    
    struct LNG_STR{
        CString *lpcsStrings;
        DWORD dwMaxStrings;
    };

    class EncParse{
    public:
        EncParse( FILE *fFile );
        
        int GetChar( void );
        void SeekOneBefore( void );
        void SeekOneBeforeEnd( void );

    private:
        DWORD  dwFilePos;
        Random cRnd;
        FILE  *fFile;
        uhyper qwLastSeed;
    };

    static BOOL ParseLngFile( EncParse &fFile, WORD wLangID, TemplateList <STR_ID> &tlStrings );
    static BOOL FetchNumber( EncParse &fFile, DWORD &dwNum, WORD &wLine );
    static BOOL FetchString( EncParse &fFile, CString &csString, WORD &wLine );
    static BOOL ToChar( EncParse &fFile, char ch, const char *invalid, WORD &wLine );

    static WORD wDefaultLng;
    static LNG_STR lpLang[ NB_SUPPORTED_LNG ];  
    
    static IntlText m_Instance;
};

//////////////////////////////////////////////////////////////////////////////////////////
// International string classes.
  /*
class intl_string;

// Proxy class for international strings.
// This class simply provides a mechanism for assigning fast temporary objects
// to convert C strings into intl_strings.
class intl_assign{
public:
    friend intl_string;

    inline intl_assign( DWORD dwTextId, const char *lpszText );    
private:
    // prohibit heap-based intl_assign objects.
    static void *operator new( size_t size ){ return NULL; };
    static void  operator delete( void *ptr ){};
    
    const char *lpszText;
    DWORD       dwTextId;
};

class intl_oper{
public:
    friend intl_string;

    inline intl_oper( DWORD dwTextId, const char *lpszDefault, WORD wLangId );

    inline intl_oper &operator + ( intl_oper &cRight );

    friend inline void operator += ( string &csTarget, intl_oper &cRight );    

private:
    // Returns a valid translated string.
    inline const char *get_str( WORD wLangId ) const;

    // prohibit heap-based intl_oper objects.
    static void *operator new( size_t size ){ return NULL; };
    static void  operator delete( void *ptr ){};

    DWORD  dwTextId;
    const  char *lpszDefault;
    string csOperText;
    WORD   wLangId;
};
                 
class intl_string{
public:
    // default constructor.
    inline intl_string( DWORD dwNewTextId, const char *lpszNewText );
    // copy constructor
    inline intl_string( intl_string &isCopy );
    // copy constructor using proxy intl class.
    inline intl_string( intl_assign &ipCopy );

    // Assignment operators on intl_assign and intl_strings.
    inline intl_string &operator = ( intl_assign  &ipCopy );
    inline intl_string &operator = ( intl_string &isCopy );

    // Returns a valid, translated string.
    inline const char *get_str( WORD wLangId ) const;
private:
    inline void Copy( intl_string &isCopy );
    inline void Copy( intl_assign  &ipCopy );

    DWORD  dwTextId;
    string csDefaultText;
};

//////////////////////////////////////////////////////////////////////////////////////////
// International string inline implementation.

//mystr = intl( 1, "allo" );

//////////////////////////////////////////////////////////////////////////////////////////
// intl_assign implementation.

// Default contructor.
intl_assign::intl_assign( DWORD dwNewTextId, const char *lpszNewText ) 
: lpszText( lpszNewText ), dwTextId( dwNewTextId )
{};

//////////////////////////////////////////////////////////////////////////////////////////
// intl_oper implementation.
intl_oper::intl_oper( DWORD dwNewTextId, const char *lpszNewDefault, WORD wNewLangId )
: dwTextId( dwNewTextId ), lpszDefault( lpszNewDefault ), wLangId( wNewLangId )
{};

// operator +
intl_oper &intl_oper::operator + ( intl_oper &cRight ){
    // If an operation doesn't exist (first time + has been used).
    if( csOperText.empty() ){
        // Set csOperText to this object's traducted string.
        csOperText = get_str( wLangId );
    }
    // Add the other object's traducted string to the operation string.
    csOperText += cRight.get_str( wLangId );
    return *this;
}
// returns a traducted string.
const char *intl_oper::get_str( WORD wLangId ) const{
    return IntlText::GetString( dwTextId, wLangId, lpszDefault );
}
// Allows strings to append an intl_oper's operation string.
void operator += ( string &csTarget, intl_oper &cRight ){
    // If an operation string does not exist for this intl_oper string.
    if( cRight.csOperText.empty() ){
        // Directly append the intl_oper's traducted string.
        csTarget += cRight.get_str( cRight.wLangId );
    }else{
        // Otherwise add the operation string.
        csTarget += cRight.csOperText;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
// intl_string implementation.

// Default contructor.    
intl_string::intl_string( DWORD dwNewTextId, const char *lpszNewText ) 
: csDefaultText( lpszNewText ), dwTextId( dwNewTextId )
{}
// Copy constructor
intl_string::intl_string( intl_string &isCopy ){
    Copy( isCopy );
}
// Copy constructor for proxy objects.
intl_string::intl_string( intl_assign &ipCopy ){
    Copy( ipCopy );
}
// Assignement operator for intl_string.
intl_string &intl_string::operator = ( intl_string &isCopy ){
    Copy( isCopy );
    return *this;
}
// Assignement operator for intl_assign.
intl_string &intl_string::operator = ( intl_assign  &ipCopy ){
    Copy( ipCopy );
    return *this;
}

const char *intl_string::get_str( WORD wLangId ) const{
    return IntlText::GetString( dwTextId, wLangId, csDefaultText.c_str() );
}

// Copy an intl_string into this.
void intl_string::Copy( intl_string &isCopy ){
    csDefaultText = isCopy.csDefaultText;
    dwTextId      = isCopy.dwTextId;
}
// Copy a intl_assign into this.
void intl_string::Copy( intl_assign &ipCopy ){
    csDefaultText = ipCopy.lpszText;
    dwTextId      = ipCopy.dwTextId;
}   

typedef intl_oper   oid;
 */
#define _DEFAULT_LNG                            IntlText::GetDefaultLng()
#define _STR( __resource, __lng )               IntlText::GetString( __resource, __lng )
#define _TELL_PLAYER( __player, __resource )    IntlText::SendPlayerMessage( __player, __resource );
#define _DEFAULT_STR( __resource )              IntlText::GetString( __resource, _DEFAULT_LNG )


#endif // !defined(AFX_INTLTEXT_H__46FDF684_11B4_11D2_836E_00E02922FA40__INCLUDED_)
