#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    // number 20
    // 给定一个只包括 '('，')'，'{'，'}'，'['，']'的字符串，判断字符串是否有效。
    //
    bool isValid(string s) {
        std::stack<char> st;

        int len = s.size();
        for (int i = 0; i < len; ++i) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{')
                st.push(s[i]);
            else {
                if (st.empty())
                    return false;

                char c = st.top();
                st.pop();
                char match;
                if (c == '(')
                    match = ')';
                else if (c == '[')
                    match = ']';
                else if (c == '{')
                    match = '}';
                else
                    assert(0);

                if (match != s[i])
                    return false;
            }
        }

        if (st.empty())
            return true;
        return false;
    }

    /*
     *  输入: ["2", "1", "+", "3", "*"]
     *  输出: 9
     */
    int evalRPN(vector<string>& tokens) {
        stack<int> st;

        for (const string& str : tokens) {

            if (str == "+" || str == "-" || str == "*" || str == "/") {
                int a = st.top();
                st.pop();
                int b = st.top();
                st.pop();

                if (str == "+") {
                    st.push(b+a);
                }else if (str == "-") {
                    st.push(b-a);
                }else if (str == "*") {
                    st.push(b*a);
                }else if (str == "/") {
                    st.push(b/a);
                }
            }else {
                st.push(stoi(str));
            }
        }

        return st.top();
    }
/*
 *  输入："/home/"
    输出："/home"
    解释：注意，最后一个目录名后面没有斜杠。

    输入："/../"
    输出："/"
    解释：从根目录向上一级是不可行的，因为根是你可以到达的最高级。

    输入："/home//foo/"
    输出："/home/foo"
    解释：在规范路径中，多个连续斜杠需要用一个斜杠替换。

    输入："/a/./b/../../c/"
    输出："/c"

    输入："/a/../../b/../c//.//"
    输出："/c"

    输入："/a//b////c/d//././/.."
    输出："/a/b/c"
 */
    string simplifyPath(string path) {

        /**
         * 截取字符串，然后拼接
         * 起点是'/'开始处，结束点是下一个'/'
         */
        vector<string> vec;

        int start = 1;
        int i = 1;
        while (i <= path.size()) {
            if (i == path.size() || path[i] == '/') {
                string f = path.substr(start, i - start);
                if (f.size()) {
                    if (f == "..") {
                        if (vec.size() > 0)
                            vec.pop_back();
                    }else if (f != ".") {
                        vec.push_back(f);
                    }
                }
                start = i + 1;
            }
            ++i;
        }

        string res = "";
        for (string &e : vec)
            res += "/" + e;
        return res == "" ? "/" : res;
    }
};

int main() {
//    bool res = Solution().isValid("");
//    std::cout << res << std::endl;

    vector<string> v{"4", "13", "5", "/", "+"};
    int res = Solution().evalRPN(v);
    std::cout << res << std::endl;
//    int r = stoi("1");
//    std::cout << r << std::endl;

    string path = Solution().simplifyPath("/././../");
    std::cout << path << std::endl;
    return 0;
}
