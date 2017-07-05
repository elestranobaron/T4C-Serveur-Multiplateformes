// Skills.h: interface for the Skills class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKILLS_H__D02F3B81_5542_11D1_BD7A_00E029058623__INCLUDED_)
#define AFX_SKILLS_H__D02F3B81_5542_11D1_BD7A_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include <string.h>
#include "vdlist.h"
#include "SkillListing.h"
#include "IntlText.h"

#define NB_CLASS 4

#define SKILL_SUCCESSFULL	1	// Skill was successfully used. Broadcasted.
#define SKILL_FAILED		2	// Skill failed. Broadcasted.
#define SKILL_NO_FEEDBACK	3	// Tells the ExecuteSkill function not to do any feedback towards
								// the client.
#define SKILL_PERSONNAL_FEEDBACK_SUCCESSFULL	4	// Only notify player of successfull skill.
#define SKILL_PERSONNAL_FEEDBACK_FAILED			5	// Only notity player of failed skill.

////////////////////////////////////////////
// Specifies at which event should the skill
// callback fonction should be called
#define NB_SKILL_HOOKS		7		// Quantity of possible hooks defined below

// Defined for array manipulations on characters.
#define Hook_None			0		// No hook, the skill must be 'used'.
#define Hook_OnAttack		1		// When player attacks.
#define Hook_OnAttacked		2		// When player gets attacked.
#define Hook_OnHit			3		// When player is hit.
#define Hook_OnMove			4		// When player moves.
#define Hook_OnTraining		5		// When player trains.
#define Hook_OnRegen		6		// When player passes its regeneration

// Defined for flag manipulations, when registering skills.
#define HOOK_USE				0x00000001	// Specifies use operations.
#define HOOK_ATTACK				0x00000002	// Auto-skill use on attacks.
#define HOOK_ATTACKED			0x00000004	// Auto-skill use when attacked.
#define HOOK_HIT				0x00000008	// Auto-skill use when struck.
#define HOOK_MOVE				0x00000010	// Auto-skill use when moving.
#define HOOK_TRAINING			0x00000020	// Auto-skill use when training.
#define HOOK_REGEN				0x00000040	// Auto-skill use when regenerating.
#define HOOK_USE_TARGET_POS		0x00000080	// Skill usable on a land position.
#define HOOK_USE_TARGET_UNIT	0x00000100	// Skill usable on a unit.
#define HOOK_NOTHING			0x00000200	// Skill never triggered.


// Typedef of the skill callback function.
typedef int (*LPSKILL_CALLBACK)(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
								void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

// Typedef of the skill add points function.
typedef void (*LPSKILLPNTFUNC)(Unit *lpuTrained, LPUSER_SKILL lpUserSkill, DWORD dwPnts);

// The skill attributes
typedef struct _SKILL_ATTRIBUTES{
 //8/Powerful Blow:   Warriors.  10  5-1000 AU    09  STR: 35.           25W.
	int Class;
	int Cost;
	int Level;
	int AGI, STR, END, INT, WIS, WIL, LCK;
	int ClassPnts[NB_CLASS];
	TemplateList <USER_SKILL> tlSkillRequired;
} SKILL_ATTRIBUTES, *LPSKILL_ATTRIBUTES;
//////////////////////////////////////////////////////////////////////////////////////////
// Easy skill requirement adding.
#define ADD_REQUIRED_SKILL( _Skill, _Strength )	{LPUSER_SKILL lpUserSkill = new USER_SKILL;\
	lpUserSkill->SetSkillID( _Skill );\
	lpUserSkill->SetSkillPnts( _Strength );\
	s_saAttrib.tlSkillRequired.AddToTail( lpUserSkill );\
}

class Skills;

// Skill structure
typedef struct _SKILL
{
    _SKILL( void ){ lpszSkillName[ 0 ] = 0; };

    LPCTSTR EXPORT GetName( WORD wLanguage );
    void                SetName( const char *lpszName ){
        strcpy( lpszSkillName, lpszName );        
    }
    LPCTSTR GetDesc( WORD wLanguage ){
        return _STR( desc, wLanguage );
    }

	LPSKILL_CALLBACK	lpFunc;				// Skill callback function.	
	SKILL_ATTRIBUTES	*lpsaAttrib;		// Attributes of the skill.
	int					nHook;				// Hook of the skill.
	int					nSkillID;			// Array index of the skill.
	LPSKILLPNTFUNC		lpAddPntFunc;		// Function to call when points are added to a skill.
    DWORD               desc;

    void Delete( void ){ delete this; };

private:
    // Prohibit assignement and stack instantiation of this class.
    ~_SKILL( void ){}
    PROHIBIT_ASSIGNMENT( _SKILL );
    TCHAR				lpszSkillName[60];	// Name of the skill.

} SKILL, *LPSKILL;


// The class
class EXPORT Skills
{
public:
	// Creates all internal structures
	static void Create();

	// Destroys all internal structures
	static void Destroy();

	// Registers a skill in the skill list
	static void Register(LPCTSTR lpszName, DWORD descId, int nID, LPSKILL_CALLBACK lpCallBack, 
						 LPSKILL_ATTRIBUTES lpAttrib, int nHook, LPSKILLPNTFUNC lpPntFunc);

	static int ExecuteSkill(int nID, int nHook, 
					  Unit *self, Unit *medium, Unit *target, void *valueIN, void *valueOUT,
					  LPUSER_SKILL lpusUserSkill);
	
	//static int GetSkillIDByName(LPCTSTR lpszName);

	// returns TRUE if nID is a skill ID
	static BOOL IsSkill(int nID, LPINT lpnHook);

	static BOOL IsSkillLearnable(int nID, Unit *uForWho,CString &reqText);

	static LPSKILL GetSkill(int nID);
    static LPSKILL GetSkillByName( std::string skillName, WORD wLang );

	static void TrainSkill(Unit *lpuTrained, LPUSER_SKILL lpUserSkill, DWORD dwNbPoints);

private:
	static int nSkillID;

	static std::vector<void*> c_aSkills; //CPtrArray //GetSize size GetAt at
};

#endif // !defined(AFX_SKILLS_H__D02F3B81_5542_11D1_BD7A_00E029058623__INCLUDED_)
