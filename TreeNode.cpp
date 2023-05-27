#include <vector>
#include <iostream>

using namespace std;


template<class T>
class TreeNode {
private:
    TreeNode<T> *left, *right;
    T data;
    TreeNode<T> *parent;
    vector<T> tmp;



    void dfs() {
        this->tmp.push_back(data);
        if (this->left != nullptr) this->dsf(this->left);
        if (this->right != nullptr) this->dsf(this->right);
    }

public:
    using iterator = typename vector<T>::iterator;
    using const_iterator = typename vector<T>::const_iterator;

    TreeNode(T data_, TreeNode *left_, TreeNode *right_) : data(data_), left(left_), right(right_), parent(nullptr) {
        if (left_ != nullptr) {
            left_->parent = this;
        }
        if (right_ != nullptr) {
            right_->parent = this;
        }
        this->dfs();
    }

    TreeNode() : left(nullptr), right(nullptr), parent(nullptr),tmp(){};

    TreeNode(const TreeNode<T> &x):left(x.left),right(x.right),parent(x.parent),tmp(x.tmp){};

    TreeNode &operator=(const TreeNode<T> &x) {
        if (*x == this) {
            return *this;
        }
        this->data = x.data;
        this->left = x.left;
        this->right = x.right;
        this->parent = x.parent;
        this->tmp=x.tmp;
        return *this;
    }

    ~TreeNode() {
        if (left != nullptr) {
            delete left;
        }
        if (right != nullptr) {
            delete right;
        }
        this->left = nullptr;
        this->right = nullptr;
    }

    bool operator==(const TreeNode<T> &test) const {
        return tmp==test.tmp;
    }

    iterator begin() {
        return tmp.begin();
    }

    const_iterator begin() const {
        return tmp.cbegin();
    }

    iterator end() {
        return tmp.end();
    }

    const_iterator end() const {
        return tmp.cend();
    }

    std::ostream &operator<<(std::ostream& x ){
        for(T t: tmp ){
            x<<t<<"    ";
        }
        return x;
    }

};


template <class T>
TreeNode<T>* v(const T data){
    return new TreeNode<T>(data, nullptr, nullptr);
}
template <class T>
TreeNode<T>* l(const T data, const TreeNode<T>& left){
    return new TreeNode<T>(data, left, nullptr);
}
template <class T>
TreeNode<T>* r(const T data, const TreeNode<T>& r){
    return new TreeNode<T>(data, nullptr, r);
}
template <class T>
TreeNode<T>* lr(const T data, const TreeNode<T>& l,const TreeNode<T>& r){
    return new TreeNode<T>(data, l, r);
}




int main() {
    TreeNode<int> t;

    {
        TreeNode<int> *x = &t;
    }

}