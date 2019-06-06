﻿#include "pch.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <conio.h>

//Zadanie p2
//1. Wczytać z pliku o podanej wcześniej nazwie dane postaci(marka, model, cena) i utworzyć z nich listę 
//jednokierunkową w kolejności zgodnej z wczytywaniem, wykorzystując funkcję, która dopisuje 
//telefon o jakichś danych na końcu listy zaczynającej się pod jakimś adresem.
//2. Wydrukować utworzoną listę, korzystając z funkcji drukującej listę zaczynającą się pod jakimś adresem.
//3. Napisać jedną funkcję(bez definiowania i wykorzystywania innych funkcji), która dla listy telefonów 
//zaczynającej się pod jakimś adresem :
//• oblicza i przekazuje przez parametr ilość telefonów, których marka zawiera jakiś ciąg znaków,
//• dopisuje telefon o jakichś danych, gdy na liście są wyłącznie telefony o cenie większej niż jakaś,
//• zwraca informację liczbową odnośnie ilości telefonów o unikalnej marce.
//4. Napisać jedną funkcję(bez definiowania i wykorzystywania innych funkcji), która dla listy telefonów 
//zaczynającej się pod jakimś adresem :
//• przenosi najdroższy telefon na miejsce tuż za telefonem, którego model ma najmniej liter,
//• usuwa co najwyżej jakąś liczbę elementów z początku listy, a zamiast nich dopisuje na końcu telefon o 
//jakiejś marce i jakimś modelu z ceną równą medianie ceny usuniętych elementów,
//• zamienia miejscami telefon o jakimś kolejnym numerze(o ile istnieje) z najtańszym telefonem i zwraca
//informację logiczną czy nastąpiła zamiana.
//5. Skasować utworzoną listę korzystając z funkcji kasującej listę zaczynającą się pod jakimś adresem.
//6. Ponownie wydrukować listę.
//Uwaga 1: słowo "jakiś" oznacza parametr funkcji.
//Uwaga 2 : Wykonując różne działania na liście(pkt 2 - 6) należy założyć, że nie znamy ilości elementów listy,
//więc trzeba uważać, aby nie odwoływać się do pola next elementu, który nie istnieje(czyli ma adres NULL);
//w szczególności należy sprawdzać, czy lista nie jest pusta(adres głowy == NULL) i czy ma ona dosyć 
//elementów(aby nie wykonywać operacji niemożliwych do wykonania).

using namespace std;


struct telefon
{
	string marka;
	string model;
	float cena;
	telefon *wsk_nastepnika;
};

// Iteracyjna funkcja drukująca zawartość listy
void drukuj_liste_it(telefon *adres_do_drukowania)
{

	cout << "\nOto wydrukowana lista:\n";
	while (adres_do_drukowania != NULL)
	{
		// wypisujemy zawartość elementu
		cout << (*adres_do_drukowania).marka << " ";
		cout << (*adres_do_drukowania).model << " ";
		cout << (*adres_do_drukowania).cena << " ";
		// i przechodzimy do następnego
		adres_do_drukowania = adres_do_drukowania->wsk_nastepnika;
	}
	cout << "\nKoniec listy\n\n";

};

telefon *wczytaj_na_liste(telefon *poczatek, string marka_przekazana,string model_przekazany, float cena_przekazana)
{
	telefon * glowa = NULL;
	telefon * nowy = new telefon;
	telefon * ostatni = poczatek;
	nowy->marka = marka_przekazana;
	nowy->cena = cena_przekazana;
	nowy->model = model_przekazany;
	if (poczatek->cena == NULL)//ten warunek sprawdza, czy mamy do czynienia z pierwszym elementem listy
	{	
		nowy->wsk_nastepnika = NULL;
		glowa = nowy;
		*poczatek = *glowa;
		return glowa;
	}
	else
	{	
		while (ostatni->wsk_nastepnika != NULL)
			ostatni = ostatni->wsk_nastepnika;
	    ostatni->wsk_nastepnika=nowy;
		nowy->wsk_nastepnika = NULL;	
		return poczatek;
	}
	
}

