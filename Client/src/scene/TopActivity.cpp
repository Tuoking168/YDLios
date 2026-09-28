#include "TopActivity.h"
#include "MainUIModule.h"
#include "EvtDataDefinition.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "userdata/LayoutData.h"

#include "utils/StringUtils.h"
#include "utils/TestUtils.h"
#include "userdata/SystemData.h"
#include "ext/GeneralMenu.h"
#include "ext/CCMenuItemTextImage.h"
#include "controls/CPNodeHelper.h"
#include "ext/CCActionDestroy.h"
#include "patchdata/ScriptPatchManager.h"

#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/MainPanel.h"
#include "scene/panel/functionPanel/ActivityPanelDefinition.h"
#include "scene/panel/guide/GuideHelper.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "scene/panel/activity/AddUpChargePanel.h"

#include "scene/panel/activity/TopActivityPanel.h"
#include "scene/panel/activity/TopWelfarePanel.h"
#include "scene/panel/activity/TopSportsPanel.h"
#include "scene/panel/shop/NpcShopPanel.h"
#include "userdata/IconTipsData.h"
#include "userdata/luadata/LuaData.h"
#include "WorldDefinition.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/UserPetData.h"
#include "userdata/HeroData.h"
#include "userdata/StaticData.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"
#include "userdata/netdata/AutoAttack.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/ActivityData.h"
#include "scene/panel/functionPanel/BoothPanel.h"
#include "logic/platform/IPlatform.h"
#include "module/PlatformModule.h"
#include "PlatformDefinition.h"
#include "ActivityModule.h"
#include "LoginHelper.h"
#include "SceneFactory.h"
#include "../../ios/channel/common/ChannelHelper.h"

#include "network/HandleMessage.h"
#include "ext/../../ios/channel/common/ChannelHelper.h"

namespace TopButton
{
	enum
	{
		button_begin = 0,
		challenge = 0,
		activity = 1,
		welfare = 2,
		help = 3,
		shop = 4,
		combined = 5, //?????????§Ñ?

		button_max,

		autoattack	=	50,
	};
}

static void checkWelfareEffect()
{
	// sclb
	if (GuideHelper::canOpenFunction(WorldDefination::shou_chong_li_bao))
	{
		IconTipsData::setShowSubWelfare(f_shouchonglibao - f_begin, false);
		if (HeroData::getProp(Entity::attr_recharge_money))
		{
			const int giftIndexData = HeroData::getProp(Entity::attr_recharge_gift);
			if ((giftIndexData & 1) == 0)
			{
				IconTipsData::setShowSubWelfare(f_shouchonglibao - f_begin, true);
			}
		}
	}

	// mrsc
	if (GuideHelper::canOpenFunction(WorldDefination::mei_ri_shou_chong))
	{
		IconTipsData::setShowSubWelfare(f_meirishouchong - f_begin, false);
		if (ActivityData::getExDataX(EvtData::evt_gfmrsc) > 0
			&& ActivityData::getExDataY(EvtData::evt_gfmrsc) == 0)
		{
			IconTipsData::setShowSubWelfare(f_meirishouchong - f_begin, true);
		}
	}

	// ljcz
	if (GuideHelper::canOpenFunction(WorldDefination::lei_ji_chong_zhi))
	{
		IconTipsData::setShowSubWelfare(f_leijichongzhi - f_begin, false);
		if (0 < AddUpChargePanel::getGiftRewardMinIndex()
			&& AddUpChargePanel::getGiftRewardMinIndex() < AddUpChargePanel::getGiftRewardCurrentIndex())
		{
			IconTipsData::setShowSubWelfare(f_leijichongzhi - f_begin, true);
		}
	}	

	// zxjl
	if (GuideHelper::canOpenFunction(WorldDefination::zai_xian_jiang_li))
	{
		const int remainTime = ActivityData::getExDataY(EvtData::evt_gfmrzxlb) - ActivityData::getWorldTime();
		const int giftFinish = ActivityData::getExDataZ(EvtData::evt_gfmrzxlb);
		IconTipsData::setShowSubWelfare(f_zaixianjiangli - f_begin, (remainTime <= 0 && giftFinish == 0));
	}

	// mzgz
	IconTipsData::setShowSubWelfare(f_meirigongzi - f_begin, false);

	// mrdl
	IconTipsData::setShowSubWelfare(f_meiridenglu - f_begin, ActivityData::getExDataX(EvtData::evt_gfmrdllb) == 0);

	//sxgz
	IconTipsData::setShowSubWelfare(f_shangxianguanzhu - f_begin, false);

	// dbcz
	if (GuideHelper::canOpenFunction(WorldDefination::dan_bi_chong_zhi))
	{
		IconTipsData::setShowSubWelfare(f_danbichongzhi - f_begin, false);
		int srn = 0;
		StaticData::getSingleRechargeTableLength(srn);
		for (int i = 0; i < srn; i++)
		{
			const int giftID = ActivityData::getSingleRechargeReward(i + 1);
			if (giftID > 0)
			{
				IconTipsData::setShowSubWelfare(f_danbichongzhi - f_begin, true);
				break;
			}
		}
	}
}

//////////TopActiviy/////////////////////////////////////////////
TopActiviy::TopActiviy():
	m_pMenu(NULL),
	m_pCurItem(NULL),
	m_iCurTag(-1),
	m_pEffect(NULL),
	m_bUP(false),
	m_bRight(false),
	m_AutoBtn(NULL),
	mMenu(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::UI_OPEN, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_CLOSE, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_DATA_READY, this);

	m_nOX = LayoutData::getInt(CPModuleName::MAIN_UI, "topActivityMenuOx");
}

TopActiviy::~TopActiviy()
{
	CPEvtDispatcher.removeEventListener(this);
	mMenu = NULL;
}

bool TopActiviy::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	setAnchorPoint(ccp(0.5f, 0.5f));
	initUI();
	onCheckActivityEffect();
	return true;
}

