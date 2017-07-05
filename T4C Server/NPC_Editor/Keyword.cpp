#include "stdafx.h"
#include "Keyword.h"
#include "InstructionFactory.h"

using namespace std;

namespace{
    string AnGetName(){
        return GetAppString( IDS_INST_KEYWORD );
    }
    string AnGetHelp(){
        return GetAppString( IDS_INST_KEYWORD_HELP );
    }    
};

namespace NPC_Editor
{

Keyword::Keyword()	: CompositeInstruction( AnGetName(), AnGetHelp(), InsKeyword )
{
    kwRelation = Or;

    // Always add a default SayText to keywords.
    Instruction *sayText = InstructionFactory::GetInstance()->CreateInstruction( InsSayText );
    subInstructions.push_back( sayText );
}

Keyword::~Keyword()
{
}
/////////////////////////////////////////////////////////////////////////////
void Keyword::SaveImp
/////////////////////////////////////////////////////////////////////////////
// 
//
(
WDAFile &file
)
// Return: WDAFile
/////////////////////////////////////////////////////////////////////////////
{
    DWORD rel = kwRelation;
    DWORD size = keywords.size();
    
    BYTE kwType = 0;
    if( IsInitKw() ){
        kwType = 1;
    }else if( IsDefaultKw() ){
        kwType = 2;
    }else if( IsByeKw() ){
		kwType = 3;
	}else if( IsDeathKw() ){
		kwType = 4;
	}else if( IsAttackKw() ){
		kwType = 5;
	}else if( IsAttackedKw() ){
		kwType = 6;
	}

    file.Write( kwType );
    file.Write( rel );
    file.Write( size );

    list< string >::iterator i;
    for( i = keywords.begin(); i != keywords.end(); i++ ){
        file.Write( *i );
    }
}
/////////////////////////////////////////////////////////////////////////////
void Keyword::LoadImp
/////////////////////////////////////////////////////////////////////////////
// 
//
(
WDAFile &file
)
// Return: WDAFile
/////////////////////////////////////////////////////////////////////////////
{
    DWORD rel = 0, size = 0, i;
    BYTE kwType;
    
    // Since the keywords will be loaded from the file, destroy the default SayText.
    list< Instruction * >::iterator k;
    for( k = subInstructions.begin(); k != subInstructions.end();){
		list< Instruction * >::iterator tmp = k;
		k ++;
		delete *tmp;
        k = subInstructions.erase(tmp);
    }

    file.Read( kwType );
    file.Read( rel );
    file.Read( size );

    if( kwType == 1 ){
        SetName( GetAppString( IDS_INITIAL_KEYWORD_NAME ) );
        SetHelpText( GetAppString( IDS_INITIAL_KEYWORD_HELP ) );
    }else if( kwType == 2 ){
        SetName( GetAppString( IDS_DEFAULT_KEYWORD_NAME ) );
        SetHelpText( GetAppString( IDS_DEFAULT_KEYWORD_HELP ) );
    }else if( kwType == 3 )	{
		SetName( GetAppString( IDS_BYE_KEYWORD_NAME ) );
        SetHelpText( GetAppString( IDS_BYE_KEYWORD_HELP ) );
	}else if( kwType == 4 )	{
		SetName( GetAppString( IDS_ONDEATH_KEYWORD_NAME ) );
        SetHelpText( GetAppString( IDS_ONDEATH_KEYWORD_HELP ) );
	}else if( kwType == 5 )	{
		SetName( GetAppString( IDS_ONATTACK_KEYWORD_NAME ) );
        SetHelpText( GetAppString( IDS_ONATTACK_KEYWORD_HELP ) );
	}else if( kwType == 6 )	{
		SetName( GetAppString( IDS_ONATTACKED_KEYWORD_NAME ) );
        SetHelpText( GetAppString( IDS_ONATTACKED_KEYWORD_HELP ) );
	}

    kwRelation = (KeywordRelations)rel;
    for( i = 0; i != size; i++ ){
        string kw;
        file.Read( kw );
        keywords.push_back( kw );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
Instruction *Keyword::Clone( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Clone a keyword
//////////////////////////////////////////////////////////////////////////////////////////
{
    Keyword *kw = new Keyword;
    
    kw->Copy( this );
    kw->keywords = this->keywords; 
	kw->kwRelation = this->kwRelation;

    return kw;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Keyword::UpdateName( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Updates the displayed name according to the keyword's content.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Do not update the default or init keyword's name.
    if( IsDefaultInitKw() ){
        return;
    }

    if( keywords.size() == 0 ){
        SetName( AnGetName() );
        return;
    }

    string newName;
    int curCount = 0;
    list< string >::iterator i;
    for( i = keywords.begin(); i != keywords.end(); i++ ){
        newName += *i;

        if( ++curCount < keywords.size() ){
            newName += ", ";
        }
    }
    SetName( newName );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Keyword::SetKw
//////////////////////////////////////////////////////////////////////////////////////////
// Sets a keyword and updates the keyword's name
// 
(
 const list< string > &kws // The new list of keywords.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    keywords = kws;

    UpdateName();
}

} // NPC_Editor

