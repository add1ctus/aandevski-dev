Како што спомнав минатиот пост, алгоритмот на Dijkstra е (според мене) еден од основните алгоритми кој се користи за натпреварување. Најчесто научен како алгоритам со `O(N^2)` сложеност, Dijkstra е перфектниот алгоритам за наоѓање на најкраткиот пат во граф со тежини од едно теме (изворот) кон сите други темиња во графот. Но што се случува кога `N` е многу голем број?

Последниот Codeforces натпревар имаше задача со граф од 100,000 темиња. `O(N^2)` сложеност би резултирало во 10 билиони операции во најлош случај, што е премногу за да се изврши во 2 секунди. Во такви околности алгоритмот на Dijkstra можеме да го оптимизираме со priority queue, намалувајќи ја сложеноста на `O(N*logN)`, што би резултирало во помалку до 2 милиона операции за истиот граф. Огромна разлика.

Во продолжение ќе ја разгледаме задачата и ќе објаснам како најлесно може да се искористи оваа оптимизација.

Предупредување : Ве очекува многу текст

## E - President and Roads

[Линк до задачата](http://codeforces.com/problemset/problem/567/E)

Се работи за држава со `N` градови, меѓусебно поврзани со `M` насочени врски, секоја со своја цена за патување, и се бара најефтиниот пат од градот `S` до градот `T`. По наоѓање на најефтиниот пат, потребно е да направите анализа за секоја врска, каде што има 3 избори:
 * Врската мора да се искористи за најефтиниот пат од `S` до `T`, печатиме `YES`
 * Врската може да се искористи за најефтиниот пат од `S` до `T` ако и се намали цената (цената сепак да е позитивен број), печатиме, `CAN X`(каде `X` означува за колку треба да се намали цената)
 * Врската не може да се искористи за најефтиниот пат од `S` до `Т` во никој случај, печатиме `NO`

За разјаснување на задачата, да разгледаме еден тест пример:

![Пример граф каде го бараме најкраткиот пат од S до T](https://aandevski.files.wordpress.com/2015/08/screenshot_12.png)

Во овој граф имаме два избора за најефтиниот пат од `S` до `T`:
 * S -> B -> C -> E -> T
 * S -> B -> D -> E -> T

И до двата случаи врските `S->B` и `E->T` се користат, така да за нив одговорот е `YES`. За останатите:

 * Доколку ја намалиме цената на `B->C` за 1 тогаш таа врска ќе се користи сигурно наместо `B->D`, исто и обратно, така да за нив печатиме `CAN 1`
 * Доколку се намали цената на `S->C` за 2, тогаш најефтиниот пат ќе е `S->C->E->T`, така да печатиме `CAN 2`
 * Доколку ја намалиме цената на `C->E` за 1 тогаш таа врска ќе се користи сигурно наместо `D->E`, исто и обратно, така да за нив печатиме `CAN 1`

## Како би ја решиле оваа задача?

Доколку би го пуштиле алгоритмот на Dijkstra од `S` кон `T`, тогаш би го добиле најефтиниот пат. Но тогаш при анализата на секоја врска не можеме да бидеме сигурни дали единствениот најефтин пат минува низ неа. Како решение на овој проблем можеме да направиме модификација на начинот на реконструкција на патот. Наместо користење на една променлива source за секое теме, можеме да користиме вектор кој ќе е способен да покаже повеќе од еден најефтин пат (доколку имаат иста должина). Додатно, би можеле да чуваме променлива `paths` за секое теме што означува колку различни најефтини патови имаме.

Иако со тоа би знаеле низ кои темиња поминува најефтиниот пат, проблемот доаѓа во печатење на резултатот. Во задачата се бара да ги изминуваме врските една по една во редоследот во кој се внесени и за секоја да го печатиме резултатот. На овој начин тоа не е можно (или многу е комплицирано). Затоа е потребен да направиме полесен начин со кој може да ги анализираме сите врски посебно.

Да се вратиме на примерот горе и да разгледаме од што се состои најефтиниот пат со било која врска. За пример може да земеме `C->E`. Доколку `C->Е` се содржи во најефтиниот пат, тогаш:

`најефтин пат од S до C + цена C->E + најефтин пат од E до T`

треба да е еднакво на најефтиниот пат од `S` до `T`. Додатно, за да утврдиме дали треба да печатиме `YES`, треба да сме сигурни дека сите најефтини патишта го користат `C->E`. Со други зборови, бројот на најефтини патови од `S` до `T` треба да е еднакво на:

`број на најефтини патови од S до C + број на најефтини патови од E до Т`

Доколку се задоволени тие два услови, тогаш со сигурност знаеме дека таа врска се користи секогаш и печатиме `YES`. Доколку само првиот услов е исполнет, тогаш потребно е да ја намалиме цената за 1 и со тоа патот да е најефтин. Доколку пак и двата услови не се исполнети, тогаш треба да ја намалиме цената на таа врска доволно за целиот пат да е поефтин од најефтиниот пат. Доколку не можеме толку да ја намалиме цената, печатиме `NO`.

## Имплементација

Сега кога знаеме како се добива резултатот за секоја врска, потребно е да ги собереме податоците кои ни го даваат резултатот. Бидејќи бараме најефтин пат од `S` до сите темиња и од `T` до сите темиња, потребно е да пуштиме 2 пати Dijkstra, еднаш од двете темиња. Но бидејќи се работи за насочен граф, ќе мора да ги смениме насоките на сите врски за да го најдеме најкраткиот пат од `T`. За таа причина чувам два посебни графа, во две насоки. Додатно во 3 низи ги меморираме сите врски за да можеме да ги анализираме за резултатот. При внес на сите темиња им правам -1 за да започнуваат од 0 (глупа навика).

```
int n,m,s,t; 
scanf("%d%d%d%d",&n,&m,&s,&t);
--s;
--t;

vector<pair<int, int> > graph[n]; 
vector<pair<int, int> > invertedGraph[n];
int from[m];
int to[m];
int weight[m];
int a,b,c;
for(int i=0;i<m;++i)
{
    scanf("%d%d%d",&a,&b,&c);
    graph[--a].push_back(make_pair(--b,c));
    invertedGraph[b].push_back(make_pair(a,c));
    from[i]=a;
    to[i]=b;
    weight[i]=c;
}
```

Со завршување на внесот, следниот чекор е Dijkstra. Како што веќе објаснив, не можеме да користиме Dijkstra со `O(N^2)` сложеност заради големиот број на темиња во графот, така да мора да употребиме priority queue.

Priority queue е податочна структура која е цело време „сортирана“. Зошто наводници? Бидејќи таа не е во целост сортирана, туку само гарантира дека првиот елемент e најголемиот. Во оваа податочна структура вие можете само да пристапувате кон најголемиот елемент. Со други зборови, доколку имате priority queue со 100,000 броја, вие можете само да видите кој е најголемиот број. Исто така можете да го извадите најголемиот број од queue-от, при што вториот најголем број го завзема неговото место. Доколку ставите нов број, тој ќе е на врвот на queue-от само доколку е најголем. Во спротивно, тој ќе е изгубен некаде во остатокот од queue-от и нема да имате пристап до него се додека не извадите доволно броеви така да тој е најголем. Внесувањето на елементи се прави со `O(log N)` сложеност, но проверката на најголемиот број се прави со `O(1)` сложеност, додека вадењето на најголемиот број се прави со `O(log N)` сложеност.

Како можеме оваа податочна структура да ја искористиме во Dijkstra? Доколку го знаете алгоритмот, знаете дека при секоја итерација ние го бараме темето со најкраток пат кое веќе не е посетено. Стандардно тоа го правиме со линеарно изминување на сите темиња и барање на најблиското теме кое не е посетено, `O(N)` сложеност. Доколку за оваа акција искористиме priority queue, тогаш можеме многу побрзо да го наоѓаме темето кое треба следно да се посети, така да целиот алгоритам се намалува од `O(N^2)` на `O(NlogN)`.

Но рековме дека priority queue работи со традиционални променливи (кои можат да се споредуваат) и секогаш ја дава најголемата вредност, не најмалата. Така да потребно е да направиме наша посебна променлива (во вид на структура) на која ќе наместиме посебни правила за споредување, така да priority queue-от ќе ни го дава потребното теме. Ја правиме следнава структура:

```
struct el
{
    int to;
    long long weight;
    el(int a=0, long long b=0) //Конструктор за полесно внесување на темињата во PQ
    {
        to=a;
        weight=b;
    }
```

Со ова имаме дефинирана структура, но фалат правилата за споредување. Потребно е да го преоптовариме операторот за споредување `<`, со кој ќе дефинираме како ќе функционира priority queue-от.

```
    bool operator<(const el &a) const
    {
        return weight>a.weight;
    }
};
```

Со ова операторот `<` го дефинираме да работи обратно од тоа што е наменето, така да priority queue-от сега ќе работи обратно (ќе ја наоѓа најмалата вредност наместо најголемата). Кога ова е спремно, можеме да започнеме со пишување на алгоритмот на Dijkstra. Бидејќи ни е потребен најефтиниот пат од две насоки, чуваме две низи: `dist_s` и `dist_t`. Исто така имаме две додатни низи `paths_s` и `paths_t` кои означуваат колку најефтини патишта постојат до секоја дестинација. За крај додаваме и низа `visited` која ќе ни е потребна за Dijkstra.

```
long long dist_s[n];
long long dist_t[n];
long long paths_s[n];
long long paths_t[n];
bool visited[n];
priority_queue<el> Q;

for(int i=0;i<n;++i)
{
    dist_s[i]=dist_t[i]=99999999999999999;
    paths_s[i]=paths_t[i]=0;
    visited[i]=0;
}
```

За да пуштиме Dijkstra од `S`, потребно е да ги иницираме вредностите:

```
    dist_s[s]=0;
    paths_s[s]=1;
    Q.push(el(s,0));
```

Наместо да броиме колку темиња сме веќе посетиле, може алгоритмот да ни работи додека има темиња во queue-от, така да условот за while циклусот ќе е `while(!Q.empty())`. Внатре во циклусот, со `Q.top` го добиваме минималниот елемент веднаш. Доколку тој елемент е веќе посетен, бараме нов од почеток. Во спротивно, го поставаме како посетен и ги менуваме далечините на сите негови соседни темиња (стандардна Dijkstra) со тоа што не забораваме да ги додаваме темињата во priority queue-от доколку најдеме најефтин пат. Исто така бидејќи бараме и број на најефтини патишта, проверуваме дали новиот пат што сме го пронашле е еднаков на патот кој веќе го знаеме, за да ја зголемиме променливата paths.

```
while(!Q.empty())
{
    int smallest=Q.top().to;
    Q.pop();

    if(visited[smallest])
        continue;

    visited[smallest]=true;

    for(int i=0;i<graph[smallest].size();++i)
    {
        if(!visited[graph[smallest][i].first] && dist_s[smallest] + graph[smallest][i].second < dist_s[graph[smallest][i].first] )
        {
            dist_s[graph[smallest][i].first] = dist_s[smallest] + graph[smallest][i].second;
            paths_s[graph[smallest][i].first] = paths_s[smallest];
            Q.push(el(graph[smallest][i].first,dist_s[graph[smallest][i].first]));
        }
        else if(!visited[graph[smallest][i].first] && dist_s[smallest] + graph[smallest][i].second == dist_s[graph[smallest][i].first])
        {
            paths_s[graph[smallest][i].first] += paths_s[smallest];
            paths_s[graph[smallest][i].first] %= MOD;
        }
    }
}
```

Променливата `paths` ја запишуваме по модул некој голем број (јас имав дефинирано MOD = 1000776999) бидејќи бројот на патишта може да го надмине ограничувањето на `long long`. Истото го правиме и за најефтиниот пат почнувајќи од `T`.

`
memset(visited,false,sizeof(visited));
dist_t[t]=0;
paths_t[t]=1;
Q=priority_queue<el>();
Q.push(el(t,0));

while(!Q.empty())
{
    int smallest=Q.top().to;
    Q.pop();

    if(visited[smallest])
        continue;

    visited[smallest]=true;

    for(int i=0;i<invertedGraph[smallest].size();++i)
    {
        if(!visited[invertedGraph[smallest][i].first] && dist_t[smallest] + invertedGraph[smallest][i].second < dist_t[invertedGraph[smallest][i].first] )
        {
            dist_t[invertedGraph[smallest][i].first] = dist_t[smallest] + invertedGraph[smallest][i].second;
            paths_t[invertedGraph[smallest][i].first] = paths_t[smallest];
            Q.push(el(invertedGraph[smallest][i].first,dist_t[invertedGraph[smallest][i].first]));
        }
        else if(!visited[invertedGraph[smallest][i].first] && dist_t[smallest] + invertedGraph[smallest][i].second == dist_t[invertedGraph[smallest][i].first] )
        {
            paths_t[invertedGraph[smallest][i].first] += paths_t[smallest];
            paths_t[invertedGraph[smallest][i].first] %= MOD;
        }
    }
}
`

Се што преостанува е да ги провериме условите кои ги наведовме на почетокот на овој пост:

```
for(int i=0;i<m;++i)
{
    long long current = weight[i] + dist_s[from[i]] + dist_t[to[i]];
    if(dist_s[t] == current)
    {
        if(paths_s[t] == (paths_s[from[i]] * paths_t[to[i]])%MOD)
            printf("YES\n");
        else if(weight[i]>1)
            printf("CAN 1\n");
        else
            printf("NO\n");
    }
    else
    {
        if(current-(dist_s[t]-1)<weight[i])
            printf("CAN %d\n",current-(dist_s[t]-1));
        else
            printf("NO\n");
    }
}
```

Со ова задачата е решена.
