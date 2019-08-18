#include "test_runner.h"

#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
public:
    struct Node {
        T value;
        Node* next = nullptr;
    };

    LinkedList() :
        head(nullptr) {}

    ~LinkedList() {
        delete head;
    }

    void PushFront(const T& value) {
        if (head != nullptr) {
            Node* node = new Node;
            node->value = value;
            node->next = head;
            head = node;
        } else {
            head = new Node;
            head->value = value;
        }
    }
    void InsertAfter(Node* node, const T& value) {
        if (node == nullptr) {
            PushFront(value);
        }
        Node* new_node = new Node;
        new_node->value = value;
        if (head == node) {
            if (head->next != nullptr) {
                new_node->next = head->next;
                head->next = new_node;
            }
            head->next = new_node;
        } else {
            if (head->next != nullptr) {
                while (head->next != node) {
                    head++;
                }
                new_node->next = head;
            }
            head->next = new_node;
        }

    }
    void RemoveAfter(Node* node) {
        if (node == nullptr) {
            PopFront();
        } else {
//            while (head != node) {
//                head++;
//            }
            if (node->next != nullptr) {
//                Node* new_node = node->next->next;
                delete[] head;
                cout << head->value << endl;
                head + 1;
                cout << node->value << endl;
                cout << head->value << endl;
//                head->next = new_node;
//                delete head;
            }

        }
    }
    void PopFront() {
        delete head;
    }

    Node* GetHead() { return head; }
    const Node* GetHead() const { return head; }

private:
    Node* head = nullptr;
};

template <typename T>
vector<T> ToVector(const LinkedList<T>& list) {
    vector<T> result;
    for (auto node = list.GetHead(); node; node = node->next) {
        result.push_back(node->value);
    }
    return result;
}

void TestPushFront() {
    LinkedList<int> list;

    list.PushFront(1);
    ASSERT_EQUAL(list.GetHead()->value, 1);
    list.PushFront(2);
    ASSERT_EQUAL(list.GetHead()->value, 2);
    list.PushFront(3);
    ASSERT_EQUAL(list.GetHead()->value, 3);

    const vector<int> expected = {3, 2, 1};
    ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
    LinkedList<string> list;

    list.PushFront("a");
    auto head = list.GetHead();
    ASSERT(head);
    ASSERT_EQUAL(head->value, "a");

    list.InsertAfter(head, "b");
    const vector<string> expected1 = {"a", "b"};
    ASSERT_EQUAL(ToVector(list), expected1);

    list.InsertAfter(head, "c");
    const vector<string> expected2 = {"a", "c", "b"};
    ASSERT_EQUAL(ToVector(list), expected2);
}

void TestRemoveAfter() {
    LinkedList<int> list;
    for (int i = 1; i <= 5; ++i) {
        list.PushFront(i);
    }
    for (auto i : ToVector(list)) {
        cout << i << " ";
    }
    cout << endl;

    const vector<int> expected = {5, 4, 3, 2, 1};
    ASSERT_EQUAL(ToVector(list), expected);

    auto next_to_head = list.GetHead()->next;
    list.RemoveAfter(next_to_head); // удаляем 3
    for (auto i : ToVector(list)) {
        cout << i << " ";
    }
    list.RemoveAfter(next_to_head); // удаляем 2

    const vector<int> expected1 = {5, 4, 1};
    ASSERT_EQUAL(ToVector(list), expected1);

//    while (list.GetHead()->next) {
//        list.RemoveAfter(list.GetHead());
//    }
//    ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront() {
    LinkedList<int> list;

    for (int i = 1; i <= 5; ++i) {
        list.PushFront(i);
    }
    for (int i = 1; i <= 5; ++i) {
        list.PopFront();
    }
    ASSERT(list.GetHead() == nullptr);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestPushFront);
    RUN_TEST(tr, TestInsertAfter);
    RUN_TEST(tr, TestRemoveAfter);
    RUN_TEST(tr, TestPopFront);
    return 0;
}