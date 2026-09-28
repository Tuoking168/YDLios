#ifndef	___CommonFunction_Data_____
#define ___CommonFunction_Data_____

#include "cocos2d.h"
#include "ext/Properties.h"
using namespace cocos2d;

#include "userdata/UserItemData.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#ifdef _DEBUG
#include <psapi.h>
#pragma comment(lib,"psapi.lib")
#endif

enum TAGType
{
	TAG_Upgrade=1,
	TAG_Ehance,
	TAG_Evaluate,
	TAG_Merge,
	TAG_StoneTrans,
	TAG_ItemChange,	//幻武替换
	TAG_MoveAttr,	//极品属性转移
	TAG_Reborn,
	TAG_MoveOther,
	TAG_ClearAttr,//极品属性清洗
	TAG_PerfectQH,	//	完美强化
	TAG_Wing,	//	 翅膀羽化
	TAG_QiLing,
	TAG_FootShengjie,
	TAG_ZHUANGBEIFUMO,
	TAG_FUMOQIANGHUA,

	TYPE_HC	=100,
	TYPE_LingZhu	=	101,
	TYPE_XunZhang,
	TYPE_DaoJu,
	TYPE_ChiBang,
	TYPE_MoJingShi,
	TYPE_JiNengShu,
	TYPE_HunShi,
	TYPE_HunShiZH,
	TYPE_HCMAX	,

	TYPE_ZBSJ	=	200,
	TYPE_HWTH,
	TYPE_ZJTH,
	TYPE_JPZY,
	TYPE_ZSDZ,
	TYPE_ZBJD,
	TYPE_ZBQH,
	TYPE_QHZY,
	TYPE_JDZY,
	TYPE_JPQX,
	TYPE_CBYH,
	TYPE_OTHER,
	TYPE_ZBFM,

	Type_special	= 300,
	Type_enhance	= 320,
	Type_wing	= 340,
	Type_evaluate	= 360,
	Type_rubbish    = 380,
	Type_max	= Type_rubbish+20,

	Type_Spider	=1000,
	Type_Setting	=1001,
	Type_Npcshop	=1002,
	Type_Chart	=1003,
	Type_PetAdvance = 1004,
	Type_PetSpec = 1005,
	Type_Stone = 1006,
	Type_NULL = 2000,
};


//---------------------------------------------------------/
class CCMenuItemImageWithItem : public CCMenuItemImage
{
public:
	CCMenuItemImageWithItem();
	~CCMenuItemImageWithItem();

	static CCMenuItemImageWithItem *create( UserItem* pUserItem ,bool isdelete);
	bool initWithItem(UserItem* pUserItem ,bool isdelete);

	UserItem* getItemData();
private:
	UserItem* m_pUserItem;
	bool m_bisDelete;
};

//
class CommonFunction
{
public:
	static void sendmsgSpider(int isdouble,int useVcoin=0);
	static void sendmsgEnhance(int iid, int enhancetype, int isProtect, int useVcoin=0);
	static void sendmsgFuMo(int iid, int IsUseGold);
	static void sendmsgFuMoEnhance(int iid, int IsUsePerfectFMF, int IsUseGold);
	static void sendmsgQiling(int iid,int useVcoin=0);
	static void sendmsgFootUp(int iid,int useVcoin=0);
	static void sendmsgEvaluate(int iid, int useVcoin=0);
	static void sendmsgClearItem( int iid , int block1,int block2, int block3, int useVcoin=0);
	static void sendmsgUpgrade(int iid, int useVcoin=0);
	static void sendmsgMerge(int sid, int useVcoin=0);
	static void sendmsgStoneTrans(int iid ,int tgtsid);
	static void sendmsgChangeMagicWeapon(int iid,int tgtiid);
	static void sendmsgChangeFoot(int iid,int tgtiid);
	static void sendmsgChangeSpecialAttr(int iid,int tgtiid, int useVcoin=0);
	static void sendmsgReborn(int iid1,int iid2,int useVcoin=0);
	static void sendmsgChangeEnhance(int iid,int tgtiid, int useVcoin=0);
	static void sendmsgChangeEvaluate(int iid,int tgtiid, int useVcoin=0);
	static void sendmsgClearSpecialAttr(int iid, int useVcoin=0);
	static void sendmsgPerfectEnhance(int iid ,int reqtype ,int useVcoin=0);
	static void sendmsgPolish(int iid ,int useVcoin=0);
	static void sendmsgWingEnhance(int iid ,int useVcoin=0);
	static void sendmsgPetAdvance(int petiid , int block1,int block2, int block3 ,int useVcoin=0);
	static void sendmsgPetSpeAttr(int petiid , int useVcoin=0);

