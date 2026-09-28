#include "SoulStonePanel.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/OtherRole.h"
#include "network/HandleMessage.h"
#include "MsgItem.h"
#include "userdata/netdata/NetItem.h"

#include "userdata/netdata/HeroModel.h"
#include "event/EventProtocol.h"
#include "userdata/netdata/HeroModel.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "CharacterPanel.h"
#include "userdata/luadata/LuaData.h"
#include "ext/GeneralMenu.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/ForgingMainPanel.h"
#include "scene/panel/MainPanel.h"
#include "event/CPEventHelper.h"
#include "scene/panel/guide/GuideHelper.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "ext/CCActionDestroy.h"
#include "event/CPEventDispatcher.h"

CCPoint EquipPos1[Equip_Total]=
{
	ccp(49, 397),	//项链
	ccp(49, 327),	//武器
	ccp(49, 258),	//幻武
	ccp(49, 188),	//手镯
	ccp(49, 119),	//戒指
	ccp(49, 50),	//宝石
	ccp(126, 50),	//时装
	ccp(201, 50),	//翅膀
	ccp(280, 50),	//腰带
	ccp(356, 50),	//鞋子
	ccp(356, 119),	//戒指2
	ccp(356, 188),	//手镯2
	ccp(356, 258),	//衣服
	ccp(356, 327),	//勋章
	ccp(356, 397),	//帽子
	ccp(280, 397),	//材料
	ccp(126, 397),	//足迹
	ccp(280, 119),	//元神
	ccp(-720, 155),	//法器
	ccp(-595, 155),	//斗笠
	ccp(-470, 155),	//肩铠
	ccp(-720, 72),	//护手
	ccp(-595, 72),	//法袍
	ccp(-470, 72)	//护腿
};

std::string EquipName1[Equip_Total]=
{
	"ui.rolepanel.equipname.necklace",
	"ui.rolepanel.equipname.weapon",
	"ui.rolepanel.equipname.huanwu",
	"ui.rolepanel.equipname.bracelet",
	"ui.rolepanel.equipname.ring",
	"ui.rolepanel.equipname.jewel",
	"ui.rolepanel.equipname.fashion",
	"ui.rolepanel.equipname.wing",
	"ui.rolepanel.equipname.belt",
	"ui.rolepanel.equipname.shoes",
	"ui.rolepanel.equipname.ring",
	"ui.rolepanel.equipname.bracelet",
	"ui.rolepanel.equipname.clothes",
	"ui.rolepanel.equipname.medal",
	"ui.rolepanel.equipname.helmet",
	"ui.rolepanel.equipname.stuff",
	"ui.rolepanel.equipname.foot",
	"ui.rolepanel.equipname.Yuanshen",
	"ui.rolepanel.equipname.Shenqi1",
	"ui.rolepanel.equipname.Shenqi2",
	"ui.rolepanel.equipname.Shenqi3",
	"ui.rolepanel.equipname.Shenqi4",
	"ui.rolepanel.equipname.Shenqi5",
	"ui.rolepanel.equipname.Shenqi6"

};
static CCRect turnRect;

const float DOUBLE_CLICK_TIME = 0.2f;
static const int ITEM_UNUSE_POS = -1000;

SoulStonePanel* SoulStonePanel::characterPanel = NULL;

SoulStonePanel::SoulStonePanel():
	m_pSprite(NULL),
	m_nPrePos(0),
	m_bIsSelf(true)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}


SoulStonePanel::~SoulStonePanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

SoulStonePanel* SoulStonePanel::create(bool isSelf)
{
	SoulStonePanel* characterPanel = new SoulStonePanel();
	if(characterPanel && characterPanel->init(isSelf))
	{
		characterPanel->autorelease();
		return characterPanel;
	}

	if (characterPanel)
	{
		delete characterPanel;
	}
	return NULL;
}

