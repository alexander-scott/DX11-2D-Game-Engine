#include "DX11Graphics.h"

#include "MainWindow.h"
#include "DXErr.h"
#include <assert.h>
#include <string>
#include <array>

namespace FramebufferShaders
{
#include "FramebufferPS.shh"
#include "FramebufferVS.shh"
}

#pragma comment( lib,"d3d11.lib" )

#define GFX_EXCEPTION( hr,note ) DX11Graphics::Exception( hr,note,_CRT_WIDE(__FILE__),__LINE__ )

using Microsoft::WRL::ComPtr;

void DX11Graphics::Initalise(HWNDKey& key)
{
	assert(key.hWnd != nullptr);

	// Create device and swap chain
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = ApplicationValues::Instance().ScreenWidth;
	sd.BufferDesc.Height = ApplicationValues::Instance().ScreenHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 1;
	sd.BufferDesc.RefreshRate.Denominator = 60;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = key.hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	HRESULT				hr;
	UINT				createFlags = 0u;
#ifdef USE_D3D_DEBUG_LAYER
#ifdef _DEBUG
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
#endif

	// Create device buffers
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pImmediateContext)))
	{
		throw GFX_EXCEPTION(hr, L"Creating device and swap chain");
	}

	// Get handle to backbuffer
	ComPtr<ID3D11Resource> pBackBuffer;
	if (FAILED(hr = pSwapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		(LPVOID*)&pBackBuffer)))
	{
		throw GFX_EXCEPTION(hr, L"Getting back buffer");
	}

	// Create a view on backbuffer that we can render to
	if (FAILED(hr = pDevice->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		&pRenderTargetView)))
	{
		throw GFX_EXCEPTION(hr, L"Creating render target view on backbuffer");
	}

	// set backbuffer as the render target using created view
	pImmediateContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), nullptr);

	// set viewport dimensions
	D3D11_VIEWPORT vp;
	vp.Width = float(ApplicationValues::Instance().ScreenWidth);
	vp.Height = float(ApplicationValues::Instance().ScreenHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pImmediateContext->RSSetViewports(1, &vp);

	// Create texture for cpu render target
	D3D11_TEXTURE2D_DESC sysTexDesc;
	sysTexDesc.Width = ApplicationValues::Instance().ScreenWidth;
	sysTexDesc.Height = ApplicationValues::Instance().ScreenHeight;
	sysTexDesc.MipLevels = 1;
	sysTexDesc.ArraySize = 1;
	sysTexDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sysTexDesc.SampleDesc.Count = 1;
	sysTexDesc.SampleDesc.Quality = 0;
	sysTexDesc.Usage = D3D11_USAGE_DYNAMIC;
	sysTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	sysTexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	sysTexDesc.MiscFlags = 0;

	// create the texture
	if (FAILED(hr = pDevice->CreateTexture2D(&sysTexDesc, nullptr, &pSysBufferTexture)))
	{
		throw GFX_EXCEPTION(hr, L"Creating sysbuffer texture");
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = sysTexDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	// create the resource view on the texture
	if (FAILED(hr = pDevice->CreateShaderResourceView(pSysBufferTexture.Get(),
		&srvDesc, &pSysBufferTextureView)))
	{
		throw GFX_EXCEPTION(hr, L"Creating view on sysBuffer texture");
	}

	// Create pixel shader for framebuffer
	if (FAILED(hr = pDevice->CreatePixelShader(
		FramebufferShaders::FramebufferPSBytecode,
		sizeof(FramebufferShaders::FramebufferPSBytecode),
		nullptr,
		&pPixelShader)))
	{
		throw GFX_EXCEPTION(hr, L"Creating pixel shader");
	}


	// Create vertex shader for framebuffer
	if (FAILED(hr = pDevice->CreateVertexShader(
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		nullptr,
		&pVertexShader)))
	{
		throw GFX_EXCEPTION(hr, L"Creating vertex shader");
	}

	// Create and fill vertex buffer with quad for rendering frame
	const FSQVertex vertices[] =
	{
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,1.0f,0.5f,1.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,-1.0f,0.5f,0.0f,1.0f },
	};
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(FSQVertex) * 6;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0u;
	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;
	if (FAILED(hr = pDevice->CreateBuffer(&bd, &initData, &pVertexBuffer)))
	{
		throw GFX_EXCEPTION(hr, L"Creating vertex buffer");
	}

	// Create input layout for fullscreen quad
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};

	if (FAILED(hr = pDevice->CreateInputLayout(ied, 2,
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		&pInputLayout)))
	{
		throw GFX_EXCEPTION(hr, L"Creating input layout");
	}

	// Create sampler state for fullscreen textured quad
	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	if (FAILED(hr = pDevice->CreateSamplerState(&sampDesc, &pSamplerState)))
	{
		throw GFX_EXCEPTION(hr, L"Creating sampler state");
	}

	std::string fontFile = "\\fonts\\italic.spritefont";
	fontFile = ApplicationValues::Instance().ResourcesPath + fontFile;
	std::wstring widestr = std::wstring(fontFile.begin(), fontFile.end());
	const wchar_t* szFile = widestr.c_str();
	mFonts.reset(new SpriteFont(pDevice.Get(), szFile));

	mSprites.reset(new SpriteBatch(pImmediateContext.Get()));
	mPrimitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(pImmediateContext.Get());
}

