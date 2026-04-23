#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* append(Node* head, int value) {
    Node* newNode = new Node{ value, nullptr, nullptr };

    if (!head) return newNode;

    Node* temp = head;
    while (temp->next)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;

    return head;
}

void printList(Node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

Node* loadFromFile(const string& filename) {
    ifstream file(filename);

    Node* head = nullptr;
    int value;

    while (file >> value) {
        head = append(head, value);
    }

    file.close();
    return head;
}

Node* removeEven(Node* head) {
    Node* temp = head;

    while (temp) {
        Node* next = temp->next;

        if (temp->data % 2 == 0) {
            if (temp->prev)
                temp->prev->next = temp->next;
            else
                head = temp->next;

            if (temp->next)
                temp->next->prev = temp->prev;

            delete temp;
        }

        temp = next;
    }

    return head;
}

void doubleOddValues(Node* head) {
    while (head) {
        if (head->data % 2 != 0)
            head->data *= 2;

        head = head->next;
    }
}

Node* createSublist(int n) {
    Node* sub = nullptr;

    for (int i = 1; i <= n; i++)
        sub = append(sub, i * 10);

    return sub;
}

Node* insertSublist(Node* head, Node* sub, int pos) {
    if (!sub) return head;

    if (pos <= 1) {
        Node* tail = sub;
        while (tail->next)
            tail = tail->next;

        tail->next = head;
        if (head) head->prev = tail;

        return sub;
    }

    Node* temp = head;
    int i = 1;

    while (temp && i < pos - 1) {
        temp = temp->next;
        i++;
    }

    if (!temp) return head;

    Node* next = temp->next;

    temp->next = sub;
    sub->prev = temp;

    Node* tail = sub;
    while (tail->next)
        tail = tail->next;

    tail->next = next;
    if (next) next->prev = tail;

    return head;
}

void deleteList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

#ifndef UNIT_TESTING
int main() {
    Node* head = loadFromFile("data.txt");

    cout << "Initial list: ";
    printList(head);

    head = removeEven(head);
    doubleOddValues(head);

    int pos, n;
    cout << "Enter position: ";
    cin >> pos;

    cout << "Enter sublist size: ";
    cin >> n;

    Node* sub = createSublist(n);
    head = insertSublist(head, sub, pos);

    cout << "Final list: ";
    printList(head);

    deleteList(head);
    return 0;
}
#endif