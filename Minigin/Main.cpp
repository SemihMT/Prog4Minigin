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

	 

	//Creating the Background
	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<TransformComponent>(glm::vec3{0,0,0});
	std::string img = "../Data/background.tga";
	go->AddComponent<SpriteRendererComponent>(img);
	scene.Add(go);

	//Creating the Logo
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<TransformComponent>(glm::vec3{320 - 103,240 - 24,0}); //need to change hardcoded values
	img = "../Data/logo.tga";
	go->AddComponent<SpriteRendererComponent>(img);
	scene.Add(go);


	//Creating the FPSCounter
	go = std::make_shared<dae::GameObject>();
	//Adding a transform component
	go->AddComponent<TransformComponent>(glm::vec3{100,25,0});

	//Defining text stuff
	std::string fontPath = "../Data/Lingua.otf";
	int fontSize = 36;
	std::string text = "Programming 4 Assignment";
	SDL_Color color = { 255, 255, 255, 255 };

	//Adding the text renderer to our gameObject and passing it the parameters
	go->AddComponent<TextRendererComponent>(fontPath, fontSize, text, color);
	//adding the gameObject to the scene
	scene.Add(go);


	//Creating the FPSCounter
	go = std::make_shared<dae::GameObject>();
	//Adding a transform component
	go->AddComponent<TransformComponent>(glm::vec3{10,10,0});

	//Defining text stuff
	fontPath = "../Data/Lingua.otf";
	fontSize = 18;
	text = "Hello, world!";
	color = { 255, 255, 0, 255 };

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