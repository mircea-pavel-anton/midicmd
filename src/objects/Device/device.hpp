#ifndef DEVICE_CLASS
#define DEVICE_CLASS

#include "../Utils/utils.hpp"

class Device {
    public:
        int portId;
        string name;
        bool isSet;

        Device() : portId(-1), name(""), isSet(false) {}
        Device(int _id, string _name) : portId(_id), name(_name), isSet(true) {}

        void clear() {
            portId = -1;
            name = "";
            isSet = false;
        }
        void set(int _id, string _name) {
            portId = _id;
            name = _name;
            isSet = true;
        }
};

#endif //DEVICE_CLASS