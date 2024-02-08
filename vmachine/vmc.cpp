//┌──────────────────────────────────────────────────────────────────┐
//│ Реализация методов классов пространства имен vmc.                │
//└──────────────────────────────────────────────────────────────────┘
#include "constants.h"
#include "vmc.h"
#include <iostream>
#include <string>

namespace vmc
{
    // Display:: Инициализация сообщения
    void Display::setDisplayMessage(std::string displayMessage) {
        displayMessage_ = displayMessage;
    }

    // Display:: Вывод сообщения на дисплей машины
    void Display::displayMessageOut() {
        std::cout << "Display->" << displayMessage_ << std::endl;
    }

    // Buttons:: Конструктор по умолчанию
    Buttons::Buttons()
    {
        buttonsActivity_    = false;
        buttonsChooseSnack_ = 0;
    }

    // Buttons:: Активация блока управления для вобора товара
    void Buttons::buttonsActivity(bool buttonsActivity)
    {
        buttonsActivity_ = buttonsActivity;
    }

    // Buttons:: Вывод меню блока управления
    void Buttons::buttonsMenu(Snack* const snack) 
    {
        std::cout << "МЕНЮ выбора товара\n"
                  << "--------------------------------"
                  << std::endl;

        for (short i = 0; i < cst::QUANTITY_SNACK; ++i) {
            std::cout << (i + 1)
                      << " - "
                      << snack[i].getPriceSnack()
                      << "р "
                      << "- "
                      << snack[i].getNameSnack()
                      << std::endl;
        }

        std::cout << "--------------------------------"
                  << std::endl; 
    }

    // Buttons:: Выбор кнопки товара
    void Buttons::buttonsPress()
    {
        std::cout << "Выберите товар: ";
        std::cin.clear();
        std::cin >> buttonsChooseSnack_;
    }

    // Buttons:: Получение выбранного товара
    short Buttons::getButtonsChooseSnack() const 
    {
        return buttonsChooseSnack_;
    }

    // Snack:: Конструктор по умолчанию
    Snack::Snack()
    {
        snackName_         = "";
        snackQuantity_     = 0;
        snackPrice_        = 0;
    }

    // Snack:: Конструктор
    Snack::Snack(std::string snackName, short snackQuantity, 
                 short snackPrice)
    {
        snackName_         = snackName;
        snackQuantity_     = snackQuantity;
        snackPrice_        = snackPrice;
    }

    // Snack:: Инициализация количества товара
    void Snack::setQuantitySnack(short snackQuantity)
    {
        snackQuantity_ = snackQuantity;
    }

    // Snack:: Получение количества товара
    short Snack::getQuantitySnack() const
    {
        return snackQuantity_;
    }

    // Snack:: Получение наименование товара
    std::string Snack::getNameSnack() const
    {
        return snackName_;
    }

    // Snack:: Получение цены товара за единицу
    short Snack::getPriceSnack() const
    {
        return snackPrice_;
    }

    // Snack:: Уменьшение товара
    void Snack::snackReduce()
    {
        --snackQuantity_;
    }

    // BillReceiver:: Конструктор по умолчанию
    BillReceiver::BillReceiver()
    {
        brAcceptedBill_ = 0;
    }

    // BillReceiver:: Реализация приема денежной купюры
    void BillReceiver::setAcceptedBill(Display* const display)
    {
        short bill {};

        do {
            std::string str = "M: Вставьте купюру 50, 100, 200, 500";

            display->setDisplayMessage(str);
            display->displayMessageOut();

            bill = 0;
            std::cin.clear();
            std::cin >> bill;
        } while (bill != 50 && bill != 100 && bill != 200 && bill != 500);

        brAcceptedBill_ += bill;
    }

    // BillReceiver:: Получение внесенной купюры
    short BillReceiver::getAcceptedBill() const
    {
        return brAcceptedBill_;
    }

    // BillReceiver:: Определение дастаточности внесенных денег
    bool BillReceiver::brEnoughBill(Snack* const snack, Buttons* const buttons)
    {
        if (brAcceptedBill_ < 
            snack[buttons->getButtonsChooseSnack() - 1].getPriceSnack()) {
            return false;
        }
        return true;
    }

    // BillReceiver:: Нужно ли выдать сдачу?
    void BillReceiver::brChange(Display* const display,
                                Snack* const snack, 
                                Buttons* const buttons)
    {
        if (brAcceptedBill_ > 
            snack[buttons->getButtonsChooseSnack()-1].getPriceSnack()) {
            short changePrice = brAcceptedBill_ - 
                  snack[buttons->getButtonsChooseSnack()-1].getPriceSnack();
            display->setDisplayMessage("M: Заберите сдачу " +
                                       std::to_string(changePrice) +
                                       " рублей");
            display->displayMessageOut();
        }
    }

    // BillReceiver:: Обнуление внесенных денег
    void BillReceiver::brAcceptedBillNull()
    {
        brAcceptedBill_ = 0;
    }

    // VendingMachine:: Загрузить лоток в аппарат
    void VendingMachine::addSlot(Display* const display, Snack* const snack)
    {
        short sizeSnack = cst::QUANTITY_SLOT * cst::CAPACITY_SLOT;

        for (short i = 0; i < cst::QUANTITY_SNACK; ++i) {
            if (snack[i].getQuantitySnack() > sizeSnack) {
                snack[i].setQuantitySnack(sizeSnack);
                std::string str = "M: Лоток с [" + 
                                  snack[i].getNameSnack() +
                                  "] загружен...";
                display->setDisplayMessage(str);
                display->displayMessageOut();
            }
            else if (snack[i].getQuantitySnack() < 1) {
                std::string str = "E: Лоток с [" + 
                                  snack[i].getNameSnack() +
                                  "] не загружен!";
                display->setDisplayMessage(str);
                display->displayMessageOut();
            }
        }
    }

    // VendingMachine:: Выдача товара
    void VendingMachine::issueSnack(Display* const display, 
                                    Snack* const snack,
                                    Buttons* const buttons) 
    {
        std::string str {};

        if (snack[buttons->getButtonsChooseSnack()-1].getQuantitySnack() != 0) {
            str = "M: Заберите товар [" +
                  snack[buttons->getButtonsChooseSnack()-1].getNameSnack() +
                  "]";
            display->setDisplayMessage(str);
            display->displayMessageOut();

            snack[buttons->getButtonsChooseSnack()-1].snackReduce();
        }
    }

    // VendingMachine:: Проверка наличия выбранного товара
    bool VendingMachine::checkAvailability(Snack* const snack,
                                           Buttons* const buttons)
    {
        if (snack[buttons->getButtonsChooseSnack()-1].getQuantitySnack() == 0) {
            return false;
        }
        return true;
    }

}
