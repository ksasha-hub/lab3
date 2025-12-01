#include "ConsoleInterface.h"
#include <algorithm>

ConsoleInterface::ConsoleInterface() = default;

ConsoleInterface::~ConsoleInterface() {
    for (const auto& pair : arrays) delete pair.second;
    for (const auto& pair : singlyLists) delete pair.second;
    for (const auto& pair : doublyLists) delete pair.second;
    for (const auto& pair : queues) delete pair.second;
    for (const auto& pair : stacks) delete pair.second;
    for (const auto& pair : hashTables) delete pair.second;
    for (const auto& pair : trees) delete pair.second;
}

std::vector<std::string> ConsoleInterface::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

int ConsoleInterface::stringToInt(const std::string& str) {
    try {
        return std::stoi(str);
    } catch (...) {
        throw std::invalid_argument("Invalid integer: " + str);
    }
}

std::string ConsoleInterface::unescapeString(const std::string& str) {
    std::string result = str;
    size_t pos = 0;
    while ((pos = result.find("\\n", pos)) != std::string::npos) {
        result.replace(pos, 2, "\n");
        pos += 1;
    }
    pos = 0;
    while ((pos = result.find("\\\"", pos)) != std::string::npos) {
        result.replace(pos, 2, "\"");
        pos += 1;
    }
    pos = 0;
    while ((pos = result.find("\\\\", pos)) != std::string::npos) {
        result.replace(pos, 2, "\\");
        pos += 1;
    }
    return result;
}

std::string ConsoleInterface::escapeString(const std::string& str) {
    std::string result = str;
    size_t pos = 0;
    while ((pos = result.find("\n", pos)) != std::string::npos) {
        result.replace(pos, 1, "\\n");
        pos += 2;
    }
    pos = 0;
    while ((pos = result.find("\"", pos)) != std::string::npos) {
        result.replace(pos, 1, "\\\"");
        pos += 2;
    }
    pos = 0;
    while ((pos = result.find("\\", pos)) != std::string::npos) {
        result.replace(pos, 1, "\\\\");
        pos += 2;
    }
    return result;
}

void ConsoleInterface::printHelp() {
    std::cout << "Доступные команды:\n";
    std::cout << "Создание контейнеров:\n";
    std::cout << "  MCREATE <name>      - Создать массив\n";
    std::cout << "  FCREATE <name>      - Создать односвязный список\n";
    std::cout << "  LCREATE <name>      - Создать двусвязный список\n";
    std::cout << "  QCREATE <name>      - Создать очередь\n";
    std::cout << "  SCREATE <name>      - Создать стек\n";
    std::cout << "  TCREATE <name>      - Создать хэш-таблицу\n";
    std::cout << "  CCREATE <name>      - Создать бинарное дерево\n\n";
    
    std::cout << "Операции с массивом:\n";
    std::cout << "  MPUSH <name> <value>          - Добавить элемент в конец\n";
    std::cout << "  MPUSHINDEX <name> <index> <value> - Вставить элемент по индексу\n";
    std::cout << "  WREPLACE <name> <index> <value>   - Заменить элемент по индексу\n";
    std::cout << "  MDEL <name> <index>           - Удалить элемент по индексу\n";
    std::cout << "  MGET <name>                   - Показать массив\n\n";
    
    std::cout << "Операции с односвязным списком:\n";
    std::cout << "  FPUSHHEAD <name> <value>      - Добавить в начало\n";
    std::cout << "  FPUSHTAIL <name> <value>      - Добавить в конец\n";
    std::cout << "  FOELHEAD <name>               - Удалить из начала\n";
    std::cout << "  FOELTAIL <name>               - Удалить из конца\n";
    std::cout << "  FGET <name>                   - Показать список\n\n";
    
    std::cout << "Операции с двусвязным списком:\n";
    std::cout << "  LPUSHHEAD <name> <value>      - Добавить в начало\n";
    std::cout << "  LPUSHTAIL <name> <value>      - Добавить в конец\n";
    std::cout << "  LDELHEAD <name>               - Удалить из начала\n";
    std::cout << "  LDELTAIL <name>               - Удалить из конца\n";
    std::cout << "  LGET <name>                   - Показать список\n\n";
    
    std::cout << "Операции с очередью:\n";
    std::cout << "  QPUSH <name> <value>          - Добавить в очередь\n";
    std::cout << "  QPOP <name>                   - Извлечь из очереди\n";
    std::cout << "  QGET <name>                   - Показать очередь\n\n";
    
    std::cout << "Операции со стеком:\n";
    std::cout << "  SPUSH <name> <value>          - Добавить в стек\n";
    std::cout << "  SPOP <name>                   - Извлечь из стека\n";
    std::cout << "  SGET <name>                   - Показать стек\n\n";
    
    std::cout << "Операции с хэш-таблицей:\n";
    std::cout << "  ITINSERT <name> <key> <value> - Вставить элемент\n";
    std::cout << "  TOEL <name> <key>             - Удалить элемент\n";
    std::cout << "  TGET <name> <key>             - Получить элемент\n";
    std::cout << "  TSHOW <name>                  - Показать всю таблицу\n\n";
    
    std::cout << "Операции с деревом:\n";
    std::cout << "  CINSERT <name> <value>        - Добавить элемент\n";
    std::cout << "  CREMOVE <name>                - Удалить корень\n";
    std::cout << "  CGET <name>                   - Показать дерево\n\n";
    
    std::cout << "Утилиты:\n";
    std::cout << "  PRINT <name>                  - Показать любой контейнер\n";
    std::cout << "  HELP                         - Показать эту справку\n";
    std::cout << "  EXIT                         - Выход\n\n";
    
    std::cout << "Примеры:\n";
    std::cout << "  MCREATE arr1\n";
    std::cout << "  MPUSH arr1 \"Hello World\"\n";
    std::cout << "  MGET arr1\n";
    std::cout << "  LCREATE list1\n";
    std::cout << "  LPUSHHEAD list1 \"First\"\n";
    std::cout << "  LPUSHTAIL list1 \"Last\"\n";
    std::cout << "  LGET list1\n";
}

