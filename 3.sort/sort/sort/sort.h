#pragma once
#include<iostream>
#include<chrono>
using namespace std;
using namespace chrono;
typedef unsigned int uint;

template<class T>
class sort
{
private:
	uint comp_times;
	uint move_times;
	double time;
	//"quick_sort" and "merge_sort" don't show the period, the move times and the compare times
	//so we use "get_quick_sort_info" and "get_merge_sort_info" to get them
public:
	void insert_sort(T arr[], size_t num);
	void shell_sort(T arr[], size_t num);
	void bubble_sort(T arr[], size_t num);
	void quick_sort(T arr[], size_t num,int start,int end);
	void get_quick_sort_info(T arr[], size_t num);
	void select_sort(T arr[], size_t num);
	void heap_sort(T arr[], size_t num);
	void merge(T arr[], T buff[], size_t num, uint start, uint mid, uint end);
	void merge_sort(T arr[], size_t num);
};

template<class T>
void sort<T>::insert_sort(T arr[], size_t num) {
	auto start = system_clock::now();
	int ptr = 1;
	comp_times = 0;
	move_times = 0;
	while (ptr < num) {
		comp_times++;
		if (arr[ptr] < arr[ptr - 1]) {
			T temp = arr[ptr];
			arr[ptr] = arr[ptr - 1];
			move_times++;
			for (int i = ptr - 2; i >= 0; i--) {
				comp_times++;
				move_times++;//can't put this at the end of the "for" loop, because it may break when we find the position
				if (temp >= arr[i]) {
					arr[i + 1] = temp;
					break;
				}
				else {
					arr[i + 1] = arr[i];
				}
			}
			if (temp < arr[0]) {
				//comp_times++;
				arr[0] = temp;
				move_times++;
			}
		}
		ptr++;
	}
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	for (int i = 0; i < num; i++) {
		//13 numbers each row
		cout << arr[i] << " ";
		if (i % 13 == 12)cout << endl;
	}
	if (num % 13)cout << endl;
	cout << "Insert_sort completes." << endl
		 << "Time: " << (double)duration.count()*microseconds::period::num / microseconds::period::den <<"s"<<endl
		 << "Move times: " << move_times << endl
		 << "Compare times: " << comp_times << endl;
}

template<class T>
void sort<T>::shell_sort(T arr[], size_t num){
	auto start = system_clock::now();
	comp_times = 0;
	move_times = 0;
	int d = num / 2;
	while (d) {
		int ptr = d;
		while (ptr < num) {
			comp_times++;
			if (arr[ptr] < arr[ptr - d]) {
				T temp = arr[ptr];
				arr[ptr] = arr[ptr - d];
				move_times++;
				int i;
				for (i = ptr - 2 * d; i >= 0; i = i - d) {
					comp_times++;
					move_times++;//can't put this at the end of the "for" loop, because it may break when we find the position
					if (arr[i] <= temp) {
						arr[i + d] = temp;
						break;
					}
					else {
						arr[i + d] = arr[i];
					}
				}
				if (i < 0) {
					//comp_times++;
					arr[i + d] = temp;
					move_times++;
				}
			}
			ptr++;
		}
		d = d / 2;
	}
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	for (int i = 0; i < num; i++) {
		//13 numbers each row
		cout << arr[i] << " ";
		if (i % 13 == 12)cout << endl;
	}
	if (num % 13)cout << endl;
	cout << "Shell_sort completes." << endl
		 << "Time: " << (double)duration.count()*microseconds::period::num / microseconds::period::den<<"s" << endl
		 << "Move times: " << move_times << endl
		 << "Compare times: " << comp_times << endl;
}

