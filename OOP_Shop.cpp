#include <iostream>
#include <string.h>
#include<windows.h>
#include<vector>

using namespace std;

class Produs{
private:

    char* nume;
    double pret;
    int garantie;
    char sector;
    const int IdProdus;
    static int contorId;

    int nrReviewuri;
    int* reviewuri;

public:
    Produs();
    Produs(char* nume, double pret, int garantie, char sector, int nrReviewuri, int* reviewuri);
    Produs(const Produs& p);
    Produs& operator = (const Produs& p);

    static int getcontorId(){return Produs::contorId;}
    int getIdProdus() {return this -> IdProdus;}

    void setNume(char* nume);
    void setPret (double pret);
    void setGarantie (int garantie);
    void setSector (char sector);
    int getPret();
    int getGarantie();
    int getSector();
    const char* getNume();

    friend istream& operator>>(istream& in, Produs& ang);
    friend ostream& operator<<(ostream& out,const Produs& ang);

    const Produs& operator++();//pre-incremetare pret
    const Produs operator++(int);//post-incrementare garantie

    float operator[](int index);

    void afisare();
    int ReviewuriPozitive();
    void stergereReview();
    void adaugareReview(int x);

    ~Produs();

    bool operator==(const Produs& p) {


        if (this->sector == p.sector )
            return true;
        return false;
    }
    Produs operator+=(int x) {

        this->pret += x;
        return *this;
    }
    Produs operator*=(int x) {

        this->pret *= x;
        return *this;
    }
    bool operator<(const Produs& p) {

        if (this->pret < p.pret)
            return true;
        return false;

    }
};
int Produs::contorId=1000;
Produs::Produs():IdProdus(contorId++){

        this->nume=new char[strlen("Anonim")+1];
        strcpy(this->nume,"Anonim");


        this -> pret = 0;
        this -> garantie = 0;
        this -> sector = 'A';
        this -> nrReviewuri = 0;
        this -> reviewuri = NULL;
}
Produs::Produs(char* nume, double pret, int garantie, char sector, int nrReviewuri, int* reviewuri):IdProdus(contorId++){

        this -> nume= new char[strlen(nume)+1];
        strcpy(this -> nume, nume);

        this -> pret = pret;
        this -> garantie = garantie;
        this -> sector = sector;

        this -> nrReviewuri= nrReviewuri;
        for(int i=0; i< this->nrReviewuri; i++)
            this->reviewuri[i]=reviewuri[i];


}
Produs::Produs(const Produs& p): IdProdus(p.IdProdus){ //copy constructor

        this -> nume= new char[strlen(p.nume)+1];
        strcpy(this -> nume,p.nume);

        this -> pret = p.pret;
        this -> garantie = p.garantie;
        this -> sector = p.sector;

        this -> nrReviewuri= p.nrReviewuri;
        for(int i=0; i< this->nrReviewuri; i++)
            this->reviewuri[i]=p.reviewuri[i];
}
Produs& Produs::operator = (const Produs& p){

        if(this!=&p){

            if(this->nume!=NULL)
            delete[] this->nume;

            this->nume=new char[strlen(p.nume)+1];
            strcpy(this->nume,p.nume);

            this -> pret = p.pret;
            this -> garantie = p.garantie;
            this -> sector = p.sector;

            this -> nrReviewuri= p.nrReviewuri;
            for(int i=0; i< this->nrReviewuri; i++)
            this->reviewuri[i]=p.reviewuri[i];
        }
        return *this;
}
Produs::~Produs(){
        if(this->nume!=NULL)
            delete[] this->nume;

        if(this->reviewuri!=NULL)
            delete[] this->reviewuri;
}
int  Produs::getPret(){

    return this->pret;

}
int  Produs::getGarantie(){

    return this->garantie;
}
int  Produs::getSector(){

    return this->sector;
}
const char* Produs::getNume(){
        return this->nume;
    }
void  Produs::setPret(double pret){
    this->pret=pret;
}
void  Produs::setGarantie(int garantie){
    this->garantie=garantie;
}
void  Produs::setSector(char sector){
    this->sector=sector;
}
void  Produs::setNume(char* nume){

         if(this->nume!=NULL)
            delete[] this->nume;
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
}
istream& operator>>(istream& in, Produs& p){

    cout<<"\nNume: ";
    char aux[100];
    in>>aux;

    if(p.nume!=NULL)
        delete[] p.nume;
    p.nume=new char[strlen(aux)+1];
    strcpy(p.nume,aux);

    int ok;
    ok=0;
    while(ok==0){
        try{
            cout<<"\nPret: ";
            in>>p.pret;
            if(p.pret<0) throw p.pret;
            ok=1;
        }
        catch(double x){
            cout<<"Pretul nu poate fi negativ!";
        }
    }
    ok=0;
    while(ok==0){
        try{
            cout<<"\nGarantie: ";
            in>>p.garantie;
            if(p.garantie<0) throw 0;
            ok=1;
        }
        catch(int x){
            cout<<"Garantia nu poate fi negativa!";
        }
    }
    ok=0;
    while(ok==0){
        try{
            cout<<"\nSector: ";
            in>>p.sector;
            if(strchr("ABCDEF",p.sector)==NULL) throw p.sector;
            ok=1;
        }
        catch(char a){
            cout<<"Sectoarele sunt doar A B C D E F";
        }
    }
    ok=0;
    while(ok==0){
        try{
            cout<<"\nCate reviewuri sunt?";
            in>>p.nrReviewuri;
            if(p.nrReviewuri<0) throw 0;
            ok=1;
        }
        catch(int x){
            cout<<"Numarul de reviewuri nu poate fi negativ!";
        }
    }
    cout<<"\nReviewuri: ";
    if(p.reviewuri!=NULL)
        delete[] p.reviewuri;
    p.reviewuri=new int[p.nrReviewuri];
    for(int i=0; i<p.nrReviewuri; i++)
    {
        ok=0;
        while(ok==0)
        try{
            in>>p.reviewuri[i];
            if(p.reviewuri[i]<1 || p.reviewuri[i]>5) throw 0;
            ok=1;
        }
        catch(int x){
            cout<<"Introduceti un review intre 1 si 5\n";
        }
    }
    return in;

}
ostream& operator<<(ostream& out, const Produs& p){

    out<<"\nNume: "<<p.nume;
    out<<"\nPret: "<<p.pret;
    out<<"\nGarantie: "<<p.garantie;
    out<<"\nSector: "<<p.sector;

    out<<"\nCele " <<p.nrReviewuri<<" reviewuri sunt: ";
    for(int i=0; i<p.nrReviewuri; i++)
        out<<p.reviewuri[i]<<", ";


    return out;
}
const Produs& Produs::operator++(){
    this->pret++;
    return *this;
}
const Produs Produs::operator++(int){
    Produs aux(*this);
    this->garantie++;
    return aux;
}
void  Produs::afisare(){

    cout<<"\nNume: "<<this -> nume;
    cout<<"\nPret: "<<this -> pret;
    cout<<"\nGarantie: "<<this -> garantie;
    cout<<"\nSector: "<<this -> sector;

    cout<<"\nCele " <<this -> nrReviewuri<<" reviewuri sunt: ";
    for(int i=0; i<this -> nrReviewuri; i++)
        cout<<this -> reviewuri[i]<<", ";

}
int Produs::ReviewuriPozitive(){

    int k=0;
    for(int i=0; i< this->nrReviewuri; i++)
        if(this->reviewuri[i] == 5) k++;
    return k;
}
float Produs::operator[](int index) {

    if (0 <= index && index < this->nrReviewuri)
        return this->reviewuri[index];
    cout << "Index introdus gresit";

}
void Produs::stergereReview(){

    int* aux;
    aux = new int[this -> nrReviewuri -1];
    for(int i=0; i< this->nrReviewuri-1; i++)
        aux[i]=this->reviewuri[i];
    if (this -> reviewuri != NULL)
            delete[] this -> reviewuri;

    this -> nrReviewuri--;

        reviewuri = new int[this -> nrReviewuri];
        for (int i = 0; i < this -> nrReviewuri; i++)
            this->reviewuri[i]=aux[i];


}
void Produs::adaugareReview(int x){

    int* aux;
    aux = new int[this -> nrReviewuri];
    for(int i=0; i< this->nrReviewuri; i++)
        aux[i]=this->reviewuri[i];
    if (this -> reviewuri != NULL)
            delete[] this -> reviewuri;

    this -> nrReviewuri++;

        reviewuri = new int[this -> nrReviewuri];
        for (int i = 0; i < this -> nrReviewuri-1; i++)
            this->reviewuri[i]=aux[i];
        this -> reviewuri[nrReviewuri-1]=x;

}

