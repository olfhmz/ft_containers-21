#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

# include <stdexcept>
# include <memory>
# include "pair.hpp"
# include "tree_iterator.hpp"
# include "tree_node.hpp"
# include "reverse_iterator.hpp"

# include <iostream>
# include <string>

namespace ft
{
	template <typename T, typename Comparator, typename Alloc>
	class RedBlackTree
	{
		public:
			typedef typename	ft::TreeNode<T>										Node;

		public:
			typedef typename	Alloc::template rebind<Node>::other					allocator_type;
			typedef typename	allocator_type::size_type							size_type;
			typedef typename	ft::tree_iterator<T, Node >							iterator;
			typedef typename	ft::tree_iterator<const T, Node >					const_iterator;
			typedef typename	ft::reverse_iterator<iterator>						reverse_iterator;
			typedef typename	ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef typename	ft::iterator_traits<iterator>::difference_type		difference_type;

		public:

			Node			*	root;
			allocator_type		allocator;
			Comparator			comparator;
			size_type			size;

		public:

			explicit RedBlackTree(allocator_type const & alloc = allocator_type(), Comparator const & comparator = Comparator())
				: root(NULL), allocator(allocator_type(alloc)), comparator(Comparator(comparator)), size(0)
			{};

			explicit RedBlackTree(const RedBlackTree & src)
				: root(NULL), allocator(src.allocator), comparator(src.comparator), size(src.size)
			{
				this->_copy(src.root, &this->root);
			};

			~RedBlackTree()
			{
				this->clear();
			};

			RedBlackTree &	operator=(const RedBlackTree & src)
			{
				this->clear();
				this->size = src.size;

				this->_copy(src.root, &this->root);

				return (*this);
			};

		private:

			void	_copy(const Node * src, Node ** dst, Node * parent = NULL)
			{
				if (!src)
					return ;

				*dst = this->allocator.allocate(1);
				this->allocator.construct(*dst, *src);
				this->_copy(src->left, &(*dst)->left, *dst);
				this->_copy(src->left, &(*dst)->right, *dst);
			};

			void	_updateRoot(void)
			{
				if (!this->root)
					return ;
					
				while (this->root->parent)
					this->root = this->root->parent;				
			};

			static void	_insertionRebalance(Node * start)
			{
				Node *	uncle = start->getUncle();

				if (!start->parent)
					start->red = false;
				else if (start->parent->red && !start->parent->parent)
					start->parent->red = false;
				else if (start->parent->red && (!uncle || !uncle->red))
				{
					if (!start->isOuterGrandchild())
					{
						Node *	buf = start->parent;

						start->getOnSurface();
						start = buf;
					}

					start->parent->getOnSurface();
					start->parent->red = false;

					if (start->parent->left)
						start->parent->left->red = true;
					if (start->parent->right)
						start->parent->right->red = true;
				}
				else if (start->parent->red && uncle->red)
				{
					start->parent->red = false;
					uncle->red = false;
					start->parent->parent->red = true;
					_insertionRebalance(start->parent->parent);
				}
			};

			static void	_deletionRebalance(Node * start)
			{
				if (!start->parent)
					return ;
				
				Node *	sibling = start->getSibling();

				if (!sibling->red && sibling->allChildrensBlack())
				{
					sibling->red = true;

					if (!start->parent->red)
						_deletionRebalance(start->parent);
					else
						start->parent->red = false;
				}
				else if (!sibling->red)
				{
					Node *	closest = *sibling->dirs[start->getDir()];

					if (closest && closest->red)
					{
						closest->getOnSurface();
						closest->red = false;
						sibling = closest;
					}

					sibling->getOnSurface();
					sibling->red = start->parent->red;
					start->parent->red = false;
				}
				else if (sibling->red)
				{
					sibling->getOnSurface();
					sibling->red = false;
					start->parent->red = true;
					_deletionRebalance(start);
				}
			};

			void	_checkBranches(Node * start, int ref_height, int cur_height = 0)	const
			{
				if (start && start->red && start->parent && start->parent->red)
					throw std::logic_error("red child have red parent");

				cur_height += (!start || !start->red);

				if (!start)
				{
					if (cur_height != ref_height)
					{
						std::cout << "cur: " << cur_height << " ref: " << ref_height << std::endl;
						throw std::logic_error("number of black nodes volatile");
					}

					return ;
				}

				this->_checkBranches(start->left, ref_height, cur_height);
				this->_checkBranches(start->right, ref_height, cur_height);
			};

			void	_checkTree(void)	const
			{
				if (!this->root)
					return ;

				Node *	cursor = this->root;
				int		height = 1;

				while (cursor)
				{
					height += !cursor->red;
					cursor = cursor->left;
				}

				this->_checkBranches(this->root, height);
			};

			void	_replaceNode(Node * src, Node * dst)
			{
				if (src)
					src->stealLinks(dst);
				else
					*dst->parent->dirs[dst->getDir()] = NULL;

				this->allocator.destroy(dst);
				this->allocator.deallocate(dst, 1);
			};

			void	_deleteNode(Node *node)
			{
				Node *	child = node->getChild();

				*node->parent->dirs[node->getDir()] = child;
				if (child)
				{
					child->parent = node->parent;
					child->red = node->red;
				}

				this->allocator.destroy(node);
				this->allocator.deallocate(node, 1);
			};

			Node *	_internalDeletionHandler(Node * node)
			{
				Node *	cursor = NULL;

				if (node->left && node->right)
				{
					cursor = node->left;
					while (cursor->right)
						cursor = cursor->right;
				}
				else
					return (node);
				
				Node *	dummy = this->allocator.allocate(1);

				this->allocator.construct(dummy, Node());

				dummy->stealLinks(cursor);

				this->_replaceNode(cursor, node);

				return (dummy);
			};

