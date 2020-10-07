#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#define SZ(x) (int)(x.size())

using namespace std;

int n;

int main()
{
	freopen("b210.in", "r", stdin);
	freopen("b210.out", "w", stdout);
	
	cin >> n;
	
	vector <int> bits;
	
	while (n > 0)
	{
		bits.push_back(n % 2);
		
		n /= 2;
	}
	
	reverse(bits.begin(), bits.end());
	
	int best = n;
	
	for (int i = 0; i < SZ(bits); i++)
	{
		int x = bits[0];
		
		for (int j = 0; j < SZ(bits) - 1; j++) swap(bits[j], bits[j + 1]);
		
		bits[SZ(bits) - 1] = x;
		
		int cur = 0;
		
		for (int j = SZ(bits) - 1, p = 1; j >= 0; j--, p *= 2)
			if (bits[j] == 1) cur += p;
			
		best = max(best, cur);
	}
	
	cout << best;
	
	return 0;
}