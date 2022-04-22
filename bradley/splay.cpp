#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

class splay
{

public:
    struct node
    {
        pair<double,double> coordinate;
        double relative; //gets distance relative to an origin point, which makes it easy to determine relative locations
        node* left = NULL;
        node* right = NULL;
    };

    node* root; //most functions use what the current root is to funciton
    node* create(pair<double,double> c) //O(1)
    {
        node* cur = new node;
        double pyth = pow(c.first, 2)+ pow(c.second,2);//used to calculate relative positions
        cur->relative = pow(pyth, .5);//calculated relative positions
        return cur;
    }
    node* zig(node* cur) //O(1)
    {
        node* swap = cur->left;
        cur->left= swap->right;
        swap->right = cur;
        return swap;
    }
    node* zag(node* cur)//O(1)
    {
        node* swap = cur->right;
        cur->right = swap->left;
        swap->left= cur;
        return swap;
    }
    node* insert(pair<double,double> c) //O(logn), top->down splaying method
    {
        static node* cur = create(c);
        if (root == NULL)
        {
            root = cur;
            delete(cur);
            return root;
        }
        root = splayFunction(cur, root);
        if (cur->relative < root->relative)
        {
            cur->left= root->left;
            cur->right = root;
            root->left= NULL;
            root = cur;
        }
        else if (cur->relative > root->relative)
        {
            cur->right = root->right;
            cur->left= root;
            root->right = NULL;
            root = cur;
        }
        else
            return root;
        delete(cur);
        return root;
    }
    node* splayFunction(node* loc, node* root) //O(logn)
    {
        node cur; //this will be the "current" node where the splays are based around
        node* curL = &cur;
        node* curR = &cur;
        while (1 != 0) //loop is broken after the tree is correctly splayed, did not result in infinite loop in testing
        {
            if (loc->relative < root->relative)
            {
                if (root->left == NULL)
                    break;
                if (loc->relative< root->left->relative)
                {
                    root = zig(root);
                    if (!root->left)
                        break;
                }
                curR->left= root;
                curR = curR->left;
                root = root->left;
                curR->left= NULL;
            }
            else if (loc->relative> root->relative)
            {
                if (root->right== NULL)
                    break;
                if (loc->relative > root->right->relative)
                {
                    root = zag(root);
                    if (!root->right)
                        break;
                }
                curL->right= root;
                curL = curL->right;
                root = root->right;
                curL->right = NULL;
            }
            else
                break;
        }
        curL->right = root->left;
        curR->left= root->right;
        root->left= cur.right;
        root->right = cur.left;
        return root;
    }



};
