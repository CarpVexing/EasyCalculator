/*作者：李云帆 学号：2018117225 日期：2020.12.25*/
//这段代码是不完整代码，无法运行
//完整代码会在几天后上传
//主干结构在此，仅供参考

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <typeinfo>

using namespace std;

typedef struct
{
    string terminator;
    string type;
    string value;
} token;

typedef struct
{
    string terminator;
    string type;
    string value;
    int father;
    int intval;
    float floval;
    bool booval;
    vector<int> son;
} node;

typedef struct
{
    vector<string> type;
    vector<int> number;
} state;

/*循环接受输入的字符串ui*/
void FrontUI();

/*综合词法分析函数*/
vector<token> LexicalAnalysis(string);

/*综合语法分析函数*/
vector<node> GrammaticalAnalysis(vector<token>, vector<node> &, vector<bool>);

/*综合语义分析函数*/
void SemanticAnalysis();
//由于采用了SLR分析器，分析一遍就能够得出结果，这里不用写了

double my_atof(string s)
{
    //assert(s.size()!=NULL);
    int i = 0;
    double dou_num = 0;
    double t = 10;
    bool fh_ = false;
    if (s[i] == '-')
    {
        fh_ = true;
        i++;
    }
    while (s[i] != '\0')
    {
        if (s[i] == '.')
        {
            i++;
            break;
        }
        dou_num = dou_num * 10 + s[i] - '0';
        i++;
    }
    while (s[i] != '\0')
    {
        dou_num = dou_num + (s[i] - '0') / t;
        t *= 10;
        i++;
    }
    if (fh_)
        return -1.0 * dou_num;
    else
        return dou_num;
}

int FindNumFromTableLine(string arr)
{
    int index;
    if (arr == "state")
        index = 0;
    else if (arr == "$")
        index = 1;
    else if (arr == "id")
        index = 2;
    else if (arr == "+")
        index = 3;
    else if (arr == "-")
        index = 4;
    else if (arr == "!")
        index = 5;
    else if (arr == "(")
        index = 6;
    else if (arr == "true")
        index = 7;
    else if (arr == "false")
        index = 8;
    else if (arr == "integer")
        index = 9;
    else if (arr == "floater")
        index = 10;
    else if (arr == ")")
        index = 11;
    else if (arr == "*")
        index = 12;
    else if (arr == "/")
        index = 13;
    else if (arr == "%")
        index = 14;
    else if (arr == "<")
        index = 15;
    else if (arr == ">")
        index = 16;
    else if (arr == "=")
        index = 17;
    else if (arr == "<=")
        index = 18;
    else if (arr == ">=")
        index = 19;
    else if (arr == "==")
        index = 20;
    else if (arr == "!=")
        index = 21;
    else if (arr == "||")
        index = 22;
    else if (arr == "&&")
        index = 23;
    else if (arr == "A")
        index = 24;
    else if (arr == "B")
        index = 25;
    else if (arr == "C")
        index = 26;
    else if (arr == "D")
        index = 27;
    else if (arr == "F")
        index = 28;
    else if (arr == "G")
        index = 29;
    else if (arr == "H")
        index = 30;
    else if (arr == "I")
        index = 31;
    else if (arr == "J")
        index = 32;
    else
        index = -1;
    return index;
}

