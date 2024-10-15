
#include "GameplayScreen.h"
#include "MainMenuScreen.h"
#include "Level.h"
#include "Level01.h"

// Callback function

/** @brief Callback function for when the gameplay screen is removed from the screen manager.
	@param pScreen A pointer to the gameplay screen that is being removed. */
void OnGameplayScreenRemoved(Screen* pScreen)
{
	pScreen->GetScreenManager()->AddScreen(new MainMenuScreen());
}


GameplayScreen::GameplayScreen(const int levelIndex)
{
	m_levelIndex = levelIndex;

	SetTransitionInTime(1);
	SetTransitionOutTime(3);

	SetRemoveCallback(OnGameplayScreenRemoved);

	Show();
}

void GameplayScreen::LoadContent(ResourceManager& resourceManager)
{
	m_pResourceManager = &resourceManager;
	LoadLevel(m_levelIndex);
}

void GameplayScreen::LoadLevel(const int levelIndex)
{
	if (m_pLevel) delete m_pLevel;

	switch (levelIndex)
	{
	case 0: m_pLevel = new Level01(); break;
	}

	m_pLevel->SetGameplayScreen(this);
	m_pLevel->LoadContent(*m_pResourceManager);
}

void GameplayScreen::HandleInput(const InputState& input)
{
	m_pLevel->HandleInput(input);
}

void GameplayScreen::Update(const GameTime& gameTime)
{
	m_pLevel->Update(gameTime);
}

void GameplayScreen::Draw(SpriteBatch& spriteBatch)
{
	spriteBatch.Begin();

	m_pLevel->Draw(spriteBatch);

	spriteBatch.End();
}
