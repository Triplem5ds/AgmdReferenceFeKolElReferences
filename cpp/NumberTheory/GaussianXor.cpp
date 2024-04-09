void insertVector(int mask) {
    for (int i = d - 1; i >= 0; i--) {
        if ((mask & 1 << i) == 0) continue;
        if (!basis[i]) {
            basis[i] = mask;
            return;
        }
        mask ^= basis[i];
    }
}