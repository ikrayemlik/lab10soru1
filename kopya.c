#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
1) Bir sýnýftaki öðrencilerin numarasý, adý, vize notu ve final notu bilgileri üzerinde
çeþitli iþlemler yapabilecek bir program yazýnýz. Programýn özellikleri aþaðýda
verilmiþtir:
a) Program bir ana menü ile açýlacak. Menüde olacak seçenekler þu þekildedir:
1- Yeni Kayýt Ekleme
2- Kayýt Listeleme
3- Kayýt Güncelleme
4- Sýnýf Ortalamasý Hesapla
5- Ortalamaya Göre En Baþarýlý Öðrenci Bilgisini Göster
b) Program hafýzadan minimum miktarda alan tüketmelidir. Bunun için dinamik
hafýza yöntemi gerçekleþtiriniz. Örneðin ne kadar öðrenci bilgisi tutuluyorsa
hafýzadan o kadar alan tüketilmelidir.
c) Kayýt listeleme seçeneði numaraya göre ve nota göre olabilir. Kullanýcý
öðrencileri vize veya final notuna uygulanacak üst veya alt limitlere göre
listeleyebilmelidir.
d) Kayýt güncelleme öðrenci numarasýna göre olacak.
*/


struct ogrenci{
       int no;
       char name[40];
       int vizenot;
       int finalnot;
       struct ogrenci* next;
};

typedef struct ogrenci node;


node *listeolusturma()
{
    int n,i;
    node *head=NULL;
    node* p=NULL;
    printf("kac ogrenci kayidi girilecek:  ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        node* newnode=(node *)malloc(sizeof(node));
        printf("%d. ogrencinin numarasini giriniz:  ",i+1);
        scanf("%d",&newnode->no);
        printf("%d. ogrencinin adini giriniz:  ",i+1);
        scanf("%s",newnode->name);
        printf("%d. ogrencinin vize notunu giriniz:  ",i+1);
        scanf("%d",&newnode->vizenot);
        printf("%d. ogrencinin final notunu giriniz:  ",i+1);
        scanf("%d",&newnode->finalnot);
        newnode->next=NULL;

        if(head==NULL)
        {
            head=newnode;
            p=newnode;
        }
        else
        {
            p->next=newnode;
            p=newnode;
        }
    }


    return head;
}


node* yenikayit(node* head) {
    int stdno;
    node* p=head;
    node* q=NULL;
    node* newnode = (node*)malloc(sizeof(node));

    printf("Yeni ogrenci numarasini giriniz: ");
    scanf("%d", &newnode->no);

    printf("Yeni ogrenci adini giriniz: ");
    scanf("%s", newnode->name);

    printf("Yeni ogrencinin vize notunu giriniz: ");
    scanf("%d", &newnode->vizenot);

    printf("Yeni ogrencinin final notunu giriniz: ");
    scanf("%d", &newnode->finalnot);

    printf("Daha once yeni kaydin eklenecegi ogrenci numarasini giriniz: ");
    scanf("%d", &stdno);


    if (p->no == stdno) { // Baþa ekleme
        newnode->next = p;
        head = newnode;
    } else {
        while (p != NULL && p->no != stdno) {
            q = p;
            p = p->next;
        }
        if (p != NULL) {
            q->next = newnode;
            newnode->next = p;
        }
        else
        {
            printf("ogrenci bulunamadi");
            free(newnode);
        }
    }

    return head;
}


void traverselist(node * head)
{
    int a=1;
    node *p=head;

    while(p!=NULL)
    {
        printf("%d-) %d %s %d %d",a,p->no,p->name,p->vizenot,p->finalnot);
        p=p->next;
        a++;
    }
}

node* updatenode(node* head)
{
    int degisimno;
    printf("Lutfen guncellemek istenen ogrenci kaydi icin ogrencinin numarasini giriniz: ");
    scanf("%d", &degisimno);

    node* current = head;

    while (current != NULL)
    {
        if (current->no == degisimno)
        {
            printf("Ogrencinin yeni numarasi: ");
            scanf("%d", &current->no);
            printf("Ogrencinin yeni adi: ");
            scanf("%s", current->name);
            printf("Ogrencinin yeni vize notu: ");
            scanf("%d", &current->vizenot);
            printf("Ogrencinin yeni final notu: ");
            scanf("%d", &current->finalnot);
            return head; // Güncelleme yapýldýktan sonra döngüyü sonlandýr
        }
        current = current->next;
    }
    printf("kayit bulunamadi\n");
    return head;
}


float hesaplaortalama(node* head)
{
    float toplamvize=0;
    float toplamfinal=0;
    int ogrencisayisi=0;

    node* current = head;

    while(current!=NULL)
    {
        toplamvize+=current->vizenot;
        toplamfinal+=current->finalnot;
        ogrencisayisi++;
        current=current->next;
    }

    float vizeortalamasi=(float)toplamvize/ogrencisayisi;
    float finalortalamasi=(float)toplamfinal/ogrencisayisi;
    float genelortalama=(vizeortalamasi+finalortalamasi)/2;

    return genelortalama;

}

node* enbasariliogrenci(node* head)
{

    node* current=head;
    node* enbarasili=NULL;
    float maxortalama=-1;

    while(current!=NULL)
    {
        float vizeortalamasi=(float)(current->vizenot);
        float finalortalamasi=(float)(current->finalnot);
        float ogrenciortalamasi=(vizeortalamasi+finalortalamasi)/2;

        if(ogrenciortalamasi>maxortalama)
        {
            maxortalama=ogrenciortalamasi;
            enbarasili=current;
        }
        current=current->next;
    }
    return enbarasili;

}


int main()
{


    node* head;
    int secim=0;
    printf("1-Ogrenci Kayitlari Girme\n2- Yeni Kayit Ekleme\n3- Kayit Listeleme\n4- Kayit Guncelleme\n5- Sinif Ortalamasi Hesapla\n6- Ortalamaya Gore En Basarili Ogrenci Bilgisini Goster\n7-Cikis\n");
    while(1)
    {
        printf("\n1-7 arasi secim yapin :  ");
        scanf("%d",&secim);
        switch(secim)
        {
        case 1:
            head=listeolusturma();
            traverselist(head);
            break;
        case 2:
            head=yenikayit(head);
            traverselist(head);
            break;
        case 3:
            traverselist(head);
            break;
        case 4:
           head= updatenode(head);
            traverselist(head);
            break;
         case 5:
            if (head == NULL) {
            printf("once ogrenci kaydi eklemelisiniz.\n");
            } else {
            float ortalama = hesaplaortalama(head);
            printf("Sinif ortalamasi= %.2f\n", ortalama);
            }
            break;
        case 6:
            if (head == NULL) {
            printf("once ogrenci kaydi eklemelisiniz.\n");
            } else {
            node* enbasarili = enbasariliogrenci(head);
            printf("en basarili ogrenci bilgileri:\n");
            printf("No: %d\nAd: %s\nVize Notu: %d\nFinal Notu: %d\n", enbasarili->no, enbasarili->name, enbasarili->vizenot, enbasarili->finalnot);
            }
            break;
        case 7:
            exit(0); // Çýkýþ
            default:
            printf("gecersiz secim 1-7 arasinda secmelisiniz.\n");
            break;

        }
    }


    return 0;
}
