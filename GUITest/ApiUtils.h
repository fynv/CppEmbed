#pragma once

#if defined(GUI_TEST_EXPORT) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#define GUI_TEST_API __declspec(dllexport)
#else
#define GUI_TEST_API 
#endif

#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#define GUI_TEST_USER_ENTRY __declspec(dllexport)
#else
#define GUI_TEST_USER_ENTRY 
#endif


#include <memory>

namespace User
{
	class CPtr
	{
	public:
		void* ptr() const 
		{
			return m_ptr;
		}

	protected:
		void* m_ptr;
		CPtr(void* ptr) : m_ptr(ptr) {}
		virtual ~CPtr() {}	
	};

	class Wrapper : public std::shared_ptr<CPtr>
	{
	public:
		using std::shared_ptr<CPtr>::shared_ptr;
		void* ptr()
		{
			return (*this)->ptr();
		}		
	};
	
}