void PrintGrammaticalTableLine(vector<int> state, vector<node> symbol, vector<token> input, int insdx, int action)
{
    string temp = "";
    cout << "|*|";
    //state
    for (auto i : state)
        temp = temp + to_string(i) + " ";
    cout << left << setw(30) << temp;
    temp = "";
    //symbol
    for (auto i : symbol)
        temp = temp + i.terminator + " ";
    cout << left << setw(30) << temp;
    temp = "";
    //input
    for (int i = insdx; i < input.size(); i++)
        temp = temp + input[i].terminator + " ";
    cout << left << setw(30) << temp;
    temp = "";
    //action
    if (action == -1)
    {
        cout << left << setw(30) << "Shift";
    }
    else
    {
        switch (action)
        {
        case 1:
            cout << left << setw(30) << "Reduce:Z->A$";
            break;
        case 2:
            cout << left << setw(30) << "A->id=B";
            break;
        case 3:
            cout << left << setw(30) << "A->B";
            break;
        case 4:
            cout << left << setw(30) << "B->B||C";
            break;
        case 5:
            cout << left << setw(30) << "B->C";
            break;
        case 6:
            cout << left << setw(30) << "C->C&&D";
            break;
        case 7:
            cout << left << setw(30) << "C->D";
            break;
        case 8:
            cout << left << setw(30) << "D->D==F";
            break;
        case 9:
            cout << left << setw(30) << "D->D!=F";
            break;
        case 10:
            cout << left << setw(30) << "D->F";
            break;
        case 11:
            cout << left << setw(30) << "F->F<G";
            break;
        case 12:
            cout << left << setw(30) << "F->F<=G";
            break;
        case 13:
            cout << left << setw(30) << "F->F>G";
            break;
        case 14:
            cout << left << setw(30) << "F->F>=G";
            break;
        case 15:
            cout << left << setw(30) << "F->G";
            break;
        case 16:
            cout << left << setw(30) << "G->G+H";
            break;
        case 17:
            cout << left << setw(30) << "G->G-H";
            break;
        case 18:
            cout << left << setw(30) << "G->H";
            break;
        case 19:
            cout << left << setw(30) << "H->H*I";
            break;
        case 20:
            cout << left << setw(30) << "H->H/I";
            break;
        case 21:
            cout << left << setw(30) << "H->H%I";
            break;
        case 22:
            cout << left << setw(30) << "I->+J";
            break;
        case 23:
            cout << left << setw(30) << "I->-J";
            break;
        case 24:
            cout << left << setw(30) << "I->!J";
            break;
        case 25:
            cout << left << setw(30) << "I->J";
            break;
        case 26:
            cout << left << setw(30) << "J->(B)";
            break;
        case 27:
            cout << left << setw(30) << "J->id";
            break;
        case 28:
            cout << left << setw(30) << "J->true";
            break;
        case 29:
            cout << left << setw(30) << "J->false";
            break;
        case 30:
            cout << left << setw(30) << "J->integer";
            break;
        case 31:
            cout << left << setw(30) << "J->floater";
            break;
        case 32:
            cout << left << setw(30) << "H->I";
            break;
        case -2:
            cout << left << setw(30) << "ACCEPT";
            break;
        case -3:
            cout << left << setw(30) << "ERROE!CANNOT LEX HERE!";
            break;
        case -4:
            cout << left << setw(30) << "Program ERROE! No Sush operationType!";
            break;
        default:
            break;
        }
    }
    cout << "|*|" << endl;
}

