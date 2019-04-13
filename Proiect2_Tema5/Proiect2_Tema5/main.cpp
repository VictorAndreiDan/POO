#include <iostream>
#include <stdlib.h>

using namespace std;

//constructor: initializare, parametrizati, de copiere              V
//destructor                                                        V
//supraincarcare <<, >>, =                                          v
//mostenire, functii virtuale                                       V
//citirea a n obiecte, memorare, afisare                            V
//operatorii sunt membrii nu friend(fara << si >>)                  V
//
//clasa elementMultime(int x)
//clasa pereche(int first, int second) : publice elementMultime
//clasa multime cu elementMultime ca elemente
//Multime_pereche(int n, Pereche * p) : Multime
//Stiva_pereche : Multime_pereche
//Coada_pereche : Multime_pereche

class   elementMultime
{
public:
    int     val;
    elementMultime(){ val = 0; }
    elementMultime(int k){ val = k; }
};

class   multime
{
private:
    elementMultime  *continut;
    int             size;
public:
    multime(){ continut = NULL; size = 0; }
    multime(int sz){ continut = new elementMultime[sz]; size = sz; }
    //functii
    virtual void    get(){cout<<"in multime\n";cout<<"Marimea este: "<<this->size<<"\n";}
    //output
    friend ostream  &operator<<( ostream &output, const multime &M )
    {
        for(int i = 0; i < M.size; i++)
            output<<M.continut[i].val<<" ";
        output<<endl;
        return output;
    }
    friend istream  &operator>>( istream  &input, multime &M )
    {
        cout<<"Introduce-ti "<<M.size<<" elemente\n";
        int actual_size = 0;
        while(actual_size < M.size)
        {
            input>>M.continut[actual_size].val;
            actual_size++;
            for(int p = 0; p < actual_size - 1; p++)
            {
                if(M.continut[p].val == M.continut[actual_size - 1].val)
                {
                    cout<<"Element deja introdus, reintroduce-ti!\n";
                    actual_size--;
                }
            }

        }
        return input;
    }
    ~multime(){ delete[] continut; }
};

class   pereche:        public elementMultime
{
    friend class multime_pereche;
    friend class stiva_pereche;
    friend class coada_pereche;
private:
    int     second;
public:
    //constructori
    pereche(){second = 0;}
    pereche(int x, int y){val = x; second = y;}
    //input & output
    friend ostream &operator<<( ostream &output, const pereche &P )
    {
        output<<P.val<<" "<<P.second;
        output<<endl;
        return output;
    }

    friend istream &operator>>( istream  &input, pereche &P )
    {
        int     x, y;

        input>>x>>y;
        P = pereche(x, y);
        return input;
    }
};

class   multime_pereche:  public multime
{
    friend void simulare_coada_add();
protected:
    int     n;
    pereche *p;
public:
    multime_pereche(){n = 0; p = NULL;}
    multime_pereche(int x){n = x;p = new pereche[x];}
    void get(){cout<<"in multime_pereche\n";cout<<this->p[0].val<<" "<<this->p[0].second;}
    ~multime_pereche(){delete[] p; n = 0;}
};

class   stiva_pereche:    public multime_pereche
{
public:
    int     current_size;
    stiva_pereche(){n = 100; p = new pereche[100]; current_size = 0;}//make standard size}
    //functii
    void    push(pereche p);
    void    pop();
    void    print();
    pereche getElement(int i){return this->p[i];}
    ~stiva_pereche(){delete[] p; current_size = 0; n = 0;}
};

class   coada_pereche:    public multime_pereche
{
public:
    int     current_size;
    coada_pereche(){n = 100; p = new pereche[100]; current_size = 0;}//make standard size}
    //functii
    void    push(pereche p);
    void    pop();
    void    print();
    ~coada_pereche(){delete[] p; current_size = 0; n = 0;}
};

void    stiva_pereche::push(pereche p)
{
    this->p[this->current_size].val = p.val;
    this->p[this->current_size].second = p.second;
    this->current_size++;
}

void    stiva_pereche::pop()
{
    if(this->current_size > 0)
    {
        this->current_size--;
        //nu mai adaug instructiuni deoarece data viitoare cand
        //se va adauga/citii totul se va oprii la current_size in mod corect
        //push scrie in locul current_size
        //afisarea se face pana la current size ce e mereu + 1
    }
    else{cout<<"Stiva este goala!\n";}
}

void    stiva_pereche::print()
{
    if(this->current_size > 0)
    {
        for(int i = current_size - 1; i >= 0; i--)
        {
            cout<<"("<<this->p[i].val<<", "<<this->p[i].second<<")"<<endl;
        }
    }
    else{cout<<"Stiva este goala!\n";}
}

void    coada_pereche::push(pereche p)
{
    this->p[this->current_size].val = p.val;
    this->p[this->current_size].second = p.second;
    this->current_size++;
}

void    coada_pereche::pop()
{
    if(this->current_size > 0)
    {
        for(int i = 0; i < this->current_size - 1; i++)
        {
            this->p[i].val = this->p[i + 1].val;
            this->p[i].second = this->p[i + 1].second;
        }
        this->current_size--;
    }
    else{cout<<"Coada este goala!\n";}
}

void    coada_pereche::print()
{
    if(this->current_size > 0)
    {
        for(int i = 0; i < current_size; i++)
        {
            cout<<"("<<this->p[i].val<<", "<<this->p[i].second<<")"<<" ";
        }
        cout<<endl;
    }
    else{cout<<"Coada este goala!\n";}
}

void simulare_coada_add(stiva_pereche *s, stiva_pereche *aux, pereche p)
{
    //mut din s in aux
    for(int i = 0; i < s->current_size; i++)
    {
        aux->push(s->getElement(i));
    }
    //eliberez s
    for(int i = 0; i < aux->current_size; i++)
    {
        s->pop();
    }
    //adaug p pe primul loc
    s->push(p);
    //adaug restul elementelor ce au fost mutate
    for(int i = 0; i < aux->current_size; i++)
    {
        s->push(aux->getElement(i));
    }
    //aux ramane libera pentru urmatoarea adaugare
    for(int i = 0; i < s->current_size - 1; i++)
    {
        aux->pop();
    }
}

int     main(void)
{
    stiva_pereche   s1, s2;
    pereche         p1(11, 11), p2(22, 22), p3(33, 33);
    cout<<"Avem doua stive, una goala si una de forma: \n";
    s1.push(p1);
    s1.push(p2);
    s1.print();
    cout<<endl<<"Adaug perechea(33, 33) folosind functia de simulare coada: \n";
    simulare_coada_add(&s1, &s2, p3);
    s1.print();
    cout<<endl<<"Sterg: \n";
    s1.pop();
    s1.print();

    stiva_pereche s;
    cout<<endl<<"Avem stiva s in care o sa adaugam (11, 11), (22, 22), (33, 33)\n";
    s.print();
    s.push(p1);
    s.push(p2);
    s.push(p3);
    cout<<endl<<"Dupa adaugare:\n";
    s.print();
    cout<<endl<<"Sterg un element:\n";
    s.pop();
    s.print();

    coada_pereche c;
    cout<<endl<<"Avem coada c in care o sa adaugam (11, 11), (22, 22), (33, 33)\n";
    c.print();
    c.push(p1);
    c.push(p2);
    c.push(p3);
    cout<<endl<<"Dupa adaugare:\n";
    c.print();
    cout<<endl<<"Sterg un element:\n";
    c.pop();
    c.print();

    return 0;
}
