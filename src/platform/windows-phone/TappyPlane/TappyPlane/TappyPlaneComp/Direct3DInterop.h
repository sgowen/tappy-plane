#pragma once

#include "pch.h"
#include "BasicTimer.h"
#include "Direct3DBase.h"
#include "Direct3DGameScreen.h"
#include <DrawingSurfaceNative.h>

namespace TappyPlaneComp
{
	public delegate void RequestAdditionalFrameHandler();
	public delegate void RecreateSynchronizedTextureHandler();
	public delegate void WinRtCallback(Platform::String^ command, Platform::String^ param);

	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Direct3DInterop sealed : public Windows::Phone::Input::Interop::IDrawingSurfaceManipulationHandler
	{
	public:
		Direct3DInterop();

		Windows::Phone::Graphics::Interop::IDrawingSurfaceContentProvider^ CreateContentProvider();

		// IDrawingSurfaceManipulationHandler
		virtual void SetManipulationHost(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ manipulationHost);

		event RequestAdditionalFrameHandler^ RequestAdditionalFrame;
		event RecreateSynchronizedTextureHandler^ RecreateSynchronizedTexture;

		bool onBackPressed();

		void setBestScore(int bestScore);

		int getScore();

		// Add callback method here to be invoked when achievements are earned
		void setWinRtCallback(WinRtCallback^ callback);

		property int screenType
		{
			int get(){ return m_screenType; }
			void set(int screenType);
		}

		property Windows::Foundation::Size WindowBounds;
		property Windows::Foundation::Size NativeResolution;
		property Windows::Foundation::Size RenderResolution
		{
			Windows::Foundation::Size get(){ return m_renderResolution; }
			void set(Windows::Foundation::Size renderResolution);
		}

	protected:
		// Event Handlers
		void OnPointerPressed(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);
		void OnPointerMoved(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);
		void OnPointerReleased(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);

	internal:
		HRESULT STDMETHODCALLTYPE Connect(_In_ IDrawingSurfaceRuntimeHostNative* host);
		void STDMETHODCALLTYPE Disconnect();
		HRESULT STDMETHODCALLTYPE PrepareResources(_In_ const LARGE_INTEGER* presentTargetTime, _Out_ BOOL* contentDirty);
		HRESULT STDMETHODCALLTYPE GetTexture(_In_ const DrawingSurfaceSizeF* size, _Out_ IDrawingSurfaceSynchronizedTextureNative** synchronizedTexture, _Out_ DrawingSurfaceRectF* textureSubRectangle);
		ID3D11Texture2D* GetTexture();

	private:
		WinRtCallback^ m_winRtCallback;
		std::unique_ptr<Direct3DGameScreen> m_gameScreen;
		Direct3DBase^ m_direct3DBase;
		BasicTimer^ m_timer;
		Windows::Foundation::Size m_renderResolution;
		int m_screenType;
	};
}