#include<iostream>
using namespace std;



int main(int argc,char** argv)
{
	int d; // une variable entiere d
	int i;

	//cout<<"****Premier programme****"<<endl;
	cout<<"****Division****"<<endl; // Question 1
	cout<<"Saisissez un nombre puis appuyez sur entree : ";

	cin >> d;

	i=0; // on met 0 dans i
	while(i<=15)
	{
		if( i % d == 0)
		{
			cout << i << " est divisible par "<< d << endl;
		}
		else
		{
			cout << i << " n'est pas divisible par "<< d << endl;
		}
		i=i+1;
	}
}
