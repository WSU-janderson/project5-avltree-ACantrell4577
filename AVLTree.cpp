#include "AVLTree.h"

#include <string>

//inserts node into the Tree using recursion
bool AVLTree::insert(const string& key, size_t value) {

}

//removes a node from the Tree using recursion
bool AVLTree::remove(const string& key) {

}

//searches the Tree for a node with the desired key
bool AVLTree::contains(const string& key) const {

    //if the tree is empty return false
    if (this->root == nullptr) {
        return false;
    }

    else {
        AVLNode* current = this->root;
        //recursive call to try and find the key
        bool found = containsNode(*current, key);
        //if found return true
        if (found) {
            return true;
        }
        //else false
        else {
            return false;
        }
    }


}

//itterates through the tree
bool AVLTree::containsNode(AVLNode& node, const string& key) const{

    //sets variables
    AVLNode* parent = &node;
    AVLNode* current = &node;
    bool found;

    //if found return found
    if (current->key == key) {
        found = true;
        return found;
    }

    //while not at the end of a branch itterate
    while (current != nullptr) {
        //if there is a left leaf
        if (parent->left != nullptr) {
            //set current to left leaf then recursively call
            current = current->left;
            found = containsNode(*current, key);
            //if node is found return true
            if (found) {
                return true;
            }
        }
        //if there is a right leaf
        else if (parent->right != nullptr) {
            //set current node and recursively call
            current = current->right;
            found = containsNode(*current, key);
            //if found then return true
            if (found) {
                return true;
            }
        }
    }

    //if never founds return false
    return false;

}


//Gets the value of a desired key using recursion
optional<size_t> AVLTree::get(const string& key) const {

    //if the tree is empty return nullopt
    if (this->root == nullptr) {
        return nullopt;
    }

    //set current to root
    AVLNode* current = this->root;
    //calls recurseive method to find the value, and if found return value else return null opt
    return get(*current, key);
}

//reccursive get call to return the value of desired string
optional<size_t> AVLTree::get(AVLNode& parent, const string& key) const {

    if (parent.key == key) {
        return parent.value;
    }

    AVLNode* current = &parent;
    optional<size_t> val;

    //if left node exists
    if (parent.left != nullptr) {
        //set current to left node then recursive call
        current = parent.left;
        val = get(*current, key);
        //if val has a value return
        if (val != nullopt) {
            return val;
        }
    }

    //if right node exists
    else if (parent.right != nullptr) {
        //set current to right node then recursive call
        current = parent.right;
        val = get(*current, key);
        //if val has a value return
        if (val != nullopt) {
            return val;
        }
    }

    //if not found return nullopt
    return nullopt;
}

//overloads [] operator to find values with the desired string
size_t& AVLTree::operator[] (const string& key) {

    if (this->root->key == key) {
        return this->root->value;
    }
    else {
        AVLNode* current = this->root;
        return search(*current, key);
    }
}

size_t& AVLTree::search(AVLNode& parent, const string& key) {

    if (parent.key == key) {
        return parent.value;
    }

    AVLNode* current = &parent;
    size_t* val = nullptr;

    //if left node exists
    if (parent.left != nullptr) {
        //set current to left node then recursive call
        current = parent.left;
        *val = search(*current, key);
        //if val has a value return
        if (val != nullptr) {
            return *val;
        }
    }

    //if right node exists
    else if (parent.right != nullptr) {
        //set current to right node then recursive call
        current = parent.right;
        *val = search(*current, key);
        //if val has a value return
        if (val != nullptr) {
            return *val;
        }
    }

    //if not found return nullptr
    return *val;

}

//finds a range of values inside the Tree using recursion
vector<string> AVLTree::findRange(const string& lowKey, const string& highKey) const {

}

//returns a vector with all of the current keys in the Tree
vector<string> AVLTree::keys() const {

}

//returns the AVLSize value of the AVL Tree
size_t AVLTree::size() const {

    return this->AVLSize;

}

//returns the height of the AVL tree
size_t AVLTree::getHeight() const {
    //calls getHeight on the root node of the AVL tree
    return root->getHeight();
}

//copy constructor using recursion
AVLTree::AVLTree(const AVLTree& other) {

}

//overloads equals operator to create a deep copy of the origional tree
void AVLTree::operator=(const AVLTree& other) {

}

//destructor
AVLTree::~AVLTree() {

}

//overloads the << operator to print the entire AVL tree using reccursion
ostream& operator<<(ostream& os, const AVLTree& tree) {

}

//returns the number of children a node has
size_t AVLTree::AVLNode::numChildren() const {

    //variable declaration
    size_t children = 0;

    //if there is a right node increase children
    if (this->right) {
        children++;
    }

    //if there is a left node increase children
    if (this->left) {
        children++;
    }

    //return the number of children
    return children;
}

//checks to see if the current node is a leaf node
bool AVLTree::AVLNode::isLeaf() const {

    //if there are no children return true
    if (this->numChildren() == 0) {
        return true;
    }

    //else return false
    else {
        return false;
    }
}

//returns the height of the current node
size_t AVLTree::AVLNode::getHeight() const {
    return this->height;
}

//recursively moves through the Tree to find and remove the desired node
bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}

//
bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}


void AVLTree::balanceNode(AVLNode *&node) {
}
