#include "NPCStructure.h"

#ifndef __TALONIRONGAZE_H
#define __TALONIRONGAZE_H

class TalonIrongaze : public NPCstructure{
public:   
    TalonIrongaze();
   ~TalonIrongaze();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
