/***********************************************************************\
*                    кафедра № 304 2 курс 3 семестр информатика			*
*-----------------------------------------------------------------------*
*	Project type : solution												*
*	Project name : LW5													*
*	File name    : main.cpp												*
*	Language     : c/c++												*
*	Programmers  : Плоцкий Б.А. Раужев Ю. М.							*
*	Created      : 17/11/22												*
*	Last revision: --/11/22												*
*	Comment(s)   : 														*
*																		*
*	Программно реализовать дек в виде двунаправленного дека согласно	*
*	варианту задания. Выполнение операций организовать с помощью меню:	*
*	•	 создание дека;													*
*	•	 вывод на экран или в файл значений элементов дека с их			*
*		индексами (номерами);											*
*	•	 очистка дека, 													*
*	•	дополнительные операции(согласно варианту задания):				*
*		1.	выборка элемента из начала дека;							*
*		4.	добавление элемента в конец дека;							*
*																		*
\***********************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/****************************************************************
*					   К О Н С Т А Н Т Ы						*
****************************************************************/

// если нужна печать по каждому действию (0, 1)
#define NEED_PRINT_DEBUG 1

// минимальное и максимальное значение ввода элементов
#define MAX_VALUE 1000.0
#define MIN_VALUE -1000.0

// минимальное и максимальное значение ввода элементов
#define MAX_VALUE_INSERT 100000
#define MIN_VALUE_INSERT 0

// вывод в консоль сообщения
#define INFO(str) if(NEED_PRINT_DEBUG) cout<<"\t"<<str<<"\n";

// не существует ли дек
#define DEQ_NOT_EXSISTS(f_name)\
	if(!deq_exists(_deq)){\
		cout << "\t" << f_name << ": дек не существует\n";\
		return;\
	}

// не существует ли дек, возвращаем ret_obj
#define DEQ_NOT_EXSISTS_RET(f_name, ret_obj)\
	if(!deq_exists(_deq)){\
		cout << "\t" << f_name << ": дек не существует\n";\
		return ret_obj;\
	}

// пуст ли дек
#define DEQ_EMPTY(f_name)\
	if(deq_is_empty(_deq)){\
		cout << "\t" << f_name << ": дек пуст\n";\
		return;\
	}

// пуст ли дек, возвращаем ret_obj
#define DEQ_EMPTY_RET(f_name, ret_obj)\
	if(deq_is_empty(_deq)){\
		cout << "\t" << f_name << ": дек пуст\n";\
		return ret_obj;\
	}

// заполнение len элементов элементом symb
#define OUT_W(symb, len) fixed << setfill(symb) << setw(len)

// коды для взаимодействия пользователья с программой
enum class input_codes
{
	exit = 1,
	template_program,
	deq_create,
	deq_push_back,
	deq_pop_back,
	deq_get_front,
	deq_print,
	deq_delete,
	clear_console
};

// строка с коммандами
const char* command_str =
"\nВведите номер комманды:\n\
\t1. Выйти из программы.\n\
\t2. Запустить пример готового алгоритма.\n\
\t3. Создать дек.\n\
\t4. Добавить элемент в конец дека.\n\
\t5. Удалить элемент с конца дека.\n\
\t6. Выбрать элемент из начала дека.\n\
\t7. Распечатать дек.\n\
\t8. Удалить дек.\n\
\t9. Очистить консоль.";

/****************************************************************
*              П Р О Т О Т И П Ы   Ф У Н К Ц И Й                *
****************************************************************/

/****************************************************************
*        В С П О М О Г А Т Е Л Ь Н Ы Е   Ф У Н К Ц И И          *
****************************************************************/

// ввод и проверка значений
template<typename T = int>
T input_and_check(
	T _min,
	T _max,
	const char* welcome_str,
	const char* err_str = "Было введено некорректное значение"
);

// функция ведения диалога с пользователем
template<typename T = double>
void dialog();

// пример работы с деком
void example_program();

/****************************************************************
*							   N O D E					        *
****************************************************************/

// элемент двусвязного дека
template<typename T>
struct node
{
	T m_data;		// информация
	node* m_next;	// указатель на следующий элемент
	node* m_prev;	// указатель на предыдущий элемент

	// конструктор
	node() :m_next(NULL), m_prev(NULL), m_data(T(0)) {};
};

// создание элемента дека
template<typename T>
node<T>* node_create(
	T _data,		// информация для хранения в элементе
	node<T>* _next,	// указатель на следующий элемент
	node<T>* _prev	// указатель на предыдущий элемент
);

// удаление элемента дека
template<typename T>
void node_delete(
	node<T>*& _node	// ссылка на элемент
);

/****************************************************************
*							   L I S T					        *
****************************************************************/

// дек
template<typename T>
struct deq
{
	node<T>* m_begin;	// указатель на первый элемент
	node<T>* m_end;		// указатель на элемент после последнего
	int m_size;			// количество элементов в деке

	// конструктор
	deq() :m_begin(NULL), m_end(NULL), m_size(0) {};
};

