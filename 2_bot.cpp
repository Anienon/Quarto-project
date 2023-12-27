//1. bot
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

// funkcja sprawdzajaca wykorzystanie pionka wczesniej
int spr_wykorzystania(char postawione[17], int pionek, char pionki[16])
{
    for(int i = 0; i < 17; i++)
    {
        if(pionki[pionek] == postawione[i]) return 0;
    }
    return 1;
}
int mojZapis(char pionek)//chce zapisac je binarnie na potrzeby funkcji ze sprawdzeniem zwyciestwa. Przy okazji konwersja na INT
{
	if(pionek >= '0' && pionek <= '9')pionek -= 48;// 0 to 48 w ASCII, 1 to 49 itd
	else if(pionek >= 'A' && pionek <= 'F')pionek -= 55; //dla A = 65 chcemy warosc 10, B = 66 11 itd.
	//jesli dostalismy pionek spoza przedzialu zwracamy po prostu 1 0 0 0 0, czyli 16 (obsluga bledu, mozna zmienic)
	else return 16;
	
	
	return (int)pionek;
}
int spr_zwyciestwa(char plansza[4][4])
{
	int il_zwyciestw = 0, licznik; //ilosc zwyciestw, zmienna pomocnicz
	int cechy[4] = {1,1,1,1}; //tablica ktora zlicza ile pionkow ma jakie cechy
	int sprawdzenie; //zmienna pomocnicza do sprawdzenia zwyciestwa
	
	cechy[2] = 1; //jesli nie zrobimy tego, to zwyciestwo zawsze wejdzie nam raz z domyslu na poczatku 
	for(int i = 0; i < 4 ; i++)// i to nasz numer kolumny, sprawdzamy czy jakias kolumna wygrywa pionowo
	{
		licznik = 1; //resetujemy licznik dla kazdej kolumny
		for(int h = 0; h < 4 ; h++)//sprawdzamy warunek z poprzedniego przejscia, zerujemy tablice
		{
			if(licznik) //chcemy dla jednej kolumny zliczyc sprawdzic czy istnieje jakas wspolna cecha, a nie ile wspolnych cech maja wszystkie pionki (bo moga byc maks. dwie)
				if(cechy[h] == 4 || cechy[h] == 0)
				{
					licznik--;//licznik to '0', warunek odbedzie sie raz
					il_zwyciestw++;
				}
				
				
			cechy[h] == 0;//zerowanie
		}
		for(int j = 0; j < 4; j++)
		{
			sprawdzenie == mojZapis(plansza[i][j]);//zapisujemy na 4 pierwszych bitach chara cechy pionkow
			while(licznik < 4)
			{
				cechy[licznik] += sprawdzenie % 2; //rozbijamy pionek na pojedyncze cechy/bity. jesli na danym bicie kazdy pionek ma 0 to suma to 0, jesli 1, to 4
				sprawdzenie /= 2;//przechodzimy na kolejny bit
				licznik++; //patrzymy na kolejna ceche
			}
		}		
	}
	
	cechy = {1,1,1,1}; //jesli nie zrobimy tego mozemy miec falszywy win condition
	for(int i = 0; i < 4 ; i++)// i to nasz numer wiersza, sprawdzamy czy jakis wiersz wygrywa poziomo
	{
		licznik = 1; //resetujemy licznik dla kazdego wiersza
		for(int h = 0; h < 4 ; h++)//sprawdzamy warunek z poprzedniego przejscia, zerujemy tablice
		{
			if(licznik) //chcemy dla jednego wiersza zliczyc sprawdzic czy istnieje jakas wspolna cecha
				if(cechy[h] == 4 || cechy[h] == 0)
				{
					licznik--;//licznik to '0', warunek odbedzie sie raz
					il_zwyciestw++;
				}
				
				
			cechy[h] == 0;//zerowanie
		}
		for(int j = 0; j < 4; j++)
		{
			sprawdzenie == mojZapis(plansza[j][i]);//zapisujemy na 4 pierwszych bitach chara cechy pionkow
			while(licznik < 4)
			{
				cechy[licznik] += sprawdzenie % 2; //rozbijamy pionek na pojedyncze cechy/bity. jesli na danym bicie kazdy pionek ma 0 to suma to 0, jesli 1, to 4
				sprawdzenie /= 2;//przechodzimy na kolejny bit
				licznik++; //patrzymy na kolejna ceche
			}
		}		
	}
	cechy = {0,0,0,0};//znowu reset
	for(int i = 0; i < 4; i++) //dla ukosu 2
	{
		licznik = 0;
		sprawdzenie == mojZapis(plansza[3 - i][i]);
		while(licznik < 4)
		{
			cechy[licznik] += sprawdzenie % 2; //rozbijamy pionek na pojedyncze cechy/bity. jesli na danym bicie kazdy pionek ma 0 to suma to 0, jesli 1, to 4
			sprawdzenie /= 2;//przechodzimy na kolejny bit
			licznik++; //patrzymy na kolejna ceche
		}
	}
	licznik = 1;
	for(int h = 0 ; h < 4; h++)
	{
		if(licznik)
			if(cechy[h] == 0 || cechy[h] == 4)
			{
				il_zwyciestw++;
				licznik--;
			}
	}
	
	for(int i = 0; i < 4; i++) //dla ukosu 1 
	{
		licznik = 0;
		sprawdzenie == mojZapis(plansza[i][i]);
		while(licznik < 4)
		{
			cechy[licznik] += sprawdzenie % 2; //rozbijamy pionek na pojedyncze cechy/bity. jesli na danym bicie kazdy pionek ma 0 to suma to 0, jesli 1, to 4
			sprawdzenie /= 2;//przechodzimy na kolejny bit
			licznik++; //patrzymy na kolejna ceche
		}
	}
	licznik = 1;
	for(int h = 0 ; h < 4; h++)
	{
		if(licznik)
			if(cechy[h] == 0 || cechy[h] == 4)
			{
				il_zwyciestw++;
				licznik--;
			}
	}
	
	
	return il_zwyciestw;
}
int main(int argc, char *argv[])
{
    char plansza[4][4], postawione[17]; //pozniej program proboje przypisywac wartosc -1
    char pionki[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    int licznik = 0;//zmienna pomocnicza
    srand(time(NULL));//inicjalizacja generatora liczb pseudolosowych
    for(int i = 1; i < 16; i++)//"zerowanie" tablicy
        postawione[i] = 16;

    // "Wizualizujemy" plansze w tablicy: plansza. Zapisujemy, ktore figury zostaly juz wykorzzystane.
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            plansza[i][j] = argv[1][licznik];
            if(argv[1][licznik] != 'p')
                postawione[licznik] = argv[1][licznik];
            licznik++;
        }
    postawione[licznik] = argv[1][licznik]; //oznaczamy pionek ktory zostal nam podany jako juz ustawiony
   
    
    
    
    int wiersz, kolumna, pionek;
    
  /*  for(int i = 0, i < 17, i++)
    {
    	pionek = pionki[i];
    	if(spr_wykorzystania(postawione, pionek, pionki) == 1)
    	{
    		for(int j = 0, j < 4 ; j++)
    		{
    			for(int k = 0; k < 4 ; k++)
    			{
    				if(plansza[j][k] == -1)
    				{
						plansza[j][k] = pionek;
					}
				}
			}
		}
    	
	}
	*/
	
    do
    {
        wiersz = rand() % 4;
        kolumna = rand() % 4;
    } while(plansza[wiersz][kolumna] != 'p');

    do{
        pionek = rand()%16;
    } while(spr_wykorzystania(postawione,pionek, pionki) == 0);


    cout << wiersz << kolumna << pionki[pionek] << "\n";
    return 0;
}
