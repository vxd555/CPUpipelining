#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

#define REGSIZE 32
#define MEMSIZE 320

/*Œci¹ga do instrukcji
Rtype R1 R2 R3
ADD - dodawanie
MUL - mno¿enie
SUB - odejmowanie
ADD i MUL s¹ tylko specjalnymi przypadkami Rtype ale z dzieleniem raczej nie bêdziey mieli do czynienia

LW R4 100 R5

SW R6 100 R7

BEQ R8 R9 loop

Rliczba - jeden unsigned int oznaczaj¹cy adres rejestru zapisany w wektorze registerTab
loop - mo¿na pomin¹æ
*/

using namespace std;

enum insType
{
	Rtype = 0, //instrukcje operacji mo¿e byæ uzywany jako zape³niacz
	ADD = 1, //dodanie
	MUL = 2, //mno¿enie
	SUB = 3, //odejmowanie
	LW = 4, //zapisanie z reg -> mem
	SW = 5, //wczytanie z mem -> reg
	BEQ = 6, //skok warunkwy
	NOP = 7 //nic
};

//instrukcja sk³ada siê z nazwy (typu) oraz indeksów rejestrów. 
//niektóre mog¹ byæ nie wype³nione lub wype³nione losowo w zale¿noœci od typu instrukcji
struct instruction
{
	insType type;
	unsigned int reg1;
	unsigned int reg2;
	unsigned int reg3;
};

vector<bool> regLock; //czy dany rejestr jest zabolowany
vector<int> reg; //wartoœci wewn¹trz rejestrów
vector<int> mem; //wartoœci wewn¹trz pamiêci
vector<instruction> ins; //lista instrukcji procesora

void ReadInstructions(fstream &f) //wczytanie instrukcji z pliku
{
	
}

int main(int argc, char** argv)
{
	for(int i = 0; i < REGSIZE; ++i) //inicjalizacja rejestrów
	{
		reg.push_back(0);
		regLock.push_back(false);
	}
	for(int i = 0; i < MEMSIZE; ++i) //inicjalizacji pamiêci
	{
		mem.push_back(0);
	}
	
	//inicjalizacjia instrukcji
	fstream file;
	file.open("instruction.txt", fstream::in);
	ReadInstructions(file);
	
	
	return 0;
}
