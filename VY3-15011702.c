#include <stdio.h>
#include <stdlib.h>


void Dosya_Okuma();
void Mst (int **arr, int satir, int sutun,int k);

int main()
{
    Dosya_Okuma();
    return 0;
}


   void Dosya_Okuma(){
        FILE *dosya;
           dosya=fopen("data.txt","r");
            char temp[512];char *pch;
            int satir=0;int sutun=0;int sutuntemp;
                while(fgets(temp,512,dosya)!=NULL){
                    pch=strtok(temp,",");
                    sutuntemp=sutun;
                    sutun=0;
                        while(pch!=NULL){
                            sutun++;
                            pch=strtok(NULL," ,");
                        }
                satir++;
   }
   sutun=sutuntemp;
   printf("sutun satir %d %d",sutun,satir);
        int i,j;
        int *arr[satir];
            for (i=0; i<satir; i++){
            arr[i] = (int *)malloc(sutun * sizeof(int));
            }


            if((dosya=fopen("data.txt","r"))!=NULL){
                printf("Dosya Acildi.\n Okunan Matris:\n");
                     i=0;
                     j=0;
                        do{
                            fscanf(dosya,"%d,",&arr[i][j]);
                            if(j<sutun-1){
                                    j++;
                                }
                                else{
                                    j=0;
                                    i++;
                                }

                        }while(!feof(dosya));


                        for(i=0;i<satir;i++){
                                for(j=0;j<sutun;j++){
                                    printf("%d ",arr[i][j]);
                                }
                                printf("\n");
                        }
                        fclose(dosya);
                   }
                   else{
                        printf("dosya açýlamadý.");
                        exit(0);
                   }
                   int k;
                   printf("K sayisini giriniz:");
                   scanf("%d",&k);
                   printf("\n");
                   Mst(arr,satir,sutun,k);

   }

