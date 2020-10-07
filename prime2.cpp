#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

typedef long long int ll;

int type, n;
int fib[100], fr[15];
ll t[55];
bool n_prime[10000050];
vector <int> primes;

bool prime(int x)
{
	for (int i = 2; 1LL * i * i <= x; i++)
		if (x % i == 0) return false;
		
	return true;
}

int get_nr_digits(ll x)
{
	int sol = 0;
	
	while (x > 0) {
		
		sol++; x = x / 10;
	}
	
	return sol;
}

int get_prime_length(ll x)
{
	int sol = 0;
	
	for (ll i = 2; i * i <= x; i++) 
		if (x % i == 0) {
			
			int nr = 0;
			
			while (x % i == 0) {
				
				nr++;
				
				x = x / i;
			}
			
			sol += get_nr_digits(i);
			
			if (nr > 1) sol += get_nr_digits(nr);
	}
	
	if (x > 1) sol += get_nr_digits(x);
	
	return sol;
}

int main()
{
	freopen("prime2.in", "r", stdin);
	freopen("prime2.out", "w", stdout);
	
	cin >> type;
	cin >> n;
	
	for (int i = 1; i <= n; i++) cin >> t[i];
	
	fib[1] = 0;
	fib[2] = 1;
		
	for (int i = 3; i <= 45; i++) fib[i] = fib[i - 1] + fib[i - 2];
	
	n_prime[1] = true;
	
	for (int i = 2; i <= 10000000; i++)
		if (!n_prime[i]) {
			
			for (int j = 2 * i; j <= 10000000; j += i) n_prime[j] = true;
			
		}
		
	for (int i = 2; i <= 10000000; i++)
		if (!n_prime[i]) primes.push_back(i);
		
	//for (int i = 1; i <= 100; i++) cout << primes[i - 1] << endl;
	
	int answer = 0;
		
	if (type == 1) {
		
		for (int i = 1; i <= n; i++) {
			
			bool fibo = false;
			
			for (int j = 1; j <= 45; j++)
				if (fib[j] == t[i]) fibo = true;
			
			if (fibo && prime(t[i])) answer++;
		}
		
	} else
	if (type == 2) {
	
		for (int i = 1; i <= n; i++) {
			
			int nr_digits = get_nr_digits(t[i]);
			
			if (nr_digits > get_prime_length(t[i])) answer++;
		}
		
		
	} else {
		
		for (int i = 1; i <= n; i++) {
			
			for (int j = 0; j < (int)(primes.size()) && primes[j] < t[i]; j++)
				if (!n_prime[t[i] - primes[j]]) {
					
					answer++; break;
				}
			
		}
		
		answer = n - answer;
	}
	
	cout << answer;
	
	return 0;
}