/*
Trade.h
Header file for the Trade object.
Its designed to be used on the trade system and also any other thing it may apply latter

Originally Written by Carlos Lima (carlos@dialsoft.com)
for Dialsoft (http://www.dialsoft.com)
*/

#ifndef DIALSOFT_TRADE_H_2005_06_24_AKJHE_9083KLJA__INCLUDED_
#define DIALSOFT_TRADE_H_2005_06_24_AKJHE_9083KLJA__INCLUDED_

#include "Lock.h"
#include "Colors.h"

//class Trade2;
class Character;
class Objects;
class ItemContainer;

////////////////////////////////////////////////////////////////////////
// Trade Manager Class
// This class should handle *everything* related to the trade
// Every access to the trade should go thru this class
////////////////////////////////////////////////////////////////////////
class EXPORT TradeMgr2 {
public:
	enum AffectedCharacter
	{
		AC_MYSELF=0,
		AC_OTHER=1,
		AC_BOTH=2
	};
	enum Colors {
		CO_TRADECOLOR = ORANGE
	};
	class Status {
		public:
		enum TradeStatus
		{
			TS_Invalid,
			TS_Inviting,
			TS_Trading
		};
		enum CharacterStatus
		{
			EditingItems=0,
			Ready=1,
			Confirmed=2,
		};
	};

	class ErrorCodes {
		public:
			enum Request 
			{
				NotCloseEnoughForTrade,
				InvalidParameters,
				InvitorIsTrading,
				TargetIsTrading,
				InvitorIsAlreadyInvitingTarget,
				InviteDone,
				TradeStarted
			};
			enum Cancel
			{
				NoTradeToCancel,
				InviteCancelled,
				TradeCancelled
			};
			enum Finish
			{
				NoTradeToFinish,
				CantFinishAnInvite,
				CantFinishImproperCharacterStatus,
				TradeFinished
			};
			enum ClearItemsFromTrade
			{
				NoTradeToClear,
				TradeCleared
			};
			enum AddItem
			{
				ItemAdded,
				ItemCantBeAdded,
				TradeInvalidForItemAdding
			};
			enum RemoveItem
			{
				ItemRemoved,
				ItemCantBeRemoved,
				TradeInvalidForItemRemoving
			};
			enum SetCharacterStatus
			{
				NoTradeToSetCharacterStatus,
				CharacterStatusInvalid,
				CharacterStatusSet,
				CharacterStatusSetAndTradeFinished
			};
			enum SetTradeStatus
			{
				NoTradeToSetStatus,
				//TradeStatusInvalid,
				TradeStatusSet
			};
			enum IsTradeValid
			{
				InvalidTrade,
				IsInviting,
				IsTrading
			};
	};
	TradeMgr2(Character &ownerCharacter);
	//TradeMgr2(/*Character &ownerCharacter*/);
	~TradeMgr2();
//	void							SetOwnerCharacter(Character *thisCharacter); // Sets the character that owns the TradeMgr
//	ErrorCodes::Request				Request(Character *invitedCharacter); // Invite or accept a trade
	ErrorCodes::Request				Request(TradeMgr2 &pInvitedTradeMgr); // Invite or accept a trade
	ErrorCodes::Cancel				Cancel(); // Cancel the trade
	ErrorCodes::Cancel				CancelDisturbed(); // Cancel triggered when disturbed
	ErrorCodes::Finish				Finish(); // Finish the trade
	ErrorCodes::ClearItemsFromTrade	ClearItemsFromTrade(); // Removes all items from trade back to the backpack
	ErrorCodes::AddItem				AddItemToTrade(Objects *itemToAdd); // Add an item to the trade list
	ErrorCodes::RemoveItem			RemoveItemFromTrade(DWORD itemID, DWORD itemQty, Objects *&removedObj); // Remove an item from the trade list and points *removedObj to it
	ErrorCodes::SetCharacterStatus	SetCharacterStatus(TradeMgr2::Status::CharacterStatus newStatus); // Set the character status on the trade.
	ErrorCodes::IsTradeValid		IsTradeValid(); // Returns a value stating if trade is invalid, is inviting or is trading.
	CLock*							GetCLock(); // Returns the static CLock object used to lock Trade operations!
	BOOL							GetItemName(DWORD pItemID, CString &pItemName, WORD pLanguageID); // Searchs for the item and if found, sets pItemName to its name and return TRUE. Else, returns FALSE.
	BOOL							GetItemNameFromOther(DWORD pItemID, CString &pItemName, WORD pLanguageID); // Searchs for the item on the other's container and if found, sets pItemName to its name and return TRUE. Else, returns FALSE.
	ItemContainer*					GetItemContainer(); // Return the internal item container. BE CAREFULL and never forget to Lock/Unlock the TradeMgr.
	unsigned int					GetFreeWeight(); // Return the amount of space available on the other character's backpack
	void							TradeSendInfoMessage(const CString &pMessage); // Send a message to the player properly identified as a Trade System Message
	void							TradeSendInfoMessage(DWORD pID); // Send a message to the player properly identified as a Trade System Message
	//BLBLBL
	//void							SetOwner(Character &newOwner);//assign the owner character
	//BLBLBL : passé variable en public :
	Character							&m_ThisCharacter; // The character who owns this instance of the TradeMgr
private:

//	inline Character*				GetOtherCharacter(); // Return the other character involved on the trade
//	Objects*						TakeFirstItemFromContainer(); // Take the top object from the container and returns it; NULL if none.
	inline void						CheckInitialization(); // Verify if the TradeMgr have been initialized
	void							PutItemsFromTradeToBackpack(CString *pItemNamesLog = NULL); // Move all items from the trade container to the backpack. If pItemNamesLog is not NULL, it's value will be set to a comma separated list with name and qty of moved items.
	ErrorCodes::SetTradeStatus		SetTradeStatus(TradeMgr2::Status::TradeStatus newStatus); // Sets the status of the trade
	void							UpdateContainersSize(); // Updates the size of the containers.
	void							ResetTradeData(); // Reset all trade data
	void							LogTradeFinish(const CString &pMyItems, const CString &pOtherItems); // Saves the log of the finished trade, stating which items where given by each characters
	void							EventInviteSent(TradeMgr2 &pInvited); // You sent an invite to the other player
	void							EventInviteReceived(TradeMgr2 &pInvitor); // Received an invite from someone
	void							EventTradeStarted(TradeMgr2 &otherParty); // The trade started!
	void							EventTradeCanceled(); // The trade got canceled
	void							EventTradeFinished(); // The trade got finished
	void							EventTradeStatusChanged(TradeMgr2::AffectedCharacter pWhoChanged, TradeMgr2::Status::CharacterStatus pNewStatus); // The status of the other character changed
	void							EventTradeContentChanged(); // The items being traded changed
	void							EventItemAdded(TradeMgr2::AffectedCharacter pWhoAdded, CString pItemDescription); // Notify character an item got added to the trade
	void							EventItemRemoved(TradeMgr2::AffectedCharacter pWhoAdded, CString pItemDescription); // Notify character an item got removed from the trade