class Client{
private:


    char* nume;
    int nrArticole;
    float pretArticole;
    const int  IdClient;
    bool fidelitate;
    static int contorId;

    Produs* listaArticole;
public:

    Client();
    Client(char* nume, int nrArticole, float pretArticole, bool fidelitate, Produs* listaArticole);
    Client(const Client& c);
    Client& operator = (const Client& c);

    static int getcontorId(){return Client::contorId;}
    int getIdClient() {return this -> IdClient;}

    void setNume(char* nume);
    void setNrArticole (int nrArticole);
    void setFidelitate (bool fidelitate);
    void setPretArticole (float pretArticole);
    int getPretArticole();
    int getNrArticole();
    int getFidelitate();
    const char* getNume();

    friend istream& operator>>(istream& in, Client& c);
    friend ostream& operator<<(ostream& out,const Client& c);


    const Client& operator++();//pre-incremetare
    const Client operator++(int);//post-incrementare
    friend Client operator+(Client c,  Produs p);
    friend Client operator+(const Produs& p, Client c);
    void stergereProdus(Client c);
    Produs operator[](int index);

    void afisare();
    void produseGarantie(int x);

    ~Client();

    bool operator==(const Client& c) {

        if (this->nrArticole == c.nrArticole )
            return true;
        return false;
    }
    Client operator+=(float x) {

        this->pretArticole += x;
        return *this;
    }
    Client operator*=(float x) {

        this->pretArticole *= x;
        return *this;
    }
    bool operator<(const Client& c) {

        if (this->pretArticole < c.pretArticole)
            return true;
        return false;

    }
};
int Client::contorId=1000;
Client::Client():IdClient(contorId++){

        this->nume=new char[strlen("Anonim")+1];
        strcpy(this->nume,"Anonim");


        this->nrArticole=0;
        this -> pretArticole = 0;
        this -> fidelitate = false;

        this -> listaArticole = NULL;
}
Client::Client(char* nume, int nrArticole, float pretArticole, bool fidelitate, Produs* listaArticole):IdClient(contorId++){

        this -> nume= new char[strlen(nume)+1];
        strcpy(this -> nume, nume);

        this -> nrArticole = nrArticole;
        this -> pretArticole = pretArticole;
        this -> fidelitate = fidelitate;

        for(int i=0; i< this->nrArticole; i++)
            this->listaArticole[i]=listaArticole[i];
    }
Client::Client(const Client& c): IdClient(c.IdClient){ //copy constructor

        this -> nume= new char[strlen(c.nume)+1];
        strcpy(this -> nume,c.nume);

        this -> nrArticole = c.nrArticole;
        this -> pretArticole = c.pretArticole;
        this -> fidelitate = c.fidelitate;

        for(int i=0; i< this->nrArticole; i++)
            this->listaArticole[i]=c.listaArticole[i];
    }
Client& Client::operator = (const Client& c){

        if(this!=&c){

            if(this->nume!=NULL)
            delete[] this->nume;

            this->nume=new char[strlen(c.nume)+1];
            strcpy(this->nume,c.nume);

            this->nrArticole=c.nrArticole;
            this->pretArticole=c.pretArticole;
            this->fidelitate=c.fidelitate;

            for(int i=0; i< this->nrArticole; i++)
            this->listaArticole[i]=c.listaArticole[i];

        }
        return *this;
    }
Client::~Client(){

        if(this->nume!=NULL)
            delete[] this->nume;

        if(this->listaArticole!=NULL)
            delete[] this->listaArticole;
     }
void  Client::setNrArticole( int nrArticole){

    this->nrArticole=nrArticole;

}
void  Client::setPretArticole(float pretArticole){

    this->pretArticole=pretArticole;

}
void  Client::setFidelitate( bool fidelitate){

    this->fidelitate=fidelitate;

}
void  Client::setNume(char* nume){

         if(this->nume!=NULL)
            delete[] this->nume;

        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
}
int  Client::getNrArticole(){

        return this->nrArticole;

    }
int  Client::getPretArticole(){

        return this->pretArticole;

    }
int  Client::getFidelitate(){

        return this->fidelitate;

    }
const char* Client::getNume(){

        return this->nume;

    }
