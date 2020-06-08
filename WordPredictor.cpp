#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
using namespace std;

struct node{
	int size;
	int end;
	node* next[26];
	node(){
		size = 0;
		end = 0;
		for(int i=0;i<26;i++)
			next[i] = nullptr;
	}
};

node* root;

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

string removeNonAlpha(string a){
	string ans;
	for(auto it : a){
		if(it-'a'>=0 && it-'a'<26)
			ans.push_back(it);
	}
	return ans;
}

vector <string> TakingInput(string filename){

	ifstream input(filename);
	stringstream sstr;
	string a;
	while(input >> sstr.rdbuf());
		a = sstr.str();

    string buf;                 // Have a buffer str
    stringstream ss(a);       // Insert the string into a stream
    vector<string> tokens; // Create vector to hold our words

    while (ss >> buf){
    	transform(buf.begin(), buf.end(), buf.begin(), ::tolower); 
    	buf = removeNonAlpha(buf);
        tokens.push_back(buf);
    }
    return tokens;
}

int main(){
	root = new node();
	vector <string> tokens = TakingInput("engmix.txt");
	cout << "Pushing words in to the trie ! " << endl;
    for(auto it : tokens){
    	insert(it);
    }
    cout << "Pushed all words ! " << endl;

    int n;
    cout << "Enter number of words for prediction : ";
    cin >> n;
    while(n--){
	    string a;
	    cin >> a;
	    vector <string> preds;
	    preds = pred(a);

	    for(auto it : preds)
	    	cout << it << " ";
	    cout << endl;
	}

}