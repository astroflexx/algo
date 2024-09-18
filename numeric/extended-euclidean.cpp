// Extended Euclidean

// for any 2 integers a and b, gcd(a, b) = g
// we can express g as a linear combination of a and b

// a * x + b * y = g

// finds the solution x and y for the above equation
// x, y can be positive, negative or zero

pair<ll, ll> extended_euclidean(ll a, ll b)
{
    if (b == 0)
    {
        return {1, 0};
    }

    auto [x, y] = extended_euclidean(b, a % b);

    return {y, x - y * (a / b)};
}