	void							PacketSendInviteReceived(TradeMgr2 &pInvitor); // Send a packet to tell the client that pInvitor is asking him for a trade
	void 							PacketSendTradeStarted(TradeMgr2 &pInvitor); // Send a packet to tell the client that a trade between him and pInvitor has just started!
	void 							PacketSendTradeCanceled(); // Send a packet to tell the client that the trade got cancelled
	void							PacketSendTradeFinished(); // Send a packet to tell the client that the trade got finished
	void							PacketSendTradeStatus(); // Send a packet with the status of both characters on the trade
	void 							PacketSendTradeContents(AffectedCharacter pSourceChar); // Send the contents of the trade
	void 							PacketSendTradeFullContents(); // Send the content of the trade (both sides) and also send the backpack contents

	// //////// /Data/ //////// //
	static CLock						m_TradeLock; // Static Lock. Only one Trade operation can be handled at a time.
	//BLBLBL//Character							&m_ThisCharacter; // The character who owns this instance of the TradeMgr
	TradeMgr2							*mOtherTrade; // The trade manager of ther other person :)
	TradeMgr2::Status::TradeStatus		m_Status; // Status of the trade
	TradeMgr2::Status::CharacterStatus	m_StatusCharacter; // Status of this character on the trade
	ItemContainer						*m_Container; // The container where my items will get deposited
};

/*
////////////////////////////////////////////////////////////////////////
// Trade Class
// This class holds only the data related to the trade
// No call to this class (functions or data) will be done except by the TradeMgr class.
////////////////////////////////////////////////////////////////////////

class __declspec(dllexport) Trade2 {
	friend TradeMgr2;
public:
private:
	// Constructor
	Trade2(Character *CharacterOne, Character *CharacterTwo) : m_CharacterOne(CharacterOne), 
		m_CharacterTwo(CharacterTwo), m_Status(TradeMgr2::Status::Inviting), m_StatusCharacterOne(TradeMgr2::Status::EditingItems), 
		m_StatusCharacterTwo(TradeMgr2::Status::EditingItems), m_ContainerFromPlayerOne(NULL), m_ContainerFromPlayerTwo(NULL)
		{}
	// Destructor
	~Trade2() {} // NEEDS ATTENTION!!


	// Data members
	Character									*m_CharacterOne; // First of the two characters involved in the trade
	Character									*m_CharacterTwo; // Second of the two characters involved in the trade
	TradeMgr2::Status::TradeStatus				m_Status; // Status of the trade
	TradeMgr2::Status::CharacterStatus			m_StatusCharacterOne; // Status of the character one on the trade
	TradeMgr2::Status::CharacterStatus			m_StatusCharacterTwo; // Status of the character two on the trade
	ItemContainer								*m_ContainerFromPlayerOne; // The container where CharacterOne's items will get deposited
	ItemContainer								*m_ContainerFromPlayerTwo; // The container where CharacterTwo's items will get deposited
};
*/

#endif //ndef DIALSOFT_TRADE_H_2005-06-24_AKJHE_9083KLJA__INCLUDED_
