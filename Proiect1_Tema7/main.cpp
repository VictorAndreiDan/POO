#include <iostream>
#include <vector>
#include <fstream>

//spraincarca <<,>> pentru ecran si fisier
//citirea completa memorarea si afisarea a n obiecte
//simulare de multimi cu duplicate
//class multime:
//               -vector in multime (sterg duplicate din vect)
//               -supraincarcare <<,>>
//               -reuniune a doua multimi (supraincarcare +)
//               -intersectie a doua multimi (supraincarcare *)
//               -diferenta a doua multimi (supraincarcare -)
//clasa pereche de int
//clasa multime de perechi de nr intregi(reprezentata ca vector de perechi) prietena a pereche
//                -supraincarcare si la perechi si multime de perechi
//
//functie produs cartezian de doua multimi si il stocheaza in multime de perechi

using namespace std;

class   multime
{
    friend class multime_perechi;
    vector  <int> continut;
public:
    //supraincarcare operatori
    friend  istream &operator>>(istream  &input, multime &M)
    {
        int i, x = 0, err = 0, aux;
        cout<<"Cate elemente are multimea?: ";input>>i;cout<<endl;
        cout<<"Introduce-ti elementele multimii!\n";
        while(++x <= i)
        {
            input>>aux;
            M.continut.push_back(aux);
            for(int p = 0; p <= M.continut.size(); p++)
            {
                for(int l = 0; l <= M.continut.size(); l++)
                {
                    if((M.continut[p] == M.continut[l]) && (l != p))
                    {
                        cout<<"Ati introdus un numar care deja apartine multimii, reintroduce-ti!\n";
                        x--;
                        M.continut.pop_back();
                        err = 1;
                        break;
                    }
                }
                if(err == 1)
                {
                    err = 0;
                    break;
                }
            }

        }
        return input;
    }

    friend  ostream &operator<<(ostream &output, const multime &M)
    {

         for(int b = 0; b < M.continut.size(); b++)
         {
             output<<M.continut[b]<<" ";
         }
         output<<endl;
    }
    //transformare vector in multime
    void    transform_vector(vector <int> v)
    {
        for(int g = 0; g < v.size(); g++)
        {
            this->continut.push_back(v[g]);
            for(int x = 0; x < this->continut.size() - 1; x++)
            {
                if(this->continut[x] == v[g])
                {
                    this->continut.pop_back();
                    break;
                }
            }
        }
    }

    //reuniune +
    multime operator+(const multime& second)
    {
        multime reuniune;
        for(int i = 0; i < this->continut.size(); i++)
            reuniune.continut.push_back(this->continut[i]);
        for(int i = 0; i < second.continut.size(); i++)
        {
            reuniune.continut.push_back(second.continut[i]);
            for(int j = 0; j < reuniune.continut.size()-1; j++)
            {
                if(reuniune.continut[j] == second.continut[i])
                {
                    reuniune.continut.pop_back();
                    break;
                }
            }
        }
        return reuniune;
    }

    //intersectie *
    multime operator*(const multime& second)
    {
        multime intersectie;
        vector <int> v;
        for(int i = 0; i < this->continut.size(); i++)
        {
            for(int j = 0; j < second.continut.size(); j++)
            {
                if(this->continut[i] == second.continut[j])
                    v.push_back(this->continut[i]);
            }
        }
        intersectie.transform_vector(v);
        return intersectie;
    }

    //diferenta -
    multime operator-(const multime& second)
    {
        multime diferenta;
        vector <int> v;
        for(int i = 0; i < this->continut.size(); i++)
        {
            v.push_back(this->continut[i]);
            for(int j = 0; j < second.continut.size(); j++)
            {
                if(this->continut[i] == second.continut[j])
                    v.pop_back();
            }
        }
        diferenta.transform_vector(v);
        return diferenta;
    }


};


class   pereche
{
    friend class multime_perechi;
public:
    int x, y;
    friend  ostream &operator<<(ostream &output, const pereche &p)
    {
         output<<p.x<<" "<<p.y;
    }
    friend  istream &operator>>(istream &input, pereche &p)
    {
         input>>p.x>>p.y;
    }
};

class   multime_perechi
{
    vector <pereche> continut;
public:
    friend  ostream &operator<<(ostream &output, const multime_perechi &Mp)
    {
         for(int i = 0; i < Mp.continut.size(); i++)
         {
            output<<Mp.continut[i].x<<" "<<Mp.continut[i].y<<endl;
         }
    }
    friend  istream &operator>>(istream &input, multime_perechi &Mp)
    {
        int x;
        pereche p;
        cout<<"Cate perechi doriti sa introduce-ti?";input>>x;
        cout<<"Introduce-ti perechile!\n";
        for(int i = 0; i < x; i++)
        {
            input>>p.x>>p.y;
            Mp.continut.push_back(p);
        }
    }
    multime_perechi produs_cartezian(multime M1, multime M2)
    {
        multime_perechi Mp;
        pereche p;
        for(int i = 0; i < M1.continut.size(); i++)
        {
            for(int j = 0; j < M2.continut.size(); j++)
            {
                p.x = M1.continut[i];
                p.y = M2.continut[j];
                Mp.continut.push_back(p);
            }
        }
        return Mp;
    }
};

int     main()
{
    multime_perechi Mp;
    multime M1, M2;
    cin>>M1>>M2;
    Mp = Mp.produs_cartezian(M1, M2);
    cout<<"Produsul cartezian este: \n";
    cout<<Mp;

    return 0;
}
