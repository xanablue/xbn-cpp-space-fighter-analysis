
#include <string>
#include "MainMenuScreen.h"
#include "GameplayScreen.h"


MainMenuScreen::MainMenuScreen()
{
	// when the screen is removed, quit the game
	SetRemoveCallback([this](){ GetGame()->Quit(); });

	SetTransitionInTime(1);
	SetTransitionOutTime(0.5f);

	Show();
}

void MainMenuScreen::LoadContent(ResourceManager& resourceManager)
{
	// Logo
	m_pTexture = resourceManager.Load<Texture>("Textures\\Logo.png");
	m_texturePosition = Game::GetScreenCenter() - Vector2::UNIT_Y * 150;

	// Create the menu items
	const int COUNT = 2;
	MenuItem *pItem;
	Font::SetLoadSize(20, true);
	Font *pFont = resourceManager.Load<Font>("Fonts\\arial.ttf");

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

	// when "Start Game" is selected, replace the "SetRemoveCallback" delegate
	// so that it doesn't quit the game (originally set in the constructor)
	GetMenuItem(START_GAME)->SetSelectCallback([this](){
		SetRemoveCallback([this](){
			GetScreenManager()->AddScreen(new GameplayScreen());
		});

		Exit();
	});

	// bind the Exit method to the quit menu item
	GetMenuItem(QUIT)->SetSelectCallback(std::bind(&MainMenuScreen::Exit, this));
}

void MainMenuScreen::Update(const GameTime& gameTime)
{
	MenuItem *pItem;

	// Set the menu item colors
	for (int i = 0; i < GetDisplayCount(); i++)
	{
		pItem = GetMenuItem(i);
		pItem->SetAlpha(GetAlpha());
		pItem->SetColor(pItem->IsSelected() ? Color::White : Color::Blue);
	}

	MenuScreen::Update(gameTime);
}

void MainMenuScreen::Draw(SpriteBatch& spriteBatch)
{
	spriteBatch.Begin();
	spriteBatch.Draw(m_pTexture, m_texturePosition, Color::White * GetAlpha(), m_pTexture->GetCenter());
	spriteBatch.End();

	MenuScreen::Draw(spriteBatch);
}
