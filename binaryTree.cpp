/********************************************************************************
  * Rachel Coughanour                                                            *
  * CS 372                                                                       *
  * Binary Tree Program                                                          *
  *                                                                              *
  * Description: This program performs many operations on a binary tree          *
  ********************************************************************************/ 
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

ifstream infile;
ofstream outfile;

//Functions 
class tree
{
private:
    struct node
{
    int num;
    int count;
    node *lChild;
    node *rChild;
};

 newNode()  //function to create a new node
 {
    node *temp;
    temp->lChild = NULL;
    temp->rChild = NULL;
    temp->num = 0;
 }
 node *root;
 
  public:
  tree()
   {
       root = NULL;
   }
  
  void insert(node *cp, int target)  //inserting numbers into the tree
  {
      
      node *p;
      p = NULL;
      
      while(cp != NULL)
      {
          p = cp;
          
          if(target < cp->num)
          {
              cp = cp->lChild;
          }
          
          else
          {
              cp = cp->rChild;
          }
      }
      
      cp = new node();
      cp->num = target;
      cp->count = 1;
      
      if(p == NULL)
      {
          root = cp;
      }
      
      if(p != NULL)
      {
          if(target < p->num)
          {
              p->lChild = cp;
          }
          
          else
          {
              p->rChild = cp;
          }
      }
  }
  
   void insert(int target)
   {
       insert(root, target);
   };
  
 bool ifNodeExists(struct node* root, int key) //bool function to search if a value is already in the tree 
{ 
     bool answer;
     bool answer2;
     
    if (root == NULL) 
        return false; 
  
    if (root->num == key) 
        return true; 
  

    answer = ifNodeExists(root->lChild, key); 
  
    if(answer) //if node is found, return true 
    {
       return true; 
    }
   
    //check right side of tree 
   answer2 = ifNodeExists(root->rChild, key); 
  
    return answer2; 
} 
  
 bool ifNodeExists(int key)
 {
     ifNodeExists(root, key);
 };
  
   
  int sum(node *root)  //function to find the sum of values in a tree
  {
     if(root == NULL)
     {
         return 0;
     }
     
     return (root->num + sum(root->lChild) + sum(root->rChild));
  }
  
    int sum()
  {
    sum(root);
  };
  
  int countNumNodes(node *root)  //function to count the number of nodes 
  {
     int c =  1;             
    if (root == NULL)
        return 0;
    else
    {
        c += countNumNodes(root->lChild);
        c += countNumNodes(root->rChild);
        return c;
    }
  }
  
  int countNumNodes()
  {
      countNumNodes(root);
  };
  
  
  int getLeafCount(node *root)   //return the number of leaf nodes
  {  
     if(root == NULL)
     {
        return 0;    
     } 
     
    if(root->lChild == NULL && root->rChild == NULL) 
    {
      return 1;      
    } 
     
    else
        return getLeafCount(root->lChild) + getLeafCount(root->rChild);  
   }
  
    int getLeafCount()
  {
     getLeafCount(root);
  };
  
  int oneChildCount(node *root) //counts the number of nodes with only 1 child
  { 
    if (root == NULL) 
       return 0; 
  
    int count = 0; 
    if  ((root->lChild == NULL && root->rChild != NULL) || (root->lChild != NULL && root->rChild == NULL)) 
       count++; 
  
    count += (oneChildCount(root->lChild) + oneChildCount(root->rChild)); 
    return count; 
  } 
  
    int oneChildCount()
  {
     oneChildCount(root);
  };
 
  
  void find(node *root, int level, int &maxLevel, int &deepest) //finds the deepest node in the tree 
 { 
    if (root != NULL) 
   { 
        find(root->lChild, ++level, maxLevel, deepest); 
  
        if (level > maxLevel) 
        { 
            deepest = root->num; 
            maxLevel = level; 
        } 
  
        find(root->rChild, level, maxLevel, deepest); 
    } 
} 
  

int deepestNode(node *root)   //returns the value of the deepest node in the tree
{ 
    int deepest = -1; 
    int maxLevel = -1; 
  
    find(root, 0, maxLevel, deepest); 
    return deepest; 
} 

  int deepestNode()
  {
     deepestNode(root);
  };
  

node* leafDelete(struct node* root) //deletes all the leaves in the tree 
                                    //with a sum of digits < 9
{ 
    if (root == NULL) 
        return NULL; 
    if (root->lChild == NULL && root->rChild == NULL) 
    { 
        if(sumDigits(root->num) < 9)
        {
             delete(root); 
             return NULL; 
        }
       
    } 
  
    root->lChild = leafDelete(root->lChild); 
    root->rChild = leafDelete(root->rChild); 
  
    return root; 
} 

 node* leafDelete()
  {
     leafDelete(root);
  };
  
  
  void printInorder(int& count)
  {
    printInorder(root, count);
  };
  
  void printInorder(node *root, int& count)  //function to print the tree in order
  {  
     if(root == NULL)
     {
         return;
     }
     
     if(count < 20)
     {
         count++;
         printInorder(root->lChild, count);
         outfile<<root->num<<" ";
         printInorder(root->rChild, count);
     }
  }
  
