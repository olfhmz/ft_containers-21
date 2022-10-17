#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include <stdexcept>
# include "reverse_iterator.hpp"
# include "pair.hpp"
# include "iterator_traits.hpp"
# include "RBTree.hpp"

namespace ft
{
	template <typename Key, typename T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{

		public:
			typedef				Key															key_type;
			typedef				T															mapped_type;
			typedef typename	ft::pair<const Key, T>										value_type;
			typedef				Compare														key_compare;
			typedef				Alloc														allocator_type;
			typedef	typename	allocator_type::reference									reference;
			typedef	typename	allocator_type::const_reference								const_reference;
			typedef	typename	allocator_type::pointer										pointer;
			typedef	typename	allocator_type::const_pointer								const_pointer;
			typedef typename	allocator_type::size_type									size_type;

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;

				protected:
					key_compare	_comparator;

					value_compare(key_compare comparator = key_compare()) : _comparator(comparator) {};

					value_compare &	operator=(const value_compare & rhd)
					{
						this->_comparator = rhd._comparator;
						return (*this);
					};

				public:

					bool	operator()(const value_type & lhd, const value_type & rhd)	const
					{
						return (this->_comparator(lhd.first, rhd.first));
					};
			};

		private:
			typedef				RedBlackTree <value_type, value_compare, allocator_type>	Tree;

		public:
			typedef typename	Tree::iterator												iterator;
			typedef typename	Tree::const_iterator										const_iterator;
			typedef typename	Tree::reverse_iterator										reverse_iterator;
			typedef typename	Tree::const_reverse_iterator								const_reverse_iterator;
			typedef typename	ft::iterator_traits<iterator>::difference_type				difference_type;

		private:
			key_compare		_comparator;
			Tree			_tree;

		public:

			explicit map(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
				: _comparator(key_compare(comp)), _tree(Tree(alloc, this->_comparator))
			{};

			template <typename InputIter>
			map(InputIter first, InputIter last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
				:	_comparator(key_compare(comp)), _tree(Tree(alloc, this->_comparator))
			{
				for (; first != last; first++)
					this->_tree.insert(*first);
			};

			map(const map & src)
				: _comparator(src._comparator), _tree(src._tree)
			{};

			~map() {};

			map &	operator=(const map & rhd)
			{
				this->_comparator = rhd._comparator;
				this->_tree = rhd._tree;

				return (*this);
			};

			mapped_type &	operator[](const key_type & key)
			{
				iterator	founded = this->find(key);

				if (founded != this->end())
					return ((*founded).second);
				
				return ((*this->insert(value_type(key, mapped_type())).first).second);
			};

			iterator	begin(void)
			{
				return (this->_tree.begin());
			};

			const_iterator	begin(void)	const
			{
				return (this->_tree.cbegin());
			};

			iterator	end(void)
			{
				return (this->_tree.end());
			};

			const_iterator	end(void)	const
			{
				return (this->_tree.cend());
			};

			reverse_iterator	rbegin(void)
			{
				return (this->_tree.rbegin());
			};

			const_reverse_iterator	rbegin(void)	const
			{
				return (this->_tree.crbegin());
			};

			reverse_iterator	rend(void)
			{
				return (this->_tree.rend());
			};

			const_reverse_iterator	rend(void)	const
			{
				return (this->_tree.crend());
			};

			const_iterator	cbegin(void)	const
			{
				return (this->_tree.cbegin());
			};

			const_iterator	cend(void)	const
			{
				return (this->_tree.cend());
			};

			const_reverse_iterator	crbegin(void)	const
			{
				return (this->_tree.crbegin());
			};

			const_reverse_iterator	crend(void)	const
			{
				return (this->_tree.crend());
			};

			bool	empty(void)	const
			{
				return (!this->_tree.size);
			};

			size_type	size(void)	const
			{
				return (this->_tree.size);
			};

			size_type	max_size(void)	const
			{
				return (this->_tree.allocator.max_size());
			};

			mapped_type &	at(const key_type & key)
			{
				iterator	founded = this->find(key);

				if (founded == this->end())
					throw std::out_of_range("map");
				
				return ((*founded).second);
			};

			const mapped_type &	at(const key_type & key)	const
			{
				const_iterator	founded = this->find(key);

				if (founded == this->end())
					throw std::out_of_range("map");
				
				return ((*founded).second);
			};

			ft::pair<iterator, bool>	insert(const value_type & val)
			{
				return (this->_tree.insert(val));
			};

			iterator	insert(iterator position, const value_type & val)
			{
				return (this->_tree.insert(val, position.current).first);
			};

			template <typename InpIter>
			void	insert(InpIter first, InpIter last)
			{
				for (; first != last; first++)
					this->insert(*first);
			};

			void	erase(iterator position)
			{
				this->_tree.erase(position.current);
			};

			size_type	erase(const key_type & key)
			{
				iterator	founded = this->find(key);

				if (founded == this->end())
					return (0);
				
				this->_tree.erase(founded.current);
				return (1);
			};

			void	erase(iterator first, iterator last)
			{
				for (; first != last; first++)
					this->erase(first);
			};

			void	swap(map & ref)
			{
				this->_tree.swap(ref._tree);
			};

			void	clear(void)
			{
				this->_tree.clear();
			};

			key_compare	key_comp(void)	const
			{
				return (this->_comparator);
			};

			value_compare	value_comp(void)	const
			{
				return (this->_tree.comparator);
			};

			iterator	find(const key_type & key)
			{
				return (this->_tree.find(value_type(key, mapped_type())));
			};

			const_iterator	find(const key_type & key)	const
			{
				return (this->_tree.find(value_type(key, mapped_type())));
			};

			size_type	count(const key_type & key)	const
			{
				return (this->find(key) != this->end());
			};

			iterator	lower_bound(const key_type & key)
			{
				return (this->_tree.lower_bound(value_type(key, mapped_type())));
			};

			const_iterator	lower_bound(const key_type & key)	const
			{
				return (this->_tree.lower_bound(value_type(key, mapped_type())));
			};

			iterator	upper_bound(const key_type & key)
			{
				return (this->_tree.upper_bound(value_type(key, mapped_type())));
			};

			const_iterator	upper_bound(const key_type & key)	const
			{
				return (this->_tree.upper_bound(value_type(key, mapped_type())));
			};

			ft::pair<iterator, iterator>	equal_range(const key_type & key)
			{
				return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
			};

			ft::pair<const_iterator, const_iterator>	equal_range(const key_type & key)	const
			{
				return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
			};

			allocator_type	get_allocator(void)	const
			{
				return (this->_tree.allocator);
			};
	};
};

#endif
