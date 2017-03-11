#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <bitset>
#include <time.h>
#include <limits>
using namespace std;
class BigNum
{
public:
	BigNum() {};
	BigNum(string s);
	BigNum(const unsigned long long  &s);
	BigNum(vector <unsigned long long> &v);
	void setValue(string s);//in case pass ( string ): in the initial state
	void setValue(unsigned long long s);//  in case pass (number) to use it in the operation
	void setValueUsingVector(vector <unsigned long long> n);
	vector <unsigned long long> getVectorContainer();
	void addNewMostSignificantDigit(unsigned long long val);
	void changeDigit(int index, unsigned long long val);
	int numberOfDigits()const;
	void editSpecificIndex(unsigned long long newValue, int index);
	unsigned long long getLastDigit();
	BigNum getSomeDigitsFromMostSignificant(int numOfdigits);
	string convertLongToString(unsigned long long mylong);
	string convertBigNumToString();
	
	// comprason
	bool greaterThan(BigNum x);
	bool greaterThan(int x);
	bool greaterThanOrEqual(BigNum x);
	bool equal(const BigNum &x);
	bool equal(int x);

	// operations
	BigNum addOperation(const BigNum & x);
	BigNum addOperation(vector <unsigned long long> num);
	BigNum subOperation(BigNum x);
	BigNum subOperation(vector <unsigned long long> num);
	BigNum subOperation(int num);
	void mul_base_shift();
	BigNum modOperation(BigNum denominator);
	BigNum modOperation2(BigNum &denominator);

	void operator=(const BigNum &m);
	void removeLeadingZero();
	void print();
	
	
	
	
	
	
private:
	vector <unsigned long long> numberContainer;
};

BigNum::BigNum(string s) {
	string temp;
	int counter = 0;
	for (int i = s.size() - 1;i >= 0;i = i - 9)
	{

		if (i >= 9) {
			temp = s.substr(i - 8, 9);
			numberContainer.push_back(stoull(temp));
			counter++;
		}
		else {
			temp = s.substr(0, s.size() - counter * 9);
			numberContainer.push_back(stoull(temp));
		}
	}

}
BigNum::BigNum(const unsigned long long &s) {
	if (s <= 999999999)
		numberContainer.push_back(s);
	else
	{
		numberContainer.push_back(s % 1000000000);
		numberContainer.push_back((s - numberContainer[0]) / 1000000000);
	}
}
BigNum::BigNum(vector <unsigned long long> &v) {
	numberContainer = v;
}

void BigNum::setValue(string s) {
	string temp;
	int counter = 0;
	for (int i = s.size() - 1;i >= 0;i = i - 9)
	{

		if (i >= 9) {
			temp = s.substr(i - 8, 9);
			numberContainer.push_back(stoull(temp));
			counter++;
		}
		else {
			temp = s.substr(0, s.size() - counter * 9);
			numberContainer.push_back(stoull(temp));
		}
	}
}
void BigNum::setValue(unsigned long long s)
{
	numberContainer.push_back(s);
}
void BigNum::setValueUsingVector(vector <unsigned long long> n) { numberContainer = n; }
vector <unsigned long long> BigNum::getVectorContainer() { return numberContainer; }
void BigNum::addNewMostSignificantDigit(unsigned long long val)
{
	numberContainer.push_back(val);
}
void BigNum::changeDigit(int index, unsigned long long val)
{
	numberContainer[index] = val;
}
int BigNum::numberOfDigits()const{
	return numberContainer.size();
}
void BigNum::editSpecificIndex(unsigned long long newValue, int index) {
	numberContainer[index] = newValue;
}
// after writing it--> i discovered : to_string funcion in c++11
string BigNum::convertLongToString(unsigned long long mylong) {
	string mystring;
	stringstream mystream;
	mystream << mylong;
	mystring = mystream.str();
	return mystring;
}
string BigNum::convertBigNumToString() {
	string mystring;
	string temp;
	int numOfDigit = numberContainer.size()-1;
	int numOfLeadingZero;
	bool firstTime = true;
	while (numOfDigit >=0 )
	{
		stringstream mystream;
		mystream << numberContainer[numOfDigit];
		temp = mystream.str();
		numOfLeadingZero = temp.size();
		// if there is leading zero
		if (firstTime) { firstTime = false; goto firstOnly; }
		while (9-numOfLeadingZero > 0)
		{
			mystring = mystring + '0' ;
			numOfLeadingZero++;
		}
		firstOnly:
		mystring = mystring + mystream.str();
		numOfDigit--;
	}
	return mystring;
}


