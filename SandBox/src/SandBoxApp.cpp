#include <Dark.h>
#include <Dark/Core/EntryPoint.h>

#include "SandBox2D.h""

class SandBox : public Dark::Application
{

public:
	SandBox(const std::string& appName, uint32_t width, uint32_t height) 
	{
		PushLayer(new SandBox2D());
	}
	~SandBox() 
	{
		
	}

};

Dark::Application* Dark::CreateApplication() 
{
	return new SandBox("Game", 960u, 540u);

}