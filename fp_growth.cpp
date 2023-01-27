#include<bits/stdc++.h> 
using namespace std; 
typedef long long ll; 
typedef pair<int,int> ii;
typedef pair<char,int> ci; 
typedef pair<int,char> ic;
typedef pair<char,char> cc;
typedef vector<int> vi; 
typedef vector<char> vc;
typedef vector<ii> vii; 
typedef vector<pair<int,ii>> viii; 
typedef set<int> si;
typedef unordered_map<char,int> umci;
typedef unordered_map<string,string> umss;
typedef unordered_map<string,vector<char>> ums_vc;
typedef priority_queue<char> pq_c;
typedef unordered_map<string,pq_c> ums_pq_c;
typedef vector<pair<vc,int>> vp_vci;
typedef map<set<char>,int> msci;

#define F first 
#define S second 
#define pb push_back 
#define loop(i,a,b) \
     for(int i=a;i<b;i++)
#define dloop(i,a,b) \
     for(int i=a; i>=b;i--)

const int N = 1e5 + 10;


struct Node{
    Node* links[26]; 
    ll freq[26];
    bool flag = false; 
    

    bool isContainsKey(char ch){return links[ch - 'A'] != NULL;}
    void put(char ch,Node *node){links[ch - 'A'] = node;freq[ch-'A']=1;}
    Node* get(char ch){return links[ch - 'A'];}
    void setEnd(){flag = true;}
    bool isEnd(){return flag;}
    // ll frequency(Node *node){return node->freq;}
};

class Trie{
     private: Node* root; 
     public:
         Trie(){root = new Node();}
         void insert(string word){
            Node *node = root; 
            loop(i,0,word.length()){
                //if(node->isContainsKey(word[i])) ++node->freq;
                if(node->isContainsKey(word[i])) node->freq[word[i]-'A']++;
                if(!node->isContainsKey(word[i])){node->put(word[i],new Node());}
                node = node->get(word[i]);
            }
            node->setEnd();
         }
         bool search(string word){
            cout << word << endl;
            Node *node = root;
            loop(i,0,word.length()){
                if(!node->isContainsKey(word[i])){return false;}
              //  cout << word[i] << " " << node->freq << "  ";
                cout << word[i] << " " << node->freq[word[i]-'A'] << " ";
                node = node->get(word[i]);
            }
            cout << endl;
            return node->isEnd();
         }
         bool startswith(string prefix){
            Node *node  = root; 
            loop(i,0,prefix.length()){
                if(!node->isContainsKey(prefix[i])){return false;}
                node = node->get(prefix[i]);
            }
            return true;
         }
         vp_vci iterTrie(string word,char ch,vp_vci cfpt){
            Node *node = root; 
           // vp_vci cfpt; // conditional fequent pattern tree
            vc chars;
            loop(i,0,word.length()){
                if(node->isContainsKey(word[i]) && word[i] != ch){
                    chars.pb(word[i]);
                   // cout << word[i] << endl;
                }
                if(word[i]==ch && node->isContainsKey(word[i])){
                    cfpt.pb({chars,node->freq[ch-'A']});
                }
                node = node->get(word[i]);
            }
            return cfpt;
         }
};

const int MIN_SUPPORT_COUNT = 3;
bool comp(ic intCharPair_1,ic intCharPair_2){
    if(intCharPair_1.first == intCharPair_2.first)return intCharPair_1.second < intCharPair_2.second; return intCharPair_1.first>intCharPair_2.first;}

