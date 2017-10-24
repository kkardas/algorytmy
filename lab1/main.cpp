#include <iostream>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int lWierzcholkow;
    int graf[lWierzcholkow][lWierzcholkow];
    int poprzedniki[lWierzcholkow];
    int wyniki[lWierzcholkow];
    int szukany = 0;
    int nieskonczonosc = 111111;

    ifstream plik("graf.txt");
    plik >> lWierzcholkow;
    for (int i = 0; i < lWierzcholkow; ++i)
    {
        for(int j = 0; j < lWierzcholkow; ++j)
        {
            plik >> graf[i][j];
        }
    }
    plik.close();
    wyniki[szukany] = 0;

    for(int i = 0; i < lWierzcholkow - 1; ++i)
    {
        cout<<"1"<<endl;
        for(int u = 0; u < lWierzcholkow; ++u)
        {
            cout<<"2"<<endl;
            for(int v = 0; v < lWierzcholkow; ++v)
            {
                cout<<"3"<<endl;
                if(wyniki[v] > wyniki[u] + graf[u][v])
                {
                    wyniki[v] = wyniki[u] + graf[u][v];
                    poprzedniki[v] = u;
                    cout<<"4"<<endl;
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
