#include "word.h"

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


vector <pair<int,string>> predusingf_helper(string x, int freq_max_required=-1, int size=5,int include_self=1){

	node *temp = root;
	vector <pair<int,string>> preds;

	for(int i=0;i<x.size();i++){
		int t = x[i] - 'a';
		if(temp->next[t]==nullptr){
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
			preds.push_back({pq.top().first,x + (char)('a' + pq.top().second) + ans});
			// cout << "Word is : " << x + (char)('a' + pq.top().second) + ans << " frequency is : " << pq.top().first << endl; 
		}
		else{
			preds.push_back({get_freq(x),x});		
			// cout << "Main Word is : " << x << " frequency is : " << get_freq(x) << endl; 
		}

		pq.pop();
		count++;
	}

	return preds;
}

vector <pair<int,string>> pred_helper_one_mistake(string x){

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


	priority_queue <pair<int,string>> pq;

	// Looping over all positions
	for(int j=0;j<x.size();j++){
		int ind = x[j]-'a';
		for(int i=0;i<closest[ind].size();i++){

			string y = x;
			y[j] = closest[ind][i];
			vector <pair<int,string>> a = predusingf_helper(y,-1,2,1);
			for(auto it : a){
				pq.push(it);
			}
		}
	}	

	int count = 0;
	vector <pair<int,string>> pred;
	while(!pq.empty() && count<5){
		pred.push_back(pq.top());
		pq.pop();
		count++;
	}


	return pred;
}





vector <pair<int,string>> pred_helper_one_delete(string x){

	set <string> y;
	priority_queue <pair<int,string>> pq;

	// Removing one character	
	for(int i=0;i<x.size();i++){
		// Using set just to remove same substring possibilities
		 y.insert(x.substr(0,i) + x.substr(i+1,x.size()));
	}

	for(auto temp : y){
		vector <pair<int,string>> a = predusingf_helper(temp,-1,2,1);
		for(auto it : a){
			pq.push(it);
		}
	}

	int count=0;
	vector <pair<int,string>> pred;
	while(!pq.empty() && count<5){
		pred.push_back(pq.top());
		pq.pop();
		count++;
	}

	return pred;

}

vector <pair<int,string>> merge(vector <pair<int,string>> A, vector <pair<int,string>> B, int cond=0){

	int size = min( (int)(A.size()+B.size()),5);
	vector <pair<int,string>> merged;

	int count=0;
	if(cond){
		if(A.size()>=2){
			merged.push_back(A[0]);
			merged.push_back(A[1]);
			for(int i=2;i<A.size();i++)
				merged.push_back(A[i]);
			count=2;
		}
		else if(A.size()==1){
			merged.push_back(A[0]);
			count=1;
		}
	}
	else{
		for(auto &it : A)
			merged.push_back(it);
	}

	for(auto &it : B)
		merged.push_back(it);

	sort(merged.begin()+count, merged.end(), greater < pair<int,string> >());

	merged.resize(size);

	return merged;
}


vector <pair<int,string>> predusingf(string x, int verbose = 0){

	vector <pair<int,string>> exact, one_mistake, one_delete;

	// Prediction using x is an exact prefix of the output
	exact = predusingf_helper(x,-1,5,0);

	if(verbose){
		cout << "Input is an exact prefix : ";
		for(auto &it : exact)
			cout << it.second << " ";
		cout << endl;
	}

	one_mistake = pred_helper_one_mistake(x);

	if(verbose){
		cout << "After assuming exactly one mistake: ";
		for(auto &it : one_mistake)
			cout << it.second << " ";
		cout << endl;
	}

	if(x.size()>=3){
		one_delete = pred_helper_one_delete(x);

		if(verbose ){
			cout << "After assuming exactly one extra character: ";
			for(auto &it : one_delete)
				cout << it.second << " ";
			cout << endl;
		}
	}
	
	vector <pair<int,string>> temp = merge(exact,one_mistake,1);
	if(x.size()<3)
		return	temp; 
	vector <pair<int,string>> ans = merge(temp,one_delete);

	return ans;
}

