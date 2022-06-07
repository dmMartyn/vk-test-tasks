//1. Предложите вариант исправления фрагмента кода:

void process(FILE* f); // сигнатура зафиксирована

void use_file(const char* name) 
{
	FILE* f = fopen(name, "w");
	process(f); // использование f, при котором может быть выброшено исключение

	fclose(f);
}

/* Ответ: Вариант исправления – обернуть вызов функции process в блок try-catch
 для того чтобы в любом случае отработал вызов fclose и следовательно не было
 потери данных и утечки ресурсов.*/

void process(FILE* f); // сигнатура зафиксирована

void use_file(const char* name) 
{
	FILE* f = fopen(name, "w");

	if(!f) 
	{
        printf("File opening failed");
        return;
	}

	try
	{
		process(f); // использование f, при котором может быть выброшено исключение
	}	
	catch(…)
	{
		printf("Exception!\n");
	}

	fclose(f);
}


//2. Предложите алгоритм для удаления дубликатов (или выбора уникальных элементов) из вектора. 
//Оцените временную и пространственную сложность.

// n - размер вектора
//Если надо вручную написанный алгоритм, то что-то такое:

template<class T>
void manualRemoveDublicates(std::vector<T>& vecT)
{
	std::sort(vecT.begin(), vecT.end());// O(n*log(n))

	// O(n)
    int n = 0;
    for(int i = 1; i < vecT.size(); ++i)
    {
        if (vecT[n] != vecT[i])
        {
            vecT[++n]=vecT[i];
        }
    }

	vecT.resize(n+1);//сложность линейная относительно разности текущего размера и желаемого
}


//В прод конечно же велосипелить бы не стал и написал примерно что-то такое:

template<class T>
void autoRemoveDublicates(std::vector<T>& vecT) 
{
    std::sort(vecT.begin(), vecT.end());// O(n*log(n))
    auto last = std::unique(vecT.begin(), vecT.end());// O(n) (в точности std::distance(vecT.begin(),,vecT.end())-1)
    vecT.erase(last, vecT.end());// O(n)
}

//Итого, если массив отсортирован, то сложность вычислений O(n)
//Если не отсортирован, то упираемся в сложность сортировки - O(n*log(n))
//Для обоих алгоритмов затраты памяти - O(n)

//3. Сколько раз эта программа напечатает слово "hello"? Обоснуйте свой ответ.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) 
{
	printf("hello");
	fork();
	printf("\n");

	return 0;
}

/*Ответ: Программа напечатает слово "Hello" 2 раза.
Первый вызов printf копирует "Hello" в буфер стандартного вывода, а поскольку в вызове нет 
символа перехода на новую строку, то в терминал в этот момент ничего не выводится. 
Далее после вызова fork() появляется два отдельных процесса с одним и тем же содержимым в 
буфере stdout. Затем каждый из процессов доходит до вызова printf с символом перехода на 
следующую строку и в терминал печатает "Hello".*/