void TopActiviy::initUI()
{
	mMenu = CCMenu::create();
	mMenu->setPosition(CCPointZero);
	addChild(mMenu);

	for (int i = TopButton::button_begin; i < TopButton::button_max; i++)
	{
		const std::string &key = "topButton" + StringUtils::toString(i);
		if (i == TopButton::combined)
		{
			combinedrank = LayoutData::getMenuItemImg(CPModuleName::MAIN_UI, key);
			combinedrank->setTarget(this, menu_selector(TopActiviy::onClick));
			mMenu->addChild(combinedrank, 0, i);
			if (!GuideHelper::canOpenFunction(WorldDefination::kua_fu_pai_hang_bang))
			{
				combinedrank->setVisible(false);
			}
		}
		else
		{
			CCMenuItemImage *btn = LayoutData::getMenuItemImg(CPModuleName::MAIN_UI, key);
			btn->setTarget(this, menu_selector(TopActiviy::onClick));	
			mMenu->addChild(btn, 0, i);
		}	
	}

	m_AutoBtn = SystemData::getMenuItemImageByPlist("topauto_attack");
	m_AutoBtn->setTarget(this, menu_selector(TopActiviy::onClick));
	m_AutoBtn->setPosition(ccp(mMenu->getChildByTag(TopButton::shop)->getPositionX()-60,mMenu->getChildByTag(TopButton::shop)->getPositionY()));
	mMenu->addChild(m_AutoBtn, 0, TopButton::autoattack);
}

void TopActiviy::moveRight()
{
	if (m_bRight)
	{
		return;
	}

	m_bRight = true;

	int y = 0;
	if (m_bUP)
	{
		y = m_nOX;
	}

	stopAllActions();
	CPAssert(mMenu != NULL);

	CCAction *action = CCEaseBackIn::create(CCMoveTo::create(0.3f, ccp(m_nOX, y)));
	runAction(action);
}

void TopActiviy::moveLeft()
{
	if (!m_bRight)
	{
		return;
	}

	m_bRight = false;

	int y = 0;
	if (m_bUP)
	{
		y = m_nOX;
	}
	
	stopAllActions();
	CPAssert(mMenu != NULL);

	CCAction *action = CCEaseBackOut::create(CCMoveTo::create(0.3f, ccp(0, y)));
	runAction(action);
}

void TopActiviy::moveUp()
{
	if (m_bUP)
	{
		return;
	}

	m_bUP = true;
	
	int x = 0;
	if (m_bRight)
	{
		x = m_nOX;
	}
	
	stopAllActions();
	CPAssert(mMenu != NULL);

	CCAction *action = CCEaseBackIn::create(CCMoveTo::create(0.3f, ccp(x, m_nOX)));
	runAction(action);
}

void TopActiviy::moveDown()
{
	if (!m_bUP)
	{
		return;
	}

	m_bUP = false;
	
	int x = 0;
	if (m_bRight)
	{
		x = m_nOX;
	}
	
	stopAllActions();
	CPAssert(mMenu != NULL);

	CCAction *action = CCEaseBackOut::create(CCMoveTo::create(0.3f, ccp(x, 0)));
	runAction(action);
}

void TopActiviy::onClick( CCObject* pSender )
{
	CCMenuItemImage *node = dynamic_cast<CCMenuItemImage *>(pSender); 
	if(node)
	{
		const int tag = node->getTag();
		if (tag==TopButton::shop)
		{
			CPEventHelper::openPanel("ShopPanel");			
		}
		else if (tag == TopButton::combined)
		{
			CPEventHelper::openPanel("CombinedServerRankPanel");
		}
		else if (tag==TopButton::autoattack)
		{
// 			int idx = LoginHelper::getSavedServerIndexBysavedId(LoginHelper::getSavedServerId());
// 			LoginHelper::startGameServer(idx);
// 			const int pid = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
// 			LoginHelper::enterGame(LoginHelper::getIndexByPID(pid));
// 			//CCDirector::sharedDirector()->replaceScene(SceneFactory::sceneResLoading());
// 			return;
			if (!AutoAttack::checkAutoAttack())
			{
				AutoAttack::openAutoAttack();
			}
			else
			{
				AutoAttack::closeAutoAttack();
			}
		}
		else
		{
			if (m_pCurItem==NULL)
			{
				m_pCurItem=node;
			}		

			if ( m_iCurTag==tag)
			{
				if (m_pCurItem)
				{
					m_pCurItem->unselected();
				}
				closeMenu();
			}
			else
			{
				if (m_pCurItem)
				{
					m_pCurItem->unselected();
				}			
				node->selected();
				openMenu(tag);
				if (tag==TopButton::activity)
				{
					IconTipsData::m_bClickActivity = true;
					onCheckActivityEffect();
				}
				m_iCurTag=tag;
				m_pCurItem=node;
			}
		}
	}
}

void TopActiviy::openMenu( int tag )
{
	if (m_pMenu)
	{
		removeChild(m_pMenu);
		m_pMenu=NULL;
	}
	m_pMenu=TopActiviyMenu::create();
	m_pMenu->setMenuType(tag);
	m_pMenu->setAnchorPoint(ccp(0.5,0.5));
	m_pMenu->setPosition(ccp(SystemData::getLayoutValue("topactivity_bkg_pos.x")-m_pMenu->getContentSize().width,SystemData::getLayoutValue("topactivity_bkg_pos.y")-m_pMenu->getContentSize().height));
	if (m_pMenu->geticonCnt()<=2 && tag==TopButton::challenge)
	{
		m_pMenu->setPositionX(m_pMenu->getPositionX()-150);
	}
	addChild(m_pMenu);
}

void TopActiviy::closeMenu()
{
	if (m_pMenu)
	{
		if (m_pCurItem)
		{
			m_pCurItem->unselected();
			if (m_pEffect)
			{
				removeChild(m_pEffect);
				m_pEffect=NULL;
			}
		}
		m_iCurTag=-1;
		m_pMenu->closeself();	
		m_pMenu = NULL;
	}
}

