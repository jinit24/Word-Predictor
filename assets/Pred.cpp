#include "word.h"
#include <unistd.h>

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

int get_freq(string x){

	node *temp = root;
	for(int i=0;i<x.size();i++){
		int t = x[i] - 'a';
		temp = temp->next[t];
	}

	return temp->end;
}

// Helper function for below predusingf function
void dfs(node* &temp, long long int freq,string &x){

	if(temp->end == freq)
		return;

	int v=0;
	for(int i=0;i<26;i++){
		if(temp->next[i] && temp->next[i]->maxfreq == freq && v==0){
			x += (char)('a'+i);
			dfs(temp->next[i],freq,x) ;
			v=1;
		}
	}
}

void add_to_ans(vector <string> a, vector <string> &ans, vector <int> &f){

	int n = ans.size();
	if(n!=5 && !a.empty()){
		ans.push_back(a[0]);
		f[n] = get_freq(a[0]);
		n++;
		if(a.size()==1)
			return;
		return add_to_ans({a[1]},ans,f);
	}
	// if(n==0){
	// 	ans.push_back(a[0]);
	// 	f[n] = get_freq(a[0]);
	// 	n++;
	// }


	// CHECK THIS
	for(int i=a.size()-1;i>=0;i--){
		if( get_freq(a[i])>f[n-1] && (find(ans.begin(), ans.end(), a[i]) == ans.end()) ){

			ans[n-1] = a[i];
			f[n-1] = get_freq(ans[n-1]);

			for(int j=n-1;j>2;j--){
				if(f[j]>f[j-1]){
					swap(f[j],f[j-1]);
					swap(ans[j],ans[j-1]);
				}
			}
		}
	}

}


vector <string> predusingf_helper(string x, int freq_max_required=-1, int size=5,int include_self=1){

	node *temp = root;
	vector <string> preds;
	for(int i=0;i<x.size();i++){
		int t = x[i] - 'a';
		if(temp->next[t]==nullptr){
			// temp->next[t] = new node();		
			return {};	
		}
		temp = temp->next[t];
	}


	long long int freq_max = -1;
	string path = x;

	priority_queue <pair<long long int,int>> pq;

	if(include_self && temp->end>0)
		pq.push({temp->maxfreq,-1});

	for(int i=0;i<26;i++){
		if(temp->next[i] && temp->next[i]->maxfreq> freq_max_required){
			pq.push({temp->next[i]->maxfreq,i});
			freq_max = max(freq_max, temp->next[i]->maxfreq);
		}
	}

	int count=0;
	while(!pq.empty() && count<size){
		string ans;
		if(pq.top().second!=-1){
			dfs(temp->next[pq.top().second],pq.top().first,ans);
			preds.push_back(x + (char)('a' + pq.top().second) + ans);
			// cout << "Word is : " << x + (char)('a' + pq.top().second) + ans << " frequency is : " << pq.top().first << endl; 
		}
		else{
			preds.push_back(x);		
			// cout << "Main Word is : " << x << " frequency is : " << get_freq(x) << endl; 
		}

		pq.pop();
		count++;
	}

	return preds;
}


void pred_helper_one_mistake(string x, vector <string> &ans, vector <int> &f){

	vector <vector <char> > closest(26);
	closest[0] = {'q','w','s','d','z'};
	closest[1] = {'v','b','g','h','n'};
	closest[2] = {'d','x','v','b','f'};
	closest[3] = {'s','e','f','c','x','r'};
	closest[4] = {'w','r','s','d','f'};
	closest[5] = {'e','r','c','d','g','v','t'};
	closest[6] = {'t','r','y','f','h','v','b'};
	closest[7] = {'g','j','y','b','n','t','u'};
	closest[8] = {'u','o','j','k','l'};
	closest[9] = {'h','u','y','k','i','n','m'}; //j
	closest[10] = {'i','o','j','m','l'}; //k
	closest[11] = {'i','o','p','m','k'}; //l
	closest[12] = {'n','j','l','k'}; //m
	closest[13] = {'b','j','h','m'}; //n
	closest[14] = {'i','k','l','p'}; //o
	closest[15] = {'i','o','k','l'}; //p
	closest[16] = {'w','a','s'}; //q
	closest[17] = {'d','e','g','t','f'}; //r
	closest[18] = {'q','e','w','a','x','d','z','c'}; //s
	closest[19] = {'h','r','y','g','f'}; //t
	closest[20] = {'y','h','j','k','i'}; //u
	closest[21] = {'c','d','g','f','b'}; //v
	closest[22] = {'q','a','s','d','e'}; //w
	closest[23] = {'z','a','s','d','c'}; //x
	closest[24] = {'h','u','t','g','j'}; //y
	closest[25] = {'a','s','d','x'}; //z

	int n = ans.size();
	int ind = x[0]-'a';
	int threshold = f[n-1];

	// Looping over all positions
	for(int j=0;j<x.size();j++){
		for(int i=0;i<closest[ind].size();i++){

			string y = x;
			y[j] = closest[ind][i];
			vector <string> a = predusingf_helper(y,threshold,2);
			// for(auto it : a){
			// 	cout << it << " " << get_freq(it) << " " ;
			// }
			// cout << endl;
			add_to_ans(a,ans,f);

		}
	}	
}


void pred_helper_one_delete(string x, vector <string> &ans, vector <int> &f){

	int n = ans.size();
	int threshold = f[n-1];
	set <string> y;

	// Removing one character	
	for(int i=0;i<x.size();i++){
		// Using set just to remove same substring possibilities
		 y.insert(x.substr(0,i) + x.substr(i+1,x.size()));
	}

	for(auto temp : y){

		vector <string> a = predusingf_helper(temp,threshold,2,0);
		add_to_ans(a,ans,f);

		// One character removed + One character mistake
		pred_helper_one_mistake(temp,ans,f);

	}
}


// Makes prediction of word with highest frequency uses dfs
vector <string> predusingf(string x){

	vector <string> ans;
	// Normal prediction assuming every letter is correct in the string
	ans = predusingf_helper(x,-1,5,0);

	cout << "Original ans: ";
	for(string &it : ans)
		cout << it << " ";
	cout << endl;

	int n = ans.size();
	vector <int> f(5);

	for(int j=0;j<n;j++){
		f[j] = get_freq(ans[j]);
	}

	// Prediction assuming first letter is incorrect
	if(x.size()>2){
		pred_helper_one_mistake(x,ans,f);

		cout << "After assuming one mistake ans: ";
		for(string &it : ans)
			cout << it << " ";
		cout << endl;

		pred_helper_one_delete(x,ans,f);

		cout << "After assuming one deletion ans: ";
		for(string &it : ans)
			cout << it << " ";
		cout << endl;
	}

	// for(auto it : ans){
	// 	cout << it << " " << get_freq(it) << endl;
	// }

	return ans;
}


// Check for repitions - try dalmont, kin
// Adding criteria only frequency?
