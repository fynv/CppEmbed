#pragma once

#include "ApiUtils.h"

extern "C"
{	
	GUI_TEST_API void HttpGetResult_Delete(void* ptr);
	GUI_TEST_API bool HttpGetResult_GetResult(void* ptr);
	GUI_TEST_API size_t HttpGetResult_GetSize(void* ptr);
	GUI_TEST_API void* HttpGetResult_GetData(void* ptr);

	GUI_TEST_API void* HttpClient_New();
	GUI_TEST_API void HttpClient_Delete(void* ptr);	
	GUI_TEST_API void* HttpClient_Get(void* ptr, const char* url);

	typedef void (*HttpGetCallback)(void* ptr_result, void* userData);
	GUI_TEST_API void HttpClient_GetAsync(void* ptr, const char* url, HttpGetCallback callback, void* userData);
}

namespace User
{
	class HttpGetResult : public Wrapper
	{
		class _Ptr : public CPtr
		{
		public:
			_Ptr(void* ptr) : CPtr(ptr) {}
			~_Ptr()
			{
				HttpGetResult_Delete(m_ptr);
			}
		};
	public:
		HttpGetResult(void* cptr) : Wrapper(new _Ptr(cptr))
		{

		}

		HttpGetResult(const HttpGetResult& in) : Wrapper(in)
		{

		}

		size_t GetSize()
		{
			return HttpGetResult_GetSize(ptr());
		}

		void* GetData()
		{
			return HttpGetResult_GetData(ptr());
		}

	};

	class HttpClient : public Wrapper
	{
		class _Ptr : public CPtr
		{
		public:
			_Ptr(void* ptr) : CPtr(ptr) {}
			~_Ptr()
			{
				HttpClient_Delete(m_ptr);
			}
		};

	public:
		HttpClient() : Wrapper(new _Ptr(HttpClient_New()))
		{

		}

		HttpClient(const HttpClient& in) : Wrapper(in)
		{

		}

		HttpGetResult Get(const char* url)
		{
			HttpGetResult res(HttpClient_Get(ptr(), url));			;
			return res;
		}

		typedef void (*GetCallback)(HttpGetResult result, void* userData);
		
		void GetAsync(const char* url, GetCallback callback, void* userData)
		{
			TUserData* ud = new TUserData({ callback, userData });
			HttpClient_GetAsync(ptr(), url, s_get_callback, ud);
		}

	private:
		struct TUserData
		{
			GetCallback callback;
			void* userData;
		};

		static void s_get_callback(void* ptr_result, void* userData)
		{
			TUserData* ud = (TUserData*)userData;
			HttpGetResult res(ptr_result);			
			ud->callback(res, ud->userData);
			delete ud;
		}

	};
}