void DX11Graphics::DrawSprite(std::string name, Vec2 pos, RECT * rect, float rot, float scale, Vec2 offset)
{
	mSprites->Draw(mTextures.at(name), XMFLOAT2(pos.x, pos.y), rect, Colors::White, rot, XMFLOAT2(offset.x, offset.y), scale);
}

void DX11Graphics::DrawLine(Vec2 v1, Vec2 v2)
{
	VertexPositionColor vec1(XMFLOAT3(v1.x, v1.y,0), XMFLOAT4(1,0,0,0));
	VertexPositionColor vec2(XMFLOAT3(v2.x, v2.y, 0), XMFLOAT4(1, 0, 0, 0));
	mPrimitiveBatch->DrawLine(vec1, vec2);
}

void DX11Graphics::DrawText(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset)
{
	std::wstring widestr = std::wstring(text.begin(), text.end());
	const wchar_t* convertedText = widestr.c_str();

	XMVECTORF32 colour = { { { rgb[0], rgb[1], rgb[2], 1 } } };
	mFonts->DrawString(mSprites.get(), convertedText, XMFLOAT2(pos.x, pos.y), colour, rot, XMFLOAT2(offset.x, offset.y), scale);
}

void DX11Graphics::Destroy()
{
	// Clear the state of the device context before destruction
	if (pImmediateContext) pImmediateContext->ClearState();
}

void DX11Graphics::CreateShaderResourceView(std::string name)
{
	HRESULT hr;

	std::string filePath = SpriteFilePaths[name];
	filePath = ApplicationValues::Instance().ResourcesPath + filePath;

	std::wstring widestr = std::wstring(filePath.begin(), filePath.end());
	const wchar_t* szName = widestr.c_str();

	ID3D11ShaderResourceView* shaderRV = nullptr;

	hr = CreateDDSTextureFromFile(pDevice.Get(), szName, nullptr, &shaderRV);

	if (FAILED(hr))
		throw GFX_EXCEPTION(hr, L"Creating DDS texture from file.");

	mTextures.insert(std::make_pair(name, shaderRV));
}

void DX11Graphics::EndFrame()
{
	HRESULT hr;

	// Render offscreen scene texture to back buffer
	pImmediateContext->IASetInputLayout(pInputLayout.Get());
	pImmediateContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);
	pImmediateContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
	pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	const UINT stride = sizeof(FSQVertex);
	const UINT offset = 0u;
	pImmediateContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
	pImmediateContext->PSSetShaderResources(0u, 1u, pSysBufferTextureView.GetAddressOf());
	pImmediateContext->PSSetSamplers(0u, 1u, pSamplerState.GetAddressOf());
	pImmediateContext->Draw(6u, 0u);

	mSprites->End();
	mPrimitiveBatch->End();

	// Flip back/front buffers
	if (FAILED(hr = pSwapChain->Present(1u, 0u)))
	{
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			throw GFX_EXCEPTION(pDevice->GetDeviceRemovedReason(), L"Presenting back buffer [device removed]");
		}
		else
		{
			throw GFX_EXCEPTION(hr, L"Presenting back buffer");
		}
	}
}

void DX11Graphics::BeginFrame()
{
	// clear render target view
	pImmediateContext->ClearRenderTargetView(pRenderTargetView.Get(), Colors::MidnightBlue);
	mSprites->Begin(SpriteSortMode_Deferred);
	mPrimitiveBatch->Begin();
}

void DX11Graphics::PreloadTextures()
{
	for (auto& s : SpriteFilePaths)
	{
		CreateShaderResourceView(s.first);
	}
}

//           DX11Graphics Exception
DX11Graphics::Exception::Exception(HRESULT hr, const std::wstring& note, const wchar_t* file, unsigned int line)
	:
	CustomException(file, line, note),
	hr(hr)
{}

std::wstring DX11Graphics::Exception::GetFullMessage() const
{
	const std::wstring empty = L"";
	const std::wstring errorName = GetErrorName();
	const std::wstring errorDesc = GetErrorDescription();
	const std::wstring& note = GetNote();
	const std::wstring location = GetLocation();
	return    (!errorName.empty() ? std::wstring(L"Error: ") + errorName + L"\n"
		: empty)
		+ (!errorDesc.empty() ? std::wstring(L"Description: ") + errorDesc + L"\n"
			: empty)
		+ (!note.empty() ? std::wstring(L"Note: ") + note + L"\n"
			: empty)
		+ (!location.empty() ? std::wstring(L"Location: ") + location
			: empty);
}

std::wstring DX11Graphics::Exception::GetErrorName() const
{
	return DXGetErrorString(hr);
}

std::wstring DX11Graphics::Exception::GetErrorDescription() const
{
	std::array<wchar_t, 512> wideDescription;
	DXGetErrorDescription(hr, wideDescription.data(), wideDescription.size());
	return wideDescription.data();
}

std::wstring DX11Graphics::Exception::GetExceptionType() const
{
	return L"DX11Graphics Exception";
}