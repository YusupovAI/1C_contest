## Typing.

### Компиляция.

`g++ -std=c++17 main.cpp Trie.cpp WindowManager.cpp -lncurses -o main`

### Интерфейс.

Для того чтобы начать добавлять слова нужно ввести `Add:`, и затем начать ввод с новой строки.

Чтобы начать писать слово, надо ввести `Type:`, и с новой строки начать писать слово.

Если хотите сделать автодополнение, нажмите `Tab`. Чтобы его подтвердить нажмите `Tab` ещё раз. В противном случае просто продолжайте ввод, слово выведется с новой строки.

### Мнение о задаче.

Я хотел сделать красивый интерфейс, чтобы когда пользоветель отменял автодополнение, слово выводилось не с новой строки, а удалялись старые символы. Изначально я хотел исполнить такой хак: дублировать ввод, и когда пользователь отменяет автодополнение убирать символы из `stdout`. Этот хак остался и в изменённом решении, но я так и не смог сделать отмену ввода (в силу нехватки времени). Для того, чтобы подавить ввод пользователя, и чтобы не ждать, когда он нажмёт `Enter` я использовал библиотеку `curses`. Разумным будет такой вопрос: "В решении мы очень часто сбрасываем буфер, наверное это очень дорого?" Действительно это непростая операция, но вряд ли производительность программы не упрётся в скорость ввода пользователя. 

### Алгоритмические детали.

Все слова хранятся в боре, в узлах бора хранятся поля `ended_, max_endex_`, в которых соответственно записано сколько слов оканчиваются конкретно в данном и узле, а также максимальная величина в поддереве. Эти поля несложно поддерживать корректными в методе `Add`. Как искать автодополнение? Если у нас есть какой-то префикс, и его состояние в боре, то можно просматривать всех детей узла, и спускаться в того, где `max_ended_` больше. Останавливаемся мы в тот момент, когда текущий узел самый выгодный среди себя и своих потомков. 