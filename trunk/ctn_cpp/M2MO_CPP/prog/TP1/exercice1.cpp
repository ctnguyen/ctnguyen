#include<iostream>
#include <cstdlib>

using namespace std;


int main(int argc,char** argv)
{
	int d; // une variable entiere d
	int i;

	//cout<<"****Premier programme****"<<endl;
	cout<<std::endl<< "****Division****" <<endl; //m2mo_tp1_question_2
	//cout<<"Saisissez un nombre puis appuyez sur entree : ";	cin >> d;

	i=0; // on met 0 dans i

	int max_N = 15;
	i=1 ; max_N = 100; //m2mo_tp1_question_3
	//cout<<"Saisissez un nombre indiquant le max : "; cin >> max_N; //m2mo_tp1_question_4


	//m2mo_tp1_question_6
	if (argc != 3) {
		cout << "Two argument expected : excercice1 [divisor] [Max_dividend]"<<std::endl;
		return 0;
	}
	else
	{
		d     = atoi(argv[1]) ;
		max_N = atoi(argv[2]) ;
	}

	while(i<=max_N)
	{
		/*
		if( i % d == 0)
		{
			cout << i << " est divisible par "<< d << endl;
		}
		else
		{
			cout << i << " n'est pas divisible par "<< d << endl;
		}
		i=i+1;
		*/

		// m2mo_tp1_question_5
		int e_quotient  = (int) i/d ;
		int e_remainder =       i%d ;
		cout << i << " = "<< e_quotient <<"*" <<d <<" + "<< e_remainder << endl;
		++i;
	}

	return 0;
}
