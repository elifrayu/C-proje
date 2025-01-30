/**
* @file Proje1.c
* @description Bu program, birim ve çalışan yönetim sistemini simüle eder. Program, birimlerin ve çalışanların bilgilerini dinamik olarak oluşturur, günceller, yazdırır ve dosyalara kaydeder.
* @assignment 1. Ödev - Çalışan ve Birim Yönetimi
* @date 23 Aralık 2024
* @author Elif Uyar, elifuyar@stu.fsm.edu.tr
*/
#include "Proje1.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_CALISAN 30
#define MAX_BIRIM 30

Birim ** birimler = NULL;
int birimSayisi=0;

Birim birimOlustur(char *birimAdi, unsigned short int birimKodu) {
    Birim yeniBirim;
    yeniBirim.birimAdi = (char *)malloc(30 * sizeof(char));
    if (yeniBirim.birimAdi == NULL) {
        printf("Birim adı için bellek ayrımı başarısız!\n");
        exit(EXIT_FAILURE);
    }

    strncpy(yeniBirim.birimAdi, birimAdi, 29);
    yeniBirim.birimAdi[29] = '\0';
    yeniBirim.birimKodu = birimKodu;

    yeniBirim.birimCalisanlar = (Calisan **)malloc(MAX_CALISAN * sizeof(Calisan *));
    if (yeniBirim.birimCalisanlar == NULL) {
        printf("Çalışanlar için bellek ayrımı başarısız!\n");
        free(yeniBirim.birimAdi);
        exit(EXIT_FAILURE);
    }

    // Çalışanlar dizisini NULL ile başlat
    for (int i = 0; i < MAX_CALISAN; i++) {
        yeniBirim.birimCalisanlar[i] = NULL;
    }

    return yeniBirim;
}

Calisan * calisanOlustur(const char *ad, const char *soyad, unsigned short int birimKodu, float maas, int girisYili) {
    Calisan *yeniCalisan = (Calisan *)malloc(sizeof(Calisan));
    if (yeniCalisan == NULL) {
        printf("Çalışan için bellek ayrımı başarısız!\n");
        return NULL;
    }

    yeniCalisan->calisanAdi = strdup(ad);
    yeniCalisan->calisanSoyadi = strdup(soyad);

    if (yeniCalisan->calisanAdi == NULL || yeniCalisan->calisanSoyadi == NULL) {
        printf("Ad veya soyad için bellek ayrımı başarısız!\n");
        free(yeniCalisan);
        return NULL;
    }

    yeniCalisan->birimKodu = birimKodu;
    yeniCalisan->maas = maas;
    yeniCalisan->girisYili = girisYili;

    printf("Çalışan oluşturuldu: %s %s, Maaş: %.2f\n", ad, soyad, maas);
    return yeniCalisan;
}

void birimEkle(Birim yeniBirim) {
    if (yeniBirim.birimAdi == NULL) {
        printf("Hata: yeniBirim NULL!\n");
        return;
    }
    // Birimler listesini genişletmek
    if (birimler == NULL) {
        birimler = (Birim **)malloc(sizeof(Birim *));
    } else {
        birimler = (Birim **)realloc(birimler, (birimSayisi + 1) * sizeof(Birim *));
    }

    if (birimler == NULL) {
        printf("Bellek tahsisi başarısız!\n");
        return;
    }

    // Yeni birim için bellek ayırma
    birimler[birimSayisi] = (Birim *)malloc(sizeof(Birim));
    if (birimler[birimSayisi] == NULL) {
        printf("Yeni birim için bellek tahsisi başarısız!\n");
        return;
    }

    // Yeni birimi bellekteki alana kopyala
    *(birimler[birimSayisi]) = yeniBirim;

    // Birim sayısını artır
    birimSayisi++;

    printf("Birim başarıyla eklendi: %s (Kodu: %u)\n", yeniBirim.birimAdi, yeniBirim.birimKodu);
    printf("Güncel birim sayısı: %d\n", birimSayisi);
}

void calisanEkle(Birim *birim, Calisan *yeniCalisan) {
    if (birim == NULL || birim->birimAdi == NULL || birim->birimCalisanlar == NULL || yeniCalisan == NULL) {
        printf("Geçersiz birim veya çalışan bilgisi!\n");
        return;
    }

    // Çalışan eklemek için boş yer bulma
    for (int i = 0; i < MAX_CALISAN; i++) {
        if (birim->birimCalisanlar[i] == NULL) { // NULL kontrolü
            birim->birimCalisanlar[i] = yeniCalisan; // Çalışanı ekle
            printf("Çalışan başarıyla eklendi: %s %s\n", yeniCalisan->calisanAdi, yeniCalisan->calisanSoyadi);
            return;
        }
    }

    printf("Çalışan kapasitesi dolu!\n");
}

