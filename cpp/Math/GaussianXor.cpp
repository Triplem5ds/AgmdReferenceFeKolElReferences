/*
    Some applications
    If you want to find the maximum in xor subset
    just ans = max(ans, ans ^ p[i]) for all i
    if you want to count the number of subsets with a certain value
    check all different subsets of p
*/
ll p[66];
bool add(ll x) {
    for(int i = 60; (~i) && x; --i) {
        if(x >> i & 1) {
            if(!p[i]) {
                p[i] = x;
                return true;
            }   else {
                x ^= p[i];
            }
        }
    }
    return false;
}