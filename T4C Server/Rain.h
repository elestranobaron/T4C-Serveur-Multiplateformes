// Rain.h: interface for the Rain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RAIN_H__157E11BF_F932_4E24_807D_63F1A1FF6E03__INCLUDED_)
#define AFX_RAIN_H__157E11BF_F932_4E24_807D_63F1A1FF6E03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Unit.h"

class Rain  
{
public:
	Rain();
	virtual ~Rain();
	
	static Rain *GetInstance();
	bool GetState(void);
	void SetState(short bNewState);
	void SwitchState(void);

	void SendRainState( Unit* self );

private:
	bool bRain;

};

#endif // !defined(AFX_RAIN_H__157E11BF_F932_4E24_807D_63F1A1FF6E03__INCLUDED_)
