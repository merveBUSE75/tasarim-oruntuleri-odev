# ogrenci bilgileri
adi:merve buse 
soyadı:demiray
numara:241229055
bölümü:yazılım mühendisliği

# konu seçimi 
konu :mini oyun 

# Mini Oyun Motoru Modeli (Yazılım Tasarım Örüntüleri Ödevi)

Bu proje, Yazılım Tasarım Örüntüleri dersi kapsamında, başlangıçta hantal ve spagetti kod olarak yazılmış bir oyun nesnesi sisteminin aşama aşama tasarım kalıpları kullanılarak esnek ve genişletilebilir hale getirilmiş bir simülasyonudur.

## 🛠 Kullanılan Tasarım Örüntüleri (Pattern Listesi)

Projede üç farklı faz boyunca toplam 5 adet tasarım örüntüsü uygulanmıştır

### 1. Creational (Nesne Yaratma) 
* **Factory Method (Fabrika Örüntüsü):** Oyuncu, Düşman veya Eşya gibi nesnelerin `main` içinde elle (`new`) üretilmesini engeller.Üretim sorumluluğunu `NesneFabrikasi` sınıfına devrederek bağımlılıkları azaltır.

### 2. Structural (Yapısal) 
* **Adapter (Adaptör Örüntüsü):** Proje kod yapısına uymayan dışarıdan alınmış eski bir ses kütüphanesini (`EskiSesSistemi`), mevcut sisteme dokunmadan oyuna entegre etmeyi sağlar.
* **Decorator (Süsleyici Örüntüsü):** Karakterlerin temel kodlarını hiç değiştirmeden, çalışma zamanında onlara dinamik olarak "Kalkan" veya "Zehir" gibi ekstra özellikler giydirmemizi sağlar

### 3. Behavioral (Davranışsal)
* **Strategy (Strateji Örüntüsü):** Nesnelerin davranışlarını (örneğin hareket etme mantığını) dinamik hale getirir.Oyuncunun mevcut kodunu kırmadan "Yuruyerek" olan hareket stilini "Ucarak" olarak değiştirmemizi sağlar (Open/Closed Prensibi).
***Observer (Gözlemci Örüntüsü):** Nesneler arası haberleşmeyi sağlar. Oyundaki düşman öldüğü anda `BasariSistemi` (Achievement) durumdan otomatik haberdar olur ve ekrana başarı bildirimi basar.

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
