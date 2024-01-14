#pragma once
#ifndef ROM_H
#define ROM_H
#include <ROM.h>
#endif
#include <inttypes.h>
struct BITS
{
    public:
    BITS(uint16_t *regs, uint8_t adress){
        this->adrs = adress / 16;
        this->index = adress % 16;
        this->regs = regs;
        this->romadr = -1;
        v = false;
    }
    BITS(uint16_t *regs, uint8_t adress, int romadr){
        this->adrs = adress / 16;
        this->index = adress % 16;
        this->regs = regs;
        if (romadr > 191 || romadr < 0){
            this->romadr = -1;
            this->v = false;
        }else{
            this->romadr = romadr;
            this->v = rom.getBit(romadr);
            if (v){
                regs[adrs] |= 1 << index;
            }else{
                regs[adrs] &= ~(1 << index);
            }
        }
    }
    bool get(){
        this->v = regs[adrs] & (1 << index);
        rom.setBit(romadr, v);
        return v;
    }
    void set(bool value){
        this->v = value;
        rom.setBit(romadr, value);
        if (v){
            regs[adrs] |= 1 << index;
        }else{
            regs[adrs] &= ~(1 << index);
        }
    }
    
    private:
    bool v;
    uint8_t adrs;
    uint8_t index;
    int romadr;
    uint16_t *regs;
    ROM rom;
};


