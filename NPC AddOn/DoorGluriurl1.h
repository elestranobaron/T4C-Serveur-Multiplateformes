#include <NPCStructure.h>

#ifndef __DOORGLURIURL1_H
#define __DOORGLURIURL1_H

class DoorGluriurl1 : public NPCstructure{
public:   
   DoorGluriurl1();
   ~DoorGluriurl1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif