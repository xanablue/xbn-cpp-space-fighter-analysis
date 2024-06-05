
#include <string>
#include "MainMenuScreen.h"
#include "GameplayScreen.h"

// Callback Functions

/** @brief Callback function for when the Start Game menu item is selected.
	@param pScreen A pointer to the menu screen that contains the menu item. */
void OnStartGameSelect(MenuScreen *pScreen)
{
	pScreen->Exit();
}

/** @brief Callback function for when the Quit menu item is selected.
	@param pScreen A pointer to the menu screen that contains the menu item. */
void OnQuitSelect(MenuScreen *pScreen)
{
	MainMenuScreen *pMainMenuScreen = (MainMenuScreen *)pScreen;
	pMainMenuScreen->SetQuittingGame();
	pScreen->Exit();
}

/** @brief Callback function for when the main menu screen is removed from the screen manager.
	@param pScreen A pointer to the menu screen that contains the menu item. */
void OnMainMenuScreenRemoved(Screen *pScreen)
{
	MainMenuScreen *pMainMenuScreen = (MainMenuScreen *)pScreen;

	if (pMainMenuScreen->IsQuittingGame()) {
		pScreen->GetGame()->Quit();
		return;
	}

	pScreen->GetScreenManager()->AddScreen(new GameplayScreen());
}


MainMenuScreen::MainMenuScreen()
{
	SetRemoveCallback(OnMainMenuScreenRemoved);

	SetTransitionInTime(1);
	SetTransitionOutTime(0.5f);

	Show(); // Show the screen
}

void MainMenuScreen::LoadContent(ResourceManager *pResourceManager)
{
	// Logo
	m_pTexture = pResourceManager->Load<Texture>("Textures\\Logo.png");
	m_texturePosition = Game::GetScreenCenter() - Vector2::UNIT_Y * 150;

	// Create the menu items
	const int COUNT = 2;
	MenuItem *pItem;
	Font::SetLoadSize(20, true);
	Font *pFont = pResourceManager->Load<Font>("Fonts\\arial.ttf");

	SetDisplayCount(COUNT);

	enum Items { START_GAME, QUIT };
	std::string text[COUNT] = { "Start Game", "Quit" };

	for (int i = 0; i < COUNT; i++)
	{
		pItem = new MenuItem(text[i]);
		pItem->SetPosition(Vector2(100, 100 + 50 * i));
		pItem->SetFont(pFont);
		pItem->SetColor(Color::Blue);
		pItem->SetSelected(i == 0);
		AddMenuItem(pItem);
	}

	GetMenuItem(START_GAME)->SetSelectCallback(OnStartGameSelect);
	GetMenuItem(QUIT)->SetSelectCallback(OnQuitSelect);
}

void MainMenuScreen::Update(const GameTime *pGameTime)
{
	MenuItem *pItem;

	// Set the menu item colors
	for (int i = 0; i < GetDisplayCount(); i++)
	{
		pItem = GetMenuItem(i);
		pItem->SetAlpha(GetAlpha());

		if (pItem->IsSelected()) pItem->SetColor(Color::White);
		else pItem->SetColor(Color::Blue);
	}

	MenuScreen::Update(pGameTime);
}

void MainMenuScreen::Draw(SpriteBatch *pSpriteBatch)
{
	pSpriteBatch->Begin();
	pSpriteBatch->Draw(m_pTexture, m_texturePosition, Color::White * GetAlpha(), m_pTexture->GetCenter());
	pSpriteBatch->End();

	MenuScreen::Draw(pSpriteBatch);
}
