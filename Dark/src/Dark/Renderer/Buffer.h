#pragma once

namespace Dark {

	//not really the actual shader type, but the types of the datat that's being sent to the shader/gpu
	//or the types of the data grouped in the vertex buffers
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Uint, Uint2, Uint3, Uint4, Mat3, Mat4, Bool
	};

	//return sthe size of the data types
	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::None:		return 0;
			case ShaderDataType::Float:		return sizeof(float);
			case ShaderDataType::Float2:	return 2 * sizeof(float);
			case ShaderDataType::Float3:	return 3 * sizeof(float);
			case ShaderDataType::Float4:	return 4 * sizeof(float);
			case ShaderDataType::Int:		return sizeof(int);
			case ShaderDataType::Int2:		return 2 * sizeof(int);
			case ShaderDataType::Int3:		return 3 * sizeof(int);
			case ShaderDataType::Int4:		return 4 * sizeof(int);
			case ShaderDataType::Uint:		return sizeof(uint32_t);
			case ShaderDataType::Uint2:		return 2 * sizeof(uint32_t);
			case ShaderDataType::Uint3:		return 3 * sizeof(uint32_t);
			case ShaderDataType::Uint4:		return 4 * sizeof(uint32_t);
			case ShaderDataType::Mat3:		return 9 * sizeof(float);
			case ShaderDataType::Mat4:		return 16 * sizeof(float);
		}

		DARK_CORE_ASSERT(false, "Unknown ShaderDataType!");

		return 0;
	}

	//buffer element, it specifices how data is laid out in the Vertex Buffer Object in GPU, each element refers to a single type
	//and the size of it and the offset determines where the specific data or the buffer starts in the Vertex Buffer
	struct BufferElement
	{

		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;
		bool Normalized;

		//default constructor
		BufferElement() = default;

		BufferElement(const std::string& c_Name, ShaderDataType c_Type, bool c_Normalized = false)
			: name{ c_Name }, type{ c_Type }, size{ ShaderDataTypeSize(c_Type) }, offset{0}, Normalized(c_Normalized)
		{
		}

		//component count is the no of components or value a specific type holds
		//its required for opengl and other rendering APIs;
		uint32_t GetComponentCount() const
		{
			switch (type)
			{
				case ShaderDataType::Float:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				case ShaderDataType::Mat3:    return 9;
				case ShaderDataType::Mat4:    return 9;
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;
				case ShaderDataType::Uint:	  return 1;
				case ShaderDataType::Uint2:	  return 2;
				case ShaderDataType::Uint3:   return 3;
				case ShaderDataType::Uint4:   return 4;
				case ShaderDataType::Bool:    return 1;
			}

			DARK_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	//Layout is a collection of all the Elements in the Buffer
	class BufferLayout
	{

	private:

		std::vector<BufferElement> m_Elements{};

		uint32_t m_Stride{};

	public:
		//default constructor
		BufferLayout() = default;

		BufferLayout(std::initializer_list<BufferElement> elements)
			: m_Elements{ elements } {

			CalculateOffsetAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }

		inline std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		inline std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		inline std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		inline std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetAndStride() {
			m_Stride = 0;
			uint32_t offset{};
			for (BufferElement& e : m_Elements) {
				e.offset = offset;
				offset += e.size;
				m_Stride += e.size;
			}
		}
	};

	//VertexBuffer Interface, to be implemented by the platform specific rendering APIs to be set up by them
	class VertexBuffer 
	{
		
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		virtual void UploadData(const void* data, uint32_t size) = 0;

		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(const void* vertices, uint32_t size);
	};


	//index buffer interface, to be implemented by the platform specific rendering APIs and to be set up by them
	class IndexBuffer
	{

	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		virtual void UploadData(const void* data, uint32_t count) = 0;

		static Ref<IndexBuffer> Create(uint32_t count);
		static Ref<IndexBuffer> Create(const void* indices, uint32_t count);
	};

}