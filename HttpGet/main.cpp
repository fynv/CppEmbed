#include <cstdio>
#include <vector>
#include "Api.h"

using namespace User;

extern "C"
{
	GUI_TEST_USER_ENTRY void init();
	GUI_TEST_USER_ENTRY void clean();
}

class App
{
public:
	App()
	{
		/*auto res = m_http.Get("https://www.baidu.com/");
		std::vector<char> str(res.GetSize() + 1, 0);
		memcpy(str.data(), res.GetData(), str.size() - 1);
		Print(str.data());*/

		m_http.GetAsync("https://www.gutenberg.org/cache/epub/1065/pg1065.txt", GetCallback, nullptr);

	}

	static void GetCallback(HttpGetResult result, void* userData)
	{
		std::vector<char> str(result.GetSize() + 1, 0);
		memcpy(str.data(), result.GetData(), str.size() - 1);
		Print(str.data());
	}

	HttpClient m_http;
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