template<class T>
void sort<T>::bubble_sort(T arr[], size_t num){
	auto start = system_clock::now();
	int comp_times = 0;
	int move_times = 0;
	int pos = num;//number of elements needing sort
	while (pos) {
		int bound = pos;
		pos = 0;
		for (int i = 0; i < bound - 1; i++) {
			comp_times++;
			if (arr[i] > arr[i + 1]) {
				arr[i] ^= arr[i + 1];
				arr[i + 1] ^= arr[i];
				arr[i] ^= arr[i + 1];
				move_times += 3;
				pos = i + 1;//attemtion! It is not "pos = i;"
			}
		}
	}
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	for (int i = 0; i < num; i++) {
		//13 numbers each row
		cout << arr[i] << " ";
		if (i % 13 == 12)cout << endl;
	}
	if (num % 13)cout << endl;
	cout << "Bubble_sort completes." << endl
		<< "Time: " << (double)duration.count()*microseconds::period::num / microseconds::period::den <<"s"<< endl
		<< "Move times: " << move_times << endl
		<< "Compare times: " << comp_times << endl;
}

//recursive
//attention: "start" and "end" should be int but not unsigned int, which will cause dead loop 
template<class T>
void sort<T>::quick_sort(T arr[], size_t num,int start,int end){
	//[start,end]
	if (start >= end)return;
	int ptr1 = start;
	int ptr2 = end;
	int ref = arr[start];
	while (ptr1 < ptr2) {
		//quick partition
		while (ptr2 > ptr1 && arr[ptr2] >= ref)ptr2--, comp_times++;
		if (ptr2 > ptr1) arr[ptr1] = arr[ptr2], ptr1++, move_times++, comp_times++;
		while (ptr2 > ptr1&&arr[ptr1] <= ref)ptr1++, comp_times++;
		if (ptr2 > ptr1)arr[ptr2] = arr[ptr1], ptr2--, move_times++, comp_times++;
	}
	if (ptr1 != start) arr[ptr1] = ref, move_times++;
	quick_sort(arr, num, start, ptr1 - 1);
	quick_sort(arr, num, ptr2 + 1, end);
}

template<class T>
void sort<T>::get_quick_sort_info(T arr[], size_t num){
	comp_times = move_times = 0;
	auto start = system_clock::now();
	quick_sort(arr, num, 0, num - 1);
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	for (int i = 0; i < num; i++) {
		//13 numbers each row
		cout << arr[i] << " ";
		if (i % 13 == 12)cout << endl;
	}
	if (num % 13)cout << endl;
	cout << "Quick_sort completes." << endl
		<< "Time: " << (double)duration.count()*microseconds::period::num / microseconds::period::den <<"s"<< endl
		<< "Move times: " << move_times << endl
		<< "Compare times: " << comp_times << endl;
}

template<class T>
void sort<T>::select_sort(T arr[], size_t num) {
	auto start = system_clock::now();
	int comp_times = 0;
	int move_times = 0;
	for (int i = 0; i < num - 1; i++) {
		int minpos = i;
		for (int j = i + 1; j < num; j++) {
			comp_times++;
			if (arr[j] < arr[minpos]) {
				minpos = j;
			}
		}
		//comp_times++;
		if (minpos != i) {
			arr[i] ^= arr[minpos];
			arr[minpos] ^= arr[i];
			arr[i] ^= arr[minpos];
			move_times += 3;
		}
	}
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	for (int i = 0; i < num; i++) {
		//13 numbers each row
		cout << arr[i] << " ";
		if (i % 13 == 12)cout << endl;
	}
	if (num % 13)cout << endl;
	cout << "Select_sort completes." << endl
		<< "Time: " << (double)duration.count()*microseconds::period::num / microseconds::period::den <<"s"<< endl
		<< "Move times: " << move_times << endl
		<< "Compare times: " << comp_times << endl;
}

