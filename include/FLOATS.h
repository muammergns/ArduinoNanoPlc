#pragma once
#ifndef ROM_H
#define ROM_H
#include <ROM.h>
#endif
#include <inttypes.h>

union Pointers
{
    uint16_t asInts[2];
    float asFloat;
};

struct FLOATS
{
    public:
    FLOATS(uint16_t *regs, uint8_t adress){
        this->adress = adress;
        this->romadr = -1;
        p.asFloat = 0;
        this->v = p.asFloat;
        this->regs = regs;
    }
    FLOATS(uint16_t *regs, uint8_t adress, int romadr){
        this->adress = adress;
        this->regs = regs;
        if (romadr > 99 || romadr < 0){
            this->romadr = -1;
            p.asFloat = 0;
            this->v = p.asFloat;
        }else{
            this->romadr = romadr;
            p.asFloat = rom.getFloat(romadr);
            this->v = p.asFloat;
            regs[adress] = p.asInts[0];
            regs[adress + 1] = p.asInts[1];
        }
    }
    float get(){
        p.asInts[1] = regs[adress];
        p.asInts[0] = regs[adress + 1];
        this->v = p.asFloat;
        rom.setFloat(romadr, p.asInts[0], p.asInts[1]);
        return v;
    }
    void set(float value){
        p.asFloat = value;
        this->v = p.asFloat;
        rom.setFloat(romadr, p.asInts[0], p.asInts[1]);
        regs[adress] = p.asInts[1];
        regs[adress + 1] = p.asInts[0];
    }
    
    private:
    float v;
    uint8_t adress;
    int romadr;
    uint16_t *regs;
    ROM rom;
    union Pointers p;
};