CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -fprofile-arcs -ftest-coverage
LDFLAGS = -lgtest -lgtest_main -lpthread -lboost_unit_test_framework -fprofile-arcs -ftest-coverage

# Исходные файлы структур данных
SRCS = Array.cpp SinglyLinkedList.cpp DoublyLinkedList.cpp \
       Queue.cpp Stack.cpp HashTable.cpp CompleteBinaryTree.cpp

HEADERS = Array.h \
          SinglyLinkedList.h \
          DoublyLinkedList.h \
          Queue.h \
          Stack.h \
          HashTable.h \
          CompleteBinaryTree.h \
          SerializationUtils.h \
          ConsoleInterface.h
		  
# Тестовые файлы
GTEST_TEST = test_array_gtest.cpp
BOOST_TEST = test_array_boost.cpp  
CXXTEST_HEADER = test_array_cxxtest.h
CXXTEST_CPP = test_runner.cpp

# Демонстрационные программы
SERIALIZATION_DEMO = demo_serialization.cpp
BENCHMARK = benchmark.cpp
CONSOLE_INTERFACE = ConsoleInterface.cpp

# Исполняемые файлы
GTEST_EXEC = gtest_tests
BOOST_EXEC = boost_tests
CXXTEST_EXEC = cxxtest_tests
MAIN_EXEC = main
SERIALIZATION_EXEC = demo_serialization
BENCHMARK_EXEC = benchmark
CONSOLE_EXEC = console_app

# Основная цель
all: main console gtest boosttest cxxtest serialization benchmark

# Основная программа с консольным интерфейсом
main: main.cpp $(SRCS) $(CONSOLE_INTERFACE)
	$(CXX) $(CXXFLAGS) -o $(MAIN_EXEC) main.cpp $(SRCS) $(CONSOLE_INTERFACE)

# Отдельная консольная программа
console: main.cpp $(SRCS) $(CONSOLE_INTERFACE)
	$(CXX) $(CXXFLAGS) -o $(CONSOLE_EXEC) main.cpp $(SRCS) $(CONSOLE_INTERFACE)

# Демонстрация сериализации
serialization: $(SRCS) $(SERIALIZATION_DEMO)
	$(CXX) $(CXXFLAGS) -o $(SERIALIZATION_EXEC) $(SRCS) $(SERIALIZATION_DEMO)

# Бенчмарк
benchmark: $(SRCS) $(BENCHMARK)
	$(CXX) $(CXXFLAGS) -o $(BENCHMARK_EXEC) $(SRCS) $(BENCHMARK)

# Google Test
gtest: $(SRCS) $(GTEST_TEST)
	$(CXX) $(CXXFLAGS) -o $(GTEST_EXEC) $(SRCS) $(GTEST_TEST) $(LDFLAGS)

# Boost Test  
boosttest: $(SRCS) $(BOOST_TEST)
	$(CXX) $(CXXFLAGS) -o $(BOOST_EXEC) $(SRCS) $(BOOST_TEST) $(LDFLAGS)

# CxxTest
cxxtest: $(CXXTEST_CPP)
	$(CXX) $(CXXFLAGS) -o $(CXXTEST_EXEC) $(SRCS) $(CXXTEST_CPP) $(LDFLAGS)

# Генерация раннера для CxxTest
$(CXXTEST_CPP): $(CXXTEST_HEADER)
	cxxtestgen --error-printer -o $(CXXTEST_CPP) $(CXXTEST_HEADER)

# Запуск тестов
run-gtest: gtest
	./$(GTEST_EXEC)

run-boost: boosttest
	./$(BOOST_EXEC)

run-cxxtest: cxxtest
	./$(CXXTEST_EXEC)

run-main: main
	./$(MAIN_EXEC)

# Запуск консольного приложения
run-console: console
	./$(CONSOLE_EXEC)

# Запуск консольного приложения с разными режимами
console-interactive: console
	./$(CONSOLE_EXEC) --interactive

console-file: console
	@if [ -f "TEST" ]; then \
		./$(CONSOLE_EXEC) --file TEST; \
	else \
		echo "❌ Файл TEST не найден. Создайте файл TEST с командами."; \
	fi

console-query: console
	@echo "💡 Пример: make console-query COMMAND='MCREATE myarray'"
	@if [ -n "$(COMMAND)" ]; then \
		./$(CONSOLE_EXEC) --query "$(COMMAND)"; \
	else \
		echo "❌ Укажите команду: make console-query COMMAND='ваша_команда'"; \
	fi

