prog‬‬‬‬: MainSecond.o Pokemon.o BattleByCategory.o LinkedList.o MaxHeap.o
	gcc MainSecond.o Pokemon.o BattleByCategory.o LinkedList.o MaxHeap.o -o prog
MainSecond.o: MainSecond.c Pokemon.h BattleByCategory.h
	gcc -c MainSecond.c
Pokemon.o: Pokemon.c Pokemon.h Defs.h
	gcc -c Pokemon.c
BattleByCategory.o: BattleByCategory.c BattleByCategory.h Defs.h LinkedList.h MaxHeap.h
	gcc -c BattleByCategory.c
LinkedList.o: LinkedList.c LinkedList.h
	gcc -c LinkedList.c
MaxHeap.o: MaxHeap.c MaxHeap.h
	gcc -c MaxHeap.c
