#ifndef __LONGER_FONT_HANDLE__
#define __LONGER_FONT_HANDLE__
#include "cocos2d.h"
using namespace cocos2d;
//////////////////////////////////////////////////////////////////////////
typedef struct _FontDefHashElement
{
    unsigned int    key;        // key. Font Unicode value
    ccBMFontDef        fontDef;    // font definition
    UT_hash_handle    hh;
} tFontDefHashElement;

static int cc_wcslen(const unsigned short* str)
{
    int i=0;
    while(*str++) i++;
    return i;
}

/* Code from GLIB gutf8.c starts here. */

#define UTF8_COMPUTE(Char, Mask, Len)        \
  if (Char < 128)                \
    {                        \
      Len = 1;                    \
      Mask = 0x7f;                \
    }                        \
  else if ((Char & 0xe0) == 0xc0)        \
    {                        \
      Len = 2;                    \
      Mask = 0x1f;                \
    }                        \
  else if ((Char & 0xf0) == 0xe0)        \
    {                        \
      Len = 3;                    \
      Mask = 0x0f;                \
    }                        \
  else if ((Char & 0xf8) == 0xf0)        \
    {                        \
      Len = 4;                    \
      Mask = 0x07;                \
    }                        \
  else if ((Char & 0xfc) == 0xf8)        \
    {                        \
      Len = 5;                    \
      Mask = 0x03;                \
    }                        \
  else if ((Char & 0xfe) == 0xfc)        \
    {                        \
      Len = 6;                    \
      Mask = 0x01;                \
    }                        \
  else                        \
    Len = -1;

#define UTF8_LENGTH(Char)            \
  ((Char) < 0x80 ? 1 :                \
   ((Char) < 0x800 ? 2 :            \
    ((Char) < 0x10000 ? 3 :            \
     ((Char) < 0x200000 ? 4 :            \
      ((Char) < 0x4000000 ? 5 : 6)))))


#define UTF8_GET(Result, Chars, Count, Mask, Len)    \
  (Result) = (Chars)[0] & (Mask);            \
  for ((Count) = 1; (Count) < (Len); ++(Count))        \
    {                            \
      if (((Chars)[(Count)] & 0xc0) != 0x80)        \
    {                        \
      (Result) = -1;                \
      break;                    \
    }                        \
      (Result) <<= 6;                    \
      (Result) |= ((Chars)[(Count)] & 0x3f);        \
    }

#define UNICODE_VALID(Char)            \
  ((Char) < 0x110000 &&                \
   (((Char) & 0xFFFFF800) != 0xD800) &&        \
   ((Char) < 0xFDD0 || (Char) > 0xFDEF) &&    \
   ((Char) & 0xFFFE) != 0xFFFE)


static const char utf8_skip_data[256] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5,
  5, 5, 5, 6, 6, 1, 1
};

static const char *const g_utf8_skip = utf8_skip_data;

#define cc_utf8_next_char(p) (char *)((p) + g_utf8_skip[*(unsigned char *)(p)])

/*
 * @str:    the string to search through.
 * @c:        the character to find.
 * 
 * Returns the index of the first occurrence of the character, if found.  Otherwise -1 is returned.
 * 
 * Return value: the index of the first occurrence of the character if found or -1 otherwise.
 * */
static unsigned int cc_utf8_find_char(std::vector<unsigned short> str, unsigned short c)
{
    unsigned int len = str.size();

    for (unsigned int i = 0; i < len; ++i)
        if (str[i] == c) return i;

    return -1;
}

/*
 * @str:    the string to search through.
 * @c:        the character to not look for.
 * 
 * Return value: the index of the last character that is not c.
 * */
static unsigned int cc_utf8_find_last_not_char(std::vector<unsigned short> str, unsigned short c)
{
    int len = str.size();

    int i = len - 1;
    for (; i >= 0; --i)
        if (str[i] != c) return i;

    return i;
}

/*
 * @str:    the string to trim
 * @index:    the index to start trimming from.
 * 
 * Trims str st str=[0, index) after the operation.
 * 
 * Return value: the trimmed string.
 * */
static void cc_utf8_trim_from(std::vector<unsigned short>* str, int index)
{
    int size = str->size();
    if (index >= size || index < 0)
        return;

    str->erase(str->begin() + index, str->begin() + size);
}

