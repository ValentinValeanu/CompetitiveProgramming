#include <stdio.h>
#include <vector>
#include <algorithm>
#define nmax 10010

using namespace std;

class BigInteger
{
	public:
		
		vector <int> vc;
	
	public:

		BigInteger();
		int Size();
		int GetIndex(int);
		void Multiply(int);
		void Print();
		void Fill(BigInteger);
		void Sum(BigInteger);
};

BigInteger::BigInteger()
{
	vc.clear();

	vc.push_back(1);
}

int BigInteger::Size()
{
	return vc.size();
}

int BigInteger::GetIndex(int index)
{
	if (index >= vc.size()) return 0; else
		return vc[index];
}

void BigInteger::Multiply(int x)
{
	if (x == 0) {

		vc.clear();
		vc.push_back(0);

		return;
	}

	int r = 0;

	for (int i = 0; i < (int)(vc.size()); i++) {

		vc[i] = vc[i] * x + r;

		r = vc[i] / 10;
		vc[i] = vc[i] % 10;
	}

	while (r > 0) { vc.push_back(r % 10); r = r / 10; }
}

void BigInteger::Sum(BigInteger n2)
{
	int r = 0;

	for (int i = 0; i < max((int)vc.size(), n2.Size()); i++) {

		int x;
		
		if (i >= vc.size()) {

			x = n2.GetIndex(i) + r;
			vc.push_back(x % 10);
		}
		else {

			x = vc[i] + n2.GetIndex(i) + r;

			vc[i] = x % 10;
		}

		r = x / 10;
	}

	if (r > 0) vc.push_back(r);
}

void BigInteger::Fill(BigInteger b)
{
	vc.clear();

	for (int i = 0; i < b.Size(); i++) vc.push_back(b.GetIndex(i));
}

void BigInteger::Print()
{
	for (int i = vc.size() - 1; i >= 0; i--) printf("%d", vc[i]);

	printf("\n");
}

int type, n, r;
int fr[nmax];
char s[nmax];

int main()
{
	freopen("roua.in", "r", stdin);
	freopen("roua.out", "w", stdout);

	scanf("%d", &type);
	scanf("%d %d", &n, &r);

	if (type == 1) {

		scanf("%s", s + 1);

		for (int i = 1; i <= n; i++)
			if (s[i] == 'r') fr[i] = fr[i - 1] + 1; else
				fr[i] = fr[i - 1];

		int answer = 0;

		for (int i = r; i <= n; i++)
			if (fr[i] - fr[i - r] == r - 1) answer++;

		printf("%d", answer);
		
		return 0;
	}

	int a = n / r;
	int b = n % r;

	BigInteger number1, number2;

	for (int i = 1; i <= a; i++) number1.Multiply(3);

	number2.Fill(number1);

	number1.Multiply(r - b);

	number2.Multiply(3);
	number2.Multiply(b);

	number1.Sum(number2);

	number1.Print();

	return 0;
}