#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
using namespace std;
//test
class NumberFile{
private:
    vector<int> listOfNumbers;
    vector<int> max_value;
    vector<int> actual_sequence;
    vector<int> sub_sequence;
    int sum;
    int currentNum;
public:
    NumberFile(ifstream& file){
        int nextNum;
        file >> nextNum;
        int i=0;
        while(!file.eof()){
            listOfNumbers.push_back(nextNum);
            max_value.push_back(nextNum);
            actual_sequence.push_back(i);
            file >> nextNum;
            i++;
        }
        
        
    }
    int execute();
    void print();
    void decode(int index);
};

int NumberFile::execute(){
    int overallMax = listOfNumbers[0];
    int overallMaxIndex = 0;
    for(int i=1; i<listOfNumbers.size(); i++){
        for(int j=0;j<i; j++){
            if(listOfNumbers[j]<listOfNumbers[i]){
                int tmp=max_value[j]+listOfNumbers[i];
                if(tmp>max_value[i]){
                    max_value[i]=tmp;
                    actual_sequence[i]=j;
                }
                if(max_value[i] > overallMax){
                    overallMax = max_value[i];
                    overallMaxIndex = i;
                }
            }
        }
    }
    return overallMaxIndex;
}

void NumberFile::print(){
    for(int i = 0; i < listOfNumbers.size(); i++){
        cout << listOfNumbers[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < max_value.size(); i++){
        cout << max_value[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < actual_sequence.size(); i++){
        cout << actual_sequence[i] << " ";
    }
    cout << endl;
}

void NumberFile::decode(int index){
    sub_sequence.push_back(listOfNumbers[index]);
    int target = actual_sequence[index];
    int new_target = actual_sequence[target];
    while(target!= new_target){
        sub_sequence.push_back(listOfNumbers[target]);
        target = actual_sequence[target];
    }
    sub_sequence.push_back(listOfNumbers[new_target]);
    cout << "Maximum Subsequence: " << endl;
    for(int i = sub_sequence.size() - 1; i >= 0; i--){
        cout << sub_sequence[i] << " ";
    }
    
}


int main(){
    int maxIndex;
    cout << "please enter the name of the number file" << endl;
    string fileName;
    cin >> fileName;
    ifstream sequenceFile(fileName);
    NumberFile n(sequenceFile);
    n.print();
    cout << endl;
    maxIndex = n.execute();
    n.print();
    n.decode(maxIndex);
    return 0;
}