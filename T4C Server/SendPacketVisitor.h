#ifndef SEND_PACKET_VISITOR_H_12151999
#define SEND_PACKET_VISITOR_H_12151999

class Unit;
class SendPacketVisitor{
public:
    virtual bool SendPacketTo( Unit *target ) = 0;
};


#endif