/// @brief 魂石面板初始化函数
/// @param isSelf 是否为自身角色（true:自身，false:其他角色）
/// @return 初始化是否成功
bool SoulStonePanel::init(bool isSelf)
{
	// 调用父类初始化
	if (!CCLayer::init())
		return false;
		
	// 设置是否为自身角色标志
	m_bIsSelf = isSelf;
	
	// 设置锚点和位置
	setAnchorPoint(CCPointZero);
	setPosition(CCPointZero);

	// 创建背景面板
	CCScale9Sprite *bkg = SystemData::getScale9SpriteByPlist("ui.bag.small_bkg", 390, 429);
	bkg->setAnchorPoint(CCPointZero);
	bkg->setContentSize(CCSizeMake(390, 429));
	bkg->setPosition(ccp(8, 8));
	addChild(bkg);

	// 创建菜单容器
	m_menu = GeneralMenu::create();
	m_menu->setPosition(CCPointZero);
	
	// 初始化装备槽位
	initEquipSlot();

	// 根据是否为自身角色获取不同的物品数据
	UserItems items;
	if (!m_bIsSelf)  // 其他角色
	{
		items = GameData::s_user->m_pOtherRole->m_pAllItemMap;
	}
	else  // 自身角色
	{
		items = GameData::s_user->getUserItemData()->userItems;
	}

	// 遍历所有物品，将符合条件的物品添加到面板
	for(std::map<short, UserItem*>::iterator it = items.begin(); it != items.end(); it++)
	{
		// 检查物品位置是否属于本面板，并排除特殊装备位置
		if (isPosInThisPanel(it->first) && 
			it->first != ItemPosition_Equip_Weapon_Two &&    // 排除副武器
			it->first != ItemPosition_Equip_Fashion &&       // 排除时装
			it->first != ItemPosition_Equip_Wings &&         // 排除翅膀
			it->first != ItemPosition_Equip_Foot &&         // 排除足迹
			it->first != ItemPosition_Equip_Material &&      // 排除法球
			it->first != ItemType_Equip_Yuanshen &&         // 排除元神
			it->first != ItemType_Equip_Shenqi1 &&           // 排除神器1
			it->first != ItemType_Equip_Shenqi2 &&         // 排除神器2
			it->first != ItemType_Equip_Shenqi3 &&  // 排除神器3
			it->first != ItemType_Equip_Shenqi4 &&  // 排除神器4
			it->first != ItemType_Equip_Shenqi5 &&  // 排除神器5
			it->first != ItemType_Equip_Shenqi6)     // 排除神器6
		{
			// 插入物品到对应位置
			insertItem(it->second, it->first);			
			// 记录前一个位置（用于界面初始化）
			m_nPrePos = -it->first - 1;
		}
	}

	// 添加菜单到面板
	addChild(m_menu);

	// 启用触摸
	setTouchEnabled(true);

	// 初始化界面（注释掉的选中精灵代码）
	// m_pSprite=SystemData::getSpriteByPlist("ui_soulstone_select"); 
	// addChild(m_pSprite);

	// 初始化界面显示
	initInterface(m_nPrePos);

	return true;
}

void SoulStonePanel::initInterface(int pos)
{
//	m_pSprite->setPosition(EquipPos1[pos]); 
	if (getChildByTag(TAG_MainSoulStone))
	{
		removeChildByTag(TAG_MainSoulStone);
	}
	SoulStoneMainPanel* pPanel=SoulStoneMainPanel::create(pos,m_bIsSelf);	
	pPanel->setTag(TAG_MainSoulStone);
	pPanel->setAnchorPoint(CCPointZero);
	pPanel->setPosition(CCPointZero);
	addChild(pPanel);
}


/**
 * 初始化装备槽位显示
 * 创建装备栏的槽位图标和名称标签，并设置相应的交互状态
 */
