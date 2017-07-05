#include "NPCStructure.h"

#ifndef __DIONYSUSSILVERSTEAM_H
#define __DIONYSUSSILVERSTEAM_H
			  	  
class DionysusSilverstream : public NPCstructure{
public:   
    DionysusSilverstream();
   ~DionysusSilverstream();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
