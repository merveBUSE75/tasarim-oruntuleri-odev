# Mini Oyun Motoru Modeli (Yazılım Tasarım Örüntüleri Ödevi)

[cite_start]Bu proje, Yazılım Tasarım Örüntüleri dersi kapsamında, başlangıçta hantal ve spagetti kod olarak yazılmış bir oyun nesnesi sisteminin aşama aşama tasarım kalıpları kullanılarak esnek ve genişletilebilir hale getirilmiş bir simülasyonudur[cite: 7].

## 🛠 Kullanılan Tasarım Örüntüleri (Pattern Listesi)

[cite_start]Projede üç farklı faz boyunca toplam 5 adet tasarım örüntüsü uygulanmıştır[cite: 32, 53, 73]:

### [cite_start]1. Creational (Nesne Yaratma) [cite: 29]
* [cite_start]**Factory Method (Fabrika Örüntüsü):** Oyuncu, Düşman veya Eşya gibi nesnelerin `main` içinde elle (`new`) üretilmesini engeller[cite: 30]. [cite_start]Üretim sorumluluğunu `NesneFabrikasi` sınıfına devrederek bağımlılıkları azaltır[cite: 30].

### [cite_start]2. Structural (Yapısal) [cite: 50]
* **Adapter (Adaptör Örüntüsü):** Proje kod yapısına uymayan dışarıdan alınmış eski bir ses kütüphanesini (`EskiSesSistemi`), mevcut sisteme dokunmadan oyuna entegre etmeyi sağlar.
* [cite_start]**Decorator (Süsleyici Örüntüsü):** Karakterlerin temel kodlarını hiç değiştirmeden, çalışma zamanında onlara dinamik olarak "Kalkan" veya "Zehir" gibi ekstra özellikler giydirmemizi sağlar[cite: 51].

### [cite_start]3. Behavioral (Davranışsal) [cite: 70]
* [cite_start]**Strategy (Strateji Örüntüsü):** Nesnelerin davranışlarını (örneğin hareket etme mantığını) dinamik hale getirir[cite: 71]. [cite_start]Oyuncunun mevcut kodunu kırmadan "Yuruyerek" olan hareket stilini "Ucarak" olarak değiştirmemizi sağlar (Open/Closed Prensibi)[cite: 75].
* [cite_start]**Observer (Gözlemci Örüntüsü):** Nesneler arası haberleşmeyi sağlar[cite: 71]. Oyundaki düşman öldüğü anda `BasariSistemi` (Achievement) durumdan otomatik haberdar olur ve ekrana başarı bildirimi basar.

---

## 📊 Son Durum Mimari Diyagramı (Faz 3 UML)

```mermaid
classDiagram
    class OyunNesnesi {
        <<Abstract>>
        +string isim
        +int can
        +dinleyiciEkle()
        +olayYayinla()
        +guncelle()*
        +etkilesimYap()*
    }
    class Oyuncu {
        -HareketStratejisi* mevcutHareket
        +hareketStratejisiDegistir()
    }
    class Dusman {
    }
    class SesSistemiAdapter {
        -EskiSesSistemi* hariciSes
    }
    class NesneDecorator {
        #OyunNesnesi* sarilanNesne
    }
    class HareketStratejisi {
        <<Interface>>
        +hareketEt()*
    }
    class OlayDinleyici {
        <<Interface>>
        +onOlayGerceklesti()*
    }

    OyunNesnesi <|-- Oyuncu
    OyunNesnesi <|-- Dusman
    OyunNesnesi <|-- SesSistemiAdapter
    OyunNesnesi <|-- NesneDecorator
    
    Oyuncu --> HareketStratejisi
    OyunNesnesi --> OlayDinleyici
    NesneDecorator --> OyunNesnesi
