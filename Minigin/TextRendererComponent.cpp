#include "TextRendererComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "TransformComponent.h"

TextRendererComponent::TextRendererComponent(dae::GameObject* parent) :
 ComponentBase{parent}
{
}

TextRendererComponent::TextRendererComponent(dae::GameObject* parent, const std::string& fontPath, int fontSize,
                                             const std::string& text, SDL_Color color):ComponentBase{parent}, m_FontPath(fontPath), m_FontSize(fontSize), m_Text(text), m_Color(color)
{
	
}

void TextRendererComponent::Render() const
{
	auto rdr = dae::Renderer::GetInstance().GetSDLRenderer();
	// Load font and render text surface
	TTF_Font* font = TTF_OpenFont(m_FontPath.c_str(), m_FontSize);
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, m_Text.c_str(), m_Color);
	// Create texture from surface and render it to the screen
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rdr, textSurface);
	SDL_Rect textRect = { static_cast<int>(GetParent()->GetComponent<TransformComponent>()->GetLocalPosition().x), static_cast<int>(GetParent()->GetComponent<TransformComponent>()->GetLocalPosition().y), textSurface->w, textSurface->h };
	SDL_RenderCopy(rdr, textTexture, nullptr, &textRect);

	// Clean up resources
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
}

void TextRendererComponent::SetFontPath(std::string& fontPath)
{
	m_FontPath = fontPath;
}

void TextRendererComponent::SetText(std::string& text)
{
	m_Text = text;
}

void TextRendererComponent::SetColor(SDL_Color& color)
{
	m_Color = color;
}

void TextRendererComponent::SetSize(int fontSize)
{
	m_FontSize = fontSize;
}
