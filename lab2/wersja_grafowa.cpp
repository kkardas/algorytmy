#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int NIESKONCZONOSC = 111111;
std::vector<int> wybierzSciezke(int startowy, int koncowy, int lWierzcholkow, std::vector<std::vector<int>>& graf);

int main() {
    int maksPrzeplyw = 0;
    int lWierzcholkow;
    int startowy;
    int koncowy;

    ifstream plik("graf.txt");
    plik >> startowy;
    plik >> koncowy;
    plik >> lWierzcholkow;

    std::vector<std::vector<int>> graf;
    int szukany = 0;

    cout<<"startowy: "<<startowy<<endl;
    cout<<"koncowy: "<<koncowy<<endl;
    cout<<"lWierzcholkow: "<<lWierzcholkow<<endl;

    for (int i = 0; i < lWierzcholkow; ++i)
    {
        std::vector<int> tempV;
        for(int j = 0; j < lWierzcholkow; ++j)
        {
            int temp;
            plik>>temp;
            tempV.push_back(temp);
        }
        graf.push_back(tempV);
    }
    plik.close();

    cout<<"Graf:"<<endl;
    for(int k=0; k<lWierzcholkow; ++k)
    {
        for(int l=0; l<lWierzcholkow; ++l)
        {
            cout<<graf[k][l]<<" ";
        }
        cout<<endl;
    }

    std::vector<std::vector<int>> sciezki;

    auto sciezka = wybierzSciezke(startowy, koncowy, lWierzcholkow, graf);

    auto fff = graf;
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
            if(min > fff[sciezka[i+1]][sciezka[i]])
            {
                min = fff[sciezka[i+1]][sciezka[i]];
            }
        }
        cout<<"maksymalny przeplyw na sciezce: "<<min<<endl;
        for(int i = 0; i < sciezka.size() - 1; ++i)
        {
            fff[sciezka[i+1]][sciezka[i]] = fff[sciezka[i+1]][sciezka[i]] - min;
            fff[sciezka[i]][sciezka[i+1]] = fff[sciezka[i]][sciezka[i+1]] + min;
        }
        cout<<endl<<endl;
        for(int i = 0;i<lWierzcholkow;++i)
        {
            for(int j = 0; j<lWierzcholkow;++j)
            {
                cout<<fff[i][j]<<" ";
            }
            cout<<endl;
        }
        sciezki.push_back(sciezka);

        sciezka = wybierzSciezke(startowy, koncowy, lWierzcholkow, fff);

        maksPrzeplyw += min;
    }
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

std::vector<int> wybierzSciezke(int startowy, int koncowy, int lWierzcholkow, std::vector<std::vector<int>>& graf)
{
    int poprzedniki[lWierzcholkow];
    int wyniki[lWierzcholkow];

    for (int i = 0; i < lWierzcholkow; ++i)
    {
        wyniki[i] = NIESKONCZONOSC;
        poprzedniki[i] = NIESKONCZONOSC;
    }
    wyniki[startowy] = 0;

    for(int i = 0; i < lWierzcholkow - 1; ++i)
    {
        for(int u = 0; u < lWierzcholkow; ++u)
        {
            for(int v = 0; v < lWierzcholkow; ++v)
            {
                if(wyniki[v] > wyniki[u] + graf[u][v] && graf[u][v] > 0)
                {
                    wyniki[v] = wyniki[u] + graf[u][v];
                    poprzedniki[v] = u;
                }
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
