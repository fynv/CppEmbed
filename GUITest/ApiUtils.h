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
	template<typename T> class TToken;
	template <typename T> class TTokenPtr;

	class Token
	{
	public:
		template<typename T>
		static TTokenPtr<T> New(T&& v)
		{
			return TToken<T>::New(v);
		}

		template<typename T>
		static TTokenPtr<T> New(const T& v)
		{
			return TToken<T>::New(v);
		}

		template<typename T>
		T& To()
		{
			return *dynamic_cast<T*>(this);
		}

		template<typename T>
		const T& To() const
		{
			return *dynamic_cast<const T*>(this);
		}

		template<typename T>
		T& ToValue()
		{
			return To<TToken<T>>().value();
		}

		template<typename T>
		const T& ToValue() const
		{
			return To<TToken<T>>().value();
		}

	protected:
		Token() {}
		virtual ~Token() {}
	};

	typedef std::shared_ptr<Token> TokenPtr;	

	template<typename T>
	class TToken : public Token
	{
	public:
		static TTokenPtr<T> New(T&& v = T())
		{
			return TTokenPtr<T>(new TToken<T>(T(v)));
		}

		static TTokenPtr<T> New(const T& v)
		{
			return TTokenPtr<T>(new TToken<T>(T(v)));
		}

		T& value()
		{
			return m_value;
		}

		const T& value() const
		{
			return m_value;
		}

	protected:
		T m_value;
		TToken(T&& v) : m_value(v)
		{

		}

		TToken(const T& v) : m_value(v)
		{

		}
	};

	template <typename T>
	class TTokenPtr : public std::shared_ptr<TToken<T>>
	{
	public:
		using std::shared_ptr<TToken<T>>::shared_ptr;

		TTokenPtr() {}

		TTokenPtr(T&& v) : std::shared_ptr(TToken<T>::New(v))
		{
		}

		TTokenPtr(const T& v) : std::shared_ptr(TToken<T>::New(v))
		{
		}

		T& operator*() const
		{
			return std::shared_ptr<TToken<T>>::get()->value();
		}

		T* operator->() const
		{
			return &std::shared_ptr<TToken<T>>::get()->value();
		}
	};
	
	class Wrapper : public Token
	{
	public:
		void* ptr()
		{
			return m_cptr;
		}

	protected:
		void* m_cptr;
		Wrapper(void* cptr) : m_cptr(cptr)
		{

		}
	};
	typedef std::shared_ptr<Wrapper> SPWrapper;

}
