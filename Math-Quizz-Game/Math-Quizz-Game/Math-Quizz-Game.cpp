
#include <iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

enum enQuestionsLevel { Easy = 1, Medium = 2, Hard = 3, Mix = 4 };
enum enOperation { Add = 1, Subtraction = 2, MultiPliction = 3, Divison = 4, MixOp = 5 };
enum enPassNotPass { pass = 1, notPass = 2 };
struct stQuestionInfo
{
    short QuestionNumber = 0;
    short LeftNumber = 0;
    enOperation operatoin;
    short RightNumber = 0;
};

struct stQuizzInfo
{
    enPassNotPass Pass;
    short NumberOfQuestions = 0;
    enQuestionsLevel QuestionLevel;
    enOperation Operation;
    short RightAnswers = 0;
    short WrongAnswers = 0;
};

short ReadHowManyQuestions()
{
    short Questions = 0;
    cout << "How Many Questions you Want to answer? ";
    cin >> Questions;
    return Questions;
}

short ReadQuestionsLevel()
{
    short QuestionsLevel;
    cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix? ";
    cin >> QuestionsLevel;
    return QuestionsLevel;
}

short ReadOperation()
{
    short Operation = 0;
    cout << "Enter operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix? ";
    cin >> Operation;
    return Operation;
}

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

short getNumberBsedOnLevel(short level)
{
    if (level == enQuestionsLevel::Easy)
        return RandomNumber(1, 10);
    else if (level == enQuestionsLevel::Medium)
        return RandomNumber(11, 50);
    else if (level == enQuestionsLevel::Hard)
        return RandomNumber(50, 100);
    else
        return RandomNumber(1, 100);
}


enOperation getOperatoin(short operation)
{
    if (operation == enOperation::MixOp)
        return (enOperation)RandomNumber(1, 4);

    return (enOperation)operation;
}


char getoperationSymbol(short Operaion)
{
    char arrOpeartoinSymbol[4] = { '+', '-','*','/' };
    return arrOpeartoinSymbol[Operaion - 1];
}

void printQuestionInfo(stQuestionInfo info)
{
    cout << info.LeftNumber << endl;
    cout << info.RightNumber << "  ";
    cout <<getoperationSymbol(info.operatoin) << endl;
    cout << "------------"<<endl;
}


short correctAnswer(stQuestionInfo answer)
{
    if (answer.operatoin == enOperation::Add)
        return answer.LeftNumber + answer.RightNumber;
    else if (answer.operatoin == enOperation::Divison)
        return answer.LeftNumber / answer.RightNumber;
    else if (answer.operatoin == enOperation::MultiPliction)
        return answer.LeftNumber * answer.RightNumber;
     
    return answer.LeftNumber - answer.RightNumber;
}

void PrintCorrectAnswerAnswer(stQuestionInfo answer, short UserAnswer, short& RightAnswers)
{
    short RightAnswer = correctAnswer(answer);
    if (UserAnswer == RightAnswer)
    {
        RightAnswers++;
        system("color 2F");
        cout << "\nRight Answer :-)" << endl;
        return;
    }
    system("color 4F");
    cout << "Wrong Answer :-(" << endl;
    cout << "The Right Answer is: " << RightAnswer<<"\n\n" << endl;
}


short WrongAnswers(short TotalQuestions ,short correct)
{
    return TotalQuestions - correct;
}

enPassNotPass isPass(short NumOfQuestions, short RightAnswers)
{
    if (RightAnswers > (NumOfQuestions/2))
        return enPassNotPass::pass;

    return enPassNotPass::notPass;
    
}

stQuizzInfo FillQuizzInfo(short NumOfQuestions, short QuestionsLevel, short Operation, short RightAnswers)
{
    stQuizzInfo quizzInfo;

    quizzInfo.NumberOfQuestions = NumOfQuestions;
    quizzInfo.Operation = (enOperation)Operation;
    quizzInfo.QuestionLevel = (enQuestionsLevel)QuestionsLevel;
    quizzInfo.RightAnswers = RightAnswers;
    quizzInfo.WrongAnswers = WrongAnswers(quizzInfo.NumberOfQuestions, quizzInfo.RightAnswers);
    quizzInfo.Pass = isPass(NumOfQuestions, RightAnswers);

    return quizzInfo;
}

stQuizzInfo playMathGame()
{
    short NumOfQuestions = ReadHowManyQuestions();
    short QuestionsLevel = ReadQuestionsLevel();
    short Operation = ReadOperation();
    short UserAnswer = 0, RightAnswers = 0;
    stQuestionInfo QuestionInfo;

    for (short Question = 1; Question <= NumOfQuestions; Question++)
    {
        QuestionInfo.QuestionNumber = Question;
        QuestionInfo.LeftNumber = getNumberBsedOnLevel(QuestionsLevel);
        QuestionInfo.RightNumber = getNumberBsedOnLevel(QuestionsLevel);
        QuestionInfo.operatoin = getOperatoin(Operation);
        
        printQuestionInfo(QuestionInfo);

        cin >> UserAnswer;

        PrintCorrectAnswerAnswer(QuestionInfo, UserAnswer, RightAnswers);
    }
    return FillQuizzInfo(NumOfQuestions, QuestionsLevel, Operation, RightAnswers);
}


string getPassName(enPassNotPass pass)
{
    string arrPassNotPass[2] = { "pass","notPass" };
    return arrPassNotPass[pass - 1];
}


string getLevelName(enQuestionsLevel level)
{
    string arrQuesLevel[4] = { "Easy","Midum","Hard","Max" };
    return arrQuesLevel[level - 1];
}

string getOperationName(enOperation op)
{
    string arrOperation[5] = { "Add","Sub", "Multi","divison","Mix" };
    return arrOperation[op - 1];
}

void printFinalResults(stQuizzInfo info)
{
    cout << "\n\n----------------------"<<endl;
    if (info.Pass == enPassNotPass::pass) {
        cout << "Final Results is      :-) : " << getPassName(info.Pass) << endl;
    }
    else
        cout << "Final Results is      :-( : " << getPassName(info.Pass) << endl;
      
    cout << "\n\n----------------------" << endl;
    cout << "Number Of Questions    :" << info.NumberOfQuestions<<endl;
    cout << "Quesitons  Level       : " << getLevelName(info.QuestionLevel)<<endl;
    cout << "opType                 : " << getOperationName(info.Operation)<<endl;
    cout << "Number Of Right Answers: " << info.RightAnswers << endl;
    cout << "Number Of Wrong Answers: " << info.WrongAnswers<<endl;
}

void startGame()
{
    char PlayAgain = 'y';
    do {
        system("cls");
        system("color 07");
        stQuizzInfo quizzInfo = playMathGame();
        printFinalResults(quizzInfo);
        cout << "\n\nDo You Want To Play Again? Y/N ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    startGame();
    return 0;
}
