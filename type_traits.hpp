#ifndef TYPE_TRAITS
# define TYPE_TRAITS

namespace ft {
	template <bool Cond, typename T = void>
		struct enable_if {};
	
	template <typename T>
		struct enable_if<true, T>
		{
			typedef T	type;
		};

	// шаблон integral_constant
	// Создает перменную определенного типа и определенного значения
	template <typename T, T v>
		struct integral_constant
		{
			typedef T					value_type;
			typedef integral_constant	type;

			static const T value = v;

			operator	T(void) { return (value) };
		};
	
	// реализация(?использование?) integral_constant
	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;


	// Создает неконстантный/долговременный тип из типа.
	template <typename T>
	struct _remove_cv
	{
		typedef	T	type;
	};

	template <typename T>
	struct _remove_cv<const T>
	{
		typedef	T	type;
	};

	template <typename T>
	struct _remove_cv<volatile T>
	{
		typedef	T	type;
	};

	template <typename T>
	struct _remove_cv<const volatile T>
	{
		typedef	T	type;
	};

	// Проверяет, является ли тип целочисленным.
	template <typename>
	struct _is_integral_helper : public false_type {};

	template <>
	struct _is_integral_helper<bool> : public true_type {};

	template <>
	struct _is_integral_helper<char> : public true_type {};

	template <>
	struct _is_integral_helper<char16_t> : public true_type {};

	template <>
	struct _is_integral_helper<char32_t> : public true_type {};

	template <>
	struct _is_integral_helper<wchar_t> : public true_type {};

	template <>
	struct _is_integral_helper<signed char> : public true_type {};

	template <>
	struct _is_integral_helper<short int> : public true_type {};

	template <>
	struct _is_integral_helper<int> : public true_type {};

	template <>
	struct _is_integral_helper<long int> : public true_type {};

	template <>
	struct _is_integral_helper<long long int> : public true_type {};

	template <>
	struct _is_integral_helper<unsigned char> : public true_type {};

	template <>
	struct _is_integral_helper<unsigned short int> : public true_type {};

	template <>
	struct _is_integral_helper<unsigned int> : public true_type {};

	template <>
	struct _is_integral_helper<unsigned long int> : public true_type {};

	template <>
	struct _is_integral_helper<unsigned long long int> : public true_type {};

	template <typename T>
	struct is_integral : public _is_integral_helper< typename _remove_cv<T>::type >::type {};

	// Cравнение типов
	template<typename T1, typename T2>
	struct is_same : false_type {};

	template <typename T>
	struct is_same<T, T> : true_type {};
};

#endif