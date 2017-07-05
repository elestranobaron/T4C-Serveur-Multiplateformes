#ifndef DEBUG_TOOLS_22112000
#define DEBUG_TOOLS_22112000

#include <string>

void SetErrorStrId( DWORD id );
void SetErrorStr( std::string lastError );
void SetProgramError( std::string debugString );
std::string GetErrorStr();


template< class T > 
class MsgBoxHelper{
public:
    MsgBoxHelper( T *parent ) : p( parent )
    {}

    DWORD ErrorBox( DWORD id, DWORD mbStyle = MB_OK ){
        return p->MessageBox( GetAppString( id ).c_str(), GetAppString( IDS_ERROR ).c_str(), mbStyle );
    }
    DWORD WarningBox( DWORD id, DWORD mbStyle = MB_OK ){
        return p->MessageBox( GetAppString( id ).c_str(), GetAppString( IDS_WARNING ).c_str(), mbStyle );
    }
    DWORD ErrorStrBox(){
        return p->MessageBox( GetErrorStr().c_str(), GetAppString( IDS_ERROR ).c_str() );
    }
private:
    T *p;
};

#endif // DEBUG_TOOLS_22112000