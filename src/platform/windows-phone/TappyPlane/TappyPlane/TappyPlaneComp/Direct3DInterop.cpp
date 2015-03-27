//
//  Direct3DInterop.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "pch.h"
#include "Direct3DInterop.h"
#include "Direct3DContentProvider.h"
#include "Direct3DGameScreen.h"
#include "Vector2D.h"
#include "TouchEvent.h"
#include "Vector2D.h"
#include "Rectangle.h"
#include "Assets.h"
#include "OverlapTester.h"
#include "GameListener.h"
#include "Renderer.h"
#include "LineBatcher.h"
#include "RectangleBatcher.h"
#include "Triangle.h"
#include "Font.h"
#include "Direct3DRenderer.h"
#include "Global.h"
#include "SpriteBatcher.h"
#include "LineBatcher.h"
#include "CircleBatcher.h"
#include "GameListener.h"
#include "Rectangle.h"
#include "Circle.h"
#include "GameSound.h"
#include "ScreenState.h"
#include "GameButton.h"

#include <string.h>
#include <sstream>

// For Randomness
#include <stdlib.h>
#include <time.h>

using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Microsoft::WRL;
using namespace Windows::Phone::Graphics::Interop;
using namespace Windows::Phone::Input::Interop;

namespace TappyPlaneComp
{
	Direct3DInterop::Direct3DInterop() : m_timer(ref new BasicTimer())
	{
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
		m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
	}

	IDrawingSurfaceContentProvider^ Direct3DInterop::CreateContentProvider()
	{
		m_gameScreen = std::unique_ptr<Direct3DGameScreen>(new Direct3DGameScreen());

		ComPtr<Direct3DContentProvider> provider = Make<Direct3DContentProvider>(this);
		return reinterpret_cast<IDrawingSurfaceContentProvider^>(provider.Get());
	}

	// IDrawingSurfaceManipulationHandler
	void Direct3DInterop::SetManipulationHost(DrawingSurfaceManipulationHost^ manipulationHost)
	{
		manipulationHost->PointerPressed += ref new TypedEventHandler<DrawingSurfaceManipulationHost^, PointerEventArgs^>(this, &Direct3DInterop::OnPointerPressed);
		manipulationHost->PointerMoved += ref new TypedEventHandler<DrawingSurfaceManipulationHost^, PointerEventArgs^>(this, &Direct3DInterop::OnPointerMoved);
		manipulationHost->PointerReleased += ref new TypedEventHandler<DrawingSurfaceManipulationHost^, PointerEventArgs^>(this, &Direct3DInterop::OnPointerReleased);
	}

	bool Direct3DInterop::onBackPressed()
	{
		return m_gameScreen->handleOnBackPressed();
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
		if (renderResolution.Width != m_renderResolution.Width || renderResolution.Height != m_renderResolution.Height)
		{
			m_renderResolution = renderResolution;

			if (m_gameScreen)
			{
				m_gameScreen->updateForRenderResolutionChange(m_renderResolution.Width, m_renderResolution.Height);
				RecreateSynchronizedTexture();
			}
		}
	}

	// Event Handlers
	void Direct3DInterop::OnPointerPressed(DrawingSurfaceManipulationHost^ sender, PointerEventArgs^ args)
	{
		addTouchEventForType(DOWN, args->CurrentPoint->RawPosition.X, args->CurrentPoint->RawPosition.Y);
	}

	void Direct3DInterop::OnPointerMoved(DrawingSurfaceManipulationHost^ sender, PointerEventArgs^ args)
	{
		if (m_touchEventsBuffer.size() < 3)
		{
			addTouchEventForType(DRAGGED, args->CurrentPoint->RawPosition.X, args->CurrentPoint->RawPosition.Y);
		}
	}

	void Direct3DInterop::OnPointerReleased(DrawingSurfaceManipulationHost^ sender, PointerEventArgs^ args)
	{
		addTouchEventForType(UP, args->CurrentPoint->RawPosition.X, args->CurrentPoint->RawPosition.Y);
	}

	// Interface With Direct3DContentProvider
	HRESULT Direct3DInterop::Connect(_In_ IDrawingSurfaceRuntimeHostNative* host)
	{
		m_gameScreen->load(m_renderResolution.Width, m_renderResolution.Height, (int)WindowBounds.Width, (int)WindowBounds.Height);
		m_gameScreen->onResume();

		// Restart timer after renderer has finished initializing.
		m_timer->Reset();

		return S_OK;
	}

	void Direct3DInterop::Disconnect()
	{
		m_gameScreen->unload();
	}

	HRESULT Direct3DInterop::PrepareResources(_In_ const LARGE_INTEGER* presentTargetTime, _Out_ BOOL* contentDirty)
	{
		*contentDirty = true;

		return S_OK;
	}

	HRESULT Direct3DInterop::GetTexture(_In_ const DrawingSurfaceSizeF* size, _Out_ IDrawingSurfaceSynchronizedTextureNative** synchronizedTexture, _Out_ DrawingSurfaceRectF* textureSubRectangle)
	{
		int screenState = m_gameScreen->getState();
		switch (screenState)
		{
		case SCREEN_STATE_NORMAL:
			for (std::vector<TouchEvent>::iterator itr = m_touchEvents.begin(); itr != m_touchEvents.end(); itr++)
			{
				if (m_touchEventsPool.size() < 50)
				{
					m_touchEventsPool.push_back(*itr);
				}
			}

			m_touchEvents.clear();
			m_touchEvents.swap(m_touchEventsBuffer);
			m_touchEventsBuffer.clear();

			m_timer->Update();
			m_gameScreen->update(m_timer->Delta, m_touchEvents);
			break;
		case SCREEN_STATE_RESET:
			m_gameScreen = std::unique_ptr<Direct3DGameScreen>(new Direct3DGameScreen());
			m_gameScreen->load(m_renderResolution.Width, m_renderResolution.Height, (int)WindowBounds.Width, (int)WindowBounds.Height);
			m_gameScreen->onResume();

			// Restart timer after renderer has finished initializing.
			m_timer->Reset();
			break;
		case SCREEN_STATE_EXIT:
			// Exiting Status
			break;
		case SCREEN_STATE_GAME_OVER:
			m_gameScreen->clearState();
			m_winRtCallback->Invoke("GAME_OVER", "NULL");
			break;
		case SCREEN_STATE_LEADERBOARDS:
			m_gameScreen->clearState();
			// TODO, show Leaderboards here if you want
			break;
		default:
			break;
		}

		m_gameScreen->present();
		m_gameScreen->handleSound();

		RequestAdditionalFrame();

		return S_OK;
	}

	ID3D11Texture2D* Direct3DInterop::GetTexture()
	{
		return m_gameScreen->getTexture();
	}

	void Direct3DInterop::addTouchEventForType(Touch_Type touchType, float x, float y)
	{
		TouchEvent touchEvent = newTouchEvent();
		touchEvent.setTouchType(touchType);
		touchEvent.setX(x);
		touchEvent.setY(y);

		m_touchEventsBuffer.push_back(touchEvent);
	}

	TouchEvent Direct3DInterop::newTouchEvent()
	{
		if (m_touchEventsPool.size() == 0)
		{
			return TouchEvent(0, 0, Touch_Type::DOWN);
		}
		else
		{
			TouchEvent touchEvent = m_touchEventsPool.back();
			m_touchEventsPool.pop_back();
			return touchEvent;
		}
	}
}