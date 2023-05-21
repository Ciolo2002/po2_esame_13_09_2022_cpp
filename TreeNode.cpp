//
// Created by Michael Sarto on 21/05/23.
//

#include "TreeNode.h"
#include <vector>
#include <iostream>

using namespace std;

template<class T>
class TreeNode {
private:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode<T> *parent;

    static bool equal_aux(const TreeNode<T> *t1, const TreeNode<T> *t2) {
        return t1 == t2 || (t1 != nullptr && t2 != nullptr && *t1 == *t2);
    }

public:

    TreeNode() = default;

    TreeNode(const TreeNode<T> &t) = default;

    TreeNode<T>(const T &t_, TreeNode<T> *l_, TreeNode<T> *r_) : data(t_), left(l_), right(r_), parent(nullptr) {
        prepopulate();
        if (l_ != nullptr) {
            left->parent = this;
        }
        if (r_ != nullptr) {
            right->parent = this;
        }
    }

    ~TreeNode() {
        if (left != nullptr) {
            delete left;
            left = nullptr;
        }
        if (right != nullptr) {
            delete right;
            right = nullptr;
        }
    }


    bool operator==(const TreeNode<T> &test) const {
        return data == test.data && equal_aux(left, test.left) && equal_aux(right, test.right);
    }

    using const_iterator = typename std::vector<T>::const_iterator;
    using iterator = typename std::vector<T>::iterator;
private:
    vector<T> children;

    void dfs(vector<T> &v) {
        v.push_back(data);
        if (left != nullptr) left->dfs(v);
        if (right != nullptr) right->dfs(v);
    }

    void prepopulate() {
        dfs(children);
    }

public:
    iterator begin() {
        return children.begin();
    }

    const_iterator begin() const {
        return children.begin();
    }

    iterator end() {
        return children.end();
    }

    const_iterator end() const {
        return children.end();
    }

};

template<class T>
TreeNode<T> *v(const T t_) {
    return new TreeNode<T>(t_, nullptr, nullptr);
}

template<class T>
TreeNode<T> *l(const T t_, TreeNode<T> *l) {
    return new TreeNode<T>(t_, l, nullptr);
}

template<class T>
TreeNode<T> *r(const T t_, TreeNode<T> *r) {
    return new TreeNode<T>(t_, nullptr, r);
}

template<class T>
TreeNode<T>* lr(const T t_, TreeNode<T>* l, TreeNode<T> *r) {
    return new TreeNode<T>(t_, l, r);
}


int main() {
    auto t1 = shared_ptr<TreeNode<int>>(
            lr(1,
               lr(2,
                  v(3),
                  v(4)),
               r(5,
                 lr(6,
                    v(7),
                    v(8)))));
    auto t3 = shared_ptr<TreeNode<int>>(
            lr(1,
               lr(2,
                  v(3),
                  v(4)),
               r(5,
                 lr(6,
                    v(7),
                    v(8)))));

    auto t2 =
    shared_ptr<TreeNode<int>>(
            lr(1,
               r(5,					// il sottoalbero destro di t2 è uguale al sinistro di t1 e viceversa
                 lr(6,
                    v(7),
                    v(8))),
               lr(2,
                  v(3),
                  v(4))));

    cout << "equality: " << (*t1 == *t2) << ", " <<  endl;	// dereferenziamo gli operandi sinistro e destro del nostro operator== perchè non accetta pointer ma reference


    // test dell'iteratore const
    cout << "const iterator: ";
    for (TreeNode<int>::const_iterator it = t1->begin(); it != t1->end(); ++it)	// t1->begin() ritorna un iterator, che viene convertito in un const_iterator dal costruttore
    {
        const int& n = *it;	// dereferenziando l'iteratore abbiamo accesso const al dato dentro il nodo, quindi non possiamo modificarlo ma solo leggerlo
        cout << n << " ";
    }
    cout << endl;
}