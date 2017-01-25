#include <iostream>
#include <vector>
#include <string>
using namespace std;

class LargeNumber
{
private:
    vector <char> numberContainer;
    //int numberOfDigits;

public:
    LargeNumber(){numberOfDigits=0;}
    void setValue(string s);  //
    int getValueUsingIndex(int index);
    void addNewMostSignificantDigit(char val);
    void changeDigit(int index,char val);
    int numberOfDigits();
};

int main()
{
    string m = "1234567890";
    LargeNumber trial_;
    trial_.setValue(m);
    int mm=1;
    char h= (char)mm;
    int g=trial_.getValueUsingIndex(10);
    vector <char> hi;
    for (int var = 0; var < 10; ++var) {
       hi.push_back(var);
    }
    hi.size();
    cout<< h<< " "<<hi.size()<<endl;

    return 0;
}



// the functions
void LargeNumber::setValue(string s)
{
    for (int i=s.size()-1;i>=0;i--)
    {
        numberContainer.push_back(s[i]);
    }
}
int LargeNumber::getValueUsingIndex(int index)
{
    if (index >=0 && index < numberContainer.size())
    {
        int temp = numberContainer[index]-'0';  // '0'=(-48) to convert from ascii to int values
        return temp;
    }
    else
        return -1;
}
void LargeNumber::addNewMostSignificantDigit(char val)
{
    numberContainer.push_back(val);
}
void LargeNumber::changeDigit(int index,char val)
{
    numberContainer[index]=val;
}
int LargeNumber::numberOfDigits(){
    return numberContainer.size();
}

/*mySign = positive;
myDigits.resize(1);
myDigits[0] = '0';
myNumDigits = 1;*/

