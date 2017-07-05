//////////////////////////////////////////////////////////////////////
// Amandra.cpp: implementation of the Amandra class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Amandra.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Amandra::Amandra()
{}

Amandra::~Amandra()
{} 

extern NPCstructure::NPC AmandraNPC;

void Amandra::Create( ){
    npc = ( AmandraNPC );
    SET_NPC_NAME( "[2914]Amandra" );
    npc.InitialPos.X = 1584; 
    npc.InitialPos.Y = 2518; 
    npc.InitialPos.world = 0;
}

void Amandra::OnTalk( UNIT_FUNC_PROTOTYPE )

{

// GiveKarma (50*(500-USER_KARMA)/500)
// GiveKarma (-50*(500-USER_KARMA)/500)
CONSTANT DUEL = 1;
CONSTANT SWORD = 2;	
CONSTANT STORY = 3;	
CONSTANT STORY2 = 4;

InitTalk

Begin
""
IF (USER_KARMA >= 300)
	Conversation
	FORMAT(INTL( 4014, "Ahhh, if it isn't %s! I've heard so much about your great deeds!"), USER_NAME)
ELSEIF (USER_KARMA <= -300)
	Conversation
	INTL( 4015, "Yes? What do you want?")
ELSE
	Conversation
	INTL( 4016, "Greetings, fellow adventurer.")
ENDIF

Command(INTL( 4017, "BROTHER'S NAME"))
""
IF(CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 2)
	Conversation
	INTL( 4018, "He goes by the name of \"Haden\".")
ELSE
	Conversation
	INTL( 4019, "I don't have time for this.")
ENDIF

Command(INTL( 4020, "HADEN"))
""
IF(CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 2)
	Conversation
	INTL( 4021, "Although he is my brother, I can't help but despise him for what he has done. It seems despite all the things "
	"I have done to keep him on the right path, he has strayed away from it.")
ELSE
	Conversation
	INTL( 4019, "I don't have time for this.")
ENDIF
	
Command(INTL( 3694, " NAME"))
INTL( 4022, "You may call me Amandra.")

Command(INTL( 4023, "AMANDRA"))
INTL( 4024, "That is my name.")

Command(INTL( 489, "WORK"))
INTL( 4025, "I am constantly travelling in search of \"adventure\" to better hone my fighting skills.")

Command(INTL( 4026, "ADVENTURE"))
INTL( 4027, "The thrill of the hunt, the intensity of the chase and the joy of overcoming an adversary "
"stronger than you, these are the things for which I live.")

Command(INTL( 4028, "BROTHER"))
""
IF (CheckFlag(__QUEST_VISITOR_SPOTTED) < 5)
	Conversation
	INTL( 4029, "How do you know I have a brother? If this is some kind of foolish attempt at gaining my favor, I "
	"must warn you that it will not only fail, but it will also anger me!") 
ELSEIF (CheckFlag(__QUEST_VISITOR_SPOTTED) == 5)
	Conversation
	INTL( 4030, "You've seen my brother? He sold a sword to Kiadus you say? I fear the worst has already happened. "
	"Listen to me carefully. It is imperative that you go back to Kiadus' shop and buy that sword, no "
	"matter what the cost! The lives of many depend upon it.")
	GiveFlag(__QUEST_VISITOR_SPOTTED, 6)
	GiveFlag(__FLAG_ASKED_ABOUT_SWORD, 2)	
ELSEIF (CheckFlag(__QUEST_VISITOR_SPOTTED) == 6)
	IF (CheckItem(__OBJ_FAKE_BLADE_OF_RUIN) == 1)
		TakeItem(__OBJ_FAKE_BLADE_OF_RUIN)
		Conversation
		INTL( 4031, "Have you brought the sword? Very good, I will keep it safe for now... what is this? "
		"Are you certain this is the sword you bought from Kiadus?")	
		GiveFlag(__FLAG_ASKED_ABOUT_SWORD, 7)
		GiveFlag(__QUEST_VISITOR_SPOTTED, 7)
		SetYesNo(SWORD)
	ELSEIF (CheckItem(__OBJ_FAKE_BLADE_OF_RUIN) > 1) 
		;int nNumFakeBlades = CheckItem(__OBJ_FAKE_BLADE_OF_RUIN);
		FOR( 0, nNumFakeBlades )
			TakeItem(__OBJ_FAKE_BLADE_OF_RUIN)
		ENDFOR
		Conversation
		INTL( 4032, "What manner of treachery is this? How can you have so many blades of ruin? These are no doubt "
		"fakes spawned by my brother to fool anyone after him. No matter, I will take these off your hands "
		"anyway. You must now seek out my brother and retrieve the true blade of ruin!")
		GiveFlag(__FLAG_ASKED_ABOUT_SWORD, 7)
		GiveFlag(__QUEST_VISITOR_SPOTTED, 7)
	ELSE
		Conversation
		INTL( 4033, "Have you brought the sword? Well, what are you waiting for? Stop wasting time and go buy that "
		"sword!")
	ENDIF
ELSEIF (CheckFlag(__QUEST_VISITOR_SPOTTED) == 7)
	Conversation
	INTL( 4034, "What are you doing wasting time here? Get out there and find my brother so you can retrieve the blade "
	"of ruin from him!")
ELSE
	Conversation
	INTL( 4035, "I don't have time for this now.")
ENDIF	

Command(INTL( 3918, "VISITOR"))
""
IF (CheckFlag(__QUEST_VISITOR_SPOTTED) < 5)
	Conversation
	INTL( 4036, "A strange visitor? I have not really been paying attention to that.")
ELSEIF (CheckFlag(__QUEST_VISITOR_SPOTTED) == 5)
	Conversation
	INTL( 4037, "You've seen my brother? He sold a sword to Kiadus you say? I fear the worst has already happened. "
	"Listen to me carefully. It is imperative that you go back to Kiadus' shop and buy that sword, no "
	"matter what the cost! The lives of many depend upon it.")
	GiveFlag(__QUEST_VISITOR_SPOTTED, 6)
	GiveFlag(__FLAG_ASKED_ABOUT_SWORD, 2)	
ELSEIF (CheckFlag(__QUEST_VISITOR_SPOTTED) == 6)
	IF (CheckItem(__OBJ_FAKE_BLADE_OF_RUIN) == 1)
		TakeItem(__OBJ_FAKE_BLADE_OF_RUIN)
		Conversation
		INTL( 4038, "Have you brought the sword? Very good, I will keep it safe for now... what is this? "
		"Are you certain this is the sword you bought from Kiadus?")
		GiveFlag(__FLAG_ASKED_ABOUT_SWORD, 7)
		GiveFlag(__QUEST_VISITOR_SPOTTED, 7)
		SetYesNo(SWORD)
	ELSEIF (CheckItem(__OBJ_FAKE_BLADE_OF_RUIN) > 1)
		;int nNumFakeBlades = CheckItem(__OBJ_FAKE_BLADE_OF_RUIN);
		FOR( 0, nNumFakeBlades )		
			TakeItem(__OBJ_FAKE_BLADE_OF_RUIN)
		ENDFOR
		Conversation
		INTL( 4039, "What manner of treachery is this? How can you have so many blades of ruin? These are no doubt "
		"fakes spawned by my brother to fool anyone after him. No matter, I will take these off your hands "
		"anyway. You must now seek out my brother and retrieve the true blade of ruin!")
		GiveFlag(__FLAG_ASKED_ABOUT_SWORD, 7)
		GiveFlag(__QUEST_VISITOR_SPOTTED, 7)
	ELSE
		Conversation
		INTL( 4040, "Have you brought the sword? Well, what are you waiting for? Stop wasting time and go buy that "
		"sword!")
	ENDIF
ELSEIF (CheckFlag(__QUEST_VISITOR_SPOTTED) == 7)
	Conversation
	INTL( 4041, "What are you doing wasting time here? Get out there and find my brother so you can retrieve the blade "
	"of ruin from him!")
ELSE
	Conversation
	INTL( 4035, "I don't have time for this now.")
ENDIF	

YES(SWORD)
	Conversation
	INTL( 4042, "This is nothing but a fake! I'm afraid that your task is not over yet. You must now seek out my "
	"brother and retrieve the true blade of ruin!")
	GiveFlag(__FLAG_ASKED_ABOUT_SWORD, 7)
	GiveFlag(__QUEST_VISITOR_SPOTTED, 7)
NO(SWORD)
	Conversation
	INTL( 4043, "It's not nice to lie you know, but no matter. In any case, this sword is a fake, no doubt spawned by "
	"my brother to fool anyone after him. You must not let him escape with the real sword, the true blade "
	"of ruin!")
	GiveFlag(__FLAG_ASKED_ABOUT_SWORD, 7)
	GiveFlag(__QUEST_VISITOR_SPOTTED, 7)
YesNoELSE(SWORD)
	Conversation
	INTL( 4044, "I'll ask you again, are you certain this is the sword you bought from Kiadus?")
	SetYesNo(SWORD)
/*	
Command("BLADE OF RUIN")
""
IF(CheckFlag(__QUEST_VISITOR_SPOTTED) >= 6)
	Conversation
	"There is a bit of a story behind the fabled sword called the Blade of Ruin. Would you like to hear about it?"
	SetYesNo(STORY)
ELSE	
	Conversation
	"How could you know anything about such a powerful sword as that? Be careful, knowledge like that will get you "
	"killed someday!"
ENDIF
	
YES(STORY)	
	Conversation
	"The famed blade of ruin was used in times old by a travelling adventurer of some renown named Alexis. The young man "
	"had happened to wander upon Cyrania, Goddess of the Spring, as she was bathing in a small pond. Upon seeing her, the "
	"youth instantly fell to his knees, his heart filled with admiration. To this day, it is still pondered upon whether the "
	"goddess intentionally lured the young man to her, or if it was nothing more than a simple coincidence. The goddess appeared "
	"to be taken aback at this intrusion into her haven. She explained to Alexis that he would be greatly rewarded, could he keep "
	"this location secret. Accepting his vow of secrecy, the goddess then placed a sword on the surface of the water. But The sword "
	"did not sink! Instead it started flowing gently towards Alexis. So amazed was he by this uncanny sight that he never noticed "
	"his hostess had disappeared. As the sword slowly approached him, his mind suddenly filled with the voice of Cyrania: 'Behold, "
	"you witness the creation of the Blade of Ruin! The sword has the power to save many a nation, but it also has the power to "
	"destroy tenfold what it is capable of saving. Should you so choose to accept guardianship of the blade, your life will "
	"undoubtedly take many unexpected twists. Many a head will be cut down in a silvery blur as you twirl the blade deftly in the "
	"air. A king you will become someday, for the blade's power is limitless.'

  
	SetYesNo(STORY2)
NO(STORY)
	Conversation
	"As you wish."
YesNoELSE(STORY)
	Conversation
	"Well, would you like to hear the story?"
	SetYesNo(STORY)
	
YES(STORY2)
	Conversation
	"So amazed was he by this uncanny sight that he never noticed his hostess had disappeared. Examining the sword, he found that "
	"he could not describe the feeling of holding it. The sword was at the same time warm to the touch as it would send chills to "
	"the bones. As he held it up to the sun, the voice of Cyrania filled his mind: 'Do what you will with the sword, but hear this. "
	"You hold in your hands the Blade of Ruin. Its power is immense, and is now yours to wield. Beware however, as this power does "
	"come without a cost. If you were ever to attempt to dispose of the sword in any way, its power would surely consume you with "
	"desire"




	"With this, the goddess departed and was never seen again by mortal eyes. After pondering over this for a few moments, Alexis "
	"gazed at his sword and completely forgot about



NO(STORY2)
	Conversation
	"I see."
YesNoELSE(STORY2)
	Conversation
	"Would you like to hear more of the story?"
	SetYesNo(STORY2)

	"The famed blade of ruin was used in times old by a travelling adventurer of some renown named Alexis. The young man "
	"had happened to wander upon Cyrania, Goddess of the Spring, as she was bathing in a small pond. Upon seeing her, the "
	"youth instantly fell to his knees, his heart filled with admiration. To this day, it is still pondered upon whether the "
	"goddess intentionally lured the young man to her, or if it was nothing more than a simple coincidence. The goddess appeared "
	"to be taken aback at this intrusion into her haven. She explained to Alexis that he would be greatly rewarded, could he keep "
	"this location secret. Accepting his vow of secrecy, the goddess then placed a sword on the surface of the water. The sword "
	"did not sink! But instead started flowing gently towards Alexis, where he plucked it out of the water. Would you like to "
	"hear more of this tale?"

  "So amazed was he by this uncanny sight that he never noticed his hostess had disappeared. Examining the sword, he found that "
	"he could not describe the feeling of holding it. The sword was at the same time warm to the touch as it would send chills to "
	"the bones. As he held it up to the sun, the voice of Cyrania filled his mind: 'Do what you will with the sword, but hear this. "
	"You hold in your hands the Blade of Ruin. Its power is immense, and is now yours to wield. Beware however, as this power does "
	"come without a cost. If you were ever to attempt to dispose of the sword in any way, its power would surely consume you with "
	"desire

  "With this, the goddess departed and was never seen again by mortal eyes. After pondering over this for a few moments, Alexis "
	"gazed at his sword and completely forgot about
*/

Command2(INTL( 4045, "FIGHT"),INTL( 4046, "DUEL"))
INTL( 4047, "Ahhh, so you wish to test your skills against mine, is that it?")
SetYesNo(DUEL)

YES(DUEL)
	Conversation
	INTL( 4048, "Ha ha ha! Prepare to taste blood then!") FIGHT
NO(DUEL)
	Conversation
	INTL( 4049, "You're probably right. I don't really feel like wiping your blood off my blade just now.")
YesNoELSE(DUEL)
	Conversation
	INTL( 4050, "Make up your mind, yes or no?")
	SetYesNo(DUEL)

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 4051, "Farewell, until the next time we meet.") BREAK

Default
INTL( 4019, "I don't have time for this.")

EndTalk

}
