#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int lWierzcholkow;

    ifstream plik("graf.txt");
    plik >> lWierzcholkow;

    int graf[lWierzcholkow][lWierzcholkow];
    int poprzedniki[lWierzcholkow];
    int wyniki[lWierzcholkow];
    int szukany = 0;
    int nieskonczonosc = 111111;

    for (int i = 0; i < lWierzcholkow; ++i)
    {
        wyniki[i] = nieskonczonosc;
        poprzedniki[i] = nieskonczonosc;
        for(int j = 0; j < lWierzcholkow; ++j)
        {
            plik >> graf[i][j];
        }
    }
    plik.close();
    wyniki[szukany] = 0;

    cout<<"Graf:"<<endl;
    for(int k=0; k<lWierzcholkow; ++k)
    {
        for(int l=0; l<lWierzcholkow; ++l)
        {
            cout<<graf[k][l]<<" ";
        }
        cout<<endl;
    }

    for(int i = 0; i < lWierzcholkow - 1; ++i)
    {
        for(int u = 0; u < lWierzcholkow; ++u)
        {
            for(int v = 0; v < lWierzcholkow; ++v)
            {
                if(wyniki[v] > wyniki[u] + graf[u][v] && graf[u][v] != 0)
                {
                    wyniki[v] = wyniki[u] + graf[u][v];
                    poprzedniki[v] = u;
                }
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
