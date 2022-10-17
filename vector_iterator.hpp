#ifndef VECTOR_ITERATOR
# define VECTOR_ITERATOR

namespace ft {
	template <typename Iterator>
		class vector_iterator {
			private:
				typedef		ft::iterator_traits<Iterator>	_traits_type;
			public:
				typedef	typename	_traits_type::iterator_category		iterator_category;
				typedef	typename	_traits_type::value_type			value_type;
				typedef	typename	_traits_type::difference_type		difference_type;
				typedef	typename	_traits_type::reference				reference;
				typedef	typename	_traits_type::pointer				pointer;
			private:
				pointer	_current;
			public:
				vector_iterator(void) {};
				vector_iterator(const vector_iterator &src) { *this = src; };
				vector_iterator(const pointer &src) : _current(src) {};
				~vector_iterator() {};

				vector_iterator &operator=(const vector_iterator &rhd) 
				{
					this->_current = rhd._current;
					return *this;
				};

				reference operator*(void) { return *_current; };
				pointer operator->(void) const { return _current; };
				reference operator[](difference_type n) const { return (this->_current[n]); };
				vector_iterator &operator+(difference_type n) const { return (vector_iterator(this->_current + n)); };
				vector_iterator	operator++(int) { return (vector_iterator(this->_current++)); };
				vector_iterator	operator-(difference_type n) const { return (vector_iterator(this->_current - n)); };
				vector_iterator	operator--(int) { return (vector_iterator(this->_current--)); };
				const pointer &	base(void) const { return (this->_current); };

				vector_iterator &operator+=(difference_type n)
				{
					this->_current += n;
					return (*this);
				};

				vector_iterator &operator++(void)
				{
					this->_current++;
					return (*this);
				};

				vector_iterator &operator-=(difference_type n)
				{
					this->_current -= n;
					return (*this);
				};

				vector_iterator &operator--(void)
				{
					this->_current--;
					return (*this);
				};
		};

		template <typename IterL, typename IterR>
		inline bool	operator==(vector_iterator<IterL> const & lhd, vector_iterator<IterR> const & rhd)
		{
			return (lhd.base() == rhd.base());
		};

		template <typename Iter>
		inline bool	operator==(vector_iterator<Iter> const & lhd, vector_iterator<Iter> const & rhd)
		{
			return (lhd.base() == rhd.base());
		};

		template <typename IterL, typename IterR>
		inline bool	operator!=(vector_iterator<IterL> const & lhd, vector_iterator<IterR> const & rhd)
		{
			return (lhd.base() != rhd.base());
		};

		template <typename Iter>
		inline bool	operator!=(vector_iterator<Iter> const & lhd, vector_iterator<Iter> const & rhd)
		{
			return (lhd.base() != rhd.base());
		};

		template <typename IterL, typename IterR>
		inline bool	operator>(vector_iterator<IterL> const & lhd, vector_iterator<IterR> const & rhd)
		{
			return (lhd.base() > rhd.base());
		};

		template <typename Iter>
		inline bool	operator>(vector_iterator<Iter> const & lhd, vector_iterator<Iter> const & rhd)
		{
			return (lhd.base() > rhd.base());
		};

		template <typename IterL, typename IterR>
		inline bool	operator>=(vector_iterator<IterL> const & lhd, vector_iterator<IterR> const & rhd)
		{
			return (lhd.base() >= rhd.base());
		};

		template <typename Iter>
		inline bool	operator>=(vector_iterator<Iter> const & lhd, vector_iterator<Iter> const & rhd)
		{
			return (lhd.base() >= rhd.base());
		};

		template <typename IterL, typename IterR>
		inline bool	operator<(vector_iterator<IterL> const & lhd, vector_iterator<IterR> const & rhd)
		{
			return (lhd.base() < rhd.base());
		};

		template <typename Iter>
		inline bool	operator<(vector_iterator<Iter> const & lhd, vector_iterator<Iter> const & rhd)
		{
			return (lhd.base() < rhd.base());
		};

		template <typename IterL, typename IterR>
		inline bool	operator<=(vector_iterator<IterL> const & lhd, vector_iterator<IterR> const & rhd)
		{
			return (lhd.base() <= rhd.base());
		};

		template <typename Iter>
		inline bool	operator<=(vector_iterator<Iter> const & lhd, vector_iterator<Iter> const & rhd)
		{
			return (lhd.base() <= rhd.base());
		};

		template <typename Iter>
		inline typename vector_iterator<Iter>::difference_type	operator-(vector_iterator<Iter> const & lhd, vector_iterator<Iter> const & rhd)
		{
			return (lhd.base() - rhd.base());
		};

		template <typename Iter>
		inline vector_iterator<Iter>	operator+(typename vector_iterator<Iter>::difference_type n, vector_iterator<Iter> const & rhd)
		{
			return (vector_iterator<Iter>(rhd.base() + n));
		};
}

#endif