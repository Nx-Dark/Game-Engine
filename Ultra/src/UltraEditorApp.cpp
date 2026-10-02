#include <Dark.h>
#include <Dark/Core/EntryPoint.h>

#include "UltraEditorLayer.h""

namespace Dark {

	class UltraEditor : public Application
	{

	public:
		UltraEditor(const std::string& appName, uint32_t width, uint32_t height)
			: Application(appName, width, height)
		{
			PushLayer(new UltraEditorLayer());
		}
		~UltraEditor()
		{

		}

	};

	Dark::Application* Dark::CreateApplication()
	{
		return new UltraEditor("DarkEngine-UltraEditor", 1280, 720);

	}
}