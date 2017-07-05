#include "NPCStructure.h"

#ifndef __KYATHOSSHATTERSKULL_H
#define __KYATHOSSHATTERSKULL_H

class KyathosShatterskull : public NPCstructure{
public:   
    KyathosShatterskull();
   ~KyathosShatterskull();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
