/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <optional>
#include <string>
#include <vector>

using namespace std;

class AVLTree {
public:
    using KeyType = std::string;
    using ValueType = size_t;

protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;

        AVLNode* left;
        AVLNode* right;

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;


    };

public:

    //Default constructor
    AVLTree() : root(nullptr), AVLSize(NULL) {};

    //used to insert into the tree
    bool insert(const string& key, size_t value);

    //used to remove a node from the tree
    bool remove(const string& key);

    //checks to see if the key exists inside the tree
    bool contains(const string& key) const;

    //returns the value of the desired key node
    optional<size_t> get(const string& key) const;

    //recursive get call
    optional<size_t> get(AVLNode& parent, const string& key) const;

    //overloads the [] operator
    size_t& operator[](const string& key);

    //recursive call for [] operator
    size_t& search(AVLNode& parent, const string& key);

    //returns a vector of all of the keys inside the tree
    vector<string> keys() const;

    //returns a vector of a range of values inside the tree
    vector<string> findRange(const string& lowKey, const string& highKey) const;

    //returns the size of the tree
    size_t size() const;

    //retrns the height og the tree
    size_t getHeight() const;

    //creates a deep copy of the tree
    AVLTree(const AVLTree& other);

    //creates a deep copy of the tree
    void operator=(const AVLTree& other);

    //destructor for the tree
    ~AVLTree();

    //overloads << operator
    friend ostream& operator<<(ostream& os, const AVLTree& avlTree);

    //creates new node then inserts it into the tree
    void insertNode(AVLNode& node);

    //reccursive call of contains
    bool containsNode(AVLNode& node, const string& key) const;

    private:
    AVLNode* root;
    size_t AVLSize;


    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType key);

    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);

    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node);

};

#endif //AVLTREE_H