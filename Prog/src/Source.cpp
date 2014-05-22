#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <Windows.h>
#include <direct.h>
#include <ctime>
#include <iomanip>
using namespace std;
struct point
{
	int x;
	int y;
};

void pratic();
void move(vector<vector <int>> &board, int n);
void randomize(vector<vector <int>> &board);
void printboard(vector<vector <int>>board);
vector<vector <int>> create_board(int size);
vector<vector <int>> newmap();
bool validmove(vector <vector <int>> board,int n);
bool victory(vector<vector <int>>board);
bool game(vector<vector <int>> board);
void endgame(bool win,int t);
void finalmenu(bool competition)	;
point findvalue(vector <vector <int>> board,int value);

void main	()
{
	cout << "Escolha\n1.Praticar\n2.Competitivo\n3.Sair";
	int ch;
	do{
		ch = _getch();
	} while (ch!='1' && ch!='2' && ch!='3');
	if(ch=='1')
		pratic();
	else
		;
}

void pratic()
{
	time_t start,end;
	time(&start);
	bool win=game(newmap());
	time(&end);
	endgame(win, difftime(end,start));
	finalmenu(false);
}

vector<vector <int>> create_board(int size)
{
	vector<vector <int>> board (size,vector <int> (size));
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			board[i][j] = i * size + j + 1;
	board[size-1][size-1]=0;
	return board;
}

void randomize(vector<vector <int>> &board)
{
	srand (time(NULL));
	int n,size=board.size();
	for (int i = 0; i < 40; i++)
	{
		do
		{
			n=rand() % (size*size-1) + 1;
		} while (!validmove(board,n));
		move(board,n);
	}
}

bool validmove(vector <vector <int>> board,int n)
{
	vector <int> valid;
	point zero=findvalue(board,0);
	int size=board.size();
	if(zero.x!=0)
		valid.push_back(board[zero.x - 1][zero.y]);
	if(zero.x!=size-1)
		valid.push_back(board[zero.x + 1][zero.y]);
	if(zero.y!=0)
		valid.push_back(board[zero.x][zero.y-1]);
	if(zero.y!=size-1)
		valid.push_back(board[zero.x][zero.y + 1]);
	for (int i = 0; i < valid.size(); i++)
	{
		if(n==valid[i])
			return true;
	}
	return false;
}

point findvalue(vector <vector <int>> board,int value)
{
	point a;
	for (int i = 0; i < board.size(); i++)
		for (int j = 0; j < board.size() ; j++)
			if(board[i][j]==value)
			{
				a.x=i;
				a.y=j;
				return a;
			}
}

void move(vector<vector <int>> &board, int n)
{
	point p0=findvalue(board,0),pn=findvalue(board,n);
	swap(board[p0.x][p0.y],board[pn.x][pn.y]);
}

bool game(vector<vector <int>> board)
{
	system("cls");
	string play;
	int value;
	bool valid;
	if (victory(board))
		return true;

	printboard(board);
	cout << "Proxima jogada (Q para sair): ";
	do
	{
		valid=false;
		cin >> play;
		if (cin.fail())
			cin.clear();
		else
		{
			value = atoi(play.c_str());
			if(play=="q"||play=="Q")
				return false;
			valid=validmove(board,value);
		}
		if(!valid)
			cout << "\nJogada invalida. Jogue de novo: ";
	}while (!valid);

	move(board,value);
	return game(board);
}

void printboard(vector<vector <int>>board)
{
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board.size(); j++)
		{
			cout << "\t";
			if(board[i][j]!=0)
				cout << board[i][j];
			else 
				cout << " ";
		}
		cout << "\n\n\n";
	}
}

bool victory(vector<vector <int>>board)
{
	for (int i = 0; i < board.size(); i++)
		for (int j = 0; j < board.size(); j++)
			if(board[i][j] != board.size()*i+j+1)
				return false;
	return true;
}

void finalmenu(bool competition)
{
	int ch;
	cout << "\nEscolha:\n1.Jogar modo ";
	cout << competition? "competitivo" : "de praticar";
	cout << " outra vez\n2.Voltar ao menu\n3.Sair";
	do{
		ch = _getch();
		ch = toupper( ch );
	}while (ch!='1' && ch!='2' && ch!='3');
	if(ch=='1')
	{
		if(competition)
			;
		else
			pratic();
	}
	else if(ch=='2')
		main();
}

vector<vector <int>> newmap()
{
	system("cls");
	cout << "Tamanho de tabuleiro?\n";
	int size;
	do{
		size = _getch();
		size = toupper( size );
	}while (size!='3' && size!='4' && size!='5');
	size=size-'0';
	vector<vector <int>> board=create_board(size);
	randomize(board);
	return board;
}

void compt()
{
	system("cls");
	cout << "Escolha:\n1.Mapa novo\n2.Mapa existente";
	int ch,t,mapn;
	vector<vector<int>> board;
	do{
		ch = _getch();
		ch = toupper( ch );
	} while (ch!='1' && ch!='2');

	if(ch=='1')
	{
		board = newmap();
		//guardar mapa
		//guardar numero do mapa
	}
	else
	{
		//escolher mapa
		//guardar numero do mapa
		;
	}

	time_t start,end;
	time(&start);
	bool win=game(board);
	time(&end);
	t=difftime(end,start);
	endgame(win,t);

	//se win
	//mostra recordes
	//se > 10º  guarda

	finalmenu(true);

}

void endgame(bool win,int t)
{
	if(win)
	{
		cout << "Ganhou e demorou " << t/60 << ":";
		if(t%60<10)
			cout << "0" << t%60;
		else cout << t%60;
	}
	else
	{
		cout << "Desistiu.";
	}
	cout << "\n";
}

/*
void savemap(vector<vector<int>> board)
{
abrir quantidade d mapas
ler quantos ha do tamanho size
guardar com o nome "size_nº"
}

void existingmaps(int size)
{
abrir quantidade d mapas
ler quantos ha do tamanho size
ciclo para i de 1 ate nº d mapas
imprime mapa i
}



*/