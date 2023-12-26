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
	class Element
	{
	public:
		virtual ~Element()
		{
			Element_Delete(m_cptr);
		}

		void* ptr()
		{
			return m_cptr;
		}

		const char* GetName()
		{
			return Element_GetName(m_cptr);
		}

		void SetName(const char* name)
		{
			Element_SetName(m_cptr, name);
		}


	protected:
		void* m_cptr;
		Element(void* cptr) : m_cptr(cptr)
		{

		}	
	};

	typedef std::shared_ptr<Element> SPElement;

	
	class Text;
	typedef std::shared_ptr<Text> SPText;

	class Text : public Element
	{
	public:
		static SPText New(const char* text)
		{
			return SPText(new Text(text));
		}

	protected:
		Text(const char* text) : Element(Text_New(text))
		{

		}
	};

	class SameLine;
	typedef std::shared_ptr<SameLine> SPSameLine;

	class SameLine : public Element
	{
	public:
		static SPSameLine New()
		{
			return SPSameLine(new SameLine);
		}

	protected:
		SameLine() : Element(SameLine_New())
		{


		}
	};

	class InputText;
	typedef std::shared_ptr<InputText> SPInputText;

	class InputText : public Element
	{
	public:
		static SPInputText New(const char* name, int size = 256, const char* str = nullptr)
		{
			return SPInputText(new InputText(name, size, str));
		}

		const char* GetText()
		{
			return InputText_GetText(m_cptr);
		}

		void SetText(const char* text)
		{
			InputText_SetText(m_cptr, text);
		}

	protected:
		InputText(const char* name, int size, const char* str)
			: Element(InputText_New(name, size, str))
		{

		}
	};

	class Button;
	typedef std::shared_ptr<Button> SPButton;

	class Button : public Element
	{
	public:
		static SPButton New(const char* name)
		{
			return SPButton(new Button(name));
		}
		
		void SetOnClick(ClickCallback callback, void* callback_data)
		{
			Button_SetOnClick(m_cptr, callback, callback_data);
		}

	protected:
		Button(const char* name) : Element(Button_New(name))
		{

		}
	};

}