#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
//Metin Furkan YAMAN
//21100011010
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int matris1[7][7];
int matris2[7][7];
int result[7][7];
int tempSum;

int len = 0;

typedef struct _arg{
    int sayi1;
    int sayi2;
    int yeni_satir;
    int yeni_sutun;
} arg;


int dosya_oku() {
    FILE *dosya1;
    dosya1 = fopen("inputA.txt", "r");
    char myString[100]; 
    int satir=0;
    while (fgets(myString, sizeof(myString), dosya1) != NULL) {
        //printf("%s", myString);

        char *veri = strtok(myString, " ");
        int sutun = 0;

        while (veri != NULL && sutun < 7) {
            matris1[satir][sutun] = atoi(veri); 
            veri = strtok(NULL, " "); 
            sutun++;
        }

        satir++;
    }
    len = satir;
       
   /* Birinci matris çıktı
   for(int i=0;i<satir;i++)
    {
    	for(int j=0;j<satir;j++)
    	{	
    		
            printf("%d ", matris1[i][j]);
    	
    	}
        printf("\n");
    }*/

/*---------------------------------------------------*/
    FILE *dosya2;
    dosya2 = fopen("inputB.txt", "r");
    char myString2[100]; 
    int satir2=0;
    while (fgets(myString2, sizeof(myString2), dosya2) != NULL) {
        //printf("%s", myString);

        char *veri = strtok(myString2, " ");
        int sutun = 0;

        while (veri != NULL && sutun < 7) {
            matris2[satir2][sutun] = atoi(veri); 
            veri = strtok(NULL, " "); 
            sutun++;
        }

        satir2++;
    }
    
    

  /*  İkinci matris çıktı
   for(int i=0;i<satir;i++)
    {
    	for(int j=0;j<satir;j++)
    	{	
    		
            printf("%d ", matris2[i][j]);
    	
    	}
        printf("\n");
    }
    */
}

void *carp(void *args) {
    arg *carpim = (arg *)args;
    


    int i = carpim->yeni_satir;
    int j = carpim->yeni_sutun;

    result[i][j] = 0;
    pthread_mutex_lock(&lock);
    for (int k = 0; k < len; ++k) {
        tempSum+=matris1[i][k] * matris2[k][j];
        result[i][j]= tempSum;
    }
    tempSum=0;
    pthread_mutex_unlock(&lock);
    
}




void thread_olustur() {
    pthread_t p[7][7];
    
   for (int i = 0; i < len; i++) {
        
        for (int j = 0; j < len; j++) {
            
            arg *arguman = malloc(sizeof(arg));
            arguman->yeni_satir = i;
            arguman->yeni_sutun = j;
            pthread_create(&p[i][j], NULL, carp, (void *)arguman);
            pthread_join(p[i][j], NULL);
            
          
            
        }
    }
        
}

void cikti_yazdir()
{
    for (int i =0;i<len;i++)
        {
            for(int j=0;j<len;j++)
            {
                printf("%d \t",result[i][j]);
                
            }
            printf("\n");
        }
}


int main() 
{
    
    dosya_oku();
    printf("Matris Boyutu: %d x %d \n",len,len);
    if(len>7)
    {
        printf("Matris boyutu maksimum 7x7 olabilir.\n");
        return 0;
    }

    else
    {
        
        thread_olustur();
        cikti_yazdir();      
        return 0;

    }
   
}

