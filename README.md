### Приветствую путник 👋

На момент написания, являюсь студентом.

🔭 В сферу интересов входят языки: C++, C(Си), Python.

Си уже знаю на достаточном, **по моим оценкам**[^1], уровне, по этому сейчас активно изучаю C++; из-за обширности последнего - python не в приоритете, несмотря на то, что уже немного изучал.

---
Некоторые из моих работ:

*Прим: названия ведут к README указанного проекта, где рядом, в той же директории, будут лежать исходники.*
- [Bash Utilities](./Projects/BashUtils/README.md) - проект, в котором реализовал свой `cat` и `grep` на Си. Один из самых первых серьёзных проектов, из-за чего логика весьма спутана, нейминг не годиться для соответствия с концепцией "чистый код".

- [Decimal](./Projects/Decimal/README.md) - первый хоть сколько-то большой и трудный проект. В нём реализовывал свой тип данных с плавающей запятой, который реализован на основе `int` массива из 4-х элементов(предполагается, что они 32-ух битные). В этом проекте уже лучше организована логика кода, и хоть нейминг всё ещё оставляет желать лучшего, зато уже появляются комментарии, которые помогают ориентироваться в коде; к тому же, уже есть тестирование проекта на основе `check.h`.

- [Matrix_C](./Projects/Matrix_C/README.md) - один из последних проектов на Си. Является реализацией 2D матрицы, и операций с ней связанных.

- [Matrix_CPP](./Projects/Matrix_CPP/README.md) - первый серьёзный C++ проект. Фактически, переписанный Matrix_C но на C++ [^2]. Здесь уже намного больше уделял времени на нейминг, который бы позволил сразу понять *что* и *зачем*; а так же, сделал тесты при помощи библиотеки `gtest.h`.

- [CTetris](./Projects/CTetris/README.md) - в проекте создавался **консольный** тетрис на языке Си. Была попытка разделить функциональность на более общий код и конкретно код для тетриса; чтобы, например, можно было заменить основной файл с отображением графики, без изменений остального кода[^3]; однако, получилось мало эффективно. Помимо прочего, основную логику игры организовал в виде конечного автомата (реализовал как двумерный массив указателей на функции; где строки - состояния, а столбцы - действия); схему КА можно увидеть в README проекта. Так-же взаимодействие с основной структуры игровой информации, `GameInfo` и `ExtGameInfo`, организовал через паттерн singleton (насколько это возможно в языке Си и насколько смог).

- [ExchangeService](https://github.com/DeathLore/ExchangeService) - work in progress. Терминальное клиент-серверное приложение для обмена валют (RUB, USD). 


<!--
**DeathLore/DeathLore** is a ✨ _special_ ✨ repository because its `README.md` (this file) appears on your GitHub profile.

Here are some ideas to get you started:

- 🔭 I’m currently working on ...
- 🌱 I’m currently learning ...
- 👯 I’m looking to collaborate on ...
- 🤔 I’m looking for help with ...
- 💬 Ask me about ...
- 📫 How to reach me: ...
- 😄 Pronouns: ...
- ⚡ Fun fact: ...
-->

### [Резюме](./CV.pdf).


[^1]: На данный момент не вижу смысла ещё сильнее углубляться. Возможно, как хорошо изучу C++, ещё буду изучать Си.

[^2]: По этому, чтоб не дублировать те же комментарии - убрал их; да и сама парадигма ООП делает код достаточно структурированным, легко читаемой.

[^3]: Чтобы было возможно легко при сборке выбирать вывод графики в консоли или в X сессии в отдельном окне.
