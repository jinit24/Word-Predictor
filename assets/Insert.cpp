#include "word.h"

void insertwWithFreq(string x, long long int freq){

	node *temp = root;
	for(int i=0;i<x.size();i++){
		int t = x[i] - 'a';
		if(temp->next[t]==nullptr)
			temp->next[t]= new node();
		temp = temp->next[t];
		temp->size++;
		temp->maxfreq = max(temp->maxfreq,freq);
	}

	temp->end=freq;
	// cout << "Word pushed in : " << x << endl;
} 


void insert(string x){
	node *temp = root;
	for(int i=0;i<x.size();i++){
		int t = x[i] - 'a';
		if(temp->next[t]==nullptr)
			temp->next[t]=new node();
		temp = temp->next[t];
		temp->size++;
	}
	temp->end++;
	// cout << "Word pushed in : " << x << endl;
} 

