//#include "bits/stdc++.h"
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
	string convertLongToString(unsigned long long mylong);
	string convertBigNumToString();
	void editSpecificIndex(unsigned long long newValue, int index);
	bool isEven();
	unsigned long long getLastDigit();
	BigNum getSomeDigitsFromMostSignificant(int numOfdigits);
	// comparison
	bool greaterThan(BigNum &x);
	bool greaterThan(int x);
	bool greaterThanOrEqual(BigNum &x);
	bool equal(const BigNum &x);
	bool equal(vector <unsigned long long> &x);
	bool equal(int x);

	// operations
	BigNum addOperation(const BigNum & x);
	BigNum addOperation(vector <unsigned long long> &num);
	BigNum addOperation_int(int x);
	BigNum subOperation(BigNum &x);
	BigNum subOperation(vector <unsigned long long> &num);
	BigNum subOperation(int num);
	BigNum subWithNegativeOperation(BigNum &x, BigNum &modd);
	BigNum mulOperation(const BigNum &x);
	BigNum divOperation(BigNum &denominator);
	BigNum divOperation2(BigNum denominator);
	BigNum binarySearchTesting(BigNum denominator, BigNum leftSide_, BigNum midd, BigNum rightSide_);
	BigNum divByTwo();
	void mul_base_shift();
	void mulWithTen();
	BigNum modOperation(BigNum &denominator);
	BigNum modOperation2(BigNum &denominator);
	BigNum powerOperation(BigNum &power, BigNum &modulus);
	bool isPrime(const int &numOfIterations);
	BigNum extendedEUCLID(BigNum &modd);

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
	numberContainer.clear();
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
int BigNum::numberOfDigits()const {
	return numberContainer.size();
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
	int numOfDigit = numberContainer.size() - 1;
	int numOfLeadingZero;
	bool firstTime = true;
	while (numOfDigit >= 0)
	{
		stringstream mystream;
		mystream << numberContainer[numOfDigit];
		temp = mystream.str();
		numOfLeadingZero = temp.size();
		// if there is leading zero
		if (firstTime) { firstTime = false; goto firstOnly; }
		while (9 - numOfLeadingZero > 0)
		{
			mystring = mystring + '0';
			numOfLeadingZero++;
		}
	firstOnly:
		mystring = mystring + mystream.str();
		numOfDigit--;
	}
	return mystring;
}
BigNum BigNum::addOperation(const BigNum & x) {
	BigNum  n1, n2;
	n1 = *this, n2 = x;
	int carry = 0;
	int n1NumOfDigit = numberContainer.size(), n2NumOfDigit = x.numberContainer.size();
	unsigned long long  tempInt;
	if (n2NumOfDigit > n1NumOfDigit) {
		n1.numberContainer.swap(n2.numberContainer);
	}
	//z.numberContainer.reserve(  n1NumOfDigit + 1);
	int i;
	for (i = 0; i < n1NumOfDigit; i++) // we use maxDigit+1 not maxDigit:--> if there is a (carry) in last step
	{
		if (i < n2NumOfDigit)
			tempInt = n1.numberContainer[i] + n2.numberContainer[i] + carry;
		else if (carry == 1) { tempInt = n1.numberContainer[i] + carry; }
		else break; // no more digits and carry = 0
		if (tempInt > 999999999)
		{
			tempInt -= 1000000000;// 1 200 000 000 - 1 000 000 000 = 200 000 000
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		n1.numberContainer[i] = tempInt;
	}
	if (carry) {
		n1.numberContainer.push_back(1);
	}
	return n1;
}
BigNum BigNum::addOperation(vector <unsigned long long> &num)
{
	BigNum  n1, n2(num);
	n1 = *this;
	int carry = 0;
	int n1NumOfDigit = numberContainer.size(), n2NumOfDigit = num.size();
	unsigned long long  tempInt;
	if (n2NumOfDigit > n1NumOfDigit) {
		n1.numberContainer.swap(n2.numberContainer);
	}
	//z.numberContainer.reserve(  n1NumOfDigit + 1);
	int i;
	for (i = 0; i < n1NumOfDigit; i++) // we use maxDigit+1 not maxDigit:--> if there is a (carry) in last step
	{
		if (i < n2NumOfDigit)
			tempInt = n1.numberContainer[i] + n2.numberContainer[i] + carry;
		else if (carry == 1) { tempInt = n1.numberContainer[i] + carry; }
		else break; // no more digits and carry = 0
		if (tempInt > 999999999)
		{
			tempInt -= 1000000000;// 1 200 000 000 - 1 000 000 000 = 200 000 000
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		n1.numberContainer[i] = tempInt;
	}
	if (carry) {
		n1.numberContainer.push_back(1);
	}
	return n1;
}
BigNum BigNum::addOperation_int(int x) {
	BigNum res = *this;
	res.numberContainer[0] += x;
	if (res.numberContainer[0] < 1000000000) return res;
	int index = 1;

	// first time will insert without checking, as i know there is a carry
	while (true)
	{
		res.numberContainer[index] += 1;
		if (res.numberContainer[index] > 999999999)
			res.numberContainer[index] -= 1000000000, index++;
		else return res;
	}
}
void BigNum::editSpecificIndex(unsigned long long newValue, int index) {
	numberContainer[index] = newValue;
}
BigNum BigNum::subOperation(BigNum &x) {
	// let (this > x) this greater than x
	if (this->equal(x))
	{
		BigNum result(0);
		return result;
	}
	BigNum result = *this;
	int minDigit = x.numberContainer.size();
	int index;
	for (int i = 0; i < minDigit; i++)
	{
		index = i + 1;
		while (true)
		{
			if (result.numberContainer[i] >= x.numberContainer[i])
			{
				result.numberContainer[i] -= x.numberContainer[i]; break;
			}
			// borrow from next digit
			else
			{
				if (result.numberContainer[index] > 0)
					while (index > i)
					{
						result.numberContainer[index] -= 1, result.numberContainer[index - 1] += 1000000000;
						index--;
					}
				index++;
			}
		}
	}
	result.removeLeadingZero();
	return result;
}
BigNum BigNum::subOperation(vector <unsigned long long> &num) {
	// let (this > x) this greater than x
	if (this->equal(num))
	{
		BigNum result(0);
		return result;
	}
	BigNum result = *this;
	int minDigit = num.size();
	int index;
	for (int i = 0; i < minDigit; i++)
	{
		index = i + 1;
		while (true)
		{
			if (result.numberContainer[i] >= num[i])
			{
				result.numberContainer[i] -= num[i]; break;
			}
			// borrow from next digit
			else
			{
				if (result.numberContainer[index] > 0)
					while (index > i)
					{
						result.numberContainer[index] -= 1, result.numberContainer[index - 1] += 1000000000;
						index--;
					}
				index++;
			}
		}
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
				while (index > 0)
				{
					thisCopy.numberContainer[index] -= 1, thisCopy.numberContainer[index - 1] += 1000000000;
					index--;
				}
			index++;
		}
	}
	return thisCopy;
}
BigNum BigNum::subWithNegativeOperation(BigNum &x, BigNum &modd) {
	// let (this > x) this greater than x
	if (this->equal(x))
	{
		BigNum result(0);
		return result;
	}
	BigNum result, num2;
	bool flag = false;
	if (this->greaterThan(x)) { result = *this; num2 = x; }
	else { result = x; num2 = *this; flag = true; }
	int minDigit = num2.numberContainer.size();
	int index;
	for (int i = 0; i < minDigit; i++)
	{
		index = i + 1;
		while (true)
		{
			if (result.numberContainer[i] >= num2.numberContainer[i])
			{
				result.numberContainer[i] -= num2.numberContainer[i]; break;
			}
			// borrow from next digit
			else
			{
				if (result.numberContainer[index] > 0)
					while (index > i)
					{
						result.numberContainer[index] -= 1, result.numberContainer[index - 1] += 1000000000;
						index--;
					}
				index++;
			}
		}
	}
	result.removeLeadingZero();
	if (flag)
	{
		result = result.modOperation(modd);
		result = modd.subOperation(result);
	}

	return result;
}
BigNum BigNum::mulOperation(const BigNum & x)
{
	BigNum result;
	int num1_digitsNum = x.numberOfDigits();
	int num2_digitsNum = numberContainer.size();
	//vector <unsigned long long> res(num1_digitsNum + num2_digitsNum);
	vector <unsigned long long> &res = result.numberContainer;
	res.resize(num1_digitsNum + num2_digitsNum);

	//#define OLD_MUL
#ifdef OLD_MUL

	unsigned long long carry = 0;

	for (int i = 0; i < num1_digitsNum; i++) // we use maxDigit+1 not maxDigit:--> if there is a (carry) in last step
	{
		for (int j = 0; j < num2_digitsNum; j++)
		{
			res[i + j] += (x.numberContainer[i] * this->numberContainer[j]);
			int counter = 0;

			while (res[i + j + counter] > 999999999)
			{
				carry = res[i + j + counter] / 1000000000;
				res[i + j + counter] -= (carry * (unsigned long long)1000000000);
				counter++;
				res[i + j + counter] += carry;
			}
		}
	}

#else
	unsigned long long carry = 0;
	unsigned long long tmp;
	for (int i = 0; i < num1_digitsNum; i++) // we use maxDigit+1 not maxDigit:--> if there is a (carry) in last step
	{
		carry = 0;
		for (int j = 0; j < num2_digitsNum; j++)
		{
			res[i + j] += (x.numberContainer[i] * this->numberContainer[j]) + carry;
			carry = res[i + j] / 1000000000;
			res[i + j] %= 1000000000;
		}
		res[i + num2_digitsNum] = carry;
	}
#endif
	result.removeLeadingZero();

	return result;
}

BigNum BigNum::divByTwo() {
	int counter = numberContainer.size() - 1;
	BigNum res;
	vector <unsigned long long> resVector;
	bool flag = false;
	unsigned long long temp;
	while (counter >= 0)
	{
		if (flag) {
			temp = numberContainer[counter] + 1000000000;
			resVector.push_back(temp / 2);
			if (temp % 2 == 0)
				flag = false;		// don't need to handle (else -> flag= True) because flag already at this time is equal true :D
		}
		else
		{
			temp = numberContainer[counter];
			resVector.push_back(temp / 2);
			if (temp % 2 == 1)
				flag = true;	// don't need to handle (else -> flag= false) because flag already at this time is equal false :D
		}
		counter--;
	}
	reverse(resVector.begin(), resVector.end());
	res.setValueUsingVector(resVector);
	res.removeLeadingZero();
	return res;
}
BigNum BigNum::powerOperation(BigNum &power, BigNum &modulus) {
	BigNum result(1);
	if (power.equal(0))
		return result;  // identity matrix
	else if (power.equal(1))
		return *this;
	BigNum multiplies = *this;
	while (1)
	{
		if (power.equal(1))
		{
			result = result.mulOperation(multiplies).modOperation(modulus);
			break;
		}
		else if (!power.isEven())
		{
			result = result.mulOperation(multiplies).modOperation(modulus);
		}
		multiplies = multiplies.mulOperation(multiplies);
		multiplies = multiplies.modOperation(modulus);
		power = power.divByTwo();
		//power.print();cout << endl;
	}
	return result;
}
/*
//function Matrix_ModExp(Matrix A, int b, int c)
// if (b == 0):
//     return I  // The identity matrix
//if (b mod 2 == 1):
//return (A * Matrix_ModExp(A, b - 1, c)) mod c
Matrix D := Matrix_ModExp(A, b / 2, c)
return (D * D) mod c
*/
//A^b mod c
/*
Function exp_by_squaring(x, n, mod)
if n < 0  then return exp_by_squaring(1 / x, -n);
else if n = 0  then return  1;
else if n = 1  then return  x ;
else if n is even  then return exp_by_squaring(x * x,  n / 2);
else if n is odd  then return x * exp_by_squaring(x * x, n / 2);
*/
bool BigNum::isEven() {
	if (numberContainer[0] & 1)
		return false;
	return true;
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
bool BigNum::greaterThan(BigNum &x) {
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
bool BigNum::greaterThanOrEqual(BigNum &x) {
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
bool BigNum::equal(vector <unsigned long long> &x) {
	if (this->numberOfDigits() > x.size()) return false;
	else if (this->numberOfDigits() < x.size()) return false;
	else // here numberOfDigits()-->(=)
	{
		for (int i = numberOfDigits() - 1; i >= 0; i--)
		{
			if (this->numberContainer[i] > x[i]) return false;
			else if (this->numberContainer[i] == x[i]) continue;
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
BigNum BigNum::divOperation2(BigNum denominator) {
	BigNum devResult;devResult.setValue(0);
	if (denominator.greaterThan(*this))
		return devResult;
	if (this->equal(denominator))
	{
		devResult.editSpecificIndex(1, 0);
		return devResult;
	}
	BigNum numinator = *this; // it is updated each iteration in the operation main loop
	BigNum rem; //remainder
	vector<BigNum>multiplesOfDenominator;
	//multiplesOfDenominator			   
	bool remainderFlag = false;
	// push  1x, 2x , 4x , 8x
	multiplesOfDenominator.push_back(denominator);
	int c = 2;
	while (c<10)
	{
		BigNum temp;temp.setValue(c);
		multiplesOfDenominator.push_back(denominator.mulOperation(temp));
		c *= 2;
	}
	while (!remainderFlag) {
		int index = -1;
		int tempInt = multiplesOfDenominator[0].numberOfDigits();
		BigNum temp = numinator.getSomeDigitsFromMostSignificant(tempInt);
		for (int i = 0; i < 4; i++)
		{
			// let 85725 numinatur and 37 denominator : compare 85 with 37		
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
		vector <unsigned long long> result(numinator.numberOfDigits() - temp.numberOfDigits()); // initialize to zeros
		if (index == 0 || index == 1)result.push_back(index + 1); else if (index == 2)result.push_back(4); else result.push_back(8);
		devResult = devResult.addOperation(result);
		// second usage for result:
		result = multiplesOfDenominator[index].getVectorContainer();
		numinator = numinator.subOperation(result);
		if (!numinator.greaterThanOrEqual(denominator))
			return devResult;
	}
	return devResult;
}
BigNum BigNum::divOperation(BigNum &denominator) {
	BigNum leftSide(0);
	if (denominator.greaterThan(*this))		return leftSide;
	leftSide.numberContainer[0] = 1;
	if (this->equal(denominator))	return leftSide;
	if (denominator.equal(1))		return *this;
	if (denominator.equal(2))		return this->divByTwo();
	BigNum rightSide(numberContainer); // rightSide = numinator || my range in the search will be from 1 to numinator
	BigNum mid = rightSide.addOperation(leftSide).addOperation(1);
	mid = mid.divByTwo();
	BigNum temp;

	while (rightSide.greaterThan(leftSide))
	{
		temp = mid.mulOperation(denominator);
		if (this->greaterThan(temp))
		{
			leftSide = mid;
			mid = rightSide.addOperation(leftSide).addOperation_int(1).divByTwo();
		}
		else if (this->equal(temp))
		{
			return mid;
		}
		else {
			rightSide = mid.subOperation(1);
			mid = rightSide.addOperation(leftSide);
			mid = mid.addOperation_int((int)1);
			mid = mid.divByTwo();
		}
	}
	return mid;
}
BigNum BigNum::binarySearchTesting(BigNum denominator, BigNum leftSide_, BigNum midd, BigNum rightSide_) {
	BigNum mid = midd;
	BigNum leftSide = leftSide_, rightSide = rightSide_;
	BigNum temp;
	while (rightSide.greaterThan(leftSide))
	{
		temp = mid.mulOperation(denominator);
		if (this->greaterThan(temp))
		{
			leftSide = mid;
			mid = rightSide.addOperation(leftSide).addOperation_int(1).divByTwo();
		}
		else if (this->equal(temp))
		{
			return mid;
		}
		else {
			rightSide = mid.subOperation(1);
			mid = rightSide.addOperation(leftSide);
			mid = mid.addOperation_int(1);
			mid = mid.divByTwo();
		}
		rightSide.print();cout << endl << "right" << endl;
		leftSide.print();cout << endl << "left" << endl;
	}
	return mid;
}
/*BigNum BigNum::divOperation(BigNum denominator) {
BigNum devResult;devResult.setValue(0);
if (!this->greaterThanOrEqual(denominator))
return devResult;

BigNum numinator=*this; // it is updated each iteration in the operation main loop
BigNum rem; //remainder

vector<BigNum>multiplesOfDenominator;
//multiplesOfDenominator
bool remainderFlag = false;
int power = 8;
int counter = pow(10,power); // initialy 10^8
// push  1x, 2x , 4x , 8x
int c = 0;
while(c<4)// initialy 10^9
{
BigNum temp;temp.setValue(counter);
multiplesOfDenominator.push_back(denominator.mulOperation(temp));
counter *=2;
c++;
}
while (! remainderFlag) {
int index = -1;// -1 value is a flag, I use it in the conditions
int tempInt = multiplesOfDenominator[0].numberOfDigits();
BigNum temp = numinator.getSomeDigitsFromMostSignificant(tempInt);
for (int i = 0; i < 4; i++)
{
label:
// let 85725 numinatur and 37 denominator : compare 85 with 37
if (temp.greaterThanOrEqual(multiplesOfDenominator[i]))
{
index = i;
}
else if (i == 0 && power >= 0 && numinator.greaterThanOrEqual(denominator))
{
power--;
counter = pow(10, power);
// push  1x, 2x , 4x , 8x
c = 0;
while (c < 4)
{
BigNum temp;temp.setValue(counter);
multiplesOfDenominator[c]=denominator.mulOperation(temp);
counter *= 2;
c++;
}
goto label;
}
else if (power == -1) { rem = numinator; remainderFlag = true;	break; }
else break;
}
//here there are 2 usage for (result) vector
//first usage for result:
vector <unsigned long long> result(numinator.numberOfDigits()-temp.numberOfDigits()); // initialize to zeros
if(index==0 || index==1)result.push_back((index + 1)*pow(10,power)); else if(index==2)result.push_back(4*pow(10, power)); else result.push_back(8* pow(10, power));
devResult = devResult.addOperation_int(result);
// second usage for result:
result = multiplesOfDenominator[index].getVectorContainer();
numinator = numinator.subOperation(result);
if ( ! numinator.greaterThanOrEqual(denominator))
return devResult;
}
return devResult;
}*/
void BigNum::mul_base_shift()
{
	vector<unsigned long long>::iterator it;
	it = numberContainer.begin();
	it = numberContainer.insert(it, 0);
}
void BigNum::mulWithTen() {
	unsigned long long r = 0, tmp;
	vector<unsigned long long int> &container = this->numberContainer;
	for (auto it = container.begin(); it != container.end(); it++) {
		tmp = (*it) * 10 + r;
		r = tmp / 1000000000;
		*it = tmp % 1000000000;
	}
	if (r != 0) {
		container.push_back(r);
	}
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
BigNum BigNum::modOperation(BigNum &denominator) {
	if (denominator.greaterThan(*this)) return *this;
	if (this->equal(denominator)) { BigNum res(0); return res; }
	string numinatorString = this->convertBigNumToString();
	BigNum result;
	int iterationNum = numinatorString.size() - 1;
	bool flagFirstIteration = true;
	int i = 0;
	while (iterationNum >= i)
	{
		if (flagFirstIteration) {
			result.setValue(numinatorString[i] - '0');
			flagFirstIteration = false;
		}
		else
		{
			result.mulWithTen();
			int trial = numinatorString[i] - '0';
			result = result.addOperation_int(trial);
		}
		while (result.greaterThanOrEqual(denominator))
		{
			result = result.subOperation(denominator);
		}
		i++;
	}
	return result;
}

bool isPrimeBigNumIteration(BigNum &n) {
	if (!n.greaterThan(1)) return false;
	// if even: not prime
	if (!n.equal(2) && n.isEven()) return false;
	int k = 0;
	// get q

	BigNum temp = n;
	temp = temp.subOperation(1); // = n - 1
	BigNum q = temp;
	while (q.isEven())
	{
		k += 1;
		q = q.divByTwo();
	}
	// let's begin the test
	BigNum a((unsigned long long) rand()), x;
	a = a.mulOperation(temp);
	x = BigNum((unsigned long long) 1 << 31);
	a = a.divOperation(x);
	a = a.addOperation_int(1);
	x = a.powerOperation(q, n);

	if (x.equal(1)) return true;

	for (int j = 0; j < k; j++)
	{
		if (x.equal(temp))
			return true;
		x = x.mulOperation(x).modOperation(n);
	}

	return false;
}

bool isPrimeBigNum(BigNum &n, const int &numOfIterations) {
	for (int i = 0; i < numOfIterations; i++) {
		if (isPrimeBigNumIteration(n) == false)
			return false;
	}
	return true;
}

BigNum BigNum::extendedEUCLID(BigNum &modd) {
	BigNum A2(0), A3 = modd, B2(1), B3 = *this, Q, T2, T3;
	int i = 0;
	while (1)
	{
		i++;
		if (B3.equal(0))
		{
			cout << "no inverse";
			BigNum zero(0); return zero;
		}

		if (B3.equal(1))
			return B2;
		Q = A3.divOperation(B3);
		BigNum tmp = Q.mulOperation(B2);
		T2 = A2.subWithNegativeOperation(tmp, modd);
		tmp = Q.mulOperation(B3);
		T3 = A3.subWithNegativeOperation(tmp, modd);
		vector <unsigned long long> temp;
		A2 = B2;
		A3 = B3;
		B2 = T2;
		B3 = T3;
	}
}
BigNum enc(BigNum &msg, BigNum &n, BigNum &e) {
	return msg.powerOperation(e, n);
}

BigNum dec(BigNum &msg, BigNum &n, BigNum &d) {
	return msg.powerOperation(d, n);
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
void BigNum::operator=(const BigNum &m) {
	numberContainer = m.numberContainer;
}

//////////////////////////////////////////////////////////////

void parsing(char chars[], string p) {
	for (unsigned int i = 0; i < strlen(chars); ++i)
	{
		p.erase(remove(p.begin(), p.end(), chars[i]), p.end());
	}
}
////////////////////////////////
///  main
///////////////////////////////
int main()
{
	ios::sync_with_stdio(true);
	int t1, t2;
	BigNum P, Q, E, N, phiN, test, D, msg(100);
	string p, q, e;
	//p = "5915587277"; prime num
	p = "12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871";
	q = "2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473";
	e = "65537";

	P.setValue(p);
	Q.setValue(q);
	E.setValue(e);

	t1 = clock();
	//	t2 = clock();
	//	cout << "time: " << (t2 - t1) / double(CLOCKS_PER_SEC)  << endl;

	cout << isPrimeBigNum(P, 4) << endl;
	cout << isPrimeBigNum(Q, 4) << endl;

	N = P.mulOperation(Q);
	phiN = (P.subOperation(1)).mulOperation(Q.subOperation(1));
	D = E.extendedEUCLID(phiN);
	test = enc(msg, N, E);
	///cout << test.convertBigNumToString() << endl;
	test = dec(test, N, D);
	cout << test.convertBigNumToString() << endl;
	//
	//	t1 = clock();
	t2 = clock();
	cout << "time: " << (t2 - t1) / double(CLOCKS_PER_SEC) << endl;
	return 0;
}
