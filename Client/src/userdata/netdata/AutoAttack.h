#ifndef	___AutoAttack_____
#define ___AutoAttack____

#include <stack>

class AutoAttack 
{
public:
	static void openAutoAttack();
	static void closeAutoAttack();
	static bool checkAutoAttack();

private:


private:
	static bool m_bAutoAttack;

};
#endif //___AutoAttack_____