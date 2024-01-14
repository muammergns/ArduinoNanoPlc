#include <BITS.h>
#include <INTS.h>
#include <LONGS.h>
#include <FLOATS.h>
#include <Wire.h>
#ifndef IO_H
#define IO_H
#include <IO.h>
#endif

/** Analog çıkış aktarımı
 * @brief
 * bu kısım tarama zamanını optimize etmek için eklendi
 * eğer aynı değer geliyorsa tekrar veriyi göndermemeli
 * analog çıkış kullanılacaksa öncelikle aktif edilmeli
 */
bool isAnalogActive = false;
int lastAnalogValue = 0;
void analogBegin(){
    Wire.begin();
    isAnalogActive = true;
}

void writeAnalog(int val){
    if (isAnalogActive && val >= 0 && val <= 4095)
    {
        if (lastAnalogValue!=val)
        {
            lastAnalogValue = val;
            Wire.beginTransmission(0x60);
            Wire.write(64);
            Wire.write(val >> 4);
            Wire.write((val & 15) << 4);
            Wire.endTransmission();
        }
    }
}



/** IO konfigürasyonu
 * @brief
 * arduino nano pinleri tasarlanan pcb için konfigüre edilmiştir.
 * bu kısımda yapılacak değişiklik pcb'nin çalışmasında hatalara neden olabilir
 */
//IO iomodbus_tx(0, INPUT);//TX D0
//IO iomodbus_rx(1, INPUT);//RX D1

IO io_output_0(2, OUTPUT);//D2
IO io_output_1(3, OUTPUT);//D3 PWM
IO io_output_2(4, OUTPUT);//D4
IO io_output_3(5, OUTPUT);//D5 PWM
IO io_output_4(6, OUTPUT);//D6 PWM
IO io_output_5(7, OUTPUT);//D7
IO io_input_0(8, INPUT_PULLUP);//D8
IO io_input_1(9, INPUT_PULLUP);//D9 PWM
IO io_input_2(10, INPUT_PULLUP);//D10 PWM SS
IO io_input_3(11, INPUT_PULLUP);//D11 PWM MOSI

IO io_buzzer(12, OUTPUT);//D12 MISO
IO io_lamp(13, OUTPUT);//D13 LED SCK

IO io_start(14, INPUT_PULLUP);//A0
IO io_stop(15, INPUT_PULLUP);//A1
IO io_emergency(16, INPUT_PULLUP);//A2
IO io_product(17, INPUT_PULLUP);//A3

//IO ioA4(18, INPUT);//A4 SDA
//IO ioA5(19, INPUT);//A5 SCL

//IO ioPOT2(20, INPUT);//A6 (only adc)
//IO ioPOT1(21, INPUT);//A7 (only adc)

uint16_t data[250];
/** VAR name([DATA], [MODBUS_ADRESS], [ROM_ADRESS]);
 * VAR = [BITS, INTS, LONGS, FLOATS]
 * BITS   : 1 bit
 * INTS   : 16 bit
 * LONGS  : 32 bit
 * FLOATS : 32 bit
 * INTS nameInt(data,0); ile BITS nameBit(data,0~15); çakışacaktır.
 * LONGS nameLong(data,0); ile INTS nameInt(data,1); çakışacaktır.
 * FLOATS nameFloat(data,0); ile LONGS nameLong(data,0); farklı data tipleridir.
 * Master programlanırken bunlara dikkat edilmelidir. Aksi halde veri kayıpları olacaktır
 * 
 * ROM_ADRESS için herhangi bir çakışma söz konusu değildir sadece limitler vardır.
 * BITS   : 192
 * INTS   : 299 bit
 * LONGS  : 99 bit
 * FLOATS : 99 bit
 * adet değişken kalıcı hafıza olarak ayarlanabilir.
 * kalıcı hafıza pil gerektirmez ve programlama sırasında silinmez
 * kalıcı hafıza için arduino nano 1024 byte kullanılabilir
 * kalıcı hafıza flash memory olduğu için yazma adet ömürleri düşüktür
 * bu yüzden örneğin saniyede 1 kalıcı hafıza güncellemek kısa sürede arduino nanoya zarar verecektir
 * okuma için böyle bir kısıtlama yoktur.
 */


BITS system_reset_button(data, 0);
BITS production_start_button(data, 1);
BITS production_stop_button(data, 2);
BITS production_info(data, 3);
BITS production_stop_info(data, 4);
BITS emergency_stop_info(data, 5);
BITS system_reset_info(data, 6);

BITS hmi_start_button_info(data, 7);
BITS hmi_stop_button_info(data, 8);
BITS hmi_acil_button_info(data, 9);
BITS hmi_product_sensor_info(data, 10);

BITS hmi_input_0_info(data, 11);
BITS hmi_input_1_info(data, 12);
BITS hmi_input_2_info(data, 13);
BITS hmi_input_3_info(data, 14);

BITS hmi_output_0_info(data, 20);
BITS hmi_output_1_info(data, 21);
BITS hmi_output_2_info(data, 22);
BITS hmi_output_3_info(data, 23);
BITS hmi_output_4_info(data, 24);
BITS hmi_output_5_info(data, 25);

BITS manu_output_0_info(data, 30);
BITS manu_output_1_info(data, 31);
BITS manu_output_2_info(data, 32);
BITS manu_output_3_info(data, 33);
BITS manu_output_4_info(data, 34);
BITS manu_output_5_info(data, 35);

BITS auto_output_0_info(data, 40);
BITS auto_output_1_info(data, 41);
BITS auto_output_2_info(data, 42);
BITS auto_output_3_info(data, 43);
BITS auto_output_4_info(data, 44);
BITS auto_output_5_info(data, 45);



LONGS total_product_count(data, 12, 0);
LONGS daily_product_count(data, 14, 1);
INTS machine_work_speed_per_hour(data, 16);
INTS inverter_speed(data, 17, 0);