// пуст ли дек
template<typename T>
bool deq_is_empty(
	deq<T>* _deq	// указатель на дек
);

// существует ли дек
template<typename T>
bool deq_exists(
	deq<T>* _deq	// указатель на дек
);

// функция инициализации дека
template<typename T>
deq<T>* deq_create();

// функция добавления элемента в конец дека
template<typename T>
void deq_push_back(
	deq<T>* _deq,	// указатель на дек
	T data			// информация для хранения в элементе
);

// функция удаления элемента из конца дек
template<typename T>
void deq_pop_back(
	deq<T>* _deq	// указатель на дек
);

// выборка элемента из левого конца (начала)
template<typename T>
node<T>* deq_get_front(
	deq<T>* _deq	// указатель на дек
);

// удаление дека
template<typename T>
void deq_delete(
	deq<T>*& _deq	// адресс дек
);

// печать дека
template<typename T>
void deq_print(
	deq<T>* _deq,				// печатаемый дек
	ostream& _out_stream = cout	// поток для печати
);

/****************************************************************
*                Г Л А В Н А Я   Ф У Н К Ц И Я                  *
****************************************************************/

int main()
{
	setlocale(LC_ALL, "ru");

	// запуск диалога с пользователем
	dialog();

	return 0;
}

/****************************************************************
*              Р Е А Л И З А Ц И Я   Ф У Н К Ц И Й              *
****************************************************************/

/****************************************************************
*        В С П О М О Г А Т Е Л Ь Н Ы Е   Ф У Н К Ц И И          *
****************************************************************/

// ввод и проверка значений
template<typename T>
T input_and_check(T _min, T _max,
	const char* welcome_str, const char* err_str)
{
	// размер массива
	T num;

	// вывод сообщения
	cout << welcome_str << "\n";
	cin >> num;

	// если было введено некорректное значение
	if (num > _max || num < _min) {
		// если была введена не цифра
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		// отчистка консоли
		//system("cls");
		cout << err_str << "\n";

		// рекурсивное обращение
		num = input_and_check(_min, _max, welcome_str, err_str);
	}
	return num;
}

// функция ведения диалога с пользователем
template<typename T>
void dialog()
{
	// переменная содержащая коды действий
	input_codes in_code;

	// элемент для вставки
	T elem;

	//позиция вставки
	int pos_to_insert;

	// переменная дека
	deq<T>* dq = NULL;

	// временный элемент 
	node<T>* temp = NULL;

	do
	{
		// запрос у пользователя следующих действий
		in_code = input_codes(input_and_check(1, 9, command_str));

		// запуск соответствующих функций
		switch (in_code)
		{
		case input_codes::exit:
			INFO("Произведен выход");
			break;

		case input_codes::template_program:
			INFO("Запуск примера кода");
			example_program();
			break;

		case input_codes::deq_create:
			if (!deq_exists(dq))
				dq = deq_create<T>();
			else
				INFO("DIALOG: Дек уже существует");
			break;

		case input_codes::deq_push_back:
			elem = input_and_check(MIN_VALUE, MAX_VALUE,
				"Введите элемент для вставки в конец");
			deq_push_back(dq, elem);
			deq_print(dq);
			break;

		case input_codes::deq_pop_back:
			deq_pop_back(dq);
			break;

		case input_codes::deq_get_front:
			temp = deq_get_front(dq);
			if (temp)
			{
				cout << "Передний элемент дека: " << temp->m_data << endl;
				deq_print(dq);
			}
			break;

		case input_codes::deq_print:
			// печать дека
			deq_print(dq);
			break;

		case input_codes::deq_delete:
			// удаление дека
			deq_delete(dq);
			break;

		case input_codes::clear_console:
			system("cls");
			break;

		default:
			INFO("Неизвестный код")
				break;
		}

	} while (
		// пока пользователь не захотел выйти из программы
		// или пока не запустил пример программыЫ
		in_code != input_codes::exit &&
		in_code != input_codes::template_program
		);
}

// пример работы с деком
void example_program()
{
	// создание дека
	deq<double>* dq = deq_create<double>();

	// добавление элементов в конец
	deq_push_back(dq, 5.2);
	deq_push_back(dq, 1.3);
	deq_push_back(dq, 5.1456);
	deq_push_back(dq, 45656.9);
	deq_push_back(dq, 0.456);

	// вывод дека
	deq_print(dq);

	// элемент в начале
	node<double>* front = deq_get_front(dq);
	cout << "Передний элемент дека: " << front->m_data << endl;

	// удаление элементов дека с конца
	deq_pop_back(dq);
	deq_pop_back(dq);
	deq_pop_back(dq);
	deq_pop_back(dq);

	// вывод дека
	deq_print(dq);

	// удаление дека
	deq_delete(dq);
}

/****************************************************************
*							   N O D E					        *
****************************************************************/

