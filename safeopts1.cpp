#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include "safeopts1.h"

// encrypted & decrypted codes length 
int encrylen;
int decrylen;
// encrypt file path & decrypt file path
char * encry_path="encrydata";
char * decry_path="decrydata";
// public key file & private key file
char * pub_key="public.pem";
char * priv_key="private.pem";

// calculate how many digits in a number. the digits of 598 is 3.
int digitnum(int idata)
{
    int power,j;
    j=idata;
    for(power=1;j>10;j/=10)
        power++;
    return power;
}

char * encrypt(char * p_src,char * pub_key)
{
    char * p_ecypt;
    int rsa_len;

    // open public key file
    FILE * pub_fp=fopen(pub_key,"r");
    if(pub_fp==NULL){
        printf("failed to open pub_key file %s!\n",pub_key);
        return NULL;
    }
    
    // read public key from public key file
    RSA *rsa1=PEM_read_RSA_PUBKEY(pub_fp,NULL,NULL,NULL);
    if(rsa1==NULL){
        printf("failed to read public key!\n");
        return NULL;
    }
    
    rsa_len=RSA_size(rsa1);
    p_ecypt=(char *)malloc(rsa_len+1);
    memset(p_ecypt,0,rsa_len+1);

    if(strlen(p_src)>=RSA_size(rsa1)-41){
        printf("failed to encrypt\n");
        return NULL;
    }
    fclose(pub_fp);
    
    // encrypt by using public key
    encrylen=RSA_public_encrypt(strlen(p_src),(const unsigned char*)p_src,(unsigned char*)p_ecypt,rsa1,RSA_PKCS1_PADDING);
    if(encrylen==-1){
        printf("failed to encrypt\n");
        return NULL;
    }
    return p_ecypt;
}

char * decrypt(char * p_ecypt,int len_ecypt,char * priv_key){
    char * p_dcypt;
    int rsa_len;

    // open private key file
    FILE* priv_fp=fopen(priv_key,"r");
    if(priv_fp==NULL){
        printf("failed to open priv_key file %s!\n", priv_key);
        return NULL;
    }
    
    // read private key from private key file
    RSA *rsa2=PEM_read_RSAPrivateKey(priv_fp,NULL,NULL,NULL);
    if(rsa2==NULL){
        printf("unable to read private key!\n");
        return NULL;
    }
    
    rsa_len=RSA_size(rsa2);
    p_dcypt=(char *)malloc(rsa_len+1);
    memset(p_dcypt,0,rsa_len+1);
 
    // decrypt by using private key 
    decrylen=RSA_private_decrypt(len_ecypt,(const unsigned char*)p_ecypt,(unsigned char*)p_dcypt,rsa2,RSA_PKCS1_PADDING);
    if(decrylen==-1){
        printf("failed to decrypt!\n");
        return NULL;
    }
    
    fclose(priv_fp);
    return p_dcypt;
}

int encryptf(FILE * fp,char * pub_key,char * encry_path)
{
        //read file to str pointer
        char * plain;
        int fsize;
        fseek(fp,0,SEEK_END);
        fsize=ftell(fp);
        fseek(fp,0,SEEK_SET);
        plain=(char *)malloc(fsize * sizeof(char));
        fread(plain,sizeof(char),fsize,fp);
//        printf("file size is:\n%d\n",fsize);
//        printf("Source is:\n%s\n",plain);
//        printf("strlen is: \n%d\n",strlen(plain));
        fclose(fp);

        // used to store encrypted file
        char encrypted[1024];

        // -------------------------------------------------------
        // use public key to encrypt plain text
        // -------------------------------------------------------
        // open public key file
        FILE* pub_fp=fopen(pub_key,"r");
        if(pub_fp==NULL){
                printf("failed to open pub_key file %s!\n", pub_key);
                return -1;
         }

        // read public key from file
        RSA* rsa1=PEM_read_RSA_PUBKEY(pub_fp, NULL, NULL, NULL);
        if(rsa1==NULL){
                printf("unable to read public key!\n");
                return -1;
        }
        if(strlen(plain)>=RSA_size(rsa1)-41){
                printf("failed to encrypt\n");
                return -1;
        }
        fclose(pub_fp);

        // use public key to encrypt 
        encrylen=RSA_public_encrypt(strlen(plain), (const unsigned char*)plain, (unsigned char*)encrypted, rsa1, RSA_PKCS1_PADDING);
        if(encrylen==-1 ){
                printf("failed to encrypt\n");
                return -1;
        }

//        printf("in encryptf func, encrylen is:\n%d\n",encrylen);

        // output encrypted data to original file
        FILE* ffp=fopen(encry_path,"w");
        if(ffp){
             fwrite(encrypted,encrylen,1,ffp);
             fclose(ffp);
        }
}

