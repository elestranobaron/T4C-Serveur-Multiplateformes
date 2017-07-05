/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "BrotherThorkas.H"

BrotherThorkas::BrotherThorkas()
{}

BrotherThorkas::~BrotherThorkas()
{}
 
extern NPCstructure::NPC BrotherThorkasNPC;

void BrotherThorkas::Create( void )
{
      npc = ( BrotherThorkasNPC );
      SET_NPC_NAME( "[2933]Brother Thorkas" );  
      npc.InitialPos.X = 1565; 
      npc.InitialPos.Y = 2398;
      npc.InitialPos.world = 0;
}

void BrotherThorkas::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{
CONSTANT HEALING = 1; 
CONSTANT GUIDANCE = 2;
CONSTANT DONATION = 3;
CONSTANT SANCTUARY = 4;
CONSTANT CHALICE = 5;
CONSTANT HOLYWATER = 6; 

InitTalk

Begin
INTL( 4357, "\"Artherk\" blesses you my friend. You are welcome in our humble temple.")

Command2(INTL( 485, "WHO ARE YOU"),INTL( 3694, " NAME"))
INTL( 4358, "I am Brother Thorkas. I am pleased to make your acquaintance.")
 
Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 4359, "I spread seeds of rightenousness for each sin caused by humans. My life "
"is devoted to the study of the various prophecies and of the upcoming "
"\"4th\" \"coming\" event. I also try to ease pain and \"suffering\" whenever "
"I am given the opportunity. In addition, I have some \"spells\" I would be willing "
"to share with you. Blessed be Artherk, he has also given me the Gift of \"sanctuary\" and "
"the ability to create \"holy\" \"water\".")

CmdAND(INTL( 8039, "RING"),INTL( 10262, "FAITH")) 
INTL( 10606, "I have some rings of faith that I would gladly offer you in return for one of our stolen "
"\"chalices\".") 

Command(INTL( 7911, "HOLY WATER"))
INTL( 7912, "If you are in need of holy water, a cleric of Artherk such as I can perform a prayer to bless a \"flask\" \"of\" "
"\"crystal\" \"water\". However, a small donation of 1000 gold to our humble temple is required for this service. "
"Do you have the required donation and a flask of crystal water?")
SetYesNo(HOLYWATER)

YES(HOLYWATER)
IF ((Gold < 1000) && (CheckItem(__OBJ_FLASK_OF_CRYSTAL_WATER) == 0))
	Conversation
	INTL( 7913, "You do not have a flask of crystal water and the required donation fee.")
ELSEIF (Gold < 1000)
	Conversation
	INTL( 7914, "You do not have enough gold.")
ELSEIF (CheckItem(__OBJ_FLASK_OF_CRYSTAL_WATER) == 0)
	Conversation
	INTL( 7915, "You do not have a flask of crystal water.")
ELSE
	Conversation
	INTL( 7916, "Done! You now have a flask of holy water!")
	PRIVATE_SYSTEM_MESSAGE(INTL( 7917, "You give 1000 gold to Thorkas."))
	PRIVATE_SYSTEM_MESSAGE(INTL( 7918, "Thorkas gives you a flask of holy water.")) 
	TakeGold(1000)
	TakeItem(__OBJ_FLASK_OF_CRYSTAL_WATER)
	GiveItem(__OBJ_FLASK_OF_HOLY_WATER) 
ENDIF

NO(HOLYWATER)
Conversation
INTL( 7919, "If you ever need holy water, feel free to ask.")

YesNoELSE(HOLYWATER)
Conversation
INTL( 7920, "Well, do you want me to bless a flask of crystal water or not?")
SetYesNo(HOLYWATER) 

Command(INTL( 7921, "FLASK OF CRYSTAL WATER"))
INTL( 7922, "Surely a seasoned adventurer such as you can easily find a flask of crystal water somewhere.")

Command(INTL( 741, "4TH COMING"))
INTL( 4360, "The prophecies are rather nebulous regarding that particular event. The "
"Key, according to what is written, lies in the previous \"events\".")

Command(INTL( 4361, "EVENT"))
INTL( 4362, "I do not have enough information about the previous events. Perhaps the "
"elves or the dwarves might know something... if they still exist on "
"this plane.")

Command2(INTL( 4363, "MONSIGNOR"),INTL( 4364, "DAMIEN"))
INTL( 4365, "Monsignore Damien was once a great member of our order, but he fell from grace for reasons "
"that I'm not aware of. All I know is that he blamed a certain \"Shadeen\" for framing him. "
"He lives in seclusion, now, and it would probably be wise to avoid mentioning her name "
"in front of him.")

