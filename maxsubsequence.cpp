#include<iostream>
#include<vector>

using namespace std;

class Subsequence{
private:
    friend class SubsequenceContainer;
    vector<int> subsequenceNumber;
    vector<int> subsequenceLIS;
    int size;
public:
    Subsequence();
    Subsequence(Subsequence &);
    void add(int,int);
    void print();
    bool find(int n);
};
Subsequence::Subsequence(){
    size=0;
}
bool Subsequence::find(int n){
    for(int i=0; i<subsequenceNumber.size();i++){
        if(subsequenceNumber[i]==n){
            return true;
        }
    }
    return false;
}
void Subsequence::print(){
    for(int i=subsequenceNumber.size(); i>=0; i--){
        cout << "Number: " << subsequenceNumber[i] << endl;
    }
    cout << endl;
}
void Subsequence::add(int num,int index){
    subsequenceNumber.push_back(num);
    subsequenceLIS.push_back(index);
    size++;
}
Subsequence::Subsequence(Subsequence &s){
    for(int i=0; i<subsequenceNumber.size(); i++){
        s.subsequenceLIS[i] = this->subsequenceLIS[i];
        s.subsequenceNumber[i] = this->subsequenceNumber[i];
        size++;
    }
}

class SubsequenceContainer{
private:
    friend class Subsequence;
    vector<Subsequence*> allMaxSubsequences;
    vector<int> arr;
    vector<int> LIS;
public:
    SubsequenceContainer(vector<int> v);
    void addSubsequence(Subsequence*& s){allMaxSubsequences.push_back(s);}
    void updateAllSubsequences(int, int);
    int findMaxLength();
    void execute(int);
    void print();
};
void SubsequenceContainer::execute(int longestSize){
    int target = longestSize;
    for(int i=arr.size()-1;i>0;i--){
        int thisNum = arr[i];
        if(LIS[i]==target){
            if(!allMaxSubsequences.empty()){
                vector<Subsequence*>::iterator sitr;
                for(sitr=allMaxSubsequences.begin();sitr!=allMaxSubsequences.end();sitr++){
                    int lastNum = (*sitr)->subsequenceNumber.back();
                    int lastLIS = (*sitr)->subsequenceLIS.back();
                    if(thisNum<lastNum && LIS[i]<lastLIS){
                        (*sitr)->add(thisNum, LIS[i]);
                        target--;
                    }
                    else if(thisNum>lastNum && LIS[i]==lastLIS){
                        Subsequence* s = new Subsequence();
                        for(int i=0;i<(*sitr)->subsequenceNumber.size()-1;i++){
                            s->add((*sitr)->subsequenceNumber[i],(*sitr)->subsequenceLIS[i]);
                        }
                        s->add(thisNum,LIS[i]);
                        allMaxSubsequences.push_back(s);
                    }
                }
            }
            else{
                Subsequence* s = new Subsequence();
                int n = LIS[i];
                s->add(thisNum, n);
                allMaxSubsequences.push_back(s);
                target--;
            }
        }
        else if(LIS[i]==longestSize){
            Subsequence* s = new Subsequence();
            int n = LIS[i];
            s->add(thisNum, n);
            allMaxSubsequences.push_back(s);
        }
    }
    
}
SubsequenceContainer::SubsequenceContainer(vector<int> v){
    for(int i=0;i<v.size();i++){
        arr.push_back(v[i]);
        LIS.push_back(1);
    }
}
void SubsequenceContainer::updateAllSubsequences(int num, int index){
    vector<Subsequence*>::iterator vitr;
    for(vitr=allMaxSubsequences.begin(); vitr!=allMaxSubsequences.end(); vitr++){
        int lastNum = (*vitr)->subsequenceNumber.back();
        int lastIndex = (*vitr)->subsequenceLIS.back();
        if(num<lastNum&&index<lastIndex){
            (*vitr)->add(num, index);
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
    return max;
}
void SubsequenceContainer::print(){
    vector<Subsequence*>::iterator sitr;
    int NumofSums = 0;
    for(sitr=allMaxSubsequences.begin();sitr!=allMaxSubsequences.end();sitr++){
        cout << "Max Sequence #" << NumofSums << endl;
        NumofSums++;
        (*sitr)->print();
    }
}
int main(){
    vector<int> arr = {186, 359, 274, 927, 890, 520, 571, 310, 916, 798, 732, 23, 196, 579,
426, 188, 524, 991, 91, 150, 117, 565, 993, 615, 48, 811, 594, 303, 191,
505, 724, 818, 536, 416, 179, 485, 334, 74, 998, 100, 197, 768, 421,
114, 739, 636, 356, 908, 477, 656};
    SubsequenceContainer sc(arr);
    int max = sc.findMaxLength();
    sc.execute(max);
    sc.print();
    return 0;
}