istream& operator>>(istream& in, Client& c){

    cout<<"\nNume: ";
    char aux[100];
    in>>aux;

    if(c.nume!=NULL)
        delete[] c.nume;
    c.nume=new char[strlen(aux)+1];
    strcpy(c.nume,aux);

    int ok=0;
    while(ok==0){
        try{
            cout<<"\nPretArticole: ";
            in>>c.pretArticole;
            if(c.pretArticole < 0) throw(0);
            ok=1;
        }
        catch(int x){
            cout<<"Pretul Articolelor nu poate fi negativ";
        }
    }
    cout<<"\nFidelitate [1-true/0-false]: ";
    in>>c.fidelitate;
    ok=0;
    while(ok==0){
        try{
            cout<<"\nNrArticole: ";
            in>>c.nrArticole;
            if(c.nrArticole < 0) throw(0);
            ok=1;
        }
        catch(int x){
            cout<<"Numarul articolelor nu poate fi negativ";
        }
    }
    cout<<"\nLista Articole:\n";

    if(c.listaArticole!=NULL)
        delete[] c.listaArticole;
    c.listaArticole=new Produs[c.nrArticole];
    for(int i=0; i<c.nrArticole; i++)
        in>>c.listaArticole[i];

    return in;

}
ostream& operator<<(ostream& out, const Client& c){

    out<<"\nNume: "<<c.nume;

    out<<"\nNrArticole: "<<c.nrArticole;
    out<<"\nPretArticole: "<<c.pretArticole;
    out<<"\nFidelitate: ";
    if(c.fidelitate) out<<"da";
    else out<<"nu";

    out<<"\nLista articole:";
    for(int i=0; i<c.nrArticole; i++)
        out<<c.listaArticole[i]<<", ";
    return out;
}
void  Client::afisare(){

    cout<<"\nNume: "<<this -> nume;
    cout<<"\nNrArticole: "<<this ->nrArticole;
    cout<<"\nPretArticole: "<<this ->pretArticole;
    cout<<"\nFidelitate: ";
    if(this -> fidelitate) cout<<"da";
    else cout<<"nu";

   cout<<"\nLista articole: ";
    for(int i=0; i<this -> nrArticole; i++)
        cout<<this -> listaArticole[i]<<", ";

}
void Client::produseGarantie(int x){

    int ok=0;
    for(int i=0; i<this -> nrArticole; i++)
        if(this -> listaArticole[i].getGarantie() >= x)
            {
                cout<<this -> listaArticole[i].getNume()<<", ";
                ok=1;
            }
    if(ok==0) cout<<"Nu e niciun produs cu garantie mai mare sau egala cu "<<x<<" ani!";
}
const Client& Client::operator++(){

    this->nrArticole++;
    return *this;
}
const Client Client::operator++(int){

    Client aux(*this);
    this->nrArticole++;

    return aux;
}
Produs Client::operator[](int index) {

    if (0 <= index && index < this->nrArticole)
        return this->listaArticole[index];
    cout << "Index introdus gresit";

}
Client operator+(Client c,  Produs p){

    Produs* listaArticoleAux;
    if(c.nrArticole!=0)
    {

        listaArticoleAux = new Produs[c.nrArticole];
        for (int i = 0; i < c.nrArticole; i++) {
            listaArticoleAux[i] = c.listaArticole[i];
        }
        if (c.listaArticole != NULL)
            delete[] c.listaArticole;

    }
        c.nrArticole++;

        c.listaArticole = new Produs[c.nrArticole];
        for (int i = 0; i < c.nrArticole - 1; i++)
            c.listaArticole[i] = listaArticoleAux[i];

        c.listaArticole[c.nrArticole - 1] = p;

        if (listaArticoleAux != NULL)
            delete[] listaArticoleAux;
        return c;


}
Client operator+(const Produs& p, Client c){
        Produs* listaArticoleAux;
        listaArticoleAux = new Produs[c.nrArticole];
        for (int i = 0; i < c.nrArticole; i++) {
            listaArticoleAux[i] = c.listaArticole[i];
        }
        if (c.listaArticole != NULL)
            delete[] c.listaArticole;

        c.nrArticole++;

        c.listaArticole = new Produs[c.nrArticole];
        for (int i = 0; i < c.nrArticole - 1; i++)
            c.listaArticole[i] = listaArticoleAux[i];

        c.listaArticole[c.nrArticole - 1] = p;

        if (listaArticoleAux != NULL)
            delete[] listaArticoleAux;
        return c;


}
void Client::stergereProdus(Client c){

    Produs* aux;
    aux = new Produs[c.nrArticole -1];
    for(int i=0; i< c.nrArticole-1; i++)
        aux[i]=c.listaArticole[i];
    if (c.listaArticole != NULL)
            delete[] c.listaArticole;

    c.nrArticole--;

        c.listaArticole = new Produs[c.nrArticole];
        for (int i = 0; i < c.nrArticole; i++)
            c.listaArticole[i]=aux[i];
}

class Management{
private:

    float* cheltuieliLunare;
    int luni;
    float donatiiONG;
    bool profit;
public:

    Management();
    Management(float* cheltuieliLunare, int luni, float donatiiONG, bool profit);
    Management(const Management& ang);
    Management& operator = (const Management& ang);

    void setLuni (int luni);
    void setDonatiiONG (float donatiiONG);
    void setProfit (bool profit);
    void setCheltuieli(float * cheltuieliLunare, int luni);

    int getLuni();
    int getDonatiiONG();
    int getProfit();
    const float*  getCheltuieli()const ;

    friend istream& operator>>(istream& in, Management& m);
    friend ostream& operator<<(ostream& out,const Management& m);

    const Management& operator++();//pre-incremetare
    const Management operator++(int);//post-incrementare

    float operator[](int index);

    void afisare();
    void stergereCheltuieliUltimaLuna();
    void adaugareCheltuieli(float x);
    void cheltuieliMaxime();

    ~Management();

     bool operator==(const Management& m) {

        if (this->donatiiONG == m.donatiiONG )
            return true;
        return false;

    }
    Management operator+=(int x) {

        this->donatiiONG += x;
        return *this;
    }
    Management operator*=(int x) {

        this->donatiiONG *= x;
        return *this;
    }
    bool operator<(const Management& m) {

        if (this->donatiiONG < m.donatiiONG)
            return true;
        return false;

    }
};
Management::Management(){

    this -> cheltuieliLunare = NULL;
    this -> luni = 0;
    this -> donatiiONG = 0;
    this -> profit = false;
}
Management::Management(float* cheltuieliLunare, int luni, float donatiiONG, bool profit){

    this -> luni = luni;
    this -> donatiiONG = donatiiONG;
    this -> profit = profit;

    for(int i=0; i< this->luni; i++)
            this->cheltuieliLunare[i]=cheltuieliLunare[i];

}
Management::Management(const Management& m){ //copy constructor

            this -> luni = m.luni;
            this -> donatiiONG = m.donatiiONG;
            this -> profit = m.profit;

            for(int i=0; i< this->luni; i++)
            this->cheltuieliLunare[i]=m.cheltuieliLunare[i];
    }
