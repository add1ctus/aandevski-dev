Уште еден (најверојатно) unrated натпревар за TopCoder. Успеав да ја решам првата задача (која впрочем беше тешка за разбирање но имаше многу интересно решение) и со тоа да завршам на 328-мото место од ~530 натпреварувачи во првата дивизија. Како и вообичаено, втората задача беше решена од едвај 30 учесника, додека третата немаше ниту едно испратено решение. Да ја разгледаме првата задача.

## 250 - The permutation game

[линк од задачата](http://pastebin.com/nnszYXfK

Изгубив добри 15 минути да сфатам што се всушност случува во задачата и што се бара. Имено, станува збор за игра која ја играат двајца. Имате дадено број `N`. Првиот играч бира број `X`, па потоа вториот играч треба да направи пермутација на броевите од 1 до `N` (пермутација е било кое подредување на броевите така што ниту еден број не се појавува повеќе од еднаш). Потоа, таа пермутација се применува на бројот `X` пати, почнувајќи од бројот 1.

![5 извршени пермутации на 3,1,2, почнувајќи од 1](https://aandevski.files.wordpress.com/2015/03/untitled.png)

Да разгледаме како изгледа тоа:

Можеме за пример да ја избереме пермутацијата `3,1,2` (`N=3`), и да ја извршиме 5 пати (`X=5`).

Бидејќи се почнува од бројот 1, при првото извршување го добиваме првиот број во пермутацијата, 3. Со второто извршување го добиваме третиот број во пермутацијата, 2. Со следното извршување се добива 1, па 3, за на крајот да го добиеме бројот 2, кој е резултатот.

Во задачата на вас ви е даден број `N`, големината на пермутацијата. Од вас се бара да го најдете најмалиот број `X`, така што резултатот ќе изнесува 1 за секоја можна пермутација.

Сега, кога веќе ја разбравме конечно задачата, можеме да преминеме на нејзиното решавање. Еден од советите кои најчесто ги давам е секогаш гледајте да ја упростите задачата што повеќе пред да почнете да пишувате код. Доколку во задачата се бара да тестираме `N!`, не мора да значи дека ние ќе ги тестираме нив. Начинот на кој доаѓаме до идеи за упростување е со решавање на неколку тест примери рачно и барање на некои повторувања / идеи., вештина која најдобро се стекнува со континуирано вежбање. Оваа задача е добар пример за тоа.

Првата забелешка е дека за била која пермутација, доколку бројот 1 е првиот број во пермутацијата, тогаш тој број нема никогаш да се смени за било колку извршувања. Тоа е така бидејќи бројот 1 се наоѓа на позицијата 1. Лесно е да се види дека кога некој број се наоѓа на својата позиција, никогаш нема да се поместиме од таа позиција. Но да видиме што се случува кога некој друг број се наоѓа на својата позиција. На пример доколку бројот 2 се наоѓа на својата позиција, ние воопшто не можеме да стигнеме до тој број. Така да на пример во пермутацијата `3,2,4,1` ние никогаш нема да го посетиме бројот 2, туку само ќе шетаме помеѓу позициите 1,3 и 4. Исто така и за пример `3,2,1,4`, ние никогаш нема да стигнеме до позициите 2 и 4(бидејќи се наоѓа ист број на иста позиција), туку само ќе шетаме помеѓу броевите 1 и 3.

Со анализа на некој пример каде што имаме пермутација со `N` бројки (од кои ниту една не се наоѓа на својата позиција), тогаш можеме да приметиме дека се потребни `N` извршување за да се вратиме назад на почетната позиција, 1. Но доколку имаме `K` броеви кои се на својата позиција (освен бројот 1), тогаш е потребно `N-K` извршувања за да добиеме 1 како резултат.

Така да на пример за `N=4`, знаеме дека постојат 4 типа на пермутации : каде што сите се на свое место, или каде што 2,3 или 4 броја не се на своето место. Бидејќи рековме дека за пермутацијата каде што сите се на свое место секогаш е резултатот 1, таа нема да ја броиме. Од тука произлегува правилото дека за `N` броеви, имаме `N-1` типа на пермутации кои ќе ги нумерираме од 2 до `N` (според бројот на броеви што не се на своето место). Да не заборавиме, тој број на пермутацијата исто значи и колку извршувања треба за да се вратиме на почетната позиција.

На нас ни е потребно да откриеме колку најмалку извршувања се потребни, така што сите пермутации би резултирале со 1. Бидејќи знаеме дека пермутацијата со 2 исти има резултат 1 на секои две извршувања, пермутацијата со 3 исти има резултат 1 на секои три извршувања, итн, на нас ни е потребно да најдеме број кој е делив со сите броеви од 2 до `N`. Или со други зборови, решението е НЗС на сите броеви од 2 до `N` по модул 100,000,007.

Доколку ја решавате задачата во втората дивизија (и имате `N` максимум 30), тогаш можете да пресметате НЗС на било кој начин. Но доколку пресметувате НЗС на 100,000 броеви, тогаш е потребна додатна оптимизација. Да се занимаваме малку со математика...

Прости броеви се броеви кои имаат само 2 делитела: 1 и самиот тој број. Пример за прости броеви се 2, 5, 7, 11, 13 и 17. Има бесконечно многу прости броеви. Интересно својство на простите броеви е што секој број може да се разложи на производ од прости броеви. Така на пример бројот 8 = 2 * 2 * 2 и бројот 18 = 2 * 3 * 3. Како можеме да го искористиме ова за НЗС? Да ги разгледаме внимателно овие броеви:

```
8 = 2 * 2 = 2^3
18 = 2 * 3 * 3 = 2 * 3^2
```

Овие два броја можат да се добијат од броевите 2 и 3. Притоа, најголемиот степен на бројот 2 е 3, а најголемиот степен на бројот 3 е 2. Доколку ги помножиме броевите со нивните најголеми степени, `2^3 * 3^2 = 72`, што е НЗС на броевите 8 и 18. Истото може да се примени и со повеќе броеви, при што ги разложуваме сите и го гледаме најголемиот степен на секој прост број.

Но сепак, доколку разложуваме 100,000 броеви, тоа би траело многу време. Да видиме за пример бројот 2 колкав степен има во различни броеви. Првата забелешка е дека во сите непарни броеви, степенот на 2 е 0 (бидејќи не се деливи со 2). Кај другите броеви, тоа е некој број поголем или еднаков на 1. Доколку ги испишете броевите од 2 до 18, можете да приметите дека степенот `2k` е присутен само кај броевите помеѓу `2^k` и `2^(k+1)` (без да го вклучиме бројот `2^(k+1)`). Така да за броевите од 2 до 18, најголемиот степен е `2^4`, кој се појавува кај броевите 16 и 18 (двата поголеми или еднакви на `2^4`). Истото важи и за било кој друг број. Така да, знаеме дека за сите броеви од 1 до `N`, можеме да го добиемо степенот `k` за бројот `x` така што ќе го најдеме најголемиот `x^k` кој е помал или еднаков на `N`.

Според овој заклучок, за да ги добиеме степените на сите прости броеви, треба да ги степенуваме се додека не стигнеме до број поголем од `N`. Но за тоа, прво е потребно да ги генерираме сите прости броеви помали од `N`, што се постигнува најлесно со Ератостеново сито.

```
vector<int> prosti;
bool eProst[100000];

memset(eProst,true,100000);
eProst[0]=eProst[1]=false;


for(int i=2;i<100000;i++)
    if(eProst[i])
    {
        prosti.push_back(i);
        for(int k=i+i;k<100000;k+=i)
            eProst[k]=false;
    }
```

Што ни преостанува е за сите прости броеви, да го најдеме најголемиот степен на тој прост број што е помал од `N` и да го додадеме во резултатот. Притоа ставаме модул за секое додавање, за да не направиме overflow на променливата.

```
long long result=1;

for(int i=0;i<prosti.size() && prosti[i]<=N;i++)
{
    long long temp=prosti[i];
    while(temp<=N)
        temp*=prosti[i];
    result*=(temp/prosti[i])%MOD;
    result%=MOD;
}
```

По извршување на овој код, во променливата `result` го имаме резултатот, со што е решена задачата.

Успеавме да стигнеме од проверка на 100,000 пермутации (доколку ве интересира колку различни пермутации има - бројот има 456,574 цифри) до проверка на ~9,500 броеви (толку прости броеви има помали од 100,000) во 20 линии код.