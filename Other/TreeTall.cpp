#include<iostream>
#include<stdlib.h>

using namespace std;
int SIZE_OF_TREE = 0;

int find_index(int * tree, int num){
    for(int i = 0; i < SIZE_OF_TREE; i++){
        if(tree[1] != -1 && tree[i] == num){
            tree[i] == -1;
            return i;
        }
    }
    return -1;
}

int main(){
    int cases = 0, level = 0;
    int record_index[3] = {0};
    cin >> cases;
    for(int does = 0; does < cases; does++){
        cin >> SIZE_OF_TREE;
        int preorder[SIZE_OF_TREE];
        int inorder[SIZE_OF_TREE];
        for(int tree_index = 0; tree_index < SIZE_OF_TREE; tree_index++) cin >> preorder[tree_index];
        for(int tree_index = 0; tree_index < SIZE_OF_TREE; tree_index++) cin >> inorder[tree_index];
        level = 1;
        for(int i = 2; i < SIZE_OF_TREE; i++){
            record_index[0] = find_index(inorder, preorder[i - 2]);
            record_index[1] = find_index(inorder, preorder[i - 1]);
            record_index[2] = find_index(inorder, preorder[i]);
            cout << record_index[0] << "," << record_index[1] << "," << record_index[2] << "L0:" << level[0] << "L1:" << level[1]<<endl;
            if(record_index[2] < record_index[0] && record_index[1] < record_index[0]){
                level++;
            } else if(record_index[2] > record_index[0] && record_index[1] > record_index[0]){
                level++;
            }
        }
        cout << level << '\n';
        cout << endl;
    }
    return 0;
}

