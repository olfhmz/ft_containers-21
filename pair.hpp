#ifndef PAIR
# define PAIR

namespace ft {
	template <typename T1, typename T2>
	class pair {

		public:
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;

			pair() : first(first_type()), second(second_type()) {};

			template <typename U, typename V>
			pair(const pair<U, V> &src) : first(src.first), second(src.second) {};

			pair(const first_type &first, const second_type &second) : first(first), second(second) {};

			~pair() {};

			pair &operator=(const pair &rhd)
			{
				this->first = rhd.first;
				this->second = rhd.second;
			};

			void swap(pair &other)
			{
				pair	buf = other;

				other = *this;
				*this = buf;
			};
	};
	
	template <typename T1, typename T2>
	inline void	swap(const pair<T1, T2> & lhd, const pair<T1, T2> & rhd)
	{
		lhd.swap(rhd);
	};

	template <typename T1, typename T2>
	inline bool	operator==(pair<T1, T2> const & lhd, pair<T1, T2> const & rhd)
	{
		return (lhd.first == rhd.first && lhd.second == rhd.second);
	};

	template <typename T1, typename T2>
	inline bool	operator!=(pair<T1, T2> const & lhd, pair<T1, T2> const & rhd)
	{
		return !(lhd == rhd);
	};

	template <typename T1, typename T2>
	inline bool	operator<(pair<T1, T2> const & lhd, pair<T1, T2> const & rhd)
	{
		return (lhd.first < rhd.first || (!(lhd.first > rhd.first) && lhd.second == rhd.second));
	};

	template <typename T1, typename T2>
	inline bool	operator<=(pair<T1, T2> const & lhd, pair<T1, T2> const & rhd)
	{
		return !(rhd < lhd);
	};

	template <typename T1, typename T2>
	inline bool	operator>(pair<T1, T2> const & lhd, pair<T1, T2> const & rhd)
	{
		return (rhd < lhd);
	};

	template <typename T1, typename T2>
	inline bool	operator>=(pair<T1, T2> const & lhd, pair<T1, T2> const & rhd)
	{
		return !(lhd < rhd);
	};

	template <typename T1, typename T2>
	inline pair<T1, T2>	make_pair(T1 const & first, T2 const & second)
	{
		return (pair<T1, T2>(first, second));
	};
};

#endif