#include "assets/word.h"
#include <fstream>
#include <chrono> 
#include <unistd.h> 
#include <sys/wait.h>

using namespace std;
using namespace std::chrono; 

node* root;

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

void print_stats(){

        struct stat{
        string most_frequent_word;
        int max_frequency;
        int total_distinct_words;
        int total_words;
    };

    cout << "Total number of words : " << stats.total_words << endl;
    cout << "Total number of distinct words : " << stats.total_distinct_words << endl;
    cout << "Most frequent word : " << stats.most_frequent_word << endl;
    cout << "Frequency of " << stats.most_frequent_word << " : " << stats.max_frequency << endl;

}

bool isNumber(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;
 
    return true;
}


int main(){
	
	root = new node();
    fstream file; 
    string word, filename; 


    // cout << "Pre-processing" << endl;
    cout << "Initialising ..." << endl;
   
    // filename = "assets/static/unigram_freq.csv"; 
    // file.open(filename.c_str()); 

    // while (file >> word) 
    // { 
    // 	int found = word.find(',',0);
    //     insertwWithFreq(word.substr(0,found),stoll(word.substr(found+1,word.size())));

    // } 

    vector <string> tokens = TakingInput("assets/static/sample.txt");
    for(auto it : tokens){
        insert(it);
    }

    // cout << "Pushed all words!" << endl;
    // cout << endl;

    cout << "Type help to get a list of commands" << endl;

    cout << endl;

    while(1){

        string s;

        cout << ">> ";
        getline (std::cin,s);
        int start = 0, end = 0;

        auto iss = std::istringstream{s};
        auto str = std::string{};
        vector <string> query;
        while (iss >> str) {
            query.push_back(str);
        }

        if(query.size()==0)
            cout << "Please type a query" << endl;
        else if(query.size()==1){
            if(query[0]=="help" || query[0]=="H" || query[0]=="h" || query[0]=="Help"){
                if(!fork()){
                    cout << "Child" << endl;
                    execlp("less","less","man/help",NULL);
                }
                while(wait(NULL)!=-1);
            }
            else if(query[0] == "quit" || query[0] == "Quit" || query[0] == "q" || query[0] == "Q"){
                cout << "Bye!" << endl;
                break;
            }
            else if(query[0]== "stats" || query[0] == "stats")
                print_stats();
            else{
                cout << "Check syntax" << endl;
            }
        }
        else if (query.size()==2){

                if(query[0]=="predict" || query[0]=="Predict" ){

                    vector <pair<int,string>> preds;
                    auto start = high_resolution_clock::now();
                    preds = predusingf(query[1],0);
                    auto stop = high_resolution_clock::now(); 
                    cout << "Time taken for query : " << duration_cast<microseconds>(stop - start).count() << " microseconds" << endl;

                    cout << "Predictions are : ";
                    if(preds.size()>0){
                        for(auto &it : preds)
                            cout << it.second << " ";
                        cout << endl;
                    }
                    else
                        cout << "Oops! No word found!" << endl;;

                }
                else if(query[0]=="add"){

                    // Default value of 100
                    insertWithFreq(query[1],100);
                    cout << query[1] << " added!" << endl;

                }
                else if(query[0]=="man"){

                    if(query[1]=="predict" || query[1]=="Predict"){
                        if(!fork()){
                            cout << "Child" << endl;
                            execlp("less","less","man/predict",NULL);
                        }
                        while(wait(NULL)!=-1);
                    }   
                    else if(query[1]=="stats" || query[1]=="Stats"){
                        if(!fork()){
                            cout << "Child" << endl;
                            execlp("less","less","man/stats",NULL);
                        }
                        while(wait(NULL)!=-1);
                    }     
                    else if(query[1]=="add" || query[1]=="Add"){
                        if(!fork()){
                            cout << "Child" << endl;
                            execlp("less","less","man/add",NULL);
                        }
                        while(wait(NULL)!=-1);
                    }     
                    else
                        cout << "Unknown command provided" << endl;

                }
                else
                    cout << "Check syntax" << endl;

        }
        else if(query.size()==3){


            if(query[0]=="predict" || query[0]=="Predict" ){

                    vector <pair<int,string>> preds;
                    auto start = high_resolution_clock::now();
                    preds = predusingf(query[1],1);
                    auto stop = high_resolution_clock::now(); 
                    cout << "Time taken for query : " << duration_cast<microseconds>(stop - start).count() << " microseconds" << endl;

                    cout << "Predictions are : ";
                    if(preds.size()>0){
                        for(auto &it : preds)
                            cout << it.second << " ";
                        cout << endl;
                    }
                    else
                        cout << "Oops! No word found!" << endl;;
            }
            else if(query[0]=="add"){

                if(isNumber(query[2])){
                    insertWithFreq(query[1],stoll(query[2]));
                    cout << query[1] << " added!" << endl;
                }
                else
                    cout << "The frequency has to be a number" << endl;
            }            

        }


    }

}