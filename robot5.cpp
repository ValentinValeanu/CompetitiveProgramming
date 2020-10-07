#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int type, h, m, s, n, t, r, v;
string _last, ss[510];

void increase_time_by_seconds(int seconds) 
{
	s += seconds;
	
	if (s >= 60) {
		
		m = m + s / 60;
		s %= 60;
	}
	
	if (m >= 60) {
		
		h = h + m / 60;
		m %= 60;
	}
}

bool bad(string s)
{
	string odd = "";
	string even = "";
	
	for (int i = 0; i < s.size(); i++) {
		
		if ((s[i] - 48) % 2 == 0) even = even + s[i]; else
			odd = odd + s[i];
	}
	
	sort(odd.begin(), odd.end());
	
	sort(even.begin(), even.end());
	reverse(even.begin(), even.end());
	
	_last = odd + even;
	
	if (_last != s || even.size() == 0 || odd.size() == 0) {
		
		if (even.size() == 0) {
			
			odd.erase(0, 1);
			
			even = even + "0";
		} else
		if (odd.size() == 0) {
			
			even.erase(0, 1);
			
			odd = odd + "9";
		}
		
		_last = odd + even;
		
		return true; 
	
	} else
	return false;
}

int main()
{
	freopen("robot5.in", "r", stdin);
	freopen("robot5.out", "w", stdout);
	
	cin >> type;
	
	cin >> n >> h >> m >> s;
	
	cin >> t >> v >> r;
	
	for (int i = 1; i <= n; i++) cin >> ss[i];
	
	for (int i = 1; i <= n; i++) {
		
		if (i > 1) increase_time_by_seconds(t);
		increase_time_by_seconds(v);
		
		if (bad(ss[i])) {
			
			increase_time_by_seconds(r);
			
			ss[i] = _last;
		}
	}
	
	if (type == 1) cout << h << ' ' << m << ' ' << s; else {
		
		for (int i = 1; i <= n; i++) cout << ss[i] << "\n";	
		
	}
	
	return 0;
}