// comparason
bool BigNum::greaterThan(BigNum x) {
	if (this->numberOfDigits() > x.numberOfDigits()) return true;
	else if (this->numberOfDigits() < x.numberOfDigits()) return false;
	else // here numberOfDigits()-->(=)
	{
		for (int i = numberOfDigits() - 1; i >= 0; i--)
		{
			if (this->numberContainer[i] > x.numberContainer[i]) return true;
			else if (this->numberContainer[i] == x.numberContainer[i]) continue;
			else return false;
		}
		return false; // this for equality
	}
}
bool BigNum::greaterThan(int x) {
	if (numberContainer.size() > 1) return true;
	if (numberContainer.size() == 1 && (numberContainer[0] > x)) return true;
	return false;
}
bool BigNum::greaterThanOrEqual(BigNum x) {
	if (this->numberOfDigits() > x.numberOfDigits()) return true;
	else if (this->numberOfDigits() < x.numberOfDigits()) return false;
	else // here numberOfDigits()-->(=)
	{
		for (int i = numberOfDigits() - 1; i >= 0; i--)
		{
			if (this->numberContainer[i] > x.numberContainer[i]) return true;
			else if (this->numberContainer[i] == x.numberContainer[i]) continue;
			else return false;
		}
		return true; // this for equality
	}
}
bool BigNum::equal(const BigNum &x) {
	if (this->numberOfDigits() > x.numberOfDigits()) return false;
	else if (this->numberOfDigits() < x.numberOfDigits()) return false;
	else // here numberOfDigits()-->(=)
	{
		for (int i = numberOfDigits() - 1; i >= 0; i--)
		{
			if (this->numberContainer[i] > x.numberContainer[i]) return false;
			else if (this->numberContainer[i] == x.numberContainer[i]) continue;
			else return false;
		}
		return true; // this for equality
	}
}
bool BigNum::equal(int x) {
	if (numberContainer.size() == 1 && numberContainer[0] == x)
		return true;
	return false;
}


// operations
BigNum BigNum::addOperation(const BigNum & x) {
	BigNum z ;
	int carry = 0;
	unsigned long long  tempInt;
	// to check which has max digits
	int minDigit , maxDigit_, yDigit = numberContainer.size(),xDigit=x.numberContainer.size();
	// y -> this and x is x
	
	if (yDigit <= xDigit) minDigit = yDigit , maxDigit_=xDigit ;
	else	minDigit = xDigit , maxDigit_ = yDigit;
	z.numberContainer.reserve(  maxDigit_ + 1);
	int i;
	for (i = 0; i < maxDigit_   ; i++) // we use maxDigit+1 not maxDigit:--> if there is a (carry) in last step
	{
		
		if (i < minDigit) tempInt = this->numberContainer[i] + x.numberContainer[i]+ carry;
		else if (carry == 0) { z.numberContainer.push_back(numberContainer[i]); continue; }
		else tempInt = this->numberContainer[i] + carry;
		if (tempInt > 999999999)
		{
			tempInt -= 1000000000;// 1 200 000 000 - 1 000 000 000 = 200 000 000
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		z.numberContainer.push_back(tempInt);
		if (i+1 == maxDigit_ && carry == 1) maxDigit_++;
	}
	return z;
}
unsigned long long BigNum::getLastDigit() {
	return numberContainer[numberContainer.size() - 1];
}
BigNum BigNum::getSomeDigitsFromMostSignificant(int numOfdigits) {
	if (numOfdigits == 1)
	{
		unsigned long long  tempInt = getLastDigit();
		BigNum temp;temp.setValue(tempInt);
		return temp;
	}
	if (this->numberOfDigits() <= numOfdigits) return *this;
	BigNum temp;
	vector<unsigned long long>thisContainer;thisContainer = this->getVectorContainer();int index = thisContainer.size() - 1;
	vector<unsigned long long>tempContainer;	tempContainer.resize(numOfdigits);
	while (numOfdigits != 0)
	{
		tempContainer[numOfdigits - 1] = thisContainer[index];
		index--;
		numOfdigits--;
	}
	temp.setValueUsingVector(tempContainer);
	return temp;
}


BigNum BigNum::addOperation(vector <unsigned long long> num)
{
	BigNum z; 
	unsigned long long carry = 0;
	unsigned long long  tempInt;
	// to check which has max digits
	int maxDigit;
	if (this->numberOfDigits() >= num.size()) maxDigit = this->numberOfDigits();
	else								  maxDigit = num.size();
	for (int i = 0; i < maxDigit + 1; i++) // we use maxDigit+1 not maxDigit:--> if there is a (carry) in last step
	{
		if (i == maxDigit && carry == 0) return z; // to not print leading zero
		tempInt = this->numberContainer[i] + num[i] + carry;
		if (tempInt > 999999999)
		{
			tempInt -= 1000000000;// 1 200 000 000 - 1 000 000 000 = 200 000 000
			carry = 1;
		}
		else carry = 0;
		z.setValue(tempInt);
	}
	return z;
}
BigNum BigNum::subOperation(BigNum x) {
	// let (this > x) this greater than x
	if (this->equal(x))
	{
		BigNum result(0);
		return result;
	}
	BigNum thisCopy = *this;
	BigNum result;
	unsigned long long carry;
	unsigned long long tempInt;
	int maxDigit = numberContainer.size();
	for (int i = 0; i < maxDigit; i++)
	{
		if (thisCopy.numberContainer[i] >= x.numberContainer[i])
			tempInt = thisCopy.numberContainer[i] - x.numberContainer[i];
		else
		{
			// borrow from next digit
			thisCopy.editSpecificIndex(thisCopy.numberContainer[i + 1] - 1, i + 1);
			carry = 1000000000;
			tempInt = (carry + thisCopy.numberContainer[i]);
			tempInt -= x.numberContainer[i];
		}
		result.numberContainer.push_back(tempInt);
	}
	result.removeLeadingZero();
	return result;
}
BigNum BigNum::subOperation(vector <unsigned long long> num) {
	// let (this > x) this greater than x
	BigNum thisCopy = *this;
	BigNum result;
	unsigned long long carry;
	unsigned long long tempInt;
	//if (this->numberOfDigits() >= num.size()) maxDigit = this->numberOfDigits();
	//else								  maxDigit = num.size();
	for (int i = 0; i < this->numberOfDigits(); i++)
	{
		if (i < num.size())
		{
			if (thisCopy.numberContainer[i] >= num[i])
				tempInt = thisCopy.numberContainer[i] - num[i];
			else
			{
				// borrow from next digit
				thisCopy.editSpecificIndex(thisCopy.numberContainer[i + 1] - 1, i + 1);
				carry = 1000000000;
				tempInt = (carry + thisCopy.numberContainer[i]);
				tempInt -= num[i];
			}
		}
		else tempInt = thisCopy.numberContainer[i];
		result.numberContainer.push_back(tempInt);
	}
	result.removeLeadingZero();
	return result;
}
BigNum BigNum::subOperation(int num) {
	// let (this > x) this greater than x
	BigNum thisCopy = *this;
	int index = 1;
	while (true)
	{
		if (thisCopy.numberContainer[0] >= num)
		{
			thisCopy.numberContainer[0] -= num; break;
		}
		else
		{
			if (thisCopy.numberContainer[index] > 0)
				thisCopy.numberContainer[index] -= 1, thisCopy.numberContainer[index - 1] += 1000000000;
			index++;
		}
	}
	return thisCopy;
}
void BigNum::mul_base_shift()
{
	vector<unsigned long long>::iterator it;
	it = numberContainer.begin();
	it = numberContainer.insert(it, 0);
}
BigNum BigNum::modOperation(BigNum denominator) {
	if (denominator.greaterThan(*this)) return *this;
	if (this->equal(denominator)) {	BigNum res(0); return res;	}
	string numinatorString = this->convertBigNumToString();
	BigNum result;
	int iterationNum = numberContainer.size()-1;
	bool flagFirstIteration = true;
	while (iterationNum >= 0)
	{
		if (flagFirstIteration) {
			result = numberContainer[iterationNum];
			flagFirstIteration = false;
		}
			
		else
		{
			result.mul_base_shift();
			result = result.addOperation(numberContainer[iterationNum]);
		}
		while (result.greaterThanOrEqual(denominator))
		{
			result = result.subOperation(denominator);
		}
		iterationNum--;
	}
	return result;
}
BigNum BigNum::modOperation2(BigNum &denominator)
{
	if (this->equal(denominator))
	{
		BigNum result; result.setValue(0);
		return result;
	}
	if (denominator.greaterThan(*this)) return *this;
	BigNum numinator = *this; // it is updated each iteration in the operation main loop
	BigNum rem; //remainder

	vector<BigNum>multiplesOfDenominator; multiplesOfDenominator.reserve(4);
	//multiplesOfDenominator			   
	// push  1x, 2x , 4x , 8x
	multiplesOfDenominator.push_back(denominator);

	int c = 2;
	while (c<10)// initialy 10^9
	{
		BigNum temp;temp.setValue(c);
		multiplesOfDenominator.push_back(denominator.mulOperation(temp));
		c *= 2;
	}
	while (true) {
		int index = -1;
		int tempInt = multiplesOfDenominator[0].numberOfDigits();
		BigNum temp = numinator.getSomeDigitsFromMostSignificant(tempInt);
		for (int i = 0; i < 4; i++)
		{
			if (temp.greaterThanOrEqual(multiplesOfDenominator[i]))
			{
				index = i;
			}
			else if (index == -1 && numinator.numberOfDigits() > denominator.numberOfDigits())
			{
				i = -1;
				temp = numinator.getSomeDigitsFromMostSignificant(tempInt + 1);
			}
		}
		//here there are 2 usage for (result) vector
		//first usage for result:
		vector <unsigned long long> result;//(numinator.numberOfDigits() - temp.numberOfDigits()); // initialize to zeros
										   // second usage for result:
		result = multiplesOfDenominator[index].getVectorContainer();
		numinator = numinator.subOperation(result);
		if (!numinator.greaterThan(denominator))
			return numinator;
	}
}


void BigNum::operator=(const BigNum &m) {
	numberContainer = m.numberContainer;
}
void BigNum::removeLeadingZero() {
	while (1) {
		if (numberContainer.back() == 0 && numberOfDigits()>1)
			numberContainer.pop_back();
		else break;
	}
}
void BigNum::print() {
	if (numberContainer.size() == 0) { cout << "empty number" << endl;return; }
	removeLeadingZero();
	int i = numberContainer.size() - 1;
	while (i != -1) {
		if (i == (numberContainer.size() - 1))
			cout << numberContainer[i];
		else
			cout << setfill('0') << setw(9) << numberContainer[i];
		i--;
	}
}
