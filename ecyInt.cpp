#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include "ecyInt.h"
#include "safeopts1.h"
#include <stdio.h>


using namespace std;

ecyInt::ecyInt(char * the_p,int the_len)
{
    p_ecy=the_p;
    len_ecy=the_len;
}

ecyInt::ecyInt():p_ecy(NULL),len_ecy(0)
{

}

char * ecyInt::get_p()
{
    return p_ecy;
}

int ecyInt::get_len()
{
    return len_ecy;
}

ecyInt operator +(ecyInt eint1,ecyInt eint2)
{
    char * dchar1;
    char * dchar2;
    int dint1,dint2,isum;
    int elen1=eint1.len_ecy;
    int elen2=eint2.len_ecy;
    char * echar1=eint1.p_ecy;
    char * echar2=eint2.p_ecy;

    ecyInt eisum;
    // decrypt & add
    dchar1=decrypt(echar1,elen1,priv_key);
    dchar2=decrypt(echar2,elen2,priv_key);
    dint1=atoi(dchar1);
    dint2=atoi(dchar2);
    isum=dint1+dint2;
//    cout << "The real sum is:" << isum << endl; 
    // assign & encrypt
    //char * csum=itoa(isum);
    char * csum=(char *)malloc((digitnum(isum)+1)*sizeof(int));
    sprintf(csum,"%d",isum);
    eisum.p_ecy=encrypt(csum,pub_key);
    eisum.len_ecy=encrylen;
    int elen3=eisum.len_ecy;
    char * echar3=eisum.p_ecy;
//    cout << "The encrypted sum is:"<< echar3 << endl;
//    char * dsum=decrypt(echar3,elen3,priv_key);
//    cout << "The decrypted sum is:"<< dsum << endl;
    return eisum;
}

ecyInt operator -(ecyInt eint1,ecyInt eint2)
{
    char * dchar1;
    char * dchar2;
    int dint1,dint2,isub;
    int elen1=eint1.len_ecy;
    int elen2=eint2.len_ecy;
    char * echar1=eint1.p_ecy;
    char * echar2=eint2.p_ecy;
    
    ecyInt eisub;
    // decrypt & sub
    dchar1=decrypt(echar1,elen1,priv_key);
    dchar2=decrypt(echar2,elen2,priv_key);
    dint1=atoi(dchar1);
    dint2=atoi(dchar2);
    isub=dint1-dint2;
//    cout << "The real sub is:" << isub << endl; 
    // assign & encrypt
    //char * csum=itoa(isum);
    char * csub=(char *)malloc((digitnum(isub)+1)*sizeof(int));
    sprintf(csub,"%d",isub);
    eisub.p_ecy=encrypt(csub,pub_key);
    eisub.len_ecy=encrylen;
    int elen3=eisub.len_ecy;
    char * echar3=eisub.p_ecy;
//    cout << "The encrypted sub is:"<< echar3 << endl;
//    char * dsub=decrypt(echar3,elen3,priv_key);
//    cout << "The decrypted sub is:"<< dsub << endl;
    return eisub;
}

istream& operator >>(istream& ins,ecyInt& eint1)
{
    int rawdata,ecylen;
    ins >> rawdata;
    char * crdata=(char *)malloc((digitnum(rawdata)+1)*sizeof(int));
    sprintf(crdata,"%d",rawdata);
    eint1.p_ecy=encrypt(crdata,pub_key);
    eint1.len_ecy=encrylen;
    return ins;
}

ostream& operator <<(ostream& outs,ecyInt& eint1)
{
    int dint1;
    int elen=eint1.len_ecy;
    char * echar=eint1.p_ecy;
    char * dchar=decrypt(echar,elen,priv_key);
    dint1=atoi(dchar);
    outs << dint1;
    return outs;
}
