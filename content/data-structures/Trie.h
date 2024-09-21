/**
 * Author: Douglas
 * Date: 2024-09-20
 * Description: Adiciona e pesquisa por strings
 * Time: $O(RAPIDO)$
 * Status: stress-tested
 */

const int ALPHASIZE = 26;
const int TOTLEN = 1e6;

struct trie {
    trie(){}
    struct node{
        int nxt[ALPHASIZE];
        node(){ memset(nxt, -1, sizeof nxt); }
    };
    node a[TOTLEN+1];
    int sz = 1;
    void add(const string& s){ // only needed if you want to add strings
        int m = s.size();
        vector<int> v(m);
        for(int i=0;i<m;i++) v[i] = s[i] - 'a';
        add(v);
    }
    void add(const vector<int>& s, int f) {
        int cur = 0;
        for(int c: s){
            if(a[cur].nxt[c] == -1) a[cur].nxt[c] = sz++;
            cur = a[cur].nxt[c];
        }
    }
};