/*
 * @ch is the unicode character whitespace?
 * 
 * Reference: http://en.wikipedia.org/wiki/Whitespace_character#Unicode
 * 
 * Return value: weather the character is a whitespace character.
 * */
static bool isspace_unicode(unsigned short ch)
{
    return  (ch >= 0x0009 && ch <= 0x000D) || ch == 0x0020 || ch == 0x0085 || ch == 0x00A0 || ch == 0x1680
        || (ch >= 0x2000 && ch <= 0x200A) || ch == 0x2028 || ch == 0x2029 || ch == 0x202F
        ||  ch == 0x205F || ch == 0x3000;
}

static void cc_utf8_trim_ws(std::vector<unsigned short>* str)
{
    int len = str->size();

    if ( len <= 0 )
        return;

    int last_index = len - 1;

    // Only start trimming if the last character is whitespace..
    if (isspace_unicode((*str)[last_index]))
    {
        for (int i = last_index - 1; i >= 0; --i)
        {
            if (isspace_unicode((*str)[i]))
                last_index = i;
            else
                break;
        }

        cc_utf8_trim_from(str, last_index);
    }
}

/*
 * g_utf8_strlen:
 * @p: pointer to the start of a UTF-8 encoded string.
 * @max: the maximum number of bytes to examine. If @max
 *       is less than 0, then the string is assumed to be
 *       null-terminated. If @max is 0, @p will not be examined and
 *       may be %NULL.
 *
 * Returns the length of the string in characters.
 *
 * Return value: the length of the string in characters
 **/
static long
cc_utf8_strlen (const char * p, int max)
{
  long len = 0;
  const char *start = p;

  if (!(p != NULL || max == 0))
  {
      return 0;
  }

  if (max < 0)
    {
      while (*p)
    {
      p = cc_utf8_next_char (p);
      ++len;
    }
    }
  else
    {
      if (max == 0 || !*p)
    return 0;

      p = cc_utf8_next_char (p);

      while (p - start < max && *p)
    {
      ++len;
      p = cc_utf8_next_char (p);
    }

      /* only do the last len increment if we got a complete
       * char (don't count partial chars)
       */
      if (p - start == max)
    ++len;
    }

  return len;
}

/*
 * g_utf8_get_char:
 * @p: a pointer to Unicode character encoded as UTF-8
 *
 * Converts a sequence of bytes encoded as UTF-8 to a Unicode character.
 * If @p does not point to a valid UTF-8 encoded character, results are
 * undefined. If you are not sure that the bytes are complete
 * valid Unicode characters, you should use g_utf8_get_char_validated()
 * instead.
 *
 * Return value: the resulting character
 **/
static unsigned int
cc_utf8_get_char (const char * p)
{
  int i, mask = 0, len;
  unsigned int result;
  unsigned char c = (unsigned char) *p;

  UTF8_COMPUTE (c, mask, len);
  if (len == -1)
    return (unsigned int) - 1;
  UTF8_GET (result, p, i, mask, len);

  return result;
}

/*
 * cc_utf16_from_utf8:
 * @str_old: pointer to the start of a C string.
 * 
 * Creates a utf8 string from a cstring.
 * 
 * Return value: the newly created utf8 string.
 * */
static unsigned short* cc_utf16_from_utf8(const char* str_old)
{
    int len = cc_utf8_strlen(str_old, -1);

    unsigned short* str_new = new unsigned short[len + 1];
    str_new[len] = 0;

    for (int i = 0; i < len; ++i)
    {
        str_new[i] = cc_utf8_get_char(str_old);
        str_old = cc_utf8_next_char(str_old);
    }

    return str_new;
}