void SoulStonePanel::initEquipSlot()
{
    // 清空现有菜单子项（带渐隐动画效果）
    // m_menu->removeAllChildren();  // 直接移除的注释代码
    
    CCObject* pObject;
    CCArray* pArray = m_menu->getChildren();
    CCARRAY_FOREACH(pArray, pObject)
    {
        CCNode* pNode = dynamic_cast<CCNode*>(pObject);
        if (pNode)
        {
            // 创建隐藏→延迟→移除的动画序列
            CCHide* hi = CCHide::create();
            CCDelayTime* dl = CCDelayTime::create(0.5f);
            CCActionInstantRemoveFromParent* rmv = CCActionInstantRemoveFromParent::create();
            CCAction* action = CCSequence::create(hi, dl, rmv, NULL);
            pNode->runAction(action);
        }
    }

    // 创建装备槽位图标
    for (int i = 0; i < Equip_Total; ++i)
    {
        CCMenuItemImage* sprite = SystemData::getMenuItemImageByPlist("ui.bag.slot.equipitem");
        sprite->setPosition(EquipPos1[i]);  // 设置预设位置
        sprite->setTag(i);  // 设置标签为装备索引
        sprite->setTarget(this, menu_selector(SoulStonePanel::itemClickCallBack));  // 设置点击回调
        
        // 特殊处理不可用的装备槽位（置灰并禁用点击）
        if (i == 2 || i == 6 || i == 7 || i == 15 || i == 16 || i == 17 || i == 18 || i == 19  || i == 20  || i == 21  || i == 22   || i == 23  || i == 24)
        {
            sprite->setColor(ccGRAY);      // 置灰显示
            sprite->setTarget(this, NULL); // 移除点击回调，禁用交互
        }
        else
        {
            m_menu->addChild(sprite);  // 添加到菜单
        }
    }
    
    // 创建装备名称标签
    for (int i = 0; i < Equip_Total; ++i)
    {
        CCLabelTTF* name = SystemData::getLabelTTF(EquipName1[i].c_str());
        name->setPosition(EquipPos1[i]);  // 与槽位图标相同位置
        name->setTag(2000 + i + 1);       // 设置唯一标签（2001开始）
        name->setColor(ccWHITE);          // 白色文字
        name->setOpacity(255 / 2);        // 半透明效果（127透明度）
        name->setFontSize(18);            // 字体大小
        
        // 不可用槽位的名称也置灰显示
        if (i == 2 || i == 6 || i == 7 || i == 15 || i == 16 || i == 17 || i == 18 || i == 19  || i == 20  || i == 21  || i == 22  || i == 23   || i == 24)
        {
            name->setColor(ccGRAY);
        }
        else
        {
            m_menu->addChild(name);  // 添加到菜单
        }
    }
}

void SoulStonePanel::insertItem( UserItem* userItem, int pos )
{
	if (!userItem)
		return;

	if (m_menu->getChildByTag(2000-pos))
	{
		m_menu->removeChildByTag(2000-pos,true);
	}
	else
	{
		return;
	}

	CCMenuItemImage* icon = CommonFunction::getItemIcon(userItem,false);
	icon->setPosition(getItemPosition(pos));
	icon->setTag(-pos);
	icon->setVisible(getItemVisible(pos));
	
	m_menu->addChild(icon);
}

cocos2d::CCPoint SoulStonePanel::getItemPosition( int pos )
{
	return EquipPos1[-pos-1];
}


void SoulStonePanel::showEnd()
{
	removeChildByTag(1000,true);
}

/**
 * 装备槽位点击回调处理函数
 * 处理装备槽位的点击事件，更新界面显示并记录选中位置
 * 
 * @param pSender 触发点击事件的装备槽位菜单项
 */
void SoulStonePanel::itemClickCallBack(CCObject* pSender)
{
    // 将发送者转换为菜单项图像对象
    CCMenuItemImage* sprite = (CCMenuItemImage*)pSender;
    // 检查是否为不可点击的槽位（标签2、6、7）
    if (sprite->getTag() == 2 || sprite->getTag() == 6 || sprite->getTag() == 7 )
    {
        return;  // 直接返回，不执行后续操作
    }
    // 初始化界面显示，传入选中的槽位标签
    initInterface(sprite->getTag()); 
    // 记录当前选中的位置，供其他功能使用
    m_nPrePos = sprite->getTag();
}

