#include <iostream>
using namespace std;
int const RED = 1;
int const BLACK = 2;
struct Interval {
      int start;
      int end;
      Interval() : start(0), end(0) {}
      Interval(int s, int e) : start(s), end(e) {}
  };
class RedBlackTree {
public:
    struct Node{
        int low;
        int high;
        Node *left, *right, *parent;
        int color;
        int  maxi;
        Node (int k, int v){
            low = k;
            high = v;
            left = right = parent = NULL;
            color = RED;
             maxi=0;
        }
        
        Node (){
            left = right = parent = NULL;
            color = BLACK;
            maxi=0;
        }
        
    } *root, *x, *y, *now;
    
    Node *NIL;
    
    RedBlackTree (){
        NIL = new Node();
        root = NIL;
    }
    
    ~RedBlackTree(){
        clear();
        delete (NIL);
    }
    
    void insert (int low, int high){
        now = new Node (low, high);
        now->left = now->right = now->parent = NIL;
        
        x = root;
        y = NIL;
        
        while (x!=NIL){
            y = x;
            if (now->low < x->low){
                   
                x = x->left;
            }
            else if (now->low > x->low) {
      
                x = x->right;
            }
            else{
                x->high = high;

                return ;
            }
        }
        
        if (y==NIL){
            root = now;
            root-> maxi= now->high;
        }
        else if (now->low <  y->low){
                y->left = now;
                now-> maxi=now->high;
                if(now-> maxi>y-> maxi)
                 y-> maxi=now-> maxi;
        }
        else{
            y->right = now;
            now-> maxi=now->high;
             if(now-> maxi>y-> maxi)
                 y-> maxi=now-> maxi;
        }
        
        
        now->parent = y;
        insert_fix(now);
    }
    
    void print ()   // print the interval tree 
    {
        print (root);
        cout<<endl;
    }
    
    void print (Node *n){
        if (n == NIL)return;
        print (n->left);

        cout<<n->low<<" "<<n->high<<" "<<n->color<<" "<<n->maxi<<endl;


        print (n->right);
    }
    
    void clear()
    {
        clear(root);
        root = NIL;
    }
    
    void clear (Node *n){
        if (n == NIL)return;
        clear (n->left);
        clear (n->right);
        delete (n);
    }
    
     void search (int l ,int h ){
        x = root;
        
        while (x!=NIL)
        {
            if(x->low<=h&& l<=x->high)
               {
                 cout<<"Overlaps with"<<x->low<<","<<x->high<<endl;
                 return;
                 
               }
            if (x->left!=NIL && x->left->maxi>=l){
                x = x->left;
            }
            else {
                x = x->right;
            }
            
        }
          if(x==NIL)
          cout<<"No overlap";
        
    }
    
    void left_rotate(Node *x){
        //make y
        y = x->right;
        
        //connect x->right to b
        x->right = y->left;
        if (x->right!=NIL){
            x->right->parent = x;
        }
        
        //connect y to parent's x
        y->parent = x->parent;
        if (x->parent == NIL){
            root = y;
        }
        else if (x->parent->left == x){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
        
        //connect y to x
        y->left = x;
        x->parent = y;
          if(x->right==NIL)
            x->right-> maxi=0;
          if(x->left==NIL)
            x->left-> maxi=0;
            x-> maxi= max(x->high, max(x->right-> maxi,x->left-> maxi));
          if(x-> maxi>y-> maxi)
            y-> maxi=x-> maxi;

    }
    
    // copy from left_rotate but change x to y, left to right and vice versa
    void right_rotate(Node *y){
        x = y->left;
        
        y->left = x->right;
        if (y->left!=NIL){
            y->left->parent = y;
        }
        
        x->parent = y->parent;
        if (y->parent == NIL){
            root = x;
        }
        else if (y->parent->left == y){
            y->parent->left = x;
        }
        else{
            y->parent->right = x;
        }
        
        x->right = y;
        y->parent = x;
        if(y->right==NIL)
            y->right-> maxi=0;
          if(y->left==NIL)
            y->left-> maxi=0;
            y-> maxi= max(y->high, max(y->right-> maxi,y->left-> maxi));
          if(x-> maxi<y-> maxi)
            x-> maxi=y-> maxi;
    }
    
    void insert_fix(Node *x){
        while (x->parent->color == RED){
            if (x->parent->parent->left == x->parent){
                y = x->parent->parent->right;
                if (y->color == RED){
                    y->color = BLACK;
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                }else{
                    if (x->parent->right == x){
                        x = x->parent;
                        left_rotate(x);
                    }
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    right_rotate(x->parent->parent);
                }
            }
            else{
                y = x->parent->parent->left;
                if (y->color == RED){
                    y->color = BLACK;
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                }else{
                    if (x->parent->left == x){
                        x = x->parent;
                        right_rotate(x);
                    }
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    left_rotate(x->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    
    int depth(){
        return depth(root);
    }
    
    int depth (Node *n){
        if (n==NIL)return 0;
        return 1 +  max(depth(n->left), depth(n->right));
    }
};

int main (){

    
    Interval ints[6] = {{15, 20}, {10, 30}, {17, 19},
        {5, 20}, {12, 15}, {30, 40}};
    
    RedBlackTree  rbt;
    for(int i=0; i<6; i++)
    rbt.insert(ints[i].start,ints[i].end);
   
    
    rbt.print();
    rbt.search(5 ,6);
    
    cout<<rbt.depth()<<endl;
    cin.get();
    return 0;
}
//hbhbhbhb;