#pragma once

#include <functional>
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
	class HttpGetResult;
	typedef std::shared_ptr<HttpGetResult> SPHttpGetResult;

	class HttpGetResult : public Wrapper
	{
	public:
		static SPHttpGetResult New(void* c_ptr)
		{
			return SPHttpGetResult(new HttpGetResult(c_ptr));
		}

		~HttpGetResult()
		{
			HttpGetResult_Delete(m_cptr);
		}

		size_t GetSize()
		{
			return HttpGetResult_GetSize(m_cptr);
		}

		void* GetData()
		{
			return HttpGetResult_GetData(m_cptr);
		}

	protected:
		HttpGetResult(void* cptr) : Wrapper(cptr)
		{

		}		
	};

	class HttpClient;
	typedef std::shared_ptr<HttpClient> SPHttpClient;

	class HttpClient : public Wrapper
	{
	public:
		static SPHttpClient New()
		{
			return SPHttpClient(new HttpClient);
		}

		~HttpClient()
		{
			HttpClient_Delete(m_cptr);
		}

		SPHttpGetResult Get(const char* url)
		{
			return HttpGetResult::New(HttpClient_Get(m_cptr, url));
		}

		void GetAsync(const char* url, const std::function<void(SPHttpGetResult)>& callback)
		{
			auto* ud = new std::function<void(SPHttpGetResult)>(callback);
			HttpClient_GetAsync(m_cptr, url, s_get_callback, ud);
		}

	protected:		
		HttpClient() : Wrapper(HttpClient_New())
		{

		}

		static void s_get_callback(void* ptr_result, void* userData)
		{
			auto* callback = (std::function<void(SPHttpGetResult)>*)userData;			
			SPHttpGetResult res = HttpGetResult::New(ptr_result);
			(*callback)(res);
			delete callback;
		}
	};
	
}