void SoulStonePanel::handleEvent( int channel )
{
}

void SoulStonePanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageUpdPlayerPropsDataNotify")
		{
			if (m_bIsSelf)
			{
				initEquipSlot();
				UserItems items = GameData::s_user->getUserItemData()->userItems;

				for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
				{
					if (isPosInThisPanel(it->first))
					{
						insertItem(it->second,it->first);
					}
				}
				initInterface(m_nPrePos);
			}
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------------------//

const int ItemSize = 74;
SoulStoneMainPanel::SoulStoneMainPanel():
	m_posType(-1),
	m_iNearPos(0),
	m_bIsSelf(true),
	m_pImage(NULL),
	pGrade(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);

}

SoulStoneMainPanel::~SoulStoneMainPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);

}

SoulStoneMainPanel* SoulStoneMainPanel::create(int pos,bool isSelf)
{
	SoulStoneMainPanel* pPanel = new SoulStoneMainPanel();
	if(pPanel && pPanel->init(pos,isSelf))
	{
		pPanel->autorelease();
		return pPanel;
	}
	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}

std::string pos[5]={
	"ui_soulstone_button1_pos","ui_soulstone_button2_pos","ui_soulstone_button3_pos","ui_soulstone_button4_pos","ui_soulstone_button5_pos"
};

bool SoulStoneMainPanel::init(int postype,bool isSelf)
{
	m_bIsSelf=isSelf;
	m_posType=postype;
	m_menu = GeneralMenu::create();
	m_menu->setPosition(CCPointZero);
	m_menu->setAnchorPoint(CCPointZero);
	addChild(m_menu);

	/*CCSprite* pbkg = SystemData::getSprite("HS_bkg");
	pbkg->setPosition(ccp(200,253));
	m_menu->addChild(pbkg);*/

	CCLabelTTF *plabel=SystemData::getLabelTTF("ui_soulstone_label");
	plabel->setPosition(SystemData::getLayoutPoint("ui_soulstone_label_pos"));
	plabel->setFontSize(14);
	plabel->setColor(ccYELLOW);
	plabel->setAnchorPoint(CCPointZero);
	addChild(plabel);

	int count = getStoneGrade();
	pGrade=CCLabelTTF::create(SystemData::intToString(count).c_str(),"微软雅黑",15);
	pGrade->setAnchorPoint(CCPointZero);
	pGrade->setPosition(ccp(plabel->getPositionX()+70,plabel->getPositionY()));
	addChild(pGrade);

	for (int i=0;i<5;i++)
	{
		CCSprite *pSprite=SystemData::getSpriteByPlist("ui.bag.slot.unlock");
		pSprite->setPosition(SystemData::getLayoutPoint(pos[i]));
		addChild(pSprite);
	} 
	 
	if (m_bIsSelf)
	{
		if (GuideHelper::canOpenFunction(FunctionName::HE_CHENG))
		{
			CCLabelTTF* plabel1=SystemData::getLabelTTF("HSHC_HSHC");
			plabel1->setFontSize(20);
			CCMenuItemImage* pItem=SystemData::getScale9MenuItemImageByPlist("ui.HSbutton");
			pItem->setTarget(this,menu_selector(SoulStoneMainPanel::MenuCallBack));
			pItem->setPosition(SystemData::getLayoutPoint("ui_soulstone_button6_pos"));
			plabel1->setColor(ccWHITE);
			plabel1->setPosition(SystemData::getLayoutPoint("ui_soulstone_button6_pos"));
			m_menu->addChild(pItem);
			m_menu->addChild(plabel1);
		}
	}

	m_pMenu=GeneralMenu::create();
	m_pMenu->setAnchorPoint(CCPointZero);
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	insertSoulStone(m_posType);

	return true;
}

