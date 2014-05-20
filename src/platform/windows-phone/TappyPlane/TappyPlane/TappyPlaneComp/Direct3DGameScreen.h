//
//  Direct3DGameScreen.h
//  tappyplane
//
//  Created by Stephen Gowen on 1/31/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#pragma once

#include "GameScreen.h"
#include "Vector2D.h"
#include "Direct3DRenderer.h"

class Direct3DGameScreen : public GameScreen
{
public:
	Direct3DGameScreen(int deviceScreenWidth, int deviceScreenHeight);

	void load(Microsoft::WRL::ComPtr<ID3D11Device1> &d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext1> &d3dContext);

	virtual void platformInit();

	virtual void platformResume();

	virtual void platformPause();

	void present(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> &d3dContext, Microsoft::WRL::ComPtr<ID3D11RenderTargetView> &renderTargetView, Microsoft::WRL::ComPtr<ID3D11DepthStencilView> &depthStencilView);

	virtual void touchToWorld(TouchEvent &touchEvent);

	void handleSoundId();

	void unload();

	virtual bool handleOnBackPressed();

private:
	std::unique_ptr<Direct3DRenderer> m_renderer;
	float m_fGameScreenToDeviceScreenWidthRatio;
	float m_fGameScreenToDeviceScreenHeightRatio;
	float m_fDipToPixelRatio;
};