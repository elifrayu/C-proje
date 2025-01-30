/**
* @file main.c
* @description Bu program, birim ve çalışan yönetim sistemini simüle eder. Program, birimlerin ve çalışanların bilgilerini dinamik olarak oluşturur, günceller, yazdırır ve dosyalara kaydeder.
* @assignment 1. Ödev - Çalışan ve Birim Yönetimi
* @date 23 Aralık 2024
* @author Elif Uyar, elifuyar@stu.fsm.edu.tr
*/
#include "Proje1.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Argüman kontrolü
    if (argc < 3) {
        fprintf(stderr, "Kullanım: %s <birim dosyası> <çalışan dosyası>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *birimFile = argv[1];
    const char *calisanFile = argv[2];
    printf("\n--- Dosyadan Okuyalım ---\n");
    birimleriVeCalisanlariDosyadanOku(calisanFile, birimFile);
    // 1. Birim ve Çalışan Oluşturma
    printf("\n--- 1. Birim ve Çalışan Oluşturma ---\n");
    Birim birim1 = birimOlustur("İnsan Kaynakları", 101);
    Birim birim2 = birimOlustur("Muhasebe", 102);
    Birim birim3 = birimOlustur("IT", 103);
    Birim birim4=birimOlustur("İK",104);
    
    Calisan *calisan1 = calisanOlustur("Ahmet", "Yılmaz", 101, 5000.0, 2010);
    Calisan *calisan2 = calisanOlustur("Ayşe", "Kara", 101, 5500.0, 2016);
    Calisan *calisan3 = calisanOlustur("Mehmet", "Demir", 103, 6000.0, 2018);
    Calisan *calisan4 = calisanOlustur("Fatma", "Ak", 102, 6500.0, 2017);

    // Birimleri global birimler dizisine ekliyoruz
    birimEkle(birim1);
    birimEkle(birim2);
    birimEkle(birim3);
    birimEkle(birim4);


    // 2. Çalışanları Birimlere Ekleme
    printf("\n--- 2. Çalışanları Birimlere Ekleme ---\n");
    calisanEkle(&birim1, calisan1);
    calisanEkle(&birim1, calisan2);
    calisanEkle(&birim3, calisan3);
    calisanEkle(&birim2, calisan4);
    

    // 3. Birim ve Çalışan Bilgilerini Yazdırma
    printf("\n--- 3. Birim ve Çalışan Bilgilerini Yazdırma ---\n");
    birimBilgileriYazdir(birim1);

    // 4. Çalışan Bilgilerini Yazdırma
    printf("\n--- 4. Çalışan Bilgilerini Yazdırma ---\n");
    calisanBilgileriYazdir(calisan1);
    calisanBilgileriYazdir(calisan4);

    // 5. Tüm Birimlerin Bilgilerini Yazdırma (tekrar)
    printf("\n--- 5. Tüm Birimlerin Bilgilerini Yazdırma ---\n");
    birimleriYazdir();

    // 6. Birim Maaş Ortalamasını Hesaplama
    printf("\n--- 6. Birim Maaş Ortalamasını Hesaplama ---\n");
    float ortalama1 = birimMaasOrtalamasi(birim1);
    float ortalama2 = birimMaasOrtalamasi(birim2);
    printf("Birim: %s - Maaş Ortalaması: %.2f\n", birim1.birimAdi, ortalama1);
    printf("Birim: %s - Maaş Ortalaması: %.2f\n", birim2.birimAdi, ortalama2);

    // 7. Maaş Ortalamasının Üstündeki Çalışanları Listeleme
    printf("\n--- 7. Maaş Ortalamasının Üstündeki Çalışanları Listeleme ---\n");
    ortalamaninUstundekiCalisanlariListele(birim1);

    // 8. Her Birimdeki En Yüksek Maaş Alan Çalışanları Listeleme
    printf("\n--- 8. Her Birimdeki En Yüksek Maaş Alan Çalışanları Listeleme ---\n");
    birimdekiEnYuksekMaasliCalisan();

    // 9. Maaş Güncelleme
    printf("\n--- 9. Maaş Güncelleme ---\n");
    maasGuncelle(18000.0);

    // 10. Tüm Bilgileri Dosyaya Yazma
    printf("\n--- 10. Dosyaya Yazma ---\n");
    birimleriVeCalisanlariDosyayaYaz(calisanFile, birimFile);

    // 11. Dosyadan Okuma
    printf("\n--- 11. Dosyadan Okuma ---\n");
    birimleriVeCalisanlariDosyadanOku(calisanFile, birimFile);

    // 12. Belleği Serbest Bırakma
    printf("\n--- 12. Belleği Serbest Bırakma ---\n");
    bellekSerbestBirak();

    printf("\n--- Test Tamamlandı ---\n");

    return 0;
}
