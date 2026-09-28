#ifndef	___NPCFunction_Data_____
#define ___NPCFunction_Data_____

#include "cocos2d.h"
#include "ext/Properties.h"
#include "gui/CCControlExtension/CCScale9Sprite.h"
#include "MsgQuest.h"
#include "ext/BasePanel.h"
#include "ext/CCTabelViewEx.h"
#include "controls/CPRichText.h"
#include <stack>
USING_NS_CC_EXT;
using namespace cocos2d;

#ifdef _DEBUG
#include <psapi.h>
#pragma comment(lib,"psapi.lib")
#endif

enum NPCtag
{
	TAG_CHANGEMAP	=10,
	TAG_NPCSHOP		=11,
	TAG_SCRIPT_C	=12,
	TAG_SCRIPT_S	=13,
	TAG_SHOWTALK	=14,
	TAG_CONNNPC		=15,
	TAG_BACK		=16,
	TAG_BACKSCENE	=17,
};

enum TASKTAG
{
	TAG_GOTONPC		=1,
	TAG_GOTOTASK	=2,

	TAG_STATE_1		=11,
	TAG_STATE_2		=12,
	TAG_STATE_3		=13,
};

struct QuestReward
{
	int rewardid;
	int rewardcnt;
};
//
class GeneralMenu;
class NPCFunctionData
{
public:
	static CCArray* getnpcFunction(std::vector<npcFunction> FunctionList,bool isSub);
	static CCMenuItemSprite* getSingleFunc(npcFunction nFunc);

	static CCLabelTTF* getSingleQuest(int qid);
	static CCString* getCString(int qid, int ptype=0);

	static void getShoesFunc(int qid,int type=0);
	static void useShoes(int qid,int type=0);

	static void AcceptQuest(int qid);
	static void SubmitQuest(int qid);
	static void GiveUpQuest(int qid);//放弃任务
	static void QuickQuest(int qid);//快速完成任务

	static void hideNPCTalkPanel();
	static void dealwithQuest(int qid);

	static void clickFunctionScriptC(int npcid, int data);
	static void clickFunctionScriptS(int npcid, int data);

	static bool clickNPCclosePanel(int npcid,int datax);
	static void clickOtherNpc(int npcid,bool isSub=false, bool isReadme=false);
	static void clearNpcStack();

	static bool checkIsQuestMonster(int id);

	static bool getNPCcontent(int npcid,std::string& content);

	static bool getNPCfuncNameSub( int npcid,std::string str,std::string& content );
	static bool getNPCcontentSub(int npcid,std::string str,std::string& content);
	static CPRichText* getNPCallContent(int npcid,int width, int height);
	static CPRichText* getBigContent(int contentid,int width, int height);

	static CPRichTextItemLabel* getSubContent(std::string str,ccColor3B color=ccWHITE,int size=18);

	static std::vector<QuestReward> getQuestReward(int qid);

	static void updatedynamicData(int NPCid);
	static void sendupdatedynamicData( int wid,int type );
	static void sendupdateinstanceData();

	static void removechildfromparent(CCNode* pNode);

	static void doFuncScript(int funcid,int datax,int datay,int dataz,std::string datas = "");
	static void repairItem();
	static void findreapairNPC();
public:
	static void setNPCID(int npcid);
	static int  getNPCID();
	static void setReadmeAndSub(bool isReadme,bool isSub);
	static bool getReadme();
	static bool getIsSub();
	static std::string getNPCName();
private:
	static int m_iNPCStaticID;
	static std::string m_sNPCname;
	static bool m_bIsSub;
	static bool m_bIsReadMe;
};

//--------------------------------------------------------------------------------------------------------------------------------------------//

class TaskRewardPanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	TaskRewardPanel();
	~TaskRewardPanel();
	virtual bool init(int qid,int row,int line);
	static TaskRewardPanel* create(int qid,int row,int line);

	void settipsdir(int tag);
private:
	void itemcallback(CCObject* pSender);
protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

private:
	CCTableViewEx * m_pTableView;
	int mrow;
	int mline;
	std::vector<QuestReward> m_rewardlist;
	int m_iTipsdir;

	enum MyEnum
	{
		dir_left,
		dir_right,
	};
};

//--------------------------------------------------------------------------------------------------------------------------------------------//
class FlyShoesMenu:public BasePanel
{
public:
	FlyShoesMenu();
	~FlyShoesMenu();
	virtual bool init(int data);
	static FlyShoesMenu* create(int data);

private:
	void flyCB(CCObject* pSender);
	void hide();
	void update(float dt);

	int m_iType;
	int m_iData;
};
#endif 
