// 트라이를 이용한 다중 문자열 검색을 할용하는 문제.
// 동적 계획법을 이용해야겠다는 생각은 했지만, 세부 구현 과정을 생각하는 것이
// 쉽지 않았다.
//
// 특히 트라이를 이용해 문자열을 받을 때마다 state가 옮겨다니는 것으로 생각하는 것이
// 주요한 아이디어였다.

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int MOD = 10007;
int cur_no;

int toNumber(char ch) {return ch - 'a';}

int memo[101][1001];

struct TrieNode {
    // 현 위치에서 끝나는 문자열의 번호
    bool terminal;
    int no;
    
    TrieNode* fail;

    // vector<int> output;

    TrieNode* children[26];

    TrieNode(): terminal(false), fail(NULL), no(cur_no++) {
        memset(children, 0, sizeof(children));
    }

    ~TrieNode() {
        for(int i=0; i<26; i++){
            if(children[i])
                delete children[i];
        }
    }

    void insert(const char* key){
        if(*key == 0)
            terminal = true;
        else{
            int next = toNumber(*key);
            if(!children[next])
                children[next] = new TrieNode();
            children[next]->insert(key + 1);
        }
    }
};

void computeFail(TrieNode* root){
    queue<TrieNode*> q;

    root->fail = root;
    q.push(root);
    while(!q.empty()){
        TrieNode* here = q.front();
        q.pop();

        for(int i=0; i<26; i++){
            TrieNode* child = here->children[i];
            if(child == NULL) continue;

            if(here == root)
                child->fail = root;
            else{
                TrieNode* t = here->fail;
                while(t!= root && t->children[i] == NULL)
                    t = t->fail;
                if(t->children[i]) t = t->children[i];
                child->fail = t;
            }

            child->terminal = child->fail->terminal || child->terminal;
            // child->output = child->fail->output;
            // if(child->terminal != -1)
                // child->output.push_back(child->terminal);
            q.push(child);
        }
    }
}

int count(int length, TrieNode* start_node){
    int &result = memo[length][start_node->no]; 
    if(result != -1) return result;

    if(start_node->terminal) return 0;
    
    if(length == 0) return 1;

    result = 0;
    for(int i=0; i<26; i++){
        result += count(length - 1, start_node->children[i]) % MOD;
    }
    return result % MOD;

}

void preCalculate(TrieNode* root){
    queue<TrieNode*> q;
    if(root == NULL) return;
    
    q.push(root);
    while(!q.empty()){
        TrieNode* tmp = q.front();
        q.pop();
        for(int i=0; i<26; i++){
            if(tmp->children[i])
                q.push(tmp->children[i]);
            else{
                TrieNode* tmp2 = tmp;
                while(tmp2 != root && tmp2->children[i] == NULL)
                    tmp2 = tmp2->fail;
                if(tmp2->children[i])
                    tmp->children[i] = tmp2->children[i];
                else
                    tmp->children[i] = tmp2;
            }
        }
    }
}

int solve(vector<string> &patterns, int length){
    TrieNode* root = new TrieNode();
    char tmp[12];
    for(int i=0; i<patterns.size(); i++){
        strcpy(tmp, patterns[i].c_str());
        root->insert(tmp);
    }

    computeFail(root);
    preCalculate(root);

    return count(length, root);
}


int main(){
    int i,j,k, N, M;
    vector<string> patterns;
    for(scanf("%d", &j), i=0; i<j; i++){
        scanf("%d %d", &N, &M);
        memset(memo, -1, sizeof(memo));
        patterns.clear();
        patterns.resize(M);
        cur_no = 0;
        for(k=0; k<M; k++){
            cin >> patterns[k];
        }
        cout << solve(patterns, N) << endl;
    }
}