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

    // supposes that there are at least cnt ocurrences of s inside the trie
    // erases does not remove connections, only decreases the counter
    void erase(const string& s, int cnt = 1){ 
        int cur = 0;
        a[cur].cnt -= cnt;
        for(char ch: s){
            cur = a[cur].nxt[ch - 'a'];
            a[cur].cnt -= cnt;
        }
        a[cur].ends_here -= cnt;
    }

    // walks through the trie using the string s and returns the last vertex visited
    // it returns -1 if s is not at the trie
    int walk(const string& s){
        int cur = 0;
        for(char ch: s){
            int c = ch - 'a';
            if(a[cur].nxt[c] == -1) return -1;
            cur = a[cur].nxt[c];
            // maybe there is a connection, but if the counter is 0 it means that this
            // connection is no longer useful
            if(a[cur].cnt == 0) return -1; 
        }
        return cur;
    }

};
