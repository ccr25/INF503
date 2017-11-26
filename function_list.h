#ifndef suffixTree.h
#define suffixTree_h

struct suffixNode{
	suffixNode * A;
	suffixNode * C;
	suffixNode * G;
	suffixNode * T;
	suffixNode * N;
	int ID;
	int start;
	int end;

};

class Suffix Tree{
	
	private char * subject;
		int G;
		
	Node * root;
	
			
	public:
		void set_subject_into_tree(char *, int size);	
		void suffix_tree();
		void suffix_tree(char *, int size);
		void ~suffix_tree();



		void insert();
		void serarch();
		struct *Node getNode();

	bool querry_trace(char *, int size);



}


int chartoASCII(char c);


#endif

