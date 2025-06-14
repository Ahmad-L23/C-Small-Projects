
#include <iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

enum enChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short Round = 0;
	enChoice PlayerChoice;
	enChoice ComputerChoice;
	enWinner Winner;
	string WinnerName = "";
};

struct stGameInfo
{
	short GameRounds = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};
short ReadRounds()
{
	short Rounds = 0;
	do
	{
		cout << "How Many Rounds you Want to Playe? ";
		cin >> Rounds;
		cout << endl;
	} while (Rounds<1 || Rounds>10);
	
	return Rounds;
}

enChoice ReadPlayerChoice()
{
	short PlayerChoice = 0;
	do
	{
		cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
		cin >> PlayerChoice;
	} while (PlayerChoice<1 || PlayerChoice>3);
	return (enChoice)PlayerChoice;
}

int RandomNumber(int From, int To)
{
	int RandomNum = rand() % (To - From + 1) + From;
	return RandomNum;
}

enChoice getComputerChoice()
{
	return (enChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheGaem(short PlayerWonTime, short ComputerWonTimes)
{
	if (PlayerWonTime > ComputerWonTimes)
		return enWinner::Player;
	else if (ComputerWonTimes > PlayerWonTime)
		return enWinner::Computer;

	return enWinner::Draw;
}

enWinner whoWinRound(stRoundInfo info)
{
	if (info.PlayerChoice == info.ComputerChoice)
	{
		system("color 6F");
		return enWinner::Draw;
	}

	if (info.ComputerChoice == enChoice::Paper && info.PlayerChoice == enChoice::Stone) {
		system("color 4F");
		cout << "\a";
		return enWinner::Computer;
	}
	else if (info.ComputerChoice == enChoice::Scissors && info.PlayerChoice == enChoice::Paper) {
		system("color 4F");
		cout << "\a";
		return enWinner::Computer;
	}
	else if (info.ComputerChoice == enChoice::Stone && info.PlayerChoice == enChoice::Scissors) {
		system("color 4F");
		cout << "\a";
		return enWinner::Computer;
	}

	system("color 2F");
	return enWinner::Player;
}


string GetWinnerName(enWinner winner)
{
	string arrWinnerNmae[3] = { "Player", "Computer", "Draw" };
	return arrWinnerNmae[winner - 1];
}


string getChoiceName(enChoice PlayerChoice)
{
	string arrChoiceNmae[3] = { "Stone", "Paper", "Scissors" };
	return arrChoiceNmae[PlayerChoice - 1];
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n-------------- Round ["<<RoundInfo.Round<<"] --------------" << endl;

	cout << "\nPlayer Choice     : " << getChoiceName(RoundInfo.PlayerChoice);
	cout << "\nComputer Choice   : " << getChoiceName(RoundInfo.ComputerChoice);
	cout << "\nRound Winner      : [" << RoundInfo.WinnerName<<"]"<<endl;

	cout << "---------------------------------------\n\n\n" << endl;

}


stGameInfo FillGameResults(short Rounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameInfo GameInfo;

	GameInfo.GameRounds = Rounds;
	GameInfo.PlayerWinTimes = PlayerWinTimes;
	GameInfo.ComputerWinTimes = ComputerWinTimes;
	GameInfo.DrawTimes = DrawTimes;
	GameInfo.GameWinner = WhoWonTheGaem(PlayerWinTimes, ComputerWinTimes);
	GameInfo.WinnerName = GetWinnerName(GameInfo.GameWinner);

	return GameInfo;
}

stGameInfo PlayGame(short Rounds)
{
	stRoundInfo roundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	for (short round = 1; round <= Rounds; round++)
	{
		cout << "Round [" << round << "] begins:\n" << endl;
		roundInfo.Round = round;
		roundInfo.PlayerChoice = ReadPlayerChoice();
		roundInfo.ComputerChoice = getComputerChoice();
		roundInfo.Winner = whoWinRound(roundInfo);
		roundInfo.WinnerName = GetWinnerName(roundInfo.Winner);

		if (roundInfo.Winner == enWinner::Player)
			PlayerWinTimes++;
		else if (roundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(roundInfo);
	}

	return FillGameResults(Rounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
	
}

string Tabs(short tab)
{
	string tabs = "";
	for (int i = 1; i < tab; i++)
	{
		tabs += '\t';
	}
	return tabs;
}

void GameHeader()
{

	cout << Tabs(6) << "-----------------------------------------" << endl;
	cout << Tabs(6) << "            +++Game Over+++     " << endl;
	cout << Tabs(6) << "-----------------------------------------" << endl;
}

void ShowFinalGameResults(stGameInfo gameInfo)
{
	GameHeader();

	cout << Tabs(6) << "-----------------------------------------" << endl;
	cout << Tabs(6) << "--------------Game Results---------------" << endl;
	cout << Tabs(6) << "Game Rounds        : "<<gameInfo.GameRounds << endl;
	cout << Tabs(6) << "Player Won Times   : "<<gameInfo.PlayerWinTimes << endl;
	cout << Tabs(6) << "Computer Won Times : "<<gameInfo.ComputerWinTimes << endl;
	cout << Tabs(6) << "Draw Times         : "<<gameInfo.DrawTimes << endl;
	cout << Tabs(6) << "Final Winner       : "<<gameInfo.WinnerName << endl;
}

void StartGAme()
{
	char PlayAgain = 'y';
	do {
		system("cls");
		stGameInfo GameInfo = PlayGame(ReadRounds());
		ShowFinalGameResults(GameInfo);
		cout << "\n\nDo You Want To Play Again? Y/N?";
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGAme();
}

