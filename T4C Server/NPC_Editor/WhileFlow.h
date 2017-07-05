// Static Model

// 
/////////////////////////////////////////////////////////////////////////////
// FILE:    WhileFlow
// PACKAGE: NPC_Editor
//	Implements the following classes:
//          WhileFlow
//	Date:   November 08, 1900
//	Author: FrancoisL
/////////////////////////////////////////////////////////////////////////////
#ifndef __WhileFlow__
#define __WhileFlow__

// Include files
#include "../Core/BoostFormula.h"
#include "../Core/WDAFile.h"
#include "Condition.h"

//  todo
namespace NPC_Editor
{
class WhileFlow	: public Condition
{
public:
	WhileFlow();
	~WhileFlow();
    
    void SaveImp( WDAFile &file );
    void LoadImp( WDAFile &file );

    virtual void SetCondition(const std::string &thecondition);

protected:
    Instruction *Clone();

private:

    void UpdateName();
};

// END CLASS DEFINITION WhileFlow
            
}
#endif // __WhileFlow__