// Çalışan bilgilerini yazdırma
void calisanBilgileriYazdir(Calisan *calisan) {
    if (calisan == NULL) {
        printf("Geçersiz çalışan bilgisi! Çalışan NULL.\n");
        return;
    }

    printf("Çalışan kontrol ediliyor: %s %s, Maaş: %.2f\n",
           calisan->calisanAdi ? calisan->calisanAdi : "NULL",
           calisan->calisanSoyadi ? calisan->calisanSoyadi : "NULL",
           calisan->maas);

    if (calisan->maas > 0) {
        printCalisan(calisan);
    } else {
        printf("Geçersiz veya boş çalışan bilgisi.\n");
    }
}


void printCalisan(Calisan *calisan) {
    if (calisan == NULL) {
        printf("Geçersiz çalışan!\n");
        return;
    }
    printf("Çalışan Adı: %s\n", calisan->calisanAdi);
    printf("Çalışan Soyadı: %s\n", calisan->calisanSoyadi);
    printf("Çalışanın Birim Kodu: %hd\n", calisan->birimKodu);
    printf("Çalışan Maaşı: %.2f\n", calisan->maas);
    printf("Çalışanın Giriş Yılı: %d\n", calisan->girisYili);
}

// Birim bilgisi yazdırma
void birimBilgileriYazdir(Birim birim) {
    if (birim.birimAdi == NULL) {
        printf("Geçersiz birim!\n");
        return;
    }
    printf("Birim Bilgileri:\n");
    printf("Birim Adı: %s\n", birim.birimAdi);
    printf("Birim Kodu: %u\n", birim.birimKodu);
    printf("Çalışanlar:\n");

    // Çalışanlar dizisini dolaşarak yazdırma
    for (int i = 0; i < MAX_CALISAN; i++) {
        // Çalışanın NULL olmadığını ve maaşının geçerli olduğunu kontrol et
        if (birim.birimCalisanlar[i] != NULL && birim.birimCalisanlar[i]->maas > 0) {
            printf("  Ad: %s, Soyad: %s, Maaş: %.2f, Giriş Yılı: %d\n",
                   birim.birimCalisanlar[i]->calisanAdi,
                   birim.birimCalisanlar[i]->calisanSoyadi,
                   birim.birimCalisanlar[i]->maas,
                   birim.birimCalisanlar[i]->girisYili);
        }
    }
}

// Birim bilgilerini yazdırma
void birimleriYazdir() {
    if (birimSayisi == 0 || birimler == NULL) {  // Listenin doluluğu kontrolü
        printf("Hiçbir birim mevcut değil!\n");
        return;
    }
    printf("Toplam birim sayısı: %d\n", birimSayisi);  // Toplam birim sayısını yazdırıyoruz.

    for (int i = 0; i < birimSayisi; i++) {
        Birim *birim = birimler[i];

        if (birim == NULL) {  // Birim geçerli değilse hata mesajı
            printf("Geçersiz birim verisi.\n");
            continue;
        }

        printf("Birim %d:\n", i + 1);  // Birim bilgisi yazdırma
        printf("Birim Adı: %s\n", birim->birimAdi);
        printf("Birim Kodu: %u\n", birim->birimKodu);

    }
}


float birimMaasOrtalamasi(Birim birim) {
    if (birim.birimAdi == NULL || birim.birimCalisanlar == NULL) {
        printf("Geçersiz birim veya çalışan bilgisi!\n");
        return 0.0;
    }

    float toplamMaas = 0.0;
    int calisanSayisi = 0;

    for (int i = 0; i < 20; i++) {
        Calisan *calisan = birim.birimCalisanlar[i];
        if (calisan != NULL && birim.birimCalisanlar[i]->maas > 0) { // Geçerli maaşı kontrol et
            toplamMaas += birim.birimCalisanlar[i]->maas;
            calisanSayisi++;
        }
    }

    if (calisanSayisi == 0) {
        printf("Bu birimde çalışan bulunmamaktadır.\n");
        return 0.0;
    }

    return toplamMaas / calisanSayisi;
}

