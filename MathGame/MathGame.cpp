#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

enum enQuestionLevel
{
	easy = 1,
	med = 2,
	hard = 3,
	mix = 4
};

enum enOperationType
{
	add = '+',
	sub = '-',
	mul = '*',
	divid = '/',
	mixt = 'm'
};

enum enWinOrLose
{
	win,
	lose
};

struct stGame
{
	short how_many_questions;

	enQuestionLevel question_level;
	enQuestionLevel first_question_level;

	enOperationType operation_type;
	enOperationType first_operation_type;

	int number1;
	int number2;

	int user_result;
	int computer_result;

	int how_many_correct = 0;
};

bool IsUnsignedAndInt(int n)
{
	if (n <= 0)
	{
		cout << "Wrong number! Please enter a positive value:\n";
		return false;
	}
	return true;
}

int ReadUnsignedInt(string message)
{
	unsigned int n;

	cout << message << endl;
	
	do
	{
		cin >> n;
	} while (!IsUnsignedAndInt(n));

	return n;
}

short GetHowManyQuestions()
{
	return ReadUnsignedInt("How many questions do you want to answer?");
}

bool IsBetweenFromAndTo(int n, int from, int to)
{
	bool true_case = ((n >= from) && (n <= to));
	if (!true_case)
	{
		cout << "Wrong number! Please enter a number between " << from << " and " << to << ":\n";
		return false;
	}

	return true;
}

int ReadIntBetweenFromAndTo(string message, int from, int to)
{
	int n;

	if (!(message.length() == 1))
		cout << message << endl;

	do
	{
		cin >> n;
	} while (!IsBetweenFromAndTo(n, from, to));

	return n;
}

enQuestionLevel GetQuestionLevel()
{
	cout << "Please enter question (s) level: ["
		<< enQuestionLevel::easy << "] Easy, [" <<
		enQuestionLevel::med << "], Medium, [" <<
		enQuestionLevel::hard << "], Hard, and [" <<
		enQuestionLevel::mix << "] Mix.\n";

	return (enQuestionLevel)ReadIntBetweenFromAndTo(" ", 1, 4);
}

bool CharIsIn(int c, char list[100], int len)
{
	for (int i = 0; i < len; i++)
	{
		if (c == list[i])
			return true;
	}

	cout << "Wrong input, please enter a valid operation:\n";

	return false;
}

char ReadCharInList(string message, char list[100], int len)
{
	char c;

	if (!(message.length() == 1))
		cout << message << endl;

	do
	{
		cin >> c;
	} while (!CharIsIn(c, list, len));

	return c;
}

enOperationType GetOperationType()
{
	cout << "Please enter question (s) level: [" <<
		(char)enOperationType::add << "] Addition, [" <<
		(char)enOperationType::sub << "], Substraction, [" <<
		(char)enOperationType::mul << "], Multiplication, and [" <<
		(char)enOperationType::divid << "], Division, and [" <<
		(char)enOperationType::mixt << "] Mix.\n";

	char list[5] = {
		(char)enOperationType::add,
		(char)enOperationType::sub,
		(char)enOperationType::mul,
		(char)enOperationType::divid,
		(char)enOperationType::mixt
	};

	return (enOperationType)ReadCharInList(" ", list, sizeof(1, list));
}

int GenerateRandomIntFromTo(int from, int to)
{
	return rand() % (to - from + 1) + from;
}

void GenerateNumbers(stGame& st_game)
{
	switch (st_game.question_level)
	{
	case enQuestionLevel::easy:
		st_game.number1 = GenerateRandomIntFromTo(1, 10);
		st_game.number2 = GenerateRandomIntFromTo(1, 10);
		break;
	case enQuestionLevel::med:
		st_game.number1 = GenerateRandomIntFromTo(10, 50);
		st_game.number2 = GenerateRandomIntFromTo(10, 50);
		break;
	default:
		st_game.number1 = GenerateRandomIntFromTo(50, 100);
		st_game.number2 = GenerateRandomIntFromTo(50, 100);
		break;
	}
}

