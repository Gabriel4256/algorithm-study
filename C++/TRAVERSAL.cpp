//간단한 전위, 후위 문제

#include <iostream>
#include <vector>

using namespace std;
int preorder[100], inorder[100], N;

void postOrder(int preorder_start, int inorder_start, int inorder_end){
    if(preorder_start == N || (inorder_end < inorder_start)) return;
    int root = preorder[preorder_start];
    int root_idx = -1;
    for(int i=inorder_start; i<inorder_end + 1; i++){
        if(inorder[i] == root){
            root_idx = i;
            break;
        }
    }
    int no_of_left = root_idx - inorder_start;
    postOrder(preorder_start + 1, inorder_start, root_idx - 1);
    postOrder(preorder_start + no_of_left + 1, root_idx + 1, inorder_end);
    printf("%d ", root);
}

int main(){
    int i,j,k;
    for(scanf("%d", &j), i=0; i<j; i++){
        cin >> N;
        for(k=0; k<N; k++){
            cin >> preorder[k];
        }
        for(k=0; k<N; k++){
            cin >> inorder[k];
        }
        postOrder(0, 0, N-1);
        cout << endl;
    }
}