vector<node> GrammaticalAnalysis(vector<token> lexicalSequence, vector<node> &symbolTable, vector<bool> operation)
{
    vector<node> grammarTree;
    /**读入状态转换图文件**/
    vector<state> stateTable;
    string tempLine, tempArr;
    ifstream fp("stateTable.txt");
    while (getline(fp, tempLine))
    {
        state oneState;
        istringstream LineStream(tempLine);
        LineStream >> tempArr;
        oneState.type.push_back("state");
        stringstream stream;
        stream << tempArr;
        int tempInt;
        stream >> tempInt;
        oneState.number.push_back(tempInt);
        while (LineStream >> tempArr)
        {
            //cout << "#Debug:tempArr: " << tempArr << endl;
            ...
        }
        stateTable.push_back(oneState);
        /*测试状态转换表内容*/
        /*
        cout << "#Debug:oneState.type: ";
        for (auto i : oneState.type)cout << i << " ";cout << endl;
        cout << "#Debug:oneState.number: ";
        for (auto i : oneState.number)cout << i << " ";cout << endl;
        */
    }
    fp.close();
    /**状态转换图每行内容**/
    //0       1     2   3   4   5   6       7       8       9       10      11
    //state   $     id	+	-	!	(	    true 	false 	integer	floater	)
    //12 13 14  15  16  17  18  19   20 21  22  23  24  25  26  27  28  29  30  31  32
    //*	/	%	<	>	=	<=	>=	 ==	!=	||	&&	A	B	C	D	F	G	H	I	J
    if (operation[0])
    {
        cout << "===============================================================";
        cout << "===============================================================" << endl;
        cout << ">Grammatical Analysis Process Table                            ";
        cout << "                                                            |*|" << endl;
        cout << "---------------------------------------------------------------";
        cout << "------------------------------------------------------------|*|" << endl;
        cout << "|*|";
        cout << left << setw(30) << "State";
        cout << left << setw(30) << "Symbol";
        cout << left << setw(30) << "Input";
        cout << left << setw(30) << "Action";
        cout << "|*|" << endl;
    }
    /**遍历词法分析结果**/
    vector<int> state;
    state.push_back(0);
    int iInput = 0;
    string operationType;
    while (true)
    {
        //cout << "#Debug:lexicalSequence[i].type:" << lexicalSequence[i].type << endl;
        //查找：当前状态下，xx最新一项之类型在表中对应的操作类型
        //cout << "#Debug:state.back():"<<state.back();
        if (state.back() < 0)
            break;
        operationType = stateTable[state.back()].type[FindNumFromTableLine(lexicalSequence[iInput].type)];
        //cout << "#Debug:operationType: ";
        if (operationType == "s")
        {
            ...
        }
        else if (operationType == "r")
        {
            ...
            if (operation[0] && state.back() >= 0)
                PrintGrammaticalTableLine(state, grammarTree, lexicalSequence, iInput, statute);
        }
        else if (operationType == "accept")
        {
            //cout << "#Debug:accept" << endl;
            ...
        }
        else if (operationType == "n")
        {
            ...
            break;
        }
        else
        {
            ...
            break;
        }
    }
    if (operation[0])
    {
        cout << "===============================================================";
        cout << "===============================================================" << endl;
    }
    if (grammarTree.size() && state.back() >= 0)
        if (grammarTree.back().type == "bool" && grammarTree.back().floval == 1)
            cout << "Final value:"
                 << " true";
        else if (grammarTree.back().type == "bool" && grammarTree.back().floval == 0)
            cout << "Final value:"
                 << " false";
        else
            cout << "Final value:" << grammarTree.back().floval;
    else
    {
        //cout << "#Debug:state.back():" << state.back();
        cout << " ERROR! " << endl;
        //cout << "The lsat state:" << state.back() << endl;
        return grammarTree;
    }
    if (operation[1])
        cout << "  Final type:" << grammarTree.back().type << endl;
    else
        cout << endl;
    return grammarTree;
}

/**判断是否为大写字母**/
bool IsUpLetter(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return true;
    return false;
}
/**判断是否为小写字母**/
bool IsLowLetter(char ch)
{
    if (ch >= 'a' && ch <= 'z')
        return true;
    return false;
}
/**判断是否为数字**/
bool IsDigit(char ch)
{
    if (ch >= '0' && ch <= '9')
        return true;
    return false;
}

