#include "NPCStructure.h"

#ifndef __KHANWULGWORTH_H
#define __KHANWULGWORTH_H

class KhanWulgworth : public NPCstructure{
public:   
    KhanWulgworth();
   ~KhanWulgworth();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
