#include "SpriteRendererComponent.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdexcept>

#include "GameObject.h"
#include "Renderer.h"
#include "TransformComponent.h"

SpriteRendererComponent::SpriteRendererComponent(dae::GameObject* parent) :
	ComponentBase{ parent }
{
}

SpriteRendererComponent::SpriteRendererComponent(dae::GameObject* parent, const std::string& imagePath) :
	ComponentBase{ parent }, m_ImageSurface{  }, m_Texture{  }
{

	m_ImageSurface = IMG_Load(imagePath.c_str());

	printf("IMG_Load: %s\n", IMG_GetError());


	if (!m_ImageSurface)
	{
		throw std::runtime_error("Failed to load image: " + imagePath);
	}
	m_Texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), m_ImageSurface);
	if (!m_Texture)
	{
		throw std::runtime_error("Failed to create texture from surface: " + std::string(SDL_GetError()));
	}
	//SDL_FreeSurface(m_ImageSurface);
	//m_ImageSurface = nullptr;
}

SpriteRendererComponent::~SpriteRendererComponent()
{
	if (m_ImageSurface)
	{
		SDL_FreeSurface(m_ImageSurface);
		m_ImageSurface = nullptr;
	}

	if (m_Texture)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;
	}
}

void SpriteRendererComponent::Render() const
{
	SDL_Rect destRect = { static_cast<int>(GetParent()->GetWorldPosition().x), static_cast<int>(GetParent()->GetWorldPosition().y), m_ImageSurface->w, m_ImageSurface->h };
	SDL_RenderCopy(dae::Renderer::GetInstance().GetSDLRenderer(), m_Texture, nullptr, &destRect);
}

