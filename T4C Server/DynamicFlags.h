// DynamicFlags.h: interface for the DynamicFlags class.
//
//////////////////////////////////////////////////////////////////////

#ifndef DYNAMICFLAGS_H_CLASS_PROTOTYPE
#define DYNAMICFLAGS_H_CLASS_PROTOTYPE

#if _MSC_VER >= 1000
#pragma once
#endif

#include "Lock.h"
#include <map>
#include <vector>

#pragma warning( disable : 4786 )

class EXPORT DynamicFlags  
{
public:
	DynamicFlags();
	virtual ~DynamicFlags();

    // FlagPair type.
    typedef std::vector< std::pair< unsigned long, long > > FlagCont;

	// Sets the value of 'flag'
	virtual void SetFlag( unsigned long dwFlagID, long lFlagValue );
	
	// Called to remove a flag
	virtual void RemoveFlag( unsigned long dwFlagID );

	// Views a flag (simple addition of static and dynamic flag)
	virtual long ViewFlag( unsigned long dwFlagID, long lDefaultValue = 0 );    

	// Returns the private members of DunamicFlags
    virtual void GetFlags( FlagCont &vFlags );

	// Destroys all dynamic flags
	virtual void DestroyFlags();    
private:	
    // No copy if this type is allowed.
    DynamicFlags( DynamicFlags & ){};
    void operator = ( DynamicFlags & ){};

    typedef std::map< unsigned long, long > FlagMap;

    CLock csThreadLock;

    FlagMap mFlagMap;

    friend CAutoLock;
};

#endif // DYNAMICFLAGS_H_CLASS_PROTOTYPE
