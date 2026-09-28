#ifndef __RichTextUtils_h__
#define __RichTextUtils_h__

#include "MacroUtils.h"
#include <string>

#include "controls/CPRichText.h"

class CPRichText;
class RichTextUtils
{
public:
	static CPRichText *getRichText(const std::string &richString, int fontSize);
	static CPRichText *getRichText(const std::string &richString, int fontSize, int width, int height);
	static CPRichText *getRichText(const std::string &richString, int fontSize, int width, int height, int align);
	static CPRichText *getRichText(const std::string &richString, int fontSize, int width, int height, int align, const std::string &delimiterL, const std::string &delimiterR);

private:
	CP_MAKE_STATIC_CLASS(RichTextUtils);
};
#endif //__RichTextUtils_h__