#include "AVLTree.h"
#include <iostream>

#include <string>

//inserts node into the Tree using recursion
bool AVLTree::insert(const string& key, size_t value) {

    //if empty tree
    if (root == nullptr) {
        root = new AVLNode();
        root->key = key;
        root->value = value;
        return true;
    }
    //if not
    else {

        //if the key already exists
        if (this->contains(key)) {
            return false;
        }
        else {
            //inserts node
            return insertNode(*this->root, key, value);
        }
    }

}

//recursive method to insert a node
bool AVLTree::insertNode(AVLNode& node, const string& key, size_t value) {

    //if key is greater than insert
    if (node.key > key) {

        //if left node is empty
        if (node.left == nullptr) {
            //create new node with data
            AVLNode* newNode = new AVLNode();
            newNode->key = key;
            newNode->value = value;

            //make new left leaf
            node.left = newNode;
        }
        //if not leaf node recursive call
        else {
            insertNode(*node.left, key, value);
        }
        AVLUpdateHeight(&node);
        return true;

    }

    //if key is less than insert
    if (node.key < key) {

        //if right node is empty
        if (node.right == nullptr) {
            //create new node with data
            AVLNode* newNode = new AVLNode();
            newNode->key = key;
            newNode->value = value;

            //make new right leaf
            node.right = newNode;
        }
        //if not leaf node recursive call
        else {
            insertNode(*node.right, key, value);
        }
        AVLUpdateHeight(&node);
        return true;

    }

}