Management& Management::operator = (const Management& m){

        if(this != &m){

            this -> luni = m.luni;
            this -> donatiiONG = m.donatiiONG;
            this -> profit = m.profit;

            for(int i=0; i< this->luni; i++)
            this->cheltuieliLunare[i]=m.cheltuieliLunare[i];
        }
        return *this;
    }
Management::~Management(){

       if(this->cheltuieliLunare!=NULL)
            delete[] this->cheltuieliLunare;

        if(this->cheltuieliLunare!=NULL)
            delete[] this->cheltuieliLunare;
}
void  Management::setLuni(int luni){

    this->luni=luni;

}
void  Management::setDonatiiONG(float donatiiONG){

    this->donatiiONG=donatiiONG;

}
void  Management::setProfit(bool profit){

    this->profit=profit;

}
void Management::setCheltuieli(float * cheltuieliLunare, int luni){

        if(this->cheltuieliLunare!=NULL)
            delete[] this->cheltuieliLunare;

        this->luni=luni;
        this->cheltuieliLunare=new float[this->luni];
        for(int i=0; i< this->luni; i++)
            this->cheltuieliLunare[i]=cheltuieliLunare[i];

    }
int  Management::getLuni(){

        return this->luni;

    }
int  Management::getDonatiiONG(){

        return this->donatiiONG;

    }
int  Management::getProfit(){

        return this->profit;

    }
const float* Management::getCheltuieli()const {

        return this->cheltuieliLunare;

}
istream& operator>>(istream& in, Management& m){

    int ok=0;
    while(ok==0){
        try{
            cout<<"\nCati bani au fost donati catre ONG-uri?: ";
            in>>m.donatiiONG;
            if(m.donatiiONG<0) throw 0;
            ok=1;
        }
        catch(int x){
            cout<<"Suma donata nu poate fi negativa";
        }
    }
    cout<<"\nProfit [1-true/0-false]: ";
    in>>m.profit;


    ok=0;
    while(ok==0){
        try{
            cout<<"\nPe cate luni contorizam cheltuielile? ";
            in>>m.luni;
            if(m.luni<0) throw 0;
            ok=1;
        }
        catch(int x){
            cout<<"Numarul de luni trebuie sa fie pozitiv";
        }
    }
    cout<<"\nCheltuieli: ";

    if(m.cheltuieliLunare!=NULL)
        delete[] m.cheltuieliLunare;
    m.cheltuieliLunare=new float[m.luni];
    for(int i=0; i<m.luni; i++)
    {
        ok=0;
        while(ok==0)
        try{
            in>>m.cheltuieliLunare[i];
            if(m.cheltuieliLunare[i]<0 ) throw 0;
            ok=1;
        }
        catch(int x){
            cout<<"Cheltuielile sunt numere pozitive\n";
        }
    }
    return in;

}
ostream& operator<<(ostream& out, const Management& m){

    out<<"\nBani donati catre ONG-uri: "<<m.donatiiONG;
    out<<"\nProfit:  ";
    if(m.profit) out<<"da";
    else out<<"nu";

    out<<"\nIn ultimele " <<m.luni<<" luni, s-au inregistrat urmatoarele cheltuieli ";
    for(int i=0; i<m.luni; i++)
        out<<m.cheltuieliLunare[i]<<", ";

    return out;
}
const Management& Management::operator++(){
    this->donatiiONG++;
    return *this;
}
const Management Management::operator++(int){
    Management aux(*this);
    this->donatiiONG++;
    return aux;
}
void  Management::afisare(){

    cout<<"\nBani donati catre ONG-uri: "<<this -> donatiiONG;
    cout<<"\nProfit:  ";
    if(this -> profit) cout<<"da";
    else cout<<"nu";

    cout<<"\nIn ultimele " <<this -> luni<<" luni, s-au inregistrat urmatoarele cheltuieli ";
    for(int i=0; i<this -> luni; i++)
        cout<<this-> cheltuieliLunare[i]<<", ";

}
void Management::cheltuieliMaxime(){

    int cheltuieliMaxime=-1,indexMaxim=-1;
    for(int i=0; i<this -> luni; i++)
        if( this -> cheltuieliLunare[i]>=cheltuieliMaxime)
        {
            cheltuieliMaxime = this -> cheltuieliLunare[i];
            indexMaxim = i+1;
        }
    cout<<"In luna "<<indexMaxim<<" s-au inregistrat cele mai mari cheltuieli, in valoare de "<<cheltuieliMaxime<<" lei.";
}
float Management::operator[](int index) {

    if (0 <= index && index < this->luni)
        return this->cheltuieliLunare[index];
    cout << "Index introdus gresit";

}
void Management::stergereCheltuieliUltimaLuna(){

    float* aux;
    aux = new float[this -> luni -1];
    for(int i=0; i< this->luni-1; i++)
        aux[i]=this->cheltuieliLunare[i];
    if (this -> cheltuieliLunare != NULL)
            delete[] this -> cheltuieliLunare;

    this -> luni--;

        cheltuieliLunare = new float[this -> luni];
        for (int i = 0; i < this -> luni; i++)
            this->cheltuieliLunare[i]=aux[i];
}
void Management::adaugareCheltuieli(float x){

    float* aux;
    aux = new float[this -> luni];
    for(int i=0; i< this->luni; i++)
        aux[i]=this->cheltuieliLunare[i];
    if (this -> cheltuieliLunare != NULL)
            delete[] this -> cheltuieliLunare;

    this -> luni++;

        cheltuieliLunare = new float[this -> luni];
        for (int i = 0; i < this -> luni-1; i++)
            this->cheltuieliLunare[i]=aux[i];
        this -> cheltuieliLunare[luni-1]=x;

}


class CitireAfisare{
public:
    virtual ostream& Afisare(ostream&)const=0;
    virtual istream& Citire(istream&)=0;
};


class Angajat: public CitireAfisare{
protected:

    char* nume;
    const int  IdAngajat;
    float* bonusLunar;
    int luni;

    static int contorId;
    int varsta;
public:

    Angajat();
    Angajat(char* nume, int varsta,float* bonusLunar, int luni);
    Angajat(const Angajat& ang);
    Angajat& operator = (const Angajat& ang);

    static int getcontorId(){return Angajat::contorId;}
    int getIdAngajat() {return this -> IdAngajat;}

    void setNume(char* nume);
    void setVarsta (int varsta);
    int getVarsta();
    const char* getNume();

