//╔══════════════════════════════════════════════════════════════════╗
//║ (c) Patriarch, 2023                                              ║
//║     Вендинговая машина для быстрой продажи девайсов для          ║
//║     телефона:                                                    ║
//║         - гарнитура;                                             ║
//║         - usb кабель;                                            ║
//║         - защитное стекло;                                       ║
//║         - чехол;                                                 ║
//║         - зарядное устройство.                                   ║
//╚══════════════════════════════════════════════════════════════════╝
#include <clocale>
#include <iostream>
#include <string>
#include "constants.h"
#include "vmc.h"

//┌──────────────────────────────────────────────────────────────────┐
//│ Точка входа...                                                   │
//└──────────────────────────────────────────────────────────────────┘
int main()
{
    // Локализация терминала ОС Windows
    #ifdef _WIN32
        setlocale(LC_ALL, "Russian");
    #endif

    // Включение (инициализация) машины
    vmc::VendingMachine* vm      = new vmc::VendingMachine;
    vmc::Display*        display = new vmc::Display;
    vmc::Buttons*        buttons = new vmc::Buttons;
    vmc::BillReceiver*   br      = new vmc::BillReceiver;

    // Определение товара для загрузки в машину
    vmc::Snack* snack = new vmc::Snack[cst::QUANTITY_SNACK] {
        {"гарнитура", 100, 500},
        {"usb кабель", 100, 100},
        {"защитное стекло", 100, 500},
        {"чехол", 100, 200},
        {"зарядное устройство", 100, 300}
    };

    // Очистка экрана и помещение курсора в строку 1, колонку 1
    std::cout << "\033[2J\033[1;1H";        

    // Загрузка товара в машину
    vm->addSlot(display, snack);

    // Готовность машины к работе
    std::string str {};
    std::cout << std::endl;
    str = "M: Вендинговая машина готова к работе\n";
    display->setDisplayMessage(str);
    display->displayMessageOut();

    do {
        // Активация блока управления кнопками выбора товара
        buttons->buttonsActivity(true);
        buttons->buttonsMenu(snack);
        buttons->buttonsPress();

        // Проверка наличия выбранного товара
        if (vm->checkAvailability(snack, buttons)) {
            std::cout << std::endl;

            // Активация купюроприемника для оплаты товара
            while (!br->brEnoughBill(snack, buttons)) {
                br->setAcceptedBill(display);

                str = "M: Вами внесено " + 
                      std::to_string(br->getAcceptedBill()) + 
                      " рублей";
                display->setDisplayMessage(str);
                display->displayMessageOut();
            }    

            // Нужно ли выдать сдачу?
            br->brChange(display, snack, buttons);

            // Выдача купленного товара
            vm->issueSnack(display, snack, buttons);
        }
        else {
            std::cout << std::endl;
            display->setDisplayMessage("E: Выбранный товар отсутствует");
            display->displayMessageOut();
        }

        // Обнуление внесенных денег
        br->brAcceptedBillNull();

        std::cin.clear();
        //std::cin.ignore(INT_MAX,'\n');

        std::cout << std::endl;
        
        char anyKey {};
        display->setDisplayMessage("M: Продолжить работу [y/n]");
        display->displayMessageOut();
        std::cin >> anyKey;

        if (anyKey != 'y' && anyKey != 'Y') {
            display->setDisplayMessage("M: До новых встреч...");
            display->displayMessageOut();

            // Чистим память за собой и обнуляем указатели
            delete [] snack;
            delete br;
            delete buttons;
            delete display;
            delete vm;
    
            snack   = nullptr;
            br      = nullptr;
            buttons = nullptr;
            display = nullptr;
            vm      = nullptr;

            return 0;
        }

        // Очистка экрана и помещение курсора в строку 1, колонку 1
        std::cout << "\033[2J\033[1;1H";

    } while (true);
}
