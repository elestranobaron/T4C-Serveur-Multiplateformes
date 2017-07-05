#include "NPCStructure.h"

#ifndef __GRANTHORNKEEP_H
#define __GRANTHORNKEEP_H

class GrantHornkeep : public NPCstructure{
public:   
    GrantHornkeep();
     ~GrantHornkeep();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
  
};

#endif
