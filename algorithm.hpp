#ifndef ALGORITHM
# define ALGORITHM

namespace ft {
	template <typename InpIter1, typename InpIter2>
	bool	equal(InpIter1 first1, InpIter1 last, InpIter2 first2)
	{
		while (first1 != last)
		{
			if (*first1 != *first2)
				return (false);
			first1++;
			first2++;
		}
		return (true);
	};

	template <typename InpIter1, typename InpIter2, typename BinPred>
	bool	equal(InpIter1 first1, InpIter1 last, InpIter2 first2, BinPred pred)
	{
		while (first1 != last)
		{
			if (!pred(*first1, *first2))
				return (false);
			first1++;
			first2++;
		}
		return (true);
	};

	// Cравнение строк
	template <typename InpIter1, typename InpIter2>
	bool	lexicographical_compare(InpIter1 first1, InpIter1 last, InpIter2 first2, InpIter2 last2)
	{
		while (first1 != last)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			if (*first1 < *first2)
				return (true);
			first1++;
			first2++;
		}

		return (first2 != last2);
	};

	template <typename InpIter1, typename InpIter2, typename Comparator>
	bool	lexicographical_compare(InpIter1 first1, InpIter1 last, InpIter2 first2, InpIter2 last2, Comparator comp)
	{
		while (first1 != last)
		{
			if (first2 == last2 || comp(*first1, *first2))
				return (false);
			if (!comp(*first1, *first2))
				return (true);
			first1++;
			first2++;
		}

		return (first2 != last2);
	};
};

#endif
