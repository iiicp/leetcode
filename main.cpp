#include <iostream>

class MyDoubleLinkedList {
private:
    class Node {
    public:
        int val;
        Node *prev, *next;
        Node(int val):val(val), prev(nullptr), next(nullptr) {}
        Node(int val, Node *prev, Node *next): val(val), prev(prev), next(next) {}
    };

    Node *dummyHead;

public:
    MyDoubleLinkedList() {
        dummyHead = new Node(-1);
    }

    int get(int index) {
        Node *cur = dummyHead->next;
        for (int i = 0; i < index && cur; ++i) {
            cur = cur->next;
        }

        if (cur == nullptr) return -1;

        return cur->val;
    }

    void addAtHead(int val) {
        dummyHead->next = new Node(val, dummyHead, dummyHead->next);
    }

    void addAtTail(int val) {
        Node *cur = dummyHead->next;
        while (cur->next) {
            cur = cur->next;
        }

        cur->next = new Node(val, cur->next, nullptr);
    }

    void addAtIndex(int index, int val) {

        Node *prev = dummyHead;
        for (int i = 0; i < index && prev; i++)
            prev = prev->next;

        if (prev)
            prev->next = new Node(val, prev, prev->next);
    }

    void deleteAtIndex(int index) {

        Node *prev = dummyHead;
        for (int i = 0; i < index && prev; i++)
            prev = prev->next;

        if (prev && prev->next) {
            Node *delNode = prev->next;
            prev->next = delNode->next;
            if (prev->next)
                delNode->next->prev = prev;
            delete delNode;
        }
    }
};

/**
 *  起点是哑结点，i = 0; i < index; i++，就表示是prev结点
 *  起点是链表头结点，i = 0; i < index; i++，表示当前结点
 */
class MyLinkedList {
private:
    class Node {
    public:
        int val;
        Node *next;
        Node(int val, Node *next) : val(val), next(next) {}
        Node(int val): val(val), next(nullptr) {}
    };

    Node *dummyHead;
public:
    /** Initialize your data structure here. */
    MyLinkedList() {
        dummyHead = new Node(-1);
    }

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {

        Node* cur = dummyHead->next;
        for (int i = 0; i < index && cur; ++i) {
            cur = cur->next;
        }
        if (!cur) return -1;

        return cur->val;
    }

    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        dummyHead->next = new Node(val, dummyHead->next);
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {

        Node *cur = dummyHead->next;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = new Node(val);
    }

    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {

        Node *prev = dummyHead;

        for (int i = 0; i < index && prev; ++i) {
            prev = prev->next;
        }

        if (prev)
            prev->next = new Node(val, prev->next);
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {

        Node *pre = dummyHead;
        for (int i = 0; i < index && pre; ++i) {
            pre = pre->next;
        }

        if (pre && pre->next) {
            Node *delNode = pre->next;
            pre->next = pre->next->next;
            delete delNode;
        }
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(NULL) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode * createList(int *arr, int len) {
        if (arr == nullptr) {
            return nullptr;
        }

        ListNode *head = new ListNode(arr[0]);
        ListNode *cur = head;
        for (int i = 1; i < len; ++i) {
            cur->next = new ListNode(arr[i]);
            cur = cur->next;
        }

        return head;
    }

    void printList(ListNode *node) {
        while (node) {
            std::cout << node->val << " -> ";
            node = node->next;
        }
        std::cout << "NULL" << std::endl;
    }

    void deleteList(ListNode *node) {
        while (node) {
            ListNode *temp = node;
            node = node->next;
            delete temp;
        }
    }

    ListNode* deleteDuplicates(ListNode* head) {

        if (head == NULL) {
            return head;
        }

        ListNode dummy(0);
        dummy.next = head;

        ListNode *prev = &dummy;
        ListNode *cur = dummy.next;

        while (cur) {
            bool duplicated = false;
            while (cur->next && cur->val == cur->next->val) {
                duplicated = true;
                ListNode *temp = cur;
                cur = cur->next;
                delete temp;
            }

            if (duplicated) {
                ListNode *temp = cur;
                cur = cur->next;
                delete temp;
                continue;
            }

            // 追踪真实的链表的流程
            prev->next = cur;
            prev = cur;
            cur = cur->next;
        }
        prev->next = cur;
        return dummy.next;
    }

    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }

        ListNode dummy(0);
        dummy.next = head;

#if 0
        ListNode *prev = &dummy;
        ListNode *node1 = prev->next;
        ListNode *node2 = node1->next;

        while (node1 && node2) {
            ListNode *next = node2->next;
            node2->next = node1;
            node1->next = next;
            prev->next = node2;

            prev = prev->next;
            node1 = next;

            if (node1) {
                node2 = node1->next;
            }
        }
#endif
        ListNode *p = &dummy;
        while (p->next && p->next->next) {
            ListNode *node1 = p->next;
            ListNode *node2 = node1->next;
            ListNode *next = node2->next;

            node2->next = node1;
            node1->next = next;
            p->next = node2;
            p = node1;
        }

        return dummy.next;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummyHead(-1);
        dummyHead.next = head;

        ListNode *pDummyHead = &dummyHead;
        while (true) {
            int n = k;
            ListNode *fastK = pDummyHead;
            while (n > 0 && fastK->next) {
                fastK = fastK->next;
                n--;
            }
            if (n > 0)
                break;

            ListNode *prev = pDummyHead;
            ListNode *tail = prev->next;
            ListNode *tailNext = fastK ? fastK->next : nullptr;
            prev->next = reverse(prev->next, k);
            tail->next = tailNext;

            pDummyHead = tail;
        }

        return dummyHead.next;
    }

