#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    freopen("robot6.in", "r", stdin);
    freopen("robot6.out", "w", stdout);

    //ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    int c;
    string s;

    cin >> c;
    cin >> s;

    int n = (int)(s.size());

    if (c == 1)
    {
        int ans = 0;

        for (int i = 0; i < n; i++)
            if (s[i] == 'A') ans++;

        cout << ans << '\n';
    }
    else
        if (c == 2)
        {
            int i = 0;
            int x = 0;

            for (; i < n; i++) {

                if (s[i] == 'T') break;

                if (s[i] == 'A') cout << x; else
                    if (s[i] == 'S') {

                        int cur = 0;
                        i++;

                        while (i < n && s[i] >= '0' && s[i] <= '9') {

                            cur = cur * 10 + s[i] - 48; i++;
                        }

                        i--;
                        x -= cur;

                        while (x < 0) x += 10;

                    }
                    else
                        if (s[i] == 'D') {

                            int cur = 0;
                            i++;

                            while (i < n && s[i] >= '0' && s[i] <= '9') {

                                cur = cur * 10 + s[i] - 48; i++;
                            }

                            i--;
                            x += cur;

                            x %= 10;
                        }
            }
        }
        else
        {
            int x = 0;
            string ans = "";

            for (int i = 0; i < n; i++)
            {
                int v = s[i] - 48;

                int go_left = 0;
                int go_right = 0;

                if (v > x) {

                    go_left = x + 10 - v;
                    go_right = v - x;
                }
                if (v < x) {

                    go_left = x - v;
                    go_right = 10 - x + v;
                }

                if (min(go_left, go_right) != 0) {

                    if (go_left < go_right) ans = ans + "S" + (char)(go_left + 48); else
                        ans = ans + "D" + (char)(go_right + 48);
                }

                ans += "A";
                x = v;
            }

            ans += "T";

            cout << ans << '\n';
        }

    return 0;
}

	