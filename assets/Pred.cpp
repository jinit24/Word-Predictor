#include "word.h"

// Makes closest word prediction using bfs
vector <string> pred(string x){

	node *temp = root;
	vector <string> preds;
	for(int i=0;i<x.size();i++){
		int t = x[i] - 'a';
		if(temp->next[t]==nullptr)
			return preds;
		temp = temp->next[t];
	}

	string path = x;

	queue <pair<node*,string> >  q;
	q.push({temp,x});

	while(!q.empty()){
		
		pair<node*,string> t = q.front();
		q.pop();
		// cout << t.second << endl;
		
		if(t.first->end>0){
			preds.push_back(t.second);
		}

		for(int i=0;i<26;i++){
			if(t.first->next[i]!=nullptr)
				q.push({t.first->next[i],t.second + (char)('a'+i) });
		}		
		if(preds.size()>4)
			break;

	}

	return preds;

}

// Helper function for below function
void dfs(node* &temp, long long int freq,string &x){

	if(temp->end == freq)
		return;

	for(int i=0;i<26;i++){
		if(temp->next[i] && temp->next[i]->maxfreq == freq){
			x += (char)('a'+i);
			dfs(temp->next[i],freq,x) ;
		}
	}

}

// Makes prediction of word with highest frequency uses dfs
vector <string> predusingf(string x){

	node *temp = root;
	vector <string> preds;
	for(int i=0;i<x.size();i++){
		int t = x[i] - 'a';
		if(temp->next[t]==nullptr)
			return preds;
		temp = temp->next[t];
	}

	string path = x;

	priority_queue <pair<long long int,int>> pq;
	for(int i=0;i<26;i++){
		if(temp->next[i])
			pq.push({temp->next[i]->maxfreq,i});
	}

	int count=0;
	while(!pq.empty() && count<5){
		string ans;
		dfs(temp->next[pq.top().second],pq.top().first,ans);
		preds.push_back(x + (char)('a' + pq.top().second) + ans);
		pq.pop();
		count++;
	}

	return preds;

}
