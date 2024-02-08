//╔════════════════════════════════════════════════════════════════════════════════════════════════╗
//║ (c) Patriarch, 2023 Шифр Цезаря.                                                               ║
//║     При шифровке каждая буква меняется таким образом, что номер получившейся буквы в           ║
//║     алфавите есть номер исходной буквы в алфавите плюс некоторое для всего шифруемого          ║
//║     текста определенное значение.                                                              ║
//║     При этом алфавит "закольцовывался" - считается, что за последней буквой алфавита идет      ║
//║     первая буквой алфавита идет первая за первой, естественно, вторая.                         ║
//╚════════════════════════════════════════════════════════════════════════════════════════════════╝
#include <clocale>
#include <iostream>
#include <cstdint>
#include <string>
#include "constants.h"
#include "desfun.h"

//┌────────────────────────────────────────────────────────────────────────────────────────────────┐
//│ Точка входа...                                                                                 │
//└────────────────────────────────────────────────────────────────────────────────────────────────┘
int main()
{
    // Локализация терминала ОС Windows
    #ifdef _WIN32
        setlocale(LC_ALL, "Russian");
    #endif

    while (true) {
        // Очистка экрана и помещение курсора в строку 1, колонку 1
        std::cout << "\033[2J\033[1;1H";        

        std::cout << "ШИФР ЦЕЗАРЯ" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        
        std::string strInput {};

        std::cout << "Введите строку: ";
        std::cin.clear();
        std::getline(std::cin, strInput);

        std::cout << "Ваши действия:" << std::endl;
        std::cout << "1 - шифрование" << std::endl;
        std::cout << "2 - дешифровка" << std::endl;
        std::cout << "-> ";

        std::uint16_t iMenu {};

        std::cin.clear();
        std::cin >> iMenu;

        if (iMenu == 1 || iMenu == 2) {
            std::cout << "Введите ключ от " << (cst::MIN_SIZE_ALPHABET + 1) << " по "
                                            << (cst::MAX_SIZE_ALPHABET - 1) << " включительно: ";
            std::int32_t iKey {};

            std::cin.clear();
            std::cin >> iKey;

            if (iKey > cst::MIN_SIZE_ALPHABET && iKey < cst::MAX_SIZE_ALPHABET) {
                std::cout << "-----------------------------------------" << std::endl;
                std::cout << "Исходная строка       -> " << strInput << std::endl;

                std::string strOutput {};

                switch (iMenu) {
                    case 1 :
                        strOutput = ::encdec(1, strInput, iKey);
                        std::cout << "Зашифрованная строка  -> " << strOutput << std::endl;
                        break;
                    case 2 :
                        strOutput = ::encdec(0, strInput, iKey);
                        std::cout << "Расшифрованная строка -> " << strOutput << std::endl;
                        break;
                }
            }
            else {
                std::cout << "E: Введенный ключ непонятен. Диапазон ключа от "
                          << (cst::MIN_SIZE_ALPHABET + 1) << " по "
                          << (cst::MAX_SIZE_ALPHABET - 1) << " включительно." << std::endl;
            }
        }
        else {
            std::cout << "E: Выбор действий непонятен." << std::endl;
        }

        char cMenu {};

        std::cout << "\nПродолжить работу [y/n]: ";
        std::cin.clear();
        std::cin >> cMenu;

        if (cMenu != 'y' && cMenu != 'Y') {
            std::cout << "До новых встреч..." << std::endl;
            return 0;
        }

        std::cin.clear();
        std::cin.ignore(INT_MAX,'\n');
    }
}
