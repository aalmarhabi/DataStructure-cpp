//ME - C++17 - hope it compile
/*
 * Authors: Alhussain Almarhabi
 * */
//Reference - future review
/* Use assignment four, how to read files of .dat
 *Use LinkedList profesor code in class
 */

#include <iostream>
#include <fstream>
#include<string>
#include <sstream>

using namespace std;

class LinkedList {
private:
    class Node{
    public:
        int data;
        Node* next;
        Node(int v, Node* next) : data(v), next(next) {}
    };
    Node* head;
public:
    LinkedList() : head(nullptr) {}
    ~LinkedList(){
        Node* q;
        for (Node* p = head; p != nullptr;){
            q = p;
            p = p->next;
            delete q;
        }
    }
#if 0
    // this is a copy constructor
         LinkedList(const LinkedList& orig) {
            if (orig.head == nullptr) {
             head = nullptr;
             return;
            }
            head = new Node(orig.head->data, nullptr);
            Node* q = head;
            for (Node* p = orig.head->next; p != nullptr; p=p->next, q = q->next)
                q->next = new Node(p->data, nullptr);
            }
#endif

    LinkedList(const LinkedList& orig) = delete;
    void operator = (const LinkedList& orig) = delete;

    void addEnd(int v) {  //O(n)
        if (head == nullptr) { // O(1)
            head = new Node(v, nullptr);
            return;
        }
        Node* p;
        for (p = head; p->next != nullptr; p = p->next) //O(n)
            ;
        // p = last element
        p->next = new Node(v, nullptr);
    }
    void addStart(int v) {  //O(1)
        head = new Node(v, head);
    }
    void removeStart() {
        if (head == nullptr)
            return;
        Node* temp = head;
        head = head->next;
        delete temp; // free the memory
    }

    void removeEnd() {
        if (head == nullptr)
            return;

        Node* p = head;
        if (p->next == nullptr) {
            delete p;
            head = nullptr;
            return;
        }

        Node* q = p;
        p = p->next;
        for ( ; p->next != nullptr; q = p, p = p->next) //O(n)
            delete p;
        q->next = nullptr;
    }

    int size() const { // O(n)
        int count = 0;
        for (Node* p = head; p != nullptr; p=p->next)
            count++;
        return count;
    }

    int get(int i) const { //O(n)
        for (Node* p = head; p != nullptr; i--, p = p->next)
            if (i == 0)
                return p->data;
        throw "Out of bounds";
    }

    void showList()
    {//O(n)
        if (this->size() == 0){
            cout << "empty" << endl;

        }
        else {
            cout << "{";
            for (int i = 0; i < this->size(); i++) {
                if (i == this->size() - 1){
                    cout << this->get(i);
                    cout << "}" << endl;
                    break;
                }
                cout << this->get(i) << ", ";
            }
        }
    }

    void removeValue(int v){
        Node* p = head;
        Node* q = p;

        while (p->next != nullptr) {

            if (p->data ==v && p == head){
                head = p->next;
                return;
            }
            if (p->data == v && p->next != nullptr){
                q->next = p->next;
                return;
            }
            q = p;
            p = p->next;
        }
        if (p->data == v && p->next == nullptr){
            q->next = nullptr;
            return;
        }

    }
    void addValue(int i, int v){
        Node* p;
        Node* q2;
        q2 = p;
        for (p = head; p->next != nullptr; q2=p, p = p->next){
            if (p->data == this->get(i) && p == head){
                Node* q = new Node(v, p);
                head = q;
                break;
            }
            if (p->data == this->get(i) && p->next != nullptr){

                Node* q = new Node(v, p);
                q2->next = q;

                break;
            }
        }

        if (p->next == nullptr){
            p = head;
            q2 = p;
            for (p = head; p->next != nullptr; q2 = p, p = p->next) //O(n)
                ;

            Node *q = new Node(v, p);
            q2->next = q;

        }

    }

    class Iterator {
    private:
        Node* current;
        Node* current2;
    public:
        Iterator(LinkedList& list) : current(list.head), current2(list.head) {}
        bool operator !() const { return current != nullptr; }
        void operator ++() { current = current->next; }
        void operator --() { current = current2; }
        int& operator *() const {
            return current->data;
        }
    };
};
int main() {
    LinkedList A,B;

    std::string filename;
    filename = "./hw5.dat";

    std::ifstream dfile;
    dfile.open(filename);

    if (!dfile.is_open()){
        cout << "Error: file did not open" << endl;
        return 0;
    }
    std::string line;
    std::getline(dfile,line);
    std::stringstream ss(line);

    int temp;
    while (ss >> temp){
        A.addEnd(temp);
    }

    cout << "original list is:  ";
    A.showList();

    int Bsize = 0;
    for (int i =0; i< A.size(); i++){
        if (A.get(i) % 2 == 0){
            B.addEnd(A.get(i));
            Bsize++;
        }
    }

    int aa[Bsize];
    aa[Bsize] = {0};
    int j = 0;
    for (LinkedList::Iterator i = A; !i; ++i){
        if (*i % 2 == 0){
            aa[j] = *i;
            j++;
        }
    }

    for(int i = 0; i<Bsize; i++){
        A.removeValue(aa[i]);
    }


    cout<<"ListB (Even) is:  "; B.showList();
    cout<<"ListA (odd) is:  "; A.showList();


    for (int i =0; i< B.size(); i++){
        if (2*i < A.size()){
            A.addValue(2*i, B.get(i));
        }
        else {
            A.addEnd(B.get(i));
        }
    }
    A.showList();

    return 0;
}
