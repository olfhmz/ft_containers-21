#ifndef STACK_HPP
# define STACK_HPP

# include "type_traits.hpp"
# include "vector.hpp"
# include <iostream>

namespace ft {
template <class T, class Container = vector<T> > 
class stack {
	public:
		typedef				Container																				container_type;
		typedef typename	ft::enable_if<ft::is_same<T, typename container_type::value_type>::value, T >::type		value_type;
		typedef typename	container_type::reference																reference;
		typedef typename	container_type::const_reference															const_reference;
		typedef typename	container_type::size_type																size_type;
	
		Container	c;
	
		explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {};
		
		~stack () {};

		bool	empty(void) const { return c.empty(); };
		size_type	size(void) const { return c.size(); };
		reference	top(void) { return c.back(); };
		const_reference	top(void) const { return c.back(); };
		void	push(const_reference val) { c.push_back(val); };
		void	pop(void) { c.pop_back(); };
		void	swap(stack &ref) { this->c.swap(ref.c); };
};

template <typename T, typename Container>
	bool	operator==(stack<T, Container> const & lhd, stack<T, Container> const & rhd)
	{
		return (lhd.c == rhd.c);
	};

template <typename T, typename Container>
	bool	operator!=(stack<T, Container> const & lhd, stack<T, Container> const & rhd)
	{
		return !(lhd.c == rhd.c);
	};

template <typename T, typename Container>
	bool	operator<(stack<T, Container> const & lhd, stack<T, Container> const & rhd)
	{
		return (lhd.c < rhd.c);
	};

template <typename T, typename Container>
	bool	operator<=(stack<T, Container> const & lhd, stack<T, Container> const & rhd)
	{
		return !(rhd.c < lhd.c);
	};

template <typename T, typename Container>
	bool	operator>(stack<T, Container> const & lhd, stack<T, Container> const & rhd)
	{
		return (rhd.c < lhd.c);
	};

template <typename T, typename Container>
	bool	operator>=(stack<T, Container> const & lhd, stack<T, Container> const & rhd)
	{
		return !(lhd.c < rhd.c);
	};

template <typename T, typename Container>
	void	swap(stack<T, Container> const & lhd, stack<T, Container> const & rhd)
	{
		lhd.swap(rhd);
	};
};

#endif
