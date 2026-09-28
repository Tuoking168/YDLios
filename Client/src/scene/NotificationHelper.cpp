#include "NotificationHelper.h"
#include "NotificationLayer.h"
#include "LowerRightNotificationPanel.h"
#include "cocos2d.h"
#include "NotificationModule.h"

#include "panel/ChatPanel.h"
#include "Game.h"

#include "userdata/LayoutData.h"
#include "userdata/GameData.h"

#include "controls/CPRichText.h"

#include "utils/RichTextUtils.h"

#include "script/LuaWrapper.h"


using namespace cocos2d;

static NotificationLayer *getNotificationLayer()
{
	CCNode *node = CCDirector::sharedDirector()->getNotificationNode();
	return dynamic_cast<NotificationLayer *>(node);
}

static bool convertTopNoteString( const std::string &baseMsg, std::string &richString )
{
	CPLua->push_utf8(baseMsg);
	if (CPLua->call("cb_convert_top_note_msg", 1, 1)
		&& CPLua->pop_utf8(richString))
	{
		return true;
	}
	CCLog(">Error: lua call cb_convert_top_note_msg failed!");
	return false;
}

static CCNode *getTopNoteNode( const std::string &baseMsg )
{
	const int fontSize = LayoutData::getInt(CPModuleName::NOTIFICATION, "topNoteFontSize");
	const int maxWith = LayoutData::getInt(CPModuleName::NOTIFICATION, "topNoteMaxWith");
	std::string richString;
	convertTopNoteString(baseMsg, richString);
	CPRichText *ret = RichTextUtils::getRichText(richString, fontSize, 0, 0, CPRichText::AlignLeft, "{", "}");
	if (ret->getContentSize().width > maxWith)
	{
		ret = RichTextUtils::getRichText(richString, fontSize, maxWith, 0, CPRichText::AlignCenter, "{", "}");
	}
	return ret;
}

//////////NotificationHelper////////////////////////////////////////////////////
LowerRightNotificationPanel *NotificationHelper::sLowerRightPanel = NULL;
void NotificationHelper::showNote( const std::string &note )
{
	showNote(note, NotificationType::normal);
}

void NotificationHelper::showNote( const std::string &note, int noteType )
{
	if (note.empty())
	{
		return;
	}

	switch (noteType)
	{
	case NotificationType::debug:
		{
			DebugCode(
				NotificationLayer *layer = getNotificationLayer();
				if (layer)
				{
					CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::NOTIFICATION, "normalNote");
					label->setString(note.c_str());
					layer->showMidRightNote(label);
				}
			);
			break;
		}
	case NotificationType::normal:
		{
			NotificationLayer *layer = getNotificationLayer();
			if (layer)
			{
				CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::NOTIFICATION, "normalNote");
				label->setString(note.c_str());
				layer->showMidRightNote(label);
			}
			break;
		}
	case NotificationType::trivial:
		{
			if (sLowerRightPanel)
			{
				CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::NOTIFICATION, "trivialNote");
				label->setString(note.c_str());
				sLowerRightPanel->showLowerRightNote(label);
			}
			break;
		}
	case NotificationType::normal_red:
		{
			NotificationLayer *layer = getNotificationLayer();
			if (layer)
			{
				CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::NOTIFICATION, "normalNote");
				label->setString(note.c_str());
				label->setColor(ccRED);
				layer->showMidRightNote(label);
			}
			break;
		}
	case NotificationType::trivial_red:
		{
			if (sLowerRightPanel)
			{
				CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::NOTIFICATION, "trivialNote");
				label->setString(note.c_str());
				label->setColor(ccRED);
				sLowerRightPanel->showLowerRightNote(label);
			}
			break;
		}
	case NotificationType::top:
		{
			showTopNote(note);
			break;
		}
	default:
		CCLog(">>>Error:NotificationHelper::showNote, unknown noteType: %d", noteType);
		break;
	}
}

void NotificationHelper::showTopNote( const std::string &baseMsg )
{
	if(GameData::s_game_state != GAME_STATE_RUNNING
		|| !Game::getGameUI())
	{
		return;
	}

	NotificationLayer *layer = getNotificationLayer();
	if (layer)
	{
		layer->showTopNote(getTopNoteNode(baseMsg));
	}
	ChatPanelHelper::addSystemMsg(baseMsg);
}

void NotificationHelper::showPeaceAreaNote( bool isInto )
{
	if (isInto)
	{
		showNote(LayoutData::getString(CPModuleName::NOTIFICATION, "intoPeaceArea"), NotificationType::trivial);
	}
	else
	{
		showNote(LayoutData::getString(CPModuleName::NOTIFICATION, "outPeaceArea"), NotificationType::trivial);
	}
}

void NotificationHelper::checkNetState()
{
	NotificationLayer *layer = getNotificationLayer();
	if (layer)
	{
		layer->checkNetState();
	}
}

void NotificationHelper::addNode( cocos2d::CCNode *node )
{
	NotificationLayer *layer = getNotificationLayer();
	if (layer)
	{
		layer->addChild(node);
	}
}

void NotificationHelper::setLowerRightPanel( LowerRightNotificationPanel *panel )
{
	sLowerRightPanel = panel;
}

void NotificationHelper::delayRun( float dt, VoidCallBack func )
{
	NotificationLayer *layer = getNotificationLayer();
	if (layer)
	{
		layer->delayRun(dt, func);
	}
}