console-help: console
	./$(CONSOLE_EXEC) --help

# Запуск демонстрации сериализации
run-serialization: serialization
	./$(SERIALIZATION_EXEC)

# Запуск бенчмарка
run-benchmark: benchmark
	./$(BENCHMARK_EXEC)

# Запуск всех тестов и демонстраций
run-all: run-gtest run-boost run-cxxtest run-serialization run-benchmark
	@echo "✅ Все тесты и демонстрации завершены"

# Покрытие кода для Google Test (только структуры данных)
coverage-gtest: gtest
	@echo "🧪 Запуск Google Test..."
	./$(GTEST_EXEC)
	@mkdir -p gtest_coverage_html
	@gcovr --html --html-details -o gtest_coverage_html/index.html \
		--exclude="main.cpp" \
		--exclude="demo_.*\.cpp" \
		--exclude="benchmark.cpp" \
		--exclude="ConsoleInterface.cpp" \
		--exclude="test_.*\.cpp" \
		--exclude="test_.*\.h" \
		--exclude=".*_test.*" \
		--print-summary
	@echo "✅ Google Test отчет создан: gtest_coverage_html/index.html"

# Покрытие кода для Boost Test (только структуры данных)
coverage-boost: boosttest
	@echo "🧪 Запуск Boost Test..."
	./$(BOOST_EXEC)
	@mkdir -p boost_coverage_html
	@gcovr --html --html-details -o boost_coverage_html/index.html \
		--exclude="main.cpp" \
		--exclude="demo_.*\.cpp" \
		--exclude="benchmark.cpp" \
		--exclude="ConsoleInterface.cpp" \
		--exclude="test_.*\.cpp" \
		--exclude="test_.*\.h" \
		--exclude=".*_test.*" \
		--print-summary
	@echo "✅ Boost Test отчет создан: boost_coverage_html/index.html"

# Покрытие кода для CxxTest (только структуры данных)
coverage-cxxtest: cxxtest
	@echo "🧪 Запуск CxxTest..."
	./$(CXXTEST_EXEC)
	@mkdir -p cxxtest_coverage_html
	@gcovr --html --html-details -o cxxtest_coverage_html/index.html \
		--exclude="main.cpp" \
		--exclude="demo_.*\.cpp" \
		--exclude="benchmark.cpp" \
		--exclude="ConsoleInterface.cpp" \
		--exclude="test_.*\.cpp" \
		--exclude="test_.*\.h" \
		--exclude=".*_test.*" \
		--print-summary
	@echo "✅ CxxTest отчет создан: cxxtest_coverage_html/index.html"

# Все отчеты покрытия (только структуры данных)
coverage: coverage-gtest coverage-boost coverage-cxxtest
	@echo ""
	@echo "🎉 Все HTML отчеты созданы (только структуры данных)!"
	@echo "📊 Google Test: gtest_coverage_html/index.html"
	@echo "📊 Boost Test: boost_coverage_html/index.html"  
	@echo "📊 CxxTest: cxxtest_coverage_html/index.html"

# Создать и открыть все отчеты
coverage-open: coverage
	@echo "🌐 Открываю все отчеты в браузере..."
	@if command -v xdg-open > /dev/null; then \
		xdg-open gtest_coverage_html/index.html; \
		xdg-open boost_coverage_html/index.html; \
		xdg-open cxxtest_coverage_html/index.html; \
	elif command -v open > /dev/null; then \
		open gtest_coverage_html/index.html; \
		open boost_coverage_html/index.html; \
		open cxxtest_coverage_html/index.html; \
	else \
		echo "❌ Не могу открыть браузер. Отчеты в папках: *_coverage_html/"; \
	fi

# Открыть существующие отчеты
open-reports:
	@if [ -f "gtest_coverage_html/index.html" ]; then \
		echo "🌐 Открываю существующие отчеты..."; \
		if command -v xdg-open > /dev/null; then \
			xdg-open gtest_coverage_html/index.html; \
			xdg-open boost_coverage_html/index.html; \
			xdg-open cxxtest_coverage_html/index.html; \
		elif command -v open > /dev/null; then \
			open gtest_coverage_html/index.html; \
			open boost_coverage_html/index.html; \
			open cxxtest_coverage_html/index.html; \
		else \
			echo "❌ Не могу открыть браузер"; \
		fi \
	else \
		echo "❌ Отчеты не найдены. Сначала выполните: make coverage"; \
	fi

