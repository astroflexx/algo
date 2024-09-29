// Z-function

// Given a string s, compute the z-function for the string
// z[i] = how many characters starting from index i match the prefix of string s
// z[0] = 0, it is generally not well defined (doesn't matter what you put there)

// if the current index is inside the z-box, we take z[i - l] as an initial answer
// and run the naive method from index i + z[i] to improve our answer
// make sure the length is capped by the index we have explored so far (till r)
// so we take min(r - i + 1, z[i - l]) as the initial answer

// else if the current index is outside the z-box
// run the naive method from the current index

// at the end, update the z-box if necessary

vector<ll> z_function(string s)
{
    ll n = (ll)s.length();

    vector<ll> z(n, 0);
    z[0] = 0;

    ll l = 0, r = 0;

    for (ll i = 1; i < n; i++)
    {
        if (i <= r)
        {
            z[i] = min(r - i + 1, z[i - l]);
        }

        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
            z[i]++;
        }

        if (i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}