Command(INTL( 8039, "RING"))
""
IF(CheckFlag(__FLAG_QUEST_FOR_BONES) == 4)
	Conversation
	INTL( 10114, "A magic ring you say? Let me see... ACK! This ring is EVIL! I will have nothing to do with it! You had best "
	"take it back to wherever you found it or whoever told you to come here.")
	GiveFlag(__FLAG_QUEST_FOR_BONES, 5)
ELSEIF(CheckFlag(__FLAG_QUEST_FOR_BONES) >= 5)
	Conversation
	INTL( 10115, "I have already told you I will have nothing to do with your ring.")
ELSE
	Conversation
	INTL( 4012, "Perhaps others would like to know about that.")
ENDIF

Command(INTL( 1581, "SHADEEN"))
INTL( 4366, "She is a well-known criminal on Raven's Dust. I do not mingle with such evil people.")

Command(INTL( 1243, "ARTHERK"))
INTL( 4367, "Artherk is the god of healing and mending. It is He who we praise in "
"this small temple. Unfortunately, we have been the target of thieves "
"recently. Sadly, they have been able to steal numerous of our precious "
"golden \"chalices\".")

Command(INTL( 4368, "SUFFER"))
INTL( 4369, "Why do we suffer? That is not ours to know the reason why. Fortunately, "
"I have the power to \"heal\" your wounds. Once, I tried to heal a poor "
"warrior but alas failed. Yet, this was not in vain for it soothed the pain. "
"Why am I telling you this? Simply to make you understand that failures are "
"not always what they seem. Sometimes, they must be to teach you who you "
"really are.")

Command(INTL( 4370, "WORTHY"))
INTL( 4371, "Making stony pathways smoother by a gentle word or deed is all what "
"you need to follow the path of worthiness.")

Command(INTL( 569, "HEAL"))
""
IF (USER_MAXHP == USER_HP)
	Conversation
	INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
	IF (USER_LEVEL < 5)
		Conversation
		INTL( 4372, "Since you are not strong enough to acquire gold pieces on your own, "
		"I shall heal your wounds. You are now healed, my friend.")
		HealPlayer(USER_MAXHP)
		CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
	ELSE
		Conversation
      FORMAT(INTL( 1146, "Do you wish to be completely healed for %u gold pieces?"), ((USER_MAXHP-USER_HP) / 2))
      SetYesNo(HEALING)
	ENDIF
ENDIF

Command(INTL( 4373, "CHALICE"))
""
IF (CheckItem(__OBJ_GOLDEN_CHALICE) >= 1)
	Conversation
	INTL( 4374, "You have found one of our precious golden chalices? Do you wish to give it back to us?")
	SetYesNo(CHALICE)
ELSE
	Conversation
	INTL( 4375, "The Church of \"Artherk\" has been the scene of a large amount of thievery. We are always "
	"search for our stolen invaluable golden chalices. If you ever find one, I implore you to "
	"bring it back within these sacred walls.")
ENDIF

YES(CHALICE)
IF (CheckItem(__OBJ_GOLDEN_CHALICE) >= 1)
	TakeItem(__OBJ_GOLDEN_CHALICE) 
	Conversation
	FORMAT(INTL( 4376, "I thank you very much, %s. It is rather difficult for us to reward you as the "
	"Church of Artherk is not wealthy enough. I hope you will find this Ring of Faith "
	"useful."), USER_NAME) 
	;int nExpReward = 5000; 	
	GiveXP(nExpReward)
	GiveItem(__OBJ_RING_OF_FAITH) 
	Conversation
	FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), nExpReward)
ELSE
	IF( USER_GENDER == GENDER_MALE )		
		Conversation
		INTL( 4377, "Are ye attempting to steal the Church, my son?")
	ELSE
		Conversation
		INTL( 4378, "Are ye attempting to steal the Church, my daughter?")
	ENDIF
ENDIF

NO(CHALICE)
IF( USER_GENDER == GENDER_MALE )		
	Conversation
	INTL( 4379, "I understand, my son.")
ELSE
	Conversation
	INTL( 4380, "I understand, my daughter.")
ENDIF

YesNoELSE(CHALICE)
Conversation
INTL( 3963, "Pardon me but was that a yes or a no?")
SetYesNo(CHALICE) 

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 698, " ASS "),INTL( 697, "ASSHOLE"))
INTL( 4381, "Do not speak hastily for your anger darkens what you say.")
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 4382, "You are always welcome in our humble temple.")
BREAK

YES(HEALING)
	IF (USER_MAXHP == USER_HP)
		Conversation
		INTL( 1147, "You do not need healing, you have no wounds.")
	ELSE
		IF (Gold < ((USER_MAXHP-USER_HP)/2))
			IF (Gold > 0) 
				Conversation
				INTL( 4383, "You did not have enough gold pieces but I have healed a few of your wounds "
				"nonetheless for what you could spare.")
				CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
				HealPlayer(Gold*2)				
				PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7548, "You give %u gold to Thorkas."), Gold)) 
				PRIVATE_SYSTEM_MESSAGE(INTL( 7512, "Some of your wounds have been healed!")) 
            TakeGold(Gold)
			ELSE
				Conversation
				INTL( 4384, "You do not have enough gold pieces to be healed. You will have to find "
				"have to find the gold first.")
			ENDIF
		ELSE
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7548, "You give %u gold to Thorkas."), (USER_MAXHP-USER_HP)/2)) 
			PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
			TakeGold( ( (USER_MAXHP-USER_HP) / 2) )
			HealPlayer(USER_MAXHP)
			CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)						
			Conversation
			INTL( 4385, "Thank you for this generous donation. Your wounds are now healed.  "
			"Please feel free to come back if you need more healing.")
		ENDIF
	ENDIF

NO(HEALING)
	Conversation
	INTL( 1239, "As you wish. Ask me again if you change your mind.")

YesNoELSE(HEALING)
	Conversation
	INTL( 2211, "So be it, my friend.")

Command3(INTL( 1609, "DEATH"),INTL( 1610, "DIE"),INTL( 1611, "KILLED"))
INTL( 4386, "It is always unfortunate to face death, but those who wear a "
"Gem of Destiny can set a \"Sanctuary\" where they will reappear "
"when they get killed.")

Command(INTL( 1613, "SANCTUARY"))
INTL( 4387, "The Sanctuary is where your body and soul are restored by the "
"Gem of Destiny if you have been killed. Do you wish to set "
"the Temple of Raven's Dust as your sanctuary?")
SetYesNo(SANCTUARY)

YES(SANCTUARY)
IF (Gold < 15000 )
   Conversation
   INTL( 4388, "I would be glad to comply, but my order would require a donation "
   "of 15000 gold pieces, which you do not appear to have. Perhaps you "
   "should come again later, when you are more fortunate.")
ELSE
   Conversation
   INTL( 4389, "Very well. My order requires a donation of 15000 gold pieces, however. "
   "Do you accept to pay that amount?")
   SetYesNo(DONATION)
ENDIF

NO(SANCTUARY)
Conversation
INTL( 1617, "Ah. Very well, then.")

YesNoELSE(SANCTUARY)
Conversation
INTL( 1617, "Ah. Very well, then.")

YES(DONATION)
IF (Gold < 15000)  // Had to put another check to prevent a user from 
   Conversation   // dropping gold after the 1st check. 
   INTL( 4390, "I would be glad to comply, but my order would require a donation "
   "of 15000 gold pieces, which you do not appear to have. Perhaps you "
   "should come again later, when you are more fortunate.")
ELSE
   Conversation
   INTL( 4391, "It is done, then. Your body and soul shall return here if you "
   "unfortunately happen to die.")
   TakeGold(15000)
   SetDeathLocation( 1558,2405,0 )  // Temple of Raven's Dust
	CastSpellTarget(__SPELL_NPC_CANTRIP_BLUE_WIPE)
	PRIVATE_SYSTEM_MESSAGE(INTL( 7549, "You give 15000 gold to Brother Thorkas.")) 
	PRIVATE_SYSTEM_MESSAGE(INTL( 7519, "Your spirit is now anchored here.")) 
ENDIF

NO(DONATION)
Conversation
INTL( 4392, "I understand. You need to think about this further. Come back "
"when you are ready.")

YesNoELSE(DONATION)
Conversation
INTL( 1621, "I... um... Was that a yes or a no?")
SetYesNo(DONATION)

Command3(INTL( 700, "SPELL"),INTL( 495, "LEARN"),INTL( 496, "TEACH"))
INTL( 7550, "Very well, I will share my knowledge with you.")
CreateSkillList
	AddTeachSkill (__SPELL_TURN_UNDEAD, 17, 15713)
	AddTeachSkill (__SPELL_TRANQUILITY, 26, 55252)
SendTeachSkillList

Default
""
IF (rnd.roll( dice( 1, 2 ) ) == 1)
    Conversation
    INTL( 4012, "Perhaps others would like to know about that.")
ELSE
    Conversation
    INTL( 4415, "I have no idea about what you are talking about.")
ENDIF

EndTalk
}
//////////////////////////////////////////////////////////////////////////////////////////
void BrotherThorkas::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_TURN_UNDEAD, 17, 15713)
         TEACH_SKILL(__SPELL_TRANQUILITY, 26, 55252)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE