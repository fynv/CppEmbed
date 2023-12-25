#include <cstdio>
#include "Api.h"

using namespace User;

extern "C"
{
	GUI_TEST_USER_ENTRY void init();
	GUI_TEST_USER_ENTRY void clean();
}

void init()
{
	Print("Hello from world");
}

void clean()
{


}