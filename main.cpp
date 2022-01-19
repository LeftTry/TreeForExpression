#include <iostream>
#include "vector"
#include "algorithm"
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
    l = nullptr;
    r = nullptr;
    s = c;
}

class Tree{
    node* root;
    vector<int> blnc;
public:
    node* getroot();
    void setroot(node* p);
    Tree();
    void build(const string& z, string& s, node* p);
    string makepostfix(node* p);
    string makeprefix(node* p);
    string makeinfix(node* p);
};

Tree::Tree() {
}

void Tree::build(const string& z, string& s, node* p) {
    if(z == "infix") {
        if (blnc.empty()) {
            blnc.resize(s.size(), 10);
            int balance = 0;
            for (int i = 0; i < s.size(); i++) {
                if (s[i] == '(') {
                    balance++;
                    blnc[i] = balance;
                } else if (s[i] == ')') {
                    balance--;
                    blnc[i] = balance;
                } else {
                    blnc[i] = balance;
                }
            }
        }
        int min = 1e9 + 7, minel = 0;
        for(int i = s.size() - 1;i >= 0;i--){
            if(blnc[i] < min){
                min = blnc[i];
                minel = i;
            }
        }
        int i = minel;
        while(i >= 0 && (s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/')) i--;
        if(i == -1){
            for(int i = 0;i < s.size();i++){
                if(s[i] == ' ') s = s.substr(0, i) + s.substr(i + 1);
            }
            p->setval(s);
            return;
        }
        p->setval(s.substr(i, 1));
        node* r = new node("");
        p->setr(r);
        node* l = new node("");
        p->setl(l);
        string sl = s.substr(0, i);
        string sr = s.substr(i + 1);
        build(z, sl, p->getl());
        build(z, sr, p->getr());
    }
    else if(z == "prefix"){
        if(s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/'){
            string s1 = s.substr(0, 1);
            p->setval(s1);
            node* r = new node("");
            p->setr(r);
            node* l = new node("");
            p->setl(l);
            s = s.substr((2));
            build(z, s, p->getl());
            build(z, s, p->getr());
        }
        else{
            int i = 0;
            while(i < s.size() && s[i] != ' ') i++;
            p->setval(s.substr(0, i));
            if(i < s.size())
                s = s.substr(i + 1);
            else
                return;
            return;
        }
    }
    else if(z == "postfix"){
        if(s[s.size() - 1] == '+' || s[s.size() - 1] == '-' || s[s.size() - 1] == '*' || s[s.size() - 1] == '/'){
            string s1 = s.substr(s.size() - 1);
            p->setval(s1);
            node* r = new node("");
            p->setr(r);
            node* l = new node("");
            p->setl(l);
            s = s.substr(0, s.size() - 2);
            build(z, s, p->getr());
            build(z, s, p->getl());
        }
        else{
            int i = s.size() - 1;
            while(i >= 0 && s[i] != ' ') i--;
            if(i != -1)
                p->setval(s.substr(i + 1));
            else
                p->setval(s);
            s = s.substr(0, i);
            return;
        }
        return;
    }
    return;
}

string Tree::makepostfix(node* p) {
    string s = "";
    if(p == nullptr) return "";
    s += makepostfix(p->getl());
    s += makepostfix(p->getr());
    s += p->getval();
    s += " ";
    return s;
}

string Tree::makeprefix(node* p) {
    string s = "";
    if(p == nullptr) return "";
    s += p->getval();
    s += " ";
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

void Tree::setroot(node* p) {
    root = p;
}

int main() {
    string z = "infix", s;
    getline(cin, s);
    Tree tree;
    node p("");
    tree.setroot(&p);
    tree.build(z, s, tree.getroot());
    cout << tree.makepostfix(tree.getroot());
    return 0;
}
