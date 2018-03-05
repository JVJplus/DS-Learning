#include<bits/stdc++.h>
using namespace std;

class TrieNode{
public: //can be made private
char data;
TrieNode **children;
bool isTerminal;
public:
	TrieNode(char data, bool isTerminal=false){
		this->data=data;
		children=new TrieNode*[26];
		for (int i = 0; i < 26; ++i){
			children[i]=NULL;
		}
		this->isTerminal=isTerminal;
	}
};

class Trie{
private:
	TrieNode *root;
	int totalWords;
public:

	Trie(){
		root=new TrieNode('\0');
		totalWords=0;
	}

private:
	void insertWord(TrieNode *root, string word){
		if(root==NULL){
			return;
		}

		if(word.size()==0){
			root->isTerminal=true;
			return;
		}

		int index=word[0]-'a';
		TrieNode *children;
		if(root->children[index]!=NULL){
			children=root->children[index];
		}
		else{
			children=new TrieNode(word[0]);
			root->children[index]=children;
		}

		insertWord(root->children[index],word.substr(1));
	}

public:
	void insertWord(string word){
		totalWords++;
		insertWord(root,word);
	}

private:
	void print(TrieNode*root, string prefix){
		if(!root)
			return;
		if(root->isTerminal){
			cout<<prefix<<endl;
		}

		for(int i=0;i<26;i++){
			if(root->children[i]!=NULL){
				print(root->children[i],prefix+root->children[i]->data);
			}
		}
	}

public:
	void print(){
		print(root,"");
	}

private:
	bool search(TrieNode *root, string s){
		if(!root)
			return false;
		if(s.empty()){
			return root->isTerminal;
		}

		int index=s[0]-'a';
		if(root->children[index]){
			return search(root->children[index],s.substr(1));
		}
		return false;
	}


public:
	bool search(string s){
		return search(root,s);
	}

private:
	void remove(TrieNode *root, string s){
		if(s.empty()){
			root->isTerminal=false;
			return;
		}
		int index=s[0]-'a';
		TrieNode *children;
		if(root->children[index]){ //if node is present
			children=root->children[index];
		}else{
			return; //not found;
		}
		remove(children,s.substr(1));

		//deallocation
		if(children->isTerminal==false){
		//all nodes are NULL
			for (int i = 0; i < 26; ++i){
				if(children->children[i]!=NULL)
					return;
			}
			delete children;
			root->children[index]=NULL;
		}
	}

public:
	void remove(string word){
		totalWords--;
		remove(root,word);
	}


private:
	bool patternMatching(TrieNode *root, string pattern){
		if(pattern.empty())
			return true;
		int index=pattern[0]-'a';
		if(root->children[index]!=NULL){
			return patternMatching(root->children[index],pattern.substr(1));
		}
		return false;
	}	

public:
	bool patternMatching(string pattern){
		//works only if suffix are also added in the trie. eg:
		/*
			vect=all_words_in tries;
			for(int j=0;j<vect.size();j++){
      		for(int i=0;i<vect[j].length();i++){
				insertWord(vect[j].substr(i));
      		}	
        }
		*/
		return patternMatching(root,pattern);
	}

	int size(){
		return totalWords;
	}

	void getAllWords(TrieNode *root, vector<string> &ans, string prefix=""){
		if(root->isTerminal){
			ans.push_back(prefix);
		}

		for (int i = 0; i < 26; ++i){
			if(root->children[i]){
				getAllWords(root->children[i],ans,prefix+root->children[i]->data);
			}
		}
	}

	vector<string> getAllWords(){
		vector<string> ans;
		getAllWords(root,ans,"");
		return ans;
	}

	void autoComplete(TrieNode *root, string pattern,string prefix){
		if(pattern.empty()==false){ //find root
			int index=pattern[0]-'a';
			if(root->children[index]!=NULL){
				autoComplete(root->children[index],pattern.substr(1),prefix);
			}
		}
		else{
			print(root,prefix);//print rest
		}
	}

	void autoComplete(string pattern) {
		autoComplete(root,pattern,pattern);
	}

	bool findIfPalindromePair(TrieNode *original, TrieNode *reverse){
		if(!original && !reverse)
			return false;

		if(original && original->isTerminal && reverse && reverse->isTerminal)
			return true;

		if(original)
		{
			for (int i = 0; i < 26; ++i){
				if(original->children[i] && original->children[i]->isTerminal)
					return true;
			}
		}
		//if one word is terminating in one end
		if(reverse)//orig and rev is null
		{
			for (int i = 0; i < 26; ++i){ 
				if(reverse->children[i] && reverse->children[i]->isTerminal)
					return true;
			}
		}

		for (int i = 0; i < 26; ++i){
			if(original && original->children[i] && reverse && reverse->children) //both are non NULL ie have some char.
				if(findIfPalindromePair(original->children[i],reverse->children[i]))
					return true;
			}

			return false;
		}

		bool findIfPalindromePair(vector<string> arr) {
			//can be done by single trie also, search each query in reverse in trie
			TrieNode *originalRoot=new TrieNode('\0'),*reverseRoot=new TrieNode('\0');
			for (int i = 0; i < arr.size(); ++i){
				string word=arr[i];
				insertWord(originalRoot,word);
				reverse(word.begin(),word.end());
				insertWord(reverseRoot,word);
			}

			return findIfPalindromePair(originalRoot,reverseRoot);
		}


	};

	int main()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);    
#ifndef ONLINE_JUDGE
    // for getting input from input.txt
		freopen("input.txt", "r", stdin);
    // for writing output to output.txt
		freopen("output.txt", "w", stdout);
#endif
///////////////////////////////////////////////////////////////////////////////


		Trie trie;
		trie.insertWord("t");
		trie.insertWord("the");
		trie.insertWord("then");
		trie.insertWord("them");
		trie.insertWord("themselves");
		trie.insertWord("pan");
		trie.insertWord("pandom");
		trie.insertWord("pen");
		trie.insertWord("pens");
		trie.insertWord("parrot");
	// trie.print();
	// cout<<trie.size()<<endl;
		vector<string> allWords;
		allWords=trie.getAllWords();

		for (int i = 0; i < allWords.size(); ++i){
			cout<<allWords[i]<<endl;
		}

		trie.autoComplete("the");
	}
