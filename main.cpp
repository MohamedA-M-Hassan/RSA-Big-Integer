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
	bool isEven();

	// comprason
	bool greaterThan(BigNum x);
	bool greaterThan(int x);
	bool greaterThanOrEqual(BigNum x);
	bool equal(const BigNum &x);
	bool equal(int x);
	bool equal(vector <unsigned long long> &x);

	// operations
	BigNum addOperation(const BigNum & x);
	BigNum addOperation(vector <unsigned long long> num);
	BigNum addOperation(int & x);
	BigNum subOperation(BigNum x);
	BigNum subOperation(vector <unsigned long long> num);
	BigNum subOperation(int num);
	void mulWithTen();
	void mul_base_shift();
	BigNum mulOperation(const BigNum &x);
	BigNum modOperation(BigNum denominator);
	BigNum modOperation2(BigNum &denominator);
	BigNum divByTwo();
	BigNum divOperation2(BigNum denominator);
	BigNum divOperation(BigNum denominator);
	BigNum powerOperation(BigNum power, BigNum modulus);

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
int BigNum::numberOfDigits()const{
	return numberContainer.size();
}
void BigNum::editSpecificIndex(unsigned long long newValue, int index) {
	numberContainer[index] = newValue;
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
bool BigNum::isEven() {
	if (numberContainer[0] & 1)
		return false;
	return true;
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


// operations
BigNum BigNum::addOperation(const BigNum & x) {
	BigNum z , n1 , n2;
	n1 = *this, n2 = x;
	int carry = 0;
	int n1NumOfDigit = numberContainer.size(), n2NumOfDigit = x.numberContainer.size();
	unsigned long long  tempInt;
	if (n2NumOfDigit > n1NumOfDigit) {
		n1.numberContainer.swap(n2.numberContainer); //make sure a has more or equal amount of digits than b
	}
	z.numberContainer.reserve(  n1NumOfDigit + 1);
	int i;
	for (i = 0; i < n1NumOfDigit ; i++) // we use maxDigit+1 not maxDigit:--> if there is a (carry) in last step
	{
		if (i < n2NumOfDigit)
			tempInt = n1.numberContainer[i] + n2.numberContainer[i]+ carry;
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
		z.numberContainer.push_back(tempInt);
	}
	if (carry) {
		z.numberContainer.push_back(1);
	}
	return z;
}
BigNum BigNum::addOperation(int & x) {
	BigNum res = *this;
	res.numberContainer[0] += x;
	if (res.numberContainer[0] < 1000000000) return res;
	int index = 1 ;

	// first time will insert without checking, as i know there is a carry
	while (true)
	{
		res.numberContainer[index] += 1;
		if (res.numberContainer[index] > 999999999)
			res.numberContainer[index] -= 1000000000,index++;
		else return res;
	}
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
	BigNum thisCopy=*this;
	BigNum result;
	unsigned long long tempInt;
	int maxDigit=numberContainer.size();
	int minDigit = x.numberContainer.size();
	int index;
	for (int  i = 0; i < maxDigit; i++)
	{
		if (i >= minDigit)
		{
			result.numberContainer.push_back(thisCopy.numberContainer[i]);
			continue;
		}
		index = i + 1;
		while (true)
		{
			if (thisCopy.numberContainer[i] >= x.numberContainer[i])
			{	tempInt = thisCopy.numberContainer[i] - x.numberContainer[i]; break;	}
			// borrow from next digit
			else
			{
				if (thisCopy.numberContainer[index] > 0)
					while (index > i)
					{
						thisCopy.numberContainer[index] -= 1, thisCopy.numberContainer[index - 1] += 1000000000;
						index--;
					}
				index++;
			}
		}
		result.numberContainer.push_back(tempInt);
	}
	result.removeLeadingZero();
	return result;
}
BigNum BigNum::subOperation(vector <unsigned long long> num) {
	// let (this > x) this greater than x
	if (this->equal(num))
	{
		BigNum result(0);
		return result;
	}
	BigNum thisCopy = *this;
	BigNum result;
	unsigned long long tempInt;
	int maxDigit = numberContainer.size();
	int minDigit = num.size();
	int index;
	for (int i = 0; i < maxDigit; i++)
	{
		if (i >= minDigit)
		{
			result.numberContainer.push_back(thisCopy.numberContainer[i]);
			continue;
		}
		index = i + 1;
		while (true)
		{
			if (thisCopy.numberContainer[i] >= num[i])
			{
				tempInt = thisCopy.numberContainer[i] - num[i]; break;
			}
			// borrow from next digit
			else
			{
				if (thisCopy.numberContainer[index] > 0)
					while (index > i)
					{
						thisCopy.numberContainer[index] -= 1, thisCopy.numberContainer[index - 1] += 1000000000;
						index--;
					}
				index++;
			}
		}
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
void BigNum::mul_base_shift()
{
	vector<unsigned long long>::iterator it;
	it = numberContainer.begin();
	it = numberContainer.insert(it, 0);
}
void BigNum::mulWithTen() {
	string temp=this->convertBigNumToString();
	temp = temp + "0";
	this->setValue(temp);
}
BigNum BigNum::mulOperation(const BigNum & x)
{
	BigNum result;
	int num1_digitsNum = x.numberOfDigits();
	int num2_digitsNum = numberContainer.size();
	//vector <unsigned long long> res(num1_digitsNum + num2_digitsNum);
	vector <unsigned long long> &res = result.numberContainer;
	res.resize(num1_digitsNum + num2_digitsNum);

	unsigned long long carry = 0;

	for (int i = 0; i < num1_digitsNum; i++) // we use maxDigit+1 not maxDigit:--> if there is a (carry) in last step
	{
		for (int j = 0; j < num2_digitsNum; j++)
		{
			res[i + j] += (x.numberContainer[i] * this->numberContainer[j]);// + carry; 
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
	result.removeLeadingZero();
	return result;
}
BigNum BigNum::modOperation(BigNum denominator) {
	if (denominator.greaterThan(*this)) return *this;
	if (this->equal(denominator)) {	BigNum res(0); return res;	}
	string numinatorString = this->convertBigNumToString();
	BigNum result;
	int iterationNum = numinatorString.size()-1;
	bool flagFirstIteration = true;
	int i = 0;
	while (iterationNum >= i)
	{
		if (flagFirstIteration) {
			result.setValue(numinatorString[i]-'0');
			flagFirstIteration = false;
		}	
		else
		{
			result.mulWithTen();
			int trial = numinatorString[i] - '0';
			result = result.addOperation(trial);
		}
		while (result.greaterThanOrEqual(denominator))
		{
			result = result.subOperation(denominator);
		}
		i++;
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
BigNum BigNum::divOperation(BigNum denominator) {
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
			mid = rightSide.addOperation(leftSide).addOperation(1).divByTwo();
		}
		else if (this->equal(temp))
		{
			return mid;
		}
		else {
			rightSide = mid.subOperation(1);
			mid = rightSide.addOperation(leftSide).addOperation(1).divByTwo();
		}
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
devResult = devResult.addOperation(result);
// second usage for result:
result = multiplesOfDenominator[index].getVectorContainer();
numinator = numinator.subOperation(result);
if ( ! numinator.greaterThanOrEqual(denominator))
return devResult;
}
return devResult;
}*/
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
BigNum BigNum::powerOperation(BigNum power,BigNum modulus) {
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
		multiplies= multiplies.modOperation(modulus);
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

////////////////////////////////
///  main
///////////////////////////////
int main()
{
	
	int t1=123456789, t2=12,fsakonya=0;
	BigNum v1, v2, v3,v4,v5;
	string p, q, m,s;
	p = "1236957152874765579811018878656718075962691046572692055656729865937039974807236650723489943282747586518964271406783620730015303505947223727581638441007787112369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871";
	q = "630603941216631539335533767665752838509345191448466426637890625961581570307726653783533222578471892075854032799900049840210985095952161891727478162213374882839379982821021539676451601044065349435787748210088633657610551178543878204319087995808618460729616929369913496086370031703299500591359418899290766870071445808905985603188683086789912429577177180650738657122243767189903773595340360338294481381655539117853370300054223762698730161735015921586991708708811442118081786314904166711698302602427383785094043365794082123205495531468565361709676428693341310455053719182917553701738156469743655119964106274556398231729777";
	m = "18359144343988646008972981828043374122041076435009721447720639424612261105913013933450813357652982359669199076450119956124339996073512289928102023490997920509770675669962417905599103699710575561913451958687135666376008127628377940002828230986440318015449260135481034486129911056684072101093510462742658398964";
	s = "100000000000000009877789738400000000000000000000341987234900009873498000000000007092";
	s = "100000000000000000000000000000000000000000000000000000000000000000000000000000000000";

	v1.setValue(s);
	v2.setValue(2);
	v3.setValue(m);
	
	t1 = clock();
	v1 = v1.subOperation(v2);
//	v2 = v2.extendedEUCLID(v3);

	v1.print();std::cout << endl ;
	//if (v1.isPrime(10)) 
		//cout << "did it " << endl;
	t2 = clock();
	cout << "time: " << (t2 - t1) / double(CLOCKS_PER_SEC)  << endl;
	
	return 0;
}