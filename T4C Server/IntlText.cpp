// IntlText.cpp: implementation of the IntlText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "IntlText.h"
#include "T4CLog.h"
#include "RegKeyHandler.h"
#include "tfc_main.h"
#include "Random.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CTFCServerApp theApp;

IntlText::LNG_STR  IntlText::lpLang[ NB_SUPPORTED_LNG ];
WORD               IntlText::wDefaultLng;

IntlText           IntlText::m_Instance;

#define SAME_STR( __str1, __str2 )  stricmp( (LPCTSTR)__str1, (LPCTSTR)__str2 ) == 0

extern Random rnd;

namespace{
    class RandomTable{
    public:
        RandomTable(){
            rnd.SetSeed( 11677 );
            int i;
            for( i = 0; i < RandomTableSize; i++ ){
                lpRandomTable[ i ] = rnd( 0, 255 );				
            }
        }

        char GetChar( long nPos ){
            return lpRandomTable[ nPos % RandomTableSize ];
        }
    
    private:
        enum{ RandomTableSize = 7823 };
        char  lpRandomTable[ RandomTableSize ];
    } cRandomTable;
}

// Construction //////////////////////////////////////////////////////////////////////////
IntlText::EncParse::EncParse
//////////////////////////////////////////////////////////////////////////////////////////
(
 FILE *fNewFile // File to auto-decrypt.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    fFile = fNewFile;
    rnd.SetSeed( 11677 );
}
//////////////////////////////////////////////////////////////////////////////////////////
int IntlText::EncParse::GetChar( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the next character in the parsed file.
// 
// Return: int, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    int ch = fgetc( fFile );

    if( ch == EOF ){
        return EOF;
    }
    
    //char bRnd = cRandomTable.GetChar( ftell( fFile ) );
    //rnd.SetSeed( static_cast< uhyper >( ftell( fFile ) ) * static_cast< uhyper >( 2309281 ) );
    //char bRnd = (char)rnd( -128, 128 );
    
//    char cEnc = cRandomTable.GetChar( ftell( fFile ) ) ^ (char)ch;//BLBLBL tentative de suppression du chiffrage
    //char cEnc = bRnd ^ (char)ch;

    //qwLastSeed = rnd.GetSeed();

    //TRACE( "%c(%u^%u)", cEnc, ch, cRandomTable.GetChar( ftell( fFile ) ) );


    //return cEnc;//BLBLBL tentative de suppression du chiffrage
	return ch;
}
//////////////////////////////////////////////////////////////////////////////////////////
void IntlText::EncParse::SeekOneBefore( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Seek the parse one step before current.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    //rnd.SetSeed( qwLastSeed );
    fseek( fFile, -1, SEEK_CUR );

   // rnd.SetSeed( 11677 );
   // int  i;
   // long count = ftell( fFile );
   // TRACE( "\r\ncount=%u", count );
   // for( i = 0; i < count; i++ ){
   //     rnd( 0, 255 );
   // }
}
//////////////////////////////////////////////////////////////////////////////////////////
void IntlText::EncParse::SeekOneBeforeEnd( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Seek the parse one step before end.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    fseek( fFile, -1, SEEK_END );
}

//////////////////////////////////////////////////////////////////////////////////////////
void IntlText::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Initializes the string buffer.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    int i;
    // Sets all languages to NULL
    for( i = 0; i < NB_SUPPORTED_LNG; i++ ){
        lpLang[ i ].lpcsStrings = NULL;
    }

    wDefaultLng = 0xFFFF;   // No default language.
}

