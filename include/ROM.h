#include <EEPROM.h>
//1000 - 1023 bits 192ad bit 0 - 191
//600 - 999 longs 100ad long 0 - 99 and floats
//0 - 599 ints 300ad int 0 - 299
union Pointer
{
    uint16_t asInts[2];
    float asFloat;
};
struct ROM
{
    void setBit(int adr, bool val){
        if (adr > 191 || adr < 0) return;
        uint8_t v = EEPROM.read(1000 + (adr/8));
        bool r = v & (1 << adr % 8);
        if (val != r){
            if (val)
            {
                v |= 1 << adr % 8;
            }else{
                v &= ~1 << adr % 8;
            }
            EEPROM.write(1000 + (adr/8), v);
        }
    }
    bool getBit(int adr){
        if (adr > 191 || adr < 0) return false;
        uint8_t val = EEPROM.read(1000 + (adr/8));
        return val & (1 << adr % 8);
    }
    void setInt(int adr, int val){
        if (adr > 299 || adr < 0) return;
        if(getInt(adr) != val){
            uint8_t lb = val;
            uint8_t hb = val >> 8;
            EEPROM.write(adr * 2, lb);
            EEPROM.write((adr * 2) + 1, hb);
        }
    }
    int getInt(int adr){
        if (adr > 299 || adr < 0) return 0;
        return EEPROM.read(adr * 2) + (EEPROM.read((adr * 2) + 1) << 8);
    }
    void setLong(int adr, long val){
        if (adr > 99 || adr < 0) return;
        if (getLong(adr) != val)
        {
            uint8_t llb = val;
            uint8_t lhb = val >> 8;
            uint8_t hlb = val >> 16;
            uint8_t hhb = val >> 24;
            EEPROM.write((adr * 4) + 600,llb);
            EEPROM.write((adr * 4) + 601,lhb);
            EEPROM.write((adr * 4) + 602,hlb);
            EEPROM.write((adr * 4) + 603,hhb);
        }
    }
    long getLong(int adr){
        if (adr > 99 || adr < 0) return 0;
        return (long)EEPROM.read((adr * 4) + 600) + 
        ((long)EEPROM.read((adr * 4) + 601) << 8) + 
        ((long)EEPROM.read((adr * 4) + 602) << 16) + 
        ((long)EEPROM.read((adr * 4) + 603) << 24);
    }
    void setFloat(int adr, uint16_t lb, uint16_t hb){
        if (adr > 99 || adr < 0) return;
        union Pointer p;
        p.asInts[0] = hb;
        p.asInts[1] = lb;
        if (getFloat(adr) != p.asFloat)
        {
            long val = (long)((long)lb + ((long)hb << 16));
            uint8_t llb = val;
            uint8_t lhb = val >> 8;
            uint8_t hlb = val >> 16;
            uint8_t hhb = val >> 24;
            EEPROM.write((adr * 4) + 600,llb);
            EEPROM.write((adr * 4) + 601,lhb);
            EEPROM.write((adr * 4) + 602,hlb);
            EEPROM.write((adr * 4) + 603,hhb);
        }
    }
    float getFloat(int adr){
        if (adr > 99 || adr < 0) return 0;
        union Pointer p;
        long v = (long)EEPROM.read((adr * 4) + 600) + 
        ((long)EEPROM.read((adr * 4) + 601) << 8) + 
        ((long)EEPROM.read((adr * 4) + 602) << 16) + 
        ((long)EEPROM.read((adr * 4) + 603) << 24);
        p.asInts[1] = (uint16_t)v;
        p.asInts[0] = (uint16_t)((uint32_t)v >> 16);
        return p.asFloat;
    }   
};

