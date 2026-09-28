
#ifndef __CCMENU_ITEM_FONT_COLOR_H__
#define __CCMENU_ITEM_FONT_COLOR_H__

#include "base_nodes/CCNode.h"
#include "CCProtocols.h"
#include "cocoa/CCArray.h"
#include "menu_nodes/CCMenuItem.h"

NS_CC_BEGIN

class CCLabelTTF;

class CCMenuItemLabelColor : public CCMenuItem
{
    /** the color that will be used to disable the item */
    CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tDisabledColor, DisabledColor);
    /** Label that is rendered. It can be any CCNode that implements the CCLabelProtocol */
    CC_PROPERTY(CCNode*, m_pLabel, Label);
public:
	CCMenuItemLabelColor()
		: m_pLabel(NULL)
    , m_fOriginalScale(0.0)
    {}
    virtual ~CCMenuItemLabelColor();
    /** creates a CCMenuItemLabel with a Label, target and selector 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemLabelColor * itemWithLabel(CCNode*label, CCObject* target, SEL_MenuHandler selector);
    /** creates a CCMenuItemLabel with a Label. Target and selector will be nill 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemLabelColor* itemWithLabel(CCNode *label);

    /** creates a CCMenuItemLabel with a Label, target and selector */
    static CCMenuItemLabelColor * create(CCNode*label, CCObject* target, SEL_MenuHandler selector);
    /** creates a CCMenuItemLabel with a Label. Target and selector will be nill */
    static CCMenuItemLabelColor* create(CCNode *label);

    /** initializes a CCMenuItemLabel with a Label, target and selector */
    bool initWithLabel(CCNode* label, CCObject* target, SEL_MenuHandler selector);
    /** sets a new string to the inner label */
    void setString(const char * label);
    // super methods
    virtual void activate();
    virtual void selected();
    virtual void unselected();
    /** Enable or disabled the CCMenuItemFont
     @warning setEnabled changes the RGB color of the font
     */
    virtual void setEnabled(bool enabled);
    virtual void setOpacity(GLubyte opacity);
    virtual GLubyte getOpacity();
    virtual void setColor(const ccColor3B& color);
    virtual const ccColor3B& getColor();
    
    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
protected:
    ccColor3B    m_tColorBackup;
    float        m_fOriginalScale;
};

/** @brief A CCMenuItemFont
 Helper class that creates a CCMenuItemLabel class with a Label
 */
class CCMenuItemFontColor : public CCMenuItemLabelColor
{
public:
    CCMenuItemFontColor() : m_uFontSize(0), m_strFontName(""){}
    virtual ~CCMenuItemFontColor(){}
    /** set default font size */
    static void setFontSize(unsigned int s);
    /** get default font size */
    static unsigned int fontSize();
    /** set the default font name */
    static void setFontName(const char *name);
    /** get the default font name */
    static const char *fontName();
    /** creates a menu item from a string without target/selector. To be used with CCMenuItemToggle 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemFontColor * itemWithString(const char *value);
    /** creates a menu item from a string with a target/selector 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCMenuItemFontColor * itemWithString(const char *value, CCObject* target, SEL_MenuHandler selector);

    /** creates a menu item from a string without target/selector. To be used with CCMenuItemToggle */
    static CCMenuItemFontColor * create(const char *value);
    /** creates a menu item from a string with a target/selector */
    static CCMenuItemFontColor * create(const char *value, CCObject* target, SEL_MenuHandler selector);

    /** initializes a menu item from a string with a target/selector */
    bool initWithString(const char *value, CCObject* target, SEL_MenuHandler selector);
    
    /** set font size
     * c++ can not overload static and non-static member functions with the same parameter types
     * so change the name to setFontSizeObj
     */
    void setFontSizeObj(unsigned int s);
    
    /** get font size */
    unsigned int fontSizeObj();
    
    /** set the font name 
     * c++ can not overload static and non-static member functions with the same parameter types
     * so change the name to setFontNameObj
     */
    void setFontNameObj(const char* name);
    
    const char* fontNameObj();
    
protected:
    void recreateLabel();
    
    unsigned int m_uFontSize;
    std::string m_strFontName;
};

NS_CC_END

#endif//__CCMENU_ITEM_FONT_COLOR_H__