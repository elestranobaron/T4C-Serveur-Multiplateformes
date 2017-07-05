#include "NPCStructure.h"

#ifndef __MADMADRIGAN_H
#define __MADMADRIGAN_H

class MadMadrigan : public NPCstructure{
public:   
    MadMadrigan();
   ~MadMadrigan();
    void Create( void );
    void OnAttack( UNIT_FUNC_PROTOTYPE );
	 void OnPopup( UNIT_FUNC_PROTOTYPE );
    
};

#endif 

