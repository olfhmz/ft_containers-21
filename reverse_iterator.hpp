#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{
	template <typename Iterator>
	class reverse_iterator : public std::iterator <
		typename ft::iterator_traits<Iterator>::iterator_category,
		typename ft::iterator_traits<Iterator>::value_type,
		typename ft::iterator_traits<Iterator>::difference_type,
		typename ft::iterator_traits<Iterator>::pointer,
		typename ft::iterator_traits<Iterator>::reference
		>
	{
		protected:
			Iterator	_current;

			typedef typename	ft::iterator_traits<Iterator>	_traits_type;

		public:
			typedef				Iterator						iterator_type;
			typedef	typename	_traits_type::difference_type	difference_type;
			typedef	typename	_traits_type::pointer			pointer;
			typedef	typename	_traits_type::reference			reference;

			reverse_iterator(void) : _current() {};
			
			explicit reverse_iterator(iterator_type it) : _current(it) {};

			reverse_iterator(const reverse_iterator & src)
			{
				*this = src;
			};

			~reverse_iterator() {};

			reverse_iterator &	operator=(const iterator_type & rhd)
			{
				this->_current = rhd._current;
				return (*this);
			};

			reverse_iterator	operator+(difference_type n)	const
			{
				return (reverse_iterator(this->_current - n));
			};

			reverse_iterator &	operator++(void)
			{
				--this->_current;
				return (*this);
			};

			reverse_iterator	operator++(int)
			{
				reverse_iterator	buf(*this);
				--this->_current;
				return (buf);
			};

			reverse_iterator	operator-(difference_type n)	const
			{
				return (reverse_iterator(this->_current + n));
			};

			reverse_iterator &	operator--(void)
			{
				++this->_current;
				return (*this);
			};

			reverse_iterator	operator--(int)
			{
				reverse_iterator	buf(*this);
				++this->_current;
				return (buf);
			};

			reverse_iterator &	operator+=(difference_type n)
			{
				this->_current -= n;
				return (*this);
			};

			reverse_iterator &	operator-=(difference_type n)
			{
				this->_current += n;
				return (*this);
			};

			reference	operator*(void)	const
			{
				iterator_type	buf = this->_current;
				--buf;
				return (*buf);
			};

			reference	operator[](difference_type n)	const
			{
				return (*(*this + n));
			};

			pointer	operator->(void)	const
			{
				iterator_type	buf = this->_current;
				--buf;
				return (&(*buf));
			};

			iterator_type	base(void)	const
			{
				return (this->_current);
			};

	};

	template <class Iterator>
	typename ft::reverse_iterator<Iterator>
		operator+(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator> & rhd)
	{
		return (reverse_iterator<Iterator>(rhd.base() - n));
	};

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type
		operator-(const reverse_iterator<Iterator> & lhd, const reverse_iterator<Iterator> & rhd)
	{
		return (rhd.base() - lhd.base());
	};

	template <class Iterator>
	bool	operator==(const reverse_iterator<Iterator> & lhd, const reverse_iterator<Iterator> & rhd)
	{
		return (rhd.base() == lhd.base());
	};

	template <class Iterator>
	bool	operator!=(const reverse_iterator<Iterator> & lhd, const reverse_iterator<Iterator> & rhd)
	{
		return (rhd.base() != lhd.base());
	};

	template <class Iterator>
	bool	operator<=(const reverse_iterator<Iterator> & lhd, const reverse_iterator<Iterator> & rhd)
	{
		return (rhd.base() <= lhd.base());
	};

	template <class Iterator>
	bool	operator>=(const reverse_iterator<Iterator> & lhd, const reverse_iterator<Iterator> & rhd)
	{
		return (rhd.base() >= lhd.base());
	};

	template <class Iterator>
	bool	operator>(const reverse_iterator<Iterator> & lhd, const reverse_iterator<Iterator> & rhd)
	{
		return (rhd.base() > lhd.base());
	};

	template <class Iterator>
	bool	operator<(const reverse_iterator<Iterator> & lhd, const reverse_iterator<Iterator> & rhd)
	{
		return (rhd.base() < lhd.base());
	};
};

#endif
