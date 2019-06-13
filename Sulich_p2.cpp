#include "pch.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <limits>
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
		cout << (*adres_do_drukowania).marka << " ";//zakomentowane do testow
		cout << (*adres_do_drukowania).model << " ";
		cout << (*adres_do_drukowania).cena << " ";//zakomentowane do testow
		//cout << "\n";
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
		else
			delete(dopisany);
		adres_do_pierwszej_funkcji = ostatni;
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
bool druga(telefon *adres_do_drugiej_funkcji,int ile_elementow_usunac,string jakas_marka, string jakis_model,int kolejny_numer)
{
	telefon *poczatek = adres_do_drugiej_funkcji;
	telefon *szukanie_najdrozszego = adres_do_drugiej_funkcji;
	telefon *najdrozszy = adres_do_drugiej_funkcji;
	telefon *najmniej_liter = adres_do_drugiej_funkcji;
	telefon *zamieniona_lista = adres_do_drugiej_funkcji;
	telefon *lista_podpunkt_pierwszy = adres_do_drugiej_funkcji;
	telefon *lista_podpunkt_drugi = adres_do_drugiej_funkcji;
	telefon *nastepny_po_najmniejliterowym = adres_do_drugiej_funkcji;
	telefon *tmp = adres_do_drugiej_funkcji;
	telefon *po_wpisaniu_mediany = poczatek;
	telefon *nastepny_po_najdrozszym = adres_do_drugiej_funkcji;
	bool czy_prawda = true;
	float mediana = 0;
	int ktory_najdrozszy = 0;
	int ktory_ma_najmniej_liter = 0;
	int ktora_iteracja = 0;
	while (szukanie_najdrozszego->wsk_nastepnika != NULL)
	{
		ktora_iteracja++;
		if (szukanie_najdrozszego->cena > najdrozszy->cena)
		{
			najdrozszy = szukanie_najdrozszego;
			ktory_najdrozszy = ktora_iteracja;
			nastepny_po_najdrozszym = szukanie_najdrozszego->wsk_nastepnika;
		}
		if (szukanie_najdrozszego->model.length() < najmniej_liter->model.length())
		{
				najmniej_liter = szukanie_najdrozszego;
				ktory_ma_najmniej_liter = ktora_iteracja;
		}
		szukanie_najdrozszego = szukanie_najdrozszego->wsk_nastepnika;
	}
	//krok numer 1
	for (int i = 1; i < ktory_najdrozszy-1; i++)//przewiniecie do elementu przed najdrozszym elementem
	{
		lista_podpunkt_pierwszy = lista_podpunkt_pierwszy->wsk_nastepnika;
	}
	
	lista_podpunkt_pierwszy->wsk_nastepnika = nastepny_po_najdrozszym;
	//dzieki powyzszej linijce,w tym momencie element poprzedzajacy najdrozszy telefon, wskazuje na następny za najdroższym
	lista_podpunkt_pierwszy = poczatek;//przewiniecie listy na poczatek;
	for (int i = 1; i < ktory_ma_najmniej_liter; i++)//teraz jestesmy w elemencie majacym najmniej liter
	{
		lista_podpunkt_pierwszy = lista_podpunkt_pierwszy->wsk_nastepnika;
	}
	nastepny_po_najmniejliterowym = lista_podpunkt_pierwszy->wsk_nastepnika;//teraz znalazlem i oznaczylem ten element ktory jest nastepny po najmniejliterowym 
	
	//krok 2
	lista_podpunkt_pierwszy = poczatek;//przewiniecie listy na poczatek;
	for (int i = 1; i < ktory_ma_najmniej_liter; i++)//teraz jestesmy w elemencie majacym najmniej liter
	{
		lista_podpunkt_pierwszy = lista_podpunkt_pierwszy->wsk_nastepnika;
	}
	lista_podpunkt_pierwszy->wsk_nastepnika = najdrozszy;//teraz ten z najkrotsza nazwa modelu wskazuje na najdrozszy
	
	//cout << "nastepny_po_najmniejliterowym";//do testow
	//drukuj_liste_it(nastepny_po_najmniejliterowym);//do testow
	//krok 3
	lista_podpunkt_pierwszy = poczatek;//przewiniecie listy na poczatek;
	for (int i = 1; i < ktory_ma_najmniej_liter+1; i++)//przewiniecie listy do elementu ktory jest po 
		//najmniejliterowym, czyli juz poprawnie umieszczonego najdrozszego;
	{
		lista_podpunkt_pierwszy = lista_podpunkt_pierwszy->wsk_nastepnika;
	}
	lista_podpunkt_pierwszy->wsk_nastepnika = nastepny_po_najmniejliterowym;//najdrozszy pokazuje teraz na element
	//ktory wczesniej stal na jego miejscu//
	lista_podpunkt_pierwszy = poczatek;//przewiniecie listy na poczatek;
	//cout << "lista_podpunkt_pierwszy";//do testow
	//drukuj_liste_it(lista_podpunkt_pierwszy);//do testow
	//cout << "\ndruk od najdrozszego, ma on numer :"<<ktory_najdrozszy<<"\n";//do testow
	//drukuj_liste_it(najdrozszy);//do testow
	//cout << "\ndruk od najmniejliter, ma on numer :" << ktory_ma_najmniej_liter << "\n";//do testow
	//drukuj_liste_it(najmniej_liter);//do testow
	*poczatek = *lista_podpunkt_pierwszy;//traz orginalna lista jest lista z zmieniona kolejnoscia
	/////////////////////////////////////////////////////PODPUNKT 2/////////////////////////////////////////////////////
	//cout << "ktora_iteracja"<<ktora_iteracja;
	if (ile_elementow_usunac > ktora_iteracja)//jezeli ten warunek jest spelniony, to trzeba usunac cala liste i dodac na koncu model z mediana
	{
		ile_elementow_usunac = ktora_iteracja + 1;//
		cout << "w funckji druga wpisano tyle parametrow, ze zostanie usunieta cala lista";
		/////////////////////////////////////////////////
		telefon*lista_po_usunieciu = poczatek;
		for (int i = 0; i < ile_elementow_usunac; i++)
		{
			if (lista_po_usunieciu != NULL)
				lista_po_usunieciu = lista_po_usunieciu->wsk_nastepnika;
		}
		/////////////////////////////////////////////////

		float *usuniete_ceny; // to oznacza, że nazwa usuniete_ceny jest wskaźnikiem do pierwszego elementu tablicy  
		usuniete_ceny = new float[ile_elementow_usunac]; // rezerwujemy pamięć dla potrzebnej ilości elementów tablicy typu float
		float *posortowane_ceny; // to oznacza, że nazwa usuniete_ceny jest wskaźnikiem do pierwszego elementu tablicy  
		posortowane_ceny = new float[ile_elementow_usunac]; // rezerwujemy pamięć dla potrzebnej ilości elementów tablicy typu float

		for (int ile_zostalo_do_usuniecia = ile_elementow_usunac; ile_zostalo_do_usuniecia > 0; ile_zostalo_do_usuniecia--)
		{
			for (int j = 0; j < ile_zostalo_do_usuniecia - 1; j++)//przesuwam sie do emenetu ktory cche usunac
			{
				if (lista_podpunkt_drugi->wsk_nastepnika != NULL)
					lista_podpunkt_drugi = lista_podpunkt_drugi->wsk_nastepnika;
			}
			tmp = lista_podpunkt_drugi;
			tmp->wsk_nastepnika = NULL;
			usuniete_ceny[ile_zostalo_do_usuniecia - 1] = tmp->cena;
			//cout << "usuwam element:";//do testow
			//drukuj_liste_it(tmp);//do testow
			tmp = NULL;
			delete tmp;

			lista_podpunkt_drugi = poczatek;
		}

		/////////////////////////////////////////////////
		telefon * nowy = new telefon;
		//cout << "Usuniete ceny wygladaja nastepujaco:\n";//do testow
		//for (int i = 0; i < ile_elementow_usunac; i++)//do testow
		//{//do testow
		//	cout << usuniete_ceny[i]<<"\n";//do testow
		//}//do testow
		float min = usuniete_ceny[0];
		float i_min = usuniete_ceny[0];;
		float tymczasowo_do_zamiany = usuniete_ceny[0];

		for (int i = 0; i < ile_elementow_usunac; i++)
		{
			min = usuniete_ceny[i];
			for (int j = i; j < ile_elementow_usunac; j++)// w tej petli ustala sie minimum nieposortowanej tablicy
			{
				if (usuniete_ceny[j] < min)
				{
					tymczasowo_do_zamiany = min;
					min = usuniete_ceny[j];
					usuniete_ceny[j] = tymczasowo_do_zamiany;
					i_min = j;
				}
			}
			posortowane_ceny[i] = min;

		}
		//cout << "posortowane ceny wygladaja nastepujaco:\n";//do testow
		//for (int i = 0; i < ile_elementow_usunac; i++)//do testow
		//{//do testow
		//	cout << posortowane_ceny[i] << "\n";//do testow
		//}//do testow
		if (ile_elementow_usunac % 2 == 1)
			mediana = posortowane_ceny[ile_elementow_usunac / 2];
		else
			mediana = (posortowane_ceny[ile_elementow_usunac / 2] + posortowane_ceny[ile_elementow_usunac / 2 - 1]) / 2;
		delete(posortowane_ceny);
		delete(usuniete_ceny);
		nowy->marka = jakas_marka;
		nowy->model = jakis_model;
		nowy->cena = mediana;
		nowy->wsk_nastepnika = NULL;
		while (po_wpisaniu_mediany->wsk_nastepnika != NULL)
		{
			po_wpisaniu_mediany = po_wpisaniu_mediany->wsk_nastepnika;
		}
		po_wpisaniu_mediany->wsk_nastepnika = nowy;
		*adres_do_drugiej_funkcji = *nowy;
		czy_prawda = false;//skoro usuniemy cala liste, i zostanie tylko jeden dopisany telefon z cena rowna medianie, to zamiana nie nastapi
	}//koniec przypadku gdzie usuwamy cala liste
	else//teraz przypadek gdzie nie usuwamy calej listy
	{
		/////////////////////////////////////////////////
		telefon*lista_po_usunieciu = poczatek;
		for (int i = 0; i < ile_elementow_usunac; i++)
		{
			if (lista_po_usunieciu!=NULL)
			lista_po_usunieciu = lista_po_usunieciu->wsk_nastepnika;
		}
		/////////////////////////////////////////////////

		float *usuniete_ceny; // to oznacza, że nazwa usuniete_ceny jest wskaźnikiem do pierwszego elementu tablicy  
		usuniete_ceny = new float[ile_elementow_usunac]; // rezerwujemy pamięć dla potrzebnej ilości elementów tablicy typu float
		float *posortowane_ceny; // to oznacza, że nazwa usuniete_ceny jest wskaźnikiem do pierwszego elementu tablicy  
		posortowane_ceny = new float[ile_elementow_usunac]; // rezerwujemy pamięć dla potrzebnej ilości elementów tablicy typu float

		for (int ile_zostalo_do_usuniecia = ile_elementow_usunac; ile_zostalo_do_usuniecia > 0; ile_zostalo_do_usuniecia--)
		{
			for (int j = 0; j < ile_zostalo_do_usuniecia - 1; j++)//przesuwam sie do emenetu ktory cche usunac
			{
				if (lista_podpunkt_drugi->wsk_nastepnika!=NULL)
				lista_podpunkt_drugi = lista_podpunkt_drugi->wsk_nastepnika;
			}
			tmp = lista_podpunkt_drugi;
			tmp->wsk_nastepnika = NULL;
			usuniete_ceny[ile_zostalo_do_usuniecia - 1] = tmp->cena;
			//cout << "usuwam element:";//do testow
			//drukuj_liste_it(tmp);//do testow
			tmp = NULL;
			delete tmp;

			lista_podpunkt_drugi = poczatek;
		}

		/////////////////////////////////////////////////
		*poczatek = *lista_po_usunieciu;//w tym momencie orginalna lista swój poczatek ma na elemencie, ktory jest emelemnetm nastepnym po ostatnim usunietym
		telefon * nowy = new telefon;
		//cout << "Usuniete ceny wygladaja nastepujaco:\n";//do testow
		//for (int i = 0; i < ile_elementow_usunac; i++)//do testow
		//{//do testow
		//	cout << usuniete_ceny[i]<<"\n";//do testow
		//}//do testow
		float min = usuniete_ceny[0];
		float i_min = usuniete_ceny[0];;
		float tymczasowo_do_zamiany = usuniete_ceny[0];

		for (int i = 0; i < ile_elementow_usunac; i++)
		{
			min = usuniete_ceny[i];
			for (int j = i; j < ile_elementow_usunac; j++)// w tej petli ustala sie minimum nieposortowanej tablicy
			{
				if (usuniete_ceny[j] < min)
				{
					tymczasowo_do_zamiany = min;
					min = usuniete_ceny[j];
					usuniete_ceny[j] = tymczasowo_do_zamiany;
					i_min = j;
				}
			}
			posortowane_ceny[i] = min;

		}
		//cout << "posortowane ceny wygladaja nastepujaco:\n";//do testow
		//for (int i = 0; i < ile_elementow_usunac; i++)//do testow
		//{//do testow
		//	cout << posortowane_ceny[i] << "\n";//do testow
		//}//do testow
		if (ile_elementow_usunac % 2 == 1)
			mediana = posortowane_ceny[ile_elementow_usunac / 2];
		else
			mediana = (posortowane_ceny[ile_elementow_usunac / 2] + posortowane_ceny[ile_elementow_usunac / 2 - 1]) / 2;
		delete(posortowane_ceny);
		delete(usuniete_ceny);
		nowy->marka = jakas_marka;
		nowy->model = jakis_model;
		nowy->cena = mediana;
		nowy->wsk_nastepnika = NULL;
		while (po_wpisaniu_mediany->wsk_nastepnika != NULL)
		{
			po_wpisaniu_mediany = po_wpisaniu_mediany->wsk_nastepnika;
		}
		po_wpisaniu_mediany->wsk_nastepnika = nowy;

		/////podpunkt 3
		telefon *zamiana = poczatek;
		int ile_telefonow_jest_w_trzecim_podpunkcie = 0;
		telefon*najtanszy = new telefon;
		najtanszy->cena = poczatek->cena;
		int ktory_telefon_jest_najtanszy = 0;
		int potencjalnie_najtanszy_telefon = 0;
		while (zamiana != NULL)
		{
			potencjalnie_najtanszy_telefon++;
			if (zamiana->cena < najtanszy->cena)
			{
				najtanszy->cena = zamiana->cena;
				najtanszy->marka = zamiana->marka;
				najtanszy->model = zamiana->model;
				najtanszy->wsk_nastepnika = zamiana->wsk_nastepnika;
				ktory_telefon_jest_najtanszy = potencjalnie_najtanszy_telefon;
			}
			zamiana = zamiana->wsk_nastepnika;
			ile_telefonow_jest_w_trzecim_podpunkcie++;

		}
		zamiana = poczatek;//wracam na poczatek listy powstalej po usunieciu elementow

		if (kolejny_numer > ile_telefonow_jest_w_trzecim_podpunkcie)
			czy_prawda = false;
		//cout << "ile_telefonow_jest_w_trzecim_podpunkcie:" << ile_telefonow_jest_w_trzecim_podpunkcie;//do testow
		else//robimy zamiane telefonow
		{

			//krok 1
			for (int i = 1; i < kolejny_numer; i++)
			{
				zamiana = zamiana->wsk_nastepnika;
			}
			telefon *kolejny_telefon = new telefon;
			kolejny_telefon->cena = zamiana->cena;
			kolejny_telefon->marka = zamiana->marka;
			kolejny_telefon->model = zamiana->model;
			kolejny_telefon->wsk_nastepnika = zamiana->wsk_nastepnika;
			zamiana = poczatek;//wracam na poczatek listy powstalej po usunieciu elementow

			

			if (kolejny_numer + 1 == ktory_telefon_jest_najtanszy)//szczegolny przypadek, gdy kolejny jest bezposrednio przed najtanszym
			{
				//cout << "wystapil szczegolny przypadek,gdy kolejny jest bezposrednio przed najtanszym\n";//do testow
				kolejny_telefon->wsk_nastepnika = najtanszy->wsk_nastepnika;//krok 1
				najtanszy->wsk_nastepnika = kolejny_telefon;//krok 2
				for (int i = 1; i < kolejny_numer - 1; i++)//przewijam do poprzednika kolejnego telefonu
				{
					zamiana = zamiana->wsk_nastepnika;
				}
				if (zamiana->cena == kolejny_telefon->cena)//taki przypadek nastapi dla 4,1 bo ususniete zostana wszystkie przed kolejnym
					*poczatek = *najtanszy;//krok 3 dla 4,1
				else
					zamiana->wsk_nastepnika = najtanszy;//krok 3 dla 1,4 zamiana tu to kruger, dla 4,1 to xiaomi
				zamiana = poczatek;
			}
			else//normalny przypadek, gdy kolejny nie jest bezposrednio przed najtanszym
			{
				if (kolejny_numer> ktory_telefon_jest_najtanszy)//gdy kolejny jest za najtanszym
				{
					for (int i = 1; i < ktory_telefon_jest_najtanszy - 1; i++)
					{
						zamiana = zamiana->wsk_nastepnika;
					}
					//cout << "zamiana->model" << zamiana->model;//do testow
					zamiana->wsk_nastepnika = kolejny_telefon;//wykonany pierwszy krok
					telefon *na_co_wskazuje_kolejny = new telefon;
					na_co_wskazuje_kolejny = kolejny_telefon->wsk_nastepnika;
					kolejny_telefon->wsk_nastepnika = najtanszy;//wykonano drugi krok
					najtanszy->wsk_nastepnika = na_co_wskazuje_kolejny;//wykonano trzeci krok

				}
				else//gdy kolejny nie jest za najtanszym
				{
					for (int i = 1; i < ktory_telefon_jest_najtanszy - 1; i++)
					{
						zamiana = zamiana->wsk_nastepnika;
					}
					//cout << "zamiana->model" << zamiana->model;//do testow
					zamiana->wsk_nastepnika = kolejny_telefon;//wykonany pierwszy krok
					/////////////////nastepny_po_kolejnym to telefon ktory jest nastepny w kolejce, zaraz po kolejnym telefonie
					telefon *nastepny_po_kolejnym = new telefon;
					if (kolejny_telefon->wsk_nastepnika != NULL)
					{
						nastepny_po_kolejnym->cena = kolejny_telefon->wsk_nastepnika->cena;
						nastepny_po_kolejnym->marka = kolejny_telefon->wsk_nastepnika->marka;
						nastepny_po_kolejnym->model = kolejny_telefon->wsk_nastepnika->model;
						nastepny_po_kolejnym->wsk_nastepnika = kolejny_telefon->wsk_nastepnika->wsk_nastepnika;
					}
					else
					{
						nastepny_po_kolejnym->cena = NULL;
						nastepny_po_kolejnym->marka = "";
						nastepny_po_kolejnym->model = "";
						nastepny_po_kolejnym->wsk_nastepnika = NULL;
					}
					/////////////////
					zamiana = poczatek;//wracam na poczatek listy powstalej po usunieciu elementow
					for (int i = 1; i < kolejny_numer - 1; i++)
					{
						zamiana = zamiana->wsk_nastepnika;
					}
					zamiana->wsk_nastepnika = najtanszy;//wykonano drugi krok;
					zamiana = poczatek;//wracam na poczatek listy powstalej po usunieciu elementow

					kolejny_telefon->wsk_nastepnika = najtanszy->wsk_nastepnika;//wykonano krok 3
					najtanszy->wsk_nastepnika = nastepny_po_kolejnym;//wykonano krok 4
					//cout << "zamiana->model" << zamiana->model;//do testow
				}

			}
		}
	}
	return czy_prawda;
}

