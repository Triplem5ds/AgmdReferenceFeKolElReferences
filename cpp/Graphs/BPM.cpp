#include<iostream>
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define IO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
struct graph
{
    int L, R;
    vector<vector<int> > adj;
    graph(int l, int r) : L(l), R(r), adj(l+1) {}
    void add_edge(int u, int v)
    {
        adj[u].push_back(v+L);
    }
    int maximum_matching()
    {
        vector<int> mate(L+R+1,-1), level(L+1);
        function<bool (void)> levelize  = [&]()
        {
            queue<int> q;
            for(int i=1; i<=L; i++)
            {
                level[i]=-1;
                if(mate[i]<0)
                    q.push(i), level[i]=0;
            }
            while(!q.empty())
            {
                int node=q.front();
                q.pop();
                for(auto i : adj[node])
                {
                    int v=mate[i];
                    if(v<0)
                        return true;
                    if(level[v]<0)
                    {
                        level[v]=level[node]+1;
                        q.push(v);
                    }
                }
            }
            return false;
        };
        function<bool (int)> augment =[&](int node)
        {
            for(auto i : adj[node])
            {
                int v=mate[i];
                if(v<0 || (level[v]>level[node] && augment(v)))
                {
                    mate[node]=i;
                    mate[i]=node;
                    return true;
                }
            }
            return false;
        };
        int match=0;
        while(levelize())
            for(int i=1; i<=L; i++)
                if(mate[i] < 0 && augment(i))
                    match++;
        return match;
    }
};

int main()
{
    IO
    int L, R, m;
    cin>>L>>R>>m;
    graph g(L, R);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin>>u>>v;
        g.add_edge(u, v);
    }
    cout<<g.maximum_matching();
}