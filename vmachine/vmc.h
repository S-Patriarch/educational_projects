#ifndef VMC_H
#define VMC_H

#include <string>

namespace vmc
{
    class Display;
    class Snack;
    class Buttons;
    class BillReceiver;
    class VendingMachine;

    // Класс описывающий работу дисплея для вывода информации
    class Display
    {
        public:
            void setDisplayMessage(std::string); // Инициализация сообщения
            void displayMessageOut();            // Вывод сообщения на дисплей машины

        private:
            std::string displayMessage_; // Сообщение дисплея
    };

    // Класс описывающий продаваемый товар 
    class Snack
    {
        public:
            Snack();
            Snack(std::string, short, short);

            void setQuantitySnack(short);     // Инициализация количества товара
            short getQuantitySnack() const;   // Получение количества товара
            std::string getNameSnack() const; // Получение наименование товара
            short getPriceSnack() const;      // Получение цены товара за единицу
            void snackReduce();               // Уменьшение товара

        private:
            std::string snackName_; // Наименование товара
            short snackQuantity_;   // Количество товара
            short snackPrice_;      // Цена товара за единицу
    };

    // Класс описывающий работу кнопок выбора товара
    class Buttons
    {
        public:
            Buttons();

            void buttonsActivity(bool);          // Активация блока управления для вобора товара
            void buttonsMenu(Snack* const);      // Вывод меню блока управления
            void buttonsPress();                 // Выбор кнопки товара
            short getButtonsChooseSnack() const; // Получение выбранного товара

        private:
            bool buttonsActivity_;     // true  - блок активен
                                       // false - блок не активен
            short buttonsChooseSnack_; // Выбранный товар
    };

    // Класс описывающий работу купюроприемника
    class BillReceiver
    {
        public:
            BillReceiver();

            void setAcceptedBill(Display* const);                        // Реализация приема денежной купюры
            short getAcceptedBill() const;                               // Получение внесенной купюры
            bool brEnoughBill(Snack* const, Buttons* const);             // Определение дастаточности внесенных денег
            void brChange(Display* const, Snack* const, Buttons* const); // Нужно ли выдать сдачу?
            void brAcceptedBillNull();                                   // Обнуление внесенных денег
            
        private:
            short brAcceptedBill_; // Принятая купюра

    };

    // Основной класс описания вендинговой машины
    class VendingMachine
    {
        public:
            void addSlot(Display* const, Snack* const);                    // Загрузить лоток в аппарат
            void issueSnack(Display* const, Snack* const, Buttons* const); // Выдача товара
            bool checkAvailability(Snack* const, Buttons* const);          // Проверка наличия выбранного товара
    };
}

#endif // VMC_H
