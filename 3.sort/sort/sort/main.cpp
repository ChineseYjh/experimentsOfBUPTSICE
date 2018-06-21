#include<iostream>
#include<cstdlib>
#include"sort.h"
using namespace std;
#define MAX_SIZE 100
int main()
{
	//freopen("output100.txt", "w", stdout);
	sort<int>sort_method;
	srand((unsigned int)time(NULL));
	//sequence
	int seq[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++) seq[i] = i;
	//inverted sequence
	int inverted_seq[MAX_SIZE];
	//random sequence
	int a[MAX_SIZE];
	//insert_sort
	for (int i = 0; i < MAX_SIZE; i++) inverted_seq[i] = MAX_SIZE - i;
	for (int i = 0; i < MAX_SIZE; i++) {
		a[i] = rand();
	}
	sort_method.insert_sort(seq, MAX_SIZE);
	sort_method.insert_sort(inverted_seq, MAX_SIZE);
	sort_method.insert_sort(a, MAX_SIZE);
	cout << endl;
	//shell_sort
	for (int i = 0; i < MAX_SIZE; i++) inverted_seq[i] = MAX_SIZE - i;
	for (int i = 0; i < MAX_SIZE; i++) {
		a[i] = rand();
	}
	sort_method.shell_sort(seq, MAX_SIZE);
	sort_method.shell_sort(inverted_seq, MAX_SIZE);
	sort_method.shell_sort(a, MAX_SIZE);
	cout << endl;
	//bubble_sort
	for (int i = 0; i < MAX_SIZE; i++) inverted_seq[i] = MAX_SIZE - i;
	for (int i = 0; i < MAX_SIZE; i++) {
		a[i] = rand();
	}
	sort_method.bubble_sort(seq, MAX_SIZE);
	sort_method.bubble_sort(inverted_seq, MAX_SIZE);
	sort_method.bubble_sort(a, MAX_SIZE);
	cout << endl;
	//select_sort
	for (int i = 0; i < MAX_SIZE; i++) inverted_seq[i] = MAX_SIZE - i;
	for (int i = 0; i < MAX_SIZE; i++) {
		a[i] = rand();
	}
	sort_method.select_sort(seq, MAX_SIZE);
	sort_method.select_sort(inverted_seq, MAX_SIZE);
	sort_method.select_sort(a, MAX_SIZE);
	cout << endl;
	//quick_sort
	for (int i = 0; i < MAX_SIZE; i++) inverted_seq[i] = MAX_SIZE - i;
	for (int i = 0; i < MAX_SIZE; i++) {
		a[i] = rand();
	}
	sort_method.get_quick_sort_info(seq, MAX_SIZE);
	sort_method.get_quick_sort_info(inverted_seq, MAX_SIZE);
	sort_method.get_quick_sort_info(a, MAX_SIZE);
	cout << endl;
	//heap_sort
	for (int i = 0; i < MAX_SIZE; i++) inverted_seq[i] = MAX_SIZE - i;
	for (int i = 0; i < MAX_SIZE; i++) {
		a[i] = rand();
	}
	sort_method.heap_sort(seq, MAX_SIZE);
	sort_method.heap_sort(inverted_seq, MAX_SIZE);
	sort_method.heap_sort(a, MAX_SIZE);
	cout << endl;
	//merge_sort
	for (int i = 0; i < MAX_SIZE; i++) inverted_seq[i] = MAX_SIZE - i;
	for (int i = 0; i < MAX_SIZE; i++) {
		a[i] = rand();
	}
	sort_method.merge_sort(seq, MAX_SIZE);
	sort_method.merge_sort(inverted_seq, MAX_SIZE);
	sort_method.merge_sort(a, MAX_SIZE);
	cout << endl;
	system("pause");
	return 0;
}