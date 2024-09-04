#include <iostream>
#include <string>
#include <queue>
using namespace std;

template<class T>
struct binTreeNode
{
	T data;
	int level = 0, pos = 0;
	binTreeNode<T>* left, * right;
	binTreeNode() :left(NULL), right(NULL) {}
	binTreeNode(T x, int p = 0, binTreeNode<T>* l = NULL, binTreeNode<T>* r = NULL) :data(x), pos(p), left(l), right(r) {}
};

template<class T>
class binTree
{
private:
	binTreeNode<T>* root;
	binTreeNode<T>* need;	//需要创建子树的节点
	bool back = false;		//判断需要结束遍历
	int size = 0, count = 0;
	bool isFirst = true;
public:
	// === 构造与析构 === //
	binTree() :root(NULL), need(NULL) {}
	~binTree() { Destroy(root); }

	// ====== 创建 ====== //
	void Create(T e, int p)
	{
		if (root)
		{
			int p_parent = p / 2;
			FindNode(root, p_parent);
			back = false;
			if (need->left == NULL)
				need->left = new binTreeNode<T>(e, p);
			else // need->right == NULL
				need->right = new binTreeNode<T>(e, p);
		}
		else root = new binTreeNode<T>(e, p);
		size++;
	}
	binTreeNode<T>* Create_Pre_In(string pre, string in)
	{
		if (pre.length() == 0 || in.length() == 0) return nullptr;
		binTreeNode<T>* t;
		t = new binTreeNode<T>(pre[0]);
		size++;
		if (!root) root = t;
		int left_size = 0;
		for (int i = 0; i < in.length(); i++)
			if (in[i] == pre[0])
			{
				left_size = i;
				break;
			}
		string L_in, R_in, L_pre, R_pre;

		L_in.assign(in, 0, left_size);

		R_in.assign(in, left_size + 1, in.length() - left_size - 1);

		L_pre.assign(pre, 1, left_size);

		R_pre.assign(pre, left_size + 1, pre.length() - left_size - 1);

		t->left = Create_Pre_In(L_pre, L_in);
		t->right = Create_Pre_In(R_pre, R_in);

		return t;
	}
	void SetPos() { SetPos(root); }
	void SetPos(binTreeNode<T>* t)
	{
		if (t) t->pos = 1;
		else return;
		if (t->left || t->right)
		{
			queue<binTreeNode<T>*> q;
			while (t)
			{
				if (t->left)
				{
					t->left->pos = t->pos * 2;
					q.push(t->left);
				}
				if (t->right)
				{
					t->right->pos = t->pos * 2 + 1;
					q.push(t->right);
				}
				t = q.front();
				q.pop();
				if (q.empty()) break;
			}
		}
		else return;
	}

	// ====== 遍历 ====== //
	void PreOrder(void(*visit)(binTreeNode<T>*), binTreeNode<T>* t)
	{
		if (t)
		{
			visit(t);
			PreOrder(visit, t->left);
			PreOrder(visit, t->right);
		}
	}
	void PreOrder() { PreOrder(root); }
	void PreOrder(binTreeNode<T>* t)
	{
		if (t)
		{
			if (isFirst)
			{
				cout << t->data;
				count++;
				isFirst = false;
			}
			else
			{
				cout << "," << t->data;
				count++;
			}
			PreOrder(t->left);
			PreOrder(t->right);
		}
		if (count == size)
		{
			isFirst = true;
			count = 0;
		}
	}
	void InOrder() { InOrder(root); }
	void InOrder(binTreeNode<T>* t)
	{
		if (t)
		{
			InOrder(t->left);
			if (isFirst)
			{
				cout << t->data;
				count++;
				isFirst = false;
			}
			else
			{
				cout << "," << t->data;
				count++;
			}
			InOrder(t->right);
		}
		if (count == size)
		{
			isFirst = true;
			count = 0;
		}
	}
	void PostOrder() { PostOrder(root); }
	void PostOrder(binTreeNode<T>* t)
	{
		if (t)
		{
			PostOrder(t->left);
			PostOrder(t->right);
			if (isFirst)
			{
				cout << t->data;
				count++;
				isFirst = false;
			}
			else
			{
				cout << "," << t->data;
				count++;
			}
		}
		if (count == size)
		{
			isFirst = true;
			count = 0;
		}
	}
	void LevelOrder() { LevelOrder(root); }
	void LevelOrder(binTreeNode<T>* t)
	{
		if (t->left || t->right)
		{
			queue<binTreeNode<T>*> q;
			while (t)
			{
				if (isFirst)
				{
					cout << t->data;
					isFirst = false;
				}
				else cout << "," << t->data;
				if (t->left) q.push(t->left);
				if (t->right) q.push(t->right);
				t = q.front();
				q.pop();
				if (q.empty())
				{
					cout << "," << t->data;
					break;
				}
			}
			isFirst = true;
		}
		else cout << t->data;
	}

