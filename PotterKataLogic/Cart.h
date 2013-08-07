// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the POTTERKATALOGIC_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// POTTERKATALOGIC_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef POTTERKATALOGIC_EXPORTS
#define POTTERKATALOGIC_API __declspec(dllexport)
#else
#define POTTERKATALOGIC_API __declspec(dllimport)
#endif

extern POTTERKATALOGIC_API const float RETAIL_BOOK_PRICE;

#include <vector>
#include <unordered_set>

using namespace std;

class POTTERKATALOGIC_API Cart {
public:
	Cart(void) {}

	void AddBook(int bookId);
	float CalculateTotal();

private:
	vector<unordered_set<int>> m_sets;
	void optimizeSets();
};