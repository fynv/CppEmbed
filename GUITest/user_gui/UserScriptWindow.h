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
	
	class ScriptWindow : public Wrapper
	{
		class _Ptr : public CPtr
		{
		public:
			_Ptr(void* ptr) : CPtr(ptr) {}
			~_Ptr()
			{
				ScriptWindow_Delete(m_ptr);
			}
		};

	public:
		ScriptWindow() : Wrapper(new _Ptr(ScriptWindow_New()))
		{
			
		}

		ScriptWindow(const ScriptWindow& in): Wrapper(in)
		{

		}

		bool GetShow()
		{
			return ScriptWindow_GetShow(ptr());
		}

		void SetShow(bool show)
		{
			ScriptWindow_SetShow(ptr(), show);
		}

		const char* GetTitle()
		{
			return ScriptWindow_GetTitle(ptr());
		}

		void SetTitle(const char* title)
		{
			ScriptWindow_SetTitle(ptr(), title);
		}

		void Add(Element elem)
		{
			ScriptWindow_Add(ptr(), elem.ptr());
			m_elements.push_back(elem);
		}

		void Remove(Element elem)
		{
			ScriptWindow_Remove(ptr(), elem.ptr());
			auto iter = std::find(m_elements.begin(), m_elements.end(), elem);
			if (iter != m_elements.end())
			{
				m_elements.erase(iter);
			}
		}

		void Clear()
		{
			ScriptWindow_Clear(ptr());
			m_elements.clear();
		}

		std::vector<Element> m_elements;
	};

}