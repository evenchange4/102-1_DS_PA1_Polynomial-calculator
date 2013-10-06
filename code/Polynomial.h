#include <cstdlib>
#include <iostream>
#include <string>
#include <new>
using namespace std;

class Polynomial
{
	public:
		Polynomial(); //Default constructor
		~Polynomial();//Destructor
		int getDegree() const;
		int getNonZero() const;
		string getPoly();
		void set( const int &newItem_exponent, const int &newItem_coefficien);// throw (PolynomialException);
		void add(Polynomial PolyAdd);// throw (PolynomialException);
		void multiplies(Polynomial PolyMult);// throw (PolynomialException);
		
	private:
		struct ListNode
		{
			int item_coefficien;
			int item_exponent;
			ListNode *next;
		};
		ListNode *head;
};

//class PolynomialException : public logic_error
//{
//	public:
//		PolynomialException(const string & message = "") : logic_error(message.c_str())
// 	{}
//};
