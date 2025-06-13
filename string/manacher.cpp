// Manacher's algorithm

// calculate d_odd and d_even for a string
// d[i] = longest palindrome with s[i] as center 
// eg: d aab b baa c, d_odd[4] = 4, d_even[4] = 2
// compute both d_odd and d_even by adding # between characters
// works basically the same as z-function 

// d[2 * i] = 2 * d_even[i] + 1
// d[2 * i + 1] = 2 * d_odd[i]

// d_even[i] = (d[2 * i] - 1) / 2
// d_odd[i] = d[2 * i + 1] / 2

// sources:
// cp-algorithms.com (https://cp-algorithms.com/string/manacher.html)

vector<ll> manacher(string &s) {
    string t = "";
    for (auto &c : s) {
        t += string("#") + c;
    }
    t += "#";
    ll n = (ll) t.length();
    t = "$" + t + "^";
    vector<ll> p(n + 2);
    ll l = 0, r = 1;
    for (ll i = 1; i <= n; i++) {
        if (i < r) {
            p[i] = min(r - i, p[l + (r - i)]);
        }
        while (t[i - p[i]] == t[i + p[i]]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<ll> (begin(p) + 1, end(p) - 1);
}