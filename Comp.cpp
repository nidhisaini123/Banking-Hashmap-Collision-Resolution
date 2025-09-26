#include "Comp.h"

using namespace std;

Comp::Comp(){
    num_of_account = 0;
    prime = 200017;
    bankStorage2d.resize(prime);
    Account A;
    A.id = "";
    A.balance = -1;
    vector<Account> V = {A};
    for(int i=0; i<prime; i++){
        bankStorage2d[i] = V;
    }
}

Comp::~Comp(){
    for (int i = 0; i < bankStorage2d.size(); i++) {
        bankStorage2d[i].clear();
    }
    bankStorage2d.clear();
}

void Merge(vector<int>& V, int l, int m, int r) {
   
    int a = m-l+1;
    int b = r-m;
    vector<int> Left(a);
    vector<int> Right(b);

    for (int i = 0; i < a; i++){
        Left[i] = V[l + i];
    }
    for (int j = 0; j < b; j++){
        Right[j] = V[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < a && j < b) {
        if(Left[i] <= Right[j]){
            V[k] = Left[i];
            i++;
        } 
        else{
            V[k] = Right[j];
            j++;
        }
        k++;
    }

    while(i < a){
        V[k] = Left[i];
        i++;
        k++;
    }
    while(j < b){
        V[k] = Right[j];
        j++;
        k++;
    }
}


void MergeSort(vector<int>& V, int l, int r) {
    if (l<r) {
        int m = l+(r-l)/2;
        MergeSort(V, l, m);
        MergeSort(V, m + 1, r);
        Merge(V, l, m, r);
    }
}


void Comp::createAccount(std::string id, int count) {
    Account acc;
    acc.id = id;
    acc.balance = count;
    bankStorage2d[hash(id)].push_back(acc);
    num_of_account++;
}

std::vector<int> Comp::getTopK(int k) {
    vector<int> TopK;
    for (int i=0; i<bankStorage2d.size(); i++){
        for(int j=0; j<bankStorage2d[i].size(); j++){
            if(bankStorage2d[i][j].balance != -1){
                TopK.push_back(bankStorage2d[i][j].balance);
            }
        }
    }

    MergeSort(TopK, 0, TopK.size()-1);

    vector<int> Sorted;
    for(int i=0; i<k; i++){
        if(TopK[i] != -1){
            Sorted.push_back(TopK[TopK.size()-i-1]);
        }
    }
    TopK.clear();
    return Sorted;
}

int Comp::getBalance(std::string id) {
    if (doesExist(id)){
        int slot = hash(id);
        for (int j=0; j<bankStorage2d[slot].size(); j++){
            if(bankStorage2d[slot][j].id == id){
                return bankStorage2d[slot][j].balance;
            }
        }
    }
    return -1; 
}

void Comp::addTransaction(std::string id, int count) {
    if (doesExist(id)){
        int slot = hash(id);
        for (int j=0; j<bankStorage2d[slot].size(); j++){
            if(bankStorage2d[slot][j].id == id){
                bankStorage2d[slot][j].balance = bankStorage2d[slot][j].balance + count;
                break;
            }
        }
    }
    else{ 
        createAccount(id, count);
    }
}

bool Comp::doesExist(std::string id) {
    int slot = hash(id);
    for (int j=0; j<bankStorage2d[slot].size(); j++){
        if(bankStorage2d[slot][j].id == id){
            return true;
        }
    }
    return false;
}

bool Comp::deleteAccount(std::string id) {
    if(doesExist(id)){
        int slot = hash(id);
        for (int j=0; j<bankStorage2d[slot].size(); j++){
            if(bankStorage2d[slot][j].id == id){
                num_of_account--;
                bankStorage2d[slot][j].id = "";
                bankStorage2d[slot][j].balance = -1;
                return true;
            }
        }
    }
    return false; 
}
int Comp::databaseSize() {
    return num_of_account;
}



int Comp::hash(std::string id) {
    long long val=0;
    long long h=1;
    for(int i=0;i<id.size();i++){
        for(int j=1; j<=i; j++){
            h = h*2;
        }
        val=(val + h*(int(id[i])-'0'+1))%prime;
    }
    return val;
}


