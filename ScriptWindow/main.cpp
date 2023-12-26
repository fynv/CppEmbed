#include <cstdio>
#include <vector>
#include <string>
#include "Api.h"

using namespace User;

extern "C"
{
	GUI_TEST_USER_ENTRY void init();
	GUI_TEST_USER_ENTRY void clean();
	GUI_TEST_USER_ENTRY void* get_script_window();
}

class App
{
public:
	App()
		: m_http(new HttpClient)
		, m_window(new ScriptWindow)
		, m_input_text(new InputText("##URL", 256, "https://www.gutenberg.org/cache/epub/1065/pg1065.txt"))
	{		
		SPButton button_get(new Button("Get!"));
		button_get->SetOnClick(buttonOnClick, this);

		m_window->Add(SPText(new Text("url:")));
		m_window->Add(SPSameLine(new SameLine));
		m_window->Add(m_input_text);
		m_window->Add(button_get);
		m_window->SetShow(true);

	}

	static void httpGetCallback(SPHttpGetResult result, void* ptr)
	{
		App* self = (App*)ptr;
		std::string text = "Text from: ";
		text += self->m_input_text->GetText();
		Print(text.c_str());
		std::vector<char> str(result->GetSize() + 1, 0);
		memcpy(str.data(), result->GetData(), str.size() - 1);
		Print(str.data());
	}

	static void buttonOnClick(void* ptr)
	{
		App* self = (App*)ptr;
		self->m_http->GetAsync(self->m_input_text->GetText(), httpGetCallback, self);
	}

	SPHttpClient m_http;
	SPScriptWindow m_window;
	SPInputText m_input_text;

};

App* g_app;

void init()
{
	g_app = new App;
}

void clean()
{
	delete g_app;
}

void* get_script_window()
{
	return g_app->m_window->ptr();
}
