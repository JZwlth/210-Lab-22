// COMSC-210 | Lab 22 | Zhaoyi Zheng
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // Constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // If no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;  
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return; 

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return;  

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        if (!head) {
            cout << "List is empty. Node not deleted.\n";
            return;  
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not deleted.\n";
            return;
        }

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;  

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void pop_front() {
        if (!head) return;  
        Node* temp = head;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        } else {
            head = tail = nullptr;
        }
        delete temp;
    }

    void pop_back() {
        if (!tail) return;  
        Node* temp = tail;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            head = tail = nullptr;
        }
        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty.\n";
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty.\n";
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    DoublyLinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);

cout << "Initial list forward: ";
    list.print();
    cout << "Initial list backward: ";
    list.print_reverse();

    // pop_front()
    cout << "\nUsing pop_front():\n";
    list.pop_front();
    cout << "List after pop_front() forward: ";
    list.print();
    cout << "List after pop_front() backward: ";
    list.print_reverse();

    // pop_back()
    cout << "\nUsing pop_back():\n";
    list.pop_back();
    cout << "List after pop_back() forward: ";
    list.print();
    cout << "List after pop_back() backward: ";
    list.print_reverse();

    // delete_pos() to delete node at position 1
    cout << "\nUsing delete_pos(1):\n";
    list.delete_pos(1);
    cout << "List after delete_pos(1) forward: ";
    list.print();
    cout << "List after delete_pos(1) backward: ";
    list.print_reverse();

    return 0;
}
