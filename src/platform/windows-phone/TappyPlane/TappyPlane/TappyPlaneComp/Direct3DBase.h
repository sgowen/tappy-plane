#pragma once

#include "DirectXHelper.h"
#include "Direct3DGameScreen.h"
#include "TouchEvent.h"

// Helper class that initializes DirectX APIs for 3D rendering.
ref class Direct3DBase sealed
{
internal:
	Direct3DBase();

	void loadScreen(Direct3DGameScreen &screen);

	void Update(Direct3DGameScreen &gameScreen, float timeDelta);

	void Render(Direct3DGameScreen &gameScreen);

public:
	void touchDown(float x, float y);
	void touchDragged(float x, float y);
	void touchUp(float x, float y);

	virtual void Initialize();
	virtual void CreateDeviceResources();
	virtual void CreateWindowSizeDependentResources();
	virtual void UpdateForRenderResolutionChange(float width, float height);
	virtual void UpdateForWindowSizeChange(float width, float height);
	virtual void cleanUp();

internal:
	virtual ID3D11Texture2D* GetTexture()
	{
		return m_renderTarget.Get();
	}

protected private:
	// Direct3D Objects.
	Microsoft::WRL::ComPtr<ID3D11Device1> m_d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_d3dContext;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_renderTarget;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

	// Cached renderer properties.
	D3D_FEATURE_LEVEL m_featureLevel;
	Windows::Foundation::Size m_renderTargetSize;
	Windows::Foundation::Rect m_windowBounds;

private:
	std::vector<TouchEvent> m_touchEvents;
	std::vector<TouchEvent> m_touchEventsPool;
	std::vector<TouchEvent> m_touchEventsBuffer;

	void addTouchEventForType(Touch_Type touchType, float x, float y);

	TouchEvent newTouchEvent();
};