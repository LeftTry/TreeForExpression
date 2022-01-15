#include <iostream>
#include "vector"
#include "string"
#include "sstream"

using namespace std;

class node{
    string s;
    node* l;
    node* r;
public:
    node();
    node(string c);
    node* getl();
    node* getr();
    string getval();
    void setl(node* l);
    void setr(node* r_);
    void setval(string str);
};

node::node() {
    s = "";
    l = nullptr;
    r = nullptr;
}

node *node::getl() {
    return l;
}

node *node::getr() {
    return r;
}

string node::getval() {
    return s;
}

void node::setl(node* l_) {
    l = l_;
}

void node::setr(node *r_) {
    r = r_;
}

void node::setval(string str) {
    s = str;
}

node::node(string c) {
    s = c;
}

class Tree{
    node* root;
    vector<int> blnc;
public:
    node* getroot();
    Tree();
    string build(const string& z, string s, node* p);
    string makepostfix(node* p);
    string makeprefix(node* p);
    string makeinfix(node* p);
};

Tree::Tree() {
    root = nullptr;
}

string Tree::build(const string& z, string s, node* p) {
    if(z == "infix") {
        if (blnc.empty()){
            blnc.resize(s.size());
            int balance = 0;
            for (int i = 0; i < s.size(); i++) {
                if (s[i] == '(') {
                    balance++;
                    blnc[i] = balance;
                }
                else if (s[i] == ')') {
                    balance--;
                    blnc[i] = balance;
                }
                else{
                    blnc[i] = balance;
                }
            }
            int min = 1e9 + 7;
            int mini = -1;
            for(int i = s.size() - 1;i >= 0;i--){
                if(blnc[i] < min){
                    min = blnc[i];
                    mini = i;
                }
            }
            int j = mini;
            while(blnc[j] == mini && (s[j] != '+' && s[j] != '-' && s[j] != '*' && s[j] != '/')) j--;
            p->setval(s.substr(j, 1));
        }

    }
    else if(z == "prefix"){
        if(s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/'){
            string s1 = s.substr(0, 1);
            p->setval(s1);
            s = build(z, s.substr(2), p->getl());
            s = build(z, s, p->getr());
        }
        else{
            int i = 0;
            while(s[i] != ' ') i++;
            p->setval(s.substr(0, i));
            s = s.substr(i + 1);
            return s;
        }
    }
    else if(z == "postfix"){
        if(s[s.size() - 1] == '+' || s[s.size() - 1] == '-' || s[s.size() - 1] == '*' || s[s.size() - 1] == '/'){
            string s1 = s.substr(s.size() - 1);
            p->setval(s1);
            s = build(z, s.substr(0, s.size() - 2), p->getr());
            s = build(z, s, p->getl());
        }
        else{
            int i = s.size() - 1;
            while(s[i] != ' ') i--;
            p->setval(s.substr(i));
            s = s.substr(0, i);
            return s;
        }
        return s;
    }
    return s;
}

string Tree::makepostfix(node* p) {
    string s = "";
    if(p == nullptr) return "";
    s += makepostfix(p->getl());
    s += " ";
    s += makepostfix(p->getr());
    s += " ";
    s += p->getval();
    return s;
}

string Tree::makeprefix(node* p) {
    string s = "";
    if(p == nullptr) return "";
    s += p->getval();
    s += makeprefix(p->getl());
    s += makeprefix(p->getr());
    return s;
}

string Tree::makeinfix(node* p) {
    string s = "";
    if(p == nullptr) return "";
    s += ")";
    s = makeinfix(p->getr()) + s;
    s = " " + s;
    s = p->getval() + s;
    s = " " + s;
    s = makeinfix(p->getl()) + s;
    s = " " + s;
    s = "(" + s;
}

node *Tree::getroot() {
    return root;
}

int main() {
    string z, s;
    cin >> z >> s;
    return 0;
}
