#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
using namespace std;

int k=7,r=0,flag=0;
COORD coord = {0, 0};

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct date
{
    int mm,dd,yy;
};

ofstream fout;
ifstream fin;

class proizvod
{
    int itemno;
    char name[25];
    date d;
public:
    void add()
    {
        cout<<"\n\n\tProizvod br.: ";
        cin>>itemno;
        cout<<"\n\n\tNaziv proizvoda: ";
        cin>>name;

        cout<<"\n\n\tDatum proizvodnje(dd-mm-gg): ";
        cin>>d.mm>>d.dd>>d.yy;
    }
    void show()
    {
        cout<<"\n\tProizvod br.: ";
        cout<<itemno;
        cout<<"\n\n\tNaziv proizvoda: ";
        cout<<name;
        cout<<"\n\n\tDatum : ";
        cout<<d.mm<<"-"<<d.dd<<"-"<<d.yy;
    }
    void report()
    {
        gotoxy(3,k);
        cout<<itemno;
        gotoxy(13,k);
        puts(name);
    }
    int retno()
    {
        return(itemno);

    }

};

class amount: public proizvod
{
    float price,qty,tax,gross,dis,netamt;
public:
    void add();
    void show();
    void report();
    void calculate();
    void pay();
    float retnetamt()
    {
        return(netamt);
    }
} amt;

void amount::add()
{
    proizvod::add();
    cout<<"\n\n\tCijena: ";
    cin>>price;
    cout<<"\n\n\tKolicina: ";
    cin>>qty;
    cout<<"\n\n\tPDV: ";
    cin>>tax;
    cout<<"\n\n\tPopust (u postotcima): ";
    cin>>dis;
    calculate();
    fout.write((char *)&amt,sizeof(amt));
    fout.close();
}
void amount::calculate()
{
    gross=price+(price*(tax/100));
    netamt=qty*(gross-(gross*(dis/100)));
}
void amount::show()
{
    fin.open("itemstore.dat",ios::binary);
    fin.read((char*)&amt,sizeof(amt));
    proizvod::show();
    cout<<"\n\n\tTezina proizvoda (u gramima): ";
    cout<<netamt;
    fin.close();
}

void amount::report()
{
    proizvod::report();
    gotoxy(23,k);
    cout<<price;
    gotoxy(33,k);
    cout<<qty;
    gotoxy(44,k);
    cout<<tax;
    gotoxy(52,k);
    cout<<dis;
    gotoxy(64,k);
    cout<<netamt;
    k=k+1;
    if(k==50)
    {
        gotoxy(25,50);
        cout<<"Pritisnuti bilo koje slovo na tastaturi!";
        getch();
        k=7;
        system("cls");
        gotoxy(30,3);
        cout<<" Detalji o proizvodu ";
        gotoxy(3,5);
        cout<<"Broj";
        gotoxy(13,5);
        cout<<"Proizvod";
        gotoxy(23,5);
        cout<<"Cijena";
        gotoxy(33,5);
        cout<<"Kolicina";
        gotoxy(44,5);
        cout<<"PDV";
        gotoxy(52,5);
        cout<<"Popust";
        gotoxy(64,5);
        cout<<"Tezina (u gramima)";
    }
}

void amount::pay()
{
    show();
    cout<<"\n\n\n\t\t*********************************************";
    cout<<"\n\t\t                 Detalji                  ";
    cout<<"\n\t\t*********************************************";
    cout<<"\n\n\t\tCijena                              :"<<price;
    cout<<"\n\n\t\tKolicina                              :"<<qty;
    cout<<"\n\t\tPDV                                     :"<<tax;
    cout<<"\n\t\tPopust (u %)                            :"<<dis;
    cout<<"\n\n\n\t\tTezina (u gramima)            :Rs."<<netamt;
    cout<<"\n\t\t*********************************************";
}

int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout<<setprecision(2);
    fstream tmp("temp.dat",ios::binary|ios::out);
menu:
    system("cls");
    gotoxy(25,2);
    cout<<"Kasa";
    gotoxy(25,3);
    cout<<"===========================\n\n";
    cout<<"\n\t\t1.Racun\n\n";
    cout<<"\t\t2.Dodaj/Izbrisi/Uredi proizvod\n\n";
    cout<<"\t\t3.Pokazi detalje o proizvodu\n\n";
    cout<<"\t\t4.Izlaz\n\n";
    cout<<"\t\tUnesite zeljenu opciju: ";
    int ch,ff;
    float gtotal;
    cin>>ch;
    switch(ch)
    {
    case 1:
ss:
        system("cls");
        gotoxy(25,2);
        cout<<"Racun ispis";
        gotoxy(25,3);
        cout<<"================\n\n";
        cout<<"\n\t\t1.Svi artikli\n\n";
        cout<<"\t\t2.Nazad na glavni meni\n\n";
        cout<<"\t\tUnesite zeljenu opciju: ";
        int cho;
        cin>>cho;
        if(cho==1)
        {
            system("cls");
            gotoxy(30,3);
            cout<<" Detalji racuna ";
            gotoxy(3,5);
            cout<<"Proizvod br.";
            gotoxy(13,5);
            cout<<"Proizvod";
            gotoxy(23,5);
            cout<<"Cijena";
            gotoxy(33,5);
            cout<<"Kolicina";
            gotoxy(44,5);
            cout<<"PDV %";
            gotoxy(52,5);
            cout<<"Popust %";
            gotoxy(64,5);
            cout<<"Kolicina (u gramima)";
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nGreska!";
                goto menu;
            }
            fin.seekg(0);
            gtotal=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    amt.report();
                    gtotal+=amt.retnetamt();
                    ff=0;
                }
                if(ff!=0) gtotal=0;
            }
            gotoxy(17,k);
            cout<<"\n\n\n\t\t\tUkupna cijena="<<gtotal;
            getch();
            fin.close();
        }
        if(cho==2)
        {
            goto menu;
        }
        goto ss;
    case 2:
