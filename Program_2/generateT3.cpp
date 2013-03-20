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

int main(int argc, char **argv) {
	int i,j,lines;
	char ch, s[5];
	if (argc < 2){
		perror("Must Input Number of Strings to Generate");
		exit(-1);
	}
	lines=atoi(argv[1]);
	string filename("SampleT3.txt");;
	ofstream output(filename.c_str());
	if (!output){
		cerr << "Error: could not open " << filename << endl;
		exit(-1);
	}
	output << lines << endl;
	if (argc<3)
		srand(time(NULL));
	else
		srand(atoi(argv[2]));
	for (i=0;i<lines;i++){
		for (j=0;j<5;j++){
			ch=rand() % 26;
			s[j]=ch+'A';
		}
		output << s << endl;
	}
}