void GenerateQuestion(int question_number, stGame& st_game)
{
	GenerateNumbers(st_game);

	cout << "\nQuestion [" << question_number << "/" << st_game.how_many_questions << "]\n\n";
	cout << st_game.number1 << endl;
	cout << st_game.number2 << "\t";
	cout << (char)st_game.operation_type << endl;
	cout << "-------------------\n";
}

enOperationType GenerateRandomOperationType()
{
	int list[4] = { '+', '-', '*', '/' };
	int operation_type = (int)list[GenerateRandomIntFromTo(0, 3)];
	return (enOperationType)operation_type;
}

enQuestionLevel GenerateRandomQuestionLevel()
{
	return (enQuestionLevel)GenerateRandomIntFromTo(0, 3);
}

int GetUserResult()
{
	int user_result;

	cin >> user_result;

	return user_result;
}

int GetComputerResult(stGame st_game)
{
	switch (st_game.operation_type)
	{
	case enOperationType::add:
		return st_game.number1 + st_game.number2;
	case enOperationType::sub:
		return st_game.number1 - st_game.number2;
	case enOperationType::mul:
		return st_game.number1 * st_game.number2;
	default:
		return st_game.number1 / st_game.number2;
	}
}

void QuestionReport(stGame& st_game)
{
	if (st_game.user_result == st_game.computer_result)
	{
		system("color 2F"); //green screen
		cout << "\nCorrect answer :)\n";
		st_game.how_many_correct++;
	}
	else
	{
		system("color 4F"); //red screen
		cout << "\nWrong answer :(\n";
		cout << "Ther right answer is : " << st_game.computer_result << endl;
	}
}

enWinOrLose WinOrLose(stGame st_game)
{
	return (enWinOrLose)(st_game.how_many_correct < st_game.how_many_questions - st_game.how_many_correct);
}

void ShowGameSummary(stGame st_game, enWinOrLose en_win_or_lose)
{
	string questions_level_list[4] = { "Easy", "Medium", "Hard", "Mix" };
	string status_message;

	switch (en_win_or_lose)
	{
	case enWinOrLose::win:
		system("color 2F");
		status_message = "Win :)";
		break;
	default:
		system("color 4F");
		status_message = "Lose :(";
		break;
	}

	cout << "\n-------------------------------------------\n";
	cout << "		Final Result is " << status_message << endl;
	cout << "-------------------------------------------\n";
	cout << "Number of questions : " << st_game.how_many_questions << endl;
	cout << "Questions level : " << questions_level_list[st_game.first_question_level - 1] << endl;
	if (st_game.first_operation_type == enOperationType::mixt)
		cout << "Operation type : Mix\n";
	else
		cout << "Operation type : " << (char)st_game.operation_type << endl;
	cout << "Number of right answers : " << st_game.how_many_correct << endl;
	cout << "Number of incorrect answers : " << st_game.how_many_questions - st_game.how_many_correct <<
		endl;
	cout << "-------------------------------------------\n";
}

bool PlayAgain()
{
	char play_again;

	cout << "\nDo you want to play again? Y/N\n";
	cin >> play_again;

	system("color 0F");

	//Reset screen
	if (char(play_again) == 'Y' || char(play_again) == 'y')
	{
		system("cls");
		return true;
	}

	return false;
}

int main()
{
	srand((unsigned)time(NULL));

	do
	{
		stGame st_game;

		st_game.how_many_questions = GetHowManyQuestions();
		st_game.question_level = GetQuestionLevel();
		st_game.operation_type = GetOperationType();

		// In case if we chosen mixt we can change operation type every loop
		st_game.first_operation_type = st_game.operation_type;
		st_game.first_question_level = st_game.question_level;

		for (int i = 1; i <= st_game.how_many_questions; i++)
		{
			// If we chosen mixt
			if (st_game.first_operation_type == enOperationType::mixt)
				st_game.operation_type = GenerateRandomOperationType();
			if (st_game.first_question_level == enQuestionLevel::mix)
				st_game.question_level = GenerateRandomQuestionLevel();

			GenerateQuestion(i, st_game);
			st_game.user_result = GetUserResult();
			st_game.computer_result = GetComputerResult(st_game);
			QuestionReport(st_game);
		}

		enWinOrLose en_win_or_lose = WinOrLose(st_game);
		ShowGameSummary(st_game, en_win_or_lose);
	} while (PlayAgain());

	return 0;
}