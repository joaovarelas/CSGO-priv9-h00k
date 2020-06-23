#pragma once
#include "getvfunc.h"
#include "Color.h"

#define FW_DONTCARE         0
#define FW_THIN             100
#define FW_EXTRALIGHT       200
#define FW_LIGHT            300
#define FW_NORMAL           400
#define FW_MEDIUM           500
#define FW_SEMIBOLD         600
#define FW_BOLD             700
#define FW_EXTRABOLD        800
#define FW_HEAVY            900





#undef CreateFont



enum FontRenderFlag_t
{
	FONT_LEFT = 0,
	FONT_RIGHT = 1,
	FONT_CENTER = 2
};

enum FontDrawType_t
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2,
};

enum FontFlags_t
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

typedef unsigned long HFont;




namespace Interfaces {
	/*
	class Surface
	{
	public:
		void DrawSetColor(int r, int g, int b, int a);
		void DrawSetColor(Color col);
		void DrawFilledRect(int x0, int y0, int x1, int y1);
		void DrawOutlinedRect(int x0, int y0, int x1, int y1);
		void DrawLine(int x0, int y0, int x1, int y1);
		void DrawPolyLine(int* px, int* py, int numPoints);
		//void DrawSetTextFont(HFont font);
		void DrawSetTextColor(int r, int g, int b, int a);
		void DrawSetTextColor(Color col);
		void DrawSetTextPos(int x, int y);
		//void DrawPrintText(const wchar_t* text, int textLen, FontDrawType_t drawType = FONT_DRAW_DEFAULT);
		void DrawSetTextureRGBA(int id, const unsigned char* rgba, int wide, int tall);
		void DrawSetTexture(int id);
		int CreateNewTextureID(bool procedural = false);
		//HFont Create_Font();
		//bool SetFontGlyphSet(HFont font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0);
		//void GetTextSize(HFont font, const wchar_t* text, int& wide, int& tall);
		void DrawOutlinedCircle(int x, int y, int radius, int segments);
		//void DrawTexturedPolygon(int n, Vertex_t* pVertice, bool bClipVertices = true);
	};

	class oldSurface
	{
	public:
	// Create a font
	long CreateFont()
	{
	typedef	int(__thiscall* oCreateFont)(void*);

	return getvfunc<oCreateFont>(this, 71)(this);
	}

	// Set font glyph set
	void SetFontGlyphSet(unsigned long& font, const char* fontName, int h, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0)
	{
	typedef void(__thiscall* oSFGS)(void*, unsigned long, const char*, int, int, int, int, int, int, int);

	return getvfunc<oSFGS>(this, 72)(this, font, fontName, h, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
	}

	// Draw color
	void DrawSetColor(Color col)
	{
	typedef void(__thiscall* oDrawSetColor)(void*, Color);

	return getvfunc<oDrawSetColor>(this, 14)(this, col);
	}

	void DrawOutlinedRect(int x, int y, int w, int h)
	{
	typedef void(__thiscall* oOutlinedRect)(void*, int, int, int, int);

	return getvfunc<oOutlinedRect>(this, 18)(this, x, y, w, h);
	}

	void DrawFilledRect(int x, int y, int x2, int y2)
	{
	typedef void(__thiscall* oDrawFilledRect)(void*, int, int, int, int);
	return getvfunc<oDrawFilledRect>(this, 16)(this, x, y, x2, y2);
	}

	// Text to draw, length, length of text, and type, type of text. Nor
	void DrawPrintText(wchar_t* text, int length, int type)
	{

	typedef void(__thiscall* oTTP) (void*, wchar_t*, int, int);

	return getvfunc<oTTP>(this, 28) (this, text, length, type);
	}

	void DrawSetTextPos(int x, int y)
	{
	typedef void(__thiscall* oSetTextPos)(void*, int, int);

	return getvfunc<oSetTextPos>(this, 26)(this, x, y);
	}

	void DrawSetTextFont(int font)
	{
	typedef void(__thiscall* oFont)(void*, int);

	return getvfunc<oFont>(this, 23)(this, font);
	}

	void DrawSetTextColor(Color col)
	{
	typedef void(__thiscall* oCol) (void*, Color);

	return getvfunc<oCol>(this, 24)(this, col);
	}
	};
	*/