int pierwsza(telefon *adres_do_pierwszej_funkcji, int &ile_telefonow_zawiera_ciag, string ciag, string dopisana_marka, string dopisany_model, float dopisana_cena,float jakas_cena )
{
	
	telefon * ostatni = adres_do_pierwszej_funkcji;
	telefon *sprawdzenie_unikalnosci_marki = adres_do_pierwszej_funkcji;
	telefon *wewnetrzne_porownanie = adres_do_pierwszej_funkcji;
	int ile_telefonow_ma_unikalna_marke = 0;
	ile_telefonow_zawiera_ciag = 0;
	string marka_ciag;
	size_t znalezionaPozycja;
	bool czy_jest_tanszy=false;
	int ile_jest_na_liscie = 0;
	while (adres_do_pierwszej_funkcji != NULL)
	{
		ile_jest_na_liscie++;
		marka_ciag = adres_do_pierwszej_funkcji->marka;
		znalezionaPozycja = marka_ciag.find(ciag);

		if (znalezionaPozycja != std::string::npos)
		{
			ile_telefonow_zawiera_ciag++;
		}
		if (adres_do_pierwszej_funkcji->cena < jakas_cena)
			czy_jest_tanszy = true;
		adres_do_pierwszej_funkcji = adres_do_pierwszej_funkcji->wsk_nastepnika;
	}
	
		telefon * dopisany = new telefon;
		dopisany->marka = dopisana_marka;
		dopisany->model = dopisany_model;
		dopisany->cena = dopisana_cena;
		dopisany->wsk_nastepnika = NULL;

		
		if (czy_jest_tanszy == false)
		{
			while (ostatni->wsk_nastepnika != NULL)
			{
				ostatni = ostatni->wsk_nastepnika;
			}
			ostatni->wsk_nastepnika = dopisany;
			ile_jest_na_liscie++;
		}
		adres_do_pierwszej_funkcji = ostatni;//tu jest blad bo przypisuje do tego element listy
		telefon *start = adres_do_pierwszej_funkcji;
		string ita_marka;
		string jta_marka;
		bool czy_unikalna=true;
		for (int i = 0; i < ile_jest_na_liscie; i++)// rozkazuje kazdemu elementowi porownac sie z innymi
		{
			czy_unikalna = true;
			ita_marka = sprawdzenie_unikalnosci_marki->marka;
			for (int j = 0; j < ile_jest_na_liscie; j++)//ile_jest_na_liscie-1 zeby nie sprawdzac ostatniego z elementem na ktory wskaze jego wsk_nastepnika, bo bedziemy powowywac z nullem
			{
				if (j != i)//to by nie porownywac marki z samą sobą
				{
					jta_marka = wewnetrzne_porownanie->marka;		
					if (ita_marka == jta_marka)//porownoje i-tą marke z j-tą
					{
						czy_unikalna = false;
					}
					if (wewnetrzne_porownanie->wsk_nastepnika != NULL)
						wewnetrzne_porownanie = wewnetrzne_porownanie->wsk_nastepnika;
				}
			}
			if (sprawdzenie_unikalnosci_marki->wsk_nastepnika!=NULL)
			sprawdzenie_unikalnosci_marki = sprawdzenie_unikalnosci_marki->wsk_nastepnika;
			wewnetrzne_porownanie = start;
			if (czy_unikalna)
				ile_telefonow_ma_unikalna_marke++;
		}
	return ile_telefonow_ma_unikalna_marke;
}

