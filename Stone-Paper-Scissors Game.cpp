#include<iostream>
#include<time.h> 
#include<cstdlib>
using namespace std;

enum enGameChoice { stone = 1 , paper = 2 , scissor = 3 };
enum enWinner { Player1 = 1 , computer = 2 , Draw = 3 };

void MoodScreen(enWinner Winner)
{
	if (Winner == enWinner::Player1)
		system("color 2f");
	else if (Winner == enWinner::computer)
		system("color 4f");
	else
		system("color 6f");
}

struct stRoundInfo
{
	enGameChoice Player1;
	enGameChoice Computer;
	short NumberRound = 0;
	enWinner WinnerRound;
	string WinnerName = "";
};

struct stGameInfo
{
	short GameRound = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	string NameWinner = "";
	enWinner WinnerTheGame;
};

int ReadNumber(string Message)
{
	int Number;
	do {
		cout << Message;
		cin >> Number;
	} while (Number < 1 || Number > 10);
	return Number;
}
 
int RandomNumber( int from , int to )
{
	return rand() % (to - from + 1) + from;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1,3);
}

enGameChoice ReadPlayer1Choice()
{
	short Choice = 1;
	do
	{
		cout << "\nYour Choice : [1]:Stone [2]:Paper [3]:Scissor \n";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);
	return (enGameChoice)Choice;
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1 == RoundInfo.Computer)
		return enWinner::Draw;
	switch (RoundInfo.Player1)
	{
	case enGameChoice::stone :
		if (RoundInfo.Computer == enGameChoice::scissor)
			return enWinner::Player1;
		break;
	case enGameChoice::paper:
		if (RoundInfo.Computer == enGameChoice::stone)
			return enWinner::Player1;
		break;
	case enGameChoice::scissor:
		if (RoundInfo.Computer == enGameChoice::paper)
			return enWinner::Player1;
		break;
	}
	return enWinner::computer;
}

enWinner WhoWontTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes == ComputerWinTimes)
		return enWinner::Draw;
	else if (Player1WinTimes >= ComputerWinTimes)
		return enWinner::Player1;
	else if (Player1WinTimes <= ComputerWinTimes)
		return enWinner::computer;
}

string ChoicePlayersInRound(enGameChoice Choice)
{
	string arrChoiceGame[3] = { "stone" , "paper" , "scissor" };
	return arrChoiceGame[Choice - 1];
}

string NameWHoWonTheRound(enWinner NameWinner)
{
	string arrWinnerGame[3] = {"Player1" , "Computer" , "Draw"};
	return arrWinnerGame[NameWinner - 1];
}

void PrintRoundInfo(stRoundInfo RoundInfo)
{
	MoodScreen(RoundInfo.WinnerRound);
	cout << "\n _____________ Round[" << RoundInfo.NumberRound << "]____________________\n";
	cout << "Choice Player1 : " << ChoicePlayersInRound(RoundInfo.Player1) << endl;
	cout << "Choice Computer : " << ChoicePlayersInRound(RoundInfo.Computer) << endl;
	cout << "Winner : [" << RoundInfo.WinnerName << "]\n";
	cout << "____________________________________________________\n";
}

stGameInfo PlayGame( short HowManyRound )
{
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	for (int GameRound = 1; GameRound <= HowManyRound; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundInfo.NumberRound = GameRound;
		RoundInfo.Player1 = ReadPlayer1Choice();
		RoundInfo.Computer = GetComputerChoice();
		RoundInfo.WinnerRound = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = NameWHoWonTheRound(RoundInfo.WinnerRound);

		if (RoundInfo.WinnerRound == enWinner::Player1) {
			Player1WinTimes++;
		}
		else if (RoundInfo.WinnerRound == enWinner::computer) {
			ComputerWinTimes++;
		}
		else {
			DrawTimes++;
		}
		PrintRoundInfo(RoundInfo);
	}

	return { HowManyRound,Player1WinTimes,ComputerWinTimes,DrawTimes,NameWHoWonTheRound(WhoWontTheGame(Player1WinTimes,ComputerWinTimes)) ,WhoWontTheGame(Player1WinTimes,ComputerWinTimes) };
}

bool CheckToPlayAgin( char start )
{
	do {
		cout << "Do You want to play agin ? Y[Yes]/N[No] ";
		cin >> start;
		if (start == 'y' || start == 'Y')
			return true;
		else if (start == 'n' || start == 'N')
			return false;
		else
			cout << "Wrong Choice....Try Agin : ";
	} while (true);
}

string Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 1; i <= NumberOfTabs; i++)
		t += "\t";
	return t;
}

void PrintFinalGameResult(stGameInfo GameInfo)
{
	cout << Tabs(3) << "Player1 Win Times : " << GameInfo.Player1WinTimes << endl;
	cout << Tabs(3) << "Computer Win Times : " << GameInfo.ComputerWinTimes << endl;
	cout << Tabs(3) << "Draw Times : " << GameInfo.DrawTimes << endl;
	cout << Tabs(3) << "The Final Winner : " << GameInfo.NameWinner << endl;
}

void PrintScreenGameOver()
{
	cout << Tabs(3) << "_________________________________________________\n";
	cout << Tabs(5) << "+++Game Over+++\n";
	cout << Tabs(3) << "_________________________________________________\n";
}

void SwapTOstruct(stGameInfo &st1, stGameInfo &st2)
{
	stGameInfo temp = st1;
	st1 = st2;
	st2 = temp;
}

void StartGame()
{
	stGameInfo OutWHile;
	char Start = 'Y';
	do {
		system("cls");
		system("color 0f");
	 int RoundGame = ReadNumber("Choice Number from 1 To 10 : ");
	 stGameInfo GameStart = PlayGame(RoundGame);
	 SwapTOstruct(OutWHile, GameStart);
	} while (CheckToPlayAgin(Start));
	PrintScreenGameOver();
	PrintFinalGameResult(OutWHile);
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}