//removes a node from the Tree using recursion
bool AVLTree::remove(const string& key) {

    //if tree is empty
    if (root == nullptr) {
        return false;
    }
    //if not
    else {
        //if key dosent exist
        if (!(this->contains(key))) {
            return false;
        }
        else {
            return remove(this->root, key);
        }
    }

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

        if (current->left == nullptr && current->right == nullptr) {
            return false;
        }


        //if key is less than parent
        if (parent->key > key) {
            //if left key exists
            if (parent->left != nullptr) {
                //set current to left leaf then recursively call
                current = current->left;
                found = containsNode(*current, key);
                //if node is found return true
                if (found) {
                    return true;
                }
            }
            else {
                return false;
            }
        }
        //if key is greater than parent
        if (parent->key < key) {
            if (parent->right != nullptr) {
                //set current node and recursively call
                current = current->right;
                found = containsNode(*current, key);
                //if found then return true
                if (found) {
                    return true;
                }
            }
            else {
                return false;
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
    if (parent.left != nullptr && parent.key > key) {
        //set current to left node then recursive call
        current = parent.left;
        val = get(*current, key);
        //if val has a value return
        if (val != nullopt) {
            return val;
        }
    }

    //if right node exists
    if (parent.right != nullptr && parent.key < key) {
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
    if (parent.left != nullptr && parent.key > key) {
        //set current to left node then recursive call
        current = parent.left;
        *val = search(*current, key);
        //if val has a value return
        if (val != nullptr) {
            return *val;
        }
    }

    //if right node exists
    if (parent.right != nullptr && parent.key < key) {
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

//TODO
//finds a range of values inside the Tree using recursion
vector<string> AVLTree::findRange(const string& lowKey, const string& highKey) const {
    vector<string> range;
    return range;
}

//returns a vector with all of the current keys in the Tree
vector<string> AVLTree::keys() const {



    //creates vector
    vector<string> keys;

    if (this->root != nullptr) {
        AVLNode* current = this->root;
        keyVector(*current, keys);
    }

    return keys;
}

//itterates through the tree adding keys by reference to the keys vector
void AVLTree::keyVector(AVLNode& parent, vector<string>& keys) const {

    //creates variable
    AVLNode* current = &parent;

    //if left node exists
    if (parent.left != nullptr) {
        //set current to left
        current = parent.left;
        //recursive call
        keyVector(*current, keys);
    }

    //adds key to vector before right side
    keys.push_back(parent.key);

    //if right exists
    if (parent.right != nullptr) {
        //set current to right node
        current = parent.right;
        //recursive call
        keyVector(*current, keys);
    }

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

    //if the tree is empty set new tree to empty
    if (other.root == nullptr) {
        this->root = nullptr;
    }
    //else recursive copy function
    else {
        this->root = copyTree(*other.root);
    }

}

//recursive call for AVLTree
AVLTree::AVLNode* AVLTree::copyTree(AVLNode& parent) {

    //vairable declaration
    AVLNode* current;

    //creates a new node
    AVLNode* node = new AVLNode();

    //if a left node exists
    if (parent.left != nullptr) {
        //sets current to left
        current = parent.left;
        //recursive call is set to the new nodes left
        node->left = copyTree(*current);
    }

    //if a right node exists
    if (parent.right != nullptr) {
        //sets current to right node
        current = parent.right;
        //recursive call sets to the new nodes right
        node->right = copyTree(*current);
    }

    node->key = parent.key;
    node->value = parent.value;
    node->height = parent.height;

}

//overloads equals operator to create a deep copy of the origional tree
void AVLTree::operator=(const AVLTree& other) {

    //cals a destructor to delete all existing nodes
    clearTree(*this->root);

    //calls copy method to copy the other AVLTree
    copyTree(*other.root);
}

//destructor
AVLTree::~AVLTree() {

    clearTree(*this->root);
    delete this->root;

}

//deletes all but the root node
void AVLTree::clearTree(AVLNode& parent) {

    AVLNode* current = &parent;

    //if a left node exists
    if (parent.left != nullptr) {
        //set current and recursive call
        current = parent.left;
        clearTree(*current);
        //delete the left node
        delete parent.left;
    }

    //if right node exists
    if (parent.right != nullptr) {
        //sets current and recursive call
        current = parent.right;
        clearTree(*current);
        //deletes right child
        delete parent.right;
    }

}

//overloads the << operator to print the entire AVL tree using reccursion
ostream& operator<<(ostream& os, const AVLTree& tree) {

    size_t depth = 0;
    tree.printTree(os, *tree.root, depth);
    return os;
}

//prints the tree to the os
void AVLTree::printTree(ostream &os, AVLNode &parent, size_t &depth) const{

    //if right exists
    if (parent.right != nullptr) {
        //increase depth and dive deeper
        size_t newDepth = depth + 1;
        printTree(os, *parent.right, newDepth);
    }

    //print tabs for depth
    for (int i = 0; i < depth; i++) {
        os << "\t";
    }
    //print key value pair
    os << "{" << parent.key << " : " << parent.value << "}" << endl ;

    //if left tree exists
    if (parent.left != nullptr) {
        //increases depth then dive deeper
        size_t newDepth = depth + 1;
        printTree(os, *parent.left, newDepth);
    }
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

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}

//recursively iterates through the tree to find the correct node and remove it
bool AVLTree::remove(AVLNode *&current, KeyType key) {

    //when key is found return true and remove node
    if (current->key == key) {
        return removeNode(current);
    }

    if (current->left != nullptr && current->key > key) {
        //set current to left node then recursive call
        current = current->left;
    }

    //if right node exists
    if (current->right != nullptr && current->key < key) {
        //set current to right node then recursive call
        current = current->right;
    }

    return true;
}

//TODO
//Balances the node if out of balance
void AVLTree::balanceNode(AVLNode *&node) {

    //update node height
    AVLUpdateHeight(node);
    //out of balance
    if (AVLGetLoadBalance(node) == -2) {
        //needs second rotation
        if (AVLGetLoadBalance(node->right) == 1) {
            //rotate right
        }
        //rotate left
    }
    //out of balance
    else if (AVLGetLoadBalance(node) == 2) {
        //needs second rotation
        if (AVLGetLoadBalance(node->left) == -1) {
            //rotate left
         }
        //Rotate right
     }
}

//updates the height of the node
void AVLTree::AVLUpdateHeight(AVLNode *node) {
    //sets left height
    size_t leftH = -1;
   if (node->left != nullptr) {
       leftH = node->left->height;
   }
    //sets right height
    size_t rightH = -1;
    if (node->right != nullptr) {
        rightH = node->right->height;
    }
    //sets node height to the larger one + 1
     node->height = max(leftH, rightH) + 1;
}

//gets the load balance of the node
size_t AVLTree::AVLGetLoadBalance(AVLNode *node) {
    //sets left height
    size_t leftH = -1;
    if (node->left != nullptr) {
        leftH = node->left->height;
    }
    //sets right height
    size_t rightH = -1;
     if (node->right != nullptr) {
         size_t rightH = node->right->height;
     }
    //returns load balance
      return leftH - rightH;
   }

//TODO
//rotates the node to the left
void AVLTree::leftRorate(AVLNode *node) {


}

//TODO
//rotates the node to the right
void AVLTree::rightRorate(AVLNode *node) {


}
