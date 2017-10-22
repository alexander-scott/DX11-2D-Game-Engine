#pragma once

#include "WinDefines.h"
#include <d3d11.h>
#include <wrl.h>
#include "CustomException.h"
#include "Colors.h"
#include "Surface.h"
#include "Rect.h"
#include <cassert>

class Graphics
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

private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x, y, z;		// position
		float u, v;			// texcoords
	};

public:
	Graphics(class HWNDKey& key);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	void EndFrame();
	void BeginFrame();
	Color GetPixel(int x, int y) const;

	void PutPixel(int x, int y, int r, int g, int b)
	{
		PutPixel(x, y, { unsigned char(r),unsigned char(g),unsigned char(b) });
	}

	void PutPixel(int x, int y, Color c);

	template<typename E>
	void DrawSprite(int x, int y, const Surface& s, E effect)
	{
		DrawSprite(x, y, s.GetRect(), s, effect);
	}

	template<typename E>
	void DrawSprite(int x, int y, const RectI& srcRect, const Surface& s, E effect)
	{
		DrawSprite(x, y, srcRect, GetScreenRect(), s, effect);
	}

	template<typename E>
	void DrawSprite(int x, int y, RectI srcRect, const RectI& clip, const Surface& s, E effect)
	{
		assert(srcRect.left >= 0);
		assert(srcRect.right <= s.GetWidth());
		assert(srcRect.top >= 0);
		assert(srcRect.bottom <= s.GetHeight());
		if (x < clip.left)
		{
			srcRect.left += clip.left - x;
			x = clip.left;
		}
		if (y < clip.top)
		{
			srcRect.top += clip.top - y;
			y = clip.top;
		}
		if (x + srcRect.GetWidth() > clip.right)
		{
			srcRect.right -= x + srcRect.GetWidth() - clip.right;
		}
		if (y + srcRect.GetHeight() > clip.bottom)
		{
			srcRect.bottom -= y + srcRect.GetHeight() - clip.bottom;
		}
		for (int sy = srcRect.top; sy < srcRect.bottom; sy++)
		{
			for (int sx = srcRect.left; sx < srcRect.right; sx++)
			{
				effect(
					s.GetPixel(sx, sy),
					x + sx - srcRect.left,
					y + sy - srcRect.top,
					*this
				);
			}
		}
	}

	~Graphics();

private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Color*                                              pSysBuffer = nullptr;

public:
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
	static RectI GetScreenRect();
};