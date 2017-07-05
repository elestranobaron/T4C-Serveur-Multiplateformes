// Snow.h: interface for the Snow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNOW_H__230144D2_D30F_48F4_80A7_604F5898CD17__INCLUDED_)
#define AFX_SNOW_H__230144D2_D30F_48F4_80A7_604F5898CD17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Snow  
{
public:
	Snow();
	virtual ~Snow();

	static Snow *GetInstance();
	bool GetState(void);
	void SetState(short bNewState);
	void SwitchState(void);

private:
	bool bSnow;


};

#endif // !defined(AFX_SNOW_H__230144D2_D30F_48F4_80A7_604F5898CD17__INCLUDED_)
