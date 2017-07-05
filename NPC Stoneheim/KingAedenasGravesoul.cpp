//////////////////////////////////////////////////////////////////////
// KingAedenasGravesoul.cpp: 
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "KingAedenasGravesoul.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

KingAedenasGravesoul::KingAedenasGravesoul()
{}

KingAedenasGravesoul::~KingAedenasGravesoul()
{}

extern NPCstructure::NPC KingAedenasGravesoulNPC;

void KingAedenasGravesoul::Create( ){
	npc = KingAedenasGravesoulNPC;
   SET_NPC_NAME(   "[10870]King Aedenas Gravesoul" );
	npc.InitialPos.X = 1050;
	npc.InitialPos.Y = 1090;
	npc.InitialPos.world = 0;		 
}

void KingAedenasGravesoul::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT GIVESTAFF = 1; 
CONSTANT TakeBooks = 2;
 
InitTalk

Begin
""
IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 16)
	Conversation 
	INTL( 8024, "Your final task is to seek the one person in the world who can combine those items into the Will of Artherk. Her "
	"name is Glaenshenmilandira. She is a white-winged Seraph, which is as close to a god as I've ever met in this "
	"world. You can find her in the Nether Isles, which lie between this world and the next. She is very powerful, but "
	"she does not like to interact with mortals, so she lives as a recluse. Seeing as you are on a higher quest, however, "
	"she will certainly help you.")
ELSEIF ((CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 14) || (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 15))
	Conversation
	FORMAT(INTL( 8025, "%s, you have served us well in the past and it is our honorable duty to tell you that you are in great danger. "
	"I had a dream last night where you walked alone in darkness and fought terrible foes. I also saw the face of a "
	"man Roen Greenleaf hover behind it all. I fear this bodes great ill for your quest. Perhaps you should seek this "
	"Greenleaf fellow at once. But if you wish to simply pursue your quest, so be it. You must now elist the aid "
	"of \"Anrak\". Seek him throughout the lands and ask him about the Drums of Fate. Only two drums are "
	"needed. That is all I can tell you."), USER_NAME) 
	GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 15) 
ELSEIF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) >= 2) 
	Conversation
	FORMAT(INTL( 8026, "Greetings, %s. It is nice to see that you have safely returned from your journey."), USER_NAME)
ELSE
	Conversation
	INTL( 8027, "What brings you into my royal presence?")
ENDIF 

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8028, "I am Aedenas Gravesoul, revered King of the centaurs.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8029, "I am king of the Centaurs. I have sworn to protect my people "
"from the Kahp Leth skraugs.")
 
CmdAND(INTL( 8030, "COLLECTOR"),INTL( 1427, "BOOK"))
""
IF (CheckItem(__OBJ_COLLECTOR_BOOK) < 5)
	Conversation
	INTL( 8031, "Those books come in series of five. Thus if you bring me a complete series, I will "
	"reward you with a \"Ring\" \"of\" \"the\" \"Lion\".")
ELSE
	Conversation
	INTL( 8032, "I happen to know you have a complete series of Collector's Books. Would you trade it for a "
	"\"Ring\" \"of\" \"the\" \"Lion\"?")
	SetYesNo(TakeBooks)
ENDIF

YES(TakeBooks)
	IF (CheckItem(__OBJ_COLLECTOR_BOOK) < 5)
		Conversation
		INTL( 8033, "I fear we must end this now, you do not have a complete series, all of a sudden. A pity, really.")
	ELSE
		Conversation 
		INTL( 8034, "Let us do this trade quickly, then.")
		FOR(0,5) 
			TakeItem(__OBJ_COLLECTOR_BOOK)
		ENDFOR
		GiveItem(__OBJ_RING_OF_THE_LION)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8035, "You receive a Ring of the Lion.")) 
		;int nExpReward = USER_LEVEL*3750;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
		GiveXP(nExpReward)
	ENDIF

NO(TakeBooks)
	Conversation
	INTL( 8036, "So be it. Your loss, then.")

YesNoELSE(TakeBooks)
	Conversation
	INTL( 8037, "Answer with a \"yes\" or a \"no\".")
	SetYesNo(TakeBooks)

Command2(INTL( 554, "HELP"),INTL( 896, "QUEST"))
INTL( 8038, "If you have time, I would look favorably upon your bringing me \"Collector's\" \"Books\" "
"to add to my collection.")