void TopActiviy::closeMenuInstant()
{
	if (m_pMenu)
	{
		if (m_pCurItem)
		{
			m_pCurItem->unselected();
			if (m_pEffect)
			{
				removeChild(m_pEffect);
				m_pEffect=NULL;
			}
		}
		m_iCurTag=-1;
		m_pMenu->removeFromParentAndCleanup(true);
		m_pMenu = NULL;
	}
}

void TopActiviy::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::UI_OPEN)
	{
		if (source == "MiniMapLayer")
		{
			moveLeft();
		}
	}
	else if (eventName == CPEventName::UI_CLOSE)
	{
		if (source == "MiniMapLayer")
		{
			moveRight();
		}
	}
	else if (eventName == CPEventName::UI_CHANGE)
	{
		if (source == "TargetPanel")
		{
			const std::string &operation = CPEventHelper::getEventStringData(CPEventData::VALUE_1);
			if (operation=="up")
			{
				moveUp();
			}
			else if (operation=="down")
			{
				moveDown();
			}
		}
		else if (source == "AutoAttack")
		{
			int i = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
			if (i==0 )
			{
				CCSprite* pNormal = SystemData::getSpriteByPlist("topauto_attack");
				CCSprite* pSelect = SystemData::getSpriteByPlist("topauto_attack.sel");
				m_AutoBtn->setNormalImage(pNormal);
				m_AutoBtn->setSelectedImage(pSelect);
			}
			else if (i==1 )
			{
				CCSprite* pNormal = SystemData::getSpriteByPlist("topstop_attack");
				CCSprite* pSelect = SystemData::getSpriteByPlist("topstop_attack.sel");
				m_AutoBtn->setNormalImage(pNormal);
				m_AutoBtn->setSelectedImage(pSelect);
			}
		}
		else if (source == "HandleMessageHideActivityListNotify")
		{
			if (!GuideHelper::canOpenFunction(WorldDefination::kua_fu_pai_hang_bang))
				combinedrank->setVisible(false);
			else
				combinedrank->setVisible(true);
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageSyncActivityBossStateNotify" )
		{
			IconTipsData::m_bClickActivity=false;
			onCheckActivityEffect();
		}
	}
	else if (eventName == CPEventName::LGC_TIMER)
	{
		if (source == "TimeManager")
		{
			onCheckWelfareEffect();
		}
	}
	else if (eventName == CPEventName::MSG_DATA_READY)
	{
		const std::string &source = CPEventHelper::getEventSource();
		if (source == "ScriptPatchManager")
		{
			int nScriptId = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
			// 20417 is the script id for XingYunDaZhuanPan, see ActivityCfgVer for detail
			if (nScriptId == 20417)
			{
				ScriptPatchManager::instance()->UpdateLastFetchTime(nScriptId);
				ScriptPatchManager::instance()->EnableScript(nScriptId);
				TopActiviy::doOpenWelfareBox(f_xingyundazhuanpan);
			}
			// Uncomment these lines if need general handling
			// if (tag >= h_kaifuhuodong && tag <= h_huodonghuikui)
			// {
			// 	ScriptPatchManager::instance()->UpdateLastFetchTime(tag);
			// 	ScriptPatchManager::instance()->EnableScript(tag);
			// 	TopActiviy::doOpenActivityBox(tag);
			// }
			// else if (tag >= f_shouchonglibao && tag <= f_xingyundazhuanpan)
			// {
			// 	ScriptPatchManager::instance()->UpdateLastFetchTime(tag);
			// 	ScriptPatchManager::instance()->EnableScript(tag);
			// 	TopActiviy::doOpenWelfareBox(tag);
			// }
		}
	}
}

void TopActiviy::onCheckActivityEffect()
{	
	if (mMenu && mMenu->getChildByTag(TopButton::activity))
	{
		CCNode* pItem = (CCNode*)mMenu->getChildByTag(TopButton::activity);
		if (IconTipsData::m_iDoingEventid!=0 )
		{
			int visicon = 0;
			LuaData::getProp("gdEventData",IconTipsData::m_iDoingEventid,"visicon",visicon);
			if (visicon!=1)
			{
				if (!pItem->getChildByTag(effect_enum) && !IconTipsData::m_bClickActivity)
				{
					EffectSprite* pSprite = EffectSprite::create(Effect::effect_activityopen);
					pSprite->setTag(effect_enum);
					pSprite->setPosition(ccp(pItem->getContentSize().width/2,pItem->getContentSize().height/2));
					pItem->addChild(pSprite);
					return;
				}
			}
		}

		if (pItem->getChildByTag(effect_enum) && IconTipsData::m_bClickActivity)
		{
			pItem->removeChildByTag(effect_enum);
		}
	}
}

void TopActiviy::onCheckIsQuickPlayEffect()
{
	if (mMenu && mMenu->getChildByTag(TopButton::help))
	{
		CCNode* pItem = (CCNode*)mMenu->getChildByTag(TopButton::help);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		if(CHANNELHELPER->isQuickPlay())
		{
			if (!pItem->getChildByTag(effect_enum) && !IconTipsData::m_bClickActivity)
			{
				EffectSprite* pSprite = EffectSprite::create(Effect::effect_activityopen);
				pSprite->setTag(effect_enum);
				pSprite->setPosition(ccp(pItem->getContentSize().width/2,pItem->getContentSize().height/2));
				pItem->addChild(pSprite);
				return;
			}
		}
		if (pItem->getChildByTag(effect_enum) && !CHANNELHELPER->isQuickPlay())
		{
			pItem->removeChildByTag(effect_enum);
		}
#endif
	}
}