db:
        system("cls");
        gotoxy(25,2);
        cout<<"Uredite racun";
        gotoxy(25,3);
        cout<<"=================\n\n";
        cout<<"\n\t\t1.Dodajte proizvod\n\n";
        cout<<"\t\t2.Uredite postojeci proizvod\n\n";
        cout<<"\t\t3.Izbrisite proizvod\n\n";
        cout<<"\t\t4.Nazad na glavni meni ";
        int apc;
        cin>>apc;
        switch(apc)
        {
        case 1:
            fout.open("itemstore.dat",ios::binary|ios::app);
            amt.add();
            cout<<"\n\t\tProizvod uspjesno preuredjen!";
            getch();
            goto db;

        case 2:
            int ino;
            flag=0;
            cout<<"\n\n\tUnesite broj proizvoda koji zelite urediti :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            fout.open("itemstore.dat",ios::binary|ios::app);
            if(!fin)
            {
                cout<<"\n\nGreska!";
                goto menu;
            }
            fin.seekg(0);
            r=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    int x=amt.proizvod::retno();
                    if(x==ino)
                    {
                        flag=1;
                        fout.seekp(r*sizeof(amt));
                        system("cls");
                        cout<<"\n\t\tTrenutni detalji su:\n";
                        amt.show();
                        cout<<"\n\n\t\tUnesi nove detalje:\n";
                        amt.add();
                        cout<<"\n\t\tUspjesno uredjeno!";
                    }
                }
                r++;
            }
            if(flag==0)
            {
                cout<<"\n\t\tNepostojeci proizvod. Pokusajte ponovo!";
                getch();
                goto db;
            }
            fin.close();
            getch();
            goto db;

        case 3:
            flag=0;
            cout<<"\n\n\tUnesite broj proizvoda kojeg zelite izmjeniti :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nGreska!";
                goto menu;
            }

            fin.seekg(0);
            while(fin.read((char*)&amt, sizeof(amt)))
            {
                int x=amt.proizvod::retno();
                if(x!=ino)
                    tmp.write((char*)&amt,sizeof(amt));
                else
                {
                    flag=1;
                }
            }
            fin.close();
            tmp.close();
            fout.open("itemstore.dat",ios::trunc|ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat",ios::binary|ios::in);
            if(!tmp)
            {
                cout<<"Greska u sistemu! Molim zatvorite i otvorite sistem i pokusajte ponovo!";
                goto db;
            }
            while(tmp.read((char*)&amt,sizeof(amt)))
                fout.write((char*)&amt,sizeof(amt));
            tmp.close();
            fout.close();
            if(flag==1)
                cout<<"\n\t\tProizvod uspjesno izbrisan!";
            else if (flag==0)
                cout<<"\n\t\tNepostojeci proizvod. Molim pokusajte ponovo!";
            getch();
            goto db;
        case 4:
            goto menu;
        default:
            cout<<"\n\n\t\tPokusajte ponovo!";
            getch();
            goto db;
        }
    case 3:
        system("cls");
        flag=0;
        int ino;
        cout<<"\n\n\t\tUnesite broj proizvoda :";
        cin>>ino;
        fin.open("itemstore.dat",ios::binary);
        if(!fin)
        {
            cout<<"\n\nFajl nije pronadjen! Fatalna greska! Program ce se sada zatvoriti!";
            goto menu;
        }
        fin.seekg(0);
        while(fin.read((char*)&amt,sizeof(amt)))
        {
            int x=amt.proizvod::retno();
            if(x==ino)
            {
                amt.pay();
                flag=1;
                break;
            }
        }
        if(flag==0)
            cout<<"\n\t\tProizvod ne postoji!";
        getch();
        fin.close();
        goto menu;
    case 4:
        system("cls");
        gotoxy(20,20);
        cout<<"Da li ste sigurni da zelite izaci? (D/N)?";
        char yn;
        cin>>yn;
        if((yn=='D')||(yn=='d'))
        {
            gotoxy(12,20);
            system("cls");
            cout<<"************************** Hvala sto ste koristili ovaj sistem! **************************************";
            getch();
            exit(0);
        }
        else if((yn=='N')||(yn=='n'))
            goto menu;
        else
        {
            goto menu;
        }
    default:
        cout<<"\n\n\t\tGreska!";
        getch();
        goto menu;
    }
    return 0;
}
