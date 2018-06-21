//recursion for eight queens problems
//complexity of time and space : O(n^n) O(n)
#include<iostream>
#include<cmath>
using namespace std;

//定义皇后数量（亦为棋盘的边长）
#define queenNum 8

//存储皇后的位置（数组角标为行数，元素值为列数）
int stackForPos[queenNum];

//画出当前棋盘的摆放状态，0作为空位置，*作为皇后的位置
void drawBoard() {
	for (int i = 0; i < queenNum; i++) {
		//一共queenNum列
		for (int j = 0; j < stackForPos[i]; j++) {
			cout << '0';
		}
		cout << '*';
		for (int j = stackForPos[i] + 1; j < queenNum; j++) {
			cout << '0';
		}
		cout << endl;
	}
}

//摆放第k行（0<=k<queenNum)的皇后
void putKthQueen(int k) {
	//检查输入是否合法，如果不合法则抛出异常
	if (k < 0 || k > queenNum)throw "输入异常";
	//检查是否到达递归终点，即当摆好了前面queenNum个皇后时，若是则输出stackForPos里的元素（亦即皇后的位置）
	if (k == queenNum) {
		for (int i = 0; i < queenNum - 1; i++) {
			cout << "( " << i + 1 << " , "<<stackForPos[i] + 1 << " )" << " ";
		}
		cout << "( " << queenNum << " , " << stackForPos[queenNum - 1] + 1 << " )" << endl;
		drawBoard();//调用该函数利用输出格式将对应的皇后在棋盘的位置模拟出来
		return;
	}
	//若没有到达递归终点，则对第k行的所有列进行枚举，而对合法的列再进行更深层的递归
	for (int col = 0; col < queenNum; col++) {
		//每次枚举都又要与前面k个皇后的位置比较，注意如果k == 1则跳过第一个for循环的执行
		int i = 0;
		for (; i < k; i++) {
			if (stackForPos[i] == col || abs(k - i) == abs(stackForPos[i] - col)) {
				//此时该col作为该皇后的列位置会使该皇后与第i行的皇后在同一列或在其斜线上
				break;
			}
		}
		if (i == k) {
			//意味着与前面k个皇后不冲突
			stackForPos[k] = col;//记录下该列标
			putKthQueen(k + 1);//继续更深层的递归
		}
	}
}

int main()
{
	try {
		putKthQueen(0);
	}
	catch (char *exceptions) {
		cout << exceptions << endl;
	}
	system("pause");
	return 0;
}