struct SA {
    struct node {
        int to[26];
        int link, len, co = 0;

        node() {
            memset(to, 0, sizeof to);
            co = 0, link = 0, len = 0;
        }
    };

    struct LogNode {
        int last, sz;
        vector<pair<pair<int, int>, int>> edges;
        pair<int, int> LinksUpdate = {0, 0};
    };

    int last, sz;
    vector<node> v;
    vector<LogNode> logs;

    SA() {
        v = vector<node>(1);
        last = 0, sz = 1;
    }

    void add_letter(int c) {
        logs.push_back({});
        logs.back().last = last;
        logs.back().sz = sz;

        int p = last;
        last = sz++;
        v.push_back({});
        v[last].len = v[p].len + 1;
        v[last].co = 1;
        for (; v[p].to[c] == 0; p = v[p].link) {
            logs.back().edges.push_back({{p, c}, 0});
            v[p].to[c] = last;
        }
        if (v[p].to[c] == last) {
            v[last].link = 0;
            return;
        }
        int q = v[p].to[c];
        if (v[q].len == v[p].len + 1) {
            v[last].link = q;
            return;
        }
        int cl = sz++;
        v.push_back(v[q]);
        v.back().co = 0;
        v.back().len = v[p].len + 1;
        logs.back().LinksUpdate = {q, v[q].link};
        v[last].link = v[q].link = cl;
        for (; v[p].to[c] == q; p = v[p].link) {
            logs.back().edges.push_back({{p, c}, q});
            v[p].to[c] = cl;
        }
    }
    void rollback() {
        assert(logs.size());
        auto log = logs.back();
        while (v.size() > log.sz)
            v.pop_back();
        for (auto edge: log.edges)
            v[edge.first.first].to[edge.first.second] = edge.second;
        if (log.LinksUpdate.first != 0)
            v[log.LinksUpdate.first].link = log.LinksUpdate.second;
        last = log.last;
        sz = log.sz;
        logs.pop_back();
    }
};