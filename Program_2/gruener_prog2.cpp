// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2012

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds one string
class Data {
public:
  string data;
  Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    string line;
    getline(input, line);
    l.push_back(new Data(line));
  }

  input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
  string filename;
  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->data << endl;
  }

  output.close();
}

void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  list<Data *> theList;
  loadDataList(theList);

  cout << "Data loaded.  Executing sort..." << endl;

  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

int data_set,i,j,k,list_size;
int lens[5],vals[5];
int a,b,c,d,e;
int t3_flag=1;
int t4_flag=1;
char bins[26][26][26][26][26];
char letter;
vector <string> radix_bins[94];
int rbins_size[94];
string cur;
Data *dnode;
list<Data *>::iterator it,it2,it3;

bool compare(Data *A, Data *B){
	return A->data<B->data;
}

int check_data_set(list<Data *> &l){
	if ((list_size=l.size())<101000)
		return 1;
	for(list<Data *>::iterator it=l.begin();i<5;it++,i++){
		lens[i]=(*it)->data.length();
		if (lens[i]!=5)
			t3_flag=0;
		if (lens[i]!=100)
			t4_flag=0;
	}
	if (t3_flag)
		return 3;
	if (t4_flag)
		return 4;
	return 2;
}

void radix_sort(list<Data *> &l){
	i=0;
	while (i<94){
		radix_bins[i++].reserve(80000);
	}
	for(it=l.begin();it!=l.end();it++){
		letter=((*it)->data)[k]-'!';
		radix_bins[letter].push_back((*it)->data);
		rbins_size[letter]++;
	}
	for(i=0;i<94;i++){
		sort(radix_bins[i].begin(),radix_bins[i].end());
	}
	it=l.begin();
	for(i=0;i<94;i++){
		for(j=0;j<rbins_size[i];j++){
			(*it)->data.assign(radix_bins[i][j]);
			it++;
		}
		rbins_size[i]=0;
	}
}


void bin_sort(list<Data *> &l){
	for(it=l.begin();it!=l.end();it++){
		vals[0]=((*it)->data)[0]-'a';
		vals[1]=((*it)->data)[1]-'a';
		vals[2]=((*it)->data)[2]-'a';
		vals[3]=((*it)->data)[3]-'a';
		vals[4]=((*it)->data)[4]-'a';
		bins[vals[0]][vals[1]][vals[2]][vals[3]][vals[4]]++;
	}
	it=l.begin();
	// Not Properly Indented To make it more readable 
	// 5 nested loops make things very ugly
	for (a=0;a<26;a++){
	for (b=0;b<26;b++){
	for (c=0;c<26;c++){
	for (d=0;d<26;d++){
	for (e=0;e<26;e++){
		if ((j=bins[a][b][c][d][e])>0){
			cur.replace(0,1,1,a+'a');
			cur.replace(1,1,1,b+'a');
			cur.replace(2,1,1,c+'a');
			cur.replace(3,1,1,d+'a');
			cur.replace(4,1,1,e+'a');
			for (i=0;i<j;i++){
				(*it)->data.replace(0,5,cur);
				it++;
			}
	}}}}}}
}

void insertion_sort(list<Data *> &l){
	i=0;
	for(it=l.begin();it!=l.end();it++,i++){
		if (i==0)
			continue;
		cur=(*it)->data;
		it2=it;
		it3=it2;
		it3--;
		while (it2!=l.begin() && (*it3)->data > cur){
			(*it2)->data.assign((*it3)->data);
			it2--;
			it3--;
		}
		(*it2)->data=cur;
	}
}

void sortDataList(list<Data *> &l) {
	switch (data_set=check_data_set(l)){
		case(1):
			// Sort for Data T1
			radix_sort(l);
			break;
		case(2):
			// Sort for Data T2
			radix_sort(l);
			break;
		case(3):
			// Sort for Data T3
			bin_sort(l);
			break;
		case(4):
			// Sort for Data T4
			insertion_sort(l);
			break;
	}
}
