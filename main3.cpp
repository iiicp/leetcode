#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 *  重点设计：返回树的跟结点
 */
void _recurseve(TreeNode* &root, int *arr, int len, int index) {

    if (index >= len || arr[index] == -1) {
        return;
    }
    // -1 mean null node
    root = new TreeNode(arr[index]);
    _recurseve(root->left, arr, len, 2 * index + 1);
    _recurseve(root->right, arr, len, 2 * index + 2);
}

TreeNode *create_tree(int *arr, int len) {
    TreeNode *root = nullptr;
    _recurseve(root, arr, len, 0);
    return root;
}


class Solution {
    class Command {
    public:
        string str;
        TreeNode *node;
        Command(string str, TreeNode *node) : str(str), node(node) {}
    };
public:

    vector<int> preorderTraversal_iter(TreeNode *root) {
        vector<int> res;
        if (root == nullptr)
            return res;

        /// 初始值的考量，第一次是go，如果是引用就没有下一步了
        stack<Command> st;
        st.push(Command("go", root));
        while (!st.empty()) {
            Command c = st.top();
            st.pop();
            if (c.str == "print")
                res.push_back(c.node->val);
            else {
                if(c.node->right) {
                    st.push(Command("go", c.node->right));
                }
                if(c.node->left) {
                    st.push(Command("go", c.node->left));
                }
                st.push(Command("print", c.node));
            }
        }
        return res;
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        _preorderTraver(res, root);
        return res;
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        _inorderTraver(res, root);
        return res;
    }

    vector<int> inorderTraversal_iter(TreeNode* root) {
        vector<int> res;
        if (root == nullptr)
            return res;

        stack<Command> st;
        st.push(Command("go", root));

        while (!st.empty()) {
            Command c = st.top();
            st.pop();

            if (c.str == "print") {
                res.push_back(c.node->val);
            }else {
                if (c.node->right) {
                    st.push(Command("go", c.node->right));
                }

                st.push(Command("print", c.node));

                if (c.node->left) {
                    st.push(Command("go", c.node->left));
                }
            }
        }
        return res;
    }

    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        _postorderTraver(res, root);
        return res;
    }

    vector<int> postorderTraversal_iter(TreeNode* root) {
        vector<int> res;
        if (root == nullptr)
            return res;

        stack<Command> st;
        st.push(Command("go", root));

        while (!st.empty()) {
            Command c = st.top();
            st.pop();

            if (c.str == "print") {
                res.push_back(c.node->val);
            }else {
                st.push(Command("print", c.node));

                if (c.node->right) {
                    st.push(Command("go", c.node->right));
                }

                if (c.node->left) {
                    st.push(Command("go", c.node->left));
                }
            }
        }
        return res;
    }

private:
    void _preorderTraver(vector<int> &res, TreeNode *root) {
        if (root == nullptr)
            return;

        res.push_back(root->val);

        _preorderTraver(res, root->left);
        _preorderTraver(res, root->right);
    }

    void _inorderTraver(vector<int> &res, TreeNode *root) {
        if (root == nullptr)
            return;

        _inorderTraver(res, root->left);
        res.push_back(root->val);
        _inorderTraver(res, root->right);
    }

    void _postorderTraver(vector<int> &res, TreeNode *root) {
        if (root == nullptr)
            return;

        _postorderTraver(res, root->left);
        _postorderTraver(res, root->right);
        res.push_back(root->val);
    }
};


void Print(TreeNode* p) {
    if (NULL == p)
        return;
    cout << p->val;
    Print(p->left);
    Print(p->right);
}

int main() {

    /*
     *           0
     *         /   \
     *        null  2
     *             /  \
     *             3   null
     */

    int arr[] = { 0, -1, 2, -1, -1, 3, -1 };
    int n = sizeof(arr)/sizeof(int);
    TreeNode *root = create_tree(arr, n);

    vector<int> res = Solution().preorderTraversal(root);
    for (auto &n : res)
        std::cout << n << " ";
    std::cout << std::endl;

    vector<int> res_iter = Solution().preorderTraversal_iter(root);
    for (auto &n : res_iter)
        std::cout << n << " ";
    std::cout << std::endl;

    vector<int> res2 = Solution().inorderTraversal(root);
    for (auto &n : res2)
        std::cout << n << " ";
    std::cout << std::endl;

    vector<int> res2_iter = Solution().inorderTraversal_iter(root);
    for (auto &n : res2_iter)
        std::cout << n << " ";
    std::cout << std::endl;

    vector<int> res3 = Solution().postorderTraversal(root);
    for (auto &n : res3)
        std::cout << n << " ";
    std::cout << std::endl;

    vector<int> res3_iter = Solution().postorderTraversal_iter(root);
    for (auto &n : res3_iter)
        std::cout << n << " ";
    std::cout << std::endl;

    return 0;
}