vector<token> LexicalAnalysis(string inputString)
{
    vector<token> tokenList;
    vector<string> inputList;

    istringstream inputStream(inputString);
    string tempString;

    /*去除空格，实际上不需要这么复杂的操作，这里为了以后增加内容留下余地*/
    while (inputStream >> tempString)
    {
        inputList.push_back(tempString);
        //cout << "#Debug:inputList.push_back：" << tempString << endl;
    }
    inputString = "";
    for (auto i : inputList)
    {
        inputString += i;
    }
    inputString += "$";
    //cout << "#Debug:New inputString:" << inputString << endl;

    /*词法分析*/
    string arr; //寻找到了的合法组成部分
    for (int i = 0; i < inputString.length(); i++)
    {
        arr = "";
        if (IsDigit(inputString[i]))
        {
            ...
        }
        /*识别下面的所有东西*/
        //{"true" , "false" , "<=",">=","==","!=","||","&&"}
        //{'(', ')','+', '-', '*', '/', '%', '>', '<', '=', '!'}
        else if (inputString[i] == '(' || inputString[i] == ')')
        {
            ...
        }
        else if (i + 1 < inputString.length() &&
                 (...)
        {
            ...
        }
        else if (...)
        {
            ...
        }
        ...
    }
    return tokenList;
}

bool CheakLexicalSequence(vector<token> lexicalSequence, vector<bool> operation)
{
    int flag = 0;
    if (operation[0])
    {
        cout << "===================================================" << endl;
        cout << ">lexical Sequence Table                         |*|" << endl;
        cout << "------------------------------------------------|*|" << endl;
        cout << "|*|";
        cout << left << setw(15) << "terminator";
        cout << left << setw(15) << "type";
        cout << left << setw(15) << "value";
        cout << "|*|" << endl;
    }
    for (auto i : lexicalSequence)
    {
        if (operation[0])
        {
            cout << "|*|";
            cout << left << setw(15) << i.terminator;
            cout << left << setw(15) << i.type;
            cout << left << setw(15) << i.value;
            cout << "|*|" << endl;
        }
        if (i.type == "error")
            flag = 1;
    }
    if (operation[0])
    {
        cout << "===================================================" << endl;
    }
    if (flag)
        return true;
    else
        return false;
}

void FrontUI()
{
    cout << "You can use \"$help\" to view how to configure your output format" << endl;
    cout << "Enter your expression.(enter ## to quit.)" << endl;
    string temp;
    /*建立全局符号表，存储变量*/
    vector<node> symbolTable;
    vector<bool> operation;
    operation.push_back(false); //induction
    operation.push_back(false); //value
    operation.push_back(true);  //type
    //operation.push_back(true); //induction
    //operation.push_back(true); //value/type
    //operation.push_back(false); //mode//true为严格模式，false为宽容模式//严格模式禁止发部分类型转换
    string tempLine;
    while (true)
    {
        cout << ">>>";
        getline(cin, temp); //读入包含空格的一行内容
        if (temp == "##")
            break;
        else if (temp == "$default") //输出时只显示默认内容
        {
            operation[0] = false; //induction
            operation[1] = false; //value/type
            operation[2] = true;  //mode
            continue;
        }
        else if (temp == "$induction") //输出时推导过程
        {
            operation[0] = !operation[0];
            continue;
        }
        else if (temp == "$value") //输出时不显示类型
        {
            operation[1] = false;
            continue;
        }
        else if (temp == "$type") //输出时显示类型
        {
            operation[1] = true;
            continue;
        }
        else if (temp == "$mode") //swich mode
        {
            operation[2] = !operation[2];
            continue;
        }
        else if (temp == "$symbols") //打开符号表
        {
            cout << "===================================================" << endl;
            cout << ">Symbols Table                                  |*|" << endl;
            cout << "------------------------------------------------|*|" << endl;
            cout << "|*|";
            cout << left << setw(15) << "terminator";
            cout << left << setw(15) << "type";
            cout << left << setw(15) << "value";
            cout << "|*|" << endl;
            for (auto i : symbolTable)
            {
                cout << "|*|";
                cout << left << setw(15) << i.terminator;
                cout << left << setw(15) << i.type;
                cout << left << setw(15) << noshowpoint << i.floval;
                cout << "|*|" << endl;
            }
            cout << "===================================================" << endl;
            continue;
        }
        else if (temp == "$help") //打开帮助
        {
            //cout << "HELP:......" << endl;
            ifstream fp("readMe.txt");
            while (getline(fp, tempLine))
            {
                cout << tempLine << endl;
            }
            continue;
        }
        //cout << "#Debug:Input：" << temp << endl;
        /*进行综合词法分析*/
        vector<token> lexicalSequence;
        lexicalSequence = LexicalAnalysis(temp);
        if (CheakLexicalSequence(lexicalSequence, operation)) //是否存在词法错误
        {
            cout << "Lexical Error!" << endl;
            continue;
        }

        /*进行综合语法\语义分析*/
        vector<node> grammarTree;
        grammarTree = GrammaticalAnalysis(lexicalSequence, symbolTable, operation);
    }
}

int main()
{
    FrontUI();

    return 0;
}
