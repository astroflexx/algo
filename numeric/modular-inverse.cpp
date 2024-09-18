// Modular Inverse (modinv)

// Given a number a and mod m, consider the equation a * ainv = 1 (mod m)
// Basically (a * ainv) % m = 1
// ainv is the modular inverse of a

// Uses extended euclidean algorithm to find x for a.x + m.y = 1
// then make x positive and take mod
// that gives us the modular inverse of a

// Example: the modular inverse of 3 wrt 7 is 5
// (3 * 5) % 7 = 1
// 15 % 7 = 1

// Works in O(log(min(a, m))) time

pair<ll, ll> extended_euclidean(ll a, ll b)
{
    if (b == 0)
    {
        return {1, 0};
    }

    auto [x, y] = extended_euclidean(b, a % b);

    return {y, x - y * (a / b)};
}

ll modinv(ll a, ll m)
{
    ll x = extended_euclidean(a, m).first;

    return (x % m + m) % m;
}