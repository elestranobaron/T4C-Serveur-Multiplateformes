// Skills.cpp: implementation of the Skills class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "TFC_MAIN.h"
#include "Skills.h"
#include "IntlText.h"
#include "format.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

std::vector<void*> Skills::c_aSkills; //CPtrArray

LPCTSTR EXPORT _SKILL::GetName( WORD wLanguage ){
    return IntlText::ParseString( lpszSkillName, wLanguage );
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Registers a skill
//		lpszName:	String containing the name of the skill
//		lpFunc:		Callback function containing the code executing the skill.
//		lpAttrib:	Pointer to a SKILL_ATTRIBUTE structure
//		nHook:		Where the skill is hooked
void Skills::Register(LPCTSTR lpszName, DWORD descId, int nID, LPSKILL_CALLBACK lpFunc, 
					  LPSKILL_ATTRIBUTES lpAttrib, int nHook, LPSKILLPNTFUNC lpPntFunc){
	

	LPSKILL lpSkill = new SKILL;
	
    lpSkill->SetName( lpszName );
	lpSkill->lpFunc = lpFunc;
	lpSkill->nHook = nHook;
	lpSkill->nSkillID = nID;
	lpSkill->lpAddPntFunc = lpPntFunc;
	lpSkill->lpsaAttrib = lpAttrib;
    lpSkill->desc = descId;

	TRACE( "\r\nRegistering skill ID %u.", lpSkill->nSkillID );

	if (nID >= c_aSkills.size())
	{
		c_aSkills.resize(nID + 1);
	}
	c_aSkills[nID] = lpSkill;

	//c_aSkills.SetAtGrow(nID, lpSkill);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Executes a skill
//	nID:	Skill ID (which skill).
//	nHook:	Which type of intrinsic skill to use.
//	self/medium/target/valueIN/valueOUT:	Standard message.
//	lpusUserSkill:	Pointer to a USER_SKILL.
int Skills::ExecuteSkill(int nID, int nHook, Unit *self, Unit *medium, 
						  Unit *target, void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill){
	LPSKILL lpSkill;	
	int nReturn = SKILL_FAILED;

	if(nID < c_aSkills.size()){
		lpSkill = (LPSKILL)c_aSkills.at(nID);
		if(lpSkill){
			nReturn = lpSkill->lpFunc(nHook, self, medium, target, valueIN, valueOUT, lpusUserSkill);
			
			if( nReturn == SKILL_SUCCESSFULL || nReturn == SKILL_FAILED ){
				//UINT param[2];
				//param[0] = nID;
				//param[1] = nReturn;			
				//Broadcast::BCast(__EVENT_SKILL_USED, self->GetWL(), 20, param);
			}
		}
#ifdef _DEBUG
		else{
			TRACE(_TEXT("\r\n!Warning! Using unreferenced skill.\r\n"));
			TRACE(_TEXT("Dump: ID %u Hook %u self %08x medium %08x target %08 valueIN %08x valueOUT %08x\r\n"), 
					nID, nHook, self, medium, target, valueIN, valueOUT);
		}		
#endif
	}
#ifdef _DEBUG
	else{
		TRACE(_TEXT("\r\n!Warning! Using out-of-bound skill.\r\n"));
		TRACE(_TEXT("Dump: ID %u Hook %u self %08x medium %08x target %08 valueIN %08x valueOUT %08x\r\n"), 
			nID, nHook, self, medium, target, valueIN, valueOUT);
	}
#endif	

	return nReturn;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Determines if nID is a skill
//	nID:		The skill to query
//  lpnHook:	Pointer to an int which will receive on what is the skill hooked, NULL otherwise
// return:	TRUE, nID is a skill
BOOL Skills::IsSkill(int nID, LPINT lpnHook){	
	if(nID < c_aSkills.size()){
		LPSKILL lpSkill = (LPSKILL)c_aSkills.at(nID);
		if(lpSkill){
			if(lpnHook){
				*lpnHook = lpSkill->nHook;
				return TRUE;
			}
		}
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// This function returns TRUE if skill nID is learnable
//	nID:		ID of the skill to learn
//	uForWho:	Unit which would learn the skill
// return: TRUE, skill is learnable
BOOL Skills::IsSkillLearnable(int nID, Unit *uLearner, CString &reqText){
	
	if(nID < c_aSkills.size()){
		LPSKILL lpSkill = (LPSKILL)c_aSkills.at(nID);
		// Then check for 'nID'
		if(lpSkill){
			LPSKILL_ATTRIBUTES lpAttrib = lpSkill->lpsaAttrib;
			/*	s_saAttrib.Class
				s_saAttrib.Cost;
				s_saAttrib.Level;
				s_saAttrib.AGI;
				s_saAttrib.STR;
				s_saAttrib.END;
				s_saAttrib.INT;
				s_saAttrib.WIS;
				s_saAttrib.ClassPnts[WARRIOR];
				s_saAttrib.ClassPnts[MAGE];
				s_saAttrib.ClassPnts[THIEF];
				s_saAttrib.ClassPnts[PRIEST];
				s_saAttrib.tlSkillRequired;
			*/
            // Form the description string.
            TFormat format;

            reqText = _STR( 7277, uLearner->GetLang() );
            bool prev = false;
            bool nothin = true;
            if( lpAttrib->Level != 0 ){
                reqText += format( _STR( 7278, uLearner->GetLang() ), lpAttrib->Level );;
                prev = true;
                nothin = false;
            }
            if( lpAttrib->STR != 0 ){
                if( prev ){
                    reqText += ", ";
                }                
                reqText += format( _STR( 7279, uLearner->GetLang() ), lpAttrib->STR );
                prev = true;
                nothin = false;
            }
            if( lpAttrib->END != 0 ){
                if( prev ){
                    reqText += ", ";
                }                
                reqText += format( _STR( 7280, uLearner->GetLang() ), lpAttrib->END );;
                prev = true;
                nothin = false;
            }
            if( lpAttrib->AGI != 0 ){
                if( prev ){
                    reqText += ", ";
                }                
                reqText += format( _STR( 7281, uLearner->GetLang() ), lpAttrib->AGI );;
                prev = true;
                nothin = false;
            }
            if( lpAttrib->INT != 0 ){
                if( prev ){
                    reqText += ", ";
                }                
                reqText += format( _STR( 7282, uLearner->GetLang() ), lpAttrib->INT );
                prev = true;
                nothin = false;
            }
            if( lpAttrib->WIS != 0 ){
                if( prev ){
                    reqText += ", ";
                }                
                reqText += format( _STR( 7283, uLearner->GetLang() ), lpAttrib->WIS );
                prev = true;
                nothin = false;
            }

            if( lpAttrib->tlSkillRequired.NbObjects() != 0 ){
                if( prev ){
                    reqText += _STR( 7284, uLearner->GetLang() );
                }
                nothin = false;
                if( lpAttrib->tlSkillRequired.NbObjects() > 1 ){
                    reqText += _STR( 7285, uLearner->GetLang() );
                }else{
                    reqText += _STR( 7287, uLearner->GetLang() );
                }
                lpAttrib->tlSkillRequired.ToHead();
                if( lpAttrib->tlSkillRequired.QueryNext() ){
                    LPUSER_SKILL lpRequired = lpAttrib->tlSkillRequired.Object();
                    LPSKILL lpSkill = GetSkill( lpRequired->GetSkillID() );
                    if( lpSkill != NULL ){
                        reqText += lpSkill->GetName( uLearner->GetLang() );   
                    }
                        
                    while( lpAttrib->tlSkillRequired.QueryNext() ){
                        reqText += ", ";
                        lpRequired = lpAttrib->tlSkillRequired.Object();
                        LPSKILL lpSkill = GetSkill( lpRequired->GetSkillID() );
                        if( lpSkill != NULL ){
                            reqText += lpSkill->GetName( uLearner->GetLang() );   
                        }           
                    }
                }
            }
            if( nothin ){
                reqText += _STR( 7286, uLearner->GetLang() );
            }else{
                reqText += ".";
            }

            
			if(lpAttrib->Level <= (int)uLearner->GetLevel()){
				if( lpAttrib->AGI <= uLearner->GetTrueAGI() && 
					lpAttrib->STR <= uLearner->GetTrueSTR() &&
					lpAttrib->END <= uLearner->GetTrueEND() &&
					lpAttrib->INT <= uLearner->GetTrueINT() &&
					lpAttrib->WIS <= uLearner->GetTrueWIS()){
					
					BOOL boOK = TRUE;
					LPUSER_SKILL lpRequired;
					LPUSER_SKILL lpUserSkill;
					lpAttrib->tlSkillRequired.Lock();
					lpAttrib->tlSkillRequired.ToHead();
					while( lpAttrib->tlSkillRequired.QueryNext() && boOK ){
						lpRequired = lpAttrib->tlSkillRequired.Object();

						lpUserSkill = uLearner->GetSkill( lpRequired->GetSkillID() );
						// If user has the skill
						if( lpUserSkill ){
							// If user doesn't has enough skill points in the required skill.
							if( lpUserSkill->GetTrueSkillPnts() < lpRequired->GetTrueSkillPnts() ){
								// user cannot learn skill
								boOK = FALSE;
							}
						}else{
							// Cannot learn if user doesn't have a required skill.
							boOK = FALSE;
						}							
					}
					lpAttrib->tlSkillRequired.Unlock();

                    if( !boOK ){
                        _LOG_DEBUG
                            LOG_DEBUG_LVL4,
                            "Skill %u is NOT valid for teaching.",
                            nID
                        LOG_
                    }else{
                        _LOG_DEBUG
                            LOG_DEBUG_LVL4,
                            "Skill %u is valid for teaching.",
                            nID
                        LOG_
                    }

					return boOK;

                }else{
                    _LOG_DEBUG
                        LOG_DEBUG_LVL4,
                        "Skill %u is NOT valid for teaching. User: AGI=%u STR=%u END=%u INT=%u WIS=%u.",
                        nID,
                        uLearner->GetTrueAGI(),uLearner->GetTrueSTR(),uLearner->GetTrueEND(),uLearner->GetTrueINT(),
                        uLearner->GetTrueWIS()
                    LOG_
                    _LOG_DEBUG
                        LOG_DEBUG_LVL4,
                        "Skill %u is NOT valid for teaching. Skill: AGI=%u STR=%u END=%u INT=%u WIS=%u.",
                        nID,
                        lpAttrib->AGI,lpAttrib->STR,lpAttrib->END,lpAttrib->INT,
                        lpAttrib->WIS
                    LOG_

                }
            }else{
                _LOG_DEBUG
                    LOG_DEBUG_LVL4,
                    "Skill %u is NOT valid for teaching. User level %u vs required level %u.", nID, uLearner->GetLevel(), lpAttrib->Level
                LOG_
            }
		}
	}

	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////
// Returns a LPSKILL pointer of the skill, or NULL
//	nID:	ID of the skill to get.
// return:	A pointer to the skill queried.
LPSKILL Skills::GetSkill(int nID){
	if(nID < c_aSkills.size()){
		return (LPSKILL)(c_aSkills.at(nID));
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////
LPSKILL Skills::GetSkillByName
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the skill with the given name.
// 
(
 std::string skillName, // The skill name
 WORD wLang             // The language.
)
// Return: LPSKILL, NULL if the skill doesn't exist.
//////////////////////////////////////////////////////////////////////////////////////////
{
    int i;
    for( i = 0; i < c_aSkills.size(); i++ ){
        LPSKILL lpSkill = reinterpret_cast< LPSKILL >( c_aSkills.at( i ) );
        if( lpSkill != NULL && 
            stricmp( lpSkill->GetName( wLang ), skillName.c_str() ) == 0 ){
            return lpSkill;
        }
    }
    return NULL;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// This function returns the ID of the skill of name name
/*int Skills::GetSkillIDByName(LPCTSTR lpszName){
	int nID = 0;

	for(nID = 0; nID < c_aSkills.GetSize(); nID++){			
		if(strcmp(lpszName, ((LPSKILL)(c_aSkills.GetAt(nID)))->lpszSkillName))
			return nID;	
	}

	return -1;
} */

//////////////////////////////////////////////////////////////////////////////////////////
void Skills::TrainSkill
//////////////////////////////////////////////////////////////////////////////////////////
// Called to train points in a skill.
// 
(
 Unit *lpuTrained,			// Unit that trained.
 LPUSER_SKILL lpUserSkill,	// User skill to train.
 DWORD dwNbPoints			// Number of skill points to add, to train.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPSKILL lpSkill = GetSkill( lpUserSkill->GetSkillID() );

	if(lpSkill){
		// Calls the skill specific training function.
		if( lpSkill->lpAddPntFunc )
			lpSkill->lpAddPntFunc(lpuTrained, lpUserSkill, dwNbPoints);
		
		lpUserSkill->SetSkillPnts( lpUserSkill->GetTrueSkillPnts() + dwNbPoints );
	}

}


//////////////////////////////////////////////////////////////////////////////////////////
void Skills::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creates the class
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
}


//////////////////////////////////////////////////////////////////////////////////////////
void Skills::Destroy( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Destroys skills
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPSKILL lpSkill;
	int i;
	
	for(i = 0; i < c_aSkills.size(); i++){
		 lpSkill = (LPSKILL)c_aSkills.at(i);
		 if(lpSkill){
			lpSkill->Delete();
		}
	}
}
