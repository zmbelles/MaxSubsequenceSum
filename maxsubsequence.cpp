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
    int sum;
    int currentNum;
public:
    NumberFile(ifstream file){
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
    void execute();
};

void NumberFile::execute(){
    for(int i=1; i<listOfNumbers.size(); i++){
        for(int j=0;j<i; j++){
            if(listOfNumbers[j]<listofNumbers[i]){
                int tmp=max_value[j]+listOfNumbers[i];
                if(tmp>max_value[i]){
                    max_value[i]=tmp;
                    actual_sequence[i]=j;
                }
            }
        }
    }
}


int main(){
    cout << "please enter the name of the number file" << endl;
    string fileName;
    cin >> fileName;
    ifstream sequenceFile(fileName);
    NumberFile n = new NumberFile(sequenceFile);
}