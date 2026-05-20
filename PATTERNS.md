# PATTERNS.md - Faz 1

## Uygulanan Örüntü: Factory Method (Fabrika Metodu)

### 1. Nerede Kullanıldı?
Projedeki oyuncu, düşman ve eşya gibi nesnelerin oluşturulduğu kısımda kullandım. Eskiden bunları main.cpp içinde tek tek el yazısıyla new diyerek üretiyordum. Şimdi ise hepsini NesneFabrikasi diye tek bir sınıfın içine topladım ve üretimi oradan yapıyorum.

### 2. Neden Seçildi?
if-else Yapılarından Kurtulmak İçin: Eski kodda main fonksiyonu hangi nesnenin nasıl kurulacağını, içine ne parametre alacağını tek tek bilmek zorundaydı. Bu da kodları birbirine çok bağlıyordu. Fabrika kullanarak main'i bu dertten kurtardım.

Yeni Karakter Ekleme Kolaylığı (Open/Closed): Oyuna ileride yeni bir nesne tipi (mesela Tuzak veya NPC) eklemek istediğimde, gidip main içindeki çalışan oyun döngüsünü bozmak istemiyorum. Yeni bir tip geldiğinde mevcut koda dokunmadan, sadece yeni bir sınıf açıp sisteme ekleyebilmek için bu örüntüyü seçtim.

### 3. Ne Kazandırdı?
Kodlar Birbirine Karışmıyor (Tek Sorumluluk): Nesnelerin oyun içindeki görevleri ile onların ilk başta nasıl üretileceği işini birbirinden ayırdım. Üretim işi artık tek bir merkezden dönüyor.

Main Fonksiyonu Sadeleşti: main fonksiyonu artık arka planda nesnelerin nasıl yaratıldığıyla, hangi constructor'ı çağırdığıyla ilgilenmiyor. Sadece fabrikaya "bana bir düşman ver" diyor ve işine bakıyor.

Daha Temiz Kod: Kodun okunması çok daha kolaylaştı. Yarın bir gün nesnelerin can değerlerini veya parametrelerini değiştirmek istersem, projenin her yerini değil sadece fabrika sınıfının içini


```mermaid

classDiagram
    class NesneTipi {
        <<enumeration>>
        OYUNCU
        DUSMAN
        ESYA
    }

    class OyunNesnesi {
        +NesneTipi tip
        +string isim
        +int can
        +OyunNesnesi(NesneTipi t, string i, int c)
        +guncelle()
        +etkilesimYap()
    }

    class main {
        // İstemci kod
        // OyunNesnesi kahraman
        // OyunNesnesi canavar
        // OyunNesnesi iksir
    }

    OyunNesnesi --> NesneTipi : kullanir
    main ..> OyunNesnesi : doğrudan bağımlı (new)





classDiagram
    class NesneTipi {
        <<enumeration>>
        OYUNCU
        DUSMAN
        ESYA
    }

    class OyunNesnesi {
        <<abstract>>
        +string isim
        +int can
        +OyunNesnesi(string i, int c)
        +virtual ~OyunNesnesi()
        +virtual guncelle()* void
        +virtual etkilesimYap()* void
    }

    class Oyuncu {
        +Oyuncu(string i, int c)
        +guncelle() void
        +etkilesimYap() void
    }

    class Dusman {
        +Dusman(string i, int c)
        +guncelle() void
        +etkilesimYap() void
    }

    class Esya {
        +Esya(string i, int c)
        +guncelle() void
        +etkilesimYap() void
    }

    class NesneFabrikasi {
        +static nesneOlustur(NesneTipi tip, string isim, int can) OyunNesnesi*
    }

    class main {
        // İstemci kod
        // vector<OyunNesnesi*> oyunDunyasi
    }

    OyunNesnesi <|-- Oyuncu : türetilir
    OyunNesnesi <|-- Dusman : türetilir
    OyunNesnesi <|-- Esya : türetilir

    NesneFabrikasi ..> NesneTipi : kullanir
    NesneFabrikasi ..> OyunNesnesi : üretir (Return Type)
    
    main ..> NesneFabrikasi : sadece fabrikaya bağımlı
    main ..> OyunNesnesi : sadece soyut arayüzü kullanır









değiştirmem yetecek. Hata yapma ihtimalim azaldı.
