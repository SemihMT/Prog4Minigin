#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Commands.h"
#include "InputManager.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	

	 /*=== BACKGROUND ===*/

	//Creating the Background
	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<TransformComponent>(glm::vec3{0,0,0});
	std::string img = "../Data/background.tga";
	go->AddComponent<SpriteRendererComponent>(img);
	scene.Add(go);
	go->SetParent(nullptr,false);

	/*=== DAE LOGO ===*/

	//Creating the Logo
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<TransformComponent>(glm::vec3{320 - 103,240 - 24,0}); //need to change hardcoded values
	img = "../Data/logo.tga";
	go->AddComponent<SpriteRendererComponent>(img);
	scene.Add(go);
	go->SetParent(nullptr,false);

	/*=== STATIC TEXT ===*/

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
	go->SetParent(nullptr,false);

	/*=== FPS COUNTER ===*/

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
	go->SetParent(nullptr,false);



	////Creating the Parent
	//auto parent = std::make_shared<dae::GameObject>();
	//parent->AddComponent<TransformComponent>(glm::vec3{320,240,0}); //need to change hardcoded values
	//img = "../Data/RocketShip.png";
	//parent->AddComponent<SpriteRendererComponent>(img);
	//parent->AddComponent<CircularMovementComponent>(25,5, glm::vec2{160,120});
	//scene.Add(parent);

	////Creating the Child
	//auto child = std::make_shared<dae::GameObject>();
	//child->AddComponent<TransformComponent>(glm::vec3{320,240,0}); //need to change hardcoded values
	//img = "../Data/Alien.png";
	//child->AddComponent<SpriteRendererComponent>(img);
	//child->AddComponent<CircularMovementComponent>(25,2);
	//scene.Add(child);

	//child->SetParent(parent.get(),false);


	/*auto UItest = std::make_shared<dae::GameObject>();
	UItest->AddComponent<TrashTheCacheComponent>();
	scene.Add(UItest);*/

	auto MovementTestP1 = std::make_shared<dae::GameObject>();
	MovementTestP1->AddComponent<TransformComponent>(glm::vec3{320,240,0}); //need to change hardcoded values
	img = "../Data/RocketShip.png";
	MovementTestP1->AddComponent<SpriteRendererComponent>(img);
	scene.Add(MovementTestP1);

	auto MovementTestP2 = std::make_shared<dae::GameObject>();
	MovementTestP2->AddComponent<TransformComponent>(glm::vec3{320,240,0}); //need to change hardcoded values
	img = "../Data/Alien.png";
	MovementTestP2->AddComponent<SpriteRendererComponent>(img);
	scene.Add(MovementTestP2);


	auto controller0 = dae::InputManager::GetInstance().AddController();
	//auto controller1 = dae::InputManager::GetInstance().AddController();
	//moves with dpad
	dae::InputManager::GetInstance().AddCommand(controller0,dae::XInputController::Button::DPAD_LEFT,std::make_unique<MoveDpadCommand>(MovementTestP1.get(),glm::vec2{-1,0},5.0f));
	dae::InputManager::GetInstance().AddCommand(controller0,dae::XInputController::Button::DPAD_RIGHT,std::make_unique<MoveDpadCommand>(MovementTestP1.get(),glm::vec2{1,0},5.0f));
	dae::InputManager::GetInstance().AddCommand(controller0,dae::XInputController::Button::DPAD_UP,std::make_unique<MoveDpadCommand>(MovementTestP1.get(),glm::vec2{0,1},5.0f));
	dae::InputManager::GetInstance().AddCommand(controller0,dae::XInputController::Button::DPAD_DOWN,std::make_unique<MoveDpadCommand>(MovementTestP1.get(),glm::vec2{0,-1},5.0f));

	//moves with arrow keys
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_A,std::make_unique<MoveKeyboardCommand>(MovementTestP2.get(),glm::vec2{-1,0},2.5f));
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_D,std::make_unique<MoveKeyboardCommand>(MovementTestP2.get(),glm::vec2{1,0},2.5f));
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_S,std::make_unique<MoveKeyboardCommand>(MovementTestP2.get(),glm::vec2{0,-1},2.5f));
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_W,std::make_unique<MoveKeyboardCommand>(MovementTestP2.get(),glm::vec2{0,1},2.5f));

}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}