	static CCMenuItemImage* getReqEnhanceItem(UserItem* pUserItem);
	static CCMenuItemImage* getReqEvaluateItem(UserItem* pUserItem);
	static CCMenuItemImage* getReqUpgradeItem(UserItem* pUserItem);
	static CCArray* getReqMergeItem(UserItem* pUserItem);
	static CCArray* getReqStoneItem(UserItem* pUserItem);
	static CCArray* getReqStoneTransItem(UserItem* pUserItem);
	static CCMenuItemImage* getReqChangeAttrItem(UserItem* pUserItem);
	static CCMenuItemImage* getReqRebornItem(UserItem* pUserItem);
	static CCMenuItemImage* getReqRebornItemSecond(UserItem* pUserItem);
	static CCMenuItemImage* getReqEnhanceAttrItem(UserItem* pUserItem);
	static CCMenuItemImage* getReqEvaluateAttrItem(UserItem* pUserItem);
	static CCMenuItemImage* getReqClearSpecialAttrItem(UserItem* pUserItem);
	static CCMenuItemImage* getReqPerfectEhanceItem(UserItem* pUserItem);
	static CCMenuItemImage* getReqWingEnhanceItem1(UserItem* pUserItem);
	static CCMenuItemImage* getReqWingEnhanceItem2(UserItem* pUserItem);

	static CCMenuItemImage* getReqMagicWeaponQLItem(UserItem* pUserItem);
	static CCMenuItemImage* getReqFootUpItem(UserItem* pUserItem);

	static CCMenuItemImage* getReqFMCLItem(UserItem* pUserItem);
	static CCMenuItemImage* getReqFMFItem(UserItem* pUserItem);
	static CCMenuItemImage* getReqJPFMFItem(UserItem* pUserItem);

	static CCMenuItemImage* getReqPetAdvanceItem();
	static CCMenuItemImage* getReqPetSpeItem();


	static CCMenuItemImage* getTgtEnhanceItem(UserItem* pUserItem);
	static CCMenuItemImage* getTgtUpgradeItem(UserItem* pUserItem);
	static CCMenuItemImage* getTgtMergeItem(UserItem* pUserItem);
	static CCMenuItemImage* getTgtStoneItem(UserItem* pUserItem);
	static CCMenuItemImage* getTgtSpecialAttrItem(UserItem* pUserItem1,UserItem* pUserItem2);
	static CCMenuItemImage* getTgtRebornItem(UserItem* pUserItem);
	static CCMenuItemImage* getTgtEnhanceAttrItem( UserItem* pUserItem1 , UserItem* pUserItem2);
	static CCMenuItemImage* getTgtEvaluateAttrItem( UserItem* pUserItem1 , UserItem* pUserItem2);
	static CCMenuItemImage* getTgtClearSpecialAttrItem(UserItem* pUserItem);
	static CCMenuItemImage* getTgtPerfectEnhanceItem(UserItem* pUserItem, int type);
	static CCMenuItemImage* getTgtWingEnhanceItem(UserItem* pUserItem);
	static CCMenuItemImage* getTgtMagicWeaponQLItem(UserItem* pUserItem);
	static CCMenuItemImage* getTgtFootUpItem(UserItem* pUserItem);

	static std::vector<UserItem*> getBagItem(int type,int BagType);

	static int getReqVcoin( UserItem* pUserItem ,int tag,int data1);

	static ItemTooltip* getItemTips(UserItem* pUserItem,int type=0);
	static ItemTooltip* getPetBaseTips(UserPet* pPet,int type=0);

	static bool IsEnoughReq( UserItem* pUserItem ,int tag, int data1=0);
	static bool IsEnoughMoney( UserItem* pUserItem ,int tag);
	static bool IsEnoughOther( UserItem* pUserItem ,int tag);
	static int CheckIsEnoughReqOrMoneyOrOther(UserItem* pUserItem ,int tag, bool useVcoin, int data1, int data2, int data3);
	static int IsEnoughVcoin( UserItem* pUserItem ,int tag,int data1);

	static int getContentID( int m_iCurSubType );
	static int getStoneLvl(std::string);
	static int getItemCnt(int itemid);
	static bool CheckRubishEquip(int sid);

	static CCMenuItemImageWithItem* getItemIcon(UserItem* pUserItem, bool flagcount=true,bool isdelete = false);
	static CCMenuItemImageWithItem* getItemIconButDelete(UserItem* pUserItem, bool flagcount=true);


	static CCMenuItemImage* getItemIconInSkillLayer(UserItem* pUserItem);

	static UserItem* createNewItem(int sid);


	//诛魔结阵专用
	static int getCurSpiderReq();

	//物品相关操作
	static int checkShoesCount(int sid,int reason);
	static bool checkCanBatchedUsing(int sid);//判断是否能够批量使用
	static int checkZhuiZonglingCount();


};

#endif

