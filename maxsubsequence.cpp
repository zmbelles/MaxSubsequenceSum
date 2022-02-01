#include<iostream>
#include<vector>

using namespace std;
//class to keep each longest subsequence
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
//initialize the size to 0 when object is created
Subsequence::Subsequence(){
    size=0;
}
//pre: a numbe to find inside the subsequenceNumber Vector
//post: returns true if it is found, false if not
//@param n: then number to find inside the array
bool Subsequence::find(int n){
    for(int i=0; i<subsequenceNumber.size();i++){
        if(subsequenceNumber[i]==n){
            return true;
        }
    }
    return false;
}
//go through all of the indexes of the subsequenceNumber vector and print them to the console
void Subsequence::print(){
    for(int i=subsequenceNumber.size(); i>=0; i--){
        cout << "Number: " << subsequenceNumber[i] << endl;
    }
    cout << endl;
}
//pre: a number and index to be added to their respective vectors
//post: both numbers have been pushed back onto their respective vectors
void Subsequence::add(int num,int index){
    subsequenceNumber.push_back(num);
    subsequenceLIS.push_back(index);
    size++;
}
//pre: an object to be copied, an empty object
//post: a new object has been created and is a deep copy of another
Subsequence::Subsequence(Subsequence &s){
    for(int i=0; i<subsequenceNumber.size(); i++){
        s.subsequenceLIS[i] = this->subsequenceLIS[i];
        s.subsequenceNumber[i] = this->subsequenceNumber[i];
        size++;
    }
}
//class to store all of the subsequences and to execute the neccesary code to print them out
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
//pre: a filled arr and LIS vector
//post: allMaxSubsequences has been updated with all longest subsequences
void SubsequenceContainer::execute(int longestSize){
    int target = longestSize;
    //loop through all array elements
    for(int i=arr.size()-1;i>0;i--){
        int thisNum = arr[i];
        //if the current LIS is what we are looking for
        if(LIS[i]==target){
            if(!allMaxSubsequences.empty()){
                vector<Subsequence*>::iterator sitr;
                //check the current number against the last number stored in each Subsequence* subsequenceNumber vector
                for(sitr=allMaxSubsequences.begin();sitr!=allMaxSubsequences.end();sitr++){
                    int lastNum = (*sitr)->subsequenceNumber.back();
                    int lastLIS = (*sitr)->subsequenceLIS.back();
                    int thisLIS = LIS[i];
                    //add thisNum to the vector if it is less than the last number AND its LIS value is lower than it
                    if(thisNum<lastNum && thisLIS<lastLIS){
                        (*sitr)->add(thisNum, thisLIS);
                        target--;
                    }
                    
                    //create a new Subsequence* if thisNum is greater than the last num in the subsequenceNumber vector, AND 
                    // both of those numbers LIS values are equal
                    //copy all but the last element from the (*sitr)->subsequenceNum vector to s*
                    //push back thisNum and thisLIS to their respective vectors
                    //push the s* onto allMaxSubsequences
                    else if(thisNum>lastNum && thisLIS==lastLIS){
                        Subsequence* s = new Subsequence();
                        for(int i=0;i<(*sitr)->subsequenceNumber.size()-1;i++){
                            s->add((*sitr)->subsequenceNumber[i],(*sitr)->subsequenceLIS[i]);
                        }
                        s->add(thisNum,thisLIS);
                        allMaxSubsequences.push_back(s);
                    }
                }
            }
            //if there allMaxSubsequences is empty, push thisNum onto it
            else{
                Subsequence* s = new Subsequence();
                int n = LIS[i];
                s->add(thisNum, n);
                allMaxSubsequences.push_back(s);
                target--;
            }
        }
        //create a new Subsequence* and push it onto the allMaxSubsequences vector if its LIS value is also the highest but not the current
        else if(LIS[i]==longestSize){
            Subsequence* s = new Subsequence();
            int n = LIS[i];
            s->add(thisNum, n);
            allMaxSubsequences.push_back(s);
        }
    }
}
//default constructor to populate the LIS and arr vectors
SubsequenceContainer::SubsequenceContainer(vector<int> v){
    for(int i=0;i<v.size();i++){
        arr.push_back(v[i]);
        LIS.push_back(1);
    }
}
//find and populate the proper LIS values in the LIS vector
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
//go through each Subsequence* inside the allMaxSubsequences vector and print out their subsequences
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
    vector<int> arr = {18,35,92,55,52,57,31,91,79,73};
    SubsequenceContainer sc(arr);
    int max = sc.findMaxLength();
    sc.execute(max);
    sc.print();
    return 0;
}
