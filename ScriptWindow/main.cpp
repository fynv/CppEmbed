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
		: m_http(HttpClient::New())
		, m_window(ScriptWindow::New())
	{		
		auto input_text = InputText::New("##URL", 256, "https://www.gutenberg.org/cache/epub/1065/pg1065.txt");
		auto button_get = Button::New("Get!");		
		button_get->SetOnClick([this, input_text]() {
			std::string url = input_text->GetText();
			m_http->GetAsync(url.c_str(), [this, url](SPHttpGetResult result)
				{					
					std::string text = "Text from: " + url;
					Print(text.c_str());
					std::vector<char> str(result->GetSize() + 1, 0);
					memcpy(str.data(), result->GetData(), str.size() - 1);
					Print(str.data());
				});
		});

		m_window->Add(Text::New("url:"));
		m_window->Add(SameLine::New());
		m_window->Add(input_text);
		m_window->Add(button_get);
		m_window->SetShow(true);
	}
	SPHttpClient m_http;
	SPScriptWindow m_window;
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