    virtual ostream& Afisare(ostream&)const;
    virtual istream& Citire(istream&);

    friend istream& operator>>(istream& in, Angajat& ang);
    friend ostream& operator<<(ostream& out,const Angajat& ang);

    const Angajat& operator++();//pre-incremetare
    const Angajat operator++(int);//post-incrementare

    float operator[](int index);

    void afisare();
    void Bonusuri(int x);
    void stergereBonus();
    void adaugareBonus(float x);


    ~Angajat();

    bool operator==(const Angajat& ang) {

        if (this->varsta == ang.varsta )
            return true;
        return false;
    }
    Angajat operator+=(int x) {

        this->varsta += x;
        return *this;
    }
    Angajat operator*=(int x) {

        for(int i=0; i<this -> luni; i++)
            this -> bonusLunar[i]*=x;
        return *this;
    }
    bool operator<(const Angajat& ang) {

        if (this->varsta < ang.varsta)
            return true;
        return false;

    }
    void Functie(){
        cout<<"\nAcesta este un Angajat";
    }
};
int Angajat::contorId=1000;
istream& Angajat::Citire(istream& in){

    cout<<"\nNume: ";
    char aux[100];
    in>>aux;

    if(this->nume!=NULL)
        delete[] this->nume;
    this->nume=new char[strlen(aux)+1];
    strcpy(this->nume,aux);

    int ok=0;
    while(ok==0){
        try{
            cout<<"\nVarsta: ";
            in>>this->varsta;
            if(this->varsta<18 || this->varsta>65) throw 0;
            ok=1;
        }
        catch(int x){
            cout<<"Varsta angajatului trebuie sa fie mai mare decat 18 si mai mica decat 65 de ani\n";
        }
    }
    ok=0;
    while(ok==0){
        try{
            cout<<"\nPe cate luni contorizam?";
            in>>this->luni;
            if(this->luni<0) throw 0;
            ok=1;
        }
        catch(int x){
            cout<<"Introduceti un numar pozitiv de luni\n";
        }
    }
    cout<<"\nBonusuri: ";

    if(this->bonusLunar!=NULL)
        delete[] this->bonusLunar;
    this->bonusLunar=new float[this->luni];
    for(int i=0; i<this->luni; i++)

    {
        ok=0;
        while(ok==0)
        try{
            in>>this->bonusLunar[i];
            if(this->bonusLunar[i]<0 ) throw 0;
            ok=1;
        }
        catch(int x){
            cout<<"Bonusurile trebuie sa fie pozitive\n";
        }
    }
    return in;

}
ostream& Angajat::Afisare(ostream& out)const{
    out<<"\nNume: "<<this->nume;
    out<<"\nVarsta: "<<this->varsta;

    out<<"\nIn ultimele " <<this->luni<<" luni, s-au inregistrat urmatoarele bonusuri ";
    for(int i=0; i<this->luni; i++)
        out<<this->bonusLunar[i]<<", ";

    return out;
}
Angajat::Angajat():IdAngajat(contorId++){

        this->nume=new char[strlen("Anonim")+1];
        strcpy(this->nume,"Anonim");


        this->varsta=0;
        this -> luni= 0;
        this -> bonusLunar = NULL;
    }
Angajat::Angajat(char* nume, int varsta, float* bonusLunar, int luni):IdAngajat(contorId++){

        this -> nume= new char[strlen(nume)+1];
        strcpy(this -> nume, nume);

         this -> varsta = varsta;
        this -> luni= luni;

        for(int i=0; i< this->luni; i++)
            this->bonusLunar[i]=bonusLunar[i];

    }
Angajat::Angajat(const Angajat& ang): IdAngajat(ang.IdAngajat){ //copy constructor

        this -> nume= new char[strlen(ang.nume)+1];
        strcpy(this -> nume,ang.nume);

        this -> varsta = ang.varsta;
        this -> luni = ang.luni;

        for(int i=0; i< this->luni; i++)
            this->bonusLunar[i]=ang.bonusLunar[i];

    }
Angajat& Angajat::operator = (const Angajat& ang){

        if(this!=&ang){

            if(this->nume!=NULL)
            delete[] this->nume;

            this->nume=new char[strlen(ang.nume)+1];
            strcpy(this->nume,ang.nume);
            this->varsta=ang.varsta;
            this -> luni = ang.luni;

            for(int i=0; i< this->luni; i++)
            this->bonusLunar[i]=ang.bonusLunar[i];
        }
        return *this;
    }
Angajat::~Angajat(){
        if(this->nume!=NULL)
            delete[] this->nume;

        if(this->bonusLunar!=NULL)
            delete[] this->bonusLunar;
     }
void  Angajat::setVarsta( int varsta){
    this->varsta=varsta;}
void  Angajat::setNume(char* nume){

        if(this->nume!=NULL)
            delete[] this->nume;
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
}
int  Angajat::getVarsta(){

        return this->varsta;
    }
const char* Angajat::getNume(){
        return this->nume;
    }
istream& operator>>(istream& in, Angajat& ang){

    /*cout<<"\nNume: ";
    char aux[100];
    in>>aux;

    if(ang.nume!=NULL)
        delete[] ang.nume;
    ang.nume=new char[strlen(aux)+1];
    strcpy(ang.nume,aux);

    cout<<"\nVarsta: ";
    in>>ang.varsta;
    cout<<"\nPe cate luni contorizam?";
    in>>ang.luni;

    cout<<"\nBonusuri: ";

    if(ang.bonusLunar!=NULL)
        delete[] ang.bonusLunar;
    ang.bonusLunar=new float[ang.luni];
    for(int i=0; i<ang.luni; i++)
        in>>ang.bonusLunar[i];

    return in;*/
    return ang.Citire(in);}
