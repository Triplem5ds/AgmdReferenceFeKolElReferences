
mt19937_64 mrand(chrono::steady_clock::now().time_since_epoch().count());
struct Node {
    int key, pri = mrand(), sz = 1;
    int lz = 0;
    int idx;
    array<Node*, 2> c = {NULL,NULL};
    Node(int key, int idx) : key(key), idx(idx) {}
};
int getsz(Node* t){
    return t ? t->sz : 0;
}
Node* calc(Node* t) {
    t->sz = 1 + getsz(t->c[0]) + getsz(t->c[1]);
    return t;
}
void prop(Node* cur) {
    if(!cur || !cur->lz)
        return;
    cur->key += cur->lz;
    if(cur->c[0])
        cur->c[0]->lz += cur->lz;
    if(cur->c[1])
        cur->c[1]->lz += cur->lz;
    cur->lz = 0;
}
array<Node*, 2> split(Node* t, int k) {
    prop(t);
    if(!t)
        return {t, t};
    if(getsz(t->c[0]) >= k) {   ///answer is in left node
        auto ret = split(t->c[0], k);
        t->c[0] = ret[1];
        return {ret[0], calc(t)};
    } else {  ///k > t->c[0]
        auto ret = split(t->c[1], k - 1 - getsz(t->c[0]));
        t->c[1] = ret[0];
        return {calc(t), ret[1]};
    }
}
Node* merge(Node* u, Node* v) {
    prop(u);
    prop(v);
    if(!u || !v)
        return u ? u : v;
    if(u->pri>v->pri) {
        u->c[1] = merge(u->c[1], v);
        return calc(u);
    } else {
        v->c[0] = merge(u, v->c[0]);
        return calc(v);
    }
}
int cnt(Node* cur, int x) {
    prop(cur);
    if(!cur)
        return 0;
    if(cur->key <= x)
        return getsz(cur->c[0]) + 1 + cnt(cur->c[1], x);
    return cnt(cur->c[0], x);
}
Node* ins(Node* root, int val, int idx, int pos) {
    auto splitted = split(root, pos);
    root = merge(splitted[0], new Node(val, idx));
    return merge(root, splitted[1]);
}
