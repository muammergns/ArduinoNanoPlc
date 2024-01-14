#pragma once
#ifndef ROM_H
#define ROM_H
#include <ROM.h>
#endif
#include <inttypes.h>

struct LONGS
{
    public:
    /// @brief long init without rom register
    /// @param regs array of modbus library data
    /// @param adress modbus adress
    LONGS(uint16_t *regs, uint8_t adress){
        this->adress = adress;
        this->romadr = -1;
        this->v = 0;
        this->regs = regs;
    }
    /// @brief long init with rom register
    /// @param regs array of modbus library data
    /// @param adress modbus adress
    /// @param romadr rom adress
    LONGS(uint16_t *regs, uint8_t adress, int romadr){
        this->adress = adress;
        this->regs = regs;
        if (romadr > 99 || romadr < 0){
            this->romadr = -1;
            this->v = 0;
        }else{
            this->romadr = romadr;
            this->v = rom.getLong(romadr);
            regs[adress] = (uint16_t)((uint32_t)v >> 16);
            regs[adress + 1] = (uint16_t)v;
        }
    }
    long get(){
        //this->v = (int32_t)((((uint32_t)regs[adress]) << 16) | ((uint32_t)regs[adress + 1] & 0xFFFFFFFF));
        this->v = (long)((long)regs[adress + 1] + ((long)regs[adress] << 16));
        rom.setLong(romadr, v);
        return v;
    }
    void set(long value){
        this->v = value;
        rom.setLong(romadr, v);
        regs[adress] = (uint16_t)((uint32_t)v >> 16);
        regs[adress + 1] = (uint16_t)v;
    }
    
    private:
    long v;
    uint8_t adress;
    int romadr;
    uint16_t *regs;
    ROM rom;
};