void ortalamaninUstundekiCalisanlariListele(Birim birim) {  

    if (birim.birimAdi == NULL || birim.birimCalisanlar == NULL) {
        printf("Geçersiz birim veya çalışan bilgisi!\n");
        return;
    }

    float ortalama = birimMaasOrtalamasi(birim);  // Birimin maaş ortalamasını hesapla
    printf("Birim: %s (Kodu: %hu) - Maaş Ortalaması: %.2f\n", birim.birimAdi, birim.birimKodu, ortalama);

    printf("Ortalamanın üzerinde maaş alan çalışanlar:\n");
    for (int i = 0; i < MAX_CALISAN; i++) {
        // Çalışanın NULL olup olmadığını ve maaşının ortalamanın üzerinde olup olmadığını kontrol et
        if (birim.birimCalisanlar[i] != NULL && 
            birim.birimCalisanlar[i]->maas > ortalama && 
            birim.birimCalisanlar[i]->birimKodu == birim.birimKodu) {  // Birim kodu kontrolü
            printf("Ad: %s, Soyad: %s, Maaş: %.2f\n",
                   birim.birimCalisanlar[i]->calisanAdi,
                   birim.birimCalisanlar[i]->calisanSoyadi,
                   birim.birimCalisanlar[i]->maas);
        }
    }
}
void birimdekiEnYuksekMaasliCalisan() {
    for (int i = 0; i < birimSayisi; i++) {
        Birim *birim = birimler[i];

        // Birim veya çalışanlar dizisi NULL ise geçersiz veri
        if (birim == NULL || birim->birimCalisanlar == NULL) {
            printf("Birim %d NULL! Geçersiz veri.\n", i + 1);
            continue;
        }

        float maxMaas = 0.0;
        Calisan *enYuksekMaasliCalisan = NULL;

        for (int j = 0; j < MAX_CALISAN; j++) {
            Calisan *calisan = birim->birimCalisanlar[j];

            // Çalışan geçerli mi, NULL değilse
            if (calisan == NULL) {
                continue;  // Çalışan NULL ise geç
            }

            // Maaşın en yüksek olup olmadığını kontrol et
            if (calisan->maas > maxMaas && calisan->birimKodu == birim->birimKodu) {
                maxMaas = calisan->maas;
                enYuksekMaasliCalisan = calisan;
            }
        }

        if (enYuksekMaasliCalisan != NULL) {
            printf("Birim: %s (Kodu: %hu) - En Yüksek Maaş Alan Çalışan:\n", birim->birimAdi, birim->birimKodu);
            printf("Ad: %s, Soyad: %s, Maaş: %.2f\n",
                   enYuksekMaasliCalisan->calisanAdi,
                   enYuksekMaasliCalisan->calisanSoyadi,
                   enYuksekMaasliCalisan->maas);
        } else {
            printf("Birim: %s (Kodu: %hu) - Çalışan bulunamadı.\n", birim->birimAdi, birim->birimKodu);
        }
    }
}

void maasGuncelle(float yeniMaas) {
    for (int i = 0; i < birimSayisi; i++) {
        Birim *birim = birimler[i];

        if (birim == NULL || birim->birimCalisanlar == NULL) {
            continue; // Birim veya çalışanlar dizisi NULL ise, geçiş yap
        }

        for (int j = 0; j < MAX_CALISAN; j++) {
            Calisan *calisan = birim->birimCalisanlar[j];

            // Çalışanın NULL olup olmadığını kontrol et
            if (calisan != NULL && calisan->maas > 0 && calisan->maas < yeniMaas && (2024 - calisan->girisYili) > 10) {
                printf("Çalışanın maaşı güncellendi: %s %s, Eski Maaş: %.2f, Yeni Maaş: %.2f\n",
                       calisan->calisanAdi, calisan->calisanSoyadi, calisan->maas, yeniMaas);
                calisan->maas = yeniMaas;
            }
        }
    }
}