CmdAND(INTL( 8039, "RING"),INTL( 8040, "LION"))
INTL( 8041, "It is quite a precious item. Not only is it almost priceless, but it will give you great courage. Unless you "
"wish to give it to Sir Beltigan, I hear he is in the business of purchasing those rings. I'm sure it would "
"help your karma.")

Command2(INTL( 8001, "ZION"),INTL( 8002, "THUNDERHEART"))
INTL( 8042, "He probably doesn't realize I know what he's been up to, but that's how it should be. I know he plots "
"behind my back and I can make sure he doesn't get out of control. Keeps your friends close, I say, and "
"your enemies even closer.")

Command2(INTL( 8005, "KYATHOS"),INTL( 8006, "SHATTERSKULL"))
INTL( 8043, "Strong and reliable Kyathos. He's one of our best warriors and an excellent guard. When he patrols our town, "
"I know everyone's safe.")

Command2(INTL( 8009, "THOR"),INTL( 8010, "GLAREFIRE"))
INTL( 8044, "His manneris a little gruff, but he's one of the best smiths you can hope to find in the world. Be sure to "
"drop by his shop, some day, and buy a few trinkets off him.")

Command2(INTL( 8013, "DIONYSUS"),INTL( 8014, "SILVERSTREAM"))
INTL( 8045, "Without Dionysus, ruling the Centaurs would be a far more daunting task than it currently is. His gentle words "
"of wisdom, his vision and his compassion would make him an excellent king to succeed me when I depart, but "
"I know he is dedicated to Artherk and would not want the position. That's why he would be perfect. *sigh* I "
"wonder sometimes if there will be someone to follow in my footsteps when I'm gone...")

Command2(INTL( 8046, "MALACHAI"),INTL( 8047, "FATEBRINGER"))
INTL( 8048, "I suspect he works in secret with Zion Thunderheart, but I have no proof.")

Command2(INTL( 8017, "GLADDIUS"),INTL( 8018, "WINDCHASER"))
INTL( 8049, "It seems the Windchasers have always been guardians of our town. They are a strong and proud lineage, and "
"I couldn't imagine our clan without them to protect us.")

CmdAND(INTL( 5672, "HAMMER"),INTL( 8050, "FINALITY"))
INTL( 8051, "Seek out Thor Glarefire, our most competent blacksmith.")

// __QUEST_FLAG_WILL_OF_ARTHERK_QUEST 
// 0: -- 
// 1: Spoken with Beltigan. Beowulf is told to seek counsel of Aedenas Gravesoul.
// 2: Spoken with Aedenas. Beowulf is told to seek the White Crow to fetch the Fangs of True Resolve. 
// 3: Spoken with Mithanna Snowraven. She requires a Jade Ring of Sorcery + a dozen of Kraanian eyes.
// 4: Brought back the required components, Mithanna Snowraver tells Beowulf that he must seek Nissus Haloseeker.  
// 5: Spoken with Nissus and the Fangs are on their way. 
// 6: The last fang is created and the Night Retrievers are summoned. If they successfully steal a Fangs, this Flag
// is reduced to 5 and minus one fang. 
// 7: Spoken with King Aedenas, told about Zion Thunderheart's betrayal 
// 8: Gotten the staff of submission from King Aedenas and sent on the quest to get mind control talisman 
// 9: Gotten all 12 talismans and brought them back to the centaur king. 
// 10:
// 11: 
// 12:
// 13:
// 14: User has the three Hammer of Finality.
//

