#include <iostream>
#include <ctype.h>
#include <time.h>
#include <string>
using namespace std;

char t[9][9]=	{{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' ',' '}};

void kiir()
{
cout<<"     ";
for(int a=0;a<9;a++) {cout<<a+1<<"   ";}
cout<<endl;
cout<<"   -------------------------------------"<<endl;
for(int i=0;i<9;i++)
	{

	cout<<i+1<<"  |";
	for(int j=0;j<9;j++) {cout<<" "<<t[i][j]<<" "<<"|";}
	cout<<endl;

	cout<<"   -------------------------------------"<<endl;
	}
}


int def[17][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},};
void gen()
{
//cleaning
for(int i=0;i<9;i++) for(int j=0;j<9;j++) t[i][j]=' ';
//cleaning

//random17

    bool rossz=true;
srand((unsigned) time(NULL));
for(int i=0;i<17;i++)
    {

        rossz=true;
        while(rossz==true)
            {
                //generálás

                for(int j=0;j<3;j++)
                {
                def[i][j]=(rand()%9)+1;

                }

                //feltételek vizsgálata
                rossz=false;

                //az első generált szám nem ismétlődhet
                if(i==0) rossz=false;

                //ismétlődést szűrő feltétel
                else
                {
                    for(int j=0;j<i;j++)
                    {
                    if(def[j][0]==def[i][0] && def[j][1]==def[i][1]) {rossz=true;break;}
                    }

                    //ismétlődik sorban
                    for(int j=0;j<i;j++)
                    {
                    if(def[i][0]==def[j][0] && def[i][2]==def[j][2]) {rossz=true;break;}
                    }

                    //ismétlődés oszlopban
                    for(int j=0;j<i;j++)
                    {
                    if(def[i][1]==def[j][1] && def[i][2]==def[j][2]) {rossz=true;break;}
                    }

                    //3x3 négyzetben ismétlődés

                    for(int j=0;j<i;j++)
                    {
                        //tesztelő kiiratás//cout<<i<<" "<<def[i][0]<<" "<<def[j][0]<<" | "<<def[i][1]<<" "<<def[j][1]<<" | "<<def[i][2]<<" "<<def[j][2]<<endl;
                        if((def[i][0]-1)/3==(def[j][0]-1)/3 && (def[i][1]-1)/3==(def[j][1]-1)/3 && def[i][2]==def[j][2]) {rossz=true;break;}
                    }

                }
            }
    }
//random17

//insert
for(int i=0;i<17;i++)
    {
    t[def[i][0]-1][def[i][1]-1]=def[i][2]+'0';
    }
//insert
}


int main()
{
setlocale(LC_ALL,"hun");
string b;
int s,o;
gen();
kiir();
while(cin)
{
    start:
getline(cin,b);

if(b.length()==3 && isdigit(b[0]) && b[0]!=0 && isdigit(b[2]) && b[2]!=0 && b[1]==' ')
	{
	s=b[0]-'0'; o=b[2]-'0';
	bool rossz=false;
	for(int i=0;i<17;i++)
    {
        if(def[i][0]==s && def[i][1]==o) {cout<<"Ez a cella nem szerkezthető!"<<endl;rossz=true;goto start;}
    }
    //if(rossz==true) break;
	cout<<"Írd be a számot!: ";
	getline(cin,b);
	if(isdigit(b[0]) && b.length()==1 && b[0]!='0')
		{
		t[s-1][o-1]=b[0];
		kiir();
		}
	else cout<<"Helytelen cellaérték."<<endl;
	}
else if(b=="uj") {gen(); kiir();}
else if(b=="feladom") return 0;
else if(b=="a") kiir();
else if(b=="help") cout<<"Cella kiválasztáshoz írd be a sorszámot, majd az oszlopszámot space-szel elválasztva (pl: 1 2)"<<endl;
else cout<<"Helytelen input"<<endl;
}

}
