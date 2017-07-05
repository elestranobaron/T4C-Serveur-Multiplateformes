#include "NPCStructure.h"

#ifndef __THORBINWILDHEART_H
#define __THORBINWILDHEART_H

class ThorbinWildheart : public NPCstructure{
public:   
    ThorbinWildheart();
   ~ThorbinWildheart();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
