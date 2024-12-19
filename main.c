#include <stdio.h>
#include <string.h>

#define MAX_ISIM_UZUNLUGU 50 // Oyuncuların ad ve soyadlarının maksimum uzunluğu
#define MAX_OYUNCU 20 // Maksimum oyuncu sayısı

// Oyuncu bilgilerini tutacak struct tanımı
struct Oyuncular {
    char ad[MAX_ISIM_UZUNLUGU];
    char soyad[MAX_ISIM_UZUNLUGU];
    int oynananMac;
    int hataliPas;
    int dogruPas;
};

// Fonksiyon prototipleri
void ekle(struct Oyuncular oyuncu[], int *oyuncuSayisi, char ad[], char soyad[], int hataliPas, int dogruPas);
void yazdir(struct Oyuncular oyuncu[], int oyuncuSayisi);

int main() {
    struct Oyuncular oyuncu[MAX_OYUNCU];
    char ad[MAX_ISIM_UZUNLUGU], soyad[MAX_ISIM_UZUNLUGU];
    int hataliPas, dogruPas;
    int oyuncuSayisi = 0;

    // paslar.txt dosyasını okuma modunda açar
    FILE *paslar = fopen("paslar.txt", "r");
    if (paslar == NULL) {
        printf("paslar.txt bulunamadi\n");
        return 1; // Dosya açılmazsa program sonlandırılır
    }

    fscanf(paslar, "%*[^\n]\n"); // Başlık satırını atla

    // paslar.txt den oyuncu verilerini oku ve ekle fonksiyonunu çağır
    while (fscanf(paslar, "%s %s %d %d", ad, soyad, &hataliPas, &dogruPas) == 4) {
        ekle(oyuncu, &oyuncuSayisi, ad, soyad, hataliPas, dogruPas); // Bir maç için değerler eklenir
    }
    fclose(paslar); // paslar.txt dosyasını kapatır

    // Oyuncu verilerini yazdır
    yazdir(oyuncu, oyuncuSayisi);

    return 0;
}

// Oyuncu bilgilerini ekleyen/güncelleyen fonksiyon
void ekle(struct Oyuncular oyuncu[], int *oyuncuSayisi, char ad[], char soyad[], int hataliPas, int dogruPas) {
    // Oyuncu daha önce eklendi mi kontrol et
    for(int i = 0; i < *oyuncuSayisi; i++) {
        if(strcmp(oyuncu[i].ad, ad) == 0 && strcmp(oyuncu[i].soyad, soyad) == 0) {
            oyuncu[i].oynananMac += 1;
            oyuncu[i].hataliPas += hataliPas;
            oyuncu[i].dogruPas += dogruPas;
            return; // Veriler güncellendi fonksiyondan çık
        }
    }
    // Yeni oyuncu ekle
    strcpy(oyuncu[*oyuncuSayisi].ad, ad);
    strcpy(oyuncu[*oyuncuSayisi].soyad, soyad);
    oyuncu[*oyuncuSayisi].oynananMac = 1;
    oyuncu[*oyuncuSayisi].hataliPas = hataliPas;
    oyuncu[*oyuncuSayisi].dogruPas = dogruPas;
    (*oyuncuSayisi)++;
}

// Oyuncu verilerini toplam.txt dosyasına yazdıran fonksiyon
void yazdir(struct Oyuncular oyuncu[], int oyuncuSayisi) {
    FILE *toplam = fopen("toplam.txt", "w"); // toplam.txt dosyasını yazdır modunda açar
    if (toplam == NULL) {
        printf("toplam.txt yazilamadi\n");
        return; // Dosya açılmazsa fonksiyonu sonlandırır
    }

    // Dosyanın ilk satırına başlıkları yaz
    fprintf(toplam, "%-15s %-15s %-15s %-15s %-15s\n","Ad", "Soyad", "Maç Sayısı", "Hatalı Pas", "Doğru Pas");

    // Oyuncuları dosyaya yaz
    for (int i = 0; i < oyuncuSayisi; i++) {
        fprintf(toplam, "%-15s %-15s %-15d %-15d %-15d\n",
            oyuncu[i].ad,
            oyuncu[i].soyad,
            oyuncu[i].oynananMac,
            oyuncu[i].hataliPas,
            oyuncu[i].dogruPas);
    }

    fclose(toplam); // Dosyayı kapatır
    printf("Veriler toplam.txt dosyasina basariyla yazildi.\n");
}
