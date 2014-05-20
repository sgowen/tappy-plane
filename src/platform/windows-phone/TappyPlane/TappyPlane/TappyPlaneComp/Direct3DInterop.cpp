#include "pch.h"
#include "Direct3DInterop.h"
#include "Direct3DContentProvider.h"
#include "GameButton.h"
#include <string.h>

using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Microsoft::WRL;
using namespace Windows::Phone::Graphics::Interop;
using namespace Windows::Phone::Input::Interop;

namespace TappyPlaneComp
{
	Direct3DInterop::Direct3DInterop() : m_timer(ref new BasicTimer())
	{
	}

	IDrawingSurfaceContentProvider^ Direct3DInterop::CreateContentProvider()
	{
		m_gameScreen = std::unique_ptr<Direct3DGameScreen>(new Direct3DGameScreen((int)NativeResolution.Width, (int)NativeResolution.Height));

		ComPtr<Direct3DContentProvider> provider = Make<Direct3DContentProvider>(this);
		return reinterpret_cast<IDrawingSurfaceContentProvider^>(provider.Detach());
	}

	// IDrawingSurfaceManipulationHandler
	void Direct3DInterop::SetManipulationHost(DrawingSurfaceManipulationHost^ manipulationHost)
	{
		manipulationHost->PointerPressed +=
			ref new TypedEventHandler<DrawingSurfaceManipulationHost^, PointerEventArgs^>(this, &Direct3DInterop::OnPointerPressed);

		manipulationHost->PointerMoved +=
			ref new TypedEventHandler<DrawingSurfaceManipulationHost^, PointerEventArgs^>(this, &Direct3DInterop::OnPointerMoved);

		manipulationHost->PointerReleased +=
			ref new TypedEventHandler<DrawingSurfaceManipulationHost^, PointerEventArgs^>(this, &Direct3DInterop::OnPointerReleased);
	}

	bool Direct3DInterop::onBackPressed()
	{
		return m_gameScreen->handleOnBackPressed();
	}

	void Direct3DInterop::setBestScore(int bestScore)
	{
		m_gameScreen->setBestScore(bestScore);
	}

	int Direct3DInterop::getScore()
	{
		return m_gameScreen->getScore();
	}

	void Direct3DInterop::setWinRtCallback(WinRtCallback^ callback)
	{
		m_winRtCallback = callback;
	}

	void Direct3DInterop::RenderResolution::set(Windows::Foundation::Size renderResolution)
	{
		if (renderResolution.Width != m_renderResolution.Width ||
			renderResolution.Height != m_renderResolution.Height)
		{
			m_renderResolution = renderResolution;

			if (m_direct3DBase)
			{
				m_direct3DBase->UpdateForRenderResolutionChange(m_renderResolution.Width, m_renderResolution.Height);
				RecreateSynchronizedTexture();
			}
		}
	}

	void Direct3DInterop::screenType::set(int screenType)
	{
		m_screenType = screenType;
	}

	// Event Handlers
	void Direct3DInterop::OnPointerPressed(DrawingSurfaceManipulationHost^ sender, PointerEventArgs^ args)
	{
		m_direct3DBase->touchDown(args->CurrentPoint->RawPosition.X, args->CurrentPoint->RawPosition.Y);
	}

	void Direct3DInterop::OnPointerMoved(DrawingSurfaceManipulationHost^ sender, PointerEventArgs^ args)
	{
		m_direct3DBase->touchDragged(args->CurrentPoint->RawPosition.X, args->CurrentPoint->RawPosition.Y);
	}

	void Direct3DInterop::OnPointerReleased(DrawingSurfaceManipulationHost^ sender, PointerEventArgs^ args)
	{
		m_direct3DBase->touchUp(args->CurrentPoint->RawPosition.X, args->CurrentPoint->RawPosition.Y);
	}

	// Interface With Direct3DContentProvider
	HRESULT Direct3DInterop::Connect(_In_ IDrawingSurfaceRuntimeHostNative* host)
	{
		m_direct3DBase = ref new Direct3DBase();
		m_direct3DBase->Initialize();
		m_direct3DBase->loadScreen(*m_gameScreen);
		m_direct3DBase->UpdateForWindowSizeChange(WindowBounds.Width, WindowBounds.Height);
		m_direct3DBase->UpdateForRenderResolutionChange(m_renderResolution.Width, m_renderResolution.Height);

		// Restart timer after renderer has finished initializing.
		m_timer->Reset();

		return S_OK;
	}

	void Direct3DInterop::Disconnect()
	{
		m_gameScreen->unload();
		m_direct3DBase = nullptr;
	}

	HRESULT Direct3DInterop::PrepareResources(_In_ const LARGE_INTEGER* presentTargetTime, _Out_ BOOL* contentDirty)
	{
		*contentDirty = true;

		return S_OK;
	}

	HRESULT Direct3DInterop::GetTexture(_In_ const DrawingSurfaceSizeF* size, _Out_ IDrawingSurfaceSynchronizedTextureNative** synchronizedTexture, _Out_ DrawingSurfaceRectF* textureSubRectangle)
	{
		int gameState = m_gameScreen->getState();
		if (gameState == 0)
		{
			m_timer->Update();
			m_direct3DBase->Update(*m_gameScreen, m_timer->Delta);
		}
		else if (gameState == 1)
		{
			m_gameScreen = std::unique_ptr<Direct3DGameScreen>(new Direct3DGameScreen((int)NativeResolution.Width, (int)NativeResolution.Height));
			m_direct3DBase->loadScreen(*m_gameScreen);
		}
		else if (gameState == 2)
		{
			// Exiting Status
		}
		else if (gameState == 3)
		{
			m_gameScreen->clearState();
			m_winRtCallback->Invoke("GAME_OVER", "NULL");
		}
		else if (gameState == 4)
		{
			m_gameScreen->clearState();
			// TODO, show Leaderboards here if you want
		}

		m_direct3DBase->Render(*m_gameScreen);

		RequestAdditionalFrame();

		return S_OK;
	}

	ID3D11Texture2D* Direct3DInterop::GetTexture()
	{
		return m_direct3DBase->GetTexture();
	}
}