static std::vector<unsigned short> cc_utf16_vec_from_utf16_str(const unsigned short* str)
{
    int len = cc_wcslen(str);
    std::vector<unsigned short> str_new;

    for (int i = 0; i < len; ++i)
    {
        str_new.push_back(str[i]);
    }
    return str_new;
}
static bool getStringImage(const char *text, CCImage& image,const CCSize& dimensions, CCTextAlignment hAlignment, CCVerticalTextAlignment vAlignment, const char *fontName, float fontSize)
{

	CCImage::ETextAlign eAlign;

	if (kCCVerticalTextAlignmentTop == vAlignment)
	{
		eAlign = (kCCTextAlignmentCenter == hAlignment) ? CCImage::kAlignTop
			: (kCCTextAlignmentLeft == hAlignment) ? CCImage::kAlignTopLeft : CCImage::kAlignTopRight;
	}
	else if (kCCVerticalTextAlignmentCenter == vAlignment)
	{
		eAlign = (kCCTextAlignmentCenter == hAlignment) ? CCImage::kAlignCenter
			: (kCCTextAlignmentLeft == hAlignment) ? CCImage::kAlignLeft : CCImage::kAlignRight;
	}
	else if (kCCVerticalTextAlignmentBottom == vAlignment)
	{
		eAlign = (kCCTextAlignmentCenter == hAlignment) ? CCImage::kAlignBottom
			: (kCCTextAlignmentLeft == hAlignment) ? CCImage::kAlignBottomLeft : CCImage::kAlignBottomRight;
	}
	else
	{
		CCAssert(false, "Not supported alignment format!");
	}

	if (!image.initWithString(text, (int)dimensions.width, (int)dimensions.height, eAlign, fontName, (int)fontSize))
	{
		return false;
	}
	return true;
}
static std::string getStringFront(const std::string& text)
{
	const char* p=text.c_str();
	//////////////////////////////////////////////////////////////////////////
	//int i, mask = 0, len;
	//unsigned int result;
	int mask=0,len;
	unsigned char c = (unsigned char) *p;

	UTF8_COMPUTE (c, mask, len);
	//if (len == -1)
		//return "";
	//UTF8_GET (result, p, i, mask, len);
	//////////////////////////////////////////////////////////////////////////
	return text.substr(0,len);
}
//////////////////////////////////////////////////////////////////////////
static unsigned int cc_utf8_get_char_len (const char * p,int& oneCharLen)
{
	int i, mask = 0;//, len;
	oneCharLen=0;
	unsigned int result;
	unsigned char c = (unsigned char) *p;

	UTF8_COMPUTE (c, mask, oneCharLen);
	if (oneCharLen == -1)
		return (unsigned int) - 1;
	UTF8_GET (result, p, i, mask, oneCharLen);

	return result;
}
static CCSize getDescSize (const std::string& desc,const std::string& fontName,float fontSize)
{
	CCTexture2D *texture = new CCTexture2D();
	texture->initWithString(
		desc.c_str(), 
		CCSizeMake(0,0), 
		kCCTextAlignmentLeft, 
		kCCVerticalTextAlignmentTop, 
		fontName.c_str(), 
		fontSize* CC_CONTENT_SCALE_FACTOR());
	const CCSize& tSize=texture->getContentSize();
	texture->release();
	return tSize;
}
static std::string getFrontChar(const std::string& desc,int len)
{
	std::string descCopy=desc;
	const char* str_old=descCopy.c_str();
	int length = cc_utf8_strlen(str_old, -1);
	length=length<len?length:len;

	unsigned int str_new(0);

	int currLen=0;
	int oneCharLen=0;
	std::string oneChar;
	std::string descResult;
	for (int i = 0; i < len; ++i)
	{
		str_new/*[i]*/ = cc_utf8_get_char_len(str_old,oneCharLen);
		if (oneCharLen!=-1)
		{
			oneChar=desc.substr(currLen,oneCharLen);
			descResult+=oneChar;
			currLen+=oneCharLen;
		}
		str_old = cc_utf8_next_char(str_old);
	}
	return descResult;
}
static std::string getWideChar(const std::string& desc,float w,const std::string& fontName,float fontSize,bool& isBig)
{
	isBig=false;
	std::string descCopy=desc;
	const char* str_old=descCopy.c_str();
	int length = cc_utf8_strlen(str_old, -1);

	unsigned int str_new(0);

	int currLen(0);
	int oneCharLen(0);
	std::string oneChar;
	std::string descResult;
	float currWide(0);
	CCSize oneCharSize;
	for (int i = 0; i < length; ++i)
	{
		str_new = cc_utf8_get_char_len(str_old,oneCharLen);
		if (oneCharLen!=-1)
		{
			oneChar=desc.substr(currLen,oneCharLen);
			oneCharSize=getDescSize(oneChar,fontName,fontSize);
			currWide+=oneCharSize.width;
			if (currWide>=w)
			{
				isBig=true;
				return descResult;
			}
			descResult+=oneChar;
			currLen+=oneCharLen;
		}
		str_old = cc_utf8_next_char(str_old);
	}
	return descResult;
}

#endif//__LONGER_FONT_HANDLE__