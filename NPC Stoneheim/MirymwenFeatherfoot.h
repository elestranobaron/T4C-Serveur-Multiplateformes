#include "NPCStructure.h"

#ifndef __MIRYMWENFEATHERFOOT_H
#define __MIRYMWENFEATHERFOOT_H

class MirymwenFeatherfoot : public NPCstructure{
public:   
    MirymwenFeatherfoot();
    ~MirymwenFeatherfoot();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
 	 void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

  
};

#endif
