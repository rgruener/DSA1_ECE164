// Robert Gruener
// ECE164 Data Structures and Algorithms I
// assngment1.cpp

/* 
Programming Assignment #1: This program will take a file containing a
lit of commands as input, containing commands that create stacks and 
queues of certain data types and push or pop values to those lists. 
The output of the program will be placed in a file specified by the 
user.  
*/

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cstdlib>

using namespace std;

// Globals: File Streams For Input/Output
ifstream infile;
ofstream outfile;

// Exception for poping from empty list
class emptyListException{
	public:
		emptyListException(){};
};

// Exception for non-existant list
class listDoesntExistException{
	public:
		listDoesntExistException(){};
};

template <class T>
class SimpleList{
	private:
		class Node{
			public:
				T value;
				Node *next;
				Node(T val,Node *n=NULL):value(val),next(n){}
		};

		Node *head;
		Node *tail;
		string name;
		int size;

	protected:
		void insert_head(T val);
		void insert_tail(T val);
		T remove_head();

	public:
		SimpleList(string n);
		string get_name(){return name;}
		virtual void push(T node){};
		virtual T pop(){};
};

// Constructor
template <class T>
SimpleList<T>::SimpleList(string n){
	head=tail=NULL;
	size=0;
	name=n;
}

// Inser node at head with value val
template <class T>
void SimpleList<T>::insert_head(T val){
	if (size==0){
		head=tail=new Node(val,NULL);
	}
	else {
		Node *node=new Node(val,head);
		head=node;
	}
	size++;
}

// Insert node at tail with value val
template <class T>
void SimpleList<T>::insert_tail(T val){
	if (size==0){
		head=tail=new Node(val,NULL);
	}
	else {
		Node *node=new Node(val,NULL);
		tail->next=node;
		tail=node;
	}
	size++;
}

// Remove Node from head and return value of Node
template <class T>
T SimpleList<T>::remove_head(){
	if (size==0){
		throw emptyListException();
	}
	Node *tmp=head;
	T ret=head->value;
	head=head->next;
	size--;
	delete tmp;
	return ret;
}

template <class T>
class Stack : public SimpleList<T>{
	public:
		Stack(string name):SimpleList<T>(name){} // Constructor
		void push(T val) {SimpleList<T>::insert_head(val);} // Push val onto top of stack
		T pop() {return SimpleList<T>::remove_head();} // Pop off top of stack, return value
};

template <class T>
class Queue : public SimpleList<T>{
	public:
		Queue(string name):SimpleList<T>(name){} // Constructor
		void push(T val) {SimpleList<T>::insert_tail(val);} // Push val onto back of queue
		T pop() {return SimpleList<T>::remove_head();} // Pop front of queue, return value
};


// Function to iterate through the list of SimpleLists and return a pointer
// to a SimpleList with the name passed in, if no SimpleList is found, it 
// throws a listDoesntExist exception
template <class T>
SimpleList<T> *find_list(list<SimpleList<T> *> src, string name){
	typename list<SimpleList<T> *>::iterator it;
	SimpleList<T> *tmp;
	for (it=src.begin();it!=src.end();it++){
		if (!name.compare((*it)->get_name()))
			return *it;
	}
	throw listDoesntExistException();
}

