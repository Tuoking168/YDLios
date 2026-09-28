#include "PanelFactory.h"
#include <map>

#include "panel/ArenaPanel.h"
#include "panel/ConvoyBeautyPanel.h"
#include "panel/MinMapPanel.h"
#include "panel/functionPanel/BoothPanel.h"
#include "panel/TreasureHuntPanel.h"
#include "panel/NPCbagPanel.h"
#include "panel/guide/GuidePanel.h"
#include "panel/guild/GuildBuildingPanel.h"
#include "panel/worship/EmigratedPanel.h"
#include "panel/worship/WorshipPanel.h"
#include "panel/worship/SpiderPanel.h"
#include "panel/social/SocialPanel.h"
#include "panel/social/dialog/AddFriendConfirmDialog.h"
#include "panel/social/dialog/AddMasterConfirmDialog.h"
#include "panel/social/dialog/AddApprenticeConfirmDialog.h"
#include "panel/social/dialog/SocialMsgNotifyDialog.h"
#include "panel/social/dialog/ProposalConfirmDialog.h"
#include "panel/social/dialog/ProposalRequestDialog.h"
#include "panel/vip/RechargePanel.h"
#include "panel/MenuListPanel.h"
#include "panel/activity/TopWelfarePanel.h"
#include "panel/activity/TopActivityPanel.h"
#include "panel/activity/TopHelpPanel.h"
#include "panel/activity/TopSportsPanel.h"
#include "panel/activity/RankPanel.h"
#include "panel/activity/CombinedServerRankPanel.h"
#include "panel/TreasureHuntPanel.h"
#include "panel/MainPanel.h"
#include "panel/RenamePanel.h"
#include "panel/activity/LevelSportsPanel.h"
#include "panel/activity/MountSportsPanel.h"
#include "panel/activity/StoneSportsPanel.h"
#include "panel/activity/OpenActivityPanel.h"
#include "panel/activity/EveryDaySalaryPanel.h"
#include "panel/activity/GiftConversionPanel.h"
#include "panel/activity/EveryDayActivePanel.h"
#include "panel/activity/LoginRewardPanel.h"
#include "panel/activity/LaunchedFocus.h"
#include "panel/activity/CombinedServer.h"
#include "panel/activity/LuckyCircle.h"
#include "panel/activity/JuBaoPenPanel.h"
#include "panel/shop/ShopPanel.h"
#include "panel/SelectRolePanel.h"
#include "panel/shop/NpcShopPanel.h"
#include "panel/shop/NpcShopComp.h"
#include "panel/setting/SystemSetting.h"

#include "panel/IconTipPanel.h"
#include "panel/shop/RubbishBagPanel.h"
#include "panel/functionpanel/BoothsellNotify.h"
#include "TopActivity.h"
#include "scene/Login.h"

using namespace cocos2d;


typedef CCLayer *(*Creator)();
typedef std::map<std::string, Creator> CreatorMap;

#define ADD_CREATOR(_map_, _class_) _map_[#_class_] = (Creator)(_class_::create);


static void addCreator( CreatorMap &creatorMap )
{
	ADD_CREATOR(creatorMap, ArenaPanel);
	ADD_CREATOR(creatorMap, ArenaFightPanel);
	ADD_CREATOR(creatorMap, ConvoyBeautyPanel);
	ADD_CREATOR(creatorMap, MiniMapPanel);
	ADD_CREATOR(creatorMap, TreasureHuntPanel);
	ADD_CREATOR(creatorMap, EmigratedPanel);
	ADD_CREATOR(creatorMap, NPCbagPanel);
	ADD_CREATOR(creatorMap, SpiderPanel);
	ADD_CREATOR(creatorMap, WorshipPanel);
	ADD_CREATOR(creatorMap, AddFriendConfirmDialog);
	ADD_CREATOR(creatorMap, AddMasterConfirmDialog);
	ADD_CREATOR(creatorMap, AddApprenticeConfirmDialog);
	ADD_CREATOR(creatorMap, SocialMsgNotifyDialog);
	ADD_CREATOR(creatorMap, ProposalConfirmDialog);
	ADD_CREATOR(creatorMap, ProposalRequestDialog);
	ADD_CREATOR(creatorMap, TopHelpPanel);
	ADD_CREATOR(creatorMap, TopSportsPanel);
	ADD_CREATOR(creatorMap, TopWelfarePanel);
	ADD_CREATOR(creatorMap, TopActivityPanel);
	ADD_CREATOR(creatorMap, NewEquipPanel);
	ADD_CREATOR(creatorMap, NewSkillPanel);
	ADD_CREATOR(creatorMap, NewFunctionPanel);
	ADD_CREATOR(creatorMap, NewGiftPanel);
	ADD_CREATOR(creatorMap, NewItemUsePanel);
	ADD_CREATOR(creatorMap, TreasureHuntPanel);
	ADD_CREATOR(creatorMap, MainPanel);
	ADD_CREATOR(creatorMap, LevelSportsPanel);
	ADD_CREATOR(creatorMap, MountSportsPanel);
	ADD_CREATOR(creatorMap, StoneSportsPanel);
	ADD_CREATOR(creatorMap, ShopPanel);
	ADD_CREATOR(creatorMap, SelectRolePanel);
	ADD_CREATOR(creatorMap, RechargePanel);
	ADD_CREATOR(creatorMap, NpcShopComp);
	ADD_CREATOR(creatorMap, OpenActivityPanel);
	ADD_CREATOR(creatorMap, EveryDaySalaryPanel);
	ADD_CREATOR(creatorMap, RankPanel);
	ADD_CREATOR(creatorMap, BoothPanel);
	ADD_CREATOR(creatorMap, SystemSetting);
	ADD_CREATOR(creatorMap, SocialPanel);
	ADD_CREATOR(creatorMap, GuildBuildingPanel);
	ADD_CREATOR(creatorMap, GiftConversionPanel);
	ADD_CREATOR(creatorMap, EveryDayActivePanel);
	ADD_CREATOR(creatorMap, SystemGiftPanel);
	ADD_CREATOR(creatorMap, LoginRewardPanel);
	ADD_CREATOR(creatorMap, LaunchedFocus);
	ADD_CREATOR(creatorMap, HollowItemPanel);
	ADD_CREATOR(creatorMap, MailPanel);
	ADD_CREATOR(creatorMap, JuBaoPenPanel);
	ADD_CREATOR(creatorMap, CombinedServer);
	ADD_CREATOR(creatorMap, NoticePanel);
	ADD_CREATOR(creatorMap, LuckyCircle);
	ADD_CREATOR(creatorMap, RenamePanel);
	ADD_CREATOR(creatorMap, CombinedServerRankPanel);

	ADD_CREATOR(creatorMap, CopyNotifyTipPanel);
	ADD_CREATOR(creatorMap, RubbishBagPanel);
	ADD_CREATOR(creatorMap, BoothsellNotify);
	ADD_CREATOR(creatorMap, ContactUs);
	ADD_CREATOR(creatorMap, AccountInfo);
	ADD_CREATOR(creatorMap, Register_3737);
}

////////////PanelFactory///////////////////////////////////////////////
CCNode * PanelFactory::create( const std::string &panelName )
{
	static CreatorMap creatorMap;
	if (creatorMap.empty())
	{
		addCreator(creatorMap);
	}

	//
	CreatorMap::iterator it = creatorMap.find(panelName);
	if (it != creatorMap.end())
	{
		return it->second();
	}
	CCLog(">>>Error: PanelFactory::create, unknown panelName = %s", panelName.c_str());
	return NULL;
}