	class Surface {
	public:

		
		HFont Create_Font()
		{
			typedef HFont(__thiscall* OriginalFn)(void*);
			return getvfunc< OriginalFn >(this, 71)(this);
		}

		bool SetFontGlyphSet(HFont font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin=0, int nRangeMax=0)
		{
			typedef bool(__thiscall* OriginalFn)(void*, HFont, const char*, int, int, int, int, int, int, int);
			return getvfunc< OriginalFn >(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
		}



		void DrawPrintText(const wchar_t *text, int textLen, FontDrawType_t drawType)
		{
			typedef void(__thiscall* OriginalFn)(void*, const wchar_t*, int, FontDrawType_t);
			return getvfunc<OriginalFn>(this, 28)(this, text, textLen, drawType);
		}


		void GetTextSize(HFont font, const wchar_t* text, int& wide, int& tall)
		{
			typedef void(__thiscall* OriginalFn)(void*, HFont, const wchar_t*, int&, int&);
			return getvfunc< OriginalFn >(this, 79)(this, font, text, wide, tall);
		}

		void DrawSetTextFont(HFont font)
		{
			typedef void(__thiscall* OriginalFn)(void*, HFont);
			return getvfunc< OriginalFn >(this, 23)(this, font);
		}

		void DrawSetColor(int r, int g, int b, int a)
		{
			typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
			return getvfunc< OriginalFn >(this, 15)(this, r, g, b, a);
		}

		void DrawSetColor(Color col)
		{
			typedef void(__thiscall* OriginalFn)(void*, Color);
			return getvfunc< OriginalFn >(this, 14)(this, col);
		}

		void DrawFilledRect(int x0, int y0, int x1, int y1)
		{
			typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
			return getvfunc< OriginalFn >(this, 16)(this, x0, y0, x1, y1);
		}

		void DrawOutlinedRect(int x0, int y0, int x1, int y1)
		{
			typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
			return getvfunc< OriginalFn >(this, 18)(this, x0, y0, x1, y1);
		}

		void DrawLine(int x0, int y0, int x1, int y1)
		{
			typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
			return getvfunc< OriginalFn >(this, 19)(this, x0, y0, x1, y1);
		}

		void DrawPolyLine(int* px, int* py, int numPoints)
		{
			typedef void(__thiscall* OriginalFn)(void*, int*, int*, int);
			return getvfunc< OriginalFn >(this, 20)(this, px, py, numPoints);
		}


		void DrawSetTextColor(int r, int g, int b, int a)
		{
			typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
			return getvfunc< OriginalFn >(this, 25)(this, r, g, b, a);
		}

		void DrawSetTextColor(Color col)
		{
			typedef void(__thiscall* OriginalFn)(void*, Color);
			return getvfunc< OriginalFn >(this, 24)(this, col);
		}

		void DrawSetTextPos(int x, int y)
		{
			typedef void(__thiscall* OriginalFn)(void*, int, int);
			return getvfunc< OriginalFn >(this, 26)(this, x, y);
		}


		void DrawSetTextureRGBA(int id, const unsigned char* rgba, int wide, int tall)
		{
			typedef void(__thiscall* OriginalFn)(void*, int, const unsigned char*, int, int);
			return getvfunc< OriginalFn >(this, 37)(this, id, rgba, wide, tall);
		}

		void DrawSetTexture(int id)
		{
			typedef void(__thiscall* OriginalFn)(void*, int);
			return getvfunc< OriginalFn >(this, 38)(this, id);
		}

		int CreateNewTextureID(bool procedural)
		{
			typedef int(__thiscall* OriginalFn)(void*, bool);
			return getvfunc< OriginalFn >(this, 43)(this, procedural);
		}


	};
}








