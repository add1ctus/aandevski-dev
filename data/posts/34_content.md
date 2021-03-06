> Ако има една структура што не ја знаете, а мора да ја научите, тоа е segment tree

За време на подготовките пред регионалниот ACM натпревар во Романија, ова беше муабетот што го слушнавме најмалку 5 пати во рок од саат време. Деновиве ја обработивме структурата по предметот алгоритми и сложеност, при што имав шанса да спремам неколку задачи за лабораториските вежби. Со тоа, би ја искористил шансава да направам поопширен пост за segment trees, кој би бил корисен и на тие што никогаш ја немаат сретнато оваа структура. Подоцна во постот ќе ги објаснам двете задачи кои ги спремив за лаб.

## Мотивација

Пред да навлеземе во структурата, да го разгледаме проблемот кој таа го решава и да ја воочиме потребата за ваква структура. Да претпоставиме дека имаме низа од `N` броеви, и од нас ќе се бара да одговараме на барања во стилот „кој е збирот на броевите од `x`-тиот до `y`-тиот број“ или „кој е најмалиот број од `x`-тиот до `y`-тиот број“.

Најосновното решение би било пуштање на `for` циклус од `x` до `y`, проверувајќи / сумирајќи ги сите броеви, што би имало `O(N)` сложеност. Сите навлезени во динамичкото програмирање без проблем би се сетиле на Range Sum Query, каде што правиме низа со динамичко каде во `DP[x]` го чуваме збирот на броевите од 0-тиот до `x`-тиот број. Тогаш збирот од `x` до `y` е `DP[y] - DP[x-1]`. Ова бара една прекалкулација на низата `DP` во `O(N)` време, а секое барање се извршува во `O(1)`.

Но што се случува кога сакаме да правиме промени во тек на извршувањето? Тогаш мораме да избереме еден од двата горенаведени начина: да имаме `O(1)` измени но `O(N)` барања или пак `O(1)` барања но `O(N)` прекалкулации при секоја измена. Бидејќи и двете се неефикасни (ако претпоставиме еднаков број на барања и измени), се појавува потреба за друга структура, која што може да изменува и извршува барања во оптимално време. Segment tree го прави тоа во `O(logN)`.

## Segment tree

Се работи за бинарно дрво кое во секоја точка чува информации за некој одреден сегмент. Во продолжетокот ќе давам примери за дрво кое дава сума на броеви во избран сегмент. Идејата на дрвото е дека во коренот ја имаме целата низа - збирот на сите броеви од 0 до `N-1`. Понатаму, за секоја точка дрвото го поделуваме на две еднакви половини, каде што тие точки чуваат збир за таа одредена половина. Ова се повторува се додека не стигнеме до точки што претставуваат само еден број од низата.