//void dopisz_przedostatni(telefon *adres)
//{
//	string dopisany_marka;
//	int dopisana_temp;
//	telefon *kopia = adres;
//	telefon *start = adres;
//	int ile = 0;
//	while (kopia != NULL)
//	{
//		ile++;
//		kopia = kopia->wsk_nastepnika;
//	}
//	if (ile == 1)
//	{
//		telefon * dopisany = new telefon;
//
//		cout << " wpisz nowy marka do dodania" << endl;
//		cin >> dopisany_marka;
//		cout << " wpisz jego temperature topienia" << endl;
//		cin >> dopisana_temp;
//		//dopisany_marka = "potas";//do testow
//		//dopisana_temp = 64;//do testow
//		dopisany->marka = dopisany_marka;
//		dopisany->cena = dopisana_temp;
//		/////
//
//		telefon * falszywy_ostatni = new telefon;
//		falszywy_ostatni->marka = adres->marka;
//		falszywy_ostatni->cena = adres->cena;
//		falszywy_ostatni->wsk_nastepnika = NULL;
//
//		dopisany->wsk_nastepnika = falszywy_ostatni;
//		*adres = *dopisany;
//	}
//
//	else if (ile > 1)
//	{	//cout << ile;//do testow;
//
//		for (int i = 1; i < ile - 1; i++)
//		{
//			adres = adres->wsk_nastepnika;
//		}
//
//		//cout << adres->marka;//do testow;
//		telefon * dopisany = new telefon;
//		cout << " wpisz nowy marka do dodania" << endl;
//		cin >> dopisany_marka;
//		cout << " wpisz jego temperature topienia" << endl;
//		cin >> dopisana_temp;
//		//dopisany_marka = "potas";//do testow
//		//dopisana_temp = 64;//do testow
//		dopisany->marka = dopisany_marka;
//		dopisany->cena = dopisana_temp;
//		//dopisany->wsk_nastepnika = adres->wsk_nastepnika;//shallow copy
//		dopisany->wsk_nastepnika = new telefon(*adres->wsk_nastepnika);//deep copy
//		adres = start;
//		for (int i = 1; i < ile - 1; i++)
//		{
//			adres = adres->wsk_nastepnika;
//		}
//		adres->wsk_nastepnika = dopisany;
//
//	}
//	else
//		cout << "lista jest zbyt krotka, aby cos do niej dopisywac na przedostatnim miejscu ";
//	cout << "nastapilo dodanie markau na przedostatnim miejscu";
//}
void skasuj_liste(telefon *lista_do_skasowania)
{
	telefon *aktualny;
	telefon *poprzedni;
	telefon *tmp;
	telefon *glowa = lista_do_skasowania;
	aktualny = glowa;
	poprzedni = NULL;
	while (aktualny != NULL)
	{
		if (aktualny == glowa)
			// jesli usuniemy glowe, to nowa glowa bedzie o jeden element dalej
			glowa = glowa->wsk_nastepnika;
		else
			// a jesli usuwamy cos w srodku lub na koncu listy, to
			// tworzymy połaczenie z pominieciem kasowanego elementu
			poprzedni->wsk_nastepnika = aktualny->wsk_nastepnika;
		// w obu przypadkach zapamietujemy adres elementu do usuniecia
		tmp = aktualny;
		// przesuwamy sie o jeden element dalej
		aktualny = aktualny->wsk_nastepnika;
		// ...i zwalniamy pamiec zajeta przez usuwany element
		delete tmp;
	};
	lista_do_skasowania = NULL;
	cout << "Skasowano liste";
	drukuj_liste_it(lista_do_skasowania);// podpunkt 5
}
int main()
{
	//podpunkt 1
	telefon *nowalista = new telefon();
	/*cout << "Wpisz nazwe pliku. Dane w pliku musza byc w formacie: marka model cena, i kazdy nastepny element listy ma byc w nastepnej linijce. Kursor pliku musi byc na koncu ostatniej zapelnionej linijki. \n";
	string nazwapliku;
	cin >> nazwapliku;*/
string nazwapliku = "dane.txt";//do testow
	ifstream plik(nazwapliku);
	if (!plik.is_open())
	{
		cout << "plik nie zostal otwarty. Sprawdz czy dobrze podales jego nazwe. Pamietaj ze musisz podac nazwe wraz z rozszerzeniem.";
		return 0;
	}
	int plik_cena = NULL;
	string plik_marka;
	string plik_model;
	int ile_telefonow_w_pliku = 0;
	while (!plik.eof())
	{
		
		plik >> plik_marka >>plik_model>> plik_cena;
		cout << "marka to :" << plik_marka <<" Model to "<<plik_model<<" cena to: " << plik_cena <<endl;//to do testow
		nowalista = wczytaj_na_liste(nowalista, plik_marka, plik_model, plik_cena);
		ile_telefonow_w_pliku++;
	}
	plik.close();
	if (plik_cena != NULL)
	{
		cout << "w pliku byly " << ile_telefonow_w_pliku << " telefony";
		drukuj_liste_it(nowalista);//podpunkt 2
		string ciag_znakow = "Nok";
		int ile_telefonow = 0;
		cout << "na liscie jest " << pierwsza(nowalista, ile_telefonow,ciag_znakow,"Fizyka","Dwa_kubki_polaczane_sznurkiem",0,20) << " telefonow, z unikalna marka\n";
		cout << "znaleziono " << ile_telefonow << " dopasowan do wzoru,,"<< ciag_znakow<<"''\n";
		drukuj_liste_it(nowalista);
		skasuj_liste(nowalista);//podpunkt 4
	}
	else
	{
		cout << "Wczytany plik jest pusty;";
	}


	cout << "\nKoniec pracy programu\n";
	return 0;
}