int main(){
    ums_vc data; 
    data["T1"]={'E','K','M','N','O','Y'};
    data["T2"]={'D','E','K','N','O','Y'};
    data["T3"]={'A','E','K','M'};
    data["T4"]={'C','K','M','U','Y'};
    data["T5"]={'C','E','I','K','O'};

    umci intCharPair; 
    for(auto &VectorValues:data)
       for(auto &Chars:VectorValues.second){
           if(intCharPair.count(Chars)){++intCharPair[Chars];}
           else intCharPair[Chars] = 1;
       }
    
    vector<ic> remain_charIntPair;
    for(auto &check:intCharPair)
        if(check.second >= MIN_SUPPORT_COUNT) remain_charIntPair.pb({check.second,check.first});
    sort(remain_charIntPair.begin(),remain_charIntPair.end(),comp);

    umci remainOrderedItemSet;
    for(auto &check:remain_charIntPair){
        remainOrderedItemSet[check.second]=check.first;}  

    umss finalItemSet; 
    for(auto &items:data){
        vector<string> ar(N,"");
        std:vector<string>::iterator it;
        finalItemSet[items.first] = "";
        for(auto &chars:items.second){if(remainOrderedItemSet[chars] > 0){ar[remainOrderedItemSet[chars]] += chars;}}
        dloop(i,N-1,0){finalItemSet[items.first]+=ar[i];}
    }
    
    for(auto &check:finalItemSet){cout << check.first << " " << check.second << endl;}

    Trie trie = Trie();
    for(auto &check:finalItemSet){
        trie.insert(check.second);
    }
    for(auto &check:finalItemSet){
        trie.search(check.second);
    }
    
    // vp_vci a ;
    // a= trie.iterTrie("KEMOY",'Y',a); 
    // a= trie.iterTrie("KEOY",'Y',a);

    unordered_map<char,vp_vci> cfpi; //conditional_frequent_pattern_items;
    vc Chars; // we will use 116 --> remain_charIntPair;
    for(auto &check:remain_charIntPair){Chars.pb(check.second);}
   

    loop(i,0,Chars.size()){
        vp_vci fip; 
        for(auto &check:finalItemSet){
            fip = trie.iterTrie(check.second,Chars[i],fip);
        }
        cfpi[Chars[i]] = fip;
        fip.clear();
    }
    unordered_map<char,msci> pattern_base;
    for(auto &check:cfpi){
        cout << check.first << " : " << endl;
        msci patterns; set<char> st;
        for(auto &item:check.second){
            for(auto &it:item.first){
                cout << it << " ";
                // st.insert(it); 
                // if(patterns[st]==NULL){patterns[st]=1;}
                // else
                // patterns[st]++;
            }
            cout << item.second << endl;
        }
    }
  
    return 0;
}



// ums_pq_c dsCheck;
    // for(auto &items:data){
    //     for(auto &chars:items.second){
    //         dsCheck[items.first].push(chars);
    //     }
    // }

    // for(auto &items:dsCheck){
    //     while(!items.second.empty()){cout << items.second.top() << " ";items.second.pop();}
    //     cout<<endl;
    // }

    // for(auto &items:dsCheck){
    //     while(!items.second.empty()){
    //         if(remainOrderedItemSet[items.second.top()])
    //         finalItemSet[items.first] += items.second.top();
    //         items.second.pop();
    //     }
    // }

    
    // for(auto &check:remainOrderedItemSet){
    //    // if(check.second > 0)
    //     cout << check.first << " " << check.second << endl;
    // }
   
    // std:unordered_map<char,int>::iterator it; 

  // for(auto &items:data){
    //     finalItemSet[items.first] = "";
    //     for(auto &chars:items.second){
    //           if(remainOrderedItemSet[chars])
    //           finalItemSet[items.first]+=chars;
    //     }
    // }

    // unordered_map<string,string *> ums_sPtr;
      // for(auto &b:a){
    //     for(auto &c:b.first){cout << c << " ";}
    //     cout << b.second << endl;
    // }

     // for(auto &check:finalItemSet){
    //     vp_vci fp(Chars.size());
    //     loop(i,0,Chars.size()){
    //         vp_vci fip; //frequent_items_pair;
    //         fip = trie.iterTrie(check.second,Chars[i],fip);
    //         cfpi[Chars[i]] = fip;
    //     }
        
    // }
