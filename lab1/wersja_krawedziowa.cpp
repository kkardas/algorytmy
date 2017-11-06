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

    for(int j = 0; j < lWierzcholkow - 1; ++j)
    {
        for(int i = 0; i < lKrawedzi; ++i)
        {
            int poczatek = krawedzie[i].poczatek;
            int koniec = krawedzie[i].koniec;
            if(wyniki[koniec] > wyniki[poczatek] + krawedzie[i].waga)
            {
                wyniki[koniec] = wyniki[poczatek] + krawedzie[i].waga;
                poprzedniki[koniec] = poczatek;
            }
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