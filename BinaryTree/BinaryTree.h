#pragma once
#include <stack>
#include <queue>
#include <list>
#include <assert.h>

template<class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;

	BinaryTreeNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}

	BinaryTree(const T* a, size_t size, const T& invalid)
	{
		size_t index = 0;
		_root = _CreateTree(a, size, index, invalid);
	}

	~BinaryTree()
	{
		_DestroyTree(_root);
		_root = NULL;
	}

	BinaryTree(const BinaryTree& t)
	{
		_root = _CopyTree(t._root);
	}

	//赋值运算符重载的传统写法
	/*BinaryTree<T>& operator=(const BinaryTree& t)
	{
		if (*this != t)
		{
			_DestroyTree(_root);
			_root = _CopyTree(t._root);
		}

		return *this;
	}*/

	//赋值运算符重载的现代写法
	BinaryTree<T>& operator=(const BinaryTree<T> t)
	{
		swap(_root, t._root);

		return *this;
	}

	/***********************************遍历二叉树********************************************/
public:
	//前序遍历
	void PreOrder()
	{
		_PreOrder(_root);
	}

	//中序遍历
	void InOrder()
	{
		_InOrder(_root);
	}

	//后序遍历
	void PostOrder()
	{
		_PostOrder(_root);
	}

	//层序遍历
	void LevelOrder()
	{
		if (_root == NULL)
			return;

		queue<Node*> q;
		q.push(_root);

		while (!q.empty())
		{
			Node* front = q.front();
			q.pop();
			cout<<front->_data<<" ";

			if (front->_left)
			{
				q.push(front->_left);
			}

			if (front->_right)
			{
				q.push(front->_right);
			}
		}
	}

	//非递归前序遍历
	void PreOrder_NonR()
	{
		if (_root == NULL)
			return;

		stack<Node*> s;
		s.push(_root);

		while (!s.empty())
		{
			Node* top = s.top();
			s.pop();
			cout<<top->_data<<" ";
			
			if (top->_right)
				s.push(top->_right);
			
			if (top->_left)
				s.push(top->_left);
		}
	}

	//非递归中序遍历
	void InOrder_NonR()
	{
		if (_root == NULL)
			return;

		stack<Node*> s;
		s.push(_root);
		Node* cur = _root;

		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			if (!s.empty())
			{
				Node* top = s.top();
				cout<<top->_data<<" ";
				s.pop();

				cur = top->_right;
			}
		}
	}

	//非递归后序遍历
	void PostOrder_NonR()
	{
		if (_root == NULL)
			return;

		stack<Node*> s;
		Node* cur = _root;
		Node* pre = NULL;

		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();

			if (top->_right == NULL || top->_right == pre)
			{
				cout<<top->_data<<" ";
				pre = top;
				s.pop();
			}
			else
			{
				cur = top->_right;
			}
		}
	}

	/***********************************节点数、深度、叶子节点数、第K层节点数*************************************/
public:
	//节点数
	size_t Size()
	{
		size_t size = 0;
		return _Size(_root);
		//return size;
	}

	//深度
	size_t Depth()
	{
		return _Depth(_root);
	}
	
	//叶子节点数
	size_t LeafSize()
	{
		size_t leafSize = 0;
		_LeafSize(_root, leafSize);
		return leafSize;
	}

	//第K层节点数
	size_t GetKlevel(const size_t& k)
	{
		return _GetKLevel(_root, k);
	}


protected:
	//创建树
	Node* _CreateTree(const T* a, size_t size, size_t& index, const T& invalid)
	{
		Node* root = NULL;

		if (index < size && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _CreateTree(a, size, ++index, invalid);
			root->_right = _CreateTree(a, size, ++index, invalid);
		}

		return root;
	}

	//销毁树
	void _DestroyTree(Node* root)
	{
		if (root == NULL)
			return;

		if (root->_left == NULL && root->_right == NULL)
		{
			delete root;
			root = NULL;
			return;
		}

		_DestroyTree(root->_left);
		_DestroyTree(root->_right);
		
		delete root;
	}

	//拷贝树
	Node* _CopyTree(Node* root)
	{
		if (root == NULL)
			return NULL;

		Node* newRoot = new Node(root->_data);
		newRoot->_left = _CopyTree(root->_left);
		newRoot->_right = _CopyTree(root->_right);

		return newRoot;
	}

	/************************************************************************/

	//前序遍历
	void _PreOrder(Node* root)
	{
		if (root == NULL)
			return;

		std::cout<<root->_data<<" ";

		_PreOrder(root->_left);
		_PreOrder(root->_right);
	}

	//中序遍历
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);

		std::cout<<root->_data<<" ";

		_InOrder(root->_right);
	}

	//后序遍历
	void _PostOrder(Node* root)
	{
		if (root == NULL)
			return;

		_PostOrder(root->_left);
		_PostOrder(root->_right);

		std::cout<<root->_data<<" ";
	}

	/************************************************************************/

	void _LeafSize(Node* root, size_t& leafSize)
	{
		if (root == NULL)
		{
			return;
		}

		if (root->_left == NULL && root->_right == NULL)
		{
			++leafSize;
			return;
		}

		_LeafSize(root->_left, leafSize);
		_LeafSize(root->_right, leafSize);
	}

protected:
	//节点数-> 左子树节点数 + 右子树节点数
	size_t _Size(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		return _Size(root->_left) + _Size(root->_right) + 1;
	}

	/*void _Size(Node* root, size_t& size)
	{
		if (root == NULL)
			return;

		++size;

		_Size(root->_left, size);
		_Size(root->_right, size);
	}*/

	//深度
	size_t _Depth(Node* root)
	{
		if (root == NULL)
			return 0;

		size_t leftDepth = _Depth(root->_left);
		size_t rightDepth = _Depth(root->_right);

		return leftDepth > rightDepth ? (leftDepth+1) : (rightDepth+1);
	}

	//第K层节点数
	size_t _GetKValue(Node* root, size_t& k)
	{
		assert(k > 0);

		if (root == NULL)
		{
			return 0;
		}

		if (k ==1)
		{
			return 1;
		}

		return _GetKValue(root->_left, k-1) + _GetKValue(root, k-1);
	}

protected:
	Node* _root;
};

void BinaryTreeTest()
{
	int a[] = {1, 2, 3, '#', '#', 4, '#', '#', 5, 6};
	BinaryTree<int> t(a, sizeof(a)/sizeof(a[0]), '#');

	cout<<"前序遍历：";
	t.PreOrder();
	cout<<endl;
	
	cout<<"中序遍历：";
	t.InOrder();
	cout<<endl;
	
	cout<<"后序遍历：";
	t.PostOrder();
	cout<<endl;

	cout<<"非递归前序遍历：";
	t.PreOrder_NonR();
	cout<<endl;

	cout<<"非递归中序遍历：";
	t.InOrder_NonR();
	cout<<endl;

	cout<<"非递归后序遍历：";
	t.PostOrder_NonR();
	cout<<endl;

	cout<<"层序遍历：";
	t.LevelOrder();
	cout<<endl;

	cout<<"Size:"<<t.Size()<<endl;

	cout<<"LeafSize:"<<t.LeafSize()<<endl;


}
