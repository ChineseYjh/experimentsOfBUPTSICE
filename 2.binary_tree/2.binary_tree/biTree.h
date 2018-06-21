#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<class T>
struct node
{
	T data;
	node<T> *l;//points to the left child
	node<T> *r;//points to the right child
};

template<class T>
class biTree
{
private:
	unsigned int size;  //the number of the nodes in the tree
	T *levelOrderArray; //store the array of the argument of the construction function
	T emptysign;
public:
	node<T> *root;		//the root of the tree
	biTree(T a[], size_t num ,T emp);
	~biTree();
	void preOrder();
	void inOrder();
	void postOrder();
	void levelOrder();
	unsigned int getDepth(node<T> *);
	void print(node<T> *);
	void printPath(node<T> *);
	//custom
	void sufficientLevelOrder();
	T getMaxElement()const;
};

/*
*implementation of the class biTree
*/

//construct the biTree, the array "a" must be the static biTree storage and the "emptyNode" is the sign of no node
//this function apts the operation of the function "preOrder"
template<class T>
biTree<T>::biTree(T a[], size_t num,T emptyNode) {
	levelOrderArray = new T[num];
	memcpy(levelOrderArray, a, num * sizeof(T));
	node<T> *tempnode = root = new node<T>({ a[0],nullptr,nullptr });	//temporary node we are inspecting
	size = 1;
	unsigned int temp = 1;	//temporary subscript of the array we are inspecting
	int *stack = new int[num];//stack for subscripts of the array
	node<T> **nodestack = new node<T>*[num];
	stack[0] = 0;
	nodestack[0] = root;
	int top = 0;
	int nodetop = 0;
	bool dir = false;//shows which side we will inspect. false is left, true is right
	while (temp < num || top != -1) {
		if (temp >= num || a[temp] == emptyNode) {
			temp = stack[top--];
			tempnode = nodestack[nodetop--];
			temp = 2 * temp + 2;
			dir = true;
		}
		else {
			stack[++top] = temp;
			if (!dir)
				nodestack[++nodetop] = tempnode = tempnode->l = new node<T>({ a[temp],nullptr,nullptr }), size++;
			else
				nodestack[++nodetop] = tempnode = tempnode->r = new node<T>({ a[temp],nullptr,nullptr }), size++;
			temp = 2 * temp + 1;
			dir = false;
		}
	}
	delete[]stack;
	delete[]nodestack;
	emptysign = emptyNode;
	cout << "A tree is constructed." << endl;
}

//destruct the biTree
//the function apts the operation of the function "postOrder"
template<class T>
biTree<T>::~biTree() {
	struct tagNode
	{
		int tag;
		node<T> *ptr;
	};
	tagNode *stack = new tagNode[size];
	int top = -1;
	node<T> *temp = root;
	stack[++top] = tagNode({ 0,root });
	while (temp != nullptr || top != 0) {//注意这里终止条件中top为0，意味着root所指的内存刚好被delete而root对应的tagNode还在栈中
		if (!temp) {
			temp = (stack[--top]).ptr;
			(stack[top]).tag++;
		}
		else {
			if (stack[top].tag == 0)
				stack[++top] = tagNode({ 0,temp = temp->l });
			else if (stack[top].tag == 1)
				stack[++top] = tagNode({ 0,temp = temp->r });
			else {
				delete stack[top].ptr;
				temp = stack[top].ptr = nullptr;
			}
		}
	}
	delete[]stack;
	delete[]levelOrderArray;
	cout << "A tree is destructed." << endl;
}

//preorder the biTree
template<class T>
void biTree<T>::preOrder() {
	if (!root) { cout << "empty tree" << endl; return; }
	cout << "Pre order: ";
	node<T> *temp = root;
	node<T> **stack = new node<T>*[size];
	int top = -1;
	while (temp != nullptr || top != -1) {
		if (temp != nullptr) {
			stack[++top] = temp;
			cout << temp->data << " ";
			temp = temp->l;
		}
		else {
			temp = stack[top--];
			temp = temp -> r;
		}
	}
	cout << endl;
	delete[]stack;
}

//inorder the biTree
template<class T>
void biTree<T>::inOrder() {
	if (!root) {
		cout << "empty tree." << endl;
		return;
	}
	cout << "In order: ";
	node<T> *temp = root;
	node<T> **stack = new node<T>*[size];
	int top = -1;
	while (temp != nullptr || top != -1) {
		if (!temp) {
			temp = stack[top--];
			cout << temp->data << " ";
			temp = temp->r;
		}
		else {
			stack[++top] = temp;
			temp = temp->l;
		}
	}
	cout << endl;
	delete[]stack;
}

