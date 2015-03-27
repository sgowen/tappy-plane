//
//  Direct3DContentProvider.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2014 Gowen Game Dev. All rights reserved.
//

#pragma once

#include "pch.h"
#include <wrl/module.h>
#include <Windows.Phone.Graphics.Interop.h>
#include <DrawingSurfaceNative.h>
#include "Direct3DInterop.h"

class Direct3DContentProvider : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::WinRtClassicComMix>, ABI::Windows::Phone::Graphics::Interop::IDrawingSurfaceContentProvider, IDrawingSurfaceContentProviderNative>
{
public:
	Direct3DContentProvider(TappyPlaneComp::Direct3DInterop^ controller);

	void ReleaseD3DResources();

	// IDrawingSurfaceContentProviderNative
	HRESULT STDMETHODCALLTYPE Connect(_In_ IDrawingSurfaceRuntimeHostNative* host);
	void STDMETHODCALLTYPE Disconnect();

	HRESULT STDMETHODCALLTYPE PrepareResources(_In_ const LARGE_INTEGER* presentTargetTime, _Out_ BOOL* contentDirty);
	HRESULT STDMETHODCALLTYPE GetTexture(_In_ const DrawingSurfaceSizeF* size, _Out_ IDrawingSurfaceSynchronizedTextureNative** synchronizedTexture, _Out_ DrawingSurfaceRectF* textureSubRectangle);

private:
	HRESULT InitializeTexture(_In_ const DrawingSurfaceSizeF* size);

	TappyPlaneComp::Direct3DInterop^ m_controller;
	Microsoft::WRL::ComPtr<IDrawingSurfaceRuntimeHostNative> m_host;
	Microsoft::WRL::ComPtr<IDrawingSurfaceSynchronizedTextureNative> m_synchronizedTexture;
};