	// ==== 获取结点 ==== //
	binTreeNode<T>* getRoot()const { return root; }
	binTreeNode<T>* Parent(binTreeNode<T>* current)
	{
		return (root == NULL || root == current) ? NULL : Parent(root, current);
	}
	binTreeNode<T>* left(binTreeNode<T>* current)
	{
		return (current != NULL) ? current->left : NULL;
	}
	binTreeNode<T>* right(binTreeNode<T>* current)
	{
		return (current != NULL) ? current->right : NULL;
	}
	void FindNode(binTreeNode<T>* t, int p)
	{
		if (back) return;
		if (t)
		{
			if (t->pos == p)
			{
				need = t;
				back = true;
				return;
			}
			else
			{
				FindNode(t->left, p);
				FindNode(t->right, p);
			}
		} 
	}
	
	// ==== 成员函数 ==== //
	void Destroy() { Destroy(root); }
	int Size() { Size(root); }
	int Size(binTreeNode<T>* t)
	{
		if (t == NULL) return 0;
		return 1 + Size(t->left) + Size(t->right);
	}
	void GetSize() { cout << size; }
	void GetHighth()
	{
		FindNode(root, size);
		cout << need->level;
	}
	bool Empty() { return(root == NULL) ? true : false; }
	void Destroy(binTreeNode<T>*& t)
	{
		if (t)
		{
			Destroy(t->left);
			Destroy(t->right);
			delete t;
			t = NULL;
		}
	}
	void Print()
	{
		cout << "[" << root->pos << "]" << root->data << "(" << root->level << ")";
		for (int i = 2; i < size + 2; i++)
		{
			FindNode(root, i);
			back = false;
			if (need) cout << ", [" << need->pos << "]" << need->data << "(" << need->level << ")";
			need = NULL;
		}
	}
	void OutputLeaves(); 
	void SwapChild();
	void SetLevel();

};

template<class T>
void binTree<T>::OutputLeaves()
{
	bool not_first = false;	//判断第一次输入
	for (int p = 1; p <= size; p++)
	{
		FindNode(root, p);
		back = false;
		if (need->left == NULL && need->right == NULL)
		{
			if (not_first)
				cout << "," << need->data;
			else
			{
				cout << need->data;
				not_first = true;
			}
		}
	}
	
}
template<class T>
void binTree<T>::SwapChild()
{
	binTreeNode<T>* temp;
	for (int p = 1; p <= size; p++)
	{
		FindNode(root, p);
		back = false;
		if (need->left) need->left->pos++;
		if (need->right) need->right->pos--;
		temp = need->left;
		need->left = need->right;
		need->right = temp;
	}
}
template<class T>
void binTree<T>::SetLevel()
{
	root->level = 1;
	for (int p = 1; p <= size; p++)
	{
		FindNode(root, p);
		back = false;
		if (need->left) need->left->level = need->level + 1;
		if (need->right) need->right->level = need->level + 1;
	}
}

int main()
{
	// binTree<char> bi;
	// char e;
	// int p = 1;
	// cout << "Input" << endl;
	// cin >> e;
	// while (e != '#')
	// {
	// 	bi.Create(e, p);
	// 	cin >> e;
	// 	p++;
	// }
	// cout << "Output" << endl;
	// cout << "Initial: ";
	// bi.Print();
	// cout << "\nLeaves: ";
	// bi.OutputLeaves();
	// cout << "\nSwap Childs: ";
	// bi.SwapChild();
	// bi.Print();
	// cout << "\nSet Level: ";
	// bi.SetLevel();
	// bi.Print();
	// cout << endl;

	binTree<char> bi1, bi2;
	string str, pre, in;
	// int p = 1, i;
	// cout << "Input1" << endl;
	// cin >> str;
	// for (i = 0; i < str.length(); i++)
	// {
	// 	bi1.Create(str[i], p);
	// 	p++;
	// }
	// cout << "Output1" << endl;
	// bi1.PreOrder(); cout << "\n";
	// bi1.InOrder(); cout << "\n";
	// bi1.PostOrder(); cout << "\n";
	// bi1.GetSize(); cout << "\n";
	// bi1.setLevel();
	// bi1.GetHighth();
	cout << "\nInput2" << endl;
	cin >> pre;
	cin >> in;
	bi2.Create_Pre_In(pre, in);
	cout << "Output2" << endl;
	// bi2.PostOrder(); cout << "\n";
	// bi2.LevelOrder();
	bi2.SetPos();
	bi2.SetLevel();
	bi2.Print();

	cout << "\nEnd" << endl;
	
	return 0;
}
