#include<iostream>
#include<set>
#include<algorithm>
#include<vector>
using namespace std;
/*利用最少的颜色染这个图，使得每个点与邻点的颜色不同*/
/*多项式复杂度的近似算法*/

#define eventsNum 7
typedef unsigned int eventNo;
typedef unsigned int color;

struct Event
{
	eventNo no;//项目编号
	color col;//颜色，也即时间段
	set<eventNo>adjevent;//邻接的节点，亦即被其他人同时选的项目编号
};

bool comp(Event a, Event b) {
	return a.adjevent.size() > b.adjevent.size();
}

int main()
{
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int people;//参赛人数
	int number;//每个人的参赛项目数，至多三个
	while (cin >> people) {
		/*初始化邻接表*/

		Event events[eventsNum];//邻接表，存储每个项目对应点的颜色及与其相连的点（项目），注意其角标就是每个元素的编号
		for (eventNo i = 0; i < eventsNum; i++) {
			events[i].no = i;
			events[i].col = 0;
		}
		for (int i = 0; i < people; i++) {
			cin >> number;
			if (number == 2) {
				eventNo eve1, eve2;
				cin >> eve1 >> eve2;
				events[eve1].adjevent.insert(eve2);
				events[eve2].adjevent.insert(eve1);
			}
			else if (number == 3) {
				eventNo eve1, eve2, eve3;
				cin >> eve1 >> eve2 >> eve3;
				events[eve1].adjevent.insert(eve2);
				events[eve1].adjevent.insert(eve3);
				events[eve2].adjevent.insert(eve1);
				events[eve2].adjevent.insert(eve3);
				events[eve3].adjevent.insert(eve1);
				events[eve3].adjevent.insert(eve2);
			}
		}
		/*排序*/

		//利用邻接表的大小，也即点的度来降序排列
		vector<Event>vevents;
		for (int i = 0; i < eventsNum; i++) {
			vevents.push_back(events[i]);
		}
		sort(vevents.begin(), vevents.end(), comp);
		/*开始染色*/

		//从度大的点开始染色，每次从1-brushes的颜色中挑一个使得该点与相邻的点不同色，若没有，就brushes加一并且用这个色染该点。
		color brushes = 1;//总共用了的颜色数
		vevents[0].col = brushes;
		events[vevents[0].no].col = brushes;
		for (auto it = vevents.begin() + 1; it != vevents.end(); it++) {
			color brush = 1;
			for (; brush <= brushes; brush++) {
				bool brushable = true;
				//考查其邻点的颜色
				for (auto itt = (*it).adjevent.begin(); itt != (*it).adjevent.end(); itt++) {
					if (events[(*itt)].col == brush) {
						brushable = false;
						break;
					}
				}
				if (brushable) {
					(*it).col = brush;
					events[(*it).no].col = brush;
					break;
				}
			}
			//此时已有的颜色无法染这个点
			if (brush == brushes + 1) {
				events[(*it).no].col = (*it).col = brushes = brush;
			}
		}
		cout << "最少需要的色种为（亦是需要的最少时间段数）：" << brushes << endl;
	}
	system("pause");
	return 0;
}