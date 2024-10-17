
/*
     ██╗  ██╗  █████╗  ████████╗  █████╗  ███╗   ██╗  █████╗ 
	 ██║ ██╔╝ ██╔══██╗ ╚══██╔══╝ ██╔══██╗ ████╗  ██║ ██╔══██╗
	 █████╔╝  ███████║    ██║    ███████║ ██╔██╗ ██║ ███████║
	 ██╔═██╗  ██╔══██║    ██║    ██╔══██║ ██║╚██╗██║ ██╔══██║
	 ██║  ██╗ ██║  ██║    ██║    ██║  ██║ ██║ ╚████║ ██║  ██║
	 ╚═╝  ╚═╝ ╚═╝  ╚═╝/\  ╚═╝    ╚═╝  ╚═╝ ╚═╝  ╚═══╝ ╚═╝  ╚═╝
   /vvvvvvvvvvvvvvvvvvv \=========================================,
   `^^^^^^^^^^^^^^^^^^^ /---------------------------------------"
        Katana Engine \/ © 2012 - Shuriken Studios LLC
			    http://www.shurikenstudios.com
*/

#include "KatanaEngine.h"

namespace KatanaEngine
{
	ScreenManager::ScreenManager(Game *pGame)
	{
		m_pGame = pGame;
	}

	ResourceManager *ScreenManager::GetResourceManager() const
	{
		return GetGame()->GetResourceManager();
	}

	void ScreenManager::HandleInput(const InputState& input)
	{
		if (m_screens.size() > 0)
		{
			bool update = true;

			for (m_rit = m_screens.rbegin(); m_rit != m_screens.rend(); ++m_rit)
			{
				Screen *pScreen = *m_rit;

				if (update)
				{
					if (pScreen->NeedsToBeRemoved()) continue;
					pScreen->HandleInput(input);
					update = pScreen->ShouldHandleInputBelow();
				}
				else break;
			}
		}
	}

	void ScreenManager::Update(const GameTime& gameTime)
	{
		Screen *pScreen;

		if (m_screensToAdd.size() > 0)
		{
			m_screens.insert(m_screens.end(), m_screensToAdd.begin(), m_screensToAdd.end());
			m_screensToAdd.clear();
		}

		if (m_screens.size() > 0)
		{
			bool update = true;

			for (m_rit = m_screens.rbegin(); m_rit != m_screens.rend(); ++m_rit)
			{
				pScreen = *m_rit;

				pScreen->UpdateTransition(gameTime);

				if (pScreen->NeedsToBeRemoved())
				{
					m_screensToRemove.push_back(pScreen);
				}
				else if (update)
				{
					pScreen->Update(gameTime);
					update = pScreen->ShouldUpdateBelow();
				}
			}
		}

		if (m_screensToRemove.size() > 0)
		{
			for (m_it = m_screensToRemove.begin(); m_it != m_screensToRemove.end(); ++m_it)
			{
				pScreen = *m_it;

				if (pScreen->m_onRemove) ((OnRemove)pScreen->m_onRemove)();

				pScreen->UnloadContent();

				m_screens.erase(std::remove(m_screens.begin(), m_screens.end(), pScreen), m_screens.end());

				delete pScreen;
			}

			m_screensToRemove.clear();
		}
	}

	void ScreenManager::Draw(SpriteBatch& spriteBatch)
	{
		Screen *pScreen;
		if (m_screens.size() > 0)
		{
			for (m_rit = m_screens.rbegin(); m_rit != m_screens.rend(); ++m_rit)
			{
				pScreen = *m_rit;
				if (pScreen->NeedsToBeRemoved()) continue;
				m_screensToDraw.push_back(pScreen);
				if (!pScreen->ShouldDrawBelow()) break;
			}
		}

		if (m_screensToDraw.size() > 0)
		{
			for (m_rit = m_screensToDraw.rbegin(); m_rit != m_screensToDraw.rend(); ++m_rit)
			{
				Screen *pScreen = *m_rit;
				RenderTarget *pRenderTarget = pScreen->GetRenderTarget();

				if (pRenderTarget) RenderTarget::Set(pRenderTarget);

				(*m_rit)->Draw(spriteBatch);

				if (pRenderTarget)
				{
					RenderTarget::Set(nullptr);
					spriteBatch.Begin();
					spriteBatch.Draw(pRenderTarget, Vector2::ZERO, pScreen->GetRenderTargetColor());
					spriteBatch.End();
				}
			}

			m_screensToDraw.clear();
		}
	}

	void ScreenManager::AddScreen(Screen *pScreen)
	{
		pScreen->SetScreenManager(*this);
		pScreen->LoadContent(*GetResourceManager());

		m_screensToAdd.push_back(pScreen);
	}
}