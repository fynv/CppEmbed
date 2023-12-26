#pragma once

#include <vector>
#include "ApiUtils.h"
#include "UserElements.h"

extern "C"
{
	GUI_TEST_API void* ScriptWindow_New();
	GUI_TEST_API void ScriptWindow_Delete(void* ptr);
	GUI_TEST_API bool ScriptWindow_GetShow(void* ptr);
	GUI_TEST_API void ScriptWindow_SetShow(void* ptr, bool show);
	GUI_TEST_API const char* ScriptWindow_GetTitle(void* ptr);
	GUI_TEST_API void ScriptWindow_SetTitle(void* ptr, const char* title);
	GUI_TEST_API void ScriptWindow_Add(void* ptr, void* ptr_elem);
	GUI_TEST_API void ScriptWindow_Remove(void* ptr, void* ptr_elem);
	GUI_TEST_API void ScriptWindow_Clear(void* ptr);
}

namespace User
{
	class ScriptWindow;
	typedef std::shared_ptr<ScriptWindow> SPScriptWindow;

	class ScriptWindow
	{
	public:
		static SPScriptWindow New()
		{
			return SPScriptWindow(new ScriptWindow);
		}
		
		~ScriptWindow()
		{
			ScriptWindow_Delete(m_cptr);
		}

		void* ptr()
		{
			return m_cptr;
		}

		bool GetShow()
		{
			return ScriptWindow_GetShow(m_cptr);
		}

		void SetShow(bool show)
		{
			ScriptWindow_SetShow(m_cptr, show);
		}

		const char* GetTitle()
		{
			return ScriptWindow_GetTitle(m_cptr);
		}

		void SetTitle(const char* title)
		{
			ScriptWindow_SetTitle(m_cptr, title);
		}

		void Add(SPElement elem)
		{
			ScriptWindow_Add(m_cptr, elem->ptr());
			m_elements.push_back(elem);
		}

		void Remove(SPElement elem)
		{
			ScriptWindow_Remove(m_cptr, elem->ptr());
			auto iter = std::find(m_elements.begin(), m_elements.end(), elem);
			if (iter != m_elements.end())
			{
				m_elements.erase(iter);
			}
		}

		void Clear()
		{
			ScriptWindow_Clear(m_cptr);
			m_elements.clear();
		}

		std::vector<SPElement> m_elements;


	private:
		void* m_cptr;
		ScriptWindow() : m_cptr(ScriptWindow_New())
		{


		}
	};

}