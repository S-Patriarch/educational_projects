//╔════════════════════════════════════════════════════════════════════════════════════════════════╗
//║ (c) Patriarch, 2023                                                                            ║
//║     Реализация внешних (::) функций.                                                           ║
//╚════════════════════════════════════════════════════════════════════════════════════════════════╝
#include <string>
#include <cstdint>
#include <string>
#include "constants.h"

//┌────────────────────────────────────────────────────────────────────────────────────────────────┐
//│ Шифрование и расшифровка строки.                                                               │
//│ Принимает:                                                                                     │
//│     fEncDec   - флаг работы шифра:                                                             │
//│                 1 - шифрование                                                                 │
//│                 0 - расшифровка                                                                │
//│     &strInput - ссылка на строку для шифрования/расшифровки                                    │
//│     iKey      - ключ для шифрования/расшифровки                                                │
//│                 ключ должен быть в диапазоне:                                                  │
//│                      от cst::MIN_SIZE_ALPHABET + 1                                             │
//│                      по cst::MAX_SIZE_ALPHABET - 1                                             │
//│ Возвращает:                                                                                    │
//│     strOutput - зашифрованная/расшифрованная строка                                            │
//│                 "ERROR_FLAG" - признак ошибки, не правильный флаг                              │
//│                 "ERROR_KEY"  - признак ошибки, не правильный ключ                              │
//└────────────────────────────────────────────────────────────────────────────────────────────────┘
std::string encdec(const std::uint16_t fEncDec, const std::string &strInput, const std::int32_t iKey)
{
    // Проверка флага работы шифра
    if (fEncDec != 1 && fEncDec != 0) {
        return "ERROR_FLAG";
    }

    // Проверка ключа на соответствие диапазону
    if (iKey < (cst::MIN_SIZE_ALPHABET + 1) || iKey > (cst::MAX_SIZE_ALPHABET - 1)) {
        return "ERROR_KEY";
    }

    bool okFlag {true};
    std::string strOutput {};

    for (std::uint32_t i = 0; i < strInput.length(); i++) {
        okFlag = false;

            for (std::int32_t j = 0; j < cst::MAX_SIZE_ALPHABET; j++) {
                if (strInput[i] == cst::CHAR_LOW[j]) {
                    if (fEncDec == 1) {
                        j += iKey;
                    }
                    else if (fEncDec == 0) {
                        j -= iKey;	
                    }

                    // Если значение вышло за диапазон алфавита, закольцовываем его
                    if (j >= cst::MAX_SIZE_ALPHABET) {
                        j = (cst::MIN_SIZE_ALPHABET + 
                            (iKey - ((cst::MAX_SIZE_ALPHABET-1) - (j - iKey)))) - 1;
                    }
                    else if (j < cst::MIN_SIZE_ALPHABET) {
                        j = ((j + iKey) + cst::MAX_SIZE_ALPHABET) - iKey;
                    }

                    // Отписываем измененный символ во возвращаемую строку
                    strOutput += cst::CHAR_LOW[j];

                    okFlag = true;
                    break;
                }
                else if (strInput[i] == cst::CHAR_HIGH[j]) {
                    if (fEncDec == 1) {
                        j += iKey;
                    }
                    else if (fEncDec == 0) {
                        j -= iKey;	
                    }

                    // Если значение вышло за диапазон алфавита, закольцовываем его
                    if (j >= cst::MAX_SIZE_ALPHABET) {
                        j = (cst::MIN_SIZE_ALPHABET + 
                            (iKey - ((cst::MAX_SIZE_ALPHABET-1) - (j - iKey)))) - 1;
                    }
                    else if (j < cst::MIN_SIZE_ALPHABET) {
                        j = ((j + iKey) + cst::MAX_SIZE_ALPHABET) - iKey;
                    }

                    // Отписываем измененный символ во возвращаемую строку
                    strOutput += cst::CHAR_HIGH[j];

                    okFlag = true;
                    break;
                }
            }

            // Если символ не в диапазоне алфавита, пишим его без изменений
            if (!okFlag) {
                strOutput += strInput[i];
            }
    }

    return strOutput;
}
