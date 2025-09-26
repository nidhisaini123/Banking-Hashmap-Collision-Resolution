#include "CubicProbing.h"
using namespace std;

CubicProbing::CubicProbing(){
    num_of_account = 0;
    prime = 200017;
    Account A;
    A.id = ""; 
    A.balance = -1;
    for(int i=0; i<prime; i++){
        bankStorage1d.push_back(A);
    }
}

CubicProbing::~CubicProbing(){
    bankStorage1d.clear();
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

void CubicProbing::createAccount(std::string id, int count) {
    int slot = hash(id);
    int f = slot;
    int i=1;
    while(bankStorage1d[slot].balance != -1){
        slot = (f + i*i*i)%prime;
        i++;
    }
    bankStorage1d[slot].id = id;
    bankStorage1d[slot].balance = count;
    num_of_account++;
}

std::vector<int> CubicProbing::getTopK(int k) {
    vector<int> temp;
    for(int i=0; i<bankStorage1d.size(); i++){
        if(bankStorage1d[i].balance != -1){
            temp.push_back(bankStorage1d[i].balance);
        }
    }
    MergeSort(temp, 0, temp.size()-1);

    vector<int> TopK;
    int a=temp.size()-1;
    for(int i=0; i<k; i++){
        TopK.push_back(temp[a-i]);
    }
    temp.clear();
    return TopK;
}

int CubicProbing::getBalance(std::string id) {
    if(doesExist(id)){
        int slot = hash(id);
        int i=0;
        while(bankStorage1d[(slot+i*i*i)%prime].id != id) {    //overflow
            i++;
        }
        return bankStorage1d[(slot+i*i*i)%prime].balance; //overflow
    }
    else{
        return -1;
    }
}

void CubicProbing::addTransaction(std::string id, int count) {
    if(doesExist(id)){
        int slot = hash(id);
        int initial_slot = hash(id);
        int j=1;
        while(bankStorage1d[slot % prime].id != id){
            slot = initial_slot + j*j*j;  // may have an overflow
            j++;
        }
        bankStorage1d[slot%prime].balance += count;
    }
    else{
        createAccount(id,count);
    }
}

bool CubicProbing::doesExist(std::string id) { // can be optimised
    int slot = hash(id);
    for(int i=0; i<=bankStorage1d.size(); i++){
        if(bankStorage1d[(slot+i)%prime].id == id) {
            return true;
        }
    }
    return false;
}

bool CubicProbing::deleteAccount(std::string id) { // can mark deleted as -2
    if(doesExist(id)){
        int slot = hash(id);
        int i=0;
        while(bankStorage1d[(slot+i*i*i)%prime].id != id) {
            i++;
        }
        bankStorage1d[(slot+i)%prime].balance = -1;
        bankStorage1d[(slot+i)%prime].id = "";
        num_of_account--;
        return true;
    }
    else{
        return false;
    }
}

int CubicProbing::databaseSize() {
    return num_of_account;
}



int CubicProbing::hash(std::string id) {
    // long long slot=0;
    // for(int i=0; i<id.size(); i++){
    //     int h = int(id[i])-'0'+1;
    //     slot = (slot + h*(i*i))%prime;
        
    // }
    // return slot;
    long long val=0;
    for(int i=0;i<id.size();i++){
        long long h=1;
        for(int j=1; j<=i; j++){
            h = h*2;
        }
        val=(val + h*(int(id[i])-'0'+1))%prime;
    }
    return val;
}

