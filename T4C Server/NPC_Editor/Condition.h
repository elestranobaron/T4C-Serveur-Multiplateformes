#ifndef __Condition__
#define __Condition__

// Include files
#include "ControlFlow.h"

//  todo
namespace NPC_Editor
{
class Condition	: public ControlFlow
{
public:
	Condition::Condition( std::string name, std::string helpText, InstructionIds id ) :
        ControlFlow( name, helpText, id ){}

    virtual std::string GetCondition() const { return condition; }
    virtual void SetCondition(const std::string &thecondition){ condition = thecondition; }
    
    virtual void Copy( Instruction *theCopy ){
        this->condition = static_cast< Condition * >( theCopy )->condition;
        ControlFlow::Copy( theCopy );
    }

    void SaveImp( WDAFile &file ) = 0{
        file.Write( condition );
    }
    void LoadImp( WDAFile &file ) = 0{
        file.Read( condition );
    }

    void UpdateName( std::string condName ){
        if( condition.size() == 0 ){
            SetName( condName );        
            return;
        }

        std::string newName = condName;
        newName += "( ";
        newName += condition;
        newName += " )";
        SetName( newName );
    }

protected:
private:
    std::string condition;
};

// END CLASS DEFINITION ControlFlow
            
}
#endif // __ControlFlow__