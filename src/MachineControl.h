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

//NOTE - Temel süre ayarları
unsigned long millisecond;//arduino millis() fonksiyonunu her döngüde 1 defa çalıştırmak için değişken oluşturuldu
unsigned long m_buzzer_fault = 40;//arıza durumunda 4 saniye boyunca buzzer'ın sinyal vermesi için süre ayarı
unsigned long m_buzzer_info = 2;//reset yapıldığında eğer bir sorun yoksa buzzer 200ms'lik sinyal süre ayarı
unsigned long m_reset_button_delay = 10;//reset yapmak için stop butonuna 1 saniye basılıtutma süre ayarı
unsigned long m_machine_speed_interval = 600;//makinenin üretim hızını hesaplamak için 1 dakikalık döngü süre ayarı
int product_count_for_machine_speed = 0;//1 dakikanın sonunda kaç adet üretim yapıldığının tutulduğu değişken

//NOTE - Zamanlayıcıların tanımlanması
/**
 * TMR name(&[unsigned long TIME_REF]) TIME_REF birimi 100ms'dir
 * 2 = 200ms
 * 10 = 1 saniye
 * 40 = 4 saniye
 * 600 = 1 dakika
 * HMI ekranda Numeric Input oluşturulurken 1,0 şeklinde ayarlandığında kolaylık olması için bu şekilde ayarlandı.
 * @see TMR.h
 */
TMR tmr_buzzer_fault(&m_buzzer_fault), tmr_buzzer_info(&m_buzzer_info), tmr_reset_button_delay(&m_reset_button_delay);
TMR tmr_machine_speed_interval(&m_machine_speed_interval);

/**
 * @brief system_reset_control
 * reset ve acil durdurma kontrollerinin yapıldığı fonksiyon
 * döngü boyunca sürekli kontrol edilir.
 * stop butonu veya ekrandan gönderilen reset komutu ile arıza var mı kontrol eder
 * eğer bir sorun yoksa sistem aktif olur. sistem aktif değilse tüm çıkışlar durdurulur
 * VEYA(||) operatörü ile başka arıza durumları eklenebilir. 
 * Örneğin bir motorun arıza sinyali alınır ve bu sinyal geldiğinde sistem durdurulur.
 * Arıza bilgisinin reset anında false yapılması gerekir. Böylece arıza halen devam ediyorsa buzzer tekrar arıza sinyali üretebilir.
 */
void system_reset_control(){
    if (!system_reset_info.get())
    {
        if (system_reset_button.get() || tmr_reset_button_delay.ON(millisecond, !io_stop.get()))
        {
            system_reset_info.set(true);
            emergency_stop_info.set(false);
        }
    }
    if (emergency_stop_info.get() /* || veya diğerleri */)
    {
        system_reset_info.set(false);
    }
    emergency_stop_info.set(!io_emergency.get());
}

/**
 * @brief production_control
 * üretimin başlatılıp durdurulmasının kontrolü
 * arıza varsa üretim duracaktır
 * sistem hazırsa start stop butonları ile üretim kontol edilebilir
 */
void production_control(){
    if (system_reset_info.get() && (io_start.get() || production_start_button.get())) { production_info.set(true); }
    if (!system_reset_info.get() || !io_stop.get() || production_stop_button.get()) { production_info.set(false); }
    production_stop_info.set(!production_info.get());
}

/**
 * @brief buzzer_control
 * buzzer ya da kırmızı ikaz lambasının kontrolü
 * sadece timer kontrolleri için ayrılmış bir fonksiyon
 * arıza durumunda 4 saniye ve sorun yok ikazı için 200ms sinyalinin kontrolü
 */
bool buzzer_control(){
    bool wFault = false; bool wInfo = false;
    if (system_reset_info.get())
    {
        wInfo = true; wFault = false;
        tmr_buzzer_fault.IN(); tmr_buzzer_info.IN(millisecond);
        if (tmr_buzzer_info.Q(millisecond)) { wInfo = false; }
    }
    else
    {
        wFault = true; wInfo = false;
        tmr_buzzer_info.IN(); tmr_buzzer_fault.IN(millisecond);
        if (tmr_buzzer_fault.Q(millisecond)) { wFault = false; }
    }
    return wFault || wInfo;
}

/**
 * @brief work_control
 * manuel ve otomatik çalışacak cihazların kontrolü
 * üretim başlatıldığında manuel çıkışlar kesilir
 * manuel kontrole geçildiğinde otomatik çıkışları kesilir
 * üretimin durumuna göre çıkışların iletilmesi gerçekleştirilir
 * yine arıza durumunda tüm çıkışların kesilmesini burası kontrol eder
 */
void work_control(){
    bool production = production_info.get();
    if (!system_reset_info.get() || production)
    {//ÜRETİM VARSA DURDURULACAKLAR 
        manu_output_0_info.set(false);
        manu_output_1_info.set(false);
        manu_output_2_info.set(false);
        manu_output_3_info.set(false);
        manu_output_4_info.set(false);
        manu_output_5_info.set(false);
    }
    if (!system_reset_info.get() || !production)
    {//ÜRETİM YOKSA DURDURULACAKLAR
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

/**
 * @brief io_control
 * fiziksel sinyallerin ekrana veya ekrandan gelen sinyallerin fiziksel çıkışlara iletilmesini kontrol eder
 * ayrıca analog çıkışın (bu durumda sürücü hızı örnek alınmış) iletildiği yer
 */
void io_control(){
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

/**
 * @brief calculate_machine_speed
 * makine hızının hesaplandığı ve üretim adetlerinin kaydedildiği fonksiyon
 * get() fonksiyonu çağırılmadığında modbus sistemine işlenmiyor ve rom'a kayıt olmuyor.
 * @see BITS.h FLOATS.h INTS.h LONGS.h
 */
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
    total_product_count.get();
    daily_product_count.get();
}

/**
 * @brief automatic_control
 * otomatik çalışacak algoritma buraya yazılmalıdır
 */
void automatic_control(bool production){
    if (production)
    {
        //TODO - DoSomething
    }
}


/**
 *  @brief machine_run
 * main.cpp içinden bu kısım çağırılır ve makinenin kontrolleri tek fonksiyondan sırasıyla gerçekleşir
 * yukarıda her sistemin fonksiyonlara ayrılmasının ve burada sıraya koyulmasının sebebi budur.
 * yani tüm sistem hazır, sırasıyla automatic_control() fonksiyonu içinde çalışacak sistemi tanımlamak yeterlidir.
 */
void machine_run(){
    millisecond = millis();
    system_reset_control();
    production_control();
    io_lamp.put(production_info.get());
    io_buzzer.put(buzzer_control());
    calculate_machine_speed();
    work_control();
    automatic_control(production_info.get());
    io_control();
}