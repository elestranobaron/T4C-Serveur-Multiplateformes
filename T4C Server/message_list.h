// message_list.h: interface for the message_list class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGE_LIST_H__330C2EE2_B3EA_11D0_9B9E_444553540000__INCLUDED_)
#define AFX_MESSAGE_LIST_H__330C2EE2_B3EA_11D0_9B9E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TFCPacket.h"
#include <VDList.h>

class __declspec(dllexport) message_list : public TemplateList <TFCPacket>
{

public:
	message_list();
	virtual ~message_list();

	void create(unsigned char *, unsigned int length);
	
	unsigned int create_list(TFCPacket &);//unsigned char **/);
	int assemble_list();

	TemplateList <TFCPacket> packet_chuncks;

	int nb_chuncked_packets;

private:
    static DWORD dwNextPacketID;
};

#endif // !defined(AFX_MESSAGE_LIST_H__330C2EE2_B3EA_11D0_9B9E_444553540000__INCLUDED_)
