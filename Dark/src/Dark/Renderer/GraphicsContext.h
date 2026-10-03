#pragma once

namespace Dark {

	//interface for the Graphics context, to be implemented by the respective context creators for the specific APIs
	class GraphicsContext {

	public:

		virtual ~GraphicsContext() = default;
		
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

	};

}