# Открыть конкретный отчет
open-gtest:
	@if [ -f "gtest_coverage_html/index.html" ]; then \
		if command -v xdg-open > /dev/null; then \
			xdg-open gtest_coverage_html/index.html; \
		elif command -v open > /dev/null; then \
			open gtest_coverage_html/index.html; \
		else \
			echo "❌ Не могу открыть браузер"; \
		fi \
	else \
		echo "❌ Google Test отчет не найден. Сначала выполните: make coverage-gtest"; \
	fi

open-boost:
	@if [ -f "boost_coverage_html/index.html" ]; then \
		if command -v xdg-open > /dev/null; then \
			xdg-open boost_coverage_html/index.html; \
		elif command -v open > /dev/null; then \
			open boost_coverage_html/index.html; \
		else \
			echo "❌ Не могу открыть браузер"; \
		fi \
	else \
		echo "❌ Boost Test отчет не найден. Сначала выполните: make coverage-boost"; \
	fi

open-cxxtest:
	@if [ -f "cxxtest_coverage_html/index.html" ]; then \
		if command -v xdg-open > /dev/null; then \
			xdg-open cxxtest_coverage_html/index.html; \
		elif command -v open > /dev/null; then \
			open cxxtest_coverage_html/index.html; \
		else \
			echo "❌ Не могу открыть браузер"; \
		fi \
	else \
		echo "❌ CxxTest отчет не найден. Сначала выполните: make coverage-cxxtest"; \
	fi

# Быстрая проверка покрытия (текстовый отчет, только структуры данных)
coverage-quick: gtest
	./$(GTEST_EXEC)
	@echo "📊 Быстрый текстовый отчет покрытия (только структуры данных):"
	@gcovr --exclude="main.cpp" --exclude="demo_.*\.cpp" --exclude="benchmark.cpp" --exclude="ConsoleInterface.cpp" --exclude="test_.*\.cpp" --exclude="test_.*\.h" --exclude=".*_test.*" --print-summary

# Сравнительная таблица покрытия (только структуры данных)
coverage-compare: coverage
	@echo "📈 Сравнительная таблица покрытия (только структуры данных):"
	@echo ""
	@echo "Структура данных    | Google Test | Boost Test | CxxTest"
	@echo "--------------------|-------------|------------|---------"
	@for file in Array.cpp SinglyLinkedList.cpp DoublyLinkedList.cpp Queue.cpp Stack.cpp HashTable.cpp CompleteBinaryTree.cpp; do \
		base_name=$$(basename "$$file" .cpp); \
		printf "%-19s |" "$$base_name"; \
		if [ -f "gtest_coverage_html/$$file.gcov.html" ]; then \
			gtest_coverage=$$(grep -o "Lines:.*%" "gtest_coverage_html/$$file.gcov.html" | head -1 | grep -o '[0-9.]*%' || echo "N/A"); \
			printf " %-11s |" "$$gtest_coverage"; \
		else \
			printf " %-11s |" "N/A"; \
		fi; \
		if [ -f "boost_coverage_html/$$file.gcov.html" ]; then \
			boost_coverage=$$(grep -o "Lines:.*%" "boost_coverage_html/$$file.gcov.html" | head -1 | grep -o '[0-9.]*%' || echo "N/A"); \
			printf " %-10s |" "$$boost_coverage"; \
		else \
			printf " %-10s |" "N/A"; \
		fi; \
		if [ -f "cxxtest_coverage_html/$$file.gcov.html" ]; then \
			cxxtest_coverage=$$(grep -o "Lines:.*%" "cxxtest_coverage_html/$$file.gcov.html" | head -1 | grep -o '[0-9.]*%' || echo "N/A"); \
			printf " %-7s" "$$cxxtest_coverage"; \
		else \
			printf " %-7s" "N/A"; \
		fi; \
		echo ""; \
	done

# Очистка
clean:
	@echo "🧹 Очистка..."
	@rm -f $(GTEST_EXEC) $(BOOST_EXEC) $(CXXTEST_EXEC) $(MAIN_EXEC) $(SERIALIZATION_EXEC) $(BENCHMARK_EXEC) $(CONSOLE_EXEC)
	@rm -f $(CXXTEST_CPP) *.gcda *.gcno *.gcov *.info
	@rm -rf *_coverage_html
	@rm -f *.txt *.bin  # Удаляем файлы сериализации

