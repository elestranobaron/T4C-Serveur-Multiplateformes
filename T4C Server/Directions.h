#ifndef __DIRECTIONS_H
#define __DIRECTIONS_H

#define KP_NORTH		8
#define	KP_SOUTH		2
#define KP_WEST			4
#define KP_EAST			6
#define KP_NORTHWEST	7
#define KP_SOUTHWEST	1
#define KP_NORTHEAST	9
#define KP_SOUTHEAST	3

class DIR
{
public:
	enum MOVE
	{
		 north = 1,
	     northeast = 2,
		 east = 3,
		 southeast = 4,
		 south = 5,
		 southwest = 6,
		 west = 7,
		 northwest = 8
	};
};
#endif