// Function to read in lines of commands, parse, and execute them
void process_commands(){
	string line,cmd,subject,name;
	char type;
	int space=0;
	list<SimpleList<int> *> int_lists;
	list<SimpleList<double> *> double_lists;
	list<SimpleList<string> *> string_lists;
		
	while (getline(infile,line)){ // Read in line from input file
		outfile << "PROCESSING COMMAND: " << line << endl;
		space=line.find(" ");
		cmd = line.substr(0,space); // first argument of line
		line=line.substr(space+1);
		if (!cmd.compare("create")){
			space=line.find(" ");
			name=line.substr(0,space); // name of List to create
			line=line.substr(space+1); // line is now either queue or stack
			type=name[0]; // The data type of List: s, d, or i
			if (type=='i'){
				SimpleList<int> *n;
				try {
					// Try to find list, if list is found print out error
					find_list(int_lists,name);
 					outfile << "ERROR: This name already exists!" << endl;
				}
				// If list isnt found, exception is thrown and make new list
				catch (listDoesntExistException ){ 
					if (!line.compare("stack"))
						n=new Stack<int>(name);
					else if (!line.compare("queue"))
						n=new Queue<int>(name);
					int_lists.push_front(n);
				}
			}
			if (type=='d'){
				SimpleList<double> *n;
				try {
					// Try to find list, if list is found print out error
					find_list(double_lists,name);
					outfile << "ERROR: This name already exists!" << endl;
				}
				// If list isnt found, exception is thrown and make new list
				catch (listDoesntExistException ){
					if (!line.compare("stack"))
						n=new Stack<double>(name);
					else if (!line.compare("queue"))
						n=new Queue<double>(name);
					double_lists.push_front(n);
				}
			}
			if (type=='s'){
				SimpleList<string> *n;
				try {
					// Try to find list, if list is found print out error
					find_list(string_lists,name.c_str());
					outfile << "ERROR: This name already exists!" << endl;
				}
				// If list isnt found, exception is thrown and make new list
				catch (listDoesntExistException ){
					if (!line.compare("stack"))
						n=new Stack<string>(name);
					else if (!line.compare("queue"))
						n=new Queue<string>(name);
					string_lists.push_front(n);
				}
			}
		}
		try { // Look for list does not exist error in push or pop commands
			if (!cmd.compare("push")){
				space=line.find(" ");
				name=line.substr(0,space); // name of list to push to
				line=line.substr(space+1); // value to push
				type=name[0]; // type of list: s, d, or i
				if (type=='i'){
					SimpleList<int> *n;
					n=find_list(int_lists,name); // If list isnt found exception thrown and caught below
					n->push(atoi(line.c_str()));
				}
				if (type=='d'){
					SimpleList<double> *n;
					n=find_list(double_lists,name);
					n->push(atof(line.c_str()));
				}
				if (type=='s'){
					SimpleList<string> *n;
					n=find_list(string_lists,name);
					n->push(line);
				}
			}
			else if (!cmd.compare("pop")){
				try { // Look for list is empty error
					space=line.find(" ");
					name=line.substr(0,space); // name of list to pop from
					type=name[0]; // type of list: s, d, or i
					if (type=='i'){
						SimpleList<int> *n;
						int ret;
						n=find_list(int_lists,name);
						ret=n->pop(); // If list is empty, exception thrown and caught below
						outfile << "Value popped: " << ret << endl;
					}
					if (type=='d'){
						SimpleList<double> *n;
						double ret;
						n=find_list(double_lists,name);	
						ret=n->pop();
						outfile << "Value popped: " << ret << endl;
					}
					if (type=='s'){
						SimpleList<string> *n;
						string ret;
						n=find_list(string_lists,name);
						ret=n->pop();
						outfile << "Value popped: " << ret << endl;
					}
				}
				// If pop is called on empty list, exception is thrown
				// caught and proper error is printed out
				catch (emptyListException){
					outfile << "ERROR: This list is empty!" << endl;
				}
			}
		}
		// If name of lsit to push or pop to doesnt exist exception is
		// thrown caught and proper error is printed out
		catch (listDoesntExistException){
			outfile << "ERROR: This name does not exist!" << endl;
		}
	}
	infile.close();
}

int main(){

	string ifname,ofname,command;
	cout << "Enter name of input file: ";
	getline(cin, ifname);
	cout << "Enter name of output file: ";
	getline(cin, ofname);
	infile.open(ifname.c_str()); // open takes c string
	outfile.open(ofname.c_str());
	if (infile.is_open())
		process_commands();
	else 
		cerr << "Error while opening input file" << endl;
	return 0;
}