void TopActiviy::onCheckWelfareEffect()
{
	checkWelfareEffect();
	if (mMenu && mMenu->getChildByTag(TopButton::welfare))
	{
		CCNode* pItem = (CCNode*)mMenu->getChildByTag(TopButton::welfare);

		if (!pItem->getChildByTag(effect_enum) && IconTipsData::needShowWelfare())
		{
			EffectSprite* pSprite = EffectSprite::create(Effect::effect_activityopen);
			pSprite->setTag(effect_enum);
			pSprite->setPosition(ccp(pItem->getContentSize().width/2,pItem->getContentSize().height/2));
			pItem->addChild(pSprite);
			return;
		}

		if (pItem->getChildByTag(effect_enum) && !IconTipsData::needShowWelfare())
		{
			pItem->removeChildByTag(effect_enum);
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------//
TopActiviyMenu::TopActiviyMenu():
	m_pBkg(NULL),
	m_iCurType(0),
	m_pMainMenu(NULL),
	m_iiconCnt(0)
{
	for (int i=0;i<MaxTopIcon;i++)
	{
		topstr[i]="";
		toptag[i]=-1;
	}
}

TopActiviyMenu::~TopActiviyMenu()
{
}

bool TopActiviyMenu::init()
{
	//initUI();
	//this->setTouchPriority(-127);
	setAnchorPoint(ccp(0.5,0.5));
	return true;
}

void TopActiviyMenu::setMenuType( int tag )
{
	m_iCurType=tag;
	initUI();
}

void TopActiviyMenu::initUI()
{
	int size=0;
	switch (m_iCurType)
	{
	case TopButton::activity:
		{
			toptag[0]=h_kaifuhuodong;
			toptag[1]=h_touzijihua;
			toptag[2]=h_caishenchuangguan;
			toptag[3]=h_xunbao;
			toptag[7]=h_libaofengshang;
			toptag[5]=h_meirihuoyue;
			toptag[6]=h_jubaopen;
			toptag[4]=h_huodonghuikui;
			

			size=SystemData::getLayoutValue("top_huodong_size");

			for (int i = 0; i<size; i++)
			{
				CCString* p = CCString::createWithFormat(SystemData::getLayoutString("top_huodong_").c_str(),i+1);
				topstr[i] = SystemData::getLayoutString(p->getCString());
			}
			break;
		}
	case TopButton::welfare:
		{
			toptag[0]=f_shouchonglibao;
			toptag[1]=f_meirishouchong;
			toptag[2]=f_leijichongzhi;
			toptag[3]=f_nyuelibao;
			toptag[4]=f_xianshidalibao;
			toptag[5]=f_zaixianjiangli;
			toptag[6]=f_meirigongzi;
			toptag[7]=f_xiaofeichoujiang;
			toptag[8]=f_meiridenglu;
			toptag[9]=f_danbichongzhi;
			toptag[10]=f_shangxianguanzhu;
			toptag[11]=f_hefuhuikui;
			toptag[12]=f_xingyundazhuanpan;

			size=SystemData::getLayoutValue("top_fuli_size");

			for (int i = 0; i<size; i++)
			{
				CCString* p = CCString::createWithFormat(SystemData::getLayoutString("top_fuli_").c_str(),i+1);
				topstr[i] = SystemData::getLayoutString(p->getCString());
			}
			break;
		}
	case TopButton::help:
		{
			toptag[0]=b_kuaisubaitan;
			toptag[1]=b_suishenshangdian;
			toptag[2]=b_xiaozhushou;
			toptag[3]=b_xitongshezhi;

			size=SystemData::getLayoutValue("top_bangzhu_size");
			const int platformID = CPPlatformMnger.getIntData(CPPlatformData::PLATFORM_ID);
			int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
			if (platformID == PlatformID::android && channel_id == ChannelID::tencent_msdk)
			{
				toptag[4]=b_lianxigm;
				toptag[5]=b_youxiluntan;
				size = SystemData::getLayoutValue("top_bangzhu_size_android");
			}else if (platformID == PlatformID::ios)
			{
				toptag[4]=b_lianxigm;
				toptag[5]=b_lianxiwomen;
				size = SystemData::getLayoutValue("top_bangzhu_size_ios");
			}else
			{
				toptag[4]=b_lianxigm;
				size = SystemData::getLayoutValue("top_bangzhu_size_local");
			}
			if (channel_id != ChannelID::ios_pp && platformID == PlatformID::ios)
			{
				size -= 1;
			}
			for (int i = 0; i<size; i++)
			{
				CCString* p = CCString::createWithFormat(SystemData::getLayoutString("top_bangzhu_").c_str(),i+1);
				std::string pStr = SystemData::getLayoutString(p->getCString());
				if (pStr == "")
				{
					if (platformID == PlatformID::android)
					{
						p = CCString::createWithFormat(SystemData::getLayoutString("top_bangzhu_android").c_str(),i+1);
					}else if (platformID == PlatformID::ios)
					{
						p = CCString::createWithFormat(SystemData::getLayoutString("top_bangzhu_ios").c_str(),i+1);
					}else
					{
						p = CCString::createWithFormat(SystemData::getLayoutString("top_bangzhu_android").c_str(),i+1);
					}
				}
				if (p)
				{
					topstr[i] = SystemData::getLayoutString(p->getCString());
				}
			}
			break;
		}
	case TopButton::challenge:
		{
			toptag[0]=h_kaifujingji;
			toptag[1]=h_zhanlijingji;
			toptag[2]=h_chengbatianxia;
			toptag[3]=h_hanghuizhengduozhan;
			toptag[4]=h_yongshijingjichang;
			toptag[5]=h_qunxiongzhulu;
			toptag[6]=h_paihangbang;

			size=SystemData::getLayoutValue("top_jingji_size");

			for (int i = 0; i<size; i++)
			{
				CCString* p = CCString::createWithFormat(SystemData::getLayoutString("top_jingji_").c_str(),i+1);
				topstr[i] = SystemData::getLayoutString(p->getCString());
			}
			break;
		}
	default:
		break;
	}

	//
	if (m_iCurType == TopButton::welfare)
	{
		removeIcon(f_xianshidalibao, size);
		size--;

		removeIcon(f_nyuelibao, size);
		size--;

		removeIcon(f_xiaofeichoujiang, size);
		size--;

		removeIcon(f_shangxianguanzhu, size);
		size--;

		removeIcon(f_hefuhuikui, size);
		size--;

//		removeIcon(f_xingyundazhuanpan, size);
//		size--;

		if (!GuideHelper::canOpenFunction(FunctionName::MEI_RI_GONG_ZI))
		{
			removeIcon(f_meirigongzi, size);
			size--;
		}

		if ((HeroData::getProp(Entity::attr_gfmrdllb_times) + 1) > SystemData::getLayoutValue("meiridenglu_day"))
		{
			removeIcon(f_meiridenglu,size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(WorldDefination::shou_chong_li_bao))
		{
			removeIcon(f_shouchonglibao, size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(WorldDefination::mei_ri_shou_chong))
		{
			removeIcon(f_meirishouchong, size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(WorldDefination::lei_ji_chong_zhi))
		{
			removeIcon(f_leijichongzhi, size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(WorldDefination::zai_xian_jiang_li))
		{
			removeIcon(f_zaixianjiangli, size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(WorldDefination::dan_bi_chong_zhi))
		{
			removeIcon(f_danbichongzhi, size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(WorldDefination::xing_yun_zhuan_pan))
		{
			removeIcon(f_xingyundazhuanpan, size);
			size--;
		}
	}
	else if (m_iCurType == TopButton::activity) 
	{
		removeIcon(h_touzijihua,size);
		size--;
		
		if (!GuideHelper::canOpenFunction(WorldDefination::kai_fu_huo_dong))
		{
			removeIcon(h_kaifuhuodong,size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(WorldDefination::li_bao_feng_shang))
		{
			removeIcon(h_libaofengshang,size);
			size--;
		}

// 		if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ios_appstore)
// 		{
// 			removeIcon(h_libaofengshang,size);//appstore need to remove libaofengshang at the moment
// 			size--;
// 		}

		if (!GuideHelper::canOpenFunction(WorldDefination::jv_bao_pen))
		{
			removeIcon(h_jubaopen,size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(FunctionName::CAI_SHEN_CHUANG_GUAN))
		{
			removeIcon(h_caishenchuangguan,size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(FunctionName::XUN_BAO))
		{
			removeIcon(h_xunbao,size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(WorldDefination::he_fu_hui_kui))
		{
			removeIcon(h_huodonghuikui, size);
			size--;
		}

		//????????????????3?????
		int visicon = 0;
		if (IconTipsData::m_iOverEventid!=0 && LuaData::getProp("gdEventData",IconTipsData::m_iOverEventid,"visicon",visicon))
		{
			if (visicon!=1)
			{
				toptag[size]=IconTipsData::m_iOverEventid;
				LuaData::getProp("gdEventData",IconTipsData::m_iOverEventid,"icon",topstr[size]);
				size++;
			}
		}

		if (IconTipsData::m_iDoingEventid!=0 && LuaData::getProp("gdEventData",IconTipsData::m_iDoingEventid,"visicon",visicon))
		{
			if (visicon!=1)
			{
				toptag[size]=IconTipsData::m_iDoingEventid;
				LuaData::getProp("gdEventData",IconTipsData::m_iDoingEventid,"icon",topstr[size]);
				size++;
			}
		}

		if (IconTipsData::m_iWillEventid!=0 && LuaData::getProp("gdEventData",IconTipsData::m_iWillEventid,"visicon",visicon))
		{
			if (visicon!=1)
			{
				toptag[size]=IconTipsData::m_iWillEventid;
				LuaData::getProp("gdEventData",IconTipsData::m_iWillEventid,"icon",topstr[size]);
				size++;
			}
		}

	}
	else if (m_iCurType == TopButton::challenge)
	{
		if (!GuideHelper::canOpenFunction(WorldDefination::kai_fu_jing_ji))
		{
			removeIcon(h_kaifujingji,size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(FunctionName::PAI_HANG_BANG))
		{
			removeIcon(h_paihangbang,size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(FunctionName::HANG_HUI_ZHENG_DUO_ZHAN))
		{
			removeIcon(h_hanghuizhengduozhan,size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(FunctionName::ZHAN_SHEN_ZHENG_BA))
		{
			removeIcon(h_chengbatianxia,size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(FunctionName::ZHAN_LI_JING_JI))
		{
			removeIcon(h_zhanlijingji,size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(FunctionName::YONG_SHI_JIAO_DOU_CHANG))
		{
			removeIcon(h_yongshijingjichang,size);
			size--;
		}

		if (!GuideHelper::canOpenFunction(FunctionName::WU_YI_ZHAN_CHANG))
		{
			removeIcon(h_qunxiongzhulu,size);
			size--;
		}
	}
	
	//
	int x;
	if (size>=4)
	{
		x=0;
	}
	else
	{
		x=4-size;
	}
	int y=(size-1)/4-1;

	m_iiconCnt=size;

	int item_width=SystemData::getLayoutValue("topactivity_item_size.w"); 
	int item_height=SystemData::getLayoutValue("topactivity_item_size.h");

	m_pBkg=SystemData::getScale9SpriteByPlist("topactivity_bkg",SystemData::getLayoutValue("topactivity_bkg_size.w")-x*item_width+10,SystemData::getLayoutValue("topactivity_bkg_size.h")+y*item_height+10);
	m_pBkg->setPosition(CCPointZero);
	m_pBkg->setAnchorPoint(CCPointZero);
	addChild(m_pBkg);

	this->setContentSize(CCSizeMake(m_pBkg->getContentSize().width,m_pBkg->getContentSize().height));

	m_pMainMenu=GeneralMenu::create();
	m_pMainMenu->setAnchorPoint(CCPointZero);
	m_pMainMenu->setPosition(CCPointZero);
	m_pBkg->addChild(m_pMainMenu);

	bool flagover = false;
	bool flagbegin = false;
	bool flagwill = false;

#ifdef APPSTORE_VERSION
	if (m_iCurType == TopButton::activity)
	{
		string topstrtmp;
		string topstrtmp1;
		int toptagtmp = 0;
		int toptagtmp1 = 0;
		int itmp = 0;
		for (int i=0;i<size;i++)
		{
			if (topstr[i] == "topicon_libaofengshang")
			{
				topstrtmp = topstr[i];
				toptagtmp = toptag[i];
				itmp = i;
				break;
			}
		}
		topstrtmp1 = topstr[size-1];
		toptagtmp1 = toptag[size-1];
		topstr[size-1] = topstrtmp;
		toptag[size-1] = toptagtmp;
		topstr[itmp] = topstrtmp1;
		toptag[itmp] = toptagtmp1;
	}
#endif	
	for (int i=1;i<=size;i++)
	{
		CCMenuItemImage* pItem=SystemData::getMenuItemImageByPlist(topstr[i-1]);
		if (pItem)
		{
			int num = i;
			pItem->setAnchorPoint(CCPointZero);
			pItem->setPosition(ccp(8+(i-1)%4*item_width,10+((size-1)/4-(i-1)/4)*item_height));
			if (topstr[i-1] == "topicon_libaofengshang")
			{
				pItem->setScale(0.8f);
				pItem->setPosition(ccp(pItem->getPositionX()+pItem->getContentSize().width*0.1f, pItem->getPositionY()+pItem->getContentSize().height*0.1f));
			}
			
			pItem->setTag(toptag[i-1]);
			pItem->setTarget(this,menu_selector(TopActiviyMenu::onClick));
			m_pMainMenu->addChild(pItem);
			CCPoint pos=ccp(pItem->getPositionX()+pItem->getContentSize().width/2,pItem->getPositionY()+pItem->getContentSize().height/2);
			if (m_iCurType==TopButton::activity && pItem)
			{
				if(IconTipsData::m_iOverEventid==toptag[i-1] && !flagover)
				{
					CCSprite* p=SystemData::getSpriteByPlist("topactivity_over_sprite");
					p->setPosition(pos);
					m_pMainMenu->addChild(p);
					flagover = true;
				}
				else if(IconTipsData::m_iDoingEventid==toptag[i-1] && !flagbegin) 
				{
					CCSprite* p=SystemData::getSpriteByPlist("topactivity_doing_sprite");
					p->setPosition(pos);
					m_pMainMenu->addChild(p);

					EffectSprite* m_pEffect=EffectSprite::create(Effect::effect_activityopen);
					m_pEffect->setAnchorPoint(CCPointZero);
					m_pEffect->setPosition(pItem->getPosition());
					m_pMainMenu->addChild(m_pEffect);
					flagbegin = true;
				}
				else if(IconTipsData::m_iWillEventid==toptag[i-1] && !flagwill)
				{
					CCSprite* p=SystemData::getSpriteByPlist("topactivity_will_sprite");
					p->setPosition(pos);
					m_pMainMenu->addChild(p);
					flagwill = true;
				}
			}
			else if (m_iCurType==TopButton::welfare && pItem)
			{
				if (checkShowWelfareEffect(toptag[i-1]))
				{
					EffectSprite* m_pEffect=EffectSprite::create(Effect::effect_activityopen);
					m_pEffect->setAnchorPoint(CCPointZero);
					m_pEffect->setPosition(pItem->getPosition());
					m_pMainMenu->addChild(m_pEffect);
				}
			}
			else if (m_iCurType==TopButton::help && pItem->getTag() == b_xitongshezhi)
			{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				if(CHANNELHELPER->isQuickPlay())
				{
					EffectSprite* m_pEffect=EffectSprite::create(Effect::effect_activityopen);
					m_pEffect->setAnchorPoint(CCPointZero);
					m_pEffect->setPosition(pItem->getPosition());
					m_pMainMenu->addChild(m_pEffect);
				}
#endif
			}
		}
	}
}
void TopActiviyMenu::onClick( CCObject* pSender )
{
	CCNode* pNode=dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag=pNode->getTag();
		switch (m_iCurType)
		{
		case TopButton::challenge:
			{	
				switch (tag)
				{
				case h_kaifujingji:
					CPEventHelper::openPanel("TopSportsPanel",TopSportsPanel::Panel_OpenSports+1,0,0,1);
					break;
				case h_zhanlijingji:
					CPEventHelper::openPanel("ArenaPanel");
					break;
				case h_chengbatianxia:
					CPEventHelper::openPanel("MainPanel",TAG_Activity_Panel, ActivityView::time_activity, EvtData::evt_cbtx, 1);
					break;
				case h_hanghuizhengduozhan:
					CPEventHelper::openPanel("MainPanel",TAG_Activity_Panel, ActivityView::time_activity, EvtData::evt_hhzdz, 1);
					break;
				case h_yongshijingjichang:
					CPEventHelper::openPanel("MainPanel",TAG_Activity_Panel, ActivityView::time_activity, EvtData::evt_ysjdc, 1);
					break;
				case h_qunxiongzhulu:
					CPEventHelper::openPanel("MainPanel",TAG_Activity_Panel, ActivityView::time_activity, EvtData::evt_qxzl, 1);
					break;
				case h_paihangbang:
					CPEventHelper::openPanel("RankPanel",0,0,0,1);
					break;
				default:
					break;
				}
				break;
			}
		case TopButton::activity:
			{
				// Uncomment these lines if you need to fetch script for activities
				// if (ScriptPatchManager::instance()->ScriptNeedUpdate(tag))
				// {
				// 	ScriptPatchManager::instance()->UpdateScript(tag);
				// }
				// else
				// {
				// 	TopActiviy::doOpenActivityBox(tag);
				// }
				//
				TopActiviy::doOpenActivityBox(tag);
				break;
			}
		case TopButton::welfare:
			{
				if (tag == f_xingyundazhuanpan)
				{
					// 20417 is the script id for XingYunDaZhuanPan, see ActivityCfgVer for detail
					if (ScriptPatchManager::instance()->ScriptNeedUpdate(20417))
					{
						ScriptPatchManager::instance()->UpdateScript(20417);
					}
					else
					{
						TopActiviy::doOpenWelfareBox(tag);
					}
				}
				else
				{
					TopActiviy::doOpenWelfareBox(tag);
				}		
				break;
			}
		case TopButton::help:
			{
				switch (tag)
				{
				case b_xiaozhushou:
					CPEventHelper::openPanel("TopHelpPanel");
					break;
				case b_xitongshezhi:
					//CPEventHelper::openPanel("MainPanel",TAG_Setting_Panel,0,0,1);
					CPEventHelper::openPanel("SystemSetting");
					break;
				case b_kuaisubaitan:
					openBooth();
					break;
				case b_suishenshangdian:
					CPEventHelper::openPanel("NpcShopComp",TAG_NPCSHOP_CARRY,0,0,0);
					break;
				case b_lianxiwomen:
					CPEventHelper::openPanel("ContactUs");
					break;
				case b_lianxigm:
					{
						int channel_id = CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID);
						if (channel_id == ChannelID::tencent_msdk)
						{
							CPPlatform->operate(PlatformOpID::lianxiGM);
						}
						else if (CPPlatformMnger.getIntData(CPPlatformData::PLATFORM_ID) == PlatformID::ios)
						{
							//ios web customer service
                            CPPlatform->operate(PlatformOpID::lianxiGM);
						}
						else
						{
							CPEventHelper::openPanel("ContactUs");
						}
					}
					break;
				case b_youxiluntan:
					CPPlatform->operate(PlatformOpID::youxiluntan);
					break;
				default:
					break;
				}			
				break;
			}
		default:
			{
				CCLog(">>>Error, TopActiviy::onClick, undefined tag %d.", m_iCurType);
				break;
			}
		}
	}

	TopActiviy* ui = dynamic_cast<TopActiviy*>(getParent());
	if (ui)
	{
		ui->closeMenuInstant();
	}
}

void TopActiviy::doOpenActivityBox(int tag)
{
	switch (tag)
	{
	case h_kaifuhuodong:
		CPEventHelper::openPanel("OpenActivityPanel");
		break;
	case h_touzijihua:
		CPEventHelper::openPanel("TopActivityPanel",TopActivityPanel::Panel_InvestPlan+1,0,0,1);
		break;
	case h_zhanshenshice:
		CPEventHelper::openPanel("TopActivityPanel",TopActivityPanel::Panel_InvestPlan+1,0,0,1);
		break;
	case h_caishenchuangguan:
		CPEventHelper::openPanel("EmigratedPanel");
		break;
	case h_xunbao:
		CPEventHelper::openPanel("TreasureHuntPanel");
		break;
	case h_libaofengshang:
		CPEventHelper::openPanel("GiftConversionPanel");
		break;
	case h_meirihuoyue:
		CPEventHelper::openPanel("EveryDayActivePanel");
		break;
	case h_jubaopen:
		CPEventHelper::openPanel("CPTips", "JuBaoPenPanel", 0, 0, 0);
		break;
	case h_huodonghuikui:
		CPEventHelper::openPanel("CombinedServer");
		break;
	default:
		CPEventHelper::openPanel("MainPanel", TAG_Activity_Panel, ActivityView::time_activity, tag, 0);
		break;
	}
}

void TopActiviy::doOpenWelfareBox(int tag)
{
	switch (tag)
	{
	case f_shouchonglibao:
		CPEventHelper::openPanel("TopWelfarePanel",TopWelfarePanel::Panel_FirstCharge+1,0,0,1);
		break;
	case f_meirishouchong:
		CPEventHelper::openPanel("TopWelfarePanel",TopWelfarePanel::Panel_EveryDayFirstCharge+1,0,0,1);
		break;
	case f_leijichongzhi:
		CPEventHelper::openPanel("TopWelfarePanel",TopWelfarePanel::Panel_AddUpCharge+1,0,0,1);
		break;
	case f_nyuelibao:
		CPEventHelper::openPanel("TopWelfarePanel",TopWelfarePanel::Panel_MonthGift+1,0,0,1);
		break;
	case f_xianshidalibao:
		CPEventHelper::openPanel("TopWelfarePanel",TopWelfarePanel::Panel_TimeLimitGift+1,0,0,1);
		break;
	case f_zaixianjiangli:
		CPEventHelper::openPanel("TopWelfarePanel",TopWelfarePanel::Panel_OnlineGift+1,0,0,1);
		break;
	case f_meirigongzi:
		CPEventHelper::openPanel("EveryDaySalaryPanel");
		break;
	case f_xiaofeichoujiang:
		CPEventHelper::openPanel("TopWelfarePanel",TopWelfarePanel::Panel_ConsumeDraw+1,0,0,1);
		break;
	case f_meiridenglu:
		CPEventHelper::openPanel("LoginRewardPanel");
		break;
	case f_danbichongzhi:
		CPEventHelper::openPanel("TopWelfarePanel", TopWelfarePanel::Panel_SingleRecharge + 1, 0, 0, 1);
		break;
	case f_shangxianguanzhu:
		CPEventHelper::openPanel("LaunchedFocus");
		break;
	case f_hefuhuikui:
		break;
	case f_xingyundazhuanpan:
		CPEventHelper::openPanel("LuckyCircle");
		break;
	default:
		break;
	}
}


bool TopActiviyMenu::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos=pTouch->getLocation();
	CCPoint toppos=ccp(395,414);
	toppos=convertToNodeSpace(toppos);
	CCRect rect=CCRectMake(toppos.x,toppos.y,270,67);
	if (rect.containsPoint( this->convertToNodeSpace(pos)))
	{
		return false;
	}
	return true;
}

void TopActiviyMenu::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void TopActiviyMenu::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos=pTouch->getLocation();
	CCRect rect=CCRectMake(m_pBkg->getPositionX(),m_pBkg->getPositionY(),m_pBkg->getContentSize().width,m_pBkg->getContentSize().height);
	if (!rect.containsPoint( this->convertToNodeSpace(pos)))
	{
		runAction(CPNodeHelper::getScaleToSmall());	
		((TopActiviy*)(this->getParent()))->closeMenu();
		//this->removeFromParent();
	}
}

void TopActiviyMenu::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}

void TopActiviyMenu::onEnter()
{
	BasePanel::onEnter();
	setScale(0.0f);
	runAction(CPNodeHelper::getScaleToBig());	
}

void TopActiviyMenu::onExit()
{
	BasePanel::onExit();

}

void TopActiviyMenu::closeself()
{
	CCShow *sh = CCShow::create();
	CCAction* ac=CPNodeHelper::getScaleToSmall();
	CCAction* rm=CCActionInstantRemoveFromParentEx::create(this);
	this->runAction(CCSequence::create(sh, ac,rm,NULL));
}

void TopActiviyMenu::openBooth()
{
	int rvt=GameData::s_user->getUserPetData()->canBooth();
	if (rvt==Error::Success)
	{
		GameData::s_user->m_pMainRole->m_bMyBooth = true;
		CPEventHelper::openPanel("MainPanel",TAG_Booth_Panel,Booth_Sell,0,0);
	}
	else
	{
		CPEventHelper::uiNotify("","",rvt);
	}
}

int TopActiviyMenu::geticonCnt()
{
	return m_iiconCnt;
}

void TopActiviyMenu::removeIcon( int enumid ,int size)
{
	int n=0;
	for (int i=0;i<size;i++)
	{
		if (toptag[i]==enumid)
		{
			n=i;
			break;
		}
	}
	int temp=toptag[n];
	for (int i=n;i<size-1;i++)
	{
		toptag[i]=toptag[i+1];
	}
	toptag[size-1]=temp;

	std::string tempstr=topstr[n];
	for (int i=n;i<size-1;i++)
	{
		topstr[i]=topstr[i+1];
	}
	topstr[size-1]=tempstr;
}

bool TopActiviyMenu::checkShowWelfareEffect( int tag )
{
	return IconTipsData::needShowSubWelfare(tag - f_begin);
}

/////////////////////////////////////////////////???????/////////////////////////////////
ContactUs::ContactUs()
{

}

ContactUs::~ContactUs()
{

}

bool ContactUs::init()
{
	if (!PartPanel::init())
	{
		return false;
	}
	initUI();
	if (CPPlatformMnger.getIntData(CPPlatformData::PLATFORM_ID) == PlatformID::ios)
	{
		if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ios_pp)
		{
			initUsDesc();
		}
	}else
	{
		initUsDescII();
	}
	initButton();
	return true;
}

void ContactUs::initUI()
{
	setContentSize(CCSizeMake(m_nWidth,m_nHeight));
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pborder=SystemData::getSpriteByPlist("ui_float_menu_border");
	pborder->setPosition(ccp(winsize.width/2,winsize.height/2));
	addChild(pborder);

	m_nWidth=pborder->getContentSize().width;
	m_nHeight=pborder->getContentSize().height;
	addCover(ccp(winsize.width/2-m_nWidth/2,winsize.height/2-m_nHeight/2));

	std::string title;
	title = LayoutData::getString(CPModuleName::ACTIVITY,"contact_us_title");
	CCLabelTTF* pLabel=CCLabelTTF::create(title.c_str(),"??????",20);
	pLabel->setColor(ccYELLOW);
	pLabel->setPosition(ccp(600,438));
	addChild(pLabel);

	
}

void ContactUs::initUsDesc()
{
	std::string str1 = LayoutData::getString(CPModuleName::ACTIVITY,"contact_us_wordsQQ");
	std::string str2 = LayoutData::getString(CPModuleName::ACTIVITY,"contact_us_wordsTel");
	std::string str3 = LayoutData::getString(CPModuleName::ACTIVITY,"contact_us_wordsMail");
	CCLabelTTF* pLabel1=CCLabelTTF::create(str1.c_str(),"??????",20);
	CCLabelTTF* pLabel2=CCLabelTTF::create(str2.c_str(),"??????",20);
	CCLabelTTF* pLabel3=CCLabelTTF::create(str3.c_str(),"??????",20);
	pLabel1->setAnchorPoint(ccp(0,0.5));
	pLabel2->setAnchorPoint(ccp(0,0.5));
	pLabel3->setAnchorPoint(ccp(0,0.5));
	pLabel1->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY,"wordsQQ"));
	addChild(pLabel1);
	pLabel2->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY,"wordsTel"));
	addChild(pLabel2);
	pLabel3->setPosition(LayoutData::getPoint(CPModuleName::ACTIVITY,"wordsMail"));
	addChild(pLabel3);
}

void ContactUs::initButton()
{
	GeneralMenu* menu = GeneralMenu::create();
	if (menu)
	{
		menu->setAnchorPoint(CCPointZero);
	//	menu->setPosition(CCPointZero);
		menu->setPosition(ccp(200,70));
		addChild(menu);
	}
	CCMenuItemImage* pclose=LayoutData::getMenuItemImg(CPModuleName::ACTIVITY,"contactusTuichu");
	pclose->setTarget(this,menu_selector(ContactUs::close));
	menu->addChild(pclose);

	CCMenuItemTextImage *pPutOff =  SystemData::getMenuItemTextImage("ui.button",SystemData::getLayoutString("panel_QueDing_label").c_str(),"??????",15,ccWHITE);
	pPutOff->setTarget(this,menu_selector(ContactUs::close));
	pPutOff->setPosition(ccp(400,128));
	menu->addChild(pPutOff);
}

void ContactUs::close( CCObject* pSender )
{
	this->removeFromParent();
}

void ContactUs::initUsDescII()
{
	// ??????1 - ?????????
	const char* contactText1 = "QQ_676545075";
	CCLabelTTF* pLabel1 = CCLabelTTF::create(contactText1, "??????", 20);
	pLabel1->setAnchorPoint(ccp(0,0.5));
	pLabel1->setPosition(ccp(520, 372));
	pLabel1->setColor(ccc3(138, 43, 226));  // ?????
	addChild(pLabel1);
	
	// ??????2 - ??????????
	const char* contactText2 = "VX_Tuoking_223";
	CCLabelTTF* pLabel2 = CCLabelTTF::create(contactText2, "??????", 20);
	pLabel2->setAnchorPoint(ccp(0,0.5));
	pLabel2->setPosition(ccp(520, 298));
	pLabel2->setColor(ccc3(255, 0, 0));  // ???
	addChild(pLabel2);
}

