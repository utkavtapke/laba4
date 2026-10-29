#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include "ElectronicLock.h"

std::string getInputHidden() {
    std::string password;
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    std::cin >> password;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << std::endl;
    return password;
}

void printLockStatus(const ElectronicLock& lock) {
    std::cout << "\n========================================\n";
    std::cout << " МОНИТОРИНГ ЭЛЕКТРОННОГО ЗАМКА:\n";
    std::cout << " Питание от сети: " << (lock.getIsPowered() ? "СТАБИЛЬНО" : "ОТКЛЮЧЕНО (АВАРИЯ)") << "\n";
    std::cout << " Физическое положение двери: " << (lock.getIsClosed() ? "Прихлопнута" : "Открыта настежь") << "\n";
    std::cout << " Ригель (засов) замка: " << (lock.getIsLocked() ? "ВЫДВИНУТ (ЗАПЕРТО)" : "УБРАН (ОТПЕРТО)") << "\n";
    std::cout << " Ошибки ввода кода: " << lock.getWrongAttempts() << " из 3\n";
    if (lock.getWrongAttempts() >= 3) {
        std::cout << " [СИСТЕМА БЛОКИРОВАНА. ВЫЗОВИТЕ МАСТЕРА]\n";
    }
    std::cout << "========================================\n";
}

int main() {
    ElectronicLock myLock("7777", true);
    int work = 1;
    int command;

    while (work) {
        printLockStatus(myLock);

        std::cout << "Выберите команду управления:\n";
        std::cout << "1. Захлопнуть дверь\n";
        std::cout << "2. Запереть на засов\n";
        std::cout << "3. Ввести секретный код разблокировки\n";
        std::cout << "4. Распахнуть дверь настежь\n";
        std::cout << "5. Сбросить блокировку тревоги (Мастер-ключ)\n";
        std::cout << "6. Отключить/Включить электропитание замка\n";
        std::cout << "0. Завершить работу симулятора\n";
        std::cout << ">> ";

        std::cin >> command;

        switch (command) {
            case 1:
                myLock.closeDoor();
                std::cout << "Вы прихлопнули дверь.\n";
                break;
            case 2:
                if (myLock.lock()) {
                    std::cout << "Засов успешно задвинут в косяк.\n";
                } else {
                    std::cout << "Ошибка: нельзя запереть открытую или обесточенную дверь!\n";
                }
                break;
            case 3: {
                std::cout << "Введите 4 цифры кода (ввод скрыт): ";
                std::string inputCode = getInputHidden();
                if (myLock.unlock(inputCode)) {
                    std::cout << "Код верный! Замок открыт.\n";
                } else {
                    std::cout << "ОТКАЗ В ДОСТУПЕ! Неверный код или превышен лимит попыток.\n";
                }
                break;
            }
            case 4:
                myLock.openDoor();
                if (!myLock.getIsClosed()) {
                    std::cout << "Вы открыли дверь.\n";
                } else {
                    std::cout << "Дверь заклинена! Сначала уберите засов кодом.\n";
                }
                break;
            case 5:
                myLock.resetAlarm();
                std::cout << "Счетчик неверных попыток обнулен.\n";
                break;
            case 6:
                myLock.togglePower();
                std::cout << "Переключение линии питания выполнено.\n";
                break;
            case 0:
                work = 0;
                break;
            default:
                std::cout << "Ошибка: Неизвестный идентификатор команды!\n";
                break;
        }
    }
    return 0;
}
