Доколку не бевте запознаени досега, постои [„скриен“ дел на Мендо](http://mendo.mk/algoritmi/) наменет за ФИНКИ, поточно за предметот Алгоритми и податочни структури (кој се изучува втора година). Таму, покрај лабораториските вежби за тој предмет и неколку предизвици по Дискретна математика, исто така можете да најдете и [интересна база на задачи за вежбање](http://mendo.mk/algoritmi/User_Competition.do?id=150) алгоритми (динамичко, графови, итн). Решавајќи ги задачите од таа секција наидов на една доста интересна задача за која морав да научам нов алгоритам кој е доста лесен и интересен, па решив да го споделам.

Задачава е [следна](http://mendo.mk/algoritmi/Task.do?competition=150&id=166). Откако ќе ја прочитате приказната за магистрални патишта, компании и инвестиции и размислите малку, станува јасно дека во задачава всушност станува збор за насочен тежински граф во кој треба да најдете најкраток пат од точката `S` до точката `T`. Звучи просто на почеток, станува збор само за школски пример на алгоритмот на Dijkstra. Но тука наидуваме на проблем, во задачава тежините можат да бидат и негативни броеви.

## Зошто Dijkstra не работи со негативни броеви?

Доколку сте добро запознаени со алгоритмот на Dijkstra, веројатно знаете дека тој работи на greedy принцип. Тоа би работело перфектно во граф со само позитивни тежини, бидејќи секогаш пробувате да ја изберете најмалата тежина (бидејќи доколку сега не сте нашле помала, сигурно нема и во иднина да најдете). Проблемот доаѓа со негативни тежини, бидејќи не можеме да бидеме сигурни дека најмалата тежина што ја гледаме во даден момент ќе е најмала и кога завршиме со изминување на графот, бидејќи можеби графот се разгранува во негативни броеви кои би пронашле алтернативен и поефтин пат до бараното теме. Доколку ова ви звучи тешко за сфаќање, ќе разгледаме еден прост пример.

![](http://i.stack.imgur.com/rmowk.png)

Најпрвин да разгледаме како алгоритмот на Dijkstra би работел тука. Почнувајќи од `A`, најблиското теме ни е `C`, така да го означуваме како посетено со далечина 0. Следното е `B`, со далечина 1, па на крајот останува `D`, со далечина 99. Врската `D->B` со тежина -300 воопшто не се користи. Доколку би ја искористиле таа врска, тогаш најкраткиот пат до `B` е -201, а најкраткиот пат до `C` е -200.

## Enter, Bellman-Ford

Смислен од прилика во исто време со алгоритмот на Dijkstra, алгоритмот на Richard Bellman и Lester Ford ја врши истата работа, наоѓање на најкраток пат во граф. Но за разлика од Dijkstra кој работи во временска сложеност од `O(N^2)` (или `O(NlogN)` со priority queue), овој алгоритам работи со приближно `O(N^3)` сложеност, што е значајно поспоро при големи тест примери. Предноста е во тоа што овој алгоритам е пофлексибилен, па како таков дозволува и негативни тежини и додатно може да најде неограничени циклуси на негативни тежини (што ќе објасниме подоцна).

Начинот на кој овој алгоритам работи е доста прост и е уште полесен за пишување во код. За разлика од Dijkstra, тука не бележиме кое теме е веќе посетено (бидејќи ќе ги посетуваме повеќе пати), туку само ја бележиме далечината на темињата од изворот. Додатно, може да го бележите изворот за секое теме (исто како кај Dijkstra) што може да се најде корисно при реконструкција на патот (што е потребно во задачата која ја решаваме).

За почеток, далечините на сите темиња ги иницијализираме на некој огромен број, освен за изворот чија далечина е 0. Потоа, за сите врски `(x,y)` (што значи врска од темето `x` кон темето `y`) со тежина `z`, проверуваме дали `dist[x] + z` е помало од `dist[y]`. Доколку е помало, тогаш го менуваме `dist[y]` и `source`-от соодветно. За поопширно објаснување како работи овој алгоритам (и следење на пример чекор по чекор), ви го препорачувам [ова видео](https://www.youtube.com/watch?v=iTW2yFYd1Nc).

На овој начин, редоследот по кој ги бираме врските би бил доста битен, но дури и тогаш алгоритмот не би го открил најкраткиот пат секогаш, бидејќи не се разгранува ни прилично доволно за да ги провери сите патишта. Како решение на овој проблем, го пуштаме горенаведениот алгоритам да работи `N-1` пати, каде `N` е бројот на темиња во графот. Со завршувањето на `N-1` итерации, овој алгоритам би го открил најкраткиот пат кон секое теме.

## Негативни циклуси

Една забелешка кај графови со негативни тежини е дека не секој граф има најкраток пат. Да го разгледаме следниов граф:

![](http://i.stack.imgur.com/pNLTw.png)

Во дадениот пример, како најкраток пат од 1 до 2 може да се земе патот `1->2` со далечина -20. Уште пократок пат би бил патот `1->2->3->2` со далечина -25. Уште пократок пат од тоа би бил `1->2->3->2->3->2` со далечина -30. Всушност секогаш кога ние додаваме `2->3->2` во патот, ние ја намалуваме должината за 5. Направете го тоа бесконечен број пати и добивате пат со бесконечно мала должина. За вакви графови се вели дека немаат најкраток пат (дека не е можно да се одреди најкраткиот пат).

За среќа, алгоритмот на Bellman-Ford ни овозможува лесно да детектираме и да ги пријавиме ваквите циклуси. Бидејќи алгоритмот гарантира дека после N-1 итерации ќе го пронајде најкраткиот пат од изворот до секое теме, потребно е ние да направиме само уште една итерација. Доколку новата итерација повторно најде некој пократок пат, значи дека овој граф има бесконечен негативен циклус.

## Пишување на код, решавање на задачата

Најпрвин ги пишуваме податочните структури и го средуваме инпутот на задачата. Графот го запишуваме во низа од вектори од парови (бидејќи работиме со тежини). Додатно имаме низи `dist` (за далечина) и `source` (за памтење на изворот за реконструкција). При внес, броевите ги намалувам за 1 за да биде графот од 0 до `N-1` наместо од 1 до `N` (бидејќи сум навикнат да пишувам for циклуси што почнуваат од 0). Додатно, `dist` низата ја иницираме на 9999999, освен изворот кој го иницираме на 0.

```
int n,m,a,b,c,s,t;
scanf("%d%d",&n,&m);

vector<pair<int,int> > graph[3000];
int dist[3000];
int source[3000];

for(int i=0;i<3000;++i)
    dist[i]=9999999;

for(;m;--m)
{
    scanf("%d%d%d",&a,&b,&c);
    graph[--a].push_back(make_pair(--b,c));
}

scanf("%d%d",&s,&t);
dist[--s]=0;
```

Со ова инпутот ни е завршен и вредностите се иницијализирани, така да можеме да преминеме на наоѓањето на најкраток пат. Почнуваме со for циклус кој ќе изброи `N-1` итерации на алгоритмот. Внатре во тој for циклус, со друг for циклус го изминуваме секое теме, чии што врски ги изминуваме со трет for циклус. На овој начин ги изминуваме сите можни врски во графот. Се што преостанува е да провериме за секоја можна врска, дали таа наоѓа нов, пократок пат, од оној што го веќе знаеме.

Заради природата на овој алгоритам, доколку сакате можете графот да го запишете само како низа од врски, каде што врската би била претставена со 3 параметри: двете точки кои се поврзани и тежината на врската. На овој начин алгоритмот би работел со `O(N*M)` сложеност, додека со матрица на поврзаност алгоритмот работи со `O(N^3)` сложеност.

```
for(int iteracii=0;iteracii<n-1;++iteracii)
    for(int i=0;i<n;++i)
        for(int j=0;j<graph[i].size();++j)
            if(dist[i] + graph[i][j].second < dist[graph[i][j].first])
            {
                source[graph[i][j].first] = i;
                dist[graph[i][j].first] = dist[i] + graph[i][j].second;
            }
```

За крај, треба да провериме дали постои некој циклус, така да правиме уште една додатна итерација која веднаш пријавува доколку сретне пократок пат и го прекинува програмот.

```
for(int i=0;i<n;++i)
    for(int j=0;j<graph[i].size();++j)
        if(dist[i] + graph[i][j].second < dist[graph[i][j].first])
        {
            printf("Impossible");
            return 0;
        }
```

Доколку не е пронајден циклус, тогаш потребно е да ја испечатиме далечината на патот и со помош на source да го измериме бројот на чекори.

```
printf("%d ",dist[--t]);

int counter=0;

while(t!=s)
{
    ++counter;
    t=source[t];
}

printf("%d",counter);
```

Со ова задачата е решена.