void ConsoleInterface::executeCommand(const std::vector<std::string>& args) {
    if (args.empty()) return;
    
    const std::string command = args[0];
    
    try {
        // ==================== ARRAY COMMANDS ====================
        if (command == "MCREATE") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (arrays.find(name) == arrays.end()) {
                    arrays[name] = new Array();
                    std::cout << "✅ Array '" << name << "' создан" << std::endl;
                } else {
                    std::cout << "❌ Array '" << name << "' уже существует" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: MCREATE <name>" << std::endl;
            }
        }
        else if (command == "MPUSH") {
            if (args.size() >= 3) {
                std::string name = args[1];
                std::string value = unescapeString(args[2]);
                if (arrays.count(name)) {
                    arrays[name]->insert(value);
                    std::cout << "✅ Значение добавлено в Array '" << name << "'" << std::endl;
                } else {
                    std::cout << "❌ Array '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: MPUSH <name> <value>" << std::endl;
            }
        }
        else if (command == "MPUSHINDEX") {
            if (args.size() >= 4) {
                std::string name = args[1];
                size_t index = stringToInt(args[2]);
                std::string value = unescapeString(args[3]);
                if (arrays.count(name)) {
                    arrays[name]->insertAt(index, value);
                    std::cout << "✅ Значение добавлено в Array '" << name << "' по индексу " << index << std::endl;
                } else {
                    std::cout << "❌ Array '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: MPUSHINDEX <name> <index> <value>" << std::endl;
            }
        }
        else if (command == "WREPLACE") {
            if (args.size() >= 4) {
                std::string name = args[1];
                size_t index = stringToInt(args[2]);
                std::string value = unescapeString(args[3]);
                if (arrays.count(name)) {
                    arrays[name]->set(index, value);
                    std::cout << "✅ Значение заменено в Array '" << name << "' по индексу " << index << std::endl;
                } else {
                    std::cout << "❌ Array '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: WREPLACE <name> <index> <value>" << std::endl;
            }
        }
        else if (command == "MDEL") {
            if (args.size() >= 3) {
                std::string name = args[1];
                size_t index = stringToInt(args[2]);
                if (arrays.count(name)) {
                    arrays[name]->remove(index);
                    std::cout << "✅ Элемент удален из Array '" << name << "' по индексу " << index << std::endl;
                } else {
                    std::cout << "❌ Array '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: MDEL <name> <index>" << std::endl;
            }
        }
        else if (command == "MGET") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (arrays.count(name)) {
                    std::cout << "Array '" << name << "': ";
                    arrays[name]->print();
                } else {
                    std::cout << "❌ Array '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: MGET <name>" << std::endl;
            }
        }
        
        // ==================== SINGLY LINKED LIST COMMANDS ====================
        else if (command == "FCREATE") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (singlyLists.find(name) == singlyLists.end()) {
                    singlyLists[name] = new SinglyLinkedList();
                    std::cout << "✅ SinglyLinkedList '" << name << "' создан" << std::endl;
                } else {
                    std::cout << "❌ SinglyLinkedList '" << name << "' уже существует" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: FCREATE <name>" << std::endl;
            }
        }
        else if (command == "FPUSHHEAD") {
            if (args.size() >= 3) {
                std::string name = args[1];
                std::string value = unescapeString(args[2]);
                if (singlyLists.count(name)) {
                    singlyLists[name]->push_front(value);
                    std::cout << "✅ Значение добавлено в начало SinglyLinkedList '" << name << "'" << std::endl;
                } else {
                    std::cout << "❌ SinglyLinkedList '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: FPUSHHEAD <name> <value>" << std::endl;
            }
        }
        else if (command == "FPUSHTAIL") {
            if (args.size() >= 3) {
                std::string name = args[1];
                std::string value = unescapeString(args[2]);
                if (singlyLists.count(name)) {
                    singlyLists[name]->push_back(value);
                    std::cout << "✅ Значение добавлено в конец SinglyLinkedList '" << name << "'" << std::endl;
                } else {
                    std::cout << "❌ SinglyLinkedList '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: FPUSHTAIL <name> <value>" << std::endl;
            }
        }
        else if (command == "FOELHEAD") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (singlyLists.count(name)) {
                    singlyLists[name]->pop_front();
                    std::cout << "✅ Элемент удален из начала SinglyLinkedList '" << name << "'" << std::endl;
                } else {
                    std::cout << "❌ SinglyLinkedList '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: FOELHEAD <name>" << std::endl;
            }
        }
        else if (command == "FOELTAIL") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (singlyLists.count(name)) {
                    singlyLists[name]->pop_back();
                    std::cout << "✅ Элемент удален из конца SinglyLinkedList '" << name << "'" << std::endl;
                } else {
                    std::cout << "❌ SinglyLinkedList '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: FOELTAIL <name>" << std::endl;
            }
        }
        else if (command == "FGET") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (singlyLists.count(name)) {
                    std::cout << "SinglyLinkedList '" << name << "': ";
                    singlyLists[name]->print();
                } else {
                    std::cout << "❌ SinglyLinkedList '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: FGET <name>" << std::endl;
            }
        }
        
        // ==================== DOUBLY LINKED LIST COMMANDS ====================
        else if (command == "LCREATE") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (doublyLists.find(name) == doublyLists.end()) {
                    doublyLists[name] = new DoublyLinkedList();
                    std::cout << "✅ DoublyLinkedList '" << name << "' создан" << std::endl;
                } else {
                    std::cout << "❌ DoublyLinkedList '" << name << "' уже существует" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: LCREATE <name>" << std::endl;
            }
        }
        else if (command == "LPUSHHEAD") {
            if (args.size() >= 3) {
                std::string name = args[1];
                std::string value = unescapeString(args[2]);
                if (doublyLists.count(name)) {
                    doublyLists[name]->push_front(value);
                    std::cout << "✅ Значение добавлено в начало DoublyLinkedList '" << name << "'" << std::endl;
                } else {
                    std::cout << "❌ DoublyLinkedList '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: LPUSHHEAD <name> <value>" << std::endl;
            }
        }
        else if (command == "LPUSHTAIL") {
            if (args.size() >= 3) {
                std::string name = args[1];
                std::string value = unescapeString(args[2]);
                if (doublyLists.count(name)) {
                    doublyLists[name]->push_back(value);
                    std::cout << "✅ Значение добавлено в конец DoublyLinkedList '" << name << "'" << std::endl;
                } else {
                    std::cout << "❌ DoublyLinkedList '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: LPUSHTAIL <name> <value>" << std::endl;
            }
        }
        else if (command == "LDELHEAD") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (doublyLists.count(name)) {
                    doublyLists[name]->pop_front();
                    std::cout << "✅ Элемент удален из начала DoublyLinkedList '" << name << "'" << std::endl;
                } else {
                    std::cout << "❌ DoublyLinkedList '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: LDELHEAD <name>" << std::endl;
            }
        }
        else if (command == "LDELTAIL") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (doublyLists.count(name)) {
                    doublyLists[name]->pop_back();
                    std::cout << "✅ Элемент удален из конца DoublyLinkedList '" << name << "'" << std::endl;
                } else {
                    std::cout << "❌ DoublyLinkedList '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: LDELTAIL <name>" << std::endl;
            }
        }
        else if (command == "LGET") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (doublyLists.count(name)) {
                    std::cout << "DoublyLinkedList '" << name << "': ";
                    doublyLists[name]->print();
                } else {
                    std::cout << "❌ DoublyLinkedList '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: LGET <name>" << std::endl;
            }
        }
        
        // ==================== QUEUE COMMANDS ====================
        else if (command == "QCREATE") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (queues.find(name) == queues.end()) {
                    queues[name] = new Queue();
                    std::cout << "✅ Queue '" << name << "' создана" << std::endl;
                } else {
                    std::cout << "❌ Queue '" << name << "' уже существует" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: QCREATE <name>" << std::endl;
            }
        }
        else if (command == "QPUSH") {
            if (args.size() >= 3) {
                std::string name = args[1];
                std::string value = unescapeString(args[2]);
                if (queues.count(name)) {
                    queues[name]->enqueue(value);
                    std::cout << "✅ Значение добавлено в Queue '" << name << "'" << std::endl;
                } else {
                    std::cout << "❌ Queue '" << name << "' не найдена" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: QPUSH <name> <value>" << std::endl;
            }
        }
        else if (command == "QPOP") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (queues.count(name)) {
                    std::string value = queues[name]->dequeue();
                    std::cout << "✅ Извлечено из Queue '" << name << "': " << value << std::endl;
                } else {
                    std::cout << "❌ Queue '" << name << "' не найдена" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: QPOP <name>" << std::endl;
            }
        }
        else if (command == "QGET") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (queues.count(name)) {
                    std::cout << "Queue '" << name << "': ";
                    queues[name]->print();
                } else {
                    std::cout << "❌ Queue '" << name << "' не найдена" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: QGET <name>" << std::endl;
            }
        }
        
        // ==================== STACK COMMANDS ====================
        else if (command == "SCREATE") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (stacks.find(name) == stacks.end()) {
                    stacks[name] = new Stack();
                    std::cout << "✅ Stack '" << name << "' создан" << std::endl;
                } else {
                    std::cout << "❌ Stack '" << name << "' уже существует" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: SCREATE <name>" << std::endl;
            }
        }
        else if (command == "SPUSH") {
            if (args.size() >= 3) {
                std::string name = args[1];
                std::string value = unescapeString(args[2]);
                if (stacks.count(name)) {
                    stacks[name]->push(value);
                    std::cout << "✅ Значение добавлено в Stack '" << name << "'" << std::endl;
                } else {
                    std::cout << "❌ Stack '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: SPUSH <name> <value>" << std::endl;
            }
        }
        else if (command == "SPOP") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (stacks.count(name)) {
                    std::string value = stacks[name]->pop();
                    std::cout << "✅ Извлечено из Stack '" << name << "': " << value << std::endl;
                } else {
                    std::cout << "❌ Stack '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: SPOP <name>" << std::endl;
            }
        }
        else if (command == "SGET") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (stacks.count(name)) {
                    std::cout << "Stack '" << name << "': ";
                    stacks[name]->print();
                } else {
                    std::cout << "❌ Stack '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: SGET <name>" << std::endl;
            }
        }
        
        // ==================== HASH TABLE COMMANDS ====================
        else if (command == "TCREATE") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (hashTables.find(name) == hashTables.end()) {
                    hashTables[name] = new HashTable();
                    std::cout << "✅ HashTable '" << name << "' создана" << std::endl;
                } else {
                    std::cout << "❌ HashTable '" << name << "' уже существует" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: TCREATE <name>" << std::endl;
            }
        }
        else if (command == "ITINSERT") {
            if (args.size() >= 4) {
                std::string name = args[1];
                int key = stringToInt(args[2]);
                std::string value = unescapeString(args[3]);
                if (hashTables.count(name)) {
                    hashTables[name]->insert(key, value);
                    std::cout << "✅ Значение добавлено в HashTable '" << name << "' с ключом " << key << std::endl;
                } else {
                    std::cout << "❌ HashTable '" << name << "' не найдена" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: ITINSERT <name> <key> <value>" << std::endl;
            }
        }
        else if (command == "TOEL") {
            if (args.size() >= 3) {
                std::string name = args[1];
                int key = stringToInt(args[2]);
                if (hashTables.count(name)) {
                    if (hashTables[name]->remove(key)) {
                        std::cout << "✅ Элемент с ключом " << key << " удален из HashTable '" << name << "'" << std::endl;
                    } else {
                        std::cout << "❌ Элемент с ключом " << key << " не найден в HashTable '" << name << "'" << std::endl;
                    }
                } else {
                    std::cout << "❌ HashTable '" << name << "' не найдена" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: TOEL <name> <key>" << std::endl;
            }
        }
        else if (command == "TGET") {
            if (args.size() >= 3) {
                std::string name = args[1];
                int key = stringToInt(args[2]);
                if (hashTables.count(name)) {
                    std::string value = hashTables[name]->get(key);
                    std::cout << "✅ HashTable '" << name << "'[" << key << "] = " << value << std::endl;
                } else {
                    std::cout << "❌ HashTable '" << name << "' не найдена" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: TGET <name> <key>" << std::endl;
            }
        }
        else if (command == "TSHOW") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (hashTables.count(name)) {
                    std::cout << "HashTable '" << name << "': ";
                    hashTables[name]->print();
                } else {
                    std::cout << "❌ HashTable '" << name << "' не найдена" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: TSHOW <name>" << std::endl;
            }
        }
        
        // ==================== TREE COMMANDS ====================
        else if (command == "CCREATE") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (trees.find(name) == trees.end()) {
                    trees[name] = new CompleteBinaryTree();
                    std::cout << "✅ CompleteBinaryTree '" << name << "' создано" << std::endl;
                } else {
                    std::cout << "❌ CompleteBinaryTree '" << name << "' уже существует" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: CCREATE <name>" << std::endl;
            }
        }
        else if (command == "CINSERT") {
            if (args.size() >= 3) {
                std::string name = args[1];
                std::string value = unescapeString(args[2]);
                if (trees.count(name)) {
                    trees[name]->insert(value);
                    std::cout << "✅ Значение добавлено в CompleteBinaryTree '" << name << "'" << std::endl;
                } else {
                    std::cout << "❌ CompleteBinaryTree '" << name << "' не найдено" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: CINSERT <name> <value>" << std::endl;
            }
        }
        else if (command == "CREMOVE") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (trees.count(name)) {
                    trees[name]->remove();
                    std::cout << "✅ Корень удален из CompleteBinaryTree '" << name << "'" << std::endl;
                } else {
                    std::cout << "❌ CompleteBinaryTree '" << name << "' не найдено" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: CREMOVE <name>" << std::endl;
            }
        }
        else if (command == "CGET") {
            if (args.size() >= 2) {
                std::string name = args[1];
                if (trees.count(name)) {
                    std::cout << "CompleteBinaryTree '" << name << "': ";
                    trees[name]->print();
                } else {
                    std::cout << "❌ CompleteBinaryTree '" << name << "' не найдено" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: CGET <name>" << std::endl;
            }
        }
        
        // ==================== UTILITY COMMANDS ====================
        else if (command == "PRINT") {
            if (args.size() >= 2) {
                std::string name = args[1];
                bool found = false;
                
                if (arrays.count(name)) {
                    std::cout << "Array '" << name << "': ";
                    arrays[name]->print();
                    found = true;
                }
                if (singlyLists.count(name)) {
                    std::cout << "SinglyLinkedList '" << name << "': ";
                    singlyLists[name]->print();
                    found = true;
                }
                if (doublyLists.count(name)) {
                    std::cout << "DoublyLinkedList '" << name << "': ";
                    doublyLists[name]->print();
                    found = true;
                }
                if (queues.count(name)) {
                    std::cout << "Queue '" << name << "': ";
                    queues[name]->print();
                    found = true;
                }
                if (stacks.count(name)) {
                    std::cout << "Stack '" << name << "': ";
                    stacks[name]->print();
                    found = true;
                }
                if (hashTables.count(name)) {
                    std::cout << "HashTable '" << name << "': ";
                    hashTables[name]->print();
                    found = true;
                }
                if (trees.count(name)) {
                    std::cout << "CompleteBinaryTree '" << name << "': ";
                    trees[name]->print();
                    found = true;
                }
                
                if (!found) {
                    std::cout << "❌ Контейнер '" << name << "' не найден" << std::endl;
                }
            } else {
                std::cout << "❌ Использование: PRINT <name>" << std::endl;
            }
        }
        else if (command == "HELP") {
            printHelp();
        }
        else if (command == "EXIT" || command == "QUIT") {
            std::cout << "👋 Выход из программы..." << std::endl;
            exit(0);
        }
        else {
            std::cout << "❌ Неизвестная команда: " << command << std::endl;
            std::cout << "💡 Используйте HELP для списка команд" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "❌ Ошибка: " << e.what() << std::endl;
    }
}

void ConsoleInterface::runFromCommandLine(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Использование:\n";
        std::cout << "  " << argv[0] << " --file <filename>          # Выполнить команды из файла\n";
        std::cout << "  " << argv[0] << " --query '<command>'        # Выполнить одну команду\n";
        std::cout << "  " << argv[0] << " --interactive              # Интерактивный режим\n";
        std::cout << "  " << argv[0] << " --help                     # Справка\n";
        return;
    }
    
    std::string mode = argv[1];
    
    if (mode == "--file" && argc >= 3) {
        std::string filename = argv[2];
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "❌ Не удалось открыть файл: " << filename << std::endl;
            return;
        }
        
        std::cout << "📁 Выполнение команд из файла: " << filename << std::endl;
        std::string line;
        int lineNum = 0;
        while (std::getline(file, line)) {
            lineNum++;
            if (!line.empty() && line[0] != '#') { // Пропускаем пустые строки и комментарии
                std::vector<std::string> args = split(line, ' ');
                if (!args.empty()) {
                    std::cout << "[" << lineNum << "] > " << line << std::endl;
                    executeCommand(args);
                }
            }
        }
        file.close();
        std::cout << "✅ Файл выполнен успешно" << std::endl;
    }
    else if (mode == "--query" && argc >= 3) {
        std::string query = argv[2];
        std::vector<std::string> args = split(query, ' ');
        executeCommand(args);
    }
    else if (mode == "--interactive") {
        interactiveMode();
    }
    else if (mode == "--help" || mode == "-h") {
        printHelp();
    }
    else {
        std::cout << "❌ Неизвестный режим: " << mode << std::endl;
        std::cout << "💡 Используйте --help для справки" << std::endl;
    }
}

void ConsoleInterface::interactiveMode() {
    std::cout << "🚀 Интерактивный режим консольного интерфейса" << std::endl;
    std::cout << "💡 Введите HELP для списка команд, EXIT для выхода" << std::endl;
    std::cout << "==============================================" << std::endl;
    
    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        
        if (input.empty()) continue;
        
        std::vector<std::string> args = split(input, ' ');
        if (!args.empty()) {
            if (args[0] == "EXIT" || args[0] == "QUIT") {
                std::cout << "👋 Выход из программы..." << std::endl;
                break;
            }
            executeCommand(args);
        }
    }
}