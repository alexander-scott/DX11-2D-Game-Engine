#pragma once

#include "IGraphics.h"
#include "Consts.h"
#include "Colors.h"

#include <cassert>
#include <map>
#include <memory>

#include <d3d11.h>
#include "DirectXTK\Inc\SpriteBatch.h"
#include "DirectXTK\Inc\SpriteFont.h"
#include "DirectXTK\Inc\DDSTextureLoader.h"
#include "directxtk\Inc\PrimitiveBatch.h"
#include "directxtk\Inc\VertexTypes.h"

using namespace DirectX;

class DX11Graphics : public IGraphics
{
public:
	virtual void Initalise(class HWNDKey& key) override;
	virtual void Destroy() override;

	virtual void EndFrame() override;
	virtual void BeginFrame() override;

	virtual void PreloadTextures() override;

	virtual void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot) override;
	virtual void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot, float scale) override;
	virtual void DrawText(std::string text, Vec2 pos) override;

	virtual void DrawLine(Vec2 v1, Vec2 v2) override;

private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x, y, z;		// position
		float u, v;			// texcoords
	};

	Microsoft::WRL::ComPtr<IDXGISwapChain>					pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>					pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>				pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>			pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>					pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>				pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>				pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>					pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>				pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>				pSamplerState;

	std::unique_ptr<SpriteBatch>							g_Sprites;
	std::unique_ptr<SpriteFont>								g_Fonts;
	std::unique_ptr<PrimitiveBatch<VertexPositionColor>>	g_primitiveBatch;
	std::map<std::string, ID3D11ShaderResourceView*>		g_textures;

	void CreateShaderResourceView(std::string name);
};