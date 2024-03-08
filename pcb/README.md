# PCB tasarımı
Tasarımın tamamı EasyEDA üzerinden yapıldı.
Malzemeler seçilirken sadece delik boyutları ve yerleşime özen gösterildi.
Baskılar JLCPCB ile üretildi
EasyEDA ile proje import yaparak kendiniz de düzenleyebilir veya kontrol edebilirsiniz
Projeyle uğraşmak istemezseniz Gerber dosyasını herhangi bir pcb üreticiye teslim ederek kartları üretebilirsiniz.

Ayrıca PCB montaj yapabileceğiniz bir kutu tasarımı da projeye eklendi. Bunu 3D yazıcı ile üretip kullanabilirsiniz.

![PCB](https://github.com/muammergns/ArduinoNanoPlc/blob/main/pcb/pcb-top.jpg)

## Klemens Bağlantıları
| 1.1 | 1.2 |
| :- | :- |
| Güç +24V | Güç 0V |

| 2.1 | 2.2 | 2.3 | 2.4 | 2.5 | 2.6 | 2.7 | 2.8 |
| :- | :- | :- | :- | :- | :- | :- | :- |
| HMI +24V | HMI 0V | Product IN | Emergency IN | Stop IN | Start IN | Lamp OUT | Buzzer OUT |

| 3.1     | 3.2     |
| :------ | :------ |
| 0-10V + | 0-10V - |

| 4.1    | 4.2    | 4.3    | 4.4    | 4.5    | 4.6    |
| :-     | :-     | :-     | :-     | :-     | :-     |
| OUT 1+ | OUT 1- | OUT 2+ | OUT 2- | OUT 3+ | OUT 3- |

| 4.7    | 4.8    | 4.9    | 4.10   | 4.11   | 4.12   |
| :-     | :-     | :-     | :-     | :-     | :-     |
| OUT 4+ | OUT 4- | OUT 5+ | OUT 5- | OUT 6+ | OUT 6- |

| 5.1     | 5.2     | 5.3       |
| :-      | :-      | :-        |
| RS485 A | RS485 B | RS485 GND |

| 6.1     | 6.2  | 6.3     | 6.4     | 6.5  | 6.6     |
| :-      | :-   | :-      | :-      | :-   | :-      |
| Sensör+ | IN 1 | Sensör- | Sensör+ | IN 2 | Sensör- |

| 6.7     | 6.8  | 6.9     | 6.10    | 6.11 | 6.12    |
| :-      | :-   | :-      | :-      | :-   | :-      |
| Sensör+ | IN 3 | Sensör- | Sensör+ | IN 4 | Sensör- |

### Malzeme Listesi yakında..

### Ürün linkleri yakında..

### Dikkat edilmesi gerekenler
- Karta enerji vermeden önce arduino headerdan sökülmelidir. Voltaj regülatörü trimpot ile `9V` ayarlandıktan sonra arduino yerine takılabilir.
- Arduino headera takılıyken RS485-TTL dönüştürücü sinyalleri bozduğu için programlanamaz. Bu yüzden her program atılırken sökülmelidir.
- Programı yükledikten sonra 0-10V kalibre edilmelidir. 12bit olduğu için analog değere 4095 gönderilir. Ardından trimpot ile `10V` ayarlanır.
