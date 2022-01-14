#include <iostream>

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
    Tree();
    string build(string z, string s, node* p);
    string makepostfix(node* p);
    string makeprefix(node* p);
    string makeinfix();
};

Tree::Tree() {
    root = nullptr;
}

string Tree::build(string z, string s, node* p) {
    if(z == "infix"){
        return s;
    }
    else if(z == "prefix"){
        if(s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/'){
            string s1 = s.substr(0, 1);
            p->setval(s1);
            s = build(z, s.substr(2), p->getl());
            s = build(z, s.substr(1), p->getr());
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
        return s;
    }
    return s;
}

string Tree::makepostfix(node* p) {
    string s = "";
    if(p == nullptr) return s;
    s += makepostfix(p->getl());
    s += makepostfix(p->getr());
    s += p->getval();
}

string Tree::makeprefix(node* p) {
    string s = "";
    if(p == nullptr) return s;
    s += p->getval();
    s += makeprefix(p->getl());
    s += makeprefix(p->getr());
}

string Tree::makeinfix() {
    return string();
}

int main() {
    string z, s;
    cin >> z >> s;
    return 0;
}
