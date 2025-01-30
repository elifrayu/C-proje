all: makeProje run

# Çalıştırılabilir dosya oluştur
makeProje: main.o Proje1.o
	gcc main.o Proje1.o -o makeProje

# main.o oluştur
main.o: main.c
	gcc -c main.c -o main.o

# Proje1.o oluştur
Proje1.o: Proje1.c Proje1.h
	gcc -c Proje1.c -o Proje1.o

# Temizlik işlemi
clean:
	rm -f *.o makeProje

# Programı çalıştır
run:
	./makeProje calisanlar.txt birimler.txt