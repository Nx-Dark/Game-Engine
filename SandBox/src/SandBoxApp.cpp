#include <Dark.h>
#include <Dark/Core/EntryPoint.h>

#include "SandBox2D.h"

class SandBox : public Dark::Application
{

public:
	SandBox() 
	{

		PushLayer(new SandBox2D());

	}
	~SandBox() 
	{
		
	}

};

Dark::Application* Dark::CreateApplication() 
{
	return new SandBox();

}