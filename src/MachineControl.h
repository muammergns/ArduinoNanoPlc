#pragma once
#ifndef REG_H
#define REG_H
#include <REGS.h>
#endif
#ifndef IO_H
#define IO_H
#include <IO.h>
#endif
#ifndef TMR_H
#define TMR_H
#include <TMR.h>
#endif

unsigned long millisecond;
unsigned long m_buzzer_fault = 40;
unsigned long m_buzzer_info = 2;
unsigned long m_reset_button_delay = 10;
unsigned long m_machine_speed_interval = 600;

int product_count_for_machine_speed = 0;
TMR tmr_buzzer_fault(&m_buzzer_fault), tmr_buzzer_info(&m_buzzer_info), tmr_reset_button_delay(&m_reset_button_delay);
TMR tmr_machine_speed_interval(&m_machine_speed_interval);


void system_reset_control(bool stopButton){
    if (!system_reset_info.get())
    {
        if (system_reset_button.get() || tmr_reset_button_delay.ON(millisecond, !stopButton))
        {
            system_reset_info.set(true);
            emergency_stop_info.set(false);
        }
    }
    if (emergency_stop_info.get() /* || veya diğerleri */)
    {
        system_reset_info.set(false);
    }
}

void production_control(bool startButton, bool stopButton){
    if (system_reset_info.get() && (startButton || production_start_button.get())) { production_info.set(true); }
    if (!system_reset_info.get() || !stopButton || production_stop_button.get()) { production_info.set(false); }
    production_stop_info.set(!production_info.get());
}

bool buzzer_control(){
    bool wFault = false;
    bool wInfo = false;
    if (system_reset_info.get())
    {
        wInfo = true;
        wFault = false;
        tmr_buzzer_fault.IN();
        tmr_buzzer_info.IN(millisecond);
        if (tmr_buzzer_info.Q(millisecond))
        {
            wInfo = false;
        }
    }
    else
    {
        wFault = true;
        wInfo = false;
        tmr_buzzer_info.IN();
        tmr_buzzer_fault.IN(millisecond);
        if (tmr_buzzer_fault.Q(millisecond))
        {
            wFault = false;
        }
    }
    return wFault || wInfo;
}

void work_control(bool production){
    if (!system_reset_info.get() || production)
    {
        //ÜRETİM VARSA DURDURULACAKLAR
        manu_output_0_info.set(false);
        manu_output_1_info.set(false);
        manu_output_2_info.set(false);
        manu_output_3_info.set(false);
        manu_output_4_info.set(false);
        manu_output_5_info.set(false);
    }
    if (!system_reset_info.get() || !production)
    {
        //ÜRETİM YOKSA DURDURULACAKLAR
        auto_output_0_info.set(false);
        auto_output_1_info.set(false);
        auto_output_2_info.set(false);
        auto_output_3_info.set(false);
        auto_output_4_info.set(false);
        auto_output_5_info.set(false);
    }
    hmi_output_0_info.set(production ? auto_output_0_info.get() : manu_output_0_info.get());
    hmi_output_1_info.set(production ? auto_output_1_info.get() : manu_output_1_info.get());
    hmi_output_2_info.set(production ? auto_output_2_info.get() : manu_output_2_info.get());
    hmi_output_3_info.set(production ? auto_output_3_info.get() : manu_output_3_info.get());
    hmi_output_4_info.set(production ? auto_output_4_info.get() : manu_output_4_info.get());
    hmi_output_5_info.set(production ? auto_output_5_info.get() : manu_output_5_info.get());
}


void io_control(bool production){
    hmi_start_button_info.set(io_start.get());
    hmi_stop_button_info.set(io_stop.get());
    hmi_acil_button_info.set(io_emergency.get());
    hmi_product_sensor_info.set(io_product.get());

    hmi_input_0_info.set(io_input_0.get());
    hmi_input_1_info.set(io_input_1.get());
    hmi_input_2_info.set(io_input_2.get());
    hmi_input_3_info.set(io_input_3.get());
    
    io_output_0.put(hmi_output_0_info.get());
    io_output_1.put(hmi_output_1_info.get());
    io_output_2.put(hmi_output_2_info.get());
    io_output_3.put(hmi_output_3_info.get());
    io_output_4.put(hmi_output_4_info.get());
    io_output_5.put(hmi_output_5_info.get());

    writeAnalog(inverter_speed.get());
}


bool product_sensor_rising_edge = false;
void calculate_machine_speed(){
    if (io_product.get() and !product_sensor_rising_edge and production_info.get())
    {
        product_sensor_rising_edge = true;
        product_count_for_machine_speed++;
        total_product_count.set(total_product_count.get()+1);
        daily_product_count.set(daily_product_count.get()+1);
    }
    if (!io_product.get())
    {
        product_sensor_rising_edge = false;
    }
    tmr_machine_speed_interval.IN(millisecond);
    if (tmr_machine_speed_interval.Q(millisecond))
    {
        tmr_machine_speed_interval.IN();
        machine_work_speed_per_hour.set(product_count_for_machine_speed * 60);
        product_count_for_machine_speed = 0;
    }
}


void automatic_control(bool production){

}



void machine_run(){
    millisecond = millis();
    system_reset_control(io_stop.get());
    emergency_stop_info.set(!io_emergency.get());
    production_control(io_start.get(), io_stop.get());
    io_lamp.put(production_info.get());
    io_buzzer.put(buzzer_control());
    calculate_machine_speed();
    total_product_count.get();
    daily_product_count.get();
    work_control(production_info.get());
    automatic_control(production_info.get());
    io_control(production_info.get());
}