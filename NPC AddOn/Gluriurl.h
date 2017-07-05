#include "NPCStructure.h"

#ifndef __GLURIURL_H
#define __GLURIURL_H

class Gluriurl : public NPCstructure{
public:
  Gluriurl();
  ~Gluriurl();
	void Create( void );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE ); 
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );

};

#endif
