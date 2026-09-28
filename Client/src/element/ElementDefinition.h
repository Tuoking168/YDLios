#ifndef __ElementDefinition_h__
#define __ElementDefinition_h__

namespace CPElement
{
	namespace Type
	{
		enum
		{
			null = 0,

			player,
			pet,
			npc,
			monster,
			skill,
		};
	}

	namespace State
	{
		enum
		{
			idle = 0,
			walk = 1,
			run = 2,
			attack = 4,
			die = 7,

			source = 0,
			middle = 1,
			target = 2,
		};
	}
}
#endif //__ElementDefinition_h__