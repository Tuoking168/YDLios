#ifndef __TopMergeServerPanel_h__
#define __TopMergeServerPanel_h__


#include "scene/panel/MenuListPanel.h"

class TopMergeServerPanel : public MenuListPanel
{
public:
	TopMergeServerPanel();
	~TopMergeServerPanel();
	CREATE_FUNC(TopMergeServerPanel);

	bool init();
	virtual const std::string dataTableName();
	virtual void onSwitch(int tag);

private:
	enum
	{
		panel_czdhk,
		panel_czdbp,
		panel_djdbp,
		panel_zldbp,
		panel_sczb,
		panel_smsd,
	};
};
#endif //TopMergeServerPanel