			Node *	_iteratorRoutine(bool end)	const
			{
				Node *	cursor = this->root;

				while (cursor && *cursor->dirs[end])
					cursor = *cursor->dirs[end];

				return (cursor);
			};

			Node *	_findPlaceForInsert(const T & val, Node * hint = NULL)	const
			{
				if (hint && hint != this->root)
				{
					if (this->comparator(val, hint->value))
						return (this->_findPlaceForInsert(val));
					if (this->comparator(hint->parent->value, val))
						return (this->_findPlaceForInsert(val));
				}
				else if (!hint)
					hint = this->root;

				Node *	crsr = hint;

				while (crsr)
				{
					if (crsr->left && this->comparator(val, crsr->value))
						crsr = crsr->left;
					else if (crsr->right && this->comparator(crsr->value, val))
						crsr = crsr->right;
					else
						break;
				}
				
				return (crsr);
			};

			static void	_print_value(Node * node, std::string before = std::string(""), std::string after = std::string(""))
			{
				if (before.size())
					std::cout << before;
				if (node)
					std::cout << node->value.first << " " << node->value.second << " color: " << node->red;
				else
					std::cout << "(null)";
				if (after.size())
					std::cout << after;
				std::cout << std::endl;
			};

		public:

			ft::pair<iterator, bool>	insert(const T & val, Node * hint = NULL)
			{
				Node *	parent = this->_findPlaceForInsert(val, hint);
				Node **	insertion_side = &parent;

				if (!parent)
					insertion_side = &this->root;
				else if (this->comparator(val, parent->value))
					insertion_side = &parent->left;
				else if (this->comparator(parent->value, val))
					insertion_side = &parent->right;
				else
					return (ft::make_pair(iterator(parent), false));

				*insertion_side = this->allocator.allocate(1);
				this->allocator.construct(*insertion_side, Node(val, parent));

				return (ft::make_pair(iterator(*insertion_side), bool(++this->size)));
			};

			iterator	find(const T & val)
			{
				Node *	founded = this->_findPlaceForInsert(val);

				if (founded
					&& !this->comparator(val, founded->value)
					&& !this->comparator(founded->value, val))
					return (iterator(founded));
				return (this->end());
			};

			const_iterator	find(const T & val)	const
			{
				Node *	founded = this->_findPlaceForInsert(val);

				if (founded
					&& !this->comparator(val, founded->value)
					&& !this->comparator(founded->value, val))
					return (const_iterator(founded));
				return (this->cend());
			};

			iterator	lower_bound(const T & key)
			{
				Node *	founded = this->_findPlaceForInsert(key);

				if (!founded
					|| (!this->comparator(founded->value, key)
						&& !this->comparator(key, founded->value)))
					return (iterator(founded));
				return (++iterator(founded));
			};

			const_iterator	lower_bound(const T & key)	const
			{
				Node *	founded = this->_findPlaceForInsert(key);

				if (!founded
					|| (!this->comparator(founded->value, key)
						&& !this->comparator(key, founded->value)))
					return (const_iterator(founded));
				return (++const_iterator(founded));
			};

			iterator	upper_bound(const T & key)
			{
				iterator	it = this->lower_bound(key);

				if (it != this->end()
					&& !this->comparator(*it, key) && !this->comparator(key, *it))
					return (++it);
				return (it);
			};

			const_iterator	upper_bound(const T & key)	const
			{
				const_iterator	it = this->lower_bound(key);

				if (it != this->end()
					&& !this->comparator(*it, key) && !this->comparator(key, *it))
					return (++it);
				return (it);
			};

			void	erase(Node * node)
			{
				if (node == this->root)
				{
					this->root = node->left;
					if (!node->left)
						this->root = node->right;
				}

				node = _internalDeletionHandler(node);
				
				Node *	child = node->getChild();

				if (!node->red && !child)
					_deletionRebalance(node);
				
				this->_deleteNode(node);
				this->_updateRoot();
				this->_checkTree();
				this->size--;
			};

			void	clear(Node * start = NULL)
			{
				if (!start)
					start = this->root;
				if (!start)
					return ;

				if (start->left)
					this->clear(start->left);
				if (start->right)
					this->clear(start->right);
				
				this->allocator.destroy(start);
				this->allocator.deallocate(start, 1);

				if (start != this->root)
					return ;

				this->root = NULL;
				this->size = 0;
			};

			iterator	begin(void)
			{
				return (iterator(this->_iteratorRoutine(false)));
			};

			const_iterator	cbegin(void)	const
			{
				return (const_iterator(this->_iteratorRoutine(false)));
			};

			iterator	end(void)
			{
				return (++iterator(this->_iteratorRoutine(true)));
			};

			const_iterator	cend(void)	const
			{
				return (++const_iterator(this->_iteratorRoutine(true)));
			};

			reverse_iterator	rbegin(void)
			{
				return (reverse_iterator(this->end()));
			};

			const_reverse_iterator	crbegin(void)	const
			{
				return (const_reverse_iterator(this->cend()));
			};

			reverse_iterator	rend(void)
			{
				return (reverse_iterator(this->begin()));
			};

			const_reverse_iterator	crend(void)	const
			{
				return (const_reverse_iterator(this->begin()));
			};

			void	swap(const RedBlackTree & ref)
			{
				Node *	buf = this->root;

				this->root = ref.root;
				ref.root = buf;
			};
	};
}

#endif