//postorder the biTree
//the structure "tagNode" is used in the stack
//everytime we inspect a node, we get the corresponding tagNode into the stack and initiate its tag as 0.
//and if the node is a nullptr, "temp" turns into the "ptr" of the one below the top of the stack
//if the node isn't a nullptr, it is divided into 3 parts:
//(1)tag == 0, 我们访问其左子树，并让左子树的根节点对应的tagNode入栈
//(2)tag == 1, 我们访问其右子树，并让右子树的根节点对应的tagNode入栈
//(3)tag == 2, 我们打印信息，再让"temp"等于nullptr等待下一次循环的操作
template<class T>
void biTree<T>::postOrder() {
	if (!root) {
		cout << "empty tree." << endl;
		return;
	}
	cout << "Post order: ";
	struct tagNode
	{
		int tag;
		node<T> *ptr;
	};
	tagNode *stack = new tagNode[size];
	int top = -1;
	stack[++top] = tagNode({ 0,root });
	node<T> *temp = root;
	while (temp != nullptr||top != 0) {
		if (!temp) {
			temp = stack[--top].ptr;
			stack[top].tag++;
		}
		else {
			if (stack[top].tag == 0)
				stack[++top] = tagNode({ 0,temp = temp->l });
			else if (stack[top].tag == 1)
				stack[++top] = tagNode({ 0,temp = temp->r });
			else {
				cout << ((stack[top]).ptr)->data << " ";
				temp = stack[top].ptr = nullptr;
			}
		}
	}
	cout << endl;
	delete[]stack;
}

//levelorder the biTree
//more efficient way: store the array "a" in the constructing funcion, which is just the level order of the biTree
//we implement it as the function "sufficientLevelOrder"
template<class T>
void biTree<T>::levelOrder() {
	if (!root) {
		cout << "empty tree." << endl;
		return;
	}
	cout << "Level order: ";
	node<T> **Q = new node<T> *[size];
	node<T> *temp = Q[0] = root;
	cout << root->data << " ";
	int front = -1;//points to the preceding one of the head of the queue
	int back = 0;//points to the last one of the queue
	for (int i = 0; i < size; i++) {
		//dequeue for "size" times because we have "size" nodes
		temp = Q[(front + 1) % size];//store the head
		front = (front + 1) % size;//dequeue
		if (temp->l)cout << ((Q[back = (++back) % size]) = temp->l)->data << " ";//enqueue and output
		if(temp->r)cout<< ((Q[back = (++back) % size]) = temp->r)->data << " ";
	}
	cout << endl;
	delete[]Q;
}

//refer to the function "levelOrder"
template<class T>
void biTree<T>::sufficientLevelOrder() {
	int count = 0;
	int ptr = 0;
	cout << "Sufficient level order: ";
	while (count < size) {
		if (levelOrderArray[ptr++] != emptysign)cout << levelOrderArray[ptr - 1] << " ", count++;
	}
	cout << endl;
}

//get the max data of the node in the tree
//this function apts the operation of the function "preOrder"
template<class T>
inline T biTree<T>::getMaxElement() const
{
	T max = root->data;
	node<T>**stack = new node<T>*[size];
	int top = -1;
	node<T> *temp = stack[++top] = root;
	while (top != -1 || temp == nullptr) {
		if (temp) {
			stack[++top] = temp;
			max = (temp->data) > max ? (temp->data) : max;
			temp = temp->l;
		}
		else {
			temp = stack[top--];
			temp = temp->r;
		}
	}
	delete[]stack;
	return max;
}

//get the depth of the tree
template<class T>
unsigned int biTree<T>::getDepth(node<T>*tempnode){
	if (tempnode == nullptr)return 0;
	int left = getDepth(tempnode->l);
	int right = getDepth(tempnode->r);
	return 1 + (left > right ? left : right);
}

//print the tree
//recursive
template<class T>
void biTree<T>::print(node<T> *tempnode) {
	if (tempnode) {
		cout << tempnode->data << "(";
		print(tempnode->l);
		cout << ",";
		print(tempnode->r);
		cout << ")";
	}
	else
		cout << " ";
}

//print the path between the node and the root
//the function apts the operation of the function "postOrder"
template<class T>
void biTree<T>::printPath(node<T> *tempnode){
	if (!root) {
		cout << "empty tree." << endl;
		return;
	}
	struct tagNode
	{
		int tag;
		node<T> *ptr;
	};
	tagNode *stack = new tagNode[size];
	bool *dir = new bool[size];//记录temp从root到当前节点的移动轨迹（false为往右走，true为往左走）
	int top = -1;
	int dirtop = -1;
	node<T> *temp = root;
	stack[++top] = tagNode({ 0,root });
	while (top != 0 || temp != nullptr) {
		if (!temp) {
			temp = stack[--top].ptr;
			stack[top].tag++;
			dirtop--;
		}
		else {
			if (temp == tempnode) break;//find the node
			if (stack[top].tag == 0)
				stack[++top] = tagNode({ 0,temp = temp->l }), dir[++dirtop] = true;
			else if (stack[top].tag == 1)
				stack[++top] = tagNode({ 0,temp = temp->r }), dir[++dirtop] = false;
			else {
				temp = stack[top].ptr = nullptr;
			}
		}
	}
	//三种情况：（1）不存在该节点（2）该节点为root（3）其他
	//(1)
	if (temp == nullptr)
		cout << "No such node" << endl;
	else if (temp == root)
		cout << "The node is the root" << endl;
	else {
		cout << "The path from the root to the given node is :" << endl;
		cout << stack[0].ptr->data ;
		for (int i = 0; i <= dirtop; i++) {
			if (dir[i])cout << "<-";
			else cout << "->";
			cout << stack[i + 1].ptr->data;
		}
		cout << endl;
	}
	delete[]stack;
	delete[]dir;
}