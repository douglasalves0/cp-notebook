const int ALPHASIZE = 26;
const int TOTLEN = 1e6;

struct trie {
    trie(){}

    struct node{
        int nxt[ALPHASIZE], ends_here, cnt;
        node(){
            memset(nxt, -1, sizeof nxt);
            ends_here = 0, cnt = 0;
        }
    };

    node a[TOTLEN+1];
    int sz = 1;

    void add(const string& s) {
        int cur = 0;
        a[0].cnt++;
        for(char ch: s){
            int c = ch - 'a';
            if(a[cur].nxt[c] == -1) a[cur].nxt[c] = sz++;
            cur = a[cur].nxt[c];
            a[cur].cnt++;
        }
        a[cur].ends_here++;
    }

    // supõe que existam pelo menos cnt ocorrências de s na trie
    // remove apenas decrementando os contadores
    void erase(const string& s, int cnt = 1){
        int cur = 0;
        a[cur].cnt -= cnt;
        for(char ch: s){
            cur = a[cur].nxt[ch - 'a'];
            a[cur].cnt -= cnt;
        }
        a[cur].ends_here -= cnt;
    }

    // percorre a trie com s, retornando o último vértice ou -1 se não existir
    int walk(const string& s){
        int cur = 0;
        for(char ch: s){
            int c = ch - 'a';
            if(a[cur].nxt[c] == -1) return -1;
            cur = a[cur].nxt[c];
            if(a[cur].cnt == 0) return -1;
        }
        return cur;
    }

};