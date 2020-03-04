//ME - C++17 - hope it compile - Clang
/*
 * Authors: Alhussain Almarhabi
 * */
//Reference - future review
/* Use assignment four, how to read files of .dat
 *Use github Trie class
 */

#include <iostream>
#include <fstream>
#include<string>
#include <sstream>
#include <list>
#include <utility>
#include <iomanip>

using namespace std;
//class HashMapLinearChaining;
class LinkedList {
private:
    class Node{
    public:
        string data;
        Node* next;
        Node(string v, Node* next) : data(std::move(v)), next(next) {}
    };
    Node* head;
public:
    friend class HashMapLinearChaining;
    LinkedList() : head(nullptr) {}
    ~LinkedList(){
        Node* q;
        for (Node* p = head; p != nullptr;){
            q = p;
            p = p->next;
            delete q;
        }
    }

    LinkedList(const LinkedList& orig) = default;
    void operator = (const LinkedList& orig) = delete;

    LinkedList::Node* HEAD(){ return head;}

    void addStart(string v) {  //O(1)
        head = new Node(std::move(v),this->head);
    }

    int size() const { // O(n)
        int count = 0;
        for (Node* p = head; p != nullptr; p=p->next)
            count++;
        return count;
    }

    [[nodiscard]] string get(int i) const { //O(n)
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

    void showList2()
    {//O(n)
        if (this->size() == 0){
            cout << "empty" << endl;

        }
        else {
            cout << "{";
            for (int i = 0; i < 10; i++) {
                if (i == 9){
                    cout << this->get(i);
                    cout << "}" << endl;
                    break;
                }
                cout << this->get(i) << ", ";
            }
        }
    }
    void removeValue(string v){
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

};

class Trie {
private:
    class Node {
    public:
        Node* next[26];
        bool isWord;
        Node(): next(), isWord(false){
            for (auto & i : next){ i = nullptr;}
            this->isWord = false;
        }
    };
    Node* root;
public:
    Trie() { root = new Node();}
    ~Trie() {}
    Trie::Node* Root(){ return root;}
    // load the trie from a file
    void load(const string& filename) {

        std::ifstream dfile;
        dfile.open(filename);

        if (!dfile.is_open()){
            cout << "Error: file did not open" << endl;
            return;
        }
        std::string line;
        int count = 0;

        while(!dfile.eof()){

            std::getline(dfile,line);
            std::stringstream ss(line);

            int i = 0;
            char temp;
            char temp1[line.size()];
            while (ss >> temp){
                temp1[i] = temp;
                i++;

            }

            int wordsize = line.length();
            add(temp1, wordsize);

            count++;
        }
        cout<< "Total loaded number of words: "<< count <<endl;
        dfile.close();
    }
    Trie(const Trie& orig) = delete;
    Trie& operator =(const Trie& orig) = delete;
    void add(const char word[], int wordsize){
        Trie::Node* p = root;

        for (int i = 0; i < wordsize ; i++ ){
           if(p->next[(int)word[i] - 'a'] == nullptr){

               p->next[(int)word[i] - 'a'] = new Node();
           }


           p = p->next[(int)word[i] - 'a'];
        }
        p->isWord = true;
    }
    void remove(const char word[], int wordsize){
        Trie::Node* p = root;

        for (int i = 0; i < wordsize ; i++ ){
            if(p->next[(int)word[i] - 'a'] == nullptr){
                return;
            }

            p = p->next[(int)word[i] - 'a'];
        }
        p->isWord = false;
    }
    bool contains(const char word[], int wordsize){
        Trie::Node* p = root;

        for (int i = 0; i < wordsize ; i++ ){
            if(p->next[(int)word[i] - 'a'] == nullptr){
                return false;
            }

            p = p->next[(int)word[i] - 'a'];
        }
        if (p->isWord){ return true; } else { return false;}
    }
    bool containsPrefix(const char word[], int wordsize){
        Trie::Node* p = root;

        for (int i = 0; i < wordsize ; i++ ){
            if(p->next[(int)word[i] - 'a'] == nullptr){

                return false;
            }
            p = p->next[(int)word[i] - 'a'];
        }
        return true;
    }
    void prefixNodeCombine(const char word[], int wordsize, const string& prefix){
        char str[20]; int level = 0;

        Trie::Node* p = root;

        for (int i = 0; i < wordsize ; i++ ){
            if(p->next[(int)word[i] - 'a'] == nullptr){

                return;
            }

            p = p->next[(int)word[i] - 'a'];
        }
        print2(p, str, level, prefix);

    }
    void print(Trie::Node* roott, char str[], int level){
        if (roott->isWord){
            str[level] = '\0';
            cout << str << endl;
        }
        for (int i = 0; i< 26; i++){
            if (roott->next[i] ){
                str[level] = i + 'a';
                print(roott->next[i], str, level+1);

            }
        }

        /*
        Trie::Node* p1 = this->root;
        Trie::Node* p = this->root;
        list<char> printl;
        char cprint;

        for (int i = 0; i< 26; i++){
            while (p->next[i] != nullptr && !p->isWord){
                cprint = i + 'a';
                cout<< cprint;
                int ii = 0;
                while (p->next[i]->next[ii]){

                    ii++;
                }
                p = p->next[i];
                //if (p->isWord){break;}
            }
            p = p1;
        }*/

        //if (p->next[0]->next[0]->isWord){ cout<<endl<< "work"<<endl;} else{cout <<endl<<"second work"<<endl;}
        /*
        for (int i = 0; i< 26; i++){
            if(p->next[0] == nullptr && p->isWord){
                cprint =0+97;
                cout << cprint;
            }
            p = p->next[0];// p->next[i+97];

        }*/
        /*
        for (int i = 0; i < 26; i++){
            sprint = i + 97;
            cout << sprint;
        }*/

        /*
        while (true){
            char xx= 25 + 97;
            p = p->next[xx];
            cout << xx<<endl;
             if (p->isWord){
               cout<< "this worked";
                 break;
             }
        }*/
    }
    void print2(Trie::Node* roott, char str[], int level, const string& prefix){
        if (roott->isWord){//(isleafNode(roott)){
            str[level] = '\0';
            cout << prefix << str << endl;
        }
        for (int i = 0; i< 26; i++){
            if (roott->next[i] ){
                str[level] = i + 'a';
                print2(roott->next[i], str, level+1, prefix);

            }
        }
}

};

class HashMapLinearChaining {
private:
    uint32_t size;
    LinkedList* table;
public:

    HashMapLinearChaining(uint32_t size): size(size) {
        table = new LinkedList[size];
    }

    ~HashMapLinearChaining() = default;

    HashMapLinearChaining(const HashMapLinearChaining &orig) = delete;

    HashMapLinearChaining &operator=(const HashMapLinearChaining &orig) = delete;
    int hash(string s){
        int sum = 0;
        for (int i =0; s[i]!='\0';i++){
            sum = sum * 26+ s[i] + ((sum >> 17)|(sum << 13));
        }
        return sum & (size - 1 );
    }

    void load(const string& filename) {
        std::ifstream dfile;
        dfile.open(filename);
        if (!dfile.is_open()){
            cout << "Error: file did not open testAdd.txt" << endl;
            return;
        }
        std::string line;
        int count = 0;

        while(!dfile.eof()){

            std::getline(dfile,line);
            std::stringstream ss(line);
            add(line);
            count++;
        }
        cout<< "Total loaded number of words: "<< count <<endl;
    }
    void add(const string &s) {
        uint32_t pos;

        pos = hash(s);
        if (pos >= 500000){pos = 0;}

        LinkedList::Node *p = table[pos].head;
        if (p == nullptr){
            table[pos].addStart(s);
        } else{
        while (p->next != nullptr){
            if (p->data == s){
                return;}
            p = p->next;
        }
            table[pos].addStart(s);
        }
    }

    void remove(const string &s) {
        int pos;
        pos = hash(s);

        if (table[pos].head == nullptr){
                return;
        } else {
            table[pos].removeValue(s);
        }

    }

    bool contains(const string &s) {
        int pos;
        pos = hash(s);
        if (table[pos].head != nullptr){
            if (table[pos].head->data == s){
                return true;
            }
        } else{
            return false;}
        while (table[pos].head->next != nullptr){
            if (table[pos].head->data == s){
                return true;
            }
            table[pos].head = table[pos].head->next;
        }
        return false;
    }

    void computeHistogram() {
        // generate an array of 10 elements
        //hist[0] = number of empty bins
        // hist[1] = number of bins containing 1 element
        // hist[2] = number of bins containing 2 elements...

        // hist[9] = number of bins containing 9 OR GREATER
        //		print all non-zero bins:
        int empt, cont1, cont2, cont9;
        empt = 0;
        cont1 = 0;
        cont2 = 0;
        cont9 = 0;
        for (int i = 0; i < size; i++) {
            if (this->table[i].size() == 0) { empt++; }
            else if (this->table[i].size() == 1) { cont1++; }
            else if (this->table[i].size() == 2) { cont2++; }
            else { cont9++; }
        }
        cout << "number of empty bins:                " << empt << endl;
        cout << "number of contains 1 bins:           " << cont1 << endl;
        cout << "numnber of contains 2 bins:          " << cont2 << endl;
        cout << "number of contains more than 9 bins: " << cont9 << endl;

        for (int i = 0; i < size; i++) {
            if (this->table[i].size() == 0 || this->table[i].size() == 1 || this->table[i].size() == 2){ continue;}
            else {
                this->table[i].showList2();
            }
        }
    }

    void printAsList(){

        for (int i =0; i < size; i++){
            if (this->table[i].size() != 0){
                std::cout << "Table[" << i << "]: as list = ";
                this->table[i].showList();
                cout<<endl;}

        }

    }

};


int main() {
    //###### this is for Trie
    cout << "-------------------"<<endl<< "      TRIE     "<<endl<<"-------------------"<<endl;
    Trie trie1,trie2;

    std::string filename1, filename2, filename22, filename3, filename4;
    filename1 = "./testAdd.txt";
    filename2 = "./testContains.txt";
    filename22 = "./testTriePrefix.txt";
    filename3 = "./testRemove.txt";
    filename4 = "./prideandprejudice.txt";
    std::ifstream dfile1,dfile2,dfile22,dfile3,dfile4;
    dfile1.open(filename1);
    dfile2.open(filename2);
    dfile22.open(filename22);
    dfile3.open(filename3);
    dfile4.open(filename4);

    if (!dfile2.is_open() || !dfile1.is_open() || !dfile22.is_open() || !dfile3.is_open()){
        cout << "Error: one of the file is not opened" << endl;

    } else{
        cout << "### Add words in testAdd.txt file"<<endl;
        trie2.load(filename1);
        /// Check word contain
        cout<<"### Trie contained word from testContained.txt"<<endl;
        std::string line;
        while(!dfile2.eof()){
            std::getline(dfile2,line);
            std::stringstream ss(line);
            int i = 0;
            char temp;
            char temp1[line.size()];
            while (ss >> temp){
                temp1[i] = temp;
                i++;
            }
            int wordsize = line.length();
            if(trie2.contains(temp1, wordsize)){
                cout<<line<<endl;
            }
            ss.clear();
        }

        /// Check word with prefix
        cout<<"### Check all words with prefix in testTriePrefix.txt"<<endl;
        while(!dfile22.eof()){
            std::getline(dfile22,line);
            std::stringstream ss(line);
            int i = 0;
            char temp;
            char temp1[line.size()];
            while (ss >> temp){
                temp1[i] = temp;
                i++;
            }
            int wordsize = line.length();
            if(trie2.containsPrefix(temp1, wordsize)){
                trie2.prefixNodeCombine(temp1, wordsize, line);
            }
        }
        /// Remove words in testRemove.txt
        cout<< "### Remove words in testRemove.txt: Done"<<endl;
        while(!dfile3.eof()){
            std::getline(dfile3,line);
            std::stringstream ss(line);
            int i = 0;
            char temp;
            char temp1[line.size()];
            while (ss >> temp){
                temp1[i] = temp;
                i++;
            }
            int wordsize = line.length();
            trie2.remove(temp1,wordsize);
        }
        /// print final trie
        cout<<"### print final trie"<<endl;
        int level = 0;
        char str[100];
        trie2.print(trie2.Root(), str, level);
    }
    /// Load dict to a diferent trie instance
    cout <<"###  Creat trie and load dict.txt "<< endl;
    trie1.load("./dict.txt");

    std::string line;
    int mainct = 0;
    while(!dfile4.eof()){
        //cout << "I'm inside the file"<<endl;
        std::getline(dfile4,line);
        //cout << line << endl;
        std::stringstream ss(line);

        std::string sline;
        char temp;

        while (ss >> sline){
           // cout << "I'm inside the first loop"<<endl;
            std::stringstream ss2(sline);
            int i = 0;
            char temp1[sline.size()];
            while (ss2 >> temp){
               // cout << "I'm inside the second loop"<<endl;
                if (((int)temp >= 97 && (int)temp <= 122)){

                    temp1[i] = temp;
                    i++;
                    }
                else {
                         break; }
            }
            if (!trie1.contains(temp1, i)) {
                mainct++;
            }
          ss.clear(); ss2.clear();
        }
    }
    cout<< "Total number of non-words at prideandprejudice file: "<< mainct<< " out of 125525"<<endl;

    //##### this is for Hash - linear chaining
    cout << "-------------------"<<endl<< "       HASH    "<<endl<<"-------------------"<<endl;

    uint32_t const defhashsize = 500000;
    HashMapLinearChaining hash1(defhashsize), hash2(defhashsize);
    dfile1.clear();dfile2.clear();dfile3.clear();
    if (!dfile1.is_open() || !dfile2.is_open() || !dfile3.is_open()){
        cout << "Error: Error: one of the file is not opened" << endl;
    } else{
        cout << "### Add words in testAdd.txt file"<<endl;
        hash2.load(filename1);
        cout<< "### Hash histogram "<<endl;
        hash2.computeHistogram();
        cout<<endl;

        cout<< "### check words that in contain file"<<endl;
        if (!dfile2.is_open()){
            cout << "Error: file did not open testContains.txt" << endl;
        }

        dfile2.seekg(0);

        while(!dfile2.eof()){
            std::string line2;
            std::getline(dfile2,line2);
            std::stringstream ss(line2);
            if (hash2.contains(line2)){cout<<line2<<endl;}
        }

        /// Remove words in testRemove.txt
        cout<< "### Remove words in testRemove.txt: Done"<<endl;

        while(!dfile3.eof()){
            std::string line3;
            std::getline(dfile3,line3);
            std::stringstream ss(line3);

           hash2.remove(line3);
        }

        /// Print final hash
        std::cout<< "### Print Hash as list "<<std::endl;
        hash2.printAsList();
    }

    cout << "load dict into a new hash" << endl;
    hash1.load("./dict.txt");
        dfile4.close();
        dfile4.open(filename4);
    mainct = 0;
    while(!dfile4.eof()){
        std::getline(dfile4,line);
        std::stringstream ss(line);

        string sline;
        char temp;

        while (ss >> sline){
            std::stringstream ss2(sline);
            if (!hash1.contains(sline)){mainct++;}
            int i = 0;
        }

    }
    cout<< "Total number of non-words at prideandprejudice file: "<< mainct<< " out of 125525"<<endl;

    dfile1.close(); dfile2.close(); dfile22.close(); dfile3.close();dfile4.close();
    return 0;
}