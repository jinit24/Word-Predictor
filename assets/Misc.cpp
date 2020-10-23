#include "word.h"

void deleteWord(string x){
	node *temp = root;
	for(int i=0;i<x.size();i++){
		int t = x[i] - 'a';
		if(temp->next[t]==nullptr)
			break;
		temp = temp->next[t];
		temp->size--;
	}

	temp->end--;
	temp = root;
	for(int i=0;i<x.size();i++){
		int t = x[i] - 'a';
		if(temp->next[t]->size==0)
		{
			temp->next[t]=nullptr;
			return;
		}
		temp = temp->next[t];

	}
}

// Finds Exact match
bool find(string x){
	node *temp = root;
	for(int i=0;i<x.size();i++){
		int t = x[i] - 'a';
		if(temp->next[t]==nullptr)
			return false;
		temp = temp->next[t];
	}
	return(temp->end);	
}

// Checks Prefix 
bool Pre(string x){
	node *temp = root;
	for(int i=0;i<x.size();i++){
		int t = x[i] - 'a';
		if(temp->next[t]==nullptr)
			return false;
		temp = temp->next[t];
	}
	return true;
}