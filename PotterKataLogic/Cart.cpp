// PotterKataLogic.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Cart.h"

#include <algorithm>

POTTERKATALOGIC_API const float RETAIL_BOOK_PRICE = 8.0f;

class SumWithDiscount {
private:
	float total;

public:
	SumWithDiscount() : total(0.0f) {}

	void operator()(const unordered_set<int>& set) {
		float discount;
		int count = set.size();

		switch (count) {
		case 2:
			discount = 0.95f;
			break;

		case 3:
			discount = 0.90f;
			break;

		case 4:
			discount = 0.80f;
			break;

		case 5:
			discount = 0.75f;
			break;

		default:
			discount = 1.0f;
		}

		total += count * RETAIL_BOOK_PRICE * discount;
	}

	operator float() {
		return total;
	}
};

void Cart::optimizeSets() {
	vector<unordered_set<int>*> full_sets;
	vector<unordered_set<int>*> half_sets;

	for_each(begin(m_sets), end(m_sets), [&](unordered_set<int> &s) { if (s.size() == 5) full_sets.push_back(&s); else if (s.size() ==3) half_sets.push_back(&s); });
	int full_count = full_sets.size();
	int half_count = half_sets.size();

	if (full_count > 0 && half_count > 0) {
		int max = full_count > half_count ? half_count : full_count;

		for (int i = 0; i < max; i++) {
			unordered_set<int> &half_set = *half_sets[i];
			unordered_set<int> &full_set = *full_sets[i];

			unordered_set<int>::iterator book = find_if(full_set.begin(), full_set.end(), [half_set](int id) { return half_set.find(id) == half_set.end(); }); 
			half_set.insert(*book);
			full_set.erase(*book);
		}
	}
}

void Cart::AddBook(int bookId) {
	vector<unordered_set<int>>::iterator foundSet = find_if(m_sets.begin(), m_sets.end(), [bookId](unordered_set<int> s) { return s.find(bookId) == s.end(); });

	if (foundSet == m_sets.end()) {
		unordered_set<int> newSet;
		newSet.insert(bookId);
		m_sets.push_back(newSet);
	} else {
		foundSet->insert(bookId);
	}
}

float Cart::CalculateTotal() {
	optimizeSets();
	return for_each(m_sets.begin(), m_sets.end(), SumWithDiscount());
}