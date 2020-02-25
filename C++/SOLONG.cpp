// 어렵지 않았던 트라이 문제.
// 다만 코너케이스들을 조심하자

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int toNumber(char ch) { return ch - 'A';}



struct TrieNode {
    TrieNode* children[26];

    bool terminal;
    int max_app;
    string dest;

    TrieNode() : terminal(false), max_app(-1) {
        memset(children, 0, sizeof(children));
    }

    ~TrieNode(){
        for(int i=0; i<26; i++){
            if(children[i])
                delete children[i];
        }
    }

    void insert(const char* key, int app){

        if(app > max_app || (app == max_app && dest.compare(key) > 0)){
            max_app = app; dest = key;
        }
        if(*key == 0){
            terminal = true;
        }
        else{
            int next = toNumber(*key);
            if(children[next] == NULL)
                children[next] = new TrieNode();
            children[next]->insert(key + 1, app);
        }
    }

    TrieNode* find(const char* key){
        if((*key) == 0) return this;
        int next = toNumber(*key);
        if(children[next] == NULL) return NULL;
        return children[next]->find(key + 1);
    }

    int typing(const char* key, bool isRoot){
        if((*key) == 0) return 0;
        int next = toNumber(*key);
        if(children[next] == NULL){
            int len = 0;
            while(*key){
                len++;
                key++;
            }
            return len;
        }
        if(!isRoot && dest.compare(key) == 0){
            return 1;
        }
        return 1 + this->children[next]->typing(key + 1, false);
    }
};

int solve(vector<string> &words, TrieNode& root){
    int ret = 0;
    char ch[21];
    for(int i=0; i<words.size(); i++){
        strcpy(ch, words[i].c_str());
        ret += root.typing(ch, true) + 1;
    }
    return ret-1;
}

int main(){
    int i,j,k, N, M;
    char str[21];
    vector<string> words;
    for(scanf("%d", &j), i=0; i<j; i++){
        scanf("%d %d", &N, &M);
        words.clear();
        words.resize(M);
        TrieNode root;
        for(k=0; k<N; k++){
            int app;
            scanf("%s %d", str, &app);
            root.insert(str, app);
        }
        for(k=0; k<M; k++){
            cin >> words[k];
        }
        printf("%d\n", solve(words, root));
    }
}