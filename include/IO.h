#include <Arduino.h>


struct IO
{
    public:
    /// @brief arduino pin configurator
    /// @param numberPin pin number 0-20
    /// @param modePin pin mode INPUT, OUTPUT, INPUT_PULLUP
    IO(uint8_t numberPin, uint8_t modePin){
        pinMode(numberPin, modePin);
        if (modePin==1)
        {
            digitalWrite(numberPin, LOW);
        }
        
        this->pin = numberPin;
        this->mode = modePin;
    }
    /// @brief arduino pin configurator
    /// @param numberPin pin number 0-20
    /// @param modePin pin mode INPUT, OUTPUT, INPUT_PULLUP
    /// @param filterCount input delay for noise
    IO(uint8_t numberPin, uint8_t modePin, unsigned int filterCount){
        pinMode(numberPin, modePin);
        if (modePin==1)
        {
            digitalWrite(numberPin, LOW);
        }
        
        this->pin = numberPin;
        this->mode = modePin;
        this->filter = filterCount;
    }

    void build(){
        pinMode(pin, mode);
        if (mode==1)
        {
            digitalWrite(pin, LOW);
        }
    }

    bool get(){
        bool s = digitalRead(pin) == 1;
        return get(mode == INPUT_PULLUP ? !s : s);
    }
    bool get(bool s){
        if (s){
            if (ih>=filter){
                st = true;
            }else{
                ih++;
            }
            il = 0;
        }else{
            if (il>=filter * 10){
                st = false;
            }else{
                il++;
            }
            ih = 0;
        }
        return st;
    }
    int geta(){
        return analogRead(pin);
    }
    void set(){
        digitalWrite(pin, HIGH);
    }
    void rst(){
        digitalWrite(pin, LOW);
    }
    void put(bool value){
        digitalWrite(pin, value);
    }
    uint8_t getPinNumber(){
        return pin;
    }
    private:
        uint8_t pin;
        uint8_t mode;
        unsigned int ih = 0;
        unsigned int il = 0;
        bool st = false;
        unsigned int filter = 10;
};


