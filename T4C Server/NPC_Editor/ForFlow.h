// Static Model

// 
/////////////////////////////////////////////////////////////////////////////
// FILE:    ForFlow
// PACKAGE: NPC_Editor
//	Implements the following classes:
//          ForFlow
//	Date:   November 08, 1900
//	Author: FrancoisL
/////////////////////////////////////////////////////////////////////////////
#ifndef __ForFlow__
#define __ForFlow__

// Include files
#include "../Core/BoostFormula.h"
#include "../Core/WDAFile.h"
#include "ControlFlow.h"

//  todo
namespace NPC_Editor
{
class ForFlow	: public ControlFlow
{
public:
	ForFlow();
	~ForFlow();
    
    std::string GetStartValue() const { return startValue; }
    void SetStartValue(const std::string &thestartValue){ startValue = thestartValue; }
    std::string GetEndValue() const { return endValue; }
    void SetEndValue(const std::string &theendValue){ endValue = theendValue; }
    std::string GetAssignedVar() const { return assignedVar; }
    void SetAssignedVar(const std::string &theendValue){ assignedVar = theendValue; }
    
    void SaveImp( WDAFile &file );
    void LoadImp( WDAFile &file );

protected:
    Instruction *Clone();

private:
    void UpdateName();

    std::string startValue;
    std::string endValue; 
    std::string assignedVar;

};

// END CLASS DEFINITION ForFlow
            
}
#endif // __ForFlow__