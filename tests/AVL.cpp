#include "AVL.hpp"
#include <string.h>

using namespace std;

//Node
 AVL :: Node :: Node(const string &str, Node *parent, Node *left, Node *right){
     element = str;
     this->parent = parent;
     this->left = left;
     this->right = right;
 }
// Returns papa of a node
AVL :: Node* AVL :: Node :: getParent()const{
     return parent;
 }
// Returns left node
 AVL :: Node * AVL :: Node :: getLeft() const{
     return left;
 }
// Returns right node
 AVL :: Node * AVL :: Node :: getRight() const{
     return right;
 }
// Returns the string of curr node
 string AVL :: Node :: getElement()const{
     return element;
 }
// Returns height of a node
 int AVL :: Node :: getHeight()const{
     return height;
 }
 
//Set left right parent node and element of a node
 void AVL :: Node :: setLeft(Node *left){
     this->left = left;
 }
 void AVL :: Node :: setRight(Node *right){
     this->right = right;
 }
 void AVL :: Node :: setParent(Node *parent){
     this->parent = parent;
 }
 void AVL :: Node :: setElement(string string){
     element = string;
 }
 void AVL :: Node :: setHeight(int height){
     this->height = height;
}

 bool AVL :: Node :: isLeft()const{ 
    //No parent return false ASAP
     if(parent == NULL){
        return false;
    }
    if((parent->getLeft() == this)){
        return true;
    }
    return false;
}

 bool AVL :: Node :: isRight()const{
    //If there is no parent return false ASAP
    if(parent == NULL){
        return false;
    }
    if((parent->getRight() == this)){
        return true;
    }
    return false;
}
//Returns height of right node... Returns 0 otherwise
//0 will help for computing if a node is isBalanced
int AVL :: Node :: rightChildHeight() const{
    if(right == NULL){
        return 0;
    }
    return right->getHeight();
}

int AVL :: Node :: leftChildHeight() const{
    if(left == NULL){
        return 0;
    }
    return left->getHeight();
}

int AVL :: Node :: updateHeight(){
    int max;
    
    max = right->getHeight();
    if(max < left->getHeight()){
        max = left->getHeight();
    }
    this->height = max+1;
 return max+1;   
}

//Check if a node is is balanced
bool AVL :: Node :: isBalanced(){
    int leftheight, rightheight;
    int diff;
    
    leftheight = leftChildHeight();
    rightheight = rightChildHeight();
    diff = leftheight-rightheight;
    
    if(diff == -1 || diff == 0 || diff == 1){
        return true;
    }
    return false;
}

//AVL constructor
AVL::AVL() : size(0), root(NULL) {}

AVL :: AVL(const AVL& tree){
    
    root = NULL;
    size = 0;
    
    if(tree.root != NULL){
        //setpreorder
        setPreOrder(this, tree.root);
    }
}

//Method to find if an element is in the tree
bool AVL :: contains(string str){
    
    AVL :: Node *existancenode;
    existancenode = AVL :: findNode(str,root);
    if(existancenode == NULL){
        return false;
    }
    return true;
}
AVL :: Node* :: AVL :: findNode(string str, AVL :: Node *node){
    AVL :: Node *nextforsearch;
    if(node == NULL){
        return NULL;
    }
    
    if(str != node->getElement()){
        nextforsearch = node->getLeft();
        if(nextforsearch != NULL){
            return findNode(str, nextforsearch);
        }
        return node;
    }
    else{
        if(str != node->getElement()){
            return node;
        }
        else{
            nextforsearch = node->getRight(); 
            if(nextforsearch == NULL){
                return node;
            }
            return findNode(str, nextforsearch);
        }
    }
    return NULL;
}

//Max method for height
int max(int a, int b){
    return (a > b)? a : b;
}

//Right rotation
 AVL :: Node *AVL :: rightRotate(AVL :: Node *y){
    AVL :: Node *x = y->getLeft();
    AVL :: Node *T2 = x->getRight();
 
    // Perform rotation
    x->setRight(y);
    y->setLeft(T2);
 
    // Update heights
    y->setHeight(max(y->getLeft()->getHeight(),y->getRight()->getHeight()) + 1);
    x->setHeight(max(x->getLeft()->getHeight(),x->getRight()->getHeight()) + 1);
 
    // Return new root
    return x;
}

//Left rotation
 AVL :: Node *AVL :: leftRotate(AVL :: Node *x){
    
    AVL :: Node *y = x->getRight();
    AVL :: Node *T2 = y->getLeft();
 
    // Perform rotation
    y->setLeft(x);
    x->setRight(T2);
 
    // Update heights
    x->setHeight(max(x->getLeft()->getHeight(),x->getRight()->getHeight()) + 1);
    y->setHeight(max(y->getLeft()->getHeight(),y->getRight()->getHeight()) + 1);
 
    // Return new root
    return y;
}

 AVL :: Node *AVL :: insert(AVL :: Node *node, string str){
     int balance;
     
    //Empty tree
    if(node == NULL){
        return (new AVL :: Node(str, NULL, NULL, NULL));
    }
    
    if(str < node->getElement()){
        node->setLeft(insert(node->getLeft(), str));
    }
    else if (str > node->getElement()){
        node->setRight(insert(node->getRight(), str));
    }
    // Equal strings are not allowed in BST
    else {
        return node;
    }
    node->setHeight( 1 + max(node->leftChildHeight(),node->rightChildHeight()));
    
    balance = node->leftChildHeight() - node->rightChildHeight();
    
    //Left Left rotation
    if (balance > 1 && str < node->getLeft()->getElement()){
        return rightRotate(node);
    }
    
    //Right Right rotation
    if (balance < -1 && str > node->getRight()->getElement()){
        return leftRotate(node);
    }
    
    //Right Left rotation
    if (balance < -1 && str < node->getRight()->getElement()){
        node->setRight(rightRotate(node->getRight()));
        return leftRotate(node);
    }
    
    //Left right rotation
    if (balance > 1 && str > node->getLeft()->getElement()){
        node->setLeft(leftRotate(node->getLeft()));
        return rightRotate(node);
    }
    return node;
}

bool AVL :: add(string string){
    AVL :: Node *inserting;
    
    //String to insert already exists!!!
    if(AVL :: contains(string) ){
        return false;
    }
    //If String is not present!
    inserting = AVL :: insert(root, string);
    if(inserting == NULL){
        return false;
    }
    //increase how big the tree is
    size++;
    
    //If i got here it means node inserted so true
    return true;
}

bool AVL :: rmv(string str){
    AVL :: Node *todelete;
    
    if(!AVL :: contains(str)){
        return false;
    }
    
    todelete = AVL :: deleteNode(root, str);
    if(todelete == NULL){
        return false;
    }
    
    //Lower height
    size--;
    
    return true;
}

AVL :: Node *AVL :: minValueNode(AVL :: Node* node){ 
    AVL :: Node* current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current->getLeft() != NULL){ 
        current = current->getLeft(); 
    }
  
    return current; 
}

AVL :: Node *AVL :: deleteNode(AVL :: Node *root, string str){
    
    int balance;
    
    if (root == NULL){ 
        return root; 
    }
    if ( str < root->getElement() ) 
        root->setLeft(deleteNode(root->getLeft(), str)); 
  
    // If the key to be deleted is greater 
    // than the root's key, then it lies 
    // in right subtree 
    else if( str > root->getElement() ) 
        root->setRight(deleteNode(root->getRight(), str)); 
  
    // if key is same as root's key, then 
    // This is the node to be deleted 
    else{ 
        // node with only one child or no child 
        if( (root->getLeft() == NULL) || (root->getRight() == NULL) ){ 
            AVL :: Node *temp = root->getLeft() ? root->getLeft() : root->getRight(); 
  
            // No child case 
            if (temp == NULL){ 
                temp = root; 
                root = NULL; 
            } 
            else // One child case 
            *root = *temp; // Copy the contents of 
                           // the non-empty child 
            free(temp); 
        } 
        else
        { 
            // node with two children: Get the inorder 
            // successor (smallest in the right subtree) 
            Node* temp = minValueNode(root->getRight()); 
  
            // Copy the inorder successor's data to this node 
            root->setElement(temp->getElement()); 
  
            // Delete the inorder successor 
            root->setRight(deleteNode(root->getRight(),temp->getElement())); 
        } 
    }
  
    // If the tree had only one node return 
    if (root == NULL){
        return root; 
    }
    root->setHeight( 1 + max(root->leftChildHeight(),root->rightChildHeight())); 
  
    balance = root->leftChildHeight() - root->rightChildHeight(); 
  
    // Left Left rotation 
    if (balance > 1 && (root->getLeft()->leftChildHeight() - root->rightChildHeight() >= 0)){
        return rightRotate(root); 
    }
  
    // Left Right Case 
    if (balance > 1 && (root->getLeft()->leftChildHeight() - root->rightChildHeight()) < 0){ 
        root->setLeft(leftRotate(root->getLeft())); 
        return rightRotate(root); 
    } 
  
    // Right Right Case 
    if (balance < -1 && (root->leftChildHeight() - root->getRight()->rightChildHeight()) <= 0) 
        return leftRotate(root); 
  
    // Right Left Case 
    if (balance < -1 && (root->leftChildHeight() - root->getRight()->rightChildHeight()) > 0){ 
        root->setRight(rightRotate(root->getRight())); 
        return leftRotate(root); 
    } 
  
    return root; 
} 


void AVL :: pre_order(Node *node, std::ostream& out){
    
    if(root != NULL){ 
        out << root->getElement() << " "; 
        pre_order(root->getLeft(), out); 
        pre_order(root->getRight(), out); 
    }
}

void AVL::setPreOrder(AVL *tree,AVL::Node *node){
    
    if(node != NULL) {
        string str = node->getElement();
        tree->add(str);
        //add kids now
        if(node->getLeft() != NULL) {
            setPreOrder(tree, node->getLeft());
        }
        if(node->getRight() != NULL) {
            setPreOrder(tree, node->getRight());
        }
    }
}
