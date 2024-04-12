// Hacer funcion para determinar si una frase o palabra es palindromo con punteros
#include <iostream>

using namespace std;

bool Palindromo(char* C)
{
	char* p = C;
	
	while (C < p)
	{
		while (*C == ' ') C++;
		while (*p == ' ') p--;

		if (*C != *p) return false;

		C++;
		p--;
	}
	return true;
}

int main()
{
	char A[100] = "Anita lava la tina";
	
	if (Palindromo(A))
		cout << "Si es palindromo";
	else
		cout << "No es palindromo";
}
