#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fstream>
//#include "ecyInt.h"
#include "ecyInt.cpp"
#include "safeopts1.h"
#include <stdio.h>

using namespace std;


int main()
{
    ecyInt eia,eib,eic,eid,eie;
    ifstream in_stream;
// read file a, b to eia, eib respectively.
    in_stream.open("a");
    if(in_stream.fail())
    {
        cout << "Input file a opening failed.\n";
        exit(1);
    }
    in_stream >> eia;
    in_stream.close();
    in_stream.open("b");
    if(in_stream.fail())
    {
        cout << "Input file b opening failed.\n";
        exit(1);
    }
    in_stream >> eib;
    in_stream.close();

//a+b
    eic=eia+eib;
//c-a
    eid=eic-eia;
//a-b
    eie=eia-eib;
    cout <<"eia.p_ecy= \n"<< eia.get_p() << endl;
    cout <<"eib.p_ecy= \n"<< eib.get_p() << endl;
    cout <<"eic.p_ecy= \n"<< eic.get_p() << endl;
    cout <<"eid.p_ecy= \n"<< eid.get_p() << endl;
    cout <<"eie.p_ecy= \n"<< eie.get_p() << endl;

    cout <<"eia= \n"<< eia << endl;
    cout <<"eib= \n"<< eib << endl;
    cout <<"eic=eia+eib, eic= \n"<< eic << endl;
    cout <<"eid=eic-eia, eid= \n"<< eid << endl;
    cout <<"eie=eia-eib, eie= \n"<< eie << endl;

    return 0;
}

/*
int main()
{
    ecyInt eic,eid,eie;
    char * ecy_a;
    char * ecy_b; 
    FILE *ecyf_a=ecyfopen("a","r");
    ecy_a=(char *)malloc(encrylen * sizeof(char));
    fread(ecy_a,encrylen,1,ecyf_a);
    printf("\noutput encrypted a:\n%s\n",ecy_a);
    ecyInt eia(ecy_a,encrylen);
    fclose(ecyf_a);

    FILE *ecyf_b=ecyfopen("b","r");
    ecy_b=(char *)malloc(encrylen * sizeof(char));
    fread(ecy_b,encrylen,1,ecyf_b);
    printf("\noutput encrypted b:\n%s\n",ecy_b);
    ecyInt eib(ecy_b,encrylen);
    fclose(ecyf_b);

//a+b
    eic=eia+eib;
//c-a
    eid=eic-eia;
//a-b
    eie=eia-eib;

    return 1;
}
*/
