#pragma once

#include "ApiUtils.h"

extern "C"
{	
	GUI_TEST_API void Element_Delete(void* ptr);
	GUI_TEST_API const char* Element_GetName(void* ptr);
	GUI_TEST_API void Element_SetName(void* ptr, const char* name);
	GUI_TEST_API void* Text_New(const char* text);
	GUI_TEST_API void* SameLine_New();
	GUI_TEST_API void* InputText_New(const char* name, int size, const char* str);
	GUI_TEST_API const char* InputText_GetText(void* ptr);
	GUI_TEST_API void InputText_SetText(void* ptr, const char* text);
	GUI_TEST_API void* Button_New(const char* name);

	typedef void (*ClickCallback)(void* ptr);	
	GUI_TEST_API void Button_SetOnClick(void* ptr, ClickCallback callback, void* callback_data);
}

namespace User
{
	class Element : public Wrapper
	{
	protected:
		class _Ptr : public CPtr
		{
		public:
			_Ptr(void* ptr) : CPtr(ptr) {}
			~_Ptr()
			{
				Element_Delete(m_ptr);
			}
		};

	public:
		using Wrapper::Wrapper;

		const char* GetName()
		{
			return Element_GetName(ptr());
		}

		void SetName(const char* name)
		{
			Element_SetName(ptr(), name);
		}

	};

	class Text : public Element
	{
	public:
		Text(const char* text) : Element(new _Ptr(Text_New(text)))
		{

		}

		Text(const Text& in) : Element(in)
		{

		}
	};

	class SameLine : public Element
	{
	public:
		SameLine() : Element(new _Ptr(SameLine_New()))
		{

		}

		SameLine(const SameLine& in) : Element(in)
		{

		}
	};

	class InputText : public Element
	{
	public:
		InputText(const char* name, int size = 256, const char* str = nullptr) 
			: Element(new _Ptr(InputText_New(name, size, str)))
		{

		}

		InputText(const InputText& in) : Element(in)
		{

		}

		const char* GetText()
		{
			return InputText_GetText(ptr());
		}

		void SetText(const char* text)
		{
			InputText_SetText(ptr(), text);
		}
	};

	class Button : public Element
	{
	public:
		Button(const char* name) : Element(new _Ptr(Button_New(name)))
		{

		}

		Button(const Button& in) : Element(in)
		{

		}

		void SetOnClick(ClickCallback callback, void* callback_data)
		{
			Button_SetOnClick(ptr(), callback, callback_data);
		}
	};
}