Command(INTL( 4053, "ANRAK"))
INTL( 8052, "I think that he lives somewhere in Raven's Dust. ")

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CmdAND(INTL( 8053, "WILL"),INTL( 1243, "ARTHERK"))
""
SWITCH( CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) ) 
	CASE(0)
		Conversation
		INTL( 8054, "You are not ready to undertake the quest that will lead you to the Will of Artherk.")
	ENDCASE
	CASE(1) 
		Conversation
		INTL( 8055, "The Holy Paladin has sent you for counsel of mine in the quest of the Will of Artherk? Then, so be it. "
		"First, you must bring back four \"Fangs\" \"of\" \"True\" \"Resolve\". I cannot tell you how they are made, however. "
		"These are not items that our kin makes. You should seek one of your own kind, the one we know as White "
		"Crow, and ask for her assistance.")
		GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 2) 
	CASE(2) 
		Conversation
		INTL( 8056, "I have already told you what you need to know. You must seek out the White Crow for further "
		"instructions.")
	ENDCASE
	CASE(3) 
		Conversation
		FORMAT(INTL( 8057, "You're doing well, %s. Come back when you've gathered the four Fangs of True Resolve."), USER_NAME) 
	ENDCASE
	CASE(4)
		Conversation
		FORMAT(INTL( 8057, "You're doing well, %s. Come back when you've gathered the four Fangs of True Resolve."), USER_NAME) 
	ENDCASE
	CASE(5)
		Conversation
		FORMAT(INTL( 8057, "You're doing well, %s. Come back when you've gathered the four Fangs of True Resolve."), USER_NAME) 
	ENDCASE
	CASE(6) 
		Conversation
		FORMAT(INTL( 8058, "%s, I congratulate you for gathering the Fangs of True Resolve. Thus, you have completed the first "
		"step of your holy quest. Alas, I am currently troubled and I cannot help you further in your quest for the "
		"moment. My cousin, Zion Thunderheart, has been spreading foul rumors about me. Although I am aware of my "
		"cousin's treachery, I cannot confront him directly. His support among the Centaurs has grown stronger "
		"recently. He has distributed \"mind-control\" \"talismans\" to some centaurs. If you could lessen "
		"his bound by freeing the red-eyed centaurs of the talismans' influence, then I could use my power "
		"to put a stop to my cousin's scheme."), USER_NAME) 
		GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 7) 
	ENDCASE
	CASE(7)  
		Conversation
		INTL( 8059, "Please help me free the red-eyed centaurs from the influence of the \"mind-control\" \"talismans\".")
	ENDCASE
	CASE(8)
		Conversation
		INTL( 8060, "Please help me free the red-eyed centaurs from the influence of the \"mind-control\" \"talismans\".")
	ENDCASE
	CASE(9)
		Conversation
		FORMAT(INTL( 8061, "%s, my friend, you have greatly aided me and I am grateful to you. You will need to be very careful, from now on. "
		"To pursue your quest, you must now find  three \"Hammers\" \"of\" \"Finality\". None can make them on Stoneheim, but I would suggest "
		"that you seek the advice of Thor Glarefire, the best smith we have. Heed his counsel and make great haste."), USER_NAME) 
	ENDCASE
	CASE(16)
		Conversation
		INTL( 8062, "Your final task is to seek the one person in the world who can combine those items into the Will of Artherk. Her "
		"name is Glaenshenmilandira. She is a white-winged seraph, which is as close to a god as I've ever met in this "
		"world. You can find her in the Nether Isles, which lie between this world and the next. She is very powerful, but "
		"she does not like to interact with mortals, so she lives as a recluse. Seeing as you are on a higher quest, however, "
		"she will certainly help you.")
		IF (CheckItem(__OBJ_ETHEREAL_KEY) == 0) 
			Conversation
			INTL( 8063, " Take this ethereal key. You will need the key to use the \"Ethereal\" \"Portal\" that "
			"will take you to her. As for the location of the portal, I do not know it. It "
			"is never located in the same place, but it is definitely on Stoneheim.")
			PRIVATE_SYSTEM_MESSAGE(INTL( 8064, "Aedenas gives you an ethereal key.")) 
			GiveItem(__OBJ_ETHEREAL_KEY) 
		ENDIF
	ENDCASE
	OTHERWISE
		Conversation
		FORMAT(INTL( 8065, "Do not lose heart, %s. You have done well so far."), USER_NAME) 
ENDSWITCH

Command(INTL( 10770, "ETHEREAL PORTAL"))
INTL( 10771, "You will need the ethereal key to use the ethereal portal. As for the location of the portal, "
"I'm afraid that you're on your own as the portal is never located in the same place.") 

CmdAND3(INTL( 8927, "FANG"),INTL( 9630, "TRUE"),INTL( 6869, "RESOLVE"))
INTL( 10772, "I have already told you all there is to know about these.")

Command(INTL( 10476, "BOND")) 
""
IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) >= 9) 
	IF (CheckItem(__OBJ_STAFF_OF_SUBMISSION) >= 1) 
		Conversation
		INTL( 10477, "You no longer need the staff of submission. Therefore, I shall take it back.")
		;int nNumStaff = CheckItem(__OBJ_STAFF_OF_SUBMISSION); 
		FOR(0, nNumStaff ) 
			TakeItem(__OBJ_STAFF_OF_SUBMISSION)
		ENDFOR 
		PRIVATE_SYSTEM_MESSAGE(INTL( 8072, "Aedenis frees you of the staff of submission's bond."))
	ELSE
		Conversation
		INTL( 10478, "It does not seem to me that you have a staff of submission in your backpack. If you "
		"actually have the staff equipped, I cannot free you of its bond.") 
	ENDIF 
ELSE
	Conversation
	INTL( 10479, "If you have a staff of submission in your possession, I cannot free you of its bond just yet.")	
ENDIF			

Command(INTL( 11348, "MIND-CONTROL TALISMAN")) 
""
IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 7) 
	Conversation
	INTL( 8069, "If you want to defeat the red-eyed centaurs, you will need the \"staff\" \"of\" \"submission\" first.")
ELSEIF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 8) 
	IF (CheckItem(__OBJ_MIND_CONTROL_TALISMAN) >= 12) 
		Conversation
		INTL( 8070, "You have freed at least twelve centaurs of the mind-control talismans? You have done a splendid job, my friend! "			
		"I cannot express my gratitude for thwarting my cousin's plot. Since you no longer need the "
	   "staff of submission, I'll free you of its \"bond\". Now that you've helped me out, it is time "
		"for you to continue your quest for the \"Will\" \"of\" \"Artherk\".")	
		PRIVATE_SYSTEM_MESSAGE(INTL( 8071, "You give the 12 mind-control talismans to Aedenas.")) 		
		;int nNumTalismans = CheckItem(__OBJ_MIND_CONTROL_TALISMAN); 
		FOR(0, nNumTalismans)  
			TakeItem(__OBJ_MIND_CONTROL_TALISMAN) 
		ENDFOR 
		GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 9) 
	ELSEIF (CheckItem(__OBJ_MIND_CONTROL_TALISMAN) == 11) 
		Conversation
		FORMAT(INTL( 8073, "Well done, %s. You only need one more mind-control talisman."), USER_NAME) 				
	ELSEIF (CheckItem(__OBJ_MIND_CONTROL_TALISMAN) == 1) 
		Conversation
		INTL( 8074, "You've gathered only one mind-control talisman. Gather eleven more mind-control talismans and your task will "
		"be completed.")
	ELSEIF (CheckItem(__OBJ_MIND_CONTROL_TALISMAN) > 1) 
		Conversation
		FORMAT( INTL( 8075, "Well done, %s. You've gathered %u of these foul mind-control talismans so far."), USER_NAME, CheckItem(__OBJ_MIND_CONTROL_TALISMAN) ) 
	ELSE
		Conversation
		INTL( 8076, "Using the \"staff\" \"of\" \"submission\", you can knock the red-eyed centaurs unconscious and free them "
		"of the hypnotic control by stealing their mind-control talismans. Once you've gathered twelve of "
		"these mind-control talismans, return to me and I shall help you further in your quest for the Will of Artherk.")				
	ENDIF
ELSEIF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) >= 9)
	Conversation
	INTL( 8077, "Now that you've helped me, it is time for you to continue your quest for the \"Will\" \"of\" \"Artherk\".")
ELSE
	IF (rnd.roll( dice(1,2) ) == 1) 
		Conversation
		INTL( 8078, "Our people have no interest in that matter.")
	ELSE
		Conversation
		INTL( 8079, "I have given no thought about this.")
	ENDIF 
ENDIF 

CmdAND3(INTL( 8066, "MIND"),INTL( 8067, "CONTROL"),INTL( 8068, "TALISMAN"))
""
IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 7) 
	Conversation
	INTL( 8069, "If you want to defeat the red-eyed centaurs, you will need the \"staff\" \"of\" \"submission\" first.")
ELSEIF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 8) 
	IF (CheckItem(__OBJ_MIND_CONTROL_TALISMAN) >= 12) 
		Conversation
		INTL( 8070, "You have freed at least twelve centaurs of the mind-control talismans? You have done a splendid job, my friend! "			
		"I cannot express my gratitude for thwarting my cousin's plot. Since you no longer need the "
	   "staff of submission, I'll free you of its \"bond\". Now that you've helped me out, it is time "
		"for you to continue your quest for the \"Will\" \"of\" \"Artherk\".")	
		PRIVATE_SYSTEM_MESSAGE(INTL( 8071, "You give the 12 mind-control talismans to Aedenas.")) 		
		;int nNumTalismans = CheckItem(__OBJ_MIND_CONTROL_TALISMAN); 
		FOR(0, nNumTalismans)  
			TakeItem(__OBJ_MIND_CONTROL_TALISMAN) 
		ENDFOR 
		GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 9) 
	ELSEIF (CheckItem(__OBJ_MIND_CONTROL_TALISMAN) == 11) 
		Conversation
		FORMAT(INTL( 8073, "Well done, %s. You only need one more mind-control talisman."), USER_NAME) 				
	ELSEIF (CheckItem(__OBJ_MIND_CONTROL_TALISMAN) == 1) 
		Conversation
		INTL( 8074, "You've gathered only one mind-control talisman. Gather eleven more mind-control talismans and your task will "
		"be completed.")
	ELSEIF (CheckItem(__OBJ_MIND_CONTROL_TALISMAN) > 1) 
		Conversation
		FORMAT( INTL( 8075, "Well done, %s. You've gathered %u of these foul mind-control talismans so far."), USER_NAME, CheckItem(__OBJ_MIND_CONTROL_TALISMAN) ) 
	ELSE
		Conversation
		INTL( 8076, "Using the \"staff\" \"of\" \"submission\", you can knock the red-eyed centaurs unconscious and free them "
		"of the hypnotic control by stealing their mind-control talismans. Once you've gathered twelve of "
		"these mind-control talismans, return to me and I shall help you further in your quest for the Will of Artherk.")				
	ENDIF
ELSEIF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) >= 9)
	Conversation
	INTL( 8077, "Now that you've helped me, it is time for you to continue your quest for the \"Will\" \"of\" \"Artherk\".")
ELSE
	IF (rnd.roll( dice(1,2) ) == 1) 
		Conversation
		INTL( 8078, "Our people have no interest in that matter.")
	ELSE
		Conversation
		INTL( 8079, "I have given no thought about this.")
	ENDIF 
ENDIF 

Command(INTL( 8080, "STAFF OF SUBMISSION"))
""
IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 7)
	Conversation
	INTL( 8081, "The staff of submission is a magical weapon that can knock unconscious the red-eyed centaurs without "
	"harming them more than necessary. If you can defeat twelve red-eyed centaurs using the staff of submission and "
	"bring me back the mind-control talismans, I shall help you further in your quest. Do you agree to help me?")
	SetYesNo(GIVESTAFF) 
ELSEIF ((CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 8) || (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 9)) 
	Conversation
	INTL( 8082, "Using the \"staff\" \"of\" \"submission\", you can knock the red-eyed centaurs unconscious and free them "
	"of the hypnotic control by seizing their mind-control talismans. Once you've gathered twelve of "
	"these mind-control talismans, return to me and I shall help you further in your quest for the Will of Artherk.")
ELSE
	Conversation
	INTL( 8083, "That does not concern you.")
ENDIF 

YES(GIVESTAFF)
	Conversation	
	FORMAT(INTL( 8084, "%s, I cannot express how grateful I am. Here, I give you this staff of submission."), USER_NAME) 
	PRIVATE_SYSTEM_MESSAGE(INTL( 8085, "Aedenas gives you a staff of submission.")) 
	GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 8) 
	GiveItem(__OBJ_STAFF_OF_SUBMISSION) 

NO(GIVESTAFF)
	Conversation
	INTL( 8086, "Come back once you've decided to help me.")

YesNoELSE(GIVESTAFF)
	Conversation
	INTL( 8087, "Well, will you aid me?")
	SetYesNo(GIVESTAFF) 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Command(INTL( 8088, "ZION THUNDERHEART"))
INTL( 8089, "Zion Thunderheart is my cousin and he is next in line for the centaur throne. He hungers for power and even went as "
"far as spreading foul rumors about me in hope of gaining support.")

CmdAND3(INTL( 8090, "RED"),INTL( 3955, "EYE"),INTL( 7995, "CENTAUR"))
INTL( 8091, "The red-eyed centaurs are under the hypnotic influence of the mind-control talismans that have been distributed "
"by my treacherous cousin, Zion Thunderheart.")

Command(INTL( 8092, "WHITE CROW"))
INTL( 8093, "If you seek the Fangs of True Resolve, the White Crow can help you in your quest.")
											
Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8094, "You are a dishonor to your race.") BREAK

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 1075, "Farewell.")
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1) 
	Conversation
	INTL( 8078, "Our people have no interest in that matter.")
ELSE
	Conversation
	INTL( 8079, "I have given no thought about this.")
ENDIF 

EndTalk
}
