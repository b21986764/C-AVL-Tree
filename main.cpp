//  Hacettepe University Software Laboratory
//  main.cpp
//  Assignment 4
//  Balanced and Left Leaning Red Black Trees
//  Balanced tree implemented fully
//  LLRBT implemented only insert operation
//  Created by Sertaç Güler on 9.12.2022.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <vector>
#include <string.h>
#include <sstream>
using namespace std;

void split(stringstream& ss, vector<string>& out){
    //Splits the lines into tokens
    string inner;
    while(getline(ss, inner, '\t')){
        out.push_back(inner);
    }
}
class rbSec{
public:
    //This node is for secondary nodes and has to declare a color
    rbSec* left;
    rbSec* right;
    string itemName;
    bool color;
    int price;
    //Constructors
    rbSec(){
        itemName = "";
        left = NULL;
        right = NULL;
        price = 0;
        color = false;
    }
    rbSec(string name, int prc,bool clr = false, int hg = 1){
        itemName = name;
        price = prc;
        left = NULL;
        right = NULL;
        color = clr;
    }
};
rbSec* newrbs(string name, int prc){
    rbSec* temp = new rbSec(name, prc);
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

class rbPrim{
public:
    //This node is for category nodes just a bst
    rbPrim* left;
    rbPrim* right;
    rbSec* link;
    string category;
    //constructors
    rbPrim(){
        left = NULL;
        right = NULL;
        link = NULL;
        category = "";
    }
    rbPrim(string ctg){
        left = NULL;
        right = NULL;
        link = NULL;
        category = ctg;
    }
};
//To create a new primary node with specific values
rbPrim* newrbp(string ctg){
    rbPrim* temp = new rbPrim(ctg);
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

rbSec* leftrbs(rbSec* root)
{
    //rotates left of a subtree
    rbSec* temp = root -> right;
    rbSec *lt = temp -> left;

    temp -> left = root;
    root -> right = lt;

    return temp;
}
rbSec* rightrbs(rbSec* root)
{
    //rotates right of a subtree
    rbSec* temp = root -> left;
    rbSec* rt = temp -> right;

    temp -> right = root;
    root -> left = rt;

    return temp;
}
bool rob(rbSec* root)
{
    //to test if a node has what color
    if (root == NULL)
        return false;
    return (root -> color == true);
}
void changecolor(rbSec* fi, rbSec* si)
{
    bool temp = si -> color;
    si -> color = fi -> color;
    fi -> color = temp;
}

rbSec* insertrbs(rbSec* root, string name,int prc)
{
    //recursively find right place to insert
    if ( !root )
         return newrbs(name, prc);

    if (name < root -> itemName)
        root -> left = insertrbs(root->left, name, prc);

    else if (name > root -> itemName)
        root -> right = insertrbs(root -> right, name, prc);

    else
        return root;

    
    // case when right child is red and left childe is black
    // left rotate and change colors
    if (rob(root -> right) && !rob(root -> left))
    {
        root = leftrbs(root);
        changecolor( root -> left,root);
    }

    // case when left child is red and left childs left child  is red
    // right rotate and change colors
    if (rob(root -> left) && rob(root -> left -> left))
    {
        
        root = rightrbs(root);
        changecolor(root -> right, root);
    }

    // case when left child is red and right child  is red
    // opposite colors must be set
    if (rob(root -> left) && rob(root -> right))
    {

        
        root -> color = !root -> color;
        root -> left -> color = false;
        root -> right -> color = false;
    }
    return root;
}



class secNode{
//This node is for items
public:
    secNode* left;
    secNode* right;
    string itemName;
    int height;
    int price;
    //constructors
    secNode(){
        itemName = "";
        left = NULL;
        right = NULL;
        price = 0;
        height = 0;
    }
    secNode(string name, int prc, int hg = 1){
        itemName = name;
        price = prc;
        left = NULL;
        right = NULL;
        height = hg;
    }
};
class primNode{
//This node is for categories
public:
    primNode* left;
    primNode* right;
    secNode* link;
    string category;
    //constructors
    primNode(){
        left = NULL;
        right = NULL;
        link = NULL;
        category = "";
    }
    primNode(string ctg){
        left = NULL;
        right = NULL;
        link = NULL;
        category = ctg;
    }
    
};
//To create a new primary node with specific values
primNode* newNode(string ctg){
    primNode* temp = new primNode(ctg);
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
//To create a new secondart node with name and price attributes
secNode* newSec(string name, int prc){
    secNode* temp = new secNode(name, prc);
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

int max(int a, int b)
{
    if(a>b){
        return a;
    }else{
        return b;
    }
}
//Recursively find the height of balanced secondary(item) tree
int getHeight(secNode* root){
    if (root == NULL)
            return 0;
        return root->height;
}

secNode* leftRotate(secNode* root)
{
    
    secNode* temp = root->right;
    secNode* temp2 = temp->left;
  
    // Rotate to left
    temp->left = root;
    root->right = temp2;
  
    //New heights are set
    root->height = 1 + max(getHeight(root->left),getHeight(root->right));
    temp->height = 1 + max(getHeight(temp->left),getHeight(temp->right));
  
    return temp;
}
secNode* rightRotate(secNode* root)
{
    secNode* temp = root->left;
    secNode* temp2 = temp->right;
  
    // Rotate to right
    temp->right = root;
    root->left = temp2;
  
    //New heights are set
    root->height = 1 +  max(getHeight(root->left),getHeight(root->right));
    temp->height = 1 + max(getHeight(temp->left),getHeight(temp->right));
  
    return temp;
}
//getBal is a method to find the height difference between left and right subtree
int getBal(secNode* root)
{
    if (root == NULL){
        return 0;
    }
    return getHeight(root->left) - getHeight(root->right);
}
//This is a test to print all secondary nodes in inorder
void printallsec(secNode* root){
    if (root != NULL) {
          printallsec(root->left);
          cout<<root->itemName<<endl;
          printallsec(root->right);
       }
    
}
//This is a test to print all primary nodes in inorder
void printallprim(primNode* root){
    if (root != NULL) {
        printallprim(root->left);
    
        cout<<root->category<<" ";
        printallsec(root->link);
        printallprim(root->right);
    }
}

int heightSec(secNode* node)
{
    //Find the maximum of left and subtree heights
    if (node == NULL)
        return 0;
    else {
        
        int lheight = heightSec(node->left);
        int rheight = heightSec(node->right);
 
        
        return (1+max(lheight,rheight));
    }
}
void printSec(secNode* root, int level,ofstream& out1)
{
    //To write to file the secondary nodes with level order
    if (root == NULL)
        return;
    if (level == 1){
        out1<<'"' << root->itemName << '"' << ":" << '"'<<root->price << '"' << "," ;
    }
        
    else if (level > 1) {
        printSec(root->left, level - 1,out1);
        
        printSec(root->right, level - 1,out1);
    }
    
}
void printallSec1(secNode* root,ofstream& out1){
    int len = heightSec(root);
    //This is a function to help print the level order
    for (int i = 1; i <= len; ++i){
        out1 << '\t';
        printSec(root, i,out1);
        long pos = out1.tellp();
        out1.seekp(pos - 1);
        
        out1.write("", 1);
        
        out1 << endl;
    }
}
int heightPrim(primNode* node)
{
    //Like height method of secondary nodes
    if (node == NULL)
        return 0;
    else {
        
        int lheight = heightPrim(node->left);
        int rheight = heightPrim(node->right);
 
        
        return (1+max(lheight,rheight));
    }
}
void printCurrentLevel(primNode* root, int level, ofstream& out1)
{
    //return if node has no element
    if (root == NULL)
        return;
    if (level == 1){
        
        out1<<'"' << root->category << '"' << ":" ;
        if(root->link ==NULL){
            out1 << "{}" << endl;
        }else{
            out1 << endl;
            printallSec1(root->link,out1);
            
        }
        
    }
    //Recursively print the level order
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1,out1);
        printCurrentLevel(root->right, level - 1,out1);
    }
}

void printallprim1(primNode* root,ofstream& out1){
    int len = heightPrim(root);
    //Send the all levels to another function to print
    for (int i = 1; i <= len; ++i){
        printCurrentLevel(root, i,out1);
    }
}

primNode* insertPrim(primNode* root, string ctg){
    // To insert to right place it is considered as normal binary search tree
    if (root == NULL) {
        primNode* node = newNode(ctg);
        return node;
    }

    if (ctg<root->category) {
        root->left = insertPrim(root->left, ctg);
    }
    else if (ctg > root->category) {
        root->right = insertPrim(root->right, ctg);
    }

    return root;
        
}
secNode* insertSec(secNode* root, string name, int prc){
    //This elements must be according to both bst rules and balanced rules
    if (root == NULL) {
        secNode* node = newSec(name, prc);
        return node;
    }
    //Recursively find the left if name is less
    if (name<root->itemName) {
        root->left = insertSec(root->left, name, prc);
    }
    else if (name > root->itemName) {
        root->right = insertSec(root->right, name, prc);
    }else{
        //Found the correct position to insert
        return root;
    }
    //Calculate current heights of left and right subtree
    root->height = 1 + max(getHeight(root->left),getHeight(root->right));
    
    int bal = getBal(root);
    //Double rotate right and left
    if (bal < -1 && name < root->right->itemName)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }else if(bal > 1 && name > root->left->itemName){
        //Double rotate left and right
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }else if(bal > 1 && name < root->left->itemName){
        //Single right rotate
        return rightRotate(root);
    }else if(bal < -1 && name > root->right->itemName){
        //Single left rotate
        return leftRotate(root);
    }
    return root;
}
primNode* searchPrim(primNode* root, string ctg){
    if(root == NULL || root->category == ctg)
        return root;

    //Search the primary node recursively
    if(root->category < ctg)
        return searchPrim(root->right,ctg);

    
    return searchPrim(root->left,ctg);
}
secNode* minValueNode(secNode* node) {
  secNode* current = node;

  //Loop to find the minimum value node
  while (current && current->left != NULL)
    current = current->left;

  return current;
}
secNode* removeSec(secNode* root, string name){
    //Null item can not be removed
    if (root == NULL) return root;
    //Recursively delete the left if we are searching a less element
    if (name < root->itemName)
        root->left = removeSec(root->left, name);
    else if (name > root->itemName)
        root->right = removeSec(root->right, name);
    else {
        
        if (root->left == NULL) {
            secNode* temp = root->right;
            delete(root);
            return temp;
        } else if (root->right == NULL) {
            secNode* temp = root->left;
            delete(root);
            return temp;
        }
        secNode* temp = minValueNode(root->right);
        //Delete the min value node of nodes right
        
        root->itemName = temp->itemName;
        
        
        root->right = removeSec(root->right, temp->itemName);
    }
    if (root == NULL)
        return root;
    //This part is similar to balanced tree insertion part
    root->height = 1 + max(getHeight(root->left),getHeight(root->right));
      

    int bal = getBal(root);
    if (bal < -1 && getBal(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }else if(bal < -1 && getBal(root->right) <= 0){
        return leftRotate(root);
    }else if(bal > 1 && getBal(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }else if(bal > 1 && getBal(root->left) >= 0){
        return rightRotate(root);
    }
    return root;
}
secNode* searchSec(secNode* tree,string name ){
    //Search recursively the balanced tree
    if(tree == NULL || tree->itemName == name)
           return tree;

       
       if(tree->itemName < name)
           return searchSec(tree->right,name);

       
       return searchSec(tree->left,name);
}
int main(int argc, const char * argv[]) {
    //Opening input and output files
    ifstream infile(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);
    ofstream outfile2;
    outfile2.open(argv[3]);
    vector<string> commands;
    string line;
    //Takin input lines
    if (infile){
        while(getline(infile, line)){
            commands.push_back(line);
            
        }
    }
    primNode* root = NULL;
    // Main loop to execute all commands
    for(int i = 0; i < commands.size(); ++i){
        stringstream streaming(commands[i]);
        vector<string> lines;
        split(streaming, lines);
        string com = lines[0];
        
        
        
        if(com == "insert"){
            
            string ctg = lines[1];
            string name = lines[2];
            int prc = atoi(lines[3].c_str());
            //If the primary tree is found just insert the item if not found create primary tree
            primNode* tree = searchPrim(root, ctg);
            if(tree == NULL){
                root = insertPrim(root, ctg);
                tree = searchPrim(root, ctg);
                tree->link =  insertSec(tree->link, name, prc);
//                cout << tree->category;
            }else{
                tree->link = insertSec(tree->link, name, prc);
//                cout << tree->category;
            }
           
            
        }else if(com == "remove"){
            string ctg = lines[1];
            string name = lines[2];
            //Search primary category if found remove the item
            primNode* tree = searchPrim(root, ctg);
            tree->link = removeSec(tree->link, name);
            tree = searchPrim(root, ctg);
            
//            cout << "remove call" << endl;
           
            
        }else if(com == "printAllItems"){
            // printallprim command prints all primary and secondary nodes
            outfile << "command:printAllItems" << endl;
            outfile << "{" << endl;
            printallprim1(root,outfile);
            outfile << "}" << endl;
            
            outfile2 << "command:printAllItems" << endl;
            outfile2 << "{" << endl;
            printallprim1(root,outfile2);
            outfile2 << "}" << endl;
            

            
        }else if(com == "printAllItemsInCategory"){
            //This command prints only chosen category items
            string ctg = lines[1];
            primNode* tree = searchPrim(root, ctg);
            outfile << "command:printAllItemsInCategory" << '\t' << tree->category << endl;
            outfile << "{" << endl;
            outfile2 << "command:printAllItemsInCategory" << '\t' << tree->category << endl;
            outfile2 << "{" << endl;
            outfile<<'"' << tree->category << '"' << ":" ;
            outfile2<<'"' << tree->category << '"' << ":" ;
            if(tree->link ==NULL){
                outfile << "{}" << endl;
                outfile2 << "{}" << endl;
            }else{
                outfile << endl;
                outfile2 << endl;
                printallSec1(tree->link,outfile);
                printallSec1(tree->link,outfile2);
                
            }
            outfile << "}" << endl;
            outfile2 << "}" << endl;
            
            
            
        }else if(com == "printItem"){
            //This command prints only one item with price tag
            string ctg = lines[1];
            string name = lines[2];
            primNode* tree = searchPrim(root, ctg);
            outfile << "command:printItem" << '\t' << ctg << '\t' << name << endl;
            outfile2 << "command:printItem" << '\t' << ctg << '\t' << name << endl;
            outfile << "{" ;
            outfile2 << "{" ;
            if(tree){
                secNode* temp = searchSec(tree->link, name);
                if(temp == NULL){
                    outfile << "}" << endl;
                    outfile2 << "}" << endl;
                }else{
                    outfile << endl;
                    outfile<<'"' << tree->category << '"' << ":" << endl;
                    outfile<< '\t' << '"' <<temp->itemName <<'"' << ":" <<'"' << temp->price <<'"' << endl;
                    outfile << "}" << endl;
                    outfile2 << endl;
                    outfile2<<'"' << tree->category << '"' << ":" << endl;
                    outfile2<< '\t' << '"' <<temp->itemName <<'"' << ":" <<'"' << temp->price <<'"' << endl;
                    outfile2 << "}" << endl;
                }
            }else{
                outfile << "}" << endl;
                outfile2 << "}" << endl;
            }
            
            
            
            
        }else if(com == "find"){
            //This command similar to print item prints only one item
//            cout << " find call" << endl;
            string ctg = lines[1];
            string name = lines[2];
            primNode* tree = searchPrim(root, ctg);
            outfile << "command:printItem" << '\t' << ctg << '\t' << name << endl;
            outfile2 << "command:printItem" << '\t' << ctg << '\t' << name << endl;
            outfile << "{" ;
            outfile2 << "{" ;
            if(tree){
                secNode* temp = searchSec(tree->link, name);
                if(temp == NULL){
                    outfile << "}" << endl;
                    outfile2 << "}" << endl;
                }else{
                    outfile << endl;
                    outfile<<'"' << tree->category << '"' << ":" << endl;
                    outfile<< '\t' << '"' <<temp->itemName <<'"' << ":" <<'"' << temp->price <<'"' << endl;
                    outfile << "}" << endl;
                    outfile2 << endl;
                    outfile2<<'"' << tree->category << '"' << ":" << endl;
                    outfile2<< '\t' << '"' <<temp->itemName <<'"' << ":" <<'"' << temp->price <<'"' << endl;
                    outfile2 << "}" << endl;
                }
            }else{
                outfile << "}" << endl;
                outfile2 << "}" << endl;
            }
            
            
        }else if(com == "updateData"){
            //This command updates the price of an item
            string ctg = lines[1];
            string name = lines[2];
            int prc = atoi(lines[3].c_str());
            primNode* tree = searchPrim(root, ctg);
            secNode* temp = searchSec(tree->link, name);
            if(temp){
                temp->price = prc;
            }
            
        }
    }
    infile.close();
    return 0;
}
