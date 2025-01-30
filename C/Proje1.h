
#ifndef PROJE1_H
#define PROJE1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char *calisanAdi;
    char *calisanSoyadi;
    unsigned short int birimKodu;
    float maas;
    int girisYili;
} Calisan;

typedef struct {
    char *birimAdi;
    unsigned short int birimKodu;
    Calisan **birimCalisanlar;
} Birim;

extern Birim ** birimler;
extern int birimSayisi;

// Birim ve Çalışan Oluşturma
Birim  birimOlustur(char *birimAdi, unsigned short int birimKodu);
//Calisan *calisanOlustur(char *calisanAdi, char *calisanSoyadi, unsigned short int birimKodu, float maas, int girisYili);
Calisan * calisanOlustur(const char *ad, const char *soyad, unsigned short int birimKodu, float maas, int girisYili);
// Ekleme Fonksiyonları

void birimEkle(Birim yeniBirim);
//void calisanEkle(Birim *birim, char *calisanAdi, char *calisanSoyadi, unsigned short int birimKodu, float maas, int girisYili);
 void calisanEkle(Birim *birim, Calisan  *yeniCalisan);


// Yazdırma Fonksiyonları
void calisanBilgileriYazdir(Calisan *calisan);
void birimBilgileriYazdir(Birim birim);
void birimleriYazdir();
void printCalisan(Calisan *calisan);

// Hesaplama Fonksiyonları
float birimMaasOrtalamasi(Birim birim);
void ortalamaninUstundekiCalisanlariListele(Birim birim);
void birimdekiEnYuksekMaasliCalisan();


void maasGuncelle(float yeniMaas);

// Dosya Giriş/Çıkış Fonksiyonları
//void tumBilgileriDosyayaYaz(Birim *birimler[], int birimSayisi, const char *dosyaAdi);
void birimleriVeCalisanlariDosyayaYaz( const char *birimDosyaAdi, const char *calisanDosyaAdi);
void birimleriVeCalisanlariDosyadanOku(const char *birimDosyaAdi, const char *calisanDosyaAdi);//

void bellekSerbestBirak();




#endif
