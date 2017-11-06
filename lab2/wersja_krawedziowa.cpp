#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int NIESKONCZONOSC = 111111;

struct krawedz
{
    int poczatek;
    int koniec;
    int waga;
};
std::vector<int> wybierzSciezke(int, int, int, int, std::vector<krawedz>&);
int findIndex(int, int, int, std::vector<krawedz>&);

int main()
{
    int maksPrzeplyw = 0;
    int lWierzcholkow;
    int lKrawedzi;
    int startowy;
    int koncowy;
    std::vector<std::vector<int>> sciezki;

    ifstream plik("krawedzie.txt");
    plik >> startowy;
    plik >> koncowy;
    plik >> lWierzcholkow;
    plik >> lKrawedzi;

    std::vector<krawedz> krawedzie;
    int nieskonczonosc = 111111;

    for(int j = 0; j < lKrawedzi; ++j)
    {
        krawedz temp;
        plik >> temp.poczatek >> temp.koniec >> temp.waga;
        krawedzie.push_back(temp);
    }

    plik.close();

    cout<<"Krawedzie:"<<endl;
    for(int i = 0; i < lKrawedzi; ++i)
    {
        cout<<krawedzie[i].poczatek<<" "<<krawedzie[i].koniec<<" "<<krawedzie[i].waga<<endl;
    }
    cout<<endl;

    auto sciezka = wybierzSciezke(startowy, koncowy, lWierzcholkow, lKrawedzi, krawedzie);
    auto fff = krawedzie;
    while(!sciezka.empty())
    {
        cout<<"sciezka"<<endl;
        for(int i = 0; i < sciezka.size(); ++i)
        {
            cout<<sciezka[i]<<" ";
        }
        cout<<endl;
        int min = NIESKONCZONOSC;
        for(int i = 0; i < sciezka.size() - 1; ++i)
        {
            int poczatek = sciezka[i+1];
            int koniec = sciezka[i];
            int index = findIndex(poczatek, koniec, lKrawedzi, krawedzie);
            cout<<"indeks: "<<index<<" "<<fff[index].waga<<endl;
            if(min > fff[index].waga)
            {
                min = fff[index].waga;
            }
        }
        cout<<"maksymalny przeplyw na sciezce: "<<min<<endl;
        for(int i = 0; i < sciezka.size() - 1; ++i)
        {
            int poczatek = sciezka[i+1];
            int koniec = sciezka[i];
            int index = findIndex(poczatek, koniec, lKrawedzi, krawedzie);
            fff[index].waga = fff[index].waga - min;
            index = findIndex(koniec, poczatek, lKrawedzi, krawedzie);
            if(index == -1)
            {
                fff.push_back({koniec, poczatek, -1 * min});
                lKrawedzi++;
            } else
            {
                fff[index].waga = fff[index].waga + min;
            }
        }
        cout<<endl<<endl;
        cout<<"Krawedzie:"<<endl;
        for(int i = 0; i < lKrawedzi; ++i)
        {
            cout<<fff[i].poczatek<<" "<<fff[i].koniec<<" "<<fff[i].waga<<endl;
        }
        cout<<endl;
        sciezki.push_back(sciezka);

        sciezka = wybierzSciezke(startowy, koncowy, lWierzcholkow, lKrawedzi, fff);

        maksPrzeplyw += min;
    }



    sciezki.push_back(sciezka);

    cout<<"Koniec"<<endl;
    for(auto& sciezkaa: sciezki)
    {
        for(int i = 0; i < sciezkaa.size(); ++i)
        {
            cout<<sciezkaa[sciezkaa.size() - i - 1]<<" ";
        }
        cout<<endl;
    }
    cout<<"Maksymalny przeplyw: "<<maksPrzeplyw<<endl;
}

std::vector<int> wybierzSciezke(int startowy,
                                int koncowy,
                                int lWierzcholkow,
                                int lKrawedzi,
                                std::vector<krawedz>& krawedzie)
{
    int poprzedniki[lWierzcholkow];
    int wyniki[lWierzcholkow];

    for (int i = 0; i < lWierzcholkow; ++i)
    {
        wyniki[i] = NIESKONCZONOSC;
        poprzedniki[i] = NIESKONCZONOSC;
    }
    wyniki[startowy] = 0;

    for(int j = 0; j < lWierzcholkow - 1; ++j)
    {
        for(int i = 0; i < lKrawedzi; ++i)
        {
            int poczatek = krawedzie[i].poczatek;
            int koniec = krawedzie[i].koniec;
            if(wyniki[koniec] > wyniki[poczatek] + krawedzie[i].waga && krawedzie[i].waga > 0)
            {
                wyniki[koniec] = wyniki[poczatek] + krawedzie[i].waga;
                poprzedniki[koniec] = poczatek;
            }
        }
    }

    int p = koncowy;
    std::vector<int> sciezka;

    sciezka.push_back(koncowy);

    if(NIESKONCZONOSC == poprzedniki[koncowy])
    {
        sciezka.clear();
        return sciezka;
    }
    while(poprzedniki[p] != startowy)
    {
        sciezka.push_back(poprzedniki[p]);
        p = poprzedniki[p];
    }
    sciezka.push_back(startowy);

    return sciezka;
}

int findIndex(int startowy,
              int koncowy,
              int lKrawedzi,
              std::vector<krawedz>& krawedzie)
{
    for(int i = 0; i < lKrawedzi; ++i)
    {
        if(krawedzie[i].poczatek == startowy && krawedzie[i].koniec == koncowy)
        {
            return i;
        }
    }
    return -1;
}