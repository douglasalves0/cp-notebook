/**
 * Author: Eu
 * Description: Builda uma árvore com prefixos de strings
 * Time: O(|s|)
 */

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
    
    // self explanatory
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

    // removes a string from the trie
    // if the string does not exist inside the trie, it is like you have a negative string
    void erase(const string& s, int cnt = 1){ 
        int cur = 0;
        a[cur].cnt -= cnt;
        for(char ch: s){
            cur = a[cur].nxt[ch - 'a'];
            a[cur].cnt -= cnt;
        }
        a[cur].ends_here -= cnt;
    }

    // returns the index of the node that have the string s
    // if the string s is not a prefix of any string inside the trie, returns -1
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
    
    // count the number of strings exactly equal to s inside the trie
    int count(string s){
        int p = walk(s);
        if(p == -1) return 0;
        return a[p].ends_here;
    }

    // count the number of strings inside the trie that have s as a prefix
    int count_prefix(string s){
        int p = walk(s);
        if(p == -1) return 0;
        return a[p].cnt;
    }

};
