// Static Model

// 
/////////////////////////////////////////////////////////////////////////////
// FILE:    Command
// PACKAGE: NPC_Editor
//	Implements the following classes:
//          Command
//	Date:   November 08, 1900
//	Author: FrancoisL
/////////////////////////////////////////////////////////////////////////////
#ifndef __Command__
#define __Command__

// Include files
#include "Instruction.h"
#include "NPC_Editor.h"
#include "../Core/WDAFile.h"

#include <list>
#include <vector>

//  todo
namespace NPC_Editor
{
class Command	: public Instruction
{
public:
    class Attribute{
    public:
        CommandAttributes type;
        std::string paramName;
    };

	Command( std::string name, std::string helpText, InstructionIds id );
	~Command();
    void GetAttributes( std::vector<Attribute> &theAttrib){ theAttrib = attributes; }
	void SetAtributes(const std::vector<Attribute> &theattributes){	attributes = theattributes; }
    void AddAttribute( Attribute attrib ){
        attributes.push_back( attrib );
    }
    void GetValues(std::vector<std::string> &theValue);
    void SetValues(const std::vector<std::string> &thevalues);
    
    void SaveImp( WDAFile &file );
    void LoadImp( WDAFile &file );

    virtual void GetSubInstructions( std::list< Instruction * > &subInstructions ){};

protected:
    Instruction *Clone();

private:
    void UpdateName();

    std::string cmdName;

	std::vector<Attribute>	attributes; 

    std::vector<std::string>	values; 

};

// END CLASS DEFINITION Command
            
}
#endif // __Command__