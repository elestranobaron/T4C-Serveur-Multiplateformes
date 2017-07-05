#include <NPCStructure.h>

#ifndef __TABLENOMAD1_H
#define __TABLENOMAD1_H

class TableNomad1 : public NPCstructure{
public:   
   TableNomad1();
   ~TableNomad1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif