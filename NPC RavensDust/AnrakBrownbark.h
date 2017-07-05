#include "NPCStructure.h"

#ifndef __ANRAKBROWNBARK_H
#define __ANRAKBROWNBARK_H

class AnrakBrownbark : public NPCstructure{
public:   
    AnrakBrownbark();
   ~AnrakBrownbark();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );

};

#endif
