#include "word.h"

stat stats;

void insertWithFreq(string x, long long int freq){

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

	stats.total_words++;
	node *temp = root;

	for(int i=0;i<x.size();i++){
		int t = x[i] - 'a';
		if(temp->next[t]==nullptr)
			temp->next[t]=new node();
		temp = temp->next[t];
		temp->size++;
	}

	if(temp->end==0)
		stats.total_distinct_words++;
	temp->end++;

	if(temp->end>stats.max_frequency){
		stats.max_frequency = temp->end;
		stats.most_frequent_word = x;
	}

	insertWithFreq(x,temp->end);
} 

