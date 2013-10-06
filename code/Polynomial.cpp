#include <string.h>
#include <sstream>
#include <iostream>
#include <string>
#include <cstddef>  // for NULL
#include <new>      // for bad_alloc
#include "Polynomial.h"  // header file
using namespace std;

Polynomial::Polynomial() : head(NULL)//, item_coefficien(0), item_exponent(0)
{
//	ListNode *cur = head;
//	cur->item_coefficien = 0;
//	cur->item_exponent = 0;
}
//******************************************************************************
Polynomial::~Polynomial()
{
	/*
	while( head != NULL ){
		ListNode *CurDelete = head;			
		head = head->next;
		CurDelete->next = NULL;
		delete CurDelete;
		CurDelete = NULL;
	}
	*/
}
//******************************************************************************
int Polynomial::getDegree() const
{
	int degree = 0;
	ListNode *prev, *cur;
	for( ListNode *cur = head; cur != NULL; cur = cur->next ){
		if( (cur->item_exponent > degree)&&(cur->item_coefficien != 0)){
			degree = cur->item_exponent;
		}
	}
		return degree;
}
//******************************************************************************
int Polynomial::getNonZero() const
{
	int countNonZero = 0;
	for( ListNode *cur = head; cur != NULL; cur = cur->next ){
		if( (cur->item_exponent != 0)&&(cur->item_coefficien != 0)){
			countNonZero++;
		}
	}
	return countNonZero;
}
//******************************************************************************
string Polynomial::getPoly()
{
	string PolyString;

	for( ListNode *cur = head; cur != NULL; cur = cur->next ){
		stringstream PolyString_coefficien;
		stringstream PolyString_exponent;
		PolyString_coefficien << cur->item_coefficien;
		PolyString_exponent << cur->item_exponent;
		if( cur->item_coefficien > 0 ){  //if coefficien  >0 print" + " «Y¼Æ>0 
			if( PolyString.empty() ){ //First time, polyString is empty  
				//	judge §PÂ_ 
				if( cur->item_coefficien > 1 ){ //«Y¼Æ>1 
					if( cur->item_exponent == 0 ){  //ax^0 exponent = 0, don't print "x^0"
						PolyString = PolyString + PolyString_coefficien.str();
					}
					else if( cur->item_exponent == 1 ){  //ax^1 exponent = 1, don't print "^1"
						PolyString = PolyString + PolyString_coefficien.str() + "x";
					}
					else{ //ax^a 
						PolyString = PolyString + PolyString_coefficien.str() + "x^" + PolyString_exponent.str();
					}
				}
				else{  //«Y¼Æ= 1 
					if( cur->item_exponent == 0 ){  //1x^0 exponent = 0, don't print "1x^0"
						PolyString = PolyString + "1";
					}
					else if( cur->item_exponent == 1 ){  //1x^1 exponent = 1, don't print "1  ^1"
						PolyString = PolyString + "x";
					}
					else{ //1x^a don't print "1 "
						PolyString = PolyString + "x^" + PolyString_exponent.str();
					}
				}
			}		
			else{  // polyString is not empty 
				//	judge §PÂ_ 
				if( cur->item_coefficien > 1 ){ //«Y¼Æ>1 
					if( cur->item_exponent == 0 ){  //ax^0 exponent = 0, don't print "x^0"
						PolyString = PolyString + "+" + PolyString_coefficien.str();
					}
					else if( cur->item_exponent == 1 ){  //ax^1 exponent = 1, don't print "^1"
						PolyString = PolyString + "+" + PolyString_coefficien.str() + "x";
					}
					else{ //ax^a 
						PolyString = PolyString + "+" + PolyString_coefficien.str() + "x^" + PolyString_exponent.str();
					}
				}
				else{  //«Y¼Æ= 1 
					if( cur->item_exponent == 0 ){  //1x^0 exponent = 0, don't print "1x^0"
						PolyString = PolyString + "+1";
					}
					else if( cur->item_exponent == 1 ){  //1x^1 exponent = 1, don't print "1  ^1"
						PolyString = PolyString + "+" + "x";
					}
					else{ //1x^a don't print "1 "
						PolyString = PolyString + "+" + "x^" + PolyString_exponent.str();
					}
				}
			}
		}
		else if( cur->item_coefficien < 0 ){	//else  if coefficien  < 0  «Y¼Æ<0 
			if( cur->item_coefficien == -1 ){	//if coefficien = -1  «Y¼Æ = -1 
				if( cur->item_exponent == 0 ){  //-1x^0 exponent = 0, don't print "x^0"
					PolyString = PolyString + "-1";
				}
				else if( cur->item_exponent == 1 ){  //-1x^1 exponent = 1, don't print "^1"
					PolyString = PolyString + "-" + "x";
				}
				else{ //-1x^a 
					PolyString = PolyString + "-" + "x^" + PolyString_exponent.str();
				}	
			}
			else{ //if coefficien <0  != -1  «Y¼Æ <0 != -1 
			//	judge §PÂ_ 
				if( cur->item_exponent == 0 ){  //-ax^0 exponent = 0, don't print "x^0"
					PolyString = PolyString + PolyString_coefficien.str();
				}
				else if( cur->item_exponent == 1 ){  //-ax^1 exponent = 1, don't print "^1"
					PolyString = PolyString + PolyString_coefficien.str() + "x";
				}
				else{ //-ax^a 
					PolyString = PolyString + PolyString_coefficien.str() + "x^" + PolyString_exponent.str();
				}	
			}
		}	
		else{	
			//do nothing
		}
	}
	if( PolyString.empty() ){
		PolyString = "0";
	}
	return PolyString;
}
//******************************************************************************
void Polynomial::set( const int &newItem_exponent, const int &newItem_coefficien) //throw (PolynomialException)
{
	ListNode *prev, *cur;
	ListNode *newPtr = new ListNode;
	//Finding the point of insertion
	for( prev = NULL, cur = head; (cur != NULL) && (newItem_exponent <= cur->item_exponent); prev = cur, cur = cur->next){
	}
	//insert(set)
	if( newItem_coefficien != 0 ){  //coefficien can't be 0 ¨t¼Æ¬°¹sªºª¬ªp 
		if( prev == NULL ){	//special case
			newPtr->next = head;
			head= newPtr;
			newPtr->item_exponent = newItem_exponent;
			newPtr->item_coefficien = newItem_coefficien;
		}
		else{	//general case
			//there is a same exponent
			if( prev->item_exponent == newItem_exponent ){  
				prev->item_coefficien += newItem_coefficien;
			}
			else{
				newPtr->next = cur;
				prev->next = newPtr;
				newPtr->item_exponent = newItem_exponent;
				newPtr->item_coefficien = newItem_coefficien;
			}
		}
	}
}
//******************************************************************************
void Polynomial::add(Polynomial PolyAdd)// throw (PolynomialException)
{
	for( ListNode *PolyAddcur = PolyAdd.head; (PolyAddcur != NULL); PolyAddcur = PolyAddcur->next){
		set(PolyAddcur->item_exponent, PolyAddcur->item_coefficien);
	} 
}
//******************************************************************************
void Polynomial::multiplies(Polynomial PolyMult)// throw (PolynomialException)
{
	int MultResult_coefficien, MultResult_exponent;
	Polynomial tempPoly;  //temp the result of two Polynomial is case of changing
	ListNode *tempPolycur = tempPoly.head;
	for( ListNode *PolyMultcur = PolyMult.head; (PolyMultcur != NULL); PolyMultcur = PolyMultcur->next){	
		for( ListNode *cur = head; cur != NULL; cur = cur->next ){
			MultResult_coefficien = cur->item_coefficien * PolyMultcur->item_coefficien;
			MultResult_exponent = cur->item_exponent + PolyMultcur->item_exponent;			
			tempPoly.set(MultResult_exponent, MultResult_coefficien);
		}
	}
	head = tempPoly.head;
}
//******************************************************************************
