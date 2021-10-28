По долга пауза (некој вид на летен распуст) повторно започнувам со онлајн натпревари. Првиот на листа е 314-тиот Codeforces натпревар, посветен на бројот Пи. Како за натпревар организиран од учесник од втора дивизија, натпреварот беше прилично лесен и не бараше познавања од некои алгоритми надвор од стандардните (стандардните ги сметам BFS, DFS, Dijkstra, Динамичко, Binary search). Потешките задачи само имаа потежок начин на доаѓање до идејата.

За време на натпреварот успеав да ги решам првите 3 и бев многу блиску до точно решение на задачата D, каде што погрешно бев разбрал дел од задачата. Со тој резултат успеав да стигнам до 212-тото место што ме доближи до првата дивизија уште повеќе. Ова беа моите решенија на првите 4 задачи (задачата E ќе ја објаснам во посебен блог пост).

## A - Lineland Mail
[Линк до задачата](http://codeforces.com/problemset/problem/567/A)

Имате дадено градови во еднодимензионално поле (означени со `Х` координата). За секој град вие треба да ја кажете далечината на градот најблиску до него и градот најдалеку до него.

За два града `x` и `y`, далечината можеме да ја добиеме како апсолутната вредност од `koordinata[x] - koordinata[y]`. Доколку знаеме дека еден град има поголема координата од другиот, тогаш можеме да го ставиме како прв број во разликата и воопшто да не користиме апсолутна вредност.

Бидејќи се работи за 10^5 градови, не е идеално решението да ги споредуваме сите градови еден со друг. Со сигурност знаеме дека за секој град, градот најдалеку од него е еден од градовите кој се наоѓа на краевите на полето. Исто така знаеме дека за секој град, градот најблиску до него е еден од двата града соседни на тој град. Според ова, доколку имаме `N` градови и пробуваме да го најдеме решението за градот `X`, тогаш најдалекиот град е еден од градовите 0 или `N-1`, додека најблискиот град е еден од градовите `X-1` или `X+1`. Единствен исклучок за ова е првиот и последниот град.

```
int n;
scanf("%d",&n);
int arr[n];
for(int i=0;i<n;++i)
    scanf("%d",&arr[i]);
printf("%d %d\n",arr[1]-arr[0],arr[n-1]-arr[0]);
for(int i=1;i<n-1;++i)
    printf("%d %d\n",min(arr[i]-arr[i-1],arr[i+1]-arr[i]),max(arr[i]-arr[0],arr[n-1]-arr[i]));
printf("%d %d",arr[n-1]-arr[n-2],arr[n-1]-arr[0]);
```

## B - Berland National Library

[Линк до задачата](http://codeforces.com/problemset/problem/567/B)

Иако на почеток задачата знае да биде збунувачка, по кратко размислување можете да забележите дека е многу проста. Имате систем во библиотека кој бележи кога некој влегува или излегува. Секој посетител има свој ID и може да влегува или излегува повеќе пати. Исто така можно е тој посетител да влегол пред да се пушти системот. За даден извештај од системот, потребно е да утврдите колку највеќе луѓе биле внатре во било кој момент.

Чуваме `boolean` низа која ни означува дали некој посетител е внатре или не. Исто така имаме и променлива што ни означува колку луѓе има внатре во моментот. Секогаш кога ќе влезе некој, го зголемуваме бројот за 1. Но кога некој излезе, постојат две опции:

 * Корисникот влегол кога бил пуштен системот, така да го намалуваме бројот на моментални посетители за 1
 * Корисникот бил влезен пред да се пушти системот, така да го зголемуваме максимумот на посетителите за 1

Со оваа забелешка решението е просто:

```
int n;
cin>>n;
char sign;
int id;
int currentlyInside=0;
int maxInside=0;
bool isInside[1000001];
memset(isInside,false,sizeof(isInside));
for(;n;--n)
{
    cin>>sign>>id;
    if(sign=='+')
    {
        isInside[id]=true;
        maxInside=max(maxInside,++currentlyInside);
    }
    else
    {
        if(!isInside[id])
            ++maxInside;
        else
        {
            isInside[id]=false;
            --currentlyInside;
        }
    }
}
cout<<maxInside;
```

## C - Geometric Progression

[Линк до задачата](http://codeforces.com/problemset/problem/567/C)

Еве уште еден индикатор дека континуирано решавање на задачи на сите страни вреди многу и дека евентуално ќе сретнете задачи кои се повторуваат. Задачава е многу слична на задачата COW од [Фебруарскиот USACO натпревар](https://aandevski.wordpress.com/2015/02/23/usaco-february-contest/), со единствена разлика што во задачата COW се бараа буквите C, O и W во правилен редослед додека тука ги бараме броевите `x`, `x*k`, `x*k*k`, за било кој број `x`.

Идејата е иста: забележуваме колку пати бројот се појавил како прв член од некоја прогресија и како втор член од некоја прогресија. При тоа, бројот `x` секогаш може да е прв член од некоја прогресија, но може да е втор член само доколку тој број е делив со `k` и пред него се појавил бројот `x/k` барем еднаш. Разгледајте го решението на задачата COW за да ја сфатите подетално идејата.

```
int n,k;
scanf("%d%d",&n,&k);
int temp;
long long result=0;
map<int, long long> appearedOnce;
map<int, long long> appearedTwice;
for(int i=0;i<n;++i)
{
    scanf("%d",&temp);
    if(temp%k==0)
    {
        result+=appearedTwice[temp/k];
        appearedTwice[temp]+=appearedOnce[temp/k];
    }
    appearedOnce[temp]++;
}

printf("%I64d",result);
```

## D - One-Dimensional Battle Ships

[Линк до задачата](http://codeforces.com/problemset/problem/567/D)

Задачава има неколкумина можни решенија, од кои успеав да најдам две доста интересни решенија со binary search. Но првин да ги разгледаме правилата на играта.

Исто како во првата задача, имаме дадено еднодимензионално поле со должина `N`. На тоа поле првиот играч постава `K` бродови со должина `A`, така да два брода не смеат да се допрат (што не приметив додека траеше натпреварот). Вториот играч, не знаејќи ги позициите на бродовите, потоа треба да „пука“, т.е. да проба да погоди на кои полиња се наоѓаат тие. Првиот играч е должен да ви каже `hit` доколку погодите некој брод. Во спротивно, ви кажува `miss`. Проблемот со првиот играч во оваа задача е тоа што секогаш кажува `miss`, дури и да погодите. Вашата задача е за дадени позиции на кои пукал вториот играч, да утврдите кога првиот играч сигурно лаже.

Можеме да сме сигурни дека првиот играч сигурно лаже само кога се погодени толку полиња така да веќе нема место да се наредат K бродови од должина A. Притоа треба да внимаваме, бидејќи не е исто да се погоди поле на почетокот од таблата и на средината од таблата. Сега, двете идеи за задачата:

 * Чуваме сортиран вектор од непогодени сегменти (парови од два броја што означуваат почеток и крај на сегмент). На секое пукање ние го наоѓаме сегментот во кој е пукано, го бришеме и додаваме два нови сегменти како резултат на поделбата од пукањето. Со додатна променлива бележиме колку вкупно бродови можат да се постават на достапните сегменти. Секогаш кога одземаме сегмент, го одземаме и бројот на бродови што можат да се стават на тој сегмент. Кога додаваме нов сегмент, додаваме број на бродови што можат да се стават на тој сегмент. За сегмент кој почнува на позиција `l` и завршува на позиција `r` (вклучувајќи ги и тие две точки), можеме да поставиме вкупно `(l+r+2) / (a+1)` бродови. Binary search користиме кога го наоѓаме сегментот во кој е пукано.
 * Правиме функција која за даден број на пукања `(X)` ќе ни каже дали може да се постават `K` брода на преостанатите полиња. Тоа можеме да го симулираме лесно така што ќе направиме низа од `boolean` со големина `N`, и првите `X` пукања ќе ги обележиме како `false` во низата (сите останати се `true`). Потоа, ја изминуваме низата од почеток до крај и броиме колку брода можеме да поставиме на greedy начин (секогаш ставаме најлево можно). Кога веќе имаме функција која ни кажува кој број на пукања е валиден, потребно е само со binary search да го пронајдеме најмалиот број на пукања каде што резултатот е `false`. Доколку по сите пукања резултатот од функцијата е `true`, значи одговорот е -1 (не можеме да докажеме дека првиот играч лаже).

Функцијата за проверка:

```
bool check(int s)
{
    bool board[200001];
    memset(board,true,sizeof(board));
    for(int i=0;i<s;++i)
        board[shots[i]]=false;
    int placedShips=0;
    for(int i=1;i<=n-a+1;++i)
    {
        bool canPlace=true;
        for(int j=i;j<i+a;++j)
            if(!board[j])
            {
                i=j;
                canPlace=false;
                break;
            }
        if(canPlace)
        {
            ++placedShips;
            i+=a;
        }
    }
    if(placedShips<k)
        return false;
    return true;
}
```

Остатокот од решението (binary search):

```
    scanf("%d%d%d%d",&n,&k,&a,&m);

    for(int i=0;i<m;++i)
        scanf("%d",&shots[i]);

    if(check(m))
    {
        printf("%d",-1);
        return 0;
    }

    int lo,mid,hi;
    lo=1;
    hi=m;

    while(lo<hi)
    {
        mid=(hi+lo)/2;
        if(!check(mid))
            hi=mid;
        else
            lo=mid+1;
    }

    printf("%d",hi);
```