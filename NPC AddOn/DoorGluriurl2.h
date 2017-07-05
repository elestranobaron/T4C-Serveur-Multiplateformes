#include <NPCStructure.h>

#ifndef __DOORGLURIURL2_H
#define __DOORGLURIURL2_H

class DoorGluriurl2 : public NPCstructure{
public:   
   DoorGluriurl2();
   ~DoorGluriurl2();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif