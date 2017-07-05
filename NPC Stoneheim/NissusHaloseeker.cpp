#pragma hdrstop
#include "NissusHaloseeker.h"
 
NissusHaloseeker::NissusHaloseeker()
{}

NissusHaloseeker::~NissusHaloseeker()
{}

extern NPCstructure::NPC NissusHaloseekerNPC;

void NissusHaloseeker::Create( void )
{
    npc = NissusHaloseekerNPC;
    SET_NPC_NAME( "[10900]Nissus Haloseeker" );
    npc.InitialPos.X = 210;
    npc.InitialPos.Y = 675;
    npc.InitialPos.world = 0; 
  	npc.boPrivateTalk = TRUE;
}

void NissusHaloseeker::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT HEALING = 1;
CONSTANT GUIDANCE = 2;
CONSTANT DONATION = 3;
CONSTANT SANCTUARY = 4;
CONSTANT RINGOFPUREFAITH = 8;
CONSTANT FANG = 9; 
CONSTANT SOUL = 10; 
CONSTANT Mithanna = 11; 
CONSTANT BELTIGAN = 13; 

InitTalk

Begin
""
IF (CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1) 
	Conversation
	INTL( 9698, "I sense the god of night's dreadful influence within you. You belong to Ogrimar now, and "
	"one day, he will feed upon your very soul. Alas, there is nothing I, or anyone else for "
	"that matter, will be able to save you when this will happen.")	
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)	
	Conversation
	INTL( 9699, "Your kind is tolerated here but let me warn you that you're in a downward spiral. "
	"You will encounter numerous hardships if you wish to pursue this path.")
ELSE
	Conversation
	INTL( 9700, "You seek \"guidance\" of the spirit? Then, you have come to the right place.")
ENDIF

Command(INTL( 5628, "ORACLE"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) >= 1)
	Conversation
	INTL( 9701, "He speaks to good and evil folks, but before you speak to him, you will need "
	"to find him, and that means you must undertake a very difficult quest... to become "
	"a Lightbringer.")
ELSE
	Conversation
	INTL( 1864, "...")
ENDIF

Command(INTL( 979, "GUIDANCE")) 
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1) 
	Conversation
	INTL( 9702, "You have reached a point in your life where no guidance of my part could actually help you. "
	"Nevertheless, our church offers several \"services\" that might help you, all of which are "
	"available for a small donation.")	
ELSEIF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 
	Conversation
	INTL( 9703, "I would gladly help you if I could but I think that the paladin, \"Beltigan\", is in a better "
	"position for that.") 
ELSE // Assuming that __QUEST_FIXED_ALIGNMENT is worth 1. 
	Conversation 
	FORMAT(INTL( 9704, "You've been once called a Champion of Light, %s. But, now is the time for you to mature and "
	"become a true follower of the deity that we follow. Thus, should you accept this great honor, "
	"you must speak with the paladin, Sir \"Beltigan\"."), USER_NAME) 
ENDIF

Command(INTL( 9705, "BELTIGAN")) 
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1) 
	Conversation
	INTL( 9706, "I strongly doubt that you wish to cross Sir Beltigan. He is a paladin and surely does "
	"not appreciate your ilk.")
ELSE
	Conversation
	INTL( 9707, "The paladin resides in his castle, a little to the south of Stonecrest. He is a good "
	"friend of mine and a man of honor with whom you should definitely talk.")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 9708, "I am Nissus Haloseeker.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 9709, "I am a \"cleric\" of Artherk.")

Command(INTL( 9710, "SOUL OF ARTHERK"))
""
IF(CheckItem(__OBJ_KEY_OF_ARTHERK) == 1)
	Conversation
	INTL( 8671, "You already have the Key of Artherk. All that is left is to find the Chamber of Providence and enter the portal.")
ELSEIF (CheckFlag(__QUEST_FLAG_ARTHERK_SOUL) == 1) 	
	Conversation
	INTL( 9593, "You already have this piece of the key. It would do you no good to have an additional one.")	
ELSE 
	IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1) 
		Conversation
		INTL( 9711, "The Soul of Artherk would not bear your malevolence.")
	ELSEIF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 0) 
		Conversation
		INTL( 9712, "You must be a Lightbringer before I can help you obtain the Soul of Artherk.")
	ELSE								 
		Conversation
		INTL( 9713, "The Soul of Artherk represents the compassion and wisdom required to "
		"lift the spirits of others and give them hope. It is possible to obtain it "
		"by merging three \"rings\" \"of\" \"pure\" \"faith\", two \"staves\" \"of\" \"hope\" and two \"pearls\" \"of\" \"wisdom\".")
		IF ((CheckItem(__OBJ_RING_OF_PURE_FAITH) >= 3) && (CheckItem(__OBJ_STAFF_OF_HOPE) >= 2)  && (CheckItem(__OBJ_PEARL_OF_WISDOM) >= 2))
			Conversation
			INTL( 9714, "Ah, I see that you have gathered all the required components. Very well, then. "
			"Shall I merge the rings, the staves and the pearls together to obtain the Soul of Artherk?")
			SetYesNo(SOUL) 
		ENDIF 
	ENDIF 
ENDIF 

YES(SOUL) 
	IF ((CheckItem(__OBJ_RING_OF_PURE_FAITH) >= 3) && (CheckItem(__OBJ_STAFF_OF_HOPE) >= 2)  && (CheckItem(__OBJ_PEARL_OF_WISDOM) >= 2))
		Conversation
		FORMAT(INTL( 9715, "Then, let's get started... It is done! The Soul of Artherk blesses us all by its presence. "
		"%s, the Soul of Artherk is in your hands."), USER_NAME) 
		CastSpellSelf(__SPELL_NPC_CANTRIP_BLUE_WIPE)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9716, "Nissus gathers the items in a circle and whispers a prayer."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 9717, "A bluish flame instantly consumes them and the Soul of Artherk appears!"))		
		PRIVATE_SYSTEM_MESSAGE(INTL( 9718, "Nissus gives you the Soul of Artherk.")) 
		;int nExpReward = 250000; 	
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"),nExpReward) )
		GiveXP(nExpReward) 
		FOR(0,3) 
			TakeItem(__OBJ_RING_OF_PURE_FAITH)
		ENDFOR
		FOR(0,2) 
			TakeItem(__OBJ_STAFF_OF_HOPE) 
		ENDFOR
		FOR(0,2) 
			TakeItem(__OBJ_PEARL_OF_WISDOM) 
		ENDFOR		
		GiveItem(__OBJ_SOUL_OF_ARTHERK) 
		GiveFlag(__QUEST_FLAG_ARTHERK_SOUL, 1) 
	ELSE
		Conversation
		INTL( 9719, "Ah, it seems that you did not have all the required components afterall. Please gather "
		"what is needed and return to me.")
	ENDIF 

NO(SOUL)
	Conversation
	INTL( 7724, "Come back if you change your mind.")

YesNoELSE(SOUL) 
	Conversation
	INTL( 9720, "Shall I merge the rings, the staves and the pearls together to obtain the Soul of Artherk?")
	SetYesNo(SOUL) 
 
CmdAND(INTL( 8891, "STAFF"),INTL( 10272, "HOPE"))
INTL( 10785, "You should walk to the land of the centaurs and ask the cleric, \"Dionysus\" \"Silverstream\" for "
"his assistance. He is the only priest who possesses both enough skill and faith to create "
"a staff of hope. He's also one of the few centaurs who won't hold you in disdain.") 

CmdAND(INTL( 10786, "STAV"),INTL( 10272, "HOPE")) 
INTL( 10787, "You should walk to the land of the centaurs and ask the cleric, \"Dionysus\" \"Silverstream\" for "
"his assistance. He is the only priest who possesses both enough skill and faith to create "
"a staff of hope. He's also one of the few centaurs who won't hold you in disdain.") 

Command2(INTL( 8013, "DIONYSUS"),INTL( 8014, "SILVERSTREAM"))
INTL( 10788, "Dionysus Silverstream is the only cleric in the town of the centaurs. Once you're there, head "
"for the temple and you'll find him.") 

CmdAND3(INTL( 8039, "RING"),INTL( 10261, "PURE"),INTL( 10262, "FAITH"))
INTL( 10789, "You'll find that a ring of pure faith can come in handy. If you need some, you must seek out "
"\"Theoran\" \"Ironfaith\", a war cleric who lives alone in a small house outside of Stonecrest.") 

Command2(INTL( 10258, "THEORAN"),INTL( 10790, "IRONFAITH"))
INTL( 10791, "Theoran lives in a small house outside of Stonecrest. I must warn you however that if you "
"or a friend of yours go there with bad intentions, Theoran might not react well at all.")

CmdAND(INTL( 7705, "PEARL"),INTL( 7712, "WISDOM")) 
INTL( 10792, "Alas, I am not entirely certain where these can be found. However, I think \"Annithae\" \"Teardrop\" "
"has a nice collection of pearls. I think that you should ask her if she has some that she "
"could give to you.") 

Command2(INTL( 8323, "ANNITHAE"),INTL( 8326, "TEARDROP")) 
INTL( 10793, "Annithae lives right here in Stonecrest. I'm sure you won't have any troubles finding her.") 

CmdAND3(INTL( 9721, "RUBY"),INTL( 1367, "DRAGON"),INTL( 8927, "FANG")) 
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1) 
	Conversation
	INTL( 8083, "That does not concern you.")
ELSE	
	Conversation
	INTL( 9722, "I'm afraid that you are out of luck. The only ancient ruby dragon that I am aware of "
	"died a long time ago in a duel to the death against Darkfang for the leadership of the "
	"dragons of Firesky. If I recall correctly, the dragon's human name was Scarlet because of "
	"its fiery red scales.")
ENDIF
 
Command(INTL( 9732, "FLASK OF HOLY WATER"))
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1) 
	Conversation
	INTL( 8083, "That does not concern you.")
ELSE
	Conversation	
	INTL( 9733, "Brother Thorkas, of Silversky, will surely help you if you request his assistance.") 	
ENDIF

CmdAND(INTL( 9734, "CANDLE"),INTL( 9735, "ETERNITY"))
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1) 
	Conversation
	INTL( 8083, "That does not concern you.")
ELSE
	Conversation
	INTL( 9736, "I heard that King Theodore's advisor is skilled enough to do these. Perhaps you should request "
	"his assistance if you cannot find the candles on your own.") 
ENDIF  

CmdAND3(INTL( 8927, "FANG"),INTL( 9630, "TRUE"),INTL( 6869, "RESOLVE"))
""
IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) >= 6)
	Conversation // User no longer needs a Fang of True Resolve. 
	INTL( 9737, "You no longer need fangs of true resolve.")
ELSEIF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) <= 3)
	Conversation // User has not reached the point where he needs a Fang of True Resolve. 	
	INTL( 9738, "I cannot help you with this for the moment.")
ELSEIF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 4) 
	Conversation 
	INTL( 9739, "You need a fang of true resolve? Then, who is the person that sent you to me?")	
	;YesNo = Mithanna;		
ELSEIF ((CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 5) && (CheckFlag(__QUEST_TIMER_FANGS_OF_TRUE_RESOLVE) == 0))
	Conversation	
	INTL( 9744, "In order to create a fang of true resolve, I will require one \"ruby\" \"dragon\" \"fang\" and two \"candles\" \"of\" \"eternity\".")
	IF ((CheckItem(__OBJ_RUBY_DRAGON_FANG) >= 1) && (CheckItem(__OBJ_CANDLE_OF_ETERNITY) >= 2))
		Conversation	
		INTL( 9745, " I see that you have already gathered all the components that the creation of a fang of true resolve demand. Do "
		"you want me to proceed with the ritual?")		
		SetYesNo(FANG)
	ELSE
		Conversation
		INTL( 9742, " Come back once you've gathered all the components needed.")
	ENDIF
ELSEIF(CurrentRound < CheckFlag(__QUEST_TIMER_FANGS_OF_TRUE_RESOLVE) ) 
	IF(CurrentRound > 6000) 
			Conversation
			INTL( 9746, "Okay, I have completed the ritual. Here's your fang of true resolve.")		
			GiveItem(__OBJ_FANG_OF_TRUE_RESOLVE)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9749, "Nissus gives you a fang of true resolve."))							
			RemFlag(__QUEST_TIMER_FANGS_OF_TRUE_RESOLVE)
			RemFlag(__QUEST_NISSUS_FANGS_OF_TRUE_RESOLVE)
			IF (CheckItem(__OBJ_FANG_OF_TRUE_RESOLVE) >= 4) 
				GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 6) 
			ENDIF
	ELSE
		Conversation
		INTL( 11343, "The fang of true resolve is not ready yet. Please come back later.")
	ENDIF
ELSEIF( CurrentRound >= CheckFlag(__QUEST_TIMER_FANGS_OF_TRUE_RESOLVE) + 6000) 	
	Conversation
	INTL( 9746, "Okay, I have completed the ritual. Here's your fang of true resolve.")		
	GiveItem(__OBJ_FANG_OF_TRUE_RESOLVE)
	PRIVATE_SYSTEM_MESSAGE(INTL( 9749, "Nissus gives you a fang of true resolve."))							
	RemFlag(__QUEST_TIMER_FANGS_OF_TRUE_RESOLVE)
	RemFlag(__QUEST_NISSUS_FANGS_OF_TRUE_RESOLVE)
	IF (CheckItem(__OBJ_FANG_OF_TRUE_RESOLVE) >= 4) 
		GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 6) 
	ENDIF
ELSE	
	Conversation
	INTL( 11343, "The fang of true resolve is not ready yet. Please come back later.")
ENDIF 
;} else if( ( msg.Find( INTL( 9582, "MITHANNA") ) != -1 ) && YesNo == Mithanna) { ;YesNo = 0;
	IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 4)
		GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 5) 
	ENDIF	
	Conversation
	INTL( 9740, "Ah, so Mithanna sent you. Very well, then. In order to create a fang of true resolve, I will require "
	"one \"ruby\" \"dragon\" \"fang\" and two \"candles\" \"of\" \"eternity\".") 	
	IF ((CheckItem(__OBJ_RUBY_DRAGON_FANG) >= 1) && (CheckItem(__OBJ_CANDLE_OF_ETERNITY) >= 2))
		Conversation	
		INTL( 9741, " I see that you have already gathered all the components that the creation of a fang of true resolve demand. Do "
		"you want me to proceed with the ritual?")		
		SetYesNo(FANG) 
	ELSE
		Conversation
		INTL( 9742, " Come back once you've gathered all the components needed.")
	ENDIF
	;} else if(YesNo == Mithanna) { ;YesNo = 0;
	Conversation
	INTL( 9743, "I am sorry, I cannot help you.")

YES(FANG)  
IF ((CheckItem(__OBJ_RUBY_DRAGON_FANG) >= 1) && (CheckItem(__OBJ_CANDLE_OF_ETERNITY) >= 2))
	Conversation
	INTL( 9753, "It will necessitate at least 5 minutes for me to complete the ritual required in the creation of fangs "
	"of true resolve. Also, I must ask that you maintain your good status and not let yourself be tempted by "
	"the ways of evil. Your karma is of such intensity that it would be a shame to see it tainted by darkness.")			
	GiveFlag(__QUEST_TIMER_FANGS_OF_TRUE_RESOLVE, CurrentRound)	
	TakeItem(__OBJ_RUBY_DRAGON_FANG)
	TakeItem(__OBJ_CANDLE_OF_ETERNITY)
	TakeItem(__OBJ_CANDLE_OF_ETERNITY)	
ELSE
	Conversation
	INTL( 9755, "You're missing some components, I'm afraid. In order to create one fang of true resolve, I'll need "
	"two \"candles\" \"of\" \"eternity\" and one \"ruby\" \"dragon\" \"fang\".")	
ENDIF

NO(FANG)
Conversation
INTL( 8220, "Come back if you ever change your mind.")

YesNoELSE(FANG) 
Conversation
INTL( 9756, "Well, do you want a fang of true resolve?")
SetYesNo(FANG) 

Command(INTL( 9757, "CLERIC"))
INTL( 9758, "Our church offers several \"services\", all of which are available for a small donation.")

Command(INTL( 9759, "SERVICES"))
INTL( 9760, "I can \"heal\" your wounds, set your \"sanctuary\" in our temple or \"teach\" you a few "
"useful spells")

Command2(INTL( 496, "TEACH"), INTL( 495, "LEARN"))
INTL( 9761, "These are the wonderful spells I can teach you.")
CreateSkillList
	AddTeachSkill (__SPELL_BLESS, 37, 126673)
	AddTeachSkill (__SPELL_MASS_HEALING, 39, 143577)
	AddTeachSkill (__SPELL_HEALING_MIST, 45, 200625)
SendTeachSkillList

Command(INTL( 9762, "BLESS"))
INTL( 9763, "The bless spell temporarily bestows upon the target the blessing of the gods, augmenting its capacity to fight and "
"cast spells in general.")

Command(INTL( 9764, "MASS HEALING"))
INTL( 9765, "The mass healing spell will cure the wounds of all the characters in the caster's group within the target area. "
"You must have the healing spell in order to learn it.")

Command(INTL( 9766, "HEALING MIST"))
INTL( 9767, "The healing mist spell will cure the wounds of all the characters in the caster's group within the target area. "
"You must have the mass healing spell in order to learn it.")

Command(INTL( 569, "HEAL"))
""
IF (USER_MAXHP == USER_HP)
	Conversation
	INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
	IF (USER_LEVEL < 5)
		Conversation
		INTL( 9768, "Since you are not strong enough to acquire gold pieces on your own, "
		"I shall heal your wounds. You are now healed, my friend.")
		CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
		HealPlayer(USER_MAXHP)
	ELSE
		Conversation
      FORMAT(INTL( 1146, "Do you wish to be completely healed for %u gold pieces?"), ((USER_MAXHP-USER_HP)))
      SetYesNo(HEALING)
	ENDIF
ENDIF

YES(HEALING)
IF (USER_MAXHP == USER_HP)
	Conversation
	INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
	IF (Gold < ((USER_MAXHP-USER_HP)))
		IF (Gold > 0) 
			Conversation
			INTL( 9769, "You did not have enough gold pieces but I have healed a few of your wounds "
			"nonetheless for what you could spare.") 
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 9770, "You give %u gold to Nissus."), Gold) ) 
			PRIVATE_SYSTEM_MESSAGE(INTL( 8225, "Your wounds have been partially healed!"))
			CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
			HealPlayer(Gold) 
			TakeGold(Gold)
		ELSE
			Conversation
			INTL( 9771, "You do not have enough gold pieces to be healed. You will have to find "
			"the gold first.")
		ENDIF
	ELSE		
		Conversation
		INTL( 9772, "Thank you for this generous donation. Your wounds are now healed.  "
		"Please feel free to come back if you need more healing.")
		TakeGold( ( (USER_MAXHP-USER_HP)) )
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 9770, "You give %u gold to Nissus."), (USER_MAXHP-USER_HP)) ) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
		CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
		HealPlayer(USER_MAXHP)      
	ENDIF
ENDIF

NO(HEALING)
Conversation
INTL( 1239, "As you wish. Ask me again if you change your mind.")

YesNoELSE(HEALING)
Conversation
INTL( 2211, "So be it, my friend.")

Command3(INTL( 1609, "DEATH"),INTL( 1610, "DIE"),INTL( 1611, "KILLED"))
INTL( 9773, "It is always unfortunate to face death, but those who wear a "
"Gem of Destiny can set a \"Sanctuary\" where they will reappear "
"when they get killed.")

Command(INTL( 1613, "SANCTUARY"))
INTL( 9774, "The Sanctuary is where your body and soul are restored by the "
"Gem of Destiny if you have been killed. Do you wish to set "
"the Temple of Stonecrest as your sanctuary?")
SetYesNo(SANCTUARY)

YES(SANCTUARY)
IF (Gold < 25000 )
   Conversation
   INTL( 9775, "I would be glad to comply, but my order would require a donation "
   "of 25000 gold pieces, which you do not appear to have. Perhaps you "
   "should come again later, when you are more fortunate.")
ELSE
   Conversation
   INTL( 9776, "Very well. My order requires a donation of 25000 gold pieces, however. "
   "Do you accept to pay that amount?")
   SetYesNo(DONATION)
ENDIF

NO(SANCTUARY)
Conversation
INTL( 1617, "Ah. Very well, then.")

YesNoELSE(SANCTUARY)
Conversation
INTL( 9777, "Do you wish to set the Temple of Stonecrest as your sanctuary?")
SetYesNo(SANCTUARY) 

YES(DONATION) 
IF (Gold < 25000)    
   Conversation	
   INTL( 9778, "I would be glad to comply, but my order would require a donation "
   "of 25000 gold pieces, which you do not appear to have. Perhaps you "
   "should come again later, when you are more fortunate.")
ELSE
   Conversation
   INTL( 9779, "It is done, then. Your body and soul shall return here if you "
   "unfortunately happen to die.")
	CastSpellTarget(__SPELL_NPC_CANTRIP_BLUE_WIPE)
   PRIVATE_SYSTEM_MESSAGE(INTL( 9780, "You give 25000 gold to Nissus.")) 
	PRIVATE_SYSTEM_MESSAGE(INTL( 7519, "Your spirit is now anchored here.")) 
	TakeGold(25000)
   SetDeathLocation( 205, 671, 0 )  
ENDIF								  

NO(DONATION)
Conversation
INTL( 9781, "I understand. Come back when you are ready.")

YesNoELSE(DONATION)
Conversation
INTL( 1621, "I... um... Was that a yes or a no?")
SetYesNo(DONATION)
 
Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 9782, "I am truly sorry to hear that.")
BREAK

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 9783, "May Artherk light thy path.")
BREAK

Command(INTL( 3771, "?"))
INTL( 9784, "Alas, I do not have all the answers.") 

Default
INTL( 9785, "If that will be all, I must return to my prayers")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void NissusHaloseeker::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_BLESS, 37, 126673)
         TEACH_SKILL(__SPELL_MASS_HEALING, 39, 143577)
         TEACH_SKILL(__SPELL_HEALING_MIST, 45, 200625)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE