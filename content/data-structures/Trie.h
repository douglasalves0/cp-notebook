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
    
    void add(string s) {
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

    void erase(const string& s, int cnt = 1){ 
        int cur = 0;
        a[cur].cnt -= cnt;
        for(char ch: s){
            cur = a[cur].nxt[ch - 'a'];
            a[cur].cnt -= cnt;
        }
        a[cur].ends_here -= cnt;
    }

    int walk(string s){
        int cur = 0;
        for(char ch: s){
            int c = ch - 'a';
            if(a[cur].nxt[c] == -1) return -1;
            cur = a[cur].nxt[c];
            if(a[cur].cnt == 0) return -1; 
        }
        return cur;
    }
    
    int count(string s){
        int p = walk(s);
        if(p == -1) return 0;
        return a[p].ends_here;
    }

    int count_prefix(string s){
        int p = walk(s);
        if(p == -1) return 0;
        return a[p].cnt;
    }

};