ostream& operator<<(ostream& out, const Angajat& ang){
    /*out<<"\nNume: "<<ang.nume;
    out<<"\nVarsta: "<<ang.varsta;

    out<<"\nIn ultimele " <<ang.luni<<" luni, s-au inregistrat urmatoarele bonusuri ";
    for(int i=0; i<ang.luni; i++)
        out<<ang.bonusLunar[i]<<", ";

    return out;*/
    return ang.Afisare(out);
}
void  Angajat::afisare(){

    cout<<"\nNume: "<<this -> nume;
    cout<<"\nVarsta: "<<this ->varsta;
    cout<<"\nIn ultimele " <<this -> luni<<" luni, s-au inregistrat urmatoarele bonusuri ";
    for(int i=0; i<this ->luni; i++)
        cout<<this -> bonusLunar[i]<<", ";

}
void  Angajat::Bonusuri(int x) {

        int ok=0;
        for(int i=0; i< this->luni; i++)
        {
            if(this->bonusLunar[i] > x) {cout<<i+1<<", "; ok=1;}
        }
        if(ok==0) cout<<"\nToate bonusurile sunt mai mici decat "<<x<<".\n";
}
void Angajat::stergereBonus(){

    float* aux;
    aux = new float[this -> luni -1];
    for(int i=0; i< this->luni-1; i++)
        aux[i]=this->bonusLunar[i];
    if (this -> bonusLunar != NULL)
            delete[] this -> bonusLunar;

    this -> luni--;

        bonusLunar = new float[this -> luni];
        for (int i = 0; i < this -> luni; i++)
            this->bonusLunar[i]=aux[i];


}
void Angajat::adaugareBonus(float x){

    float* aux;
    aux = new float[this -> luni];
    for(int i=0; i< this->luni; i++)
        aux[i]=this->bonusLunar[i];
    if (this -> bonusLunar != NULL)
            delete[] this -> bonusLunar;

    this -> luni++;

        bonusLunar = new float[this -> luni];
        for (int i = 0; i < this -> luni-1; i++)
            this->bonusLunar[i]=aux[i];
        this -> bonusLunar[luni-1]=x;

}
const Angajat& Angajat::operator++(){
    this->varsta++;
    return *this;
}
const Angajat Angajat::operator++(int){
    Angajat aux(*this);
    this->varsta++;
    return aux;
}
float Angajat::operator[](int index){

    if (0 <= index && index < this->luni)
        return  this->bonusLunar[index];
    cout << "Index introdus gresit";

}


class Vanzator: virtual public Angajat{
protected:
    char sector;
    int nrArticoleVandute;

    Produs* ArticoleVandute;
public:

    Vanzator();
    Vanzator(char sector, int nrArticoleVandute, Produs* ArticoleVandute,char* nume, int varsta, float* bonusLunar, int luni);
    Vanzator(const Vanzator& v);
    Vanzator& operator = (const Vanzator& v);
    ostream& Afisare(ostream&)const;
    istream& Citire(istream&);
    ~Vanzator();
    void Functie(){
        cout<<"\nAcesta este un Vanzator";
    }

};
Vanzator::Vanzator() : Angajat(){
    this->sector='A';
    this->nrArticoleVandute=0;

    this->ArticoleVandute= NULL;
}
Vanzator::Vanzator(char sector, int nrArticoleVandute, Produs* ArticoleVandute,char* nume, int varsta, float* bonusLunar, int luni):Angajat(){

    this->sector = sector;
    this->nrArticoleVandute = nrArticoleVandute;
    for(int i=0; i< this->nrArticoleVandute; i++)
            this->ArticoleVandute[i]=ArticoleVandute[i];
}
Vanzator::Vanzator(const Vanzator& v):Angajat(v){
    this->sector = v.sector;
    this->nrArticoleVandute = v.nrArticoleVandute;
    for(int i=0; i< this->nrArticoleVandute; i++)
            this->ArticoleVandute[i]=v.ArticoleVandute[i];
}
Vanzator& Vanzator:: operator=(const Vanzator& v){
    if(this!=&v)
    {
        Angajat::operator=(v);
        this->sector=v.sector;
        this->nrArticoleVandute = v.nrArticoleVandute;
        for(int i=0; i< this->nrArticoleVandute; i++)
            this->ArticoleVandute[i]=v.ArticoleVandute[i];
    }
    return *this;
}
istream& Vanzator::Citire(istream& in){


    Angajat::Citire(in);
    int ok=0;
    while(ok==0){
        try{
            cout<<"\nSector: ";
            in>>this->sector;
            if(strchr("ABCDEF",this->sector)==NULL) throw this->sector;
            ok=1;
        }
        catch(char a){
            cout<<"Sectoarele sunt doar A B C D E F";
        }
    }
    ok=0;
    while(ok==0){
        try{
            cout<<"\nCate articole a vandut?: ";
            in>>this->nrArticoleVandute;
            if(this-> nrArticoleVandute < 0) throw 0;
            ok=1;
        }
        catch(int a){
            cout<<"Numarul articolelor vandute trebuie sa fie pozitiv";
        }
    }
    cout<<"\nCe articole a vandut?:";

    if(this->ArticoleVandute!=NULL)
        delete[] this->ArticoleVandute;
    this->ArticoleVandute=new Produs[this->nrArticoleVandute];
    for(int i=0; i<this->nrArticoleVandute; i++)
        in>>this->ArticoleVandute[i];

    return in;
}
ostream& Vanzator::Afisare(ostream& out) const{

    Angajat::Afisare(out);
    cout<<"\nSector: ";
    out<<this->sector;

    cout<<"\nA vandut "<< this->nrArticoleVandute <<" articole";
    cout<<"\nArticolele pe care le-a vandut au fost:";

    for(int i=0; i<this->nrArticoleVandute; i++)
        out<<this->ArticoleVandute[i];
    return out;

}
Vanzator::~Vanzator(){

    if(this->ArticoleVandute!=NULL)
            delete[] this->ArticoleVandute;
}

class Manager: virtual public Angajat{
protected:
    int nrSubordonati;
    Management situatieMagazin;
public:

    Manager();
    Manager(int nrSubordonati, Management situatieMagazin,char* nume, int varsta, float* bonusLunar, int luni);
    Manager(const Manager& m);
    Manager& operator = (const Manager& m);
    ostream& Afisare(ostream&)const;
    istream& Citire(istream&);
    void Functie(){
        cout<<"\nAcesta este un Manager";
    }
};
Manager::Manager() : Angajat(){
    this->nrSubordonati=0;
    this->situatieMagazin = Management();
}
Manager::Manager(int nrSubordonati, Management situatieMagazin,char* nume, int varsta, float* bonusLunar, int luni):Angajat(){

    this->nrSubordonati=nrSubordonati;
    this->situatieMagazin = situatieMagazin;
}
Manager::Manager(const Manager& m):Angajat(m){
    this->nrSubordonati=m.nrSubordonati;
    this->situatieMagazin = m.situatieMagazin;
}
Manager& Manager:: operator=(const Manager& m){
    if(this!=&m)
    {
        this->nrSubordonati=m.nrSubordonati;
        Angajat::operator=(m);
        this->situatieMagazin = m.situatieMagazin;
    }
    return *this;
}
istream& Manager::Citire(istream& in){


    Angajat::Citire(in);
    int ok=0;
    while(ok==0){
        try{
            cout<<"\nCati subordinati are?: ";
            in>>this->nrSubordonati;
            if(this->nrSubordonati<0) throw 0;
            ok=1;
        }
        catch(int x){
            cout<<"Introduceti un numar pozitiv de subordinati\n";
        }
    }
    cout<<"\nCare este situatia magazinului?\n ";
    in>>this->situatieMagazin;
    return in;
}
ostream& Manager::Afisare(ostream& out) const{


    Angajat::Afisare(out);
    cout<<"\nNumar subordonati: ";
    out<<this->nrSubordonati;
    cout<<"\nSituatia magazinului este urmatoarea: ";
    out<<this->situatieMagazin;
    return out;

}

