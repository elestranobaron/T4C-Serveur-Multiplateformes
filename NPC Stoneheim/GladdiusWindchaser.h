#include "NPCStructure.h"

#ifndef __GLADDIUSWINDCHASER_H
#define __GLADDIUSWINDCHASER_H

class GladdiusWindchaser : public NPCstructure{
public:   
    GladdiusWindchaser();
   ~GladdiusWindchaser();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
