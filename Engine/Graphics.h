#pragma once

#include "WinDefines.h"
#include <d3d11.h>
#include <wrl.h>
#include "CustomException.h"
#include "Colors.h"
#include <cassert>

#include "DirectXTK\Inc\SpriteBatch.h"
#include "DirectXTK\Inc\SpriteFont.h"
#include "DirectXTK\Inc\DDSTextureLoader.h"
#include <map>
#include <memory>

using namespace DirectX;

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

	void DrawSpriteDX11(std::string name, XMFLOAT2 pos);
	void DrawSpriteDX11(std::string name, XMFLOAT2 pos, RECT* rect);

	void DrawTextDX11(std::string text, XMFLOAT2 pos);

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

	std::unique_ptr<SpriteBatch>                        g_Sprites;
	std::unique_ptr<SpriteFont>                         g_Fonts;
	std::map<std::string, ID3D11ShaderResourceView*>	textures;

	void CreateShaderResourceView(std::string name);

public:
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
};