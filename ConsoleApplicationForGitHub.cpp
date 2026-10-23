#include <iostream>
using namespace std;
enum enOperatorType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };
enum enQuestionLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, MixLevels = 4 };
struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperatorType OpType;
	enQuestionLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};
struct stQuizz
{
	stQuestion QuestionList[100];
	int NumberOfQuestions = 0;
	enQuestionLevel QuestionLevel;
	enOperatorType OpType;
	int NumberOfRightAnswers = 0;
	int NumberOfWrongAnswers = 0;
	bool isPass = false;
};
int RandomNumber(int From, int To)
{
	int Number = rand() % (To - From + 1) + From;
	return Number;
}
int SimpleCalculater(int Number1, int Number2, enOperatorType OpType)
{
	switch (OpType)
	{
	case enOperatorType::Add:
		return Number1 + Number2;
	case enOperatorType::Sub:
		return Number1 - Number2;
	case enOperatorType::Mult:
		return Number1 * Number2;
	case enOperatorType::Div:
		return Number1 / Number2;
	default: return Number1 + Number2;
	}
}
stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperatorType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionLevel::MixLevels)
	{
		QuestionLevel = enQuestionLevel(RandomNumber(1, 3));
	}
	if (OpType == enOperatorType::MixOp)
	{
		OpType = enOperatorType(RandomNumber(1, 4));
	}

	Question.OpType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OpType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OpType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OpType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
	return Question;

}
void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short QuestionNumber = 0;QuestionNumber < Quizz.NumberOfQuestions;QuestionNumber++)
	{
		Quizz.QuestionList[QuestionNumber] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
	}
}
int ReadNumberOfQuestions()
{
	int NumberOfQuestions = 0;
	do
	{
		cout << "Please enter How many rounds you want to play [1-10] ? ";
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions < 1 || NumberOfQuestions>10);
	return NumberOfQuestions;

}
enQuestionLevel ReadQuestionLevel()
{
	int QuestionLevel = 0;
	do
	{
		cout << "Enter Question Level [1] Easy [2] Med [3] Hard [4] Mix ? ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel>4);
	return enQuestionLevel(QuestionLevel);
}
enOperatorType ReadOpetaterType()
{
	int OperatorType = 0;
	do
	{
		cout << "Please enter operator type [1] Add [2] Sub [3] Mult [4] Div [5] Mix ? ";
		cin >> OperatorType;
	} while (OperatorType < 1 || OperatorType>5);
	return enOperatorType(OperatorType);
}
string PrintSampleType(enOperatorType OpType)
{
	switch (OpType)
	{
	case enOperatorType::Add:
		return "+";
	case enOperatorType::Sub:
		return "-";
	case enOperatorType::Mult:
		return"*";
	case enOperatorType::Div:
		return "/";
	default: return "Mix";
	}

}
void PrintQuestion(stQuizz Quizz, int QuestionNumber)
{
	cout << "\n\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << "\n";
	cout << Quizz.QuestionList[QuestionNumber].Number2 << "  ";
	cout << PrintSampleType(Quizz.QuestionList[QuestionNumber].OpType);
	cout << "\n_____________\n";
}
int ReadPlayerAnswer()
{
	int Number = 0;
	cin >> Number;
	return Number;
}
void SetScreenColor(bool AnswerResult)
{
	if (AnswerResult)
		system("color 2f");
	else system("color 4f");
}
void PrintQuesionResult(stQuizz& Quizz, int QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].CorrectAnswer != Quizz.QuestionList[QuestionNumber].PlayerAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer :-( \n";
		cout << "The right answer is : ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer << "\n\n";
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-) \n";
	}
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}
void AskAndCorrectQuestionList(stQuizz& Quizz)
{
	for (short QuestionNumber = 0;QuestionNumber < Quizz.NumberOfQuestions;QuestionNumber++)
	{
		PrintQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();
		PrintQuesionResult(Quizz, QuestionNumber);
	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}
string PrintFinalResultText(bool isPass)
{
	if (isPass)
		return "Pass";
	else return "Fail";
}
string PrintQuesionLevelText(enQuestionLevel QuestionLevel)
{
	string ArrQuestionLevel[4] = { "Easy","Med","Hard","Mix" };
	return ArrQuestionLevel[QuestionLevel - 1];
}
void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n\n_____________________________________________\n";
	cout << "Your Result is " << PrintFinalResultText(Quizz.isPass) << endl;
	cout << "\n_________________________________________\n";
	cout << "Number Of Questions : " << Quizz.NumberOfQuestions << endl;
	cout << "Question Level      : " << PrintQuesionLevelText(Quizz.QuestionLevel) << endl;
	cout << "Operator Type       : " << PrintSampleType(Quizz.OpType) << endl;
	cout << "Number Of Right Questions : " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Questions : " << Quizz.NumberOfWrongAnswers << endl;
	cout << "_____________________________________________\n";

}
void PlayGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadNumberOfQuestions();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOpetaterType();

	GenerateQuizzQuestions(Quizz);

	AskAndCorrectQuestionList(Quizz);
	PrintQuizzResults(Quizz);
}
void ResetScreen()
{
	system("cls");
	system("color 0f");
}
void StartGame()
{
	char PlayMore = 'Y';
	do
	{
		ResetScreen();
		PlayGame();

		cout << "Do you want to play again [Y/N] ? ";
		cin >> PlayMore;
	} while (PlayMore == 'Y' || PlayMore == 'y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();





	return 0;
}