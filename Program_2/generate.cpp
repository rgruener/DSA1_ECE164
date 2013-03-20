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

void addT4str(string &str, int digit = 99, bool areweadding = true)
{
if(areweadding)
{
if(str[digit]<'Z')
{
str[digit] += 1;
} else {
str[digit] = 'A';
if(digit > 0)
{
addT4str(str,digit-1,true);
} else {
cout<<"OH SHIT IMPOSSIBLE CHANCES!!!!"<<endl;
}
}
} else {
if(str[digit]>'A')
{
str[digit] -= 1;
} else {
str[digit] = 'Z';
if(digit > 0)
{
addT4str(str,digit-1,false);
} else {
cout<<"OH SHIT IMPOSSIBLE CHANCES!!!!"<<endl;
}
}
}
}

string genT4str(string str)
{
bool areweadding = true;
int addNum = rand()%11-5;
if(addNum < 0)
{
areweadding = false;
addNum = -1*(addNum);
}
for(int ii=0; ii<addNum; ++ii)
{
addT4str(str,99,areweadding);
}
return str;
}

int main()
{
int ii;
int oo;
int len;
int MAX;
int dtype;
stringstream cc;
string filename;
string str;
cout<<"Which type?"<<endl;
cin>>str;
cc<<str;
cc>>dtype;
list<Data *> theList;
switch(dtype)
{
case 1:
{
MAX=99000+(rand()%2001);
for(ii=0; ii<MAX; ++ii)
{
len = rand()%500+1;
str.clear();
for(oo=0; oo<len; ++oo) str+=(char)(rand()%94+33);
theList.push_front(new Data(str));
}
break;
}
case 2:
{
MAX=990000+(rand()%20001);
for(ii=0; ii<MAX; ++ii)
{
len = rand()%500+1;
str.clear();
for(oo=0; oo<len; ++oo) str+=(char)(rand()%94+33);
theList.push_front(new Data(str));
}
break;
}
case 3:
{
MAX=990000+(rand()%20001);
for(ii=0; ii<MAX; ++ii)
{
str.clear();
for(oo=0; oo<5; ++oo) str+=(char)(rand()%26+97);
theList.push_front(new Data(str));
}
break;
}
case 4:
{
MAX=990000+(rand()%20001);
str.clear();
for(oo=0; oo<100; ++oo) str+=(char)(rand()%26+65);
for(ii=0; ii<MAX; ++ii)
{
theList.push_back(new Data(genT4str(str)));
addT4str(str);
}
break;
}
default:
{cout<<"Whoops. Incorrect type!"<<endl; return 1337;}
}
writeDataList(theList);
return 0;
}