int SoulStoneMainPanel::getStoneGrade()
{
	int count=0;
	for (int j = 0; j < Pos_Foot; j++)//最大
	{
		for (int i = 0; i < 5; i++)
		{
			UserItem* pUserItem;
			if (m_bIsSelf)
			{
				pUserItem=GameData::s_user->m_pMainRole->m_pStoneArray[j][i];
			}
			else
			{
				pUserItem=GameData::s_user->m_pOtherRole->m_pStoneArray[j][i];
			}
			if (pUserItem!=NULL)
			{
				std::string name=pUserItem->name;
				string b;
				for (int n = 0; n != name.length(); ++n)
				{
					if (name.at(n) >= '0' && name.at(n) <= '9')
					{
						b += name.at(n);
					}
					else
					{
						b += '\0';
						break;
					}
				}
				int cnt=SystemData::stringToInt(b.c_str());
				int allcnt=pow(3,cnt-1);
				/*for (cnt;cnt>0;cnt--)
				{
					
					allcnt=allcnt*3;
				}*/
				count+=allcnt;
			}
		}
	}
	return count;
}

void SoulStoneMainPanel::MenuCallBack( CCObject* pSender )
{
	//打开魂石合成界面
	CPEventHelper::openPanel("MainPanel",TAG_Merge_Panel,TAG_HSHC,0,0);
}

void SoulStoneMainPanel::insertSoulStone( int postype )
{
	//判断是否该位置装备了  装备
	bool hasEquip=false;
	UserItems items;
	if (m_bIsSelf)
	{
		items = GameData::s_user->getUserItemData()->userItems;
	}
	else
	{
		items = GameData::s_user->m_pOtherRole->m_pAllItemMap;
	}
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		if (-it->first-1==postype)
		{
			hasEquip=true;
		}
	}

	m_iNearPos=0;

	CCArray *children =m_pMenu->getChildren();
	if (children && children->count() > 0)
	{
		CCObject *obj = NULL;
		CCARRAY_FOREACH(children, obj)
		{
			CCNode *child = dynamic_cast<CCNode *>(obj);
			if (child)
			{
				CCHide *hi = CCHide::create();
				CCDelayTime *dl = CCDelayTime::create(0.5f);
				CCActionInstantRemoveFromParent *rmv = CCActionInstantRemoveFromParent::create();
				CCAction *action = CCSequence::create(hi, dl, rmv, NULL);
				child->runAction(action);
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		UserItem* pUserItem;
		if (m_bIsSelf)
		{
			pUserItem=GameData::s_user->m_pMainRole->m_pStoneArray[postype][i];
		}
		else
		{
			pUserItem=GameData::s_user->m_pOtherRole->m_pStoneArray[postype][i];
		}
		if (pUserItem)
		{
			CCMenuItemImage* pItem = CommonFunction::getItemIcon(pUserItem,false);
			/*pItem->setNormalImage(LayoutData::getItemIcon(pUserItem->sid));
			pItem->setSelectedImage(LayoutData::getItemIcon(pUserItem->sid));*/
			pItem->setPosition(SystemData::getLayoutPoint(pos[i]));
			pItem->setTarget(this,menu_selector(SoulStoneMainPanel::ItemCallBack));
			//pItem->setUserData(pUserItem);
			if (!hasEquip)
			{
				pItem->setColor(ccGRAY);
			}
			if (CommonFunction::getStoneLvl(pUserItem->name)>=7)
			{
				EffectSprite* p=EffectSprite::create(Effect::effect_stoneputon);
				p->setPosition(ccp(pItem->getContentSize().width/2,pItem->getContentSize().height/2));
				pItem->addChild(p);
			}
			m_pMenu->addChild(pItem);
		}
		else
		{
			if (m_iNearPos==0)
			{				
				m_iNearPos=-(postype*5+100+i);
			}
		}
	}
	if (m_iNearPos==0)
	{
		m_iNearPos=-(postype*5+100+4);
	}
}

void SoulStoneMainPanel::ItemCallBack( CCObject* pSender )
{
	CCNode* pImage = dynamic_cast<CCNode*>(pSender);
	if(pImage)
	{
		UserItem* item = (UserItem*)pImage->getUserData();
		int tag = 0;
		if (item)
		{
			tag = item->position;
			m_pImage = pImage;

			if (m_bIsSelf)
			{
				if(isDoubleClickItem(tag))
				{				
					CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_POSTMSG,(CCObject *)item);
				}
				else
				{
					scheduleOnce(schedule_selector(SoulStoneMainPanel::singleClickCallback),DOUBLE_CLICK_TIME);
				}		
			}
			else
			{
				m_nPrePos = tag;
				showTooltip(m_nPrePos);
			}
		}
	}
	


	
	/*if (m_bIsSelf)
	{
		/ *if(isDoubleClickItem(tag))
		{
			// Send Message
			MsgItemOperationRequestUse* req = new MsgItemOperationRequestUse;
			UserItem* item = GameData::s_user->getUserItemData()->getItemByPosition(tag);
			req->iid = item->iid;
			req->eid = 1;
			req->cnt = 1;
			//req->version = 1;
			HandleMessage::sendMessage(req);
		}
		else
		{
			scheduleOnce(schedule_selector(SoulStoneMainPanel::singleClickCallback),DOUBLE_CLICK_TIME);
		}* /
	}
	else
	{
		m_nPrePos = tag;
		showTooltip(m_nPrePos);
	}*/
	

}