# Линтинг C++ кода с cppcheck
lint:
	@echo "🔍 Линтинг C++ кода..."
	@which cppcheck >/dev/null 2>&1 || (echo "❌ cppcheck не установлен. Установите: brew install cppcheck" && exit 1)
	@cppcheck --enable=all \
	          --suppress=missingInclude \
	          --suppress=unusedFunction \
	          --suppress=unusedStructMember \
	          --suppress=knownConditionTrueFalse \
	          --suppress=unreadVariable \
			  --suppress=ctuOneDefinitionRuleViolation \
	          --suppress=constParameter \
	          --language=c++ --std=c++17 \
	          *.cpp *.h 2>&1 | grep -E "(error|warning|style):" || true
	@echo "✅ Линтинг завершен"

# Тестирование сериализации
test-serialization: serialization
	@echo "🧪 Тестирование сериализации..."
	./$(SERIALIZATION_EXEC)

# Демонстрация всех возможностей сериализации
demo-all: serialization
	@echo "🚀 Демонстрация всех возможностей сериализации..."
	./$(SERIALIZATION_EXEC)

# Быстрая демонстрация (только основные структуры)
demo-quick: serialization
	@echo "⚡ Быстрая демонстрация сериализации..."
	./$(SERIALIZATION_EXEC)

# Создание тестового файла для консольного интерфейса
create-test-file:
	@echo "📝 Создание тестового файла TEST..."
	@echo "# Тестовый файл для консольного интерфейса" > TEST
	@echo "# Создание структур данных" >> TEST
	@echo "MCREATE myarray" >> TEST
	@echo "FCREATE mylist" >> TEST
	@echo "QCREATE myqueue" >> TEST
	@echo "SCREATE mystack" >> TEST
	@echo "TCREATE myhashtable" >> TEST
	@echo "CCREATE mytree" >> TEST
	@echo "" >> TEST
	@echo "# Работа с массивом" >> TEST
	@echo "MPUSH myarray \"Hello\"" >> TEST
	@echo "MPUSH myarray \"World\"" >> TEST
	@echo "MPUSHINDEX myarray 1 \"Beautiful\"" >> TEST
	@echo "MGET myarray" >> TEST
	@echo "MDEL myarray 1" >> TEST
	@echo "MGET myarray" >> TEST
	@echo "" >> TEST
	@echo "# Работа со списком" >> TEST
	@echo "FPUSHHEAD mylist \"First\"" >> TEST
	@echo "FPUSHTAIL mylist \"Last\"" >> TEST
	@echo "FPUSHHEAD mylist \"NewFirst\"" >> TEST
	@echo "FGET mylist" >> TEST
	@echo "FOELHEAD mylist" >> TEST
	@echo "FGET mylist" >> TEST
	@echo "" >> TEST
	@echo "# Работа с очередью" >> TEST
	@echo "QPUSH myqueue \"Job1\"" >> TEST
	@echo "QPUSH myqueue \"Job2\"" >> TEST
	@echo "QPOP myqueue" >> TEST
	@echo "QPUSH myqueue \"Job3\"" >> TEST
	@echo "" >> TEST
	@echo "# Работа со стеком" >> TEST
	@echo "SPUSH mystack \"Layer1\"" >> TEST
	@echo "SPUSH mystack \"Layer2\"" >> TEST
	@echo "SPOP mystack" >> TEST
	@echo "SPUSH mystack \"Layer3\"" >> TEST
	@echo "" >> TEST
	@echo "# Работа с хеш-таблицей" >> TEST
	@echo "ITINSERT myhashtable 1 \"Alice\"" >> TEST
	@echo "ITINSERT myhashtable 2 \"Bob\"" >> TEST
	@echo "ITINSERT myhashtable 17 \"Charlie\"" >> TEST
	@echo "TGET myhashtable 1" >> TEST
	@echo "TGET myhashtable 17" >> TEST
	@echo "" >> TEST
	@echo "# Работа с деревом" >> TEST
	@echo "CINSERT mytree \"Root\"" >> TEST
	@echo "CINSERT mytree \"Left\"" >> TEST
	@echo "CINSERT mytree \"Right\"" >> TEST
	@echo "CINSERT mytree \"Middle\"" >> TEST
	@echo "" >> TEST
	@echo "# Вывод всех структур" >> TEST
	@echo "PRINT myarray" >> TEST
	@echo "PRINT mylist" >> TEST
	@echo "PRINT myqueue" >> TEST
	@echo "PRINT mystack" >> TEST
	@echo "PRINT myhashtable" >> TEST
	@echo "PRINT mytree" >> TEST
	@echo "" >> TEST
	@echo "HELP" >> TEST
	@echo "✅ Тестовый файл TEST создан"

