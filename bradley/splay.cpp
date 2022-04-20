#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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
	vector<pair<double, double>> guess()
	{
		if (root == nullptr) return;
		vector<pair<double, double>> ans;
		ans.push_back(root->coordinates);
		node* r = root->right;
		node* l = root->left;
		for (int i = 0; i < 10; i++)
		{
			if (r != nullptr)
			{
				for (int j = 0; j < r->frequency; j++)
				{
					ans.push_back(r->coordinates);
				}
				if (r->left != nullptr) ans.push_back(r->left->coordinates);
				if (r->right != nullptr) r = r->right;
				else r = r->left;
			}
			if (l != nullptr)
			{
				for (int j = 0; j < l->frequency; j++)
				{
					ans.push_back(l->coordinates);
				}
				if (l->left != nullptr) ans.push_back(l->left->coordinates);
				if (l->right != nullptr) l = l->right;
				else l = l->left;
			}
		}
		return ans;
		
	}
};

//think i delete old node when found, put it on top, and adjust nodes around old location
//obtains a tweet, compares contents to word list, and then calculates (figure out how to comapre simmilar words, like with 1/2 letters off)

int main ()
{
	
	return 0;
}