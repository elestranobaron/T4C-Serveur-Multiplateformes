// Commands.h: interface for the Commands class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMANDS_H__A59AE261_3BCA_11D4_B5B2_00E0296B9056__INCLUDED_)
#define AFX_COMMANDS_H__A59AE261_3BCA_11D4_B5B2_00E0296B9056__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TFLAG        1
#define TNUMBER      2
#define TITEM        3
#define TSPELL       4
#define TGOLD        5

#define REQUAL       1
#define RDIFF        2
#define RSMALL       3
#define RBIG         4
#define RSMALLEQ     5
#define RBIGEQ       6

#define CGIVEITEM           1
#define CGIVEXP             2
#define CSETFLAG            3
#define CHEALPLAYER         4
#define CCONDTEXT           5
#define CBREAKCONVERSATION  6
#define CFIGHTPLAYER        7
#define CTAKEITEM           8
#define CTELEPORT           9
#define CCASTSPELL          10
#define CCASTSPELLSELF      11
#define CGIVEGOLD           12
#define CTAKEGOLD           13
#define CPRIVATESYSTEMMESSAGE   14
#define CGLOBALSYSTEMMESSAGE    15
#define CSHOUTMESSAGE           16
#define CSETGLOBALFLAG          17
#define CGIVEKARMA				18

#include "WDAFile.h"
#include <list>

class Commands;
class Script;
class ScriptItem{
public:
    friend Commands;
    friend Script;

    enum ItemType{
        tUndefined = -1,
        tCommand = 1,
        tFolder = 2,
        tConditionalCommand = 3,
        tConditionalText = 4,
        tContainer = 5,        
        tKeyword = 6,
        tConditionalTeleport = 7
    };

    ScriptItem( ItemType i );
    virtual ~ScriptItem() = 0;

    virtual void DisplayHelp( CWnd *targetWindow );
    virtual std::list< ScriptItem * > *Clone( bool &rootOnly ) = 0;
    virtual void Edit( CTreeCtrl &tree, HTREEITEM h ) = 0;
    virtual bool CanDelete() = 0;
    virtual void Save( WDAFile &o );
    virtual void Load( WDAFile &i, DWORD ver );

    virtual std::string   GetDisplayName(){ return displayName; };
    virtual void     SetDisplayName( std::string n ){ displayName = n; };
    virtual DWORD    GetImg(){ return img; };
    virtual DWORD    GetSelectedImg(){ return selectedImg; };
    virtual ItemType GetType(){ return type; };
    virtual DWORD    GetId(){ return id; };
    virtual void     SetId( DWORD newId ){ id = newId; };
    virtual void     SetImg( DWORD i ){ img = i; };
    virtual void     SetSelectedImg( DWORD i ){ selectedImg = i; };
    virtual void     SetName( std::string i ){ name = i; };
    virtual std::string   GetName(){ return name; };
    virtual std::string   GetHelp(){ return help; };

    virtual bool     IsFolder(){ return isFolder; };
protected:
    virtual void LoadImp( WDAFile &o, DWORD ver ) = 0;
    virtual void SaveImp( WDAFile &o ) = 0;

    ItemType type;
    DWORD    id;
    std::string   help;
    std::string   name;
    std::string   displayName;
    DWORD    img;    
    DWORD    selectedImg;
    bool     isFolder;
    HTREEITEM h;    
};

class Command : public ScriptItem{
public:
    friend Commands;
    Command  () : ScriptItem( tCommand ){};
    virtual std::list< ScriptItem * > *Clone( bool &rootOnly );

    virtual void Edit( CTreeCtrl &tree, HTREEITEM h );

    virtual bool CanDelete(){ return true; };    

    virtual void SaveImp( WDAFile &o );
    virtual void LoadImp( WDAFile &i, DWORD ver );
};

class ConditionalCommand : public ScriptItem{
public:
    friend Commands;
    ConditionalCommand() : ScriptItem( tConditionalCommand ){
        rel = leftType = rightType = leftVal = rightVal = val = to = 0;
    };
    virtual std::list< ScriptItem * > *Clone( bool &rootOnly );

    virtual void Edit( CTreeCtrl &tree, HTREEITEM h );

    virtual bool CanDelete(){ return true; };

    virtual void SaveImp( WDAFile &o );
    virtual void LoadImp( WDAFile &i, DWORD ver );

    DWORD valueType;
    bool  reqTo;
    
    DWORD rel;
    DWORD leftType;
    DWORD rightType;
    DWORD leftVal;
    DWORD rightVal;
    DWORD val;
    DWORD to;
};

class ConditionalText : public ScriptItem{
public:
    friend Commands;
    ConditionalText() : ScriptItem( tConditionalText ){
        rel = leftType = rightType = leftVal = rightVal = 0;
    };
    virtual std::list< ScriptItem * > *Clone( bool &rootOnly );

