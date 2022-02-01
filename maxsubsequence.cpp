#include<iostream>
#include<vector>

using namespace std;

class Subsequence{
private:
    friend class SubsequenceContainer;
    vector<int> subsequenceNumber;
    vector<int> subsequenceIndex;
    int size;
public:
    Subsequence();
    Subsequence(Subsequence &);
    void add(int,int);
    void print();
};
void Subsequence::print(){
    for(int i=0; i<subsequenceNumber.size(); i++){
        cout << "Number: " << subsequenceNumber[i] << endl;
        cout << "Index: " << subsequenceIndex[i] << endl;
    }
    cout << endl;
}
void Subsequence::add(int num,int index){
    subsequenceNumber.push_back(num);
    subsequenceIndex.push_back(index);
}
Subsequence::Subsequence(Subsequence &s){
    for(int i=0; i<subsequenceNumber.size(); i++){
        s.subsequenceIndex[i] = this->subsequenceIndex[i];
        s.subsequenceNumber[i] = this->subsequenceNumber[i];
        size++;
    }
}

class SubsequenceContainer{
private:
    friend class Subsequence;
    vector<Subsequence> allMaxSubsequences;
    vector<int> arr;
    vector<int> LIS;
public:
    SubsequenceContainer();
    void addSubsequence(Subsequence s){allMaxSubsequences.push_back(s);}
    void updateAllSubsequences(int, int);
    int findMaxLength();
    void print();
};
void SubsequenceContainer::updateAllSubsequences(int num, int index){
    vector<Subsequence>::iterator vitr;
    for(vitr=allMaxSubsequences.begin(); vitr!=allMaxSubsequences.end(); vitr++){
        int lastNum = vitr->subsequenceNumber.back();
        int lastIndex = vitr->subsequenceIndex.back();
        if(num<lastNum&&index<lastIndex){
            vitr->add(num, index);
        }
    }
}
int SubsequenceContainer::findMaxLength(){
    int max = 0;
    int index = 0;
    for(int i = 1; i < arr.size(); i++){
        for(int j = 0; j < i; j++){
            if(arr[i] > arr[j] && LIS[i] < LIS[j] + 1)
                LIS[i] = LIS[j] + 1;
                if(LIS[i] > max){
                    max = LIS[i];
                    index = i;
                }
        }
    }
    return index;
}
void SubsequenceContainer::print(){
    vector<Subsequence>::iterator sitr;
    int NumofSums = 0;
    for(sitr=allMaxSubsequences.begin();sitr!=allMaxSubsequences.end();sitr++){
        cout << "Max Sequence #" << NumofSums << endl;
        NumofSums++;
        sitr->print();
    }
}