#pragma once

#include "CustomException.h"
#include "WinDefines.h"
#include "IEMath.h"
#include <wrl.h>

class IGraphics
{
public:
	class Exception : public CustomException
	{
	public:
		Exception(HRESULT hr, const std::wstring& note, const wchar_t* file, unsigned int line);
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;

	private:
		HRESULT hr;
	};

	virtual void Initalise(class HWNDKey& key) = 0;
	virtual void Destroy() = 0;

	virtual void EndFrame() = 0;
	virtual void BeginFrame() = 0;

	virtual void PreloadTextures() = 0;

	virtual void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot) = 0;
	virtual void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot, float scale) = 0;
	virtual void DrawText(std::string text, Vec2 pos) = 0;
};