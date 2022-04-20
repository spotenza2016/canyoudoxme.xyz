#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class splay
{
private:
	struct node {
		pair<double, double> coordinates;
		string name;
		int frequency;
		node* left;
		node* right;
		node* parent;
		node* prev;
	};

public:
	
	static node* root;
	node* getRoot()
	{
		return root;
	}
	node* find(string s, node* n)
	{
		if (n == nullptr)
		{
			return 0;
		}
		if (n->name == s) return n;
		node* ans =find(s, n->left);
		ans =find(s, n->right);
		return ans;
	}
	void splayFunction(node* n)
	{
		node* temp = n->parent;
		if (n->parent->left = n) //zig, single right
		{
			n->right->parent = n->parent;
			n->parent->left = n->right;
			n->right = n->parent;
			n->parent = n->parent->parent;
			temp->parent = n;
		}
		else //zag, single left
		{
			n->left->parent = n->parent;
			n->parent->right = n->left;
			n->left = n->parent;
			n->parent = n->parent->parent;
			temp->parent = n;
		}
		if (temp != root) splayFunction(n);
		else root = n;

		
	}
	void insert(node* n) // splay tree should grab the nodes nearby since it should theoretically have accessed nodes  be close to eachother if in same area
	{
		//default to nodes on the right having higher numbers (count)
		if (root->name == "N/A") root = n;
		node* found = find(n->name, root); //make sure to delete lol
		if (found == nullptr)//inserts on top
		{
			node* move = root;
			while (move != nullptr) //here maybe do coordinates to get distances and scale them this way
			{
				move->prev = move;
				n->prev = move->prev;
				if (move->right != nullptr && move->left != nullptr)move = move->right;
				else if (move->right != nullptr) move = move->left;
				else move = move->right;

			}
			splayFunction(n);
			//splayFunction here
		}
		else
		{
			found->frequency++;
			delete(n);
			splayFunction(found);
		}
	}
};

//think i delete old node when found, put it on top, and adjust nodes around old location
//obtains a tweet, compares contents to word list, and then calculates (figure out how to comapre simmilar words, like with 1/2 letters off)

int main ()
{
	
	return 0;
}