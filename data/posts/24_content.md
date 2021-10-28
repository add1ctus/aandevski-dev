*За почеток, да се извинам за долгата неактивност на блогов. Покрај колоквиумската недела и испитната сесија немав време да решавам било какви натпревари, а не пак да пишувам за нив. Од денеска започнувам со подготвување за локалните ACM квалификации, така да очекувајте зголемен број на постови.*

Еден од последните натпревари на кој учествував е 9-тото финале на CodeFu. Бидејќи натпреварот беше во исто време со испитната сесија, не успеав да се подготвам за него. Завршив 6-то место со 800 поени, губејќи 200 поени заради многу глупа грешка. Резултатите можете да ги отворите [тука](http://codefu.mk/codefu2015-final-round.html?subpage=results). А сега, на задачите.

![Атмосферата за време на натпреварот. Credits: codefu.mk](http://codefu.mk/files/codefu2015/a5.jpg)

## 100 - ChessPieces
[Линк до задачата](http://codefu.mk/codefu2015-final-round.html?subpage=problem&problemid=2205)

Доста проста задача, која само бара да имплементирате тоа што е напишано. Ова може да се изведе на 2 начина, со барање на минимумот при делење на бројот на секоја фигура со бројот на фигури што одат во еден сет, или пак brute force со `while` циклус. Бидејќи има највеќе 100 фигури, тоа се во најлош случај 12 итерации, така да јас се одлучив за `while` варијантата за време на натпреварот.

Се додека имаме доволно фигури да направиме еден сет (8 пешаци, 2 коњи, 2 ловци, 2 топа, 1 крал, 1 кралица, од двете бои), го зголемуваме бројачот на сетови за 1 и ги одземаме тие фигури. Го враќаме резултатот кога еден од условите не е исполнет (фали една фигура од некој тип за сет). Исто така треба да го собереме и бројот на фигури кои не се искористени, што го правиме со `for` циклус.

Бидејќи одговорот треба да е `string`, користиме и `getString` функција која број ќе претвори во стринг (можете да ја најдете во претходниот CodeFu пост).

```
string howMany(vector<int> pieces)
    {
        int completeSets=0;
        while(pieces[0]>=8
            && pieces[1]>=2
            && pieces[2]>=2
            && pieces[3]>=2
            && pieces[4]>=1
            && pieces[5]>=1
            && pieces[6]>=8
            && pieces[7]>=2
           && pieces[8]>=2
            && pieces[9]>=2
            && pieces[10]>=1
            && pieces[11]>=1)
        {
            pieces[0]-=8;
            pieces[1]-=2;
            pieces[2]-=2;
            pieces[3]-=2;
            pieces[4]-=1;
            pieces[5]-=1;
            pieces[6]-=8;
            pieces[7]-=2;
            pieces[8]-=2;
            pieces[9]-=2;
            pieces[10]-=1;
            pieces[11]-=1;
            completeSets++;
        }

        int sum=0;
        for(int i=0;i<12;i++)
            sum+=pieces[i];

        string result;
        result+=getString(completeSets);
        result+=',';
        result+=getString(sum);

      return result;
  }
```

## 200 - Calculator

[Линк до задачата](http://codefu.mk/codefu2015-final-round.html?subpage=problem&problemid=2206)

Доста интересна задача која само бара внимателно кодирање, а не познавања од некои стандардни алгоритми. Задачата е многу полесна доколку ја поделете на повеќе мали функции наместо еден огромен код. Јас ги користев следниве променливи:

 * `long long screen` - бројот кој е прикажан на екранот
 * `long long memory` - бројот запишан во меморија
 * `long long lastDigit` - ова се користи за вршење на операции и го памти првиот број внесен (пред да се внесе некоја операциа и да почнете да го внесувате вториот број)
 * `char lastOperation` - ја памти последната внесена операција (собирање / одземање / множење / делење)
 * `bool clearOnInput` - доколку ова е true, тогаш треба да се внесе нов број (доколку се внесе некој број, бришеме се што има на екранот)

Потоа, потребни ни се следниве функции:
 * `void enterDigit(char c)` - Доколку `clearOnInput` е `true`, брише се од екранот и ја внесува цифрата `c`, а во спротивно ја додава на крајот на бројот (целиот број го множи со 10 прво)
 * `void doOperation(char c)` - Ја извршува операцијата дадена со `c`, помеѓу броевите `lastDigit` и `screen`.
 * `void enterOperation(char c)` - Ја извршува претходната операција (`lastOperation`) и ги поставува променливите за нови внесувања
 * `void toMemory()` - Го внесува бројот од `screen` во `memory`
 * `void fromMemory()` - Го враќа бројот од меморија

Кога ги напишеме овие функции, се што преостанува е да го изминеме целиот инпут со фор циклус и да ги повикуваме функциите кога е потребно.

```
long long lastDigit;
long long memory;
long long screen;
bool clearOnInput;
char lastOperation;
void enterDigit(char c)
{
    if(clearOnInput)
    {
        screen=c-'0';
        clearOnInput=false;
    }
    else
    {
        screen*=10;
        screen+=c-'0';
    }
}
void doOperation(char c)
{
    if(c=='+')
    {
        screen=lastDigit+screen;
    }
    else if(c=='-')
    {
        screen=lastDigit-screen;
    }
    else if(c=='*')
    {
        screen=lastDigit*screen;
    }
    else
    {
        screen=lastDigit/screen;
    }
}
void enterOperation(char c)
{
    doOperation(lastOperation);
    lastOperation=c;
    lastDigit=screen;
    clearOnInput=true;
}
void toMemory()
{
    memory=screen;
}
void fromMemory()
{
    screen=memory;
    clearOnInput=false;
}
int getResult(string input)
{
    lastDigit=0;
    memory=0;
    screen=0;
    clea rOnInput=false;
    lastOperation='+';
    for(int i=0;i<input.size()-1;i++)
    {
        if(input[i]>='0' && input[i]<='9')
            enterDigit(input[i]);
        else if(input[i]=='M')
            toMemory();
        else if(input[i]=='R')
            fromMemory();
        else
            enterOperation(input[i]);
    }

    doOperation(lastOperation);

    return screen;
}
```

## 300 - KthNumber
[Линк до задачата](http://codefu.mk/codefu2015-final-round.html?subpage=problem&problemid=2207)

Омилената задача од овој натпревар и според мене потешка од четвртата. Го користиме фактот дека секој број може да се претстави како уникатна комбинација од прости множители. Пример, бројот 12 може да се претстави како `2*2*3` и на никој друг начин. Исто така, `2*2*3` го претставува само бројот 12 и никој друг.

Задачава ја решаваме brute force со помош на priority queue. Првиот број од кој почнуваме е 1. Кога вадиме некој број од priority queue, додаваме `P` нови броеви (каде што `P` е бројот на дадени прости броеви). Доколку простите броеви ни се 2, 3 и 5, а го вадиме бројот 15 од queue-от, тогаш ги додаваме броевите 30 (2*15), 45 (3*15) и 75(5*15). При ова додавање само треба да внимаваме да не додадеме ист број два пати, што може лесно да се направи со `int,bool` мапа. На овој начин цело време вадиме и додаваме броеви од queue-то, кое само ни ги сортира броевите цело време. `K`-тиот број што ќе го извадиме е решението.

Единствено нешто на кое што треба да внимавате е priority queue-от. Треба посебно да се дефинира да ги сортира во обратен редослед (од најмал кон најголем).

```
string kthNumber(vector<int> primes, int k)
{
    map<long long, bool> found;
    priority_queue<long long, vector<long long>, greater<long long> > Q;

    found[1]=true;
    Q.push(1);

    for(int i=0;i<k-1;i++)
    {
        long long current=Q.top();
        Q.pop();
        for(int j=0;j<primes.size();j++)
            if(!found[current*primes[j]])
            {
                found[current*primes[j]]=true;
                Q.push(current*primes[j]);
            }
    }


    return getString(Q.top());
}
```

## 400 - DigitsGame

[Линк до задачата](http://codefu.mk/codefu2015-final-round.html?subpage=problem&problemid=2208)

Не толку проста greedy задача. Најпрво броиме колку цифри имаме на располагање, и потоа ги користиме нив за да составиме број. Бројот го составуваме почнувајќи од лево кон десно. Бидејќи бројот што го составуваме треба да биде што поблиску до бројот `A` (или најмалиот број поголем од `A` или најголемиот број помал од `A`), секогаш пробуваме прво да ставиме иста цифра од бројот `A` на иста позиција. Доколку немаме таква цифра на располагање, тогаш додаваме друга цифра (пoголема од потребната за `X`, помала од потребната за `Y`). Кога веќе еднаш додадеме различна цифра, тогаш останатите цифри ги додаваме greedy. За `X` секогаш земаме помала цифра, додека за `Y` секогаш земаме поголема цифра (за да стигнеме што поблиску до `A`).

Решението го имплементираме рекурзивно (две посебни функции за поголем или помал број). Рекурзијата има два параметри - `int` што означува на кое место треба да додадеме цифра и `bool` што означува дали веќе имаме еднаш додадено различна цифра (за да го пополниме остатокот од бројот со greedy). Функцијата е од тип `bool`, која би вратила `false` доколку не можеме да добиеме таков број.

```
string target;
int available[10];
int temp[10];

string result=";

bool getSmaller(int targetPosition, bool goHam)
{
    if(targetPosition==target.size())
        return !(target==result);
    if(goHam)
    {
        for(int i=9;i>=0;i--)
        {
            if(available[i])
            {
                available[i]--;
                result+=(char)(i+'0');
                if(getSmaller(targetPosition+1,goHam))
                    return true;
                available[i]++;
                result.erase(result.size()-1,1);
            }
        }
    }
    int neededDigit=target[targetPosition]-'0';
    if(available[neededDigit])
    {
        result+=(char)(neededDigit+'0');
        available[neededDigit]--;
        if(getSmaller(targetPosition+1,false))
            return true;
        available[neededDigit]++;
        result.erase(result.size()-1,1);
    }
    if(targetPosition==0 && neededDigit==1)
        return false;
    for(int i=neededDigit-1;i>=0;i--)
    {
        if(available[i])
        {
            available[i]--;
            result+=(char)(i+'0');
            if(getSmaller(targetPosition+1,true))
                return true;
            available[i]++;
            result.erase(result.size()-1,1);
        }
    }
    return false;
}

bool getBigger(int targetPosition, bool goHam)
{
    if(targetPosition==target.size())
        return true;
    if(goHam)
    {
        for(int i=0;i<=9;i++)
        {
            if(available[i])
            {
                available[i]--;
                result+=(char)(i+'0');
                if(getBigger(targetPosition+1,true))
                    return true;
                available[i]++;
                result.erase(result.size()-1,1);
            }
        }
    }
    int neededDigit=target[targetPosition]-'0';
    if(available[neededDigit])
    {
        result+=(char)(neededDigit+'0');
        available[neededDigit]--;
        if(getBigger(targetPosition+1,false))
            return true;
        available[neededDigit]++;
        result.erase(result.size()-1,1);
    }
    for(int i=neededDigit+1;i<=9;i++)
    {
        if(available[i])
        {
            available[i]--;
            result+=(char)(i+'0');
            if(getBigger(targetPosition+1,true))
                return true;
            available[i]++;
            result+=(char)(i+'0');
        }
    }
    return false;
}

class DigitsGame
{
  public:
    string getNumbers(string A, string B)
    {
        for(int i=0;i<10;i++)
            available[i]=0;
        target=A;
        for(int i=0;i<B.size();i++)
        {
            available[B[i]-'0']++;
        }

        string rez;
        if(!getBigger(0,false))
            result="0";
        rez+=result;
        rez+=',';
        result=";
        for(int i=0;i<10;i++)
            available[i]=0;
        for(int i=0;i<B.size();i++)
        {
            available[B[i]-'0']++;
        }
        if(!getSmaller(0,false))
            result="0";
        rez+=result;

      return rez;
  }
};
```