int decryptf(FILE * fp,char * priv_key,char * decry_path)
{
        //read file to str pointer
        char * encrypted;
        encrypted=(char *)malloc(encrylen * sizeof(char));
        fread(encrypted,encrylen,1,fp);
        fclose(fp);

        char decrypted[1024];

        // -------------------------------------------------------
        // use private key to decrypt the encrypted file
        // -------------------------------------------------------
        // out private key file 
        FILE* priv_fp=fopen(priv_key,"r");
        if(priv_fp==NULL){
            printf("failed to open priv_key file %s!\n", priv_key);
            return -1;
        }

        // read private key from private key file
        RSA *rsa2 = PEM_read_RSAPrivateKey(priv_fp, NULL, NULL, NULL);
        if(rsa2==NULL){
            printf("unable to read private key!\n");
            return -1; 
        }
    
        // use private key to decrypt encrypted data
        decrylen=RSA_private_decrypt(encrylen, (const unsigned char*)encrypted, (unsigned char*)decrypted, rsa2, RSA_PKCS1_PADDING);
        if(decrylen==-1){
            printf("failed to decrypt!\n");
            return -1;
        }

        fclose(priv_fp);
        
//        printf("in decryptf func, decrylen is:\n%d\n",decrylen);

        // output decrypted plain text
//        printf("in decryptf func, decrypted string is \n%s\n",decrypted);

        // output decrypted data to a new file
        FILE* ffp=fopen(decry_path,"w");
        if(ffp){
             fwrite(decrypted,decrylen,1,ffp);
             fclose(ffp);
        }
}

FILE * ecyfopen(const char * path, const char * mode)
{
        FILE * fp_src;
        fp_src=fopen(path,"r");
        // encrypt source file & store the encrypted codes into a new file
        encryptf(fp_src,pub_key,encry_path);
        // open encrypted file, & return the file pointer
        FILE* encyfp=fopen(encry_path,mode);
        return encyfp;
}

FILE * dcyfopen(const char * path, const char * mode)
{
        FILE * fp_encry;
        fp_encry=fopen(encry_path,"r");
        // decrypt encrypted file & store the decrypted file into a new file
        decryptf(fp_encry,priv_key,decry_path);
        //open decrypted file, & return the file pointer
        FILE* decryfp=fopen(decry_path,mode);
        return decryfp;
}

int dcyprint(char * path,char * mode)
{
        FILE * decry_fp;
        char * dcypted_code;
        decry_fp=dcyfopen(path,mode);
        dcypted_code=(char *)malloc(decrylen * sizeof(char));
        fread(dcypted_code,decrylen,1,decry_fp);
        fclose(decry_fp);
        // remove the decrypted file
        remove(decry_path);
        printf("output decrypted code:\n%s\n",dcypted_code);
        return 1;
}

int dcyprint_Temp(char * path,char * mode)
{
        int temp_value;
        FILE * decry_fp;
        char * dcypted_code;
        decry_fp=dcyfopen(path,mode);
        dcypted_code=(char *)malloc(decrylen * sizeof(char));
        fread(dcypted_code,decrylen,1,decry_fp);
        fclose(decry_fp);
        // remove the decrypted file
        remove(decry_path);
        // Calculate temperature
        temp_value = atoi(dcypted_code)*500/4096;
        printf("\ntemperature value is:\n%dC. \n",temp_value);
        return 1;
}