![Пример за дрво направено на низа со 8 броеви: (0, 1, 2, 3, 4, 5, 6, 7)](https://aandevski.files.wordpress.com/2016/04/screenshot_37.png)

Во горниот пример со црвени букви ви е означено кој сегмент е покриен од страна на одредена точка во дрвото. Вкупно `2*N-1` точки се потребни да се претстави segment tree за низа со должина `N`. Бидејќи секоја точка треба да се измине еднаш, евидентно е дека времето за градење на вакво дрво е `O(N)`.

Но како се извршуваат барањата и измените во ова дрво? Можеме да воочиме дека за некои сегменти веќе имаме пресметано резултати, така да доколку ни е потребен збирот на сегментот `[4,7]`, можеме веднаш да вратиме 22. Но доколку сегментот не ни е претставен во дрвото како таков, тогаш мора да спојуваме повеќе сегменти. Така да на пример за барањето `[3,5]` ние би вратиле како резултат `[3,3]` + `[4,5]`. Бидејќи дрвото е балансирано (што ја прави неговата максимална длабочина `logN`), при што се посетуваат највеќе 2 точки од секое ниво (можете да го изгуглате доказот, нема до толку да навлегувам во ова), сложеноста на барањата е `O(logN)`.

Измените ги правиме така што рекурзивно навлегуваме во дрвото се додека не стигнеме до листот. Кога стигнеме до листот, враќајки се назад ја изменуваме вредноста на сите точки што го имаат во нивниот сегмент бројот кој го изменуваме. Така да доколку би го смениле 3-тиот број, тогаш ќе ги смениме само точките кои ги содржат сегментите `[3,3]`, `[2,3]`, `[0,3]` и `[0,7]`. Бидејќи има logN вакви точки, сложенсота на измените исто така е O(logN).

За додатно разјаснување можете да го разгледате следниов [линк](http://visualgo.net/segmenttree.html).

## Претставување во меморија, кодирање

Кога веќе ја разбравме идејата зад дрвото, сега преостанува да го имплементираме. Иако името наложува дека се работи за дрво, всушност оваа структура ја претставуваме во еднодимензионална низа со големина `2*2^(log2 n)-1`. Но зошто оваа големина, кога веќе спомнавме дека ни се потребни само `2N-1` темиња во дрвото. Примерот што го прикажавме горе е со големина на низа степен на два, така да дрвото е комплетно. Но доколку земеме било кој друг број (на пример 10), ќе приметите дека некои темиња порано стигаат до листовите (едно ниво повисоко). Заради ова ни остануваат празни места во дрвото, така да мораме да дефинираме вишок променливи. Доколку ви е тешко да ја запомните формулава, најлесно е да правите `3*N` низа за дрвото.

Дрвото е претставено во низата така што коренот се наоѓа на позиција 1. Децата на коренот се наоѓаат на позициите 2 и 3 (2*1 и 2*1+1). Оваа идеја се применува за сите останати точки. Децата на точката `K` се точките `K*2` и `K*2+1`.

![Редни броеви на точките на дрвото од претходниот пример](https://aandevski.files.wordpress.com/2016/04/screenshot_38.png)

Градењето на ова дрво се прави со функцијата `build(l,r,p)`, каде што `l` го означува почетокот на сегментот, `r` го означува крајот на сегментот а `p` го означува редниот број на точката што го означува тој сегмент. Оваа функција се повикува со `build(0,n-1,1)` што ја става целата низа во коренот на дрвото. Понатаму вршиме рекурзивни повици со што се потполнува остатокот од дрвото. Рекурзиите се вршат се додека не стигнеме до лист на дрвото, каде што сегментот ни е само еден број, при што знаеме дека вредноста на тој сегмент е вредноста на самиот број.

```
int n;
int arr[100000];
int st[300000];

void build(int l = 0, int r = n - 1, int p = 1)
{
    if(l == r) //Доколку сегментот е само еден број, значи сме стигнале до лист
        st[p] = arr[l];
    else
    {
        build(l, (l+r)/2, p*2); //Го градиме левиот дел од дрвото
        build((l+r)/2+1, r, p*2+1); //Го градиме десниот дел од дрвото
        st[p] = st[p*2] + st[p*2+1]; //Го ставаме збирот на двата дела во точката
    }
}
```

За барањата имаме функција `query(i,j,l,r,p)`, каде што `l`,`r` и `p` ни ја означуваат точката исто како претходната функција, додека `i` и `j` ни го означуваат сегментот кој сме го побарале. На пример доколку го сакаме збирот од 2 до 5, повикот би бил `query(2,5,0,N-1,1)`. Рекурзивно го изминуваме дрвото се додека не стигнеме до состојба каде точката во која сме влегле е комплетно во сегментот или воопшто не е во сегментот. Доколку не се исполнети овие два услови, тогаш повикуваме рекурзија за двете половини на точката.

```
int query(int i, int j, int l = 0, int r = n - 1, int p = 1)
{
    if(i > r || j < l) //Бараниот сегмент не ја содржи точката p воопшто
        return 0;
    if(i <= l && r <= j) //Бараниот сегмент целосно ја содржи точката p
        return st[p];
    return query(i, j, l, (l+r)/2, p*2) + query(i, j, (l+r)/2+1, r, p*2+1);
}
```

Преостанува функцијата за измени, `update(index,value,l,r,p)`, со која во точката `arr[index]` ја ставаме вредноста `value`. `l`, `r` и `p` имаат исти значења повторно. Слично како `build`, повторно рекурзивно навлегуваме во дрвото се додека не стигнеме до листот, и од таму при враќање назад ја ажурираме вредноста на сите точки.

```
void update(int index, int value, int l = 0, int r = n - 1, int p = 1)
{
     if(l == r) // Сме стигнале до листот, ја менуваме вредноста
         arr[l] = st[p] = value;
     else
     {
         if(index > (l+r)/2) //Проверуваме дали бараниот елемент е во лева или десна половина
            update(index, value, (l+r)/2+1, r, p*2+1);
        else
            update(index, value, l, (l+r)/2, p*2);
        st[p] = st[p*2] + st[p*2+1];
    }
}
```

## Lazy propagation, прва задача

Горенаведениот пример работи супер кога имаме барања за сегменти и правиме измени на само еден број. Но доколку би сакале да напраивме измена на некој сегмент (како во [една од задачите](http://mendo.mk/algoritmi/Task.do?competition=268&id=651) кои ги зададов за лабораториските вежби), тогаш би требало да ја повикаме функцијата `update` онолку пати колку што имаме броеви во сегментот. Со ова измените би биле `O(NlogN)`, што воопшто не е оптимално. Со таа цел користиме lazy propagation, трик кој ни овозможува да правиме многу побрзи измени во дрвото.

Со иста големина како сегментното дрво чуваме нова низа lazy, која што меморира некои измени што треба да ги направиме, но уште не сме ги направиле. Зошто ни е потребно ова? Во сликите погоре, доколку би сакале да направиме измена на сегментот `[0,3]`, тогаш би требало рекурзивно да влеземе и во точките `[0,1]`, `[2,3]`, `[0,0]`, `[1,1]`, `[2,2]` и `[3,3]` за да ја направиме измената секаде. Наместо да го правиме тоа, можеме за точките `[0,1]` и `[2,3]` да ја ставиме вредноста во `lazy`, и да ги измениме тие точки друг пат.

Доколку се прашувате зошто ги изменуваме тие точки, тоа се прави бидејќи во иднина можеби ќе провериме некој од тие под-сегменти. Доколку сме направиле измена на `[0,3]`, тогаш можеби во иднина би направиле барање за сегментот `[2,3]`, каде што измената мора да е одразена. Доколку измената сеуште не е направена, туку е само меморирана во `lazy`, тогаш при извршување на барањето ќе ја довршиме измената. Со ова измените ги правиме само доколку ни се потребни за барање, наместо да ги правиме секогаш. Бидејќи измените ги правиме во исто време со барањето, ова воопшто не ја зголемува сложеноста.

Кодот не е многу сменет. Во `build` функцијата доволно е да ја иницираме вредноста на lazy на 0, додека во `query` доволно е да го додадеме следниов код на почетокот на функцијата:

```
if(lazy[p] > 0) //Доколку треба да се направи некоја измена
{
    st[p] += lazy[p] * (r - l + 1); //Има (r-l+1) точки во сегментот, сите ги зголемуваме за lazy[p]
    if(l != r) //Доколку сегментот има под-сегменти
    {
        lazy[p*2] += lazy[p]; //Додаваме lazy за под-сегментите
        lazy[p*2+1] += lazy[p];
    }
    lazy[p] = 0;
}
```

Единствена функција која е поразлична е `update` функцијата, која сега треба да менува цели сегменти наместо само една точка. Прво во функцијата проверуваме дали има некои поранешни промени меморирани во `lazy` кои треба да ги извршиме. По тоа, ги правиме истите проверки како query (дали сегментот е комплетно во точката или пак целосно надвор од неа).

```
void update(int i, int j, int value, int l = 0, int r = n - 1, int p = 1)
{
    if(lazy[p] > 0)
    {
        st[p] += lazy[p] * (r - l + 1);
        if(l != r)
        {
            lazy[p*2] += lazy[p];
            lazy[p*2+1] += lazy[p];
        }
        lazy[p] = 0;
    }
    if(i > r || j < l)
        return;
    if(i <= l && r <= j)
    {
        st[p] += value * (r - l + 1);
        if(l != r)
        {
            lazy[p*2] += value;
            lazy[p*2+1] += value;
        }
    }
    else
    {
        update(i, j, value, l, (l+r)/2, p*2);
        update(i, j, value, (l+r)/2+1, r, p*2+1);
        st[p] = st[p*2] + st[p*2+1];
    }
}
```

Кога веќе имаме комплетно имплементиран код за segment tree со lazy propagation, останува само да го напишеме main-от кој ќе ја реши задачата.

```
int main() {     cin>>n;
    for(int i = 0 ; i < n ; ++i)         cin>>input[i];

    build();
    int queries;
    cin>>queries;
    for(int i = 0 ; i < queries ; ++i)
    {
        char type;
        int l,r;
        cin>>type;
        if(type == 'U')
        {
            int l,r,amount;
            cin>>l>>r>>amount;
            update(l,r,amount);
        }
        else
        {
            int l,r;
            cin>>l>>r;
            cout<<query(l,r)<<"\n";
        }
    }
    return 0;
}
```

## Истерување (втора задача)
[Линк до задачата](http://mendo.mk/algoritmi/Task.do?competition=268&id=652)

Клучна идеја за оваа задача е дека можеше да се претстави како низа од правоаголници, секој со ширина 1 и висина - гласност на фанот.

![Тест пример: (2, 1, 5, 6, 2, 3)](https://aandevski.files.wordpress.com/2016/04/screenshot_39.png)

Кога вака ќе ги претставиме фановите, тогаш решението на задачата е плоштината на најголемиот правоаголник. Исфрлањето на фанови од лево и од десно е само друг начин за да се претстави фактот дека преостанатите фанови мора да седат еден до друг.

Идејата при решавање е divide and conquer, каде што почнуваме со сите фанови и во секој чекор го исфрламе најтивкиот фан (бидејќи доколку не го исфрлиме, само ќе го намалиме бројот на фанови а нивната гласност ќе остане иста). При исфрлање на некој фан може да добиеме две посебни групи на фанови (каде што само една ќе може да ја искористиме за резултатот на крај). Да разгледаме како би работело ова за примерот погоре.

На почетокот групата ги содржи сите фанови и нејзината гласност е 6 (6 фана * 1 гласност). Доколку го исфрлиме фанот со гласност 1, тогаш добиваме 2 групи: една со гласност 2 (1 фан * 2 гласност) и една со гласност 8 (4 фана * 2 гласност). Бидејќи првата група не можеме веќе да ја делиме, продолжуваме со втората. Доколку го исфрлиме фанот со гласност 2, тогаш добиваме две групи: една со гласност 10(2 фана * 5 гласност) и една со гласност 3 (1 фан * 3 гласност). Бидејќи втората не можеме да ја поделуваме, продолжуваме со првата. Го исфрламе фанот со гласност 5 и ни останува група со гласност 6 (1 фан * 6 гласност). Со ова веќе нема групи за поделба и сме го завршиле алгоритмот. Од сите групи кои сме ги направиле, забележуваме дека групата со гласност 10 е најгласната група, така да ја земаме таа вредност како резултат.

Во оваа задача можеме да искористиме segment tree за да можеме ефикасно да го наоѓаме најтивкиот фан во одредена група. Бидејќи во секоја итерација на овој алгоритам исфрламе по еден фан, можеме да заклучиме дека овој дел е `O(N)`. Доколку би го барале најтивкиот фан помеѓу сите со for циклус, тогаш овој алгоритам би бил `O(N^2)`, додека со segment tree овој алгоритам е `O(NlogN)`.

Кога го имаме divide and conquer алгоритмот (кој исто е имплементиран рекурзивно), преостанува само да имплементираме segment tree (внимавајте, овој пат дрвото треба да ви го дава индексот на најтивкиот фан, не збирот на сегментот).

```
#include <cstdio>
#include <algorithm>

using namespace std;

int n;
int input[100000];
int st[300000];

void build(int l = 0, int r = n - 1, int p = 1)
{
    if(l == r)
    {
        st[p] = l;
        return;
    }
    build(l, (l+r)/2, p*2);
    build((l+r)/2+1, r, p*2+1);
    if(input[st[p*2]] > input[st[p*2+1]])
        st[p] = st[p*2+1];
    else
        st[p] = st[p*2];
}

int query(int l, int r, int i = 0, int j = n - 1, int p = 1)
{
    if(l > j || r < i)
        return -1;
    if(l <= i && j <= r)
        return st[p];

    int query1 = query(l, r, i, (i+j)/2, p*2);
    int query2 = query(l, r, (i+j)/2+1, j, p*2+1);

    if(query1 == -1)
        return query2;
    else if(query2 == -1)
        return query1;
    else if(input[query1] > input[query2])
        return query2;
    else
        return query1;
}

int solve(int l = 0, int r = n - 1)
{
    int smallest = query(l, r);
    int solution = input[smallest] * (r - l + 1);

    if(smallest - 1 >= l)
        solution = max(solution, solve(l, smallest - 1));
    if(smallest + 1 <= r)
        solution = max(solution, solve(smallest + 1, r));

    return solution;
}

int main()
{
    scanf("%d",&n);
    for(int i = 0 ; i < n ; ++i)
        scanf("%d",&input[i]);

    build();
    printf("%d",solve());

    return 0;
}
```
