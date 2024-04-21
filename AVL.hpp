#ifndef __AVL_HPP_
#define __AVL_HPP_

#include <iostream>
#include <fstream>

using namespace std;

class AVL {
private:
  class Node {
    Node *parent, *left, *right;
    int height;
    string element;

  public:
    Node(const string &e, Node *parent, Node *left, Node *right);
    
    Node*  getParent() const;
    Node*  getLeft() const;
    Node*  getRight() const;
    string getElement() const;
    int getHeight() const;
    void setLeft(Node *left);
    void setRight(Node *right);
    void setParent(Node *parent);
    void setElement(string string);
    int max(int a, int b);
    void setHeight(int height);
    bool isLeft() const;
    bool isRight() const;
    int  rightChildHeight() const;
    int  leftChildHeight() const;
    int  updateHeight();
    bool isBalanced();
  };
private:
  
  int   size;
  Node* root;
  
public:
    
    class Iterator {
      
    public:
      Iterator& operator++();
      Iterator operator++(int a);
      string operator*(); 
      bool operator!=(Iterator it);
      bool operator==(Iterator it);
    };
    
  Iterator begin() const;  
  Iterator end() const;
  
  static const int MAX_HEIGHT_DIFF = 1;
  AVL();
  AVL(const AVL& );
  bool contains(string e);
  bool add(string e);
  Node *insert(Node *node, string str);
  bool rmv(string e);
  void print2DotFile(char *filename);
  void pre_order(Node *node,std::ostream& out);
  Node *findNode(string str, Node *node);
  Node *rightRotate(Node *y);
  Node *leftRotate(Node *x);
  Node *deleteNode(Node *root, string str);
  Node *minValueNode(Node *node);
  void setPreOrder(AVL *tree,Node *node);

   

  friend std::ostream& operator<<(std::ostream& out, const AVL& tree);  
  AVL& operator  =(const AVL& avl);
  AVL  operator  +(const AVL& avl);
  AVL& operator +=(const AVL& avl);
  AVL& operator +=(const string& e);
  AVL& operator -=(const string& e);
  AVL  operator  +(const string& e);
  AVL  operator  -(const string& e);
};

#endif
