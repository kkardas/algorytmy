#include <iostream>
#include <fstream>

using namespace std;

struct krawedz
{
    int poczatek;
    int koniec;
    int waga;
};

int main()
{
    int lWierzcholkow;
    int lKrawedzi;

    ifstream plik("krawedzie.txt");
    plik >> lWierzcholkow;
    plik >> lKrawedzi;

    krawedz krawedzie[lKrawedzi];
    int poprzedniki[lWierzcholkow];
    int wyniki[lWierzcholkow];
    int szukany = 0;
    int nieskonczonosc = 111111;

    for (int i = 0; i < lWierzcholkow; ++i)
    {
        wyniki[i] = nieskonczonosc;
        poprzedniki[i] = nieskonczonosc;
    }
    for(int j = 0; j < lKrawedzi; ++j)
    {
        plik >> krawedzie[j].poczatek >> krawedzie[j].koniec >> krawedzie[j].waga;
    }

    plik.close();
    wyniki[szukany] = 0;

    cout<<"Krawedzie:"<<endl;
    for(int i = 0; i < lKrawedzi; ++i)
    {
        cout<<krawedzie[i].poczatek<<" "<<krawedzie[i].koniec<<" "<<krawedzie[i].waga<<endl;
    }
    cout<<endl;

    for(int i = 0; i < lKrawedzi - 1; ++i)
    {
        if(wyniki[krawedzie[i].koniec] > krawedzie[i].poczatek + krawedzie[i].waga)
        {
            wyniki[krawedzie[i].koniec] = wyniki[krawedzie[i].poczatek] + krawedzie[i].waga;
            poprzedniki[krawedzie[i].koniec] = krawedzie[i].poczatek;
        }
    }

    cout << "poprzedniki" << endl;
    for (int k = 0; k < lWierzcholkow; ++k)
    {
        cout << poprzedniki[k] << " ";
    }
    cout << endl << "wyniki" << endl;
    for (int k = 0; k < lWierzcholkow; ++k)
    {
        cout << wyniki[k] << " ";
    }
    cout << endl;
}