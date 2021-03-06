Невообичаен натпревар за Codeforces. 6 задачи, 150 минути, само за втора дивизија. Бидејќи влегов во првата дивизија минатиот натпревар, не учествував овој пат, но сепак ги разгледав задачите. Првите три задачи беа невообичаени за Codeforces натпревар, кои не бараа познавање од напредни алгоритми туку само имаа незгодни имплементации или бараа многу оптимизации. Од останатите задачи (кои сеуште ги немам решено), четвртата се базираше на динамичко и веројатност додека последните две беа ad hoc решенија.

## А - Vitaly and Strings
[Текст од задачата](http://codeforces.com/problemset/problem/518/A)

За дадени два стринга `s` и `t` со иста должина кои се состојат само од мали латинични букви, каде што `s` е лексикографски помал стринг од `t`, да се најде дали постои некој стринг измеѓу тие два (лексикографски помал од `s` но поголем од `t`), и доколку постои да се испечати.

Лексикографско споредување на два стринга се врши буква по буква, од првата буква. Доколку првата буква на првиот стринг е поголема од првата буква на вториот стринг, тогаш првиот стринг е лексикографски поголем. (`baa > aaa`). Доколку првите две букви се еднакви, се споредуваат вторите две букви. (`aba > aaa`). Така се споредува додека не стигнеме до крајот на некој стринг. Доколку немаат различни букви, тогаш стринговите се еднакви и лексикографски.

Доколку имаме некој даден стринг (пример, `abc`), наредниот лексикографски стринг е кога последната буква ја зголемуваме за 1. Во овој случај, `abd` е следниот стринг. Доколку пак буквата што треба да ја зголемиме е `z` (пример, `abz`), тогаш таа буква ја ставаме да е `a`, и ја зголемуваме следната буква (во тој пример, добиваме `aca`).

За да нема стрингови помеѓу стринговите `s` и `t`, тогаш s мора да е претходник на `t` (наредниот лексикографски стринг на `s` да е `t`). Така да само е потребно да го провериме овој услов. Доколку наредниот стринг на `s` е `t`, тогаш не постои таков стринг. Во спротивно, го печатиме наредниот стринг.

Зголемувањето на стрингот го правиме рекурзивно со функција која ја повикуваме на последната буква, која ја зголемуваме за 1. Доколку последната буква е `z`, тогаш ја ставаме да е еднаква на `a` функцијата ја повикуваме на следната буква. Кога ќе го зголемиме стрингот, само ги споредуваме и печатиме резултат.

[Решение во C++](http://codeforces.com/contest/518/submission/10022971)

## B - Tanya and postcard
[Текст од задачата](http://codeforces.com/problemset/problem/518/B)

Повторно стрингови. Тања има дадено порака (`string s`), и весник (`string t`). Потребно е со сечење на буквите од весникот да ја добие саканата порака. Доколку искористи буква од весникот, и таа е со точната големина, таа се радува, но доколку буквата е со погрешна големина (пример - се бара мала буква, а таа има само голема во весникот), таа е тажна. Од вас се бара да проверите колку пати таа ќе е тажна, а колку пати ќе се радува. Потребно е да се максимизира колку пати ќе се радува.

За броење на буквите користиме мапи. Потребни ни е да броиме колку пати се појавува секоја буква во двата стринга посебно. Едниот бројач е case sensitive, каде што разликуваме големи од мали букви, а во вториот бројач ги броиме исто (пример, имаме еден бројач за `a` и `A`). Така да потребни ни се вкупно 4 мапи, од тип `<char, int>`. Двете case sensitive мапи ги пополнуваме со буквите кои ги читаме од стрингот, а за другите две мапи ги претвораме сите букви во мали букви.

Кога веќе ги имаме изброено буквите, тогаш прво проверуваме колку букви можеме да искористиме од весникот за стрингот со потребната големина, а потоа и со погрешна големина, и за двете чуваме посебни бројачи.

[Решение во C++](http://codeforces.com/contest/518/submission/10054805)

## C - Anya and smartphone

[Текст од задачата](http://codeforces.com/problemset/problem/518/C)

Имаме смартфон со `n` апликации, од кои секоја има своја икона на екранот. Екранот може да прикаже најмногу `k` апликации во исто време. Доколку има повеќе од `k` апликации, тогаш тој ги поделува според страници така што првите `k` апликации се на првата страница, вторите `k` апликации на втората, итн. Сите апликации се нумерирани од 1 до `n` и ни е даден нивниот првобитен редослед. Но нивниот редослед се менува со текот на користење, така што кога ќе пуштиме некоја апликација, таа се поместува едно место понапред (бидејќи е почесто користена).

На нас ни е дадена првобитната листа на апликации, и редоследот во кој ќе ги пуштаме (можно е една апликација да ја пуштиме повеќе пати). Треба да изброиме со колку допира ќе се изврши тоа. За секоје менување на страница ни треба 1 допир и за пуштање на апликација 1 допир. Кога ќе завршиме со користење на една апликација, повторно се враќаме на првата страница.

На прв поглед многу лесна задача за brute force имплементација. Секогаш кога некоја апликација ќе се пушти, проверуваме на која позиција е (за да знаеме на која страница е, колку допири ни се потребни за неа). Потоа проверуваме која апликација е пред неа, и им ги заменуваме местата. Проблемот во ова е што имаме можни 100,000 апликации и 100,000 пуштања на истите, така да доколку користиме линеарно пребарување и секогаш се отвора последната апликација, тогаш сложеноста на овој алгоритам може да достигне до 20,000,000,000 операции, нешто што не е изводливо во една секунда.

Затоа чуваме две низи: една што ни покажува на која позиција која апликација стои, и друга што ни покажува која апликација на која позиција е. Така да кога прочитаме некоја апликација, можеме веднаш да провериме на која позиција е и да изброиме колку допири треба (при делење со `k`), да видиме која апликација се наоѓа на едно место пред неа во низата за позиции и да го смениме местото на двете апликации во двете низи.

[Решение во C++](http://codeforces.com/contest/518/submission/10054893)
