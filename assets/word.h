#include <bits/stdc++.h>
using namespace std;

#ifndef WORD_H
#define WORD_H
	
	struct node{
		int size ,end;
		long long int maxfreq;
		node* next[26];
		node(){
			size = 0,end = 0, maxfreq=0;
			for(int i=0;i<26;i++)
				next[i] = nullptr;
		}
	};

	struct stat{
		string most_frequent_word;
		int max_frequency;
		int total_distinct_words;
		int total_words;
	};


	// Global Variable - root of trie
	extern node* root;
	extern stat stats;

	// Inserting Algorithms
	extern void insertWithFreq(string x, long long int freq);
	extern void insert(string x);

	// Prediction Algorithms
	extern vector <pair<int,string>> predusingf(string x, int verbose);
	// extern vector <string> pred(string x);

	// Miscellaneous Algorithms
	extern void deleteWord(string x);
	extern bool find(string x);
	extern bool Pre(string x);


#endif /* SORT_H */
