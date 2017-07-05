// Static Model

// 
/////////////////////////////////////////////////////////////////////////////
// FILE:    ElseIfFlow
// PACKAGE: NPC_Editor
//	Implements the following classes:
//          ElseIfFlow
//	Date:   November 08, 1900
//	Author: FrancoisL
/////////////////////////////////////////////////////////////////////////////
#ifndef __ElseIfFlow__
#define __ElseIfFlow__

// Include files
#include "Condition.h"
#include "../Core/BoostFormula.h"
#include "../Core/WDAFile.h"

//  todo
namespace NPC_Editor
{
class IfFlow;
class ElseIfFlow	: public Condition
{
public:
    friend IfFlow;

	ElseIfFlow();
	~ElseIfFlow();
    
    void SaveImp( WDAFile &file );
    void LoadImp( WDAFile &file );

    virtual void SetCondition(const std::string &thecondition);

protected:
    Instruction *Clone();

private:
    void UpdateName();
};

// END CLASS DEFINITION ElseIfFlow
            
}
#endif // __ElseIfFlow__