# Быстрый старт консольного приложения
quick-start: console create-test-file
	@echo "🚀 Быстрый старт консольного приложения..."
	@echo "💡 Доступные команды:"
	@echo "   make console-interactive  - Интерактивный режим"
	@echo "   make console-file         - Выполнить команды из файла TEST"
	@echo "   make console-query COMMAND='ваша_команда' - Выполнить одну команду"
	@echo ""
	@echo "🔧 Примеры команд:"
	@echo "   make console-query COMMAND='MCREATE testarr'"
	@echo "   make console-query COMMAND='MPUSH testarr \"Hello\"'"
	@echo "   make console-query COMMAND='MGET testarr'"

# Помощь
help:
	@echo "Доступные команды:"
	@echo "  make all              - Собрать все исполняемые файлы"
	@echo "  make main             - Собрать основную программу"
	@echo "  make console          - Собрать консольное приложение"
	@echo "  make serialization    - Собрать демонстрацию сериализации"
	@echo "  make benchmark        - Собрать бенчмарк"
	@echo "  make coverage         - Создать все отчеты покрытия (только структуры данных)"
	@echo "  make coverage-open    - Создать и открыть все отчеты"
	@echo "  make open-reports     - Открыть существующие отчеты"
	@echo "  make coverage-compare - Сравнительная таблица покрытия"
	@echo "  make run-all          - Запустить все тесты"
	@echo "  make clean            - Очистка"
	@echo "  make lint             - Линтинг кода"
	@echo ""
	@echo "🎮 Команды консольного интерфейса:"
	@echo "  make run-console          - Запустить консольное приложение"
	@echo "  make console-interactive  - Интерактивный режим"
	@echo "  make console-file         - Выполнить команды из файла TEST"
	@echo "  make console-query        - Выполнить одну команду (указать COMMAND)"
	@echo "  make console-help         - Показать справку консольного приложения"
	@echo "  make create-test-file     - Создать тестовый файл команд"
	@echo "  make quick-start          - Быстрый старт консольного приложения"
	@echo ""
	@echo "🧪 Команды сериализации:"
	@echo "  make run-serialization - Запустить демонстрацию сериализации"
	@echo "  make test-serialization- Тестирование сериализации"
	@echo "  make demo-all         - Полная демонстрация сериализации"
	@echo "  make demo-quick       - Быстрая демонстрация сериализации"
	@echo ""
	@echo "📊 Команды покрытия (только структуры данных):"
	@echo "  make coverage-gtest   - Отчет только для Google Test"
	@echo "  make coverage-boost   - Отчет только для Boost Test"
	@echo "  make coverage-cxxtest - Отчет только для CxxTest"
	@echo "  make coverage-quick   - Быстрый текстовый отчет"
	@echo ""
	@echo "🌐 Команды открытия отчетов:"
	@echo "  make open-gtest       - Открыть Google Test отчет"
	@echo "  make open-boost       - Открыть Boost Test отчет"
	@echo "  make open-cxxtest     - Открыть CxxTest отчет"
	@echo ""
	@echo "💡 Примеры использования консольного интерфейса:"
	@echo "  make console-query COMMAND='MCREATE myarray'"
	@echo "  make console-query COMMAND='MPUSH myarray \"Hello World\"'"
	@echo "  make console-query COMMAND='MGET myarray'"
	@echo "  make console-interactive"

.PHONY: all main console serialization benchmark gtest boosttest cxxtest run-gtest run-boost run-cxxtest \
        run-main run-console console-interactive console-file console-query console-help run-serialization \
        run-benchmark run-all coverage coverage-gtest coverage-boost coverage-cxxtest coverage-open \
        open-reports open-gtest open-boost open-cxxtest coverage-quick coverage-compare clean lint \
        test-serialization demo-all demo-quick create-test-file quick-start help