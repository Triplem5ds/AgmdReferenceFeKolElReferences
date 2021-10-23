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