#pragma once
#ifndef ROM_H
#define ROM_H
#include <ROM.h>
#endif
#include <inttypes.h>

struct INTS
{
    public:
    INTS(uint16_t *regs, uint8_t adress){
        this->adress = adress;
        this->romadr = -1;
        this->v = 0;
        this->regs = regs;
    }
    INTS(uint16_t *regs, uint8_t adress, int romadr){
        this->adress = adress;
        this->regs = regs;
        if (romadr > 299 || romadr < 0){
            this->romadr = -1;
            this->v = 0;
        }else{
            this->romadr = romadr;
            this->v = rom.getInt(romadr);
            regs[adress] = (uint16_t)v;
        }
    }
    int get(){
        this->v = regs[adress];
        rom.setInt(romadr, v);
        return v;
    }
    void set(int value){
        this->v = value;
        rom.setInt(romadr, v);
        regs[adress] = (uint16_t)v;
    }
    
    private:
    int v;
    uint8_t adress;
    int romadr;
    uint16_t *regs;
    ROM rom;
};