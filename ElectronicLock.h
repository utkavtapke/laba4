#ifndef ELECTRONIC_LOCK_H
#define ELECTRONIC_LOCK_H

#include <string>

class ElectronicLock {
private:
    bool isLocked;
    bool isClosed;
    bool isPowered;
    int wrongAttempts;
    std::string secretPassword;

public:
    ElectronicLock();
    ElectronicLock(std::string password, bool powerStatus);

    bool lock();
    bool unlock(std::string password);
    void closeDoor();
    void openDoor();
    void resetAlarm();
    void togglePower();

    bool getIsLocked() const { return isLocked; }
    bool getIsClosed() const { return isClosed; }
    bool getIsPowered() const { return isPowered; }
    int getWrongAttempts() const { return wrongAttempts; }
};

#endif
