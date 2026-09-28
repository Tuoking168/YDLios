#ifndef __GUILD_MEMBER_PANEL_H__
#define __GUILD_MEMBER_PANEL_H__

/*
功能：行会
*/

#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "MsgQuest.h"
#include "event/IEventListener.h"

USING_NS_CC_EXT;

//-----------------------------------------------------------------------------------------------------------------------------------------------//
/*
功能：
*/
class CPComboBox;
struct GuildMemberInfo;
class GuildMemberPanel : public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate, public IEventListener
{
public:
	GuildMemberPanel();
	~GuildMemberPanel();
	virtual bool init(const char* filename);
	static GuildMemberPanel* create();
	virtual void handleEvent(int channel);
	void onCPEvent(const std::string &eventName);
protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table); 


	void initFrame(); 
	void initLabels();
	void initButtons();
	void initCell(CCTableViewCell *cell,int idx);
	void loadCell(CCTableViewCell *cell,unsigned int idx);

	void loadGuildMemberPageUp();
	void loadGuildMemberPageDown();

	void editNicknameView();
	void reloadTableView();

	void filterPost();

	int getMaxPage();

	int getMemberListIndex();
	bool isSelectIndexValid();
public:
	virtual void MenuCallBack(CCObject* pSender);
	void changeNicknameCancelCallBack(CCObject* pSender);
	void CloseSelf(CCObject* pSender);
	void comboCallBack(CCNode* pSender);
	void filterCallBack(CCNode* pSender);

protected:
	
	GeneralMenu* m_pMainMenu;
	CCTableViewEx * m_pTableView;
	CCLabelTTF* m_LabelPage;

	std::vector<CPComboBox*> m_NicknameList;
	CPComboBox* m_filterNickname;

	std::vector<GuildMemberInfo> m_MemberList;

	const int m_kNumOfEachPage;
	int m_selIndex;
	int m_curPage;
	int m_filterValue;

	enum Child_Tag
	{
		Tag_NULL=0,
		//button
		Button_Detail,
		Button_Chat,
		Button_Friend,
		Button_Invite,
		Button_Apply,
		Button_AppList,
		Button_Call,
		Button_Editnickname,
		Button_Pageup,
		Button_Pagedown,
		Button_ChangeMaster,
		Button_Delete,
		//label
		Tag_Name,
		Tag_Job,
		Tag_Level,
		Tag_Contribution,
		Tag_Nickname,
		//Alert
		Alert_ChangeMaster_Confirm,
		Alert_Delete_Confirm,
		Alert_ChangeNickname_Confirm,
		
		//combo
		Combo_Nickname_Start = 100,
		Combo_Nickname_End = 110,
	};
};
class NickNameEditPanel : public BasePanel
{
public:
	NickNameEditPanel();
	~NickNameEditPanel();
	virtual bool init(int tag);
	static NickNameEditPanel* create(int tag);

protected:
	void initFrame();
	void initLabels();
	void initButtons();
public:
	virtual void MenuCallBack(CCObject* pSender);
	void closeSelf();
protected:
	GeneralMenu* m_pMainMenu;
	int m_selIndex;
};
#endif//__GUILD_MEMBER_PANEL_H__