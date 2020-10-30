# Word-Predictor / Auto-Complete
For a given input we try to predict the word using a trie.

# Input Files
In assets/static the sample.txt is used as the data for the trie.
The input file can be changed and make changes in line 87 of word.cpp
```
    vector <string> tokens = TakingInput("Your File Location");
```

# Usage 
1. Clone the repository.
```
git clone https://github.com/jinit24/Word-Predictor
```

2. To compile the files use : 
```
make
```

3. To run the program use   : 
```
./a.out
```
4. You should see :
```
Initialising ...
Type help to get a list of commands

>>

```
5. To make predictions type - predict 'word' <br>
   For a verbose version you could type - predict 'word' -v .
```
>> predict jj
Time taken for query : 155 microseconds
Predictions are : just judge jim ji 

```

```
>> predict kin -v
Input is an exact prefix : kind king kinsman kinky kine 
After assuming exactly one mistake: mind line lingered min kong 
After assuming exactly one extra character: in into know knew kind 
Time taken for query : 347 microseconds
Predictions are : kind king in into know 
```

6. To add words apart from the input file, you can use - add 'word' 'frequency'  
You can leave frequency blank, a default value if assigned.

7. stats can be used to get an idea of the data provided.
````
>> stats
Total number of words : 1000000
Total number of distinct words : 37589
Most frequent word : the
Frequency of the : 54664
````

8. You can type help to get a list of all commnands. Once you enter the new window just type q to exit.
````
HELP

DESCRIPTION
        Based on a given input file we make a trie. 
        Then for any given input we try to predict what could be the word. 
        You can go through the traversal, prediction and insertion algorithm in assets folder.

COMMANDS
        predict [word] [options]
        add     [word] [frequency]
        stats
        quit 

        Type man [command] to know more

Press q to exit
````


9. Use man [command] to know more about a specific command.

10. To exit type quit.


# Fun stuff
I used data from one of my whatsapp chats and results were fun. Give it a shot.  
You can also use directly files where each line is of the form  
word - frequency   
To use these types of files, uncomment lines 77-85 in word.cpp and comment out 87-90 in word.cpp  
````
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

````

Make the necessary changes to file name in 

````
filename = "New file location"; 

````

# Version
V3 : A word predictor based on frequency which is based of the input file.  
Newer UI - shell like interface  
Improvement in algorithms - allows one edit and deletion in addition to exact prefix match
