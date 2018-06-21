#include"biTree.h"
#include<cstdlib>
using namespace std;
void terminal() {
	system("pause");
}
int main()
{
	//test the biTree
	int a[11] = { 1,2,3,4,5,0,7,0,0,0,11 };
	biTree<int>mytree(a, 11, 0);		//A tree is constructed.
	unsigned int h;
	h = mytree.getDepth(mytree.root);	//h = 4
	mytree.preOrder();					//Pre order: 1 2 4 5 11 3 7
	mytree.inOrder();					//In order: 4 2 5 11 1 3 7
	mytree.postOrder();					//Post order: 4 11 5 2 7 3 1
	mytree.levelOrder();				//Level order: 1 2 3 4 5 7 11
	mytree.sufficientLevelOrder();		//Sufficient level order: 1 2 3 4 5 7 11
	mytree.print(mytree.root);
	cout << endl;						//1(2(4( , ),5( ,11( , ))),3( ,7( , )))
	mytree.print(mytree.root->l);
	cout << endl;						//2(4( , ),5( ,11( , )))
	mytree.printPath(mytree.root->l->r->r);
										//The path from the root to the given node is :
										//1<-2->5->11
	mytree.printPath(mytree.root);		//The node is the root
	mytree.printPath(mytree.root->r->l);//No such node
	cout<<"max: "<< mytree.getMaxElement() << endl;//max: 11
	atexit(terminal);					//A tree is destructed.
	return 0;
}