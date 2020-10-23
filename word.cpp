#include "assets/word.h"
#include <fstream>
using namespace std;

node* root;

int main(){
	
	root = new node();
    fstream file; 
    string word, filename; 
    filename = "assets/static/unigram_freq.csv"; 
    file.open(filename.c_str()); 

    cout << "########################################" << endl;
    cout << "Pre-processing" << endl;
    cout << "Pushing words to trie." << endl;
    while (file >> word) 
    { 
    	int found = word.find(',',0);
        insertwWithFreq(word.substr(0,found),stoll(word.substr(found+1,word.size())));

    } 
    cout << "Pushed all words!" << endl;
    cout << "########################################" << endl << endl;


    cout << "########################################" << endl;
    cout << "Welcome! Here are the queries you can use" << endl;
    cout << "1. Prediction (Type 1 to use this)" << endl;
    cout << "2. Quit" << endl;
    cout << "########################################" << endl << endl;;

    while(1){

        // int n;
        cout << "Type query : ";
        string s;
        cin >> s;

        if(s=="Prediction" || s=="1" || s=="prediction" || s=="pred"){
            
            // cin >> n;
            // while(n--){
            cout << "Enter string for prediction : ";
            string a;
            cin >> a;
            vector <string> preds;
            preds = predusingf(a);

            cout << "Predictions are : ";
            for(string &it : preds)
                cout << it << " ";

            if(preds.size()==0)
                cout << "Oops! No word found!";

            cout << endl << endl;
            // }

        }
        else if(s=="quit" || s=="Quit" || s=="q" || s=="2")
            return 0;
        else{
            cout << "Please use the above queries : 1 or 2" << endl << endl;
            continue;
        }
    }

}