#include "stdafx.h"
#include "CppUnitTest.h"

#include "../PotterKataLogic/Cart.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PotterKataTests
{		
	TEST_CLASS(CartTests)
	{
	private:
		void test_single_set(int bookCount, float expectedDiscount) {
			float expectedCost = RETAIL_BOOK_PRICE * bookCount * expectedDiscount;

			Cart cart;
			for (int i = 0; i < bookCount; i++) {
				cart.AddBook(i);
			}

			Assert::AreEqual(expectedCost, cart.CalculateTotal());
		}

	public:
		TEST_METHOD(AddingOneBookCostsFullRetail) {
			test_single_set(1, 1.0f);
		}

		TEST_METHOD(AddingSameBookAgainCostsFullRetail) {
			float expectedCost = RETAIL_BOOK_PRICE * 2;
			Cart cart;

			cart.AddBook(1);
			cart.AddBook(1);

			Assert::AreEqual(expectedCost, cart.CalculateTotal());			
		}

		TEST_METHOD(AddingSecondDifferentBookGetsDiscount) {
			test_single_set(2, 0.95f);
		}

		TEST_METHOD(AddingThirdDifferentBookGetsDiscount) {
			test_single_set(3, 0.90f);
		}

		TEST_METHOD(AddingFourthDifferentBookGetsDiscount) {
			test_single_set(4, 0.80f);
		}

		TEST_METHOD(AddingFifthDifferentBookGetsDiscount) {
			test_single_set(5, 0.75f);
		}

		TEST_METHOD(TwoSetsGetCorrectDiscount) {
			float expectedCost = RETAIL_BOOK_PRICE * 4 * 0.95f;
			Cart cart;

			cart.AddBook(1);
			cart.AddBook(2);
			cart.AddBook(1);
			cart.AddBook(2);

			Assert::AreEqual(expectedCost, cart.CalculateTotal());			
		}

		TEST_METHOD(AdjustsSetsForBestDiscount) {
			float expectedCost = RETAIL_BOOK_PRICE * 8 * 0.80f;

			Cart cart;

			cart.AddBook(1);
			cart.AddBook(1);
			cart.AddBook(2);
			cart.AddBook(2);
			cart.AddBook(3);
			cart.AddBook(3);
			cart.AddBook(4);
			cart.AddBook(5);

			Assert::AreEqual(expectedCost, cart.CalculateTotal());			
		}

		TEST_METHOD(PassesKataTest) {
			float expectedCost = 3 * (RETAIL_BOOK_PRICE * 5 * 0.75f) + 2 * (RETAIL_BOOK_PRICE * 4 * 0.8f);
			Cart cart;

			for (int i = 0; i < 5; i++) {
				cart.AddBook(1);
				cart.AddBook(2);
				cart.AddBook(4);
			}

			for (int i = 0; i < 4; i++) {
				cart.AddBook(3);
				cart.AddBook(5);
			}

			Assert::AreEqual(expectedCost, cart.CalculateTotal());			
		}
	};
}