void skasuj_liste(telefon *&lista_do_skasowania)
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
	float plik_cena = NULL;
	string plik_marka;
	string plik_model;
	int ile_telefonow_w_pliku = 0;
	while (!plik.eof())
	{
		
		plik >> plik_marka >>plik_model>> plik_cena;
		//cout << "marka to :" << plik_marka <<" Model to "<<plik_model<<" cena to: " << plik_cena <<endl;//to do testow
		nowalista = wczytaj_na_liste(nowalista, plik_marka, plik_model, plik_cena);//podpunkt 1
		ile_telefonow_w_pliku++;
	}
	plik.close();
	if (plik_cena != NULL)
	{
		int ile_usunac = 3;
		int kolejny_numer = 1;
		//cout << "w pliku byly " << ile_telefonow_w_pliku << " telefony";//do testow
		drukuj_liste_it(nowalista);//podpunkt 2
		string ciag_znakow = "Nok";
		int ile_telefonow = 0;
		cout << "na liscie jest " << pierwsza(nowalista, ile_telefonow,ciag_znakow,"Fizyka","Dwa_kubki_polaczane_sznurkiem",0,20) << " telefonow, z unikalna marka\n";//podpunkt 3
		cout << "znaleziono " << ile_telefonow << " dopasowan do wzoru,,"<< ciag_znakow<<"''\n";
		cout << "lista po zrobieniu pierwszej funkcji wyglada nastepujaco:";
		drukuj_liste_it(nowalista);
		
		if (druga(nowalista, ile_usunac, "SuperDzynDzynPolska", "stacjonarny", kolejny_numer))//podpunkt 4
		{
			cout << "w trzecim podpunkcie drugiej funkcji nastapila zamiana \n";
		}
		else
		{
			cout << "w trzecim podpunkcie drugiej funkcji nie bylo zamiany\n";		
		}
		cout << "lista po zrobieniu drugiej funkcji wyglada nastepujaco:";
		cout << "\n\n ile_usunac =" << ile_usunac << ",kolejny_numer=" << kolejny_numer << "\n";//do testow

		drukuj_liste_it(nowalista);
		skasuj_liste(nowalista);//podpunkt 5
		drukuj_liste_it(nowalista);	// podpunkt 6


	}
	else
	{
		cout << "Wczytany plik jest pusty;";
	}
	cout << "\nKoniec pracy programu\n";
	return 0;
}