//////////////////////////////////////////////////////////////////////////////////////////
void IntlText::Destroy( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Frees string resources
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    int i;
    // Unmaps all views
    for( i = 0; i < NB_SUPPORTED_LNG; i++ ){
        if( lpLang[ i ].lpcsStrings != NULL ){
            delete [] lpLang[ i ].lpcsStrings;
        }        
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL IntlText::ToChar
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
 EncParse &encFile,   // Advances the file pointer to the next char 'ch'
 char ch,       // Char to advance to.
 const char *no,// Chars which shouldn't be encountered when search for ch.
 WORD &wLine    // Line count for debugging.
)
// Return: BOOL, TRUE if function is at char, FALSE if an error occured.
//////////////////////////////////////////////////////////////////////////////////////////
{    
    char cCh;
    if( strchr( no, '\1' ) ){
        cCh = encFile.GetChar();        
        if( cCh == '\n' ) wLine++;
        while( cCh != EOF && cCh != ch && ( cCh == ' ' || cCh == '\r' || cCh == '\n' || cCh == '\t' ) ){
            cCh = encFile.GetChar();
            if( cCh == '\n' ) wLine++;            
        }

        if( cCh == EOF || ( cCh != ' ' && cCh != '\r' && cCh != '\n' && cCh != '\t' ) && cCh != ch ){
            return FALSE;
        }
    }else{
        cCh = encFile.GetChar();
        if( cCh == '\n' ) wLine++;

        //TRACE( "%u,", cCh );
        while( cCh != EOF && cCh != ch && strchr( no, cCh ) == NULL ){
            cCh = encFile.GetChar();     
            if( cCh == '\n' ) wLine++;
        }
    }    
    if( cCh == EOF /*|| strchr( no, cCh ) != NULL */){
        return FALSE;
    }

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL IntlText::FetchNumber
//////////////////////////////////////////////////////////////////////////////////////////
// Fetches the next number in the specified file.
// 
(
 EncParse &encFile,       // File to fetch number from
 DWORD &dwNumber,   // DWORD in which to put number.
 WORD &wLine        // Line count for debugging.
)
// Return: BOOL, TRUE if function succeeded, FALSE if any error occured
//////////////////////////////////////////////////////////////////////////////////////////
{    
    char ch = encFile.GetChar();
    if( ch == '\n' ) wLine++;
    // Eleminate white spaces.
    while( ch != EOF && ch == ' ' ){        
        ch = encFile.GetChar();
        if( ch == '\n' ) wLine++;
    }

    dwNumber = 0;
    while( ch != EOF && isdigit( ch ) ){
        dwNumber *= 10;
        dwNumber += ch - '0';
        ch = encFile.GetChar();
        if( ch == '\n' ) wLine++;
    }
    // Reposition to last char.
    //fseek( fFile, -1, SEEK_CUR );
    encFile.SeekOneBefore();
    if( ch == EOF ){
        return FALSE;
    }

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL IntlText::FetchString
//////////////////////////////////////////////////////////////////////////////////////////
// Fetches the next string in the file
// 
(
 EncParse &encFile,       // The file
 CString &csString, // The string which will contain the string.
 WORD &wLine        // Line count for debugging.
)
// Return: BOOL, TRUE if function succeeded. FALSE if any error occured.
//////////////////////////////////////////////////////////////////////////////////////////
{
    BOOL boError;
    BOOL boEndString;    
    BOOL boEndChunck;
    char ch;    

    boError = FALSE;
    boEndString = FALSE;

    CString csChunck;
    
    while( !boEndString ){        
        csChunck = "";

        boEndChunck = FALSE;

        // Fetch chunck        
        while( !boEndChunck ){
            ch = encFile.GetChar();
            if( ch == '\n' ) wLine++;

            switch( ch ){
            case EOF:
                boError = TRUE;
                boEndChunck = TRUE;
                break;
            case '"':
                // If "" paste a single "
                if( encFile.GetChar() == '"' ){
                    csChunck += '"';
                }
                // Otherwise end chunck.
                else{
                    boEndChunck = TRUE;
                }
                break;
            default:
                // Any other char should be added to chunck
                csChunck += ch;           
                break;
            }                      
        }

        if( ch != EOF ){        
            // Try to find another chunck
            ch = encFile.GetChar();
            if( ch == '\n' ) wLine++;
            while( ch == ' ' || ch == '\r' || ch == '\n' ){
                ch = encFile.GetChar();
                if( ch == '\n' ) wLine++;
            }
            // Is ch the beginning of a new chunck?
            if( ch != '"' ){
                if( ch == EOF ){
                    //fseek( fFile, -1, SEEK_END );
                    encFile.SeekOneBeforeEnd();
                }
                // If not, end string
                boEndString = TRUE;
            }

            // Add chuck to string
            csString += csChunck;
        }else{
            boError = TRUE;
        }
    }

//    TRACE( "\r\nFound string %s!", (LPCTSTR)csString );

    return !boError;
}
//////////////////////////////////////////////////////////////////////////////////////////
BOOL IntlText::ParseLngFile
//////////////////////////////////////////////////////////////////////////////////////////
// Parses the language file and loads all its strings.
// 
(
 EncParse &encFile,   // The file from which we should load the strings.
 WORD wLangID,   // Language ID of the file being loaded.
 TemplateList< STR_ID > &tlStrings
)
// Return: BOOL, TRUE if file parsed successfully. FALSE if any error occured.
//////////////////////////////////////////////////////////////////////////////////////////
{
    int nError = 0;
    DWORD dwStringID;
    CString csString;
    WORD wLine = 1;
   
    // While it finds string ID blocks.
    while( ToChar( encFile, '(', ")\"", wLine ) && nError == 0 ){
        // Fetch string ID.
        if( FetchNumber( encFile, dwStringID, wLine ) ){

            //TRACE( "\r\nFound string ID (%u)", dwStringID );
            
            // Make sure parenthesis is closed to avoid conflicts
            if( ToChar( encFile, ')', "(\"", wLine ) ){
                // Go to string definition
                if( ToChar( encFile, '"', "()\1", wLine ) ){
                    csString = "";
                    // Fetch string.
                    if( FetchString( encFile, csString, wLine ) ){
                        // Add string to string to list.
                        STR_ID *lpStrID = new STR_ID;
                        lpStrID->csString = csString;
                        lpStrID->dwStringID = dwStringID;
                        tlStrings.AddToTail( lpStrID );
                    }else{
                        nError = 4;
                    }
                }else{
                    nError = 3;
                }
            }else{
                nError = 2;
            }
        }else{
            nError = 1;
        }
    }

    if( nError != 0 ){
        CString csError;
        switch( nError ){
        case 1: csError.Format( "Language file error fetching string ID on line %u. (mind the carriage return in last line !)", wLine ); break;
        case 2: csError.Format( "Language file error: closing parenthesis not found on line %u.", wLine ); break;
        case 3: csError.Format( "Language file error trying to find string on line %u.", wLine ); break;
        case 4: csError.Format( "Language file error fetching string on line %u.", wLine ); break;
        default: csError.Format( "An unkown language file error occured on line %u.", wLine ); break;
        }
        _LOG_DEBUG
            LOG_DEBUG_LVL1,
            (char *)(LPCTSTR)csError
        LOG_

        return FALSE;
    }

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void IntlText::LoadLngDB
//////////////////////////////////////////////////////////////////////////////////////////
// Loads a language into the database
// 
(
    CString csFile     // File containing the language strings.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    BOOL boLoaded = FALSE;
    CString csLoadedFile;
    WORD wLangID;
    FILE *fFile;

    // If file could not be opened.
    csLoadedFile = csFile;
    fFile = fopen( (LPCTSTR)csLoadedFile, "rb" );
    
    if( fFile == NULL ){
        // Try adding the server's binary path.
        csLoadedFile = theApp.sPaths.csBinaryPath;
        csLoadedFile += csFile;
        TRACE( "Trying %s.", (LPCTSTR)csLoadedFile );
        fFile = fopen( (LPCTSTR)csLoadedFile, "rb" );  
        // If it again failed to open.
        if( fFile == NULL ){
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "Could not load language file %s.",
                (LPCTSTR)csFile
            LOG_
            // Nothing else to do here.
            return;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////
    BOOL boError;
    CString csError;
    CString csLang;
    CString csDefault;
    bool boDefault = false;

    EncParse encParser( fFile );

        
    char ch;
    ch = encParser.GetChar();
    while( ch != EOF && ch == ' ' ){
        ch = encParser.GetChar();
    }

    while( ch != EOF && isalpha( ch ) ){
        csLang += ch;
        ch = encParser.GetChar();
    }

    wLangID = 0xFFFF;
    if( SAME_STR( csLang, "english" ) ){
        wLangID = LNG_ENGLISH;
    }else
    if( SAME_STR( csLang, "italian" ) || SAME_STR( csLang, "italiano" ) ){
        wLangID = LNG_ITALIAN;
    }else
    if( SAME_STR( csLang, "french" ) || SAME_STR( csLang, "francais" ) ){
        wLangID = LNG_FRENCH;
    }else
    if( SAME_STR( csLang, "portugese" ) ){
        wLangID = LNG_PORTUGESE;
    }else
    if( SAME_STR( csLang, "spanish" ) || SAME_STR( csLang, "espanol" ) ){
        wLangID = LNG_SPANISH;
    }else
    if( SAME_STR( csLang, "german" ) || SAME_STR( csLang, "deutsh" ) ){
        wLangID = LNG_GERMAN;
    }else
    if( SAME_STR( csLang, "korean" ) ){
        wLangID = LNG_KOREAN;
    }

    // Fetch the word default.
    ch = encParser.GetChar();
    while( ch != EOF && ch == ' ' ){
        ch = encParser.GetChar();
    }
    while( ch != EOF && isalpha( ch ) ){
        csDefault += ch;
        ch = encParser.GetChar();
    }

    // If it was found, set this language to default.
    if( SAME_STR( csDefault, "default" ) ){
        boDefault = true;
    }

    if( wLangID != 0xFFFF ){
        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Loading language %s, file %s, lngID%u",
            (LPCTSTR)csLang,
            (LPCTSTR)csFile,
            wLangID
        LOG_

        if( wLangID < NB_SUPPORTED_LNG ){
            if( lpLang[ wLangID ].lpcsStrings == NULL ){            
                
                if( boDefault ){
 
                    if( wDefaultLng != 0xFFFF ){
                        _LOG_DEBUG
                            LOG_DEBUG_LVL2,
                            "A default language has already been set, language %s in file %s will not be default",
                            (LPCTSTR)csLang,
                            (LPCTSTR)csFile
                        LOG_
                    }else{
                        wDefaultLng = wLangID;

                        _LOG_DEBUG
                            LOG_DEBUG_LVL2,
                            "Setting default language to %s.",
                            (LPCTSTR)csLang
                        LOG_
                    }
                }
            
                TemplateList < STR_ID > tlStrings;
                if( ParseLngFile( encParser, wLangID, tlStrings ) ){
                    TRACE( "\r\nFound %u strings!", tlStrings.NbObjects() );

                    // Find highest string ID.
                    DWORD dwHighestID = 0;
                    tlStrings.ToHead();
                    while( tlStrings.QueryNext() ){
                        if( tlStrings.Object()->dwStringID > dwHighestID ){
                            dwHighestID = tlStrings.Object()->dwStringID;
                        }
                    }
                
                    // Allocate space for that much strings for that language.
                    lpLang[ wLangID ].lpcsStrings = new CString[ dwHighestID + 1 ];
                    lpLang[ wLangID ].dwMaxStrings = dwHighestID + 1;
                
                    // Setup the strings
                    tlStrings.ToHead();
                    while( tlStrings.QueryNext() ){
                        STR_ID *lpStrID = tlStrings.Object();

                        if( lpLang[ wLangID ].lpcsStrings[ lpStrID->dwStringID ].IsEmpty() ){
                            // Set string.
                            lpLang[ wLangID ].lpcsStrings[ lpStrID->dwStringID ] = lpStrID->csString;
                        }else{
                            _LOG_DEBUG
                                LOG_DEBUG_LVL2,
                                "String ID %u in language file %s has already been defined. Using only the first definition.",
                                lpStrID->dwStringID,
                                (LPCTSTR)csLoadedFile
                            LOG_
                        }
                    }
                }else{
                    boError = TRUE;
                    csError.Format( "Error parsing language file %s. Language will be invalid.", (LPCTSTR)csLoadedFile );
                }

                tlStrings.AnnihilateList();
            }else{
                boError = TRUE;
                csError.Format( "Language %s in file %s has already been loaded.", (LPCTSTR)csLang, (LPCTSTR)csLoadedFile );
            }
        }else{
            boError = TRUE;
            csError.Format( "Unsupported language %s in file %s .", (LPCTSTR)csLang, (LPCTSTR)csLoadedFile );
        }
    }else{
        boError = TRUE;
        csError.Format( "Unsupported language %s in file %s .", (LPCTSTR)csLang, (LPCTSTR)csLoadedFile );
    }

    if( boError ){
        _LOG_DEBUG
            LOG_DEBUG_LVL2,
            (char *)(LPCTSTR)csError
        LOG_
    }else{
        _LOG_DEBUG
            LOG_DEBUG_LVL1,
            "Loading language file %s .", 
            (LPCTSTR)csLoadedFile
        LOG_
    }

    fclose( fFile );        
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL IntlText::IsLngOK( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Verifies if at least one language was loaded and set the default language.
// 
// Return: BOOL, TRUE if there is at least one language.
//////////////////////////////////////////////////////////////////////////////////////////
{    
    BOOL boOK = FALSE;
    int i;
    for( i = 0; i < NB_SUPPORTED_LNG; i++ ){
        // If language exists
        if( lpLang[ i ].lpcsStrings != NULL ){
            // If no default language.
            if( wDefaultLng == 0xFFFF ){
                // Set default language
                wDefaultLng = i;

                _LOG_DEBUG
                    LOG_DEBUG_LVL2,
                    "Setting language ID%u as default language.",
                    i
                LOG_
            }
            boOK = TRUE;
        }
    }
    return boOK;
}

//////////////////////////////////////////////////////////////////////////////////////////
CString &IntlText::GetString
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the string defined by dwResource in the desired language
// 
(
 DWORD dwResource,  // String resource
 WORD wLanguage,    // Language ID
 CString &csSource  // Source string in which text will be put.
)
// Return: CString, the modified csSource
//////////////////////////////////////////////////////////////////////////////////////////
{    
    // If language is supported
    if( wLanguage < NB_SUPPORTED_LNG ){
        // If language wasn't loaded
        if( lpLang[ wLanguage ].lpcsStrings == NULL ){
            // Use default language
            wLanguage = wDefaultLng;
        }
    }else{
        // Use default language
        wLanguage = wDefaultLng;
    }
    // If dwResource is lower then the highest string ID.
    if( dwResource < lpLang[ wLanguage ].dwMaxStrings ){
        csSource = lpLang[ wLanguage ].lpcsStrings[ dwResource ];
    }else{
        csSource = "";
    }
    
    return csSource;
}

//////////////////////////////////////////////////////////////////////////////////////////
CString &IntlText::AppendString
//////////////////////////////////////////////////////////////////////////////////////////
// Appends a resource string into an existing CString.
// 
(
 DWORD dwResource,  // The resource string ID to load.
 WORD wLanguage,    // The language from which to load the string.
 CString &csSource  // The original CString;
)
// Return: CString, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // If language is supported
    if( wLanguage < NB_SUPPORTED_LNG ){
        // If language wasn't loaded
        if( lpLang[ wLanguage ].lpcsStrings == NULL ){
            // Use default language
            wLanguage = wDefaultLng;
        }
    }else{
        // Use default language
        wLanguage = wDefaultLng;
    }
    // If dwResource is lower then the highest string ID.
    if( dwResource < lpLang[ wLanguage ].dwMaxStrings ){
        csSource += lpLang[ wLanguage ].lpcsStrings[ dwResource ];
    }
    
    return csSource;
}

//////////////////////////////////////////////////////////////////////////////////////////
LPCTSTR IntlText::GetString
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the string buffer of the resource.
// 
(
 DWORD dwResource,  // The resource ID
 WORD wLanguage,     // The language
 const char *szDefault
)
// Return: LPCTSTR, the string buffer.
//////////////////////////////////////////////////////////////////////////////////////////
{
    LPCTSTR lpszStr = NULL;
    
    if( dwResource == 0 ){
        return szDefault;
    }

    // If language is supported
    if( wLanguage < NB_SUPPORTED_LNG ){
        // If language wasn't loaded
        if( lpLang[ wLanguage ].lpcsStrings == NULL ){
            // Use default language
            wLanguage = wDefaultLng;
        }
    }else{
        // Use default language
        wLanguage = wDefaultLng;
    }
    // If dwResource is lower then the highest string ID.
    if( dwResource < lpLang[ wLanguage ].dwMaxStrings ){
        lpszStr = (LPCTSTR)lpLang[ wLanguage ].lpcsStrings[ dwResource ];
    }else{
        lpszStr = szDefault;
    }

    return lpszStr;
}

//////////////////////////////////////////////////////////////////////////////////////////
WORD IntlText::GetDefaultLng( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the default server language.
// 
// Return: WORD, the language ID.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return wDefaultLng;
}

//////////////////////////////////////////////////////////////////////////////////////////
void IntlText::SendPlayerMessage
//////////////////////////////////////////////////////////////////////////////////////////
// Sends a server message to a player.
// 
(
 Unit *lpUnit,      // The Unit structure to send message to.
 DWORD dwID         // ID of the message to send.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( lpUnit != NULL ){
        TFCPacket sending;
        CString csMessage;

        csMessage = GetString( dwID, lpUnit->GetLang(), csMessage );

        sending << (RQ_SIZE)RQ_ServerMessage;
		sending << (short)30;
		sending << (short)3;
		sending << (CString &)csMessage;
		sending << (long)0x000A64E0/*RGB( 0, 100, 255 )*/;
		lpUnit->SendPlayerMessage( sending );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
const char *IntlText::ParseString
//////////////////////////////////////////////////////////////////////////////////////////
// Parses an 'intlstring' (in the form of: [id]default_text ) and returns a valid string.  
// 
(
 const char *szString,  // The intl string.
 WORD wLanguage        // The language in which to search the parsed string ID from. 
)
// Return: const char, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( szString == NULL ){
        return "";
    }
    
    int  nStrLen = strlen( szString );
    const char *szText = szString;

    if( nStrLen > 2 ){
        // If this string contains a language ID.        
        if( szString[ 0 ] == '[' ){
            int i = 1;
            DWORD dwID = 0;
            bool boDone = false;

            if( !isdigit( szString[ 1 ] ) ){
                boDone = true;
            }

            // Parse to get the ID.            
            while( !boDone ){
                dwID *= 10;
                dwID += szString[ i ] - '0';

                ++i;
                if( i < nStrLen ){                    
                    if( !isdigit( szString[ i ] ) ){
                        boDone = true;            
                    }
                }else{
                    boDone = true;
                }                
            }            
            
            // If the ID corresponds to a set language string.
            const char *szNameID = GetString( dwID, wLanguage );
            if( szNameID[ 0 ] != '\0' ){
                // Returns the string found in the language file.
                return szNameID;
            }
            // Otherwise increment szName to remove the [id] header.
            if( ++i < nStrLen ){
                // Returns the string's default value.
                szText = &szString[ i ];
            }else{
                // Otherwise return a null string.
                return "";
            }
        }
    }

    return szText;
}