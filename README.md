# Arduino Nano Plc
  indusrial arduino nano plc 8DI 8DO 1AO
 Tasarım amacı; kontrol panelli, 4 adet sensör ve 6 adet valf bağlanabilen kompak ve endüstriyel bir cihaz üretmek.


### Güç voltajı 24V Max 6A
8 dijital giriş PNP
8 dijital çıkış NPN
1 analog çıkış 0-10V
1 rs485 seri veriyolu Modbus RTU 8N1

### Besleme Voltajı
Güç girişi için önerilen voltaj 24V olarak belirlendi.
Yapılan testlerde 12-30V arası düzgün çalıştığı gözlemlendi.
PLC kartı maksimum 6A yük taşıyabilir. Eğer daha fazla bir yük gerekiyorsa anahtarlama elemanları ile (role gibi) yük karttan alınabilir.

### Dijital Girişler
4 adet PNP giriş sensör besleme voltajı klemenste bulunduğu için doğrudan bağlantı yapılabilir.
4 adet PNP giriş kontrol paneli buton bağlantıları için ayrıldı. (klemens grubu ayrı)

### Dijital Çıkışlar
6 adet NPN çıkış kontaktör, role, solenoid valf için besleme voltajı klemenste bulunduğu için direk bağlantı yapılabilir.
2 adet NPN çıkış kontrol paneli ikaz lambaları bağlantıları için ayrıldı. (klemens grubu ayrı)

### Analog Çıkış
1 adet 0-10V 12 bit analog çıkış programlanabilir.

### Seri Veriyolu
1 adet RS485 bağlantı ile Modbus RTU Master cihazlarla iletişim kurabilir.
Arduino nano'nun getirdiği kısıtlama nedeniyle haberleşme parametresi yalnızca 8N1 ayarlanabilir.
önerilen haberleşme hızı 9600 baud rate'dir. 115200 baud rate hızına kadar destekler.
250 word hafıza alanına kadar destekler ve tüm modbus adresleri aynı alana referans verir.
örneğin, holding register 400010 ile 300010 aynı adrese karşılık gelir.
veya, coil 10 ile input coil 10 aynı adrese karşılık gelir
son olarak ÖNEMLİ!!! coil 10 = input coil 10 = holding register 400000.10 = input register 300000.10 aynı adreslerdir.
tüm değerler REGS.h içinde uint16_t data[250]; dizisi ile tutulur.

### Kontrol Paneli
Start Butonu
Stop Butonu
Acil Stop Butonu
Ürün Sensörü

Yeşil İkaz Lambası
Kırmızı İkaz Lambası

### Çalışma Şekli
İlk enerjilendiğinde veya bir arıza durumunda sistem reset gereklidir.
Stop Butonuna 1 saniye basılı tutulduğunda sistem reset aktif olur.
Arıza durumunda pasif olur ve korumaya alır. Örneğin acil durdurma veya bir arıza koşulu eklenirse.
Yine arıza durumunda Kırmızı İkaz Lambası veya Buzzer sinyal verir.
Start Butonuna basıldığında üretim başlar ve Stop Butonu ile üretim durdurulur.
Üretim başladığında Yeşil İkaz Lambası sinyal verir.
Ürün Sensörü aslında bir döngülük otomatik hareketi başlatmak için tasarlandı ve sinyal kontrol panelinden alındı.
Bu bağlantılar yapıldıktan sonra;
4 adet dijital giriş PNP (3 kablolu sensörler direk bağlanabiliyor)
6 adet dijital çıkış NPN (2 kablo direk kontaktöre veya valfe bağlanabilir)
Bu kısım kartın PCB bağlantılarında detaylandırılacak.

Modbus kütüphanesi hakkında detaylı bilgi için ziyaret ediniz. 
https://github.com/smarmengol/Modbus-Master-Slave-for-Arduino

PlatformIO 
include hatalarını gidermek için .vscode\c_cpp_properties.json dosyasını kontrol edin