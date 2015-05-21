#include <iostream>
using namespace std;

class ecyInt
{
public:
    ecyInt();
    ecyInt(char * the_p, int the_len);
    char * get_p();
    int get_len();
    friend ecyInt operator +(ecyInt eint1,ecyInt eint2); 
    friend ecyInt operator -(ecyInt eint1,ecyInt eint2);
    friend istream& operator >>(istream& ins,ecyInt& eint1);
    friend ostream& operator <<(ostream& outs,ecyInt& eint1); 
private:
    char * p_ecy;
    int len_ecy;
};
