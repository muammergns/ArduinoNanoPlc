struct TMR
{
    public:
    /// @brief 
    /// @param PT 
    TMR(unsigned long* PT){
        this->PT = PT;
    }
    //TMR(unsigned long PT){
    //    this->PT = &PT;
    //}
    long ET(unsigned long millis){
        if (EN) return millis - (*PT * 100) + ST;
        return 0;
    }
    bool Q(unsigned long millis){
        if (EN) return millis - ST > (*PT * 100);
        return false;
    }
    void IN(unsigned long millis){
        if (!this->EN){
            this->ST = millis;
            this->EN = true;
        }   
    }
    void IN(unsigned long millis, bool ENABLE){
        if (!this->EN && ENABLE){
            this->ST = millis;
        }
        this->EN = ENABLE;
    }
    void IN(){
        this->EN = false;
    }
    bool ON(unsigned long millis, bool ENABLE){
        if (!this->EN && ENABLE){
            this->ST = millis;
        }
        this->EN = ENABLE;
        if (EN) {
            if (millis - ST > (*PT * 100))
            {
                this->EN = false;
                return true;
            }
        }
        return false;
    }
    private: 
    unsigned long ST = 0;
    bool EN = false;
    unsigned long* PT;

};