class VanzatorManager: public Vanzator, public Manager{
private:
    float bonusOreSuplimentare;
public:
    VanzatorManager();
    VanzatorManager(float bonusOreSuplimentare,char* nume, int varsta, float*
                                  bonusLunar,int luni,char sector, int nrArticoleVandute,
                                  Produs* ArticoleVandute,int nrSubordonati, Management situatieMagazin);
    VanzatorManager(const VanzatorManager& vm);
    VanzatorManager& operator = (const VanzatorManager& vm);
    ostream& Afisare(ostream&)const;
    istream& Citire(istream&);
    void Functie(){
        cout<<"\nAcesta este un Vanzator care este si Manager";
    }
};
VanzatorManager::VanzatorManager() : Vanzator(), Manager(){
    this->bonusOreSuplimentare=0;
}
VanzatorManager::VanzatorManager(float bonusOreSuplimentare,char* nume, int varsta, float*
                                  bonusLunar,int luni,char sector, int nrArticoleVandute,
                                  Produs* ArticoleVandute,int nrSubordonati, Management situatieMagazin) :  Vanzator(), Manager(){

    this->bonusOreSuplimentare=bonusOreSuplimentare;
}
VanzatorManager::VanzatorManager(const VanzatorManager& vm):Vanzator(vm), Manager(vm){

    this->bonusOreSuplimentare=vm.bonusOreSuplimentare;
}
VanzatorManager& VanzatorManager:: operator =(const VanzatorManager& vm){
    if(this!=&vm)
    {
        Vanzator::operator=(vm);
        Manager::operator=(vm);
        this->bonusOreSuplimentare=vm.bonusOreSuplimentare;
    }
    return *this;
}
istream& VanzatorManager::Citire(istream& in){

    Vanzator::Citire(in);
    //Manager::Citire(in);
    int ok=0;
    while(ok==0){
        try{
            cout<<"\nCati subordinati are?: ";
            in>>this->nrSubordonati;
            if(this->nrSubordonati<0) throw 0;
            ok=1;
        }
        catch(int x){
            cout<<"Introduceti un numar pozitiv de subordinati\n";
        }
    }
    cout<<"\nCare este situatia magazinului?\n ";
    in>>this->situatieMagazin;
    ok=0;
    while(ok==0){
        try{
            cout<<"\nCe bonus pentru ore suplimentare are?: ";
            in>>this->bonusOreSuplimentare;
            if(this->bonusOreSuplimentare<0) throw 0;
            ok=1;
        }
        catch(int x){
            cout<<"Angajatul nu poate avea bonusuri negative\n";
        }
    }

    return in;
}
ostream& VanzatorManager::Afisare(ostream& out) const{

    Vanzator::Afisare(out);
    //Manager::Afisare(out);
    cout<<"\nNumar subordonati: ";
    out<<this->nrSubordonati;
    cout<<"\nSituatia magazinului este urmatoarea: ";
    out<<this->situatieMagazin;
    cout<<"\nBonusul pentru orele suplimentare este: ";
    out<<this->bonusOreSuplimentare;
    return out;

}

