#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include "algorithm.hpp"
# include "type_traits.hpp"
# include "iterator_traits.hpp"
# include "vector_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
	template <typename T, class Alloc = std::allocator<T>>
	class vector
	{
		public:

			typedef				T													value_type;
			typedef				Alloc												allocator_type;
			typedef typename	allocator_type::reference							reference;
			typedef typename	allocator_type::const_reference						const_reference;
			typedef typename	allocator_type::pointer								pointer;
			typedef typename	allocator_type::const_pointer						const_pointer;
			typedef typename	allocator_type::size_type							size_type;

			typedef  			ft::vector_iterator<pointer>						iterator;
			typedef  			ft::vector_iterator<const_pointer>					const_iterator;
			typedef typename	ft::iterator_traits<iterator>::difference_type		difference_type;
			typedef				reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef 			reverse_iterator<iterator>							reverse_iterator;

		private:

			allocator_type	_allocator;

			pointer		_values;
			size_type	_size;
			size_type	_capacity;

			void	_reallocWithCapacity(size_type new_capacity)
			{
				pointer	new_values = _allocator.allocate(new_capacity);

				for (size_type i = 0; i < this->_size; i++)
				{
					_allocator.construct(new_values + i, this->_values[i]);
					_allocator.destroy(this->_values + i);
				}
				
				for (size_type i = this->_size; i < this->_capacity; i++)
					_allocator.destroy(this->_values + i);

				_allocator.deallocate(this->_values, this->_capacity);
				this->_values = new_values;
				this->_capacity = new_capacity;
			};

			iterator	_insertion_routine(iterator position, size_type val_num)
			{
				size_type indx = position.base() - this->_values;

				if (this->_size + val_num > this->_capacity * 2)
					this->reserve(this->_size + val_num);
				else if (this->_capacity < this->_size + val_num)
					this->reserve(this->_capacity * 2);

				position = this->begin() + indx;

				iterator last = this->end() + val_num;

				while (--last > this->end())
					this->_allocator.construct(last.base(), *(last - val_num));
				this->_allocator.construct(last.base(), *(last - val_num));

				while (--last > position + val_num - 1)
					*last = *(last - val_num);

				this->_size += val_num;

				return position;
			}

		public:
			explicit	vector(const allocator_type & alloc = allocator_type())
				: _values(nullptr), _size(0), _capacity(0), _allocator(alloc) {};

			explicit	vector(size_type n, const value_type & val = value_type(),
				const allocator_type & alloc = allocator_type())
					: _values(nullptr), _size(n), _capacity(n)
			{
				this->_allocator = allocator_type(alloc);

				this->_values = this->_allocator.allocate(n);
				for (size_type i = 0; i < n; i++)
					this->_allocator.construct(this->_values + i, val);
			};

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type())
				: _values(nullptr), _size(std::distance(first, last)), _capacity(std::distance(first, last)), _allocator(alloc)
			{
				this->_values = this->_allocator.allocate(std::distance(first, last));
				std::copy(first, last, this->begin());
			};

			vector(const vector & src)
				: _values(nullptr), _size(0), _capacity(0)
			{
				*this = src;
			};

			~vector() {
				this->clear();
			};

			vector &	operator=(vector const & rhd) {
				if (this->_capacity != rhd._capacity)
				{

					for (size_type i = 0; i < this->_capacity; i++)
						_allocator.destroy(this->_values + i);
					
					_allocator.deallocate(this->_values, this->_capacity);
					this->_values = _allocator.allocate(rhd._capacity);
					this->_capacity = rhd._capacity;
				}

				this->_size = rhd._size;

				for (size_type i = 0; i < this->_size; i++)
					_allocator.construct(this->_values + i, rhd._values[i]);
				
				for (size_type i = this->_size; i < this->_capacity; i++)
					_allocator.construct(this->_values + i, value_type());
				
				return (*this);
			};

			inline reference	operator[](size_type n) {
				return (this->_values[n]);
			};

			inline const_reference	operator[](size_type n)	const {
				return (this->_values[n]);
			};

			inline iterator	begin(void) {
				return (iterator(this->_values));
			};

			inline const_iterator	begin(void)	const {
				return (const_iterator(this->_values));
			};

			iterator	end(void) {
				if (this->empty())
					return (this->begin());

				return (iterator(this->_values + this->_size));
			};

			const_iterator	end(void)	const {
				if (this->empty())
					return (this->begin());

				return (const_iterator(this->_values + this->_size));
			};

			inline reverse_iterator	rbegin(void) {
				return (reverse_iterator(this->end()));
			};

			inline const_reverse_iterator	rbegin(void)	const {
				return (const_reverse_iterator(this->end()));
			};

			inline reverse_iterator	rend(void) {
				return (reverse_iterator(this->begin()));
			};

			inline const_reverse_iterator	rend(void)	const {
				return (const_reverse_iterator(this->begin()));
			};

			inline const_iterator	cbegin(void)	const {
				return (const_iterator(this->_values));
			};

			const_iterator	cend(void)	const {
				if (this->empty())
					return (this->cbegin());

				return (const_iterator(this->_values + this->_size));
			};

			inline const_reverse_iterator	crbegin(void)	const {
				return (const_reverse_iterator(this->end()));
			};

			inline const_reverse_iterator	crend(void)	const {
				return (const_reverse_iterator(this->begin()));
			};

			inline size_type	size(void)	const {
				return (this->_size);
			};

			inline size_type	max_size(void)	const {
				return (_allocator.max_size());
			};

			void	resize(size_type n, value_type val = value_type()) {
				if (n <= this->_size)
				{
					this->_size = n;
					for (size_type i = this->_size; i < this->_capacity; i++)
						_allocator.destroy(this->_values + i);
					return ;
				}

				this->reserve(n);

				while (this->_size < n)
					_allocator.construct(this->_values + this->_size++, val);
			};

			inline size_type	capacity(void)	const {
				return (this->_capacity);
			};

			inline bool	empty(void)	const {
				return (!this->_size);
			};

			void	reserve(size_type n) {
				if (n <= this->_capacity)
					return ;
				this->_reallocWithCapacity(n);
			};

			void	shrink_to_fit(void) {
				if (this->_size == this->_capacity)
					return ;
				this->_reallocWithCapacity(this->_size);
			};

			reference	at(size_type n) {
				if (!(n < this->_size))
					throw std::out_of_range("vector");
				
				return (this->_values[n]);
			};

			const_reference	at(size_type n)	const {
				if (!(n < this->_size))
					throw std::out_of_range("vector");
				
				return (this->_values[n]);
			};

			inline reference	front(void) {
				return (*this->_values);
			};

			inline const_reference	front(void)	const {
				return (*this->_values);
			};

			inline reference	back(void) {
				return (this->_values[this->_size - 1]);
			};

			inline const_reference	back(void)	const {
				return (this->_values[this->_size - 1]);
			};

			inline value_type *	data(void) {
				return (this->_values);
			};

			inline const value_type *	data(void)	const {
				return (this->_values);
			};

			template <typename InputIterator>
			void	assign(InputIterator first, InputIterator last) {
				size_type	n = std::distance(first, last);
				this->reserve(n);

				iterator	start = this->begin();

				for (;first != last; first++)
					*(start++) = *first;
				
				for (; start != this->end(); start++)
					this->_allocator.destroy(start.base());
				
				this->_size = n;
			};

			void	assign(size_type n, const_reference val) {
				this->reserve(n);

				iterator start = this->begin();

				for (size_type i = 0; i < n; i++)
					*(start++) = val;
				
				for (; start != this->end(); start++)
					this->_allocator.destroy(start.base());

				this->_size = n;
			};

			void	push_back(const_reference val) {
				if (this->_size == this->_capacity)
					this->reserve(this->_size * 2 + !this->_size);
				this->_allocator.construct(this->_values + this->_size++, val);
			};

			void	pop_back(void) {
				if (!this->_size)
					return ;
				this->_allocator.destroy(this->_values + --this->_size);
			};

			iterator	insert(iterator position, const_reference val) {
				position = this->_insertion_routine(position, 1);

				*position = val;

				return (position);
			};

			void	insert(iterator position, size_type n, const_reference val) {
				position = this->_insertion_routine(position, n);

				while (n--)
					*(position++) = val;
			};

			template <typename InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last) {
				position = this->_insertion_routine(position, std::distance(first, last));

				while (first++ != last)
					*(position++) = *first;
			};

			inline iterator	erase(iterator position) {
				return(this->erase(position, position + 1));
			};

			iterator	erase(iterator first, iterator last) {
				iterator	edge = first;
				size_type	n = last - first;

				while (last != this->end())
					*(first++) = *(last++);
				
				for (; first != this->end(); first++)
					this->_allocator.destroy(first.base());

				this->_size -= n;

				return (edge);
			};

			void	swap(vector & src) {
				value_type *	buf = src._values;
				size_type		size_buf = src._size;
				size_type		capacity_buf = src._capacity;

				src._values = this->_values;
				src._size = this->_size;
				src._capacity = this->_capacity;
				this->_values = buf;
				this->_size = size_buf;
				this->_capacity = capacity_buf;
			};

			void	clear(void) {
				for (iterator start = this->begin(); start != this->end(); start++)
					_allocator.destroy(start.base());
				this->_size = 0;
			};

			inline allocator_type	get_allocator(void)	const {
				return (_allocator);
			};
	};

	template <typename T, typename Alloc>
	inline void	swap(vector<T, Alloc> & lhd, vector<T, Alloc> & rhd) {
		lhd.swap(rhd);
	};

	template <typename T, typename Alloc>
	bool	operator==(vector<T, Alloc> & lhd, vector<T, Alloc> & rhd) {
		if (lhd.size() != rhd.size())
			return (false);
		return (ft::equal(lhd.begin(), lhd.end(), rhd.begin()));
	};

	template <typename T, typename Alloc>
	inline bool	operator!=(vector<T, Alloc> & lhd, vector<T, Alloc> & rhd) {
		return !(lhd == rhd);
	};

	template <typename T, typename Alloc>
	inline bool	operator<(vector<T, Alloc> & lhd, vector<T, Alloc> & rhd) {
		return (ft::lexicographical_compare(lhd.begin(), lhd.end(), rhd.begin(), rhd.end()));
	};

	template <typename T, typename Alloc>
	inline bool	operator>(vector<T, Alloc> & lhd, vector<T, Alloc> & rhd) {
		return (rhd < lhd);
	};

	template <typename T, typename Alloc>
	inline bool	operator<=(vector<T, Alloc> & lhd, vector<T, Alloc> & rhd) {
		return !(rhd > lhd);
	};

	template <typename T, typename Alloc>
	inline bool	operator>=(vector<T, Alloc> & lhd, vector<T, Alloc> & rhd) {
		return !(lhd > rhd);
	};
};

#endif
