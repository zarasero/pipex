# pipex
1. Базовые тесты
Эти тесты проверяют основную функциональность проекта — передача данных между командами через пайпы:

Тест 1: Простой кейс с двумя командами
Команда:
bash
Copy code
./pipex file1 "cat" "grep something" file2
Проверка: выходной файл file2 должен содержать результат работы:
bash
Copy code
< file1 cat | grep something > file2
Тест 2: Необходимость экранирования команд с аргументами
Команда:
bash
Copy code
./pipex file1 "grep 'some text'" "wc -l" file2
Проверка: результат работы должен соответствовать:
bash
Copy code
< file1 grep 'some text' | wc -l > file2
Тест 3: Несуществующий входной файл
Команда:
bash
Copy code
./pipex non_existing_file "cat" "wc" file2
Проверка: программа должна корректно сообщить об ошибке отсутствия файла.
2. Обработка ошибок и аргументов
Тест 4: Неверное количество аргументов
Команда:
bash
Copy code
./pipex file1 "cat"
Проверка: программа должна вернуть ошибку о неправильном количестве аргументов.
Тест 5: Неисполняемая команда
Команда:
bash
Copy code
./pipex file1 "nonexistent_command" "wc" file2
Проверка: программа должна сообщить об ошибке, если команда не существует.
Тест 6: Права доступа на файлы
Создать файл file1 без прав на чтение, а затем выполнить команду:
bash
Copy code
./pipex file1 "cat" "wc" file2
Проверка: программа должна сообщить об ошибке прав доступа к файлу.
3. Бонусные тесты
Тест 7: Несколько пайпов
Команда:
bash
Copy code
./pipex file1 "grep 'some text'" "sort" "uniq" "wc -l" file2
Проверка: результат работы должен соответствовать следующей последовательности команд:
bash
Copy code
< file1 grep 'some text' | sort | uniq | wc -l > file2
Тест 8: Использование here_doc и >>
Тест с << и >>:
bash
Copy code
./pipex here_doc LIMIT "grep something" "wc -l" file2
После ввода данных до символа LIMIT, программа должна завершить ввод, а результат работы должен быть добавлен в конец file2 с помощью >>.
4. Граничные случаи
Тест 9: Пустой файл
Команда:
bash
Copy code
./pipex empty_file "cat" "wc -l" file2
Проверка: программа должна корректно обработать пустой входной файл.
Тест 10: Очень большой файл
Создать большой файл (несколько гигабайт) и выполнить команду:
bash
Copy code
./pipex big_file "cat" "wc -l" file2
Проверка: программа не должна аварийно завершиться, и результат должен соответствовать ожидаемому выводу.
Тест 11: Некорректная команда с here_doc
Команда:
bash
Copy code
./pipex here_doc LIMIT "nonexistent_command" "wc -l" file2
Проверка: программа должна корректно сообщить об ошибке выполнения первой команды и завершить работу.