template<class T>
void sort<T>::heap_sort(T arr[], size_t num){
	//initiate the big root heap
	auto start = system_clock::now();
	comp_times = 0;
	move_times = 0;
	int prt = (num - 2) / 2;//parent
	while (prt >= 0) {
		//initiate the child heap, assuming the left and right child both have been heaps already
		int i = prt;
		int chd = 2 * prt + 1;//child
		while (chd < num) {
			if (chd + 1 < num && (comp_times += 1, arr[chd] < arr[chd + 1]))chd++;
			comp_times++;
			if (arr[i] >= arr[chd])break;
			else
			{
				arr[i] ^= arr[chd];
				arr[chd] ^= arr[i];
				arr[i] ^= arr[chd];
				move_times += 3;
				i = chd;
				chd = 2 * chd + 1;
			}
		}
		prt--;
	}
	//reset the heap
	for (int t = num - 1; t >= 1; t--) {
		arr[0] ^= arr[t];
		arr[t] ^= arr[0];
		arr[0] ^= arr[t];
		move_times += 3;
		//reset the heap:[0,1,...,t-1]
		prt = 0;
		int chd = prt * 2 + 1;
		while (chd < t) {
			if (chd + 1 < t && (comp_times += 1, arr[chd] < arr[chd + 1]))chd++;
			comp_times++;
			if (arr[prt] >= arr[chd])break;
			else
			{
				arr[prt] ^= arr[chd];
				arr[chd] ^= arr[prt];
				arr[prt] ^= arr[chd];
				move_times += 3;
				prt = chd;
				chd = 2 * prt + 1;
			}
		}
	}
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	for (int i = 0; i < num; i++) {
		//13 numbers each row
		cout << arr[i] << " ";
		if (i % 13 == 12)cout << endl;
	}
	if (num % 13)cout << endl;
	cout << "Heap_sort completes." << endl
		<< "Time: " << (double)duration.count()*microseconds::period::num / microseconds::period::den <<"s"<< endl
		<< "Move times: " << move_times << endl
		<< "Compare times: " << comp_times << endl;
}

//array "arr" and "buff" have the same length and we merge arr[start,mid] and arr[mid+1,end] into buff[start,end]
template<class T>
void sort<T>::merge(T arr[], T buff[], size_t num, uint start, uint mid, uint end){
	if (mid >= num)return;
	int pstart = mid + 1;
	int ptr = start;//points to the head of the buff
	while (start <= mid && pstart <= end) {
		if (arr[start] > arr[pstart])
			buff[ptr++] = arr[pstart++], comp_times++, move_times++;
		else
			buff[ptr++] = arr[start++], comp_times++, move_times++;
	}
	while (start <= mid)buff[ptr++] = arr[start++], move_times++;
	while (pstart <= end)buff[ptr++] = arr[pstart++], move_times++;
}

template<class T>
void sort<T>::merge_sort(T arr[], size_t num){
	auto start = system_clock::now();
	comp_times = 0;
	move_times = 0;
	T *buffer = new T[num];
	uint h = 1;//merge length
	while (h < num) {
		int i = 0;
		//attention: if we write "i <= num - 2 * h", it may be dead loop because the result is unsigned int, which won't be negative
		while (i + 2 * h <= num) {
			merge(arr, buffer, num, i, i + h - 1, i + 2 * h - 1);
			i += 2 * h;
		}
		if (i + h <= num)
			merge(arr, buffer, num, i, i + h - 1, num - 1);
		else
			while (i < num) buffer[i++] = arr[i++];
		h *= 2;
		i = 0;
		while (i + 2 * h <= num) {
			merge(buffer, arr, num, i, i + h - 1, i + h * 2 - 1);
			i += 2 * h;
		}
		if (i + h <= num)
			merge(buffer, arr, num, i, i + h - 1, num - 1);
		else
			while (i < num) buffer[i++] = arr[i++], move_times++;
		h *= 2;
	}
	delete[]buffer;
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	for (int i = 0; i < num; i++) {
		//13 numbers each row
		cout << arr[i] << " ";
		if (i % 13 == 12)cout << endl;
	}
	if (num % 13)cout << endl;
	cout << "Merge_sort completes." << endl
		<< "Time: " << (double)duration.count()*microseconds::period::num / microseconds::period::den <<"s"<< endl
		<< "Move times: " << move_times << endl
		<< "Compare times: " << comp_times << endl;
}
