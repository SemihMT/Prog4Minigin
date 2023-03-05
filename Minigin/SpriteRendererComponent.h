#include "ComponentBase.h"
#include <SDL.h>
#include <SDL_ttf.h>

class SpriteRendererComponent final : public dae::ComponentBase {
public:
    //Basic constructor, elements need to be set before use
    SpriteRendererComponent(const dae::GameObject* parent);
    //Constructor that sets all elements of the component 
    SpriteRendererComponent(const dae::GameObject* parent,const std::string& imagePath);

    ~SpriteRendererComponent() override;
	SpriteRendererComponent(const SpriteRendererComponent& other) = delete;
	SpriteRendererComponent(SpriteRendererComponent&& other) = delete;
	SpriteRendererComponent& operator=(const SpriteRendererComponent& other) = delete;
	SpriteRendererComponent& operator=(SpriteRendererComponent&& other) = delete;

    void Render() const override;
  

private:
    SDL_Surface* m_ImageSurface = nullptr;
    SDL_Texture* m_Texture = nullptr;
};