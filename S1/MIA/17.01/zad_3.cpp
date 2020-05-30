#include <iostream>
#include <string>
#include <vector>
//#include <conio.h>

using namespace std;

//Stałe i zmienne globalne zawsze na górę
const int N=50;
int numer_id_biezacy = 0;
int suma_probek = 0; //Chcemy wiedzieć ile próbek mamy aktualnie w tablicy, żeby móc na jej koniec wstawić naszą nową próbkę

struct T_dane_probki{ //Nazwa struktury trochę chujowa, bo to po prostu powinna być Probka a nie jakieś T_dane
    string nazwas;
    vector<char> nazwa;
    unsigned int numer_id;
    float stezenie;
    float objtosc;
    string imie_nazwiskos;
    vector<char> imie_nazwisko; //W poleceniu masz tablice nie wiem czy możesz korzystać z vectorów i stringów
    unsigned int pobranie_dzien;
    unsigned int pobranie_miesiac;
    unsigned int pobranie_rok;
    unsigned int badanie_dzien;
    unsigned int badanie_miesiac;
    unsigned int badanie_rok;
    int rodzaj;
};

T_dane_probki dane[N];

void DODANIE(/*hT_dane_probki& dane Na chuj to?*/){
    cout<<"Podaj nazwe probki (max 256 znakow) "<<endl;
    T_dane_probki dodawana_probka; //Probka którą będziemy dodawać
    cin>>dodawana_probka.nazwas;
    int t = dodawana_probka.nazwas.size();
    if(t>257){ //Próbka o nazwie o długości 257 też się powinna wypierdolić
        cout<<"Podales za dluga nazwe probki "<<endl;
        return;
    }
    else{
        dodawana_probka.nazwa.resize(t);
        for(int i=0; i<t; i++){
                dodawana_probka.nazwa.push_back(dodawana_probka.nazwas[i]);
        }
    }
    cout<<"Podaj objetosc probki "<<endl;
    cin>>dodawana_probka.objtosc;
    cout<<"Podaj stezenie probki (max 100) "<<endl;
    cin>>dodawana_probka.stezenie;
    if(dodawana_probka.stezenie>100){
        cout<<"Stezenie nie moze byc wieksze niz 100 "<<endl;
        return;
    }
    else {} // Po co ten else?

    cout<<"Podaj imie i nazwisko wlascicela (max 100 znakow) "<<endl;
    cin>>dodawana_probka.imie_nazwiskos;
    int s = dodawana_probka.imie_nazwiskos.size();
    if(s>100){
        cout<<"Podales za dlugie imie i nazwisko "<<endl;
        return;
    }
    else{
        dodawana_probka.imie_nazwisko.resize(s);
        for(int i=0; i<s; i++)
                dodawana_probka.imie_nazwisko.push_back(dodawana_probka.imie_nazwiskos[s]);
    }
    cout<<"Podaj dzien, miesiac i rok pobrania probki "<<endl;
    cin>>dodawana_probka.pobranie_dzien;
    cin>>dodawana_probka.pobranie_miesiac;
    cin>>dodawana_probka.pobranie_rok;
    cout<<"Podaj dzien, miesiac i rok badania probki "<<endl;
    cin>>dodawana_probka.badanie_dzien;
    cin>>dodawana_probka.badanie_miesiac;
    cin>>dodawana_probka.badanie_rok;
    enum rodzaje{
    staly=1,lotny,ciekly};
    cout<<"Podaj rodzaj preparatu: 1.staly \n2.lotny \n3.ciekly"<<endl;
    cin>>dodawana_probka.rodzaj;
    /*Dopisuję numer id dla każdej próbki, każda próbka będzie miała swój unikalny numer.
    Zauważ, że gdybyśmy korzystali z numeracji, nr_id próbki = indeks w tablicy dane[] próbki to wtedy
    po usunięciu próbki_2 próbka_3 by miała numer 2, a tego numeru miało już nie być bo go usunęliśmy.
    */
    dodawana_probka.numer_id = numer_id_biezacy;
    //Zwiększam numer który będzie przypisany dla kolejnej próbki, w ten sposób każda próbka będzie miała inny ID
    numer_id_biezacy++;
    dane[suma_probek] = dodawana_probka; //dodajemy próbkę
    suma_probek++; //zwiększamy sumę próbek w bazie po dodaniu
}
void USUWANIE(/*T_dane_probki& dane <- To jest nie potrzebne*/){
    cout<<"Ktora probke chcesz usunac" <<endl;
    int usun;
    cin>>usun;
    for(int i=0; i<N; i++){
        if(dane[i].numer_id == usun){ //znaleźliśmy próbkę do usunięcia
            for(int j=usun; j<N-1; j++) dane[i] = dane[i+1]; //Nadpisujemy usuwany element. Przesuwamy tablice na prawo od usuwanego o 1 w lewo.
            break; //znaleźliśmy usuwany, usunęliśmy, czas wypierdalać z pętli
        }
    }
    suma_probek--; //zmniejszamy ilość próbek w bazie
}
void MENU(){
    cout<<"Wybierz opcje z ponizszych"<<endl;
    cout<<"1.Dodanie probki"<<endl;
    cout<<"2.Usunuiecie probki"<<endl;
    cout<<"3.Zmiana danych probki"<<endl;
    cout<<"4.Wyszukanie probki po nazwie"<<endl;
    cout<<"5.Zapis danych do pliku"<<endl;
    cout<<"6.Odczyt danych z pliku"<<endl;
}


void DEBUG_wypisz(){ //funkcja do debugu, wypisuje numery próbek
    for(int i=0; i<N; i++) cout<<dane[i].numer_id<<" ";
    cout<<endl;
}

/* Komentarz do Twojego problemu:

Nie wiem czemu przekazujesz referencje do pewnego obiektu typu T_dane_probki w obu funkcjach.
Domyślam się, że robisz to bo chciałeś aby twój delete działał. W cpp nie możesz tak o sobie usunać delete elementu z tablicy.
Nie możesz dopóki nie operujesz na wskaźnikach a ty tego nie robisz. Domyślam się, że zaczynasz swoją przygodę z programowaniem więc
póki co zastosowałbym na twoim miejscu bardziej elementarne rozwiązanie (intuicyjne).

Mając tablicę dane[N], po prostu będziemy nadpisywać element usuwany.
Bardziej po ludzku załóżmy że dane[]={probka_1,probka_2,probka_3,probka_4,probka_5} i załóżmy że chcesz usunąć probka_2 po prostu jakby przesuniemy 
elementy tablicy na prawo od probka_2 na lewo o jeden indeks w ten sposób nasza tablica będzie wyglądała tak:
dane[] = {probka_1,probka_3,probka_4,probka_5}. Jest to nasz zamierzony efekt.
*/
int main(){
    int o=0;
    int wybor;
    cout<<"**********************  \nWitaj w laboraturium kryminalistycznym \n**********************"<<endl;
    MENU();
    enum opcje{Dodanie=1, Usuniecie=2, Zmiana, Wyszukanie, Zapis, Odczyt}; //Deklaracje stałych takich jak enum powinny raczej gdzieś na górze być w Twoim zadaniu
    while(true){ //program teraz działa w nieskończoność, możesz wypisać wpisać ile chcesz próbek
        cin>>wybor;
        switch(wybor){
            case Dodanie:
                 DODANIE();
                 break;
            case Usuniecie:
                USUWANIE();
                break;
        }
        DEBUG_wypisz(); //wypisuję żeby sprawdzić czy wpisaywanie i wypisywanie z bazy dobrze działa
    }
    return 0;
}