template<class T>
class Temp{
private:
    T a,b;
public:
    Temp(T x, T y)
    {
        a=x;
        b=y;
    }
    void Compara()
    {
        if(a<b) cout<<a;
        else cout<<b;
    }
    void Aduna()
    {
        cout<<a+b;
    }
};
class MeniuInteractiv{
public:
    void meniu(){
        int l=0;
        while(l==0)
       {
            cout<<"\n1-Angajat\n2-Produs\n3-Client\n4-Management\n5-Casting\n0-Stop\n";
            l=1;
            int comanda1;
            cin>>comanda1;
            switch(comanda1)
            {
                case 1:{
                    while(l==1){
                    cout<<'\n';
                    cout<<"\n1-Vanzator\n2-Manager\n3-VanzatorManager\n0-Stop";
                    int comanda2;
                    cin>>comanda2;
                    l=2;
                    switch(comanda2)
                    {
                        case 1:
                        { //Vanzator
                            Vanzator v;
                            while(l==2)
                            {
                                cout<<'\n';
                                cout<<"\n1-Citire\n2-Contorizare Bonusuri\n3-Creste varsta\n4-Stergere bonus pe ultima luna\n5-Adaugare bonus\n6-Afisare\n7-Functie\n0-Stop\n";
                                int comanda3;
                                cin>>comanda3;
                                switch(comanda3){

                                    case 1: {cin>>v; break;}
                                    case 2: {
                                        // if(system("CLS")) system("clear");
                                        cout<<"Cu ce valoare camparam bonusurile? ";
                                        int x;
                                        cin>>x;
                                        cout<<"Bonusurile mai mari decat "<<x<<" au fost inregistrate in lunile:";
                                        v.Angajat::Bonusuri(x);
                                        break;
                                    }
                                    case 3: {
                                        ++v; break;
                                    }
                                    case 4: {v.stergereBonus(); break;}
                                    case 5: {
                                        int x;
                                        cout<<"Ce bonus adaugam? ";
                                        cin>>x;
                                        v.adaugareBonus(x); break;
                                    }
                                    case 6: {cout<<v<<'\n'; break;}
                                    case 7: {v.Functie(); break;}
                                    case 0: {l=1; break;}

                                }
                            }
                        }
                        case 2:
                        {
                            //Manager
                            Manager m;
                            while(l==2)
                            {
                                cout<<'\n';
                                cout<<"\n1-Citire\n2-Contorizare Bonusuri\n3-Creste varsta\n4-Stergere bonus pe ultima luna\n5-Adaugare bonus\n6-Afisare\n7-Functie\n0-Stop\n";
                                int comanda3;
                                cin>>comanda3;
                                switch(comanda3){

                                    case 1: {cin>>m; break;}
                                    case 2: {
                                        // if(system("CLS")) system("clear");
                                        cout<<"Cu ce valoare camparam bonusurile? ";
                                        int x;
                                        cin>>x;
                                        cout<<"Bonusurile mai mari decat "<<x<<" au fost inregistrate in lunile:";
                                        m.Angajat::Bonusuri(x);
                                        break;
                                    }
                                    case 3: {
                                        ++m; break;
                                    }
                                    case 4: {m.stergereBonus(); break;}
                                    case 5: {
                                        int x;
                                        cout<<"Ce bonus adaugam? ";
                                        cin>>x;
                                        m.adaugareBonus(x); break;
                                    }
                                    case 6: {cout<<m<<'\n'; break;}
                                    case 7: {m.Functie(); break;}
                                    case 0: {l=1; break;}

                                }
                            }
                        }
                        case 3:
                        {
                            //VanzatorManager
                            VanzatorManager vm;
                            while(l==2)
                            {
                                cout<<'\n';
                                cout<<"\n1-Citire\n2-Contorizare Bonusuri\n3-Creste varsta\n4-Stergere bonus pe ultima luna\n5-Adaugare bonus\n6-Afisare\n7-Functie\n0-Stop\n";
                                int comanda3;
                                cin>>comanda3;
                                switch(comanda3){

                                    case 1: {cin>>vm; break;}
                                    case 2: {
                                        // if(system("CLS")) system("clear");
                                        cout<<"Cu ce valoare camparam bonusurile? ";
                                        int x;
                                        cin>>x;
                                        cout<<"Bonusurile mai mari decat "<<x<<" au fost inregistrate in lunile:";
                                        vm.Angajat::Bonusuri(x);
                                        break;
                                    }
                                    case 3: {
                                        ++vm; break;
                                    }
                                    case 4: {vm.stergereBonus(); break;}
                                    case 5: {
                                        int x;
                                        cout<<"Ce bonus adaugam? ";
                                        cin>>x;
                                        vm.adaugareBonus(x); break;
                                    }
                                    case 6: {cout<<vm<<'\n'; break;}
                                    case 7: {vm.Functie(); break;}
                                    case 0: {l=1; break;}

                                }
                            }
                        }
                    }

                }

                        break;
                }
                case 2:{
                    while(l==1){
                        //if(system("CLS")) system("clear");
                        cout<<'\n';
                        cout<<"\n1-Citire";
                        cout<<"\n2-Numar de reviewuri maxime";
                        cout<<"\n3-Set Garantie";
                        cout<<"\n4-Sterge ultimul review";
                        cout<<"\n5-Adauga review";
                        cout<<"\n6-Afisare";
                        cout<<"\n0-Stop\n";

                        int comanda2;
                        cin>>comanda2;
                        Produs p;
                        switch(comanda2)
                        {

                            case 1: {cin>>p; break;}
                            case 2: {

                                cout<<'\n';
                                cout<<p.ReviewuriPozitive()<<" reviewuri maxime";
                                break;
                            }
                            case 3: {
                                int x;
                                cout<<"Ce garantie introducem? (numar natural)? ";
                                cin>>x;
                                p.setGarantie(x);
                                break;
                            }
                            case 4: {p.stergereReview(); break;}
                            case 5: {

                                int x;
                                cout<<"Ce review adaugam? (Numar intre 1 si 5) ";
                                cin>>x;
                                p.adaugareReview(x); break;
                            }
                            case 6: {cout<<p<<'\n'; break;}
                            case 0: l=0; break;}

                        }break;
                    }
                case 3:{
                    while(l==1){
                        //if(system("CLS")) system("clear");
                        cout<<'\n';
                        cout<<"\n1-Citire";
                        cout<<"\n2-Numele produselor cu garantie mare";
                        cout<<"\n3-Cate articole avem?";
                        cout<<"\n4-Setare fidelitate";
                        cout<<"\n5-Afisare";
                        cout<<"\n0-Stop\n";

                        int comanda2;
                        cin>>comanda2;
                        Client c;
                        switch(comanda2)
                        {

                            case 1: {cin>>c; break;}
                            case 2: {

                                cout<<'\n';
                                int x;
                                cout<<"Cati ani garantie vrem sa introducem? ";
                                cin>>x;
                                cout<<"Numele produselor cu garantie mai mare de "<<x<<" ani sunt: ";
                                c.produseGarantie(x);
                                break;
                            }
                            case 3: {

                                cout<<"Clientul are "<<c.getNrArticole()<<" articole";
                                break;
                            }
                            case 4: {

                                int x;
                                cout<<"Este clitentul fidel? (1-da 0-nu) ";
                                cin>>x;
                                c.setFidelitate(x);
                                break;
                            }
                            case 5: {cout<<c<<'\n'; break;}
                            case 0: {l=0; break;}
                        }
                    }break;
               }
                case 4:{
                    while(l==1){
                        //if(system("CLS")) system("clear");
                        cout<<'\n';
                        cout<<"\n1-Citire";
                        cout<<"\n2-Luna cu cele mai mari cheltuieli:";
                        cout<<"\n3-Bani donati catre ONG-uri: ";
                        cout<<"\n4-Sterge cheltuielile pe ultima luna";
                        cout<<"\n5-Adauga cheltuieli";
                        cout<<"\n6-Afisare";;
                        cout<<"\n0-Stop\n";

                        int comanda2;
                        cin>>comanda2;
                        Management m;
                        switch(comanda2)
                        {

                            case 1: {cin>>m; break;}
                            case 2: {

                                m.cheltuieliMaxime();
                                break;
                            }
                            case 3: {

                                cout<<"Au fost donati catre ONG-uri "<<m.getDonatiiONG()<<" lei.";
                                break;
                            }
                            case 4: {m.stergereCheltuieliUltimaLuna(); break;}
                            case 5: {

                                int x;
                                cout<<"Ce cheltuieli adaugam? ";
                                cin>>x;
                                m.adaugareCheltuieli(x); break;
                            }
                            case 6: {cout<<m<<'\n'; break;}
                            case 0: l=0; break;}

                        }break;
                    }
                case 0:{ cout<<"Va multumesc!"; return;}
                case 5:{
                        Vanzator v;
                        Angajat* a=&v; // upcasting implicit
                        Angajat* a2=static_cast<Vanzator*> (&v);// upcasting explicit

                        Angajat* vanzator = new Angajat();
                        //Angajat* vanzator = new Vanzator();


                       // Vanzator* p1 = dynamic_cast<Vanzator*>(manager);
                        Vanzator* p1 = dynamic_cast<Vanzator*>(vanzator);

                        a->Functie();
                        a2->Functie();

                        p1->Functie();
                        //p0->Functie();
                   }
                }

        }
    }
};
int main()
{
    MeniuInteractiv meniulMeu;
    meniulMeu.meniu();

}