    virtual void Edit( CTreeCtrl &tree, HTREEITEM h );

    virtual bool CanDelete(){ return true; };

    virtual void SaveImp( WDAFile &o );
    virtual void LoadImp( WDAFile &i, DWORD ver );

    DWORD rel;
    DWORD leftType;
    DWORD rightType;
    DWORD leftVal;
    DWORD rightVal;
    std::string txt;
    
};

class ConditionalTeleport : public ScriptItem{
public:
    friend Commands;
    ConditionalTeleport() : ScriptItem( tConditionalTeleport ){
        rel = leftType = rightType = leftVal = rightVal = X = Y = WL = 0;
    };
    virtual std::list< ScriptItem * > *Clone( bool &rootOnly );

    virtual void Edit( CTreeCtrl &tree, HTREEITEM h );

    virtual bool CanDelete(){ return true; };

    virtual void SaveImp( WDAFile &o );
    virtual void LoadImp( WDAFile &i, DWORD ver );

    DWORD rel;
    DWORD leftType;
    DWORD rightType;
    DWORD leftVal;
    DWORD rightVal;
    DWORD X, Y, WL;    
};

/////////////////////////////////////
class AFolder : public ScriptItem{
public:
    AFolder() : ScriptItem( tFolder ){};
    virtual std::list< ScriptItem * > *Clone( bool &rootOnly );

    virtual void Edit( CTreeCtrl &tree, HTREEITEM h );

    virtual bool CanDelete(){ return false; };

    virtual void SaveImp( WDAFile &o );
    virtual void LoadImp( WDAFile &i, DWORD ver );

protected:
    std::list< ScriptItem * > script;
};
//////////////////////////////////////////
// ScriptItems which can contain subitems
class ScriptContainer : public ScriptItem{
public:
    ScriptContainer() : ScriptItem( tContainer ){
        isFolder = true;
    }
    ~ScriptContainer();

    virtual void InsertItem( ScriptItem *item, ScriptItem *insertAfter );
    std::list< ScriptItem * > &GetScript(){ return script; };

    virtual bool MoveItemUp( ScriptItem *item );
    virtual bool MoveItemDown( ScriptItem *item );
    virtual void Edit( CTreeCtrl &tree, HTREEITEM h );
    virtual void DeleteItem( ScriptItem *item );
    virtual bool CanDelete(){ return true; };

    virtual std::list< ScriptItem * > *Clone( bool &rootOnly );        

    virtual void SaveImp( WDAFile &o );
    virtual void LoadImp( WDAFile &i, DWORD ver );

private:
    std::list< ScriptItem * > script;    
};

/////////////////////////////////////
class Keyword : public ScriptContainer{
public:
    Keyword() : kwtype( Normal ), rel( ROR ){
        type = tKeyword;
    }

    enum KWType {
        Normal = 0,
        Intro = 1,
        End = 2,
		Bye = 3,
		Death = 4
    };
    enum Relation{
        ROR = 0, RAND = 1, RORDERED = 2
    };
   
    virtual std::list< ScriptItem * > *Clone( bool &rootOnly );

    void SetKWType( KWType itype ){ kwtype = itype; };
    KWType GetKWType(){ return kwtype; }

    virtual void Edit( CTreeCtrl &tree, HTREEITEM h );

    std::list< std::string > &GetKW(){ return keywords; };    

    void SetRelation( Relation i ){ rel = i; };
    Relation GetRelation(){ return rel; };

    void UpdateName();

    virtual bool CanDelete(){ 
        if( kwtype != Normal ){
            return false;
        }
        return true; 
    };

    virtual void SaveImp( WDAFile &o );
    virtual void LoadImp( WDAFile &i, DWORD ver );

    std::string txt;

private:
    KWType kwtype;
    std::list< std::string > keywords;
    Relation rel;
};


class Commands  
{
public:
    friend Script;

	virtual ~Commands();

    static Commands *GetInstance();

    void LoadCommands();

    std::list< ScriptItem * > *CreateScriptItem( DWORD id, ScriptItem::ItemType itemType, bool &rootOnly );

    void GetCmdList( std::list< Command * > &cmdList );
    
private:
    Commands();

    void LoadFunctions();
    void LoadMisc();

    ScriptItem *CreateItem( ScriptItem *flow,  DWORD id, std::string name, std::string help, DWORD img, DWORD selectedImg, HTREEITEM hparent );

    std::list< ScriptItem * > itemList;
};

#endif // !defined(AFX_COMMANDS_H__A59AE261_3BCA_11D4_B5B2_00E0296B9056__INCLUDED_)