Mst(int **arr,int satir,int sutun,int k){
       int i,j;
       int TempArray[satir][sutun];
       /*Geçici Array oluþturuldu ayný düðümleri almamak için kullanýldý*/
       for(i=0;i<satir;i++){
            for(j=0;j<sutun;j++){
                TempArray[i][j]=arr[i][j];
            }
        }

        /*Tablo oluþturulup bütün geçiþler tabloya yazýldý*/
        int Tablo[satir*(satir-1)][3];
        int z=0;
            for(i=0;i<satir;i++){
                for(j=0;j<sutun;j++){
                    if(arr[i][j]!=0 && i+1!=j+1 && arr[i][j]!=-1){
                        Tablo[z][0]=i+1;
                        Tablo[z][1]=j+1;
                        Tablo[z][2]=arr[i][j];
                        z++;
                        arr[j][i]=-1;
                    }
                }
            }

            /*Tabloyu minimum geçiþten maksimum geçiþe doðru sýraladýk*/
                        int temp=0;
                        for(i=0;i<z;i++){
                            for(j=i+1;j<z;j++){
                                if(Tablo[i][2]>Tablo[j][2]){
                                    temp=Tablo[i][0];
                                    Tablo[i][0]=Tablo[j][0];
                                    Tablo[j][0]=temp;

                                    temp=Tablo[i][1];
                                    Tablo[i][1]=Tablo[j][1];
                                    Tablo[j][1]=temp;

                                    temp=Tablo[i][2];
                                    Tablo[i][2]=Tablo[j][2];
                                    Tablo[j][2]=temp;
                                }
                            }
                        }

                        /*Elimizde küçükten büyüðe sýralý geçiþ tablosu oluþtu ve onu yazdýrdýk.*/
                        for(i=0;i<z;i++){
                            printf("%d -- %d ==> %d\n",Tablo[i][0],Tablo[i][1],Tablo[i][2]);
                        }



                        /*Burada MST YAPICAZ KAPALI YOL OLUÞTURAN DÜÐÜMLERÝ ALMICAZ....*/
                        static int dizi[100];
                        int MstTablo[500][3];
                        int cevrim=satir-k;
                        int loop=0;
                        int count=0;
                        int t=0;
                        int x=1;
                        i=0;
                        int yer;
                        int yer1;

                        while(loop<cevrim){
                                yer=Tablo[i][0];
                                yer1=Tablo[i][1];
                                if(dizi[yer]==0 && dizi[yer1]==0){
                                    dizi[yer]=x;
                                    dizi[yer1]=x;
                                    MstTablo[t][0]=Tablo[i][0];
                                    MstTablo[t][1]=Tablo[i][1];
                                    MstTablo[t][2]=Tablo[i][2];
                                    count=count+2;
                                    x++;
                                    t++;
                                    loop++;
                                }
                                else if(dizi[yer]==0 && dizi[yer1]!=0){
                                        dizi[yer]=dizi[yer1];
                                         MstTablo[t][0]=Tablo[i][0];
                                        MstTablo[t][1]=Tablo[i][1];
                                        MstTablo[t][2]=Tablo[i][2];
                                        count++;
                                        t++;
                                        loop++;
                                }
                                else if(dizi[yer]!=0 && dizi[yer1]==0){
                                        dizi[yer1]=dizi[yer];
                                         MstTablo[t][0]=Tablo[i][0];
                                        MstTablo[t][1]=Tablo[i][1];
                                        MstTablo[t][2]=Tablo[i][2];
                                        count++;
                                        t++;
                                        loop++;
                                }
                                else if(dizi[yer]!=0 && dizi[yer1]!=0 && dizi[yer]!=dizi[yer1]){
                                        int bul;
                                        int degis;
                                        bul=dizi[yer];
                                        degis=dizi[yer1];

                                     for(j=1;j<satir+1;j++){
                                        if(dizi[j]==bul){
                                            dizi[j]=degis;
                                        }
                                    }

                                    MstTablo[t][0]=Tablo[i][0];
                                    MstTablo[t][1]=Tablo[i][1];
                                    MstTablo[t][2]=Tablo[i][2];
                                    t++;
                                    loop++;
                                }
                                else if(dizi[yer]!=0 && dizi[yer1]!=0 && dizi[yer]==dizi[yer1]){
                                    //printf("kapalý yol %d %d \n",Tablo[i][0],Tablo[i][1]);

                                }
                                i++;
                        }



                        printf("MST :\n");
                        for(j=0;j<t;j++){
                            printf("%d -- %d ==> %d\n",MstTablo[j][0],MstTablo[j][1],MstTablo[j][2]);
                        }
                        printf("\n");
                        for(j=1;j<satir+1;j++){
                            printf("%d ",dizi[j]);
                        }



                        int enk;
                        int m=0;
                        int n=1;
                        int Mesafe[satir+k];
                        int p=0;
                        printf("\n\n");
                        for(i=1; i<satir+1; i++){
                            if(dizi[i]!=0 && dizi[i]!=-1){
                                      enk=dizi[i];
                                        for(j=i+1; j<satir+1; j++){
                                            if(dizi[j]<enk && dizi[j]!=0 && dizi[j]!=-1){
                                                enk=dizi[j];
                                            }
                                        }

                                        printf("%d.kume==>",n);
                                        for(m=1;m<satir+1;m++){
                                                if(dizi[m]==enk){
                                                    printf("%d,",m);
                                                    Mesafe[p]=m;
                                                    p++;
                                                    dizi[m]=-1;
                                                }
                                        }
                                        Mesafe[p]=-1;
                                        p++;
                                        printf("\n");
                                        n++;

                                //printf("\n%d enk=",enk);

                            }
                        }



                        for(i=1; i<satir+1; i++){
                            if(dizi[i]==0){


                                Mesafe[p]=i;
                                p++;
                                Mesafe[p]=-1;
                                p++;
                                printf("%d.kume==>%d\n",n,i);
                                n++;
                            }
                        }

                            printf("\n");
                        for(i=0; i<satir+k; i++){
                        printf("%d ",Mesafe[i]);
                        }

                        int KumeNo1,KumeNo2;
                        int KumeA[50];
                        int KumeB[50];
                        int Asay=0;
                        int Bsay=0;
                        int tut=0;
                        printf("\nKume numarasi giriniz:");
                        scanf("%d",&KumeNo1);

                        printf("\nKume numarasi giriniz:");
                        scanf("%d",&KumeNo2);

                        printf("\n");

                        for(i=0;i<satir+k;i++){
                                if(KumeNo1-1==tut && Mesafe[i]!=-1){
                                    //printf("%d ",Mesafe[i]);
                                    KumeA[Asay]=Mesafe[i];
                                    Asay++;
                                }
                                if(Mesafe[i]==-1){
                                    tut++;
                                }
                        }


                           printf("\n");
                        tut=0;
                        for(i=0;i<satir+k;i++){
                                if(KumeNo2-1==tut && Mesafe[i]!=-1){
                                    //printf("%d ",Mesafe[i]);
                                    KumeB[Bsay]=Mesafe[i];
                                    Bsay++;
                                }
                                if(Mesafe[i]==-1){
                                    tut++;
                                }
                        }

                        for(i=0;i<Asay;i++){
                            printf("%d ",KumeA[i]);
                        }

                        printf("\n");
                        for(i=0;i<Bsay;i++){
                            printf("%d ",KumeB[i]);
                        }


                        int yol=1000;
                        int c,d;
                        int dugum1,dugum2;

                        for(i=0;i<Asay;i++){
                            for(j=0;j<Bsay;j++){
                                    c=KumeA[i];
                                    d=KumeB[j];

                                    printf("\n %d -- %d===>%d",c,d,TempArray[c-1][d-1]);
                                    if(TempArray[c-1][d-1]!=0 && TempArray[c-1][d-1]<yol){
                                        yol=TempArray[c-1][d-1];
                                        dugum1=c;
                                        dugum2=d;
                                    }
                            }
                        }

                        if(yol!=1000){
                            printf("\nverilen iki kume arasinda en kisa yol= %d",yol);
                            printf("\n Dugumler %d ve %d",dugum1,dugum2);
                        }else{
                            printf("\n Verilen 2 kume arasinda yol yoktur.");
                        }










}





