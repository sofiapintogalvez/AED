#include <iostream>

using namespace std;

template <class T>
struct ASC
{
	bool operator()(T a, T b)
	{   return a > b;   }
};

template <class T>
struct DESC
{
	bool operator()(T a, T b)
	{	return a < b;   }
};

template <class T, class O>
struct bubble
{
	void operator()(T* ini, T* fin)
	{
		O op;
		bool sigue = true;
		while (ini < fin && sigue)
		{
			sigue = false;
			for (int* p = ini; p < fin; p++)
			{
				if (op(*p, *(p + 1)))
				{
					swap(*p, *(p + 1));
					sigue = true;
				}
			}
			fin--;
		}
	}
};

int main()
{
	bubble<int, ASC<int>> b;

	int A[10] = { 3,5,7,9,1,8,10,6,4,2 };

	b(A, A + 9);

	for (int i = 0; i < 10; i++)
		cout << A[i] << " ";
}
