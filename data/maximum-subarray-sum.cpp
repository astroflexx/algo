// Maximum Subarray Sum

// Pass an array and a range [l, r]
// Returns the maximum subarray sum in the range [l, r] (inclusive indexes)
// We take the max element in the range as a starting answer, change this if you want
// Uses Kadane's algorithm

// O(n) where n = r - l + 1, we iterate from l to r

ll maximum_subarray_sum(vector<ll> &arr, ll l, ll r)
{
    ll ans = *max_element(arr.begin() + l, arr.begin() + r);
    ll sum = 0;
 
    for (ll i = l; i <= r; i++)
    {
        sum += arr[i];
        ans = max(ans, sum);
        sum = max(sum, 0LL);
    }
 
    return ans;
}