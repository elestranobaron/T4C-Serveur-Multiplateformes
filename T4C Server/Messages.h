// Here are defined all messages passed to unit handling DLLs

#define MSG_OnAttack				1	// Creatures, Characters, Effects
#define MSG_OnAttacked				2	// Creatures, Characters, Effects
#define MSG_OnDisturbed				3	// Objects
#define MSG_OnUse					4	// Objects
#define MSG_OnTimer					5	// None
#define MSG_OnInitialise			6	// Each
#define MSG_OnTalk					7	// Creatures
#define MSG_OnQuerySchedule			8	// None
#define MSG_OnDestroy				9	// Effects
#define MSG_OnView					10	// None
#define MSG_OnNoMoreShots			11	// None
#define MSG_OnMove					12	// Objects, Effects
#define MSG_OnDeath					13	// Creatures, Objects
#define MSG_OnHit					14	// Creatures, Characters
#define MSG_OnAttackHit             28  // Creatures, Items, Characters
#define MSG_OnEquip					15	// Objects
#define MSG_OnUnequip				16	// Objects
#define MSG_OnServerInitialisation	17	// Each
#define MSG_OnServerTermination		18	// Each
#define MSG_OnNPCDataExchange		19	// Creatures
#define MSG_OnGetUnitStructure		20	// Each
#define MSG_OnPopup					21	// Creatures
#define MSG_OnTriggered				22	// Sentries
#define MSG_OnSavePlayer			23	// Characters
#define MSG_OnLoadPlayer			24	// Characters
#define MSG_OnQueryAttackSkill		25	// Units
#define MSG_OnQueryDodgeSkill		26	// Units
#define MSG_OnDispell               27  // Spells
