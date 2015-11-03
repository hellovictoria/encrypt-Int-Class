#ifndef SAFEOPTS_H
#define SAFEOPTS_H

// encrypted & decrypted codes length 
extern int encrylen;
extern int decrylen;
// encrypt file path & decrypt file path
extern char * encry_path;
extern char * decry_path;
// public key file & private key file
extern char * pub_key;
extern char * priv_key;

// calculate how many digits in a number. the digits of 598 is 3.
int digitnum(int idata);
// encrypt & decrypt file function
int encryptf(FILE * fp,char * pub_key,char * encry_path);
int decryptf(FILE * fp,char * priv_key,char * decry_path);
FILE * ecyfopen(const char * path, const char * mode);
FILE * dcyfopen(const char * path, const char * mode);
// encrypt & decrypt char * function
char * decrypt(char * p_ecypt,int len_ecypt,char * priv_key);
char * encrypt(char * p_src,char * pub_key);
// print decrypted codes
int dcyprint(char * path,char * mode);
int dcyprint_Temp(char * path,char * mode);

#endif
