#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class LargeNumber
{
private:
    vector <char> numberContainer;
public:
    LargeNumber(){}
    void setValue(string s);
    int getValueUsingIndex(int index);
    void addNewMostSignificantDigit(char val);
    void changeDigit(int index,char val);
    int numberOfDigits();
    void print();
    LargeNumber helpAddOperation(LargeNumber x,LargeNumber y);
    LargeNumber addOperation(LargeNumber x,LargeNumber y);
};

/*class BigNumberOperatin
{
public:
    BigNumberOperatin();
    LargeNumber helpAddOperation(LargeNumber x,LargeNumber y);
    LargeNumber addOperation(LargeNumber x,LargeNumber y);
};*/

int main()
{
    string m = "1234567890";
    LargeNumber trial1;
    LargeNumber trial2;

    trial1.setValue(m);
    m = "9871236540";
    trial2.setValue(m);
    LargeNumber trial3;
    trial3= trial3.addOperation(trial1,trial2);
    int mm=9;
    char h= mm+'0';
    string sss = static_cast<ostringstream*>( &(ostringstream() << mm) )->str();

    int g=trial1.getValueUsingIndex(22);
    vector <char> hi;
    for (int var = 0; var < 10; ++var) {
       hi.push_back(var);
    }
    hi.size();
    cout<< g<< " "<<sss<<endl;
    trial3.print();

    return 0;
}



//  LargeNumber functions implementation
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
        return numberContainer[index];
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
void LargeNumber::print(){
    for (int i=numberContainer.size()-1;i>=0;i--)
    {
        cout << numberContainer[i];
    }
}

// add: z=x+y :: 2 functions
// helpAddOperation fn just we call it in (addOperation) fn
LargeNumber LargeNumber::helpAddOperation(LargeNumber x,LargeNumber y){
    LargeNumber z;
    int carry=0;
    int tempInt;
    for (int i = 0; i < y.numberOfDigits(); i++) // we use y.numberOfDigits() not y.numberOfDigits()-1  if there is a (carry) in last step
    {
        string tempString;
        tempInt=x.getValueUsingIndex(i)+y.getValueUsingIndex(i)+carry;
         if (tempInt > 9)
         {
              tempInt -= 10;
              carry = 1;
              tempString = static_cast<ostringstream*>( &(ostringstream() << tempInt) )->str();;
              z.setValue(tempString);
         }
         else
         {
             carry = 0;
             tempString = static_cast<ostringstream*>( &(ostringstream() << tempInt) )->str();;
             z.setValue(tempString);
         }
    }
    return z;
}
LargeNumber LargeNumber::addOperation(LargeNumber x,LargeNumber y){
    LargeNumber z;
    if (y.numberOfDigits()>=x.numberOfDigits())
    {
        z= helpAddOperation(x,y);
    }
    else z= helpAddOperation(y,x);  // x > y in digits

    return z;

}
