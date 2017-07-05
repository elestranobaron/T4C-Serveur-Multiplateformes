#include "NPCStructure.h"

class Brother1 : public NPCstructure{
public:   
    Brother1();
   ~Brother1();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
};
