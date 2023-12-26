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
	class HttpGetResult
	{
	public:
		HttpGetResult(void* cptr) : m_cptr(cptr)
		{

		}

		~HttpGetResult()
		{
			HttpGetResult_Delete(m_cptr);
		}

		void* ptr()
		{
			return m_cptr;
		}

		size_t GetSize()
		{
			return HttpGetResult_GetSize(m_cptr);
		}

		void* GetData()
		{
			return HttpGetResult_GetData(m_cptr);
		}

	private:
		void* m_cptr;
	};

	typedef std::shared_ptr<HttpGetResult> SPHttpGetResult;

	class HttpClient
	{
	public:
		HttpClient() : m_cptr(HttpClient_New())
		{

		}

		~HttpClient()
		{
			HttpClient_Delete(m_cptr);
		}

		SPHttpGetResult Get(const char* url)
		{
			SPHttpGetResult res(new HttpGetResult(HttpClient_Get(m_cptr, url)));
			return res;
		}

		typedef void (*GetCallback)(SPHttpGetResult result, void* userData);

		void GetAsync(const char* url, GetCallback callback, void* userData)
		{
			TUserData* ud = new TUserData({ callback, userData });
			HttpClient_GetAsync(m_cptr, url, s_get_callback, ud);
		}

	private:
		void* m_cptr;

		struct TUserData
		{
			GetCallback callback;
			void* userData;
		};

		static void s_get_callback(void* ptr_result, void* userData)
		{
			TUserData* ud = (TUserData*)userData;
			SPHttpGetResult res(new HttpGetResult(ptr_result));
			ud->callback(res, ud->userData);
			delete ud;
		}
	};

	typedef std::shared_ptr<HttpClient> SPHttpClient;
	
}