// создание элемента дека
template<typename T>
node<T>* node_create(T _data, node<T>* _next, node<T>* _prev)
{
	// создаем первый элемент в деке
	node<T>* new_node = new node<T>;

	// настраиваем только что созданный элемент
	new_node->m_data = _data;
	new_node->m_next = _next;
	new_node->m_prev = _prev;

	INFO("Элемент был создан");

	return new_node;
}

// удаление элемента дека
template<typename T>
void node_delete(node<T>*& _node)
{
	// разрыв связей с другими элементами
	_node->m_data = T(0);
	_node->m_next = NULL;
	_node->m_prev = NULL;

	// обнуление памяти
	delete _node;

	// обнуление адреса
	_node = NULL;

	INFO("Элемент был удален");
}

/****************************************************************
*							   L I S T					        *
****************************************************************/

// пуст ли дек
template<typename T>
bool deq_is_empty(deq<T>* _deq)
{
	return _deq->m_begin == NULL;
}

// существует ли дек
template<typename T>
bool deq_exists(deq<T>* _deq)
{
	return _deq != NULL;
}

// функция инициализации
template<typename T>
deq<T>* deq_create()
{
	// выделение памяти под дек
	deq<T>* _deq = new deq<T>;

	INFO("Дек был создан");

	// возвращение адресса дека
	return _deq;
}

// функция добавления элемента в конец дека
template<typename T>
void deq_push_back(deq<T>* _deq, T data)
{
	// выход, если дек не существует
	DEQ_NOT_EXSISTS("PUSH");

	// элемент добавления
	node<T>* new_node;

	// если дек пуст
	if (deq_is_empty(_deq))
	{
		// создаем новый элемент дека
		new_node = node_create<T>(data, NULL, NULL);

		// записываем адресс нового элемента в дек
		// в качестве первого элемента
		_deq->m_begin = new_node;
		_deq->m_end = new_node;
	}
	// если в деке есть элементы
	else
	{
		// создаем элемент для вставки в дек
		new_node = node_create<T>(
			data, NULL, _deq->m_end);

		// настравиваем последний элемент в деке
		_deq->m_end->m_next = new_node;

		// настраиваем сам дек
		_deq->m_end = new_node;
	}

	//увеличиваем количество элементов
	_deq->m_size++;

	INFO("Элемент добавлен в конец");
}

// функция удаления элемента из конца дека
template<typename T>
void deq_pop_back(deq<T>* _deq)
{
	// выходим, если дек не существует или пуст
	DEQ_NOT_EXSISTS("POP");
	DEQ_EMPTY("POP");

	// элемент удаления
	node<T>* to_delete = _deq->m_end;

	// если в деке минимум 2 элемента
	if (_deq->m_begin != to_delete)
	{
		// настройка дека
		_deq->m_end = to_delete->m_prev;

		// разрыв связей с элементом удаления
		to_delete->m_prev->m_next = NULL;
	}
	else
	{
		// обнуляем адреса дека, указвающие
		// на первый и последний элементы дека
		_deq->m_begin = _deq->m_end = NULL;
	}

	// удаления самого элемента
	node_delete(to_delete);

	// уменьшение размера дека на 1
	_deq->m_size--;

	INFO("Последний элемент был удален");
}

template<typename T>
node<T>* deq_get_front(deq<T>* _deq)
{
	// выходим, если дек не существует
	DEQ_NOT_EXSISTS_RET("GET_FRONT", NULL);
	return _deq->m_begin;
}

// удаление дека
template<typename T>
void deq_delete(deq<T>*& _deq)
{
	// выходим, если дек не существует
	DEQ_NOT_EXSISTS("DELETE");

	// пока дек не пуст
	while (!deq_is_empty(_deq))
	{
		// удаляем элементы дека с конца
		deq_pop_back(_deq);
	}

	// очищение памяти
	delete _deq;

	// обнуление адреса
	_deq = NULL;

	INFO("дек был удален")
}

// печать дека
template<typename T>
void deq_print(deq<T>* _deq, ostream& _out_stream)
{
	// выходим, если дек не существует или пуст
	DEQ_NOT_EXSISTS("PRINT");
	DEQ_EMPTY("PRINT");

	// создаем элемент для чтения данных
	node<T>* cur_el = _deq->m_begin;

	// индекс элемента
	int i = 0;

	// печать шапки таблицы
	_out_stream << OUT_W('_', 22) << '\n';

	// дополнительная информация о деке
	_out_stream << "|_размер:_" <<
		OUT_W('_', 9) << _deq->m_size << "_|\n";
	_out_stream << "|_индекс_|_значение_|\n";

	// идем по деку, пока на наткнемся на конечный элемент
	while (cur_el != NULL)
	{
		// вывод данных элемента
		_out_stream << "| " << OUT_W(' ', 6) << i
			<< " | " << setprecision(1)
			<< OUT_W(' ', 8) << cur_el->m_data
			<< " |\n";

		// переход к следующему элементу
		cur_el = cur_el->m_next;
		i++;
	}
	// печать конца таблицы
	_out_stream << OUT_W('-', 22) << '\n';
}
/**************** End Of LW4.cpp File ***************/
