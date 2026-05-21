# AI Log - Faz 1

## 1. AI'a Ne Sordunuz? (Prompt)
"GitHub Desktop üzerinden phase-1 branch'ini nasıl açabilirim? Ayrıca Faz 1 gereksinimleri olan nesne yaratma sorumluluğunu merkezi bir yapıya taşıma (Factory Method) işlemini kodumda nasıl uygularım? Mevcut kodumu amatör bir stilde kalarak nasıl iyileştirebilirim?"


## 2. AI Ne Yanıtladı? (Özet)
- **GitHub Süreci:** Branch açma, commit yapma ve Issue (#1) ile bağlama adımları detaylandırıldı.
- **Tasarım Örüntüsü:** Nesne oluşturma karmaşasını çözmek için **Factory Method** (Fabrika Metodu) önerildi.
- **Teknik Detay:** `OyunNesnesi` sınıfının soyutlaştırılması ve nesne üretiminin `NesneFabrikasi` sınıfına devredilmesi gerektiği belirtildi. Bellek yönetimi için `unique_ptr` kullanımı tavsiye edildi.

## 3. Siz Ne Uyguladınız ve Neden Farklı/Aynı?
- **Uygulanan:** AI'ın önerdiği Factory Method yapısı ve sınıf hiyerarşisi (Oyuncu, Dusman, Esya) birebir uygulandı.
- **Neden ayni** Bu yapı, Faz 0'da `main` içerisinde bulunan karmaşık `if-else` bloklarını ortadan kaldırarak kodun esnekliğini artırdığı için tercih edildi.
Çünkü koddaki sorun çok netti ve yapay zekanın önerdiği Factory Method yapısı bu sorunu çözdü. Başlangıç kodunda main fonksiyonu, hangi nesnenin nasıl üretileceğini tek tek el yazısıyla bilmek zorundaydı. Bu durum sınıflar arasında bağlılık yaratıyor ve oyuna yeni bir nesne türü eklemeyi zorlaştırıyordu . Önerilen mimarisi, nesne yaratma sürecini tek bir merkezde toplayarak bu bağımlılığı kökten çözdü. Yapay zekanın sunduğu çözüm, projenin bu fazdaki "nesne üretimini soyutlama" hedefini eksiksiz karşıladığı ve kodun bakımını doğrudan kolaylaştırdığı için yapıda çok bir değişikliğe gidilmedi.

## 4. Faz 1 UML Diyagramı (Factory Method)

```mermaid
classDiagram
    class OyunNesnesi {
        <<Abstract>>
        +string isim
        +guncelle()*
        +etkilesimYap()*
    }
    class Oyuncu {
        +guncelle()
        +etkilesimYap()
    }
    class Dusman {
        +guncelle()
        +etkilesimYap()
    }
    class Esya {
        +guncelle()
        +etkilesimYap()
    }
    class NesneFabrikasi {
        +olustur(NesneTipi, string) OyunNesnesi
    }

    OyunNesnesi <|-- Oyuncu
    OyunNesnesi <|-- Dusman
    OyunNesnesi <|-- Esya
    NesneFabrikasi ..> OyunNesnesi : Nesne Üretir