bool SoulStoneMainPanel::isDoubleClickItem( int pos )
{
	float curTime = SystemData::getSystemTime();
	if(m_nPrePos==pos && curTime-m_nPreTime < DOUBLE_CLICK_TIME)
	{
		m_nPrePos = ITEM_UNUSE_POS;
		m_nPreTime = curTime;
		m_bDoubleClick = true;
		return true;
	}
	m_nPrePos = pos;
	m_nPreTime = curTime;
	m_bDoubleClick = false;
	return false; 
}

void SoulStoneMainPanel::singleClickCallback( float dt )
{
	if(!m_bDoubleClick)
	{
		showTooltip(m_nPrePos);
		m_nPrePos = ITEM_UNUSE_POS;
		m_nPreTime = SystemData::getSystemTime();
	}
}

void SoulStoneMainPanel::showTooltip( int tag )
{
	if (m_pImage)
	{
		UserItem* pItem=(UserItem*)m_pImage->getUserData();
		CCPoint anpos=CCPointZero;
		CCPoint pos=ccp(300,10);
		CCPoint itempos=m_pImage->getPosition();
		itempos=convertToWorldSpace(itempos);
		CCPoint pos1=ccp(itempos.x-ItemSize/2,itempos.y+(ItemSize/2));
		CCPoint pos2=ccp(itempos.x+ItemSize/2,itempos.y+(ItemSize/2));
		CCPoint pos3=ccp(itempos.x+ItemSize/2,itempos.y+(-ItemSize/2));
		CCPoint pos4=ccp(itempos.x-ItemSize/2,itempos.y+(-ItemSize/2));

		pos=ccp(pos2.x,pos2.y-SystemData::getLayoutValue("Tips_size.h"));
		if (pos2.y<SystemData::getLayoutValue("Tips_size.h"))
		{
			pos=ccp(pos2.x,pos3.y);
		}
		int tipstype=TAG_Tips_XX;
		if (!m_bIsSelf)
		{
			tipstype=TAG_Tips;
		}
		Game::getGameUI()->showTipsPanel(pItem,tipstype,pos,anpos);
	}
}

void SoulStoneMainPanel::handleEvent( int channel )
{
}

void SoulStoneMainPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "MsgItemUpdPositionNotify" ||
			source == "HandleMessageItemAddNotifyEx")
		{
			if (m_bIsSelf)
			{
				GameData::s_user->UpdStoneArray();
				insertSoulStone(m_posType); 
			}
		}
		pGrade->setString(SystemData::intToString(getStoneGrade()).c_str());
	}
}
