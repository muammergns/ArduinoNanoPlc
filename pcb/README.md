# PCB tasarımı
Tasarımın tamamı EasyEDA üzerinden yapıldı.
Malzemeler seçilirken sadece delik boyutları ve yerleşime özen gösterildi.
Baskılar JLCPCB ile üretildi
EasyEDA ile proje import yaparak kendiniz de düzenleyebilir veya kontrol edebilirsiniz
Projeyle uğraşmak istemezseniz Gerber dosyasını herhangi bir pcb üreticiye teslim ederek kartları üretebilirsiniz.

Ayrıca PCB montaj yapabileceğiniz bir kutu tasarımı da projeye eklendi. Bunu 3D yazıcı ile üretip kullanabilirsiniz.

## Klemens Bağlantıları
1.1: Kart güç +24V
1.2: Kart güç 0V

2.1: HMI için +24V
2.2: HMI için 0V
2.3: Ürün sensörü giriş
2.4: Acil Stop giriş
2.5: Stop butonu giriş
2.6: Start butonu giriş
2.7: Yeşil ikaz çıkış
2.8: Kırmızı ikaz çıkış

3.1: 0-10V +
3.2: 0-10V -

4.1:  OUT 1 +
4.2:  OUT 1 -
4.3:  OUT 2 +
4.4:  OUT 2 -
4.5:  OUT 3 +
4.6:  OUT 3 -
4.7:  OUT 4 +
4.8:  OUT 4 -
4.9:  OUT 5 +
4.10: OUT 5 -
4.11: OUT 6 +
4.12: OUT 6 -

5.1: RS485 A
5.2: RS485 B
5.3: RS485 GND

6.1:  Sensör +
6.2:  IN 1
6.3:  Sensör -
6.4:  Sensör +
6.5:  IN 2
6.6:  Sensör -
6.7:  Sensör +
6.8:  IN 3
6.9:  Sensör -
6.10: Sensör +
6.11: IN 4
6.12: Sensör -

### Malzeme Listesi yakında..

### Ürün linkleri yakında..

### Dikkat edilmesi gerekenler
- Karta enerji vermeden önce arduino headerdan sökülmelidir. Voltaj regülatörü trimpot ile `9V` ayarlandıktan sonra arduino yerine takılabilir.
- Arduino headera takılıyken RS485-TTL dönüştürücü sinyalleri bozduğu için programlanamaz. Bu yüzden her program atılırken sökülmelidir.
- Programı yükledikten sonra 0-10V kalibre edilmelidir. 12bit olduğu için analog değere 4095 gönderilir. Ardından trimpot ile `10V` ayarlanır.
