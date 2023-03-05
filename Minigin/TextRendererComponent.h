#pragma once
#include "ComponentBase.h"
#include <SDL.h>
#include <SDL_ttf.h>

class TextRendererComponent final : public dae::ComponentBase {
public:
    //Basic constructor, elements need to be set before use
    TextRendererComponent(const dae::GameObject* parent);
    //Constructor that sets all elements of the component 
    TextRendererComponent(const dae::GameObject* parent,const std::string& fontPath, int fontSize, const std::string& text, SDL_Color color);

    ~TextRendererComponent() = default;
	TextRendererComponent(const TextRendererComponent& other) = delete;
	TextRendererComponent(TextRendererComponent&& other) = delete;
	TextRendererComponent& operator=(const TextRendererComponent& other) = delete;
	TextRendererComponent& operator=(TextRendererComponent&& other) = delete;

    void Update(float ) override {}
    void Render() const override;
    void SetFontPath(std::string& fontPath);
    void SetText(std::string& text);
    void SetColor(SDL_Color& color);
    void SetSize(int fontSize);

private:
    std::string m_FontPath;
    int m_FontSize;
    std::string m_Text;
    SDL_Color m_Color;
};
