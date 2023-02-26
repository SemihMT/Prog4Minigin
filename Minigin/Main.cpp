#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Creating the gameObject
	auto go = std::make_shared<dae::GameObject>();

	//Adding a transform component
	go->AddComponent<TransformComponent>(glm::vec3{10,10,0});

	//Defining text stuff
	std::string fontPath = "Resources/LiberationSans-Regular.ttf";
	int fontSize = 24;
	std::string text = "Hello, world!";
	SDL_Color color = { 255, 255, 0, 255 };

	//Adding the text renderer to our gameObject and passing it the parameters
	go->AddComponent<TextRendererComponent>(fontPath, fontSize, text, color);
	//Adding the fps calculator
	go->AddComponent<FPSCalculatorComponent>();
	//adding the gameObject to the scene
	scene.Add(go);

}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}