    ListNode* reverse(ListNode *head, int n) {
        ListNode *prev = nullptr;
        ListNode *cur = head;
        while (n--) {
            ListNode *next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }

    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;

        // 初始情况，也要满足快于一倍
        ListNode *slow = head;
        ListNode *fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *head2 = slow->next;
        slow->next = nullptr;

        head = sortList(head);
        head2 = sortList(head2);

        return merge(head, head2);
    }

    ListNode *merge(ListNode *l1, ListNode *l2) {
        ListNode dummyHead(-1);
        ListNode *cur = &dummyHead;
        ListNode *p1 = l1, *p2 = l2;

        while (p1 || p2) {
            int a = p1 ? p1->val : INT_MAX;
            int b = p2 ? p2->val : INT_MAX;

            if (a < b) {
                cur->next = p1;
                p1 = p1 ? p1->next : nullptr;
            }else {
                cur->next = p2;
                p2 = p2 ? p2->next : nullptr;
            }

            cur = cur->next;
        }

        return dummyHead.next;
    }

    void deleteNode(ListNode* node) {
        ListNode *next = node->next;
        node->val = next->val;
        node->next = next->next;
        delete next;
    }

    /*
     * 给定一个链表: 1->2->3->4->5, 和 n = 2.
     * 当删除了倒数第二个节点后，链表变为 1->2->3->5.
     */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummyHead(-1);
        dummyHead.next = head;

        ListNode *prev = &dummyHead;
        // fast语义，指向链表最后一个节点的下一个节点
        // 初始值指向链表第一个节点
        // 倒数第n个节点，即让fast移动n个节点
        ListNode *fast = prev->next;
        for (int i = 0; i < n; ++i) fast = fast->next;

        while (fast) {
            fast = fast->next;
            prev = prev->next;
        }

        ListNode *del = prev->next;
        prev->next = prev->next->next;
        delete del;

        return dummyHead.next;
    }

    /*
        给定一个链表，旋转链表，将链表每个节点向右移动k个位置，其中k是非负数。

        示例1:

        输入: 1->2->3->4->5->NULL, k = 2
        输出: 4->5->1->2->3->NULL
        解释:
        向右旋转 1 步: 5->1->2->3->4->NULL
        向右旋转 2 步: 4->5->1->2->3->NULL
        示例2:

        输入: 0->1->2->NULL, k = 4
        输出: 2->0->1->NULL
        解释:
        向右旋转 1 步: 2->0->1->NULL
        向右旋转 2 步: 1->2->0->NULL
        向右旋转 3 步: 0->1->2->NULL
        向右旋转 4 步: 2->0->1->NULL
     */
    ListNode* rotateRight(ListNode* head, int k) {
        ListNode dummyHead(-1);
        dummyHead.next = head;

        ListNode *prev1 = &dummyHead;
        ListNode *head1 = prev1->next;
        ListNode *tail1 = prev1->next;

        ListNode *prev2 = &dummyHead;
        // iter为链表开头，语义没有问题，iter表示链表最后一个节点的最后一部分
        ListNode *iter = prev1->next;
        for (int i = 0; i < k; ++i) iter = iter->next;

        int n = 0;
        while (iter) {
            prev2 = prev2->next;
            iter = iter->next;
            ++n;
        }
        ListNode *head2 = prev2->next;
        ListNode *tail2 = prev2->next;

        prev2->next = reverse(head2, k);
        // update right head
        head2 = prev2->next;
        tail2->next = nullptr;

        prev1->next = reverse(head1, n);
        head1 = prev1->next;
        tail1->next = head2;

        prev1->next = reverse(prev1->next, n + k);

        return dummyHead.next;
    }

    /**
     * 套模板的导致的后果，并不优美
     */
    ListNode* rotateRight2(ListNode* head, int k) {

        ListNode dummyHead(-1);
        dummyHead.next = head;

        ListNode *prev1 = &dummyHead;
        ListNode *head1 = prev1->next;
        ListNode *tail = head1;

        ListNode *prev2 = &dummyHead;
        ListNode *iter = head; // 注意iter初始值为头结点，这样iter指向链表最后一个节点的最后一位符合语义

        for (int i = 0; i < k; ++i) iter = iter->next;
        int n = 0;
        while (iter) {
            ++n;
            iter = iter->next;
            prev2 = prev2->next;
        }
        ListNode *head2 = prev2->next;
        ListNode *tail2 = head2;

        prev2->next = reverse2(head2, k);
        head2 = prev2->next;
        tail2->next = nullptr;

        prev1->next = reverse2(head1, n);
        head1 = prev1->next;
        tail->next = head2;

        prev1->next = reverse2(prev1->next, k + n);
        return dummyHead.next;
    }

    ListNode *reverse2(ListNode *head, int n) {
        ListNode *prev = nullptr;
        ListNode *cur = head;

        while (n--) {
            ListNode *next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }

        return prev;
    }

    /**
     * 链表的好处就是不太需要搬移元素，不依赖物理位置在一起
     * 旋转链表，很好的体现了链表这种数据结构的优点
     */
    ListNode* rotateRight3(ListNode* head, int k) {
        if(head == nullptr) {
            return head;
        }
        int len = getListLen(head);
        k = k % len;

        ListNode *end = head;
        for (int i = 0; i < k; i++) end = end->next;

        ListNode *start = head;
        while (end->next) {
            start = start->next;
            end = end->next;
        }

        /// 改变链式关系，一定要用next域去做
        /// 用指针去做，只是改变临时关系
        end->next = head;
        head = start->next;
        start->next = nullptr;

        return head;
    }

    int getListLen(ListNode *head) {
        int len = 0;
        while (head) {
            len++;
            head = head->next;
        }
        return len;
    }

    /*
     *  L0->L1->L2->L3->L4
     *
     *  L0->L4->L1->L3
     */
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return;

        ListNode *slow = head;
        ListNode *fast = head->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 右半部分头部
        ListNode *head2 = slow->next;
        // 左边部分尾部
        slow->next = nullptr;

        // 反转后边的链表
        head2 = reverseList(head2);

        // 合并两个链表
        ListNode *cur = head;
        ListNode *p1 = head->next, *p2 = head2;
        while (p1 || p2) {
            if (p2) {
                cur->next = p2;
                p2 = p2->next;
                cur = cur->next;
            }
            if (p1) {
                cur->next = p1;
                p1 = p1->next;
                cur = cur->next;
            }
        }

    }

    ListNode * reverseList(ListNode *head) {
#if 0
        ListNode *prev = NULL;
        ListNode *cur = head;

        while (cur) {
            ListNode *next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }

        return prev;
#else
        // 如果是单一结点，直接返回单一结点
        if (head == nullptr || head->next == nullptr)
            return head;

        // 反转剩下的结点
        ListNode *ret = reverseList(head->next);

        // 倒数第二个结点的next指向第一个结点
        head->next->next = head;
        // 尾部结点重置为null;
        head->next = nullptr;

        return ret;
#endif
    }

    /**
     *
     *  1->2->3->2->1
     */
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return true;
        }

        ListNode *slow = head;
        ListNode *fast = head->next;

        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }

        slow->next = reverseList(slow->next);

        ListNode *cur = head;
        ListNode *head2 = slow->next;
        while (head2) {
            if (cur->val != head2->val)
                return false;
            cur = cur->next;
            head2 = head2->next;
        }
        return true;
    }
};

int main() {

    int arr[] = {1,2,3,2,1};

    Solution s;
    ListNode *node = s.createList(arr, sizeof(arr)/sizeof(int));
    s.printList(node);

//    ListNode *node2 = s.createList(arr, sizeof(arr)/sizeof(int));
//    s.printList(node2);

//    node = s.deleteDuplicates(node);
//    node = s.removeNthFromEnd(node, 6);
//    node = s.swapPairs(node);
//    node = s.merge(node, node2);
//    node = s.sortList(node);
//    s.printList(node);


//    s.deleteNode(node->next->next);
//    node = s.removeNthFromEnd(node, 5);
//    s.printList(node);
//    node = s.rotateRight3(node, 2);
//    s.reorderList(node);
    bool res = s.isPalindrome(node);
    std::cout << res << std::endl;
    s.printList(node);

    s.deleteList(node);
    return 0;
}
