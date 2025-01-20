#include<iostream>

using namespace std;

enum enOperationType { Add = 1, Sub, Mult, Div, MixOp };
enum enQuestionLevel { EasyLevel = 1, MedLevel, HardLevel, MixLevel };

struct stQuestion
{
	int Number1{ 0 }, Number2{ 0 }, CorrectAnswer{ 0 }, PlayerAnswer{ 0 };
	enOperationType OperationType;
	enQuestionLevel QuestionLevel;
	bool AnswerResult{ false };
};

struct stQuiz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions{ 0 }, NumberOfRightAnswers{ 0 }, NumberOfWrongAnswers{ 0 };
	enQuestionLevel QuestionLevel;
	enOperationType OpType;
	bool IsPass{ false };
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

short ReadHowManyQuestions()
{
	short NumberOfQuestions{ 0 };
	do
	{
		cout << "How Many Questions do you want to answer ? ";
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions < 1 || NumberOfQuestions>10);
	return NumberOfQuestions;
}

enQuestionLevel ReadQuestionLevel()
{
	short QuestionLevel{ 0 };
	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel>4);
	return enQuestionLevel(QuestionLevel);
}

enOperationType ReadOpType()
{
	short OpType{ 0 };
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType>5);
	return enOperationType(OpType);
}

enOperationType GetRandomOperationType()
{
	return enOperationType(RandomNumber(1, 4));
}

int SimpleCalculator(int Number1, int Number2, enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;
	if (QuestionLevel == enQuestionLevel::MixLevel)
		QuestionLevel = enQuestionLevel(RandomNumber(1, 3));
	if (OpType == enOperationType::MixOp)
		OpType = GetRandomOperationType();
	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 9);
		Question.Number2 = RandomNumber(1, 9);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	case enQuestionLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 99);
		Question.Number2 = RandomNumber(10, 99);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionLevel::HardLevel:
		Question.Number1 = RandomNumber(100, 999);
		Question.Number2 = RandomNumber(100, 999);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	default:
		Question.Number1 = 0;
		Question.Number2 = 0;
	}
	return Question;
}


void GenerateQuizQuestions(stQuiz& Quiz)
{
	for (short Question{ 0 }; Question < Quiz.NumberOfQuestions; Question++)
		Quiz.QuestionList[Question] = GenerateQuestion(Quiz.QuestionLevel, Quiz.OpType);
}

string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "*";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";

	}
}

void PrintTheQuestion(stQuiz& Quiz, short QuestionNumber)
{
	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestions << "]\n\n";
	cout << Quiz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quiz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quiz.QuestionList[QuestionNumber].OperationType) << "\n_________\n";
}

int ReadQuestionAnswer()
{
	int Answer{ 0 };
	cin >> Answer;
	return Answer;
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

void CorrectTheQuestionAnswer(stQuiz& Quiz, short QuestionNumber)
{
	if (Quiz.QuestionList[QuestionNumber].PlayerAnswer != Quiz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quiz.QuestionList[QuestionNumber].AnswerResult = false;
		Quiz.NumberOfWrongAnswers++;
		cout << "Wrong Answer :-(\n";
		cout << "The right answer is: " << Quiz.QuestionList[QuestionNumber].CorrectAnswer << endl;
	}
	else
	{
		Quiz.QuestionList[QuestionNumber].AnswerResult = true;
		Quiz.NumberOfRightAnswers++;
		cout << "Right Answer :-)\n";
	}
	cout << endl;
	SetScreenColor(Quiz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQusetionListAnswers(stQuiz& Quiz)
{
	for (short QuestionNumber{ 0 }; QuestionNumber < Quiz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quiz, QuestionNumber);
		Quiz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quiz, QuestionNumber);
	}
	Quiz.IsPass = Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers;
}

string GetFinalResultTexts(bool Pass)
{
	return Pass ? "Pass :-)" : "Fail :-(";
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
	string ArrQuestionLevel[]{ "Easy","Med","Hard","Mix" };
	return ArrQuestionLevel[QuestionLevel - 1];
}

void PrintQuizResults(stQuiz Quiz)
{
	cout << "\n______________________________\n\n";
	cout << " Final Results is " << GetFinalResultTexts(Quiz.IsPass) << "\n______________________________\n\n";
	cout << "Number of Questions: " << Quiz.NumberOfQuestions << endl;
	cout << "Questions Level    : " << GetQuestionLevelText(Quiz.QuestionLevel) << endl;
	cout << "OpType             : " << GetOpTypeSymbol(Quiz.OpType) << endl;
	cout << "Number of Right Answers: " << Quiz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers: " << Quiz.NumberOfWrongAnswers << endl;
	cout << "______________________________\n";

	SetScreenColor(Quiz.IsPass);
}

void ResetScreen()
{
	system("cls");
	system("color 03");
}

void PlayMathGame()
{
	stQuiz Quiz;
	Quiz.NumberOfQuestions = ReadHowManyQuestions();
	Quiz.QuestionLevel = ReadQuestionLevel();
	Quiz.OpType = ReadOpType();

	GenerateQuizQuestions(Quiz);
	AskAndCorrectQusetionListAnswers(Quiz);
	PrintQuizResults(Quiz);
}

void StartGame()
{
	char PlayAgain{ 'y' };
	do
	{
		ResetScreen();
		PlayMathGame();
		cout << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}