    void printPreorder(int& count1)
   {
       printPreorder(root, count1);
   };

void printPreorder(node *root, int& count1) //function to print the tree in preorder 
  {
     if (root==NULL)
       {
           return;
       }
       
     if(count1 < 20)
       {
           count1++;
           outfile<<root->num<<" ";
           printPreorder(root->lChild, count1);
           printPreorder(root->rChild, count1);
       }
  }


 void printPostorder(int &count)
   {
       printPostorder(root, count);
   };
   
void printPostorder(node *root, int& count)  //function to print the tree in postorder
  {
      if (root == NULL)
        {
            return;
        }
        
      if(count < 20)
        {
            count++;
            printPostorder(root->lChild, count);
            printPostorder(root->rChild, count);
            outfile<<root->num<<" ";
        }
  }

int sumDigits(int n)  //recursive function to find the sum of a digit
{
    if(n == 0)
    {
        return 0;
    }
    
    return (n % 10 + sumDigits(n / 10));
}
};
 
   
void fileHeader()  //header for top of file output 
{
    outfile<<"**********************************"<<endl;
    outfile<<"Rachel Coughanour CS 372"<<endl;
    outfile<<"Output file for Binary Tree Program"<<endl;
    outfile<<"**********************************"<<endl<<endl;
}




int main()
{
   infile.open("C://data//input//treeData.txt");
   outfile.open("C:\\data\\treeResults.txt");
   
    if(!infile)
   {
        cout<<"File cannot be open. Please try again.";
        return 0;
    }
    
    tree root;
    int val;        //the value to be read into the node
    int printCount = 0;  //the number of nodes to print 
    int treeSum;   //sum of the nodes in the tree 
    float avg;     //average of the nodes in the tree 
    int leafCount;  //the number of leaves in the tree 
    int nodeDel;    //the node to be deleted 
    int deepest;    //the deepest node in the tree
    int oneChild;   //number of nodes with only 1 child 
    int numNodes;  //the number of nodes in the binary tree 
    int numDup = 0;   //the number of duplicates read in 
    
    fileHeader();
    
    //while reading the values from a file, check if it is a duplicate
   while(infile)
   {
     infile>>val;
     
     //if it is, bump the duplicate counter and skip the number
      if(root.ifNodeExists(val))
      {
         numDup++;
         continue;
      }
    
     //else, insert it into the tree 
      else
      {
        root.insert(val); 
      }
   }  
    
    //printing the tree inorder
    outfile<<"Binary Tree printed In-order (first 20 values)"<<endl;
    root.printInorder(printCount);
    outfile<<endl<<endl;
    printCount = 0;  //reset the print count
    
    //printing the tree preorder 
    outfile<<"Binary tree printed in pre-order (first 20 values)"<<endl;
    root.printPreorder(printCount);
    outfile<<endl<<endl;
    printCount = 0; //reset the print count 
    
    //printing the tree in postorder
    outfile<<"Binary Tree in post-order (first 20 values)"<<endl;
    root.printPostorder(printCount);
    outfile<<endl<<endl;
    printCount = 0; //reset the print count
    
    //finding the number of nodes
    numNodes = root.countNumNodes();
    outfile<<"The number of nodes in the tree is: "<<numNodes<<endl<<endl;
    
     //printing the sum and average of the values in the tree
     outfile<<"The sum and average of the binary tree: "<<endl;
     treeSum = root.sum();
     avg = treeSum/numNodes;
     outfile<<"Sum: "<<treeSum<<" Average: "<<fixed<<setprecision(1)<<avg<<endl<<endl;
    
    //find the number of duplicates read in
    outfile<<"The number of duplicates in the tree was: "<<numDup<<endl<<endl;
    
    //find the number of leaves in the tree
    leafCount = root.getLeafCount();
    outfile<<"The number of leaves in the tree is: "<<leafCount<<endl<<endl;
    
    //find the number of nodes that have only (1) child
    oneChild = root.oneChildCount();
    outfile<<"The number of nodes with only 1 child: "<<oneChild<<endl<<endl;
    
    //find the deepest leaf in the tree
    deepest = root.deepestNode();
    outfile<<"The deepest leaf in the tree: "<<deepest<<endl<<endl;
    
    //delete nodes where the sum of the digits is <9
    root.leafDelete();
    outfile<<"Deleting nodes where the sum of the digits is < 9..."<<endl<<endl;
    
    ////print the tree inorder again
    outfile<<"The binary tree In-order after deletion (first 20 values): "<<endl;
    root.printInorder(printCount);
    outfile<<endl<<endl;
    
    //print the number of nodes
    numNodes = 0;  //reset variable
    numNodes = root.countNumNodes();
    outfile<<"The number of nodes in the tree after deletion is: "<<numNodes<<endl<<endl;
    
    //find the sum and average of the tree again
     outfile<<"The sum and average of the tree after deletion"<<endl;
     treeSum = root.sum();
     avg = treeSum/numNodes;
     outfile<<"Sum: "<<treeSum<<" Average: "<<fixed<<setprecision(1)<<avg<<endl;
    
infile.close();
outfile.close();
return 0;
}

