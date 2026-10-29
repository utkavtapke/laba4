#include "ElectronicLock.h"

ElectronicLock::ElectronicLock() {
    isLocked = false;
    isClosed = false;
    isPowered = true;
    wrongAttempts = 0;
    secretPassword = "1234";
}

ElectronicLock::ElectronicLock(std::string password, bool powerStatus) {
    isLocked = false;
    isClosed = false;
    isPowered = powerStatus;
    wrongAttempts = 0;
    secretPassword = password;
}

bool ElectronicLock::lock() {
    if (!isPowered) return false;
    if (isClosed) {
        isLocked = true;
        return true;
    }
    return false;
}

bool ElectronicLock::unlock(std::string password) {
    if (!isPowered) return true;
    if (wrongAttempts >= 3) return false;

    if (password == secretPassword) {
        isLocked = false;
        wrongAttempts = 0;
        return true;
    } else {
        wrongAttempts++;
        return false;
    }
}

void ElectronicLock::closeDoor() {
    isClosed = true;
}