void birimleriVeCalisanlariDosyayaYaz(const char *birimDosyaAdi, const char *calisanDosyaAdi) {
    // Birim bilgileri dosyasını aç
    FILE *birimDosya = fopen(birimDosyaAdi, "w");
    if (birimDosya == NULL) {
        printf("Birim dosyası açılamadı: %s\n", birimDosyaAdi);
        return;
    }

    // Çalışan bilgileri dosyasını aç
    FILE *calisanDosya = fopen(calisanDosyaAdi, "w");
    if (calisanDosya == NULL) {
        printf("Çalışan dosyası açılamadı: %s\n", calisanDosyaAdi);
        fclose(birimDosya);
        return;
    }
    
    // Birimler ve çalışanları yazma
    for (int i = 0; i < birimSayisi; i++) {
        if (birimler[i]->birimAdi == NULL) {
            continue;
        }

        // Birim bilgilerini yaz
        fprintf(birimDosya, "Birim Adı: %s\n", birimler[i]->birimAdi);
        fprintf(birimDosya, "Birim Kodu: %u\n\n", birimler[i]->birimKodu);

        // Çalışan bilgilerini yaz
        for (int j = 0; j < MAX_CALISAN; j++) {
            Calisan *calisan = birimler[i]->birimCalisanlar[j];
            if (calisan != NULL) { // Geçerli çalışan kontrolü
                // Çalışan bilgilerini yaz, ancak birim bilgisi eklemeden
                fprintf(calisanDosya, "Ad: %s, Soyad: %s, Maaş: %.2f, Giriş Yılı: %d\n",
                        calisan->calisanAdi,
                        calisan->calisanSoyadi,
                        calisan->maas,
                        calisan->girisYili);
            }
        }
    }

    fclose(birimDosya);
    fclose(calisanDosya);

    printf("Birimler %s dosyasına yazıldı.\n", birimDosyaAdi);
    printf("Çalışanlar %s dosyasına yazıldı.\n", calisanDosyaAdi);
}

void birimleriVeCalisanlariDosyadanOku(const char *birimDosyaAdi, const char *calisanDosyaAdi) {
    // Birim dosyasını aç
    FILE *birimDosya = fopen(birimDosyaAdi, "r");
    if (birimDosya == NULL) {
        printf("Birim dosyası açılamadı: %s\n", birimDosyaAdi);
        return;
    }

    // Çalışan dosyasını aç
    FILE *calisanDosya = fopen(calisanDosyaAdi, "r");
    if (calisanDosya == NULL) {
        printf("Çalışan dosyası açılamadı: %s\n", calisanDosyaAdi);
        fclose(birimDosya);
        return;
    }

    // Birim dosyasından okuma ve ekrana yazdırma
    printf("Birim Bilgileri:\n");
    char line[256];
    while (fgets(line, sizeof(line), birimDosya)) {
        printf("%s", line);  // Satırları olduğu gibi yazdır
    }
     
    // Çalışan dosyasından okuma ve ekrana yazdırma
    printf("\nÇalışan Bilgileri:\n");
    while (fgets(line, sizeof(line), calisanDosya)) {
        printf("%s", line);  // Satırları olduğu gibi yazdır
    }

    fclose(birimDosya);
    fclose(calisanDosya);

    printf("Birimler ve çalışanlar başarıyla ekrana yazdırıldı.\n");
}


void bellekSerbestBirak() {
    for (int i = 0; i < birimSayisi; i++) {
        if (birimler[i] != NULL) {
            // Birim adını serbest bırak
            if (birimler[i]->birimAdi != NULL) {
                free(birimler[i]->birimAdi);
            }

            // Çalışanlar dizisini serbest bırak
            if (birimler[i]->birimCalisanlar != NULL) {
                for (int j = 0; j < MAX_CALISAN; j++) {
                    // Çalışanları kontrol et ve serbest bırak
                    if (birimler[i]->birimCalisanlar[j] != NULL) {
                        if (birimler[i]->birimCalisanlar[j]->calisanAdi != NULL) {
                            free(birimler[i]->birimCalisanlar[j]->calisanAdi);
                        }
                        if (birimler[i]->birimCalisanlar[j]->calisanSoyadi != NULL) {
                            free(birimler[i]->birimCalisanlar[j]->calisanSoyadi);
                        }

                        // Çalışan nesnesini serbest bırak
                        free(birimler[i]->birimCalisanlar[j]);
                    }
                }
                // Çalışanlar dizisini serbest bırak
                free(birimler[i]->birimCalisanlar);
            }

            // Birim nesnesini serbest bırak
            free(birimler[i]);
        }
    }

    // Birimler dizisini serbest bırak
    free(birimler);
    birimler = NULL; // Belleği serbest bıraktıktan sonra işaretçiyi NULL yapıyoruz.
    birimSayisi = 0;

    printf("Bellek başarıyla serbest bırakıldı.\n");
}


