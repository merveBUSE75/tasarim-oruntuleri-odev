1. if-else Zinciri ile Davranış Yönetimi

Kodda:

if (tip == NesneTipi::OYUNCU)

else if (tip == NesneTipi::DUSMAN)

else if (tip == NesneTipi::ESYA)

şeklinde davranış ayrımı yapılıyor.

Sorun

Bu yapı:

Yeni nesne tipi eklendiğinde (NPC, Boss, Sandik vb.)

tüm if-else bloklarının değiştirilmesini gerektirir.

Kod büyüdükçe karmaşıklaşır.

Open/Closed Principle ihlal edilir.

(Kod genişlemeye açık ama değiştirmeye kapalı olmalı.)

Ayrıca tüm davranışlar tek sınıfta toplandığı için sınıf aşırı sorumluluk yükleniyor.

Çözüm: Strategy veya Polymorphism

En doğru yaklaşım:

→ Polymorphism (Kalıtım + Sanal Fonksiyonlar)

Örneğin:

class OyunNesnesi {

public:

    virtual void guncelle() = 0;
    
    virtual void etkilesimYap() = 0;
};

Sonra:

class Oyuncu : public OyunNesnesi

class Dusman : public OyunNesnesi

class Esya : public OyunNesnesi

Her sınıf kendi davranışını yazar.

Neden iyi?

if-else kalkar.

Yeni nesne eklemek kolaylaşır.

Kod daha okunabilir olur.

SOLID prensiplerine uygun hale gelir.

2. Nesne Oluşturmanın Elle Yapılması

Kodda:

OyunNesnesi kahraman(...);

OyunNesnesi canavar(...);

şeklinde nesneler manuel oluşturuluyor.

Sorun
Nesne oluşturma mantığı dağınık.

Yeni tipler geldiğinde main() sürekli değişir.

Büyük oyunlarda nesne üretimi merkezi yönetilmezse karmaşa oluşur.

Çözüm: Factory Method / Abstract Factory

→ Factory Method

Örnek:

class NesneFactory {

public:

    static OyunNesnesi* olustur(NesneTipi tip);
    
};

Kullanım:

auto oyuncu = NesneFactory::olustur(NesneTipi::OYUNCU);

Neden iyi?

Nesne üretimi merkezi olur.

Kod tekrarını azaltır.

Yeni nesne tipleri eklemek kolaylaşır.

main() sadeleşir.


3. Tek Sınıfın Fazla Sorumluluk Alması

OyunNesnesi:

veri tutuyor

davranış yönetiyor

tip kontrolü yapıyor

etkileşim yönetiyor

Sorun

Bu durum:

Single Responsibility Principle ihlalidir.

Kodun test edilmesini zorlaştırır.

Büyük projelerde “God Object” problemine dönüşebilir.

Çözüm: Component-Based Design / Entity Component System (ECS)

Özellikle oyun geliştirmede yaygın çözüm:

RenderComponent

MovementComponent

AttackComponent

gibi bileşenlere ayırmaktır.

Neden iyi?

Esnek yapı sağlar.

Kod tekrarını azaltır.

Oyun motorlarında performans ve bakım avantajı sağlar.

4. Tür Bilgisinin (enum) Davranışı Kontrol Etmesi

Kodda:

NesneTipi tip;

davranışın merkezinde.

Sorun

Bu yaklaşım procedural mantığa yakındır.

Nesne yönelimli programlamada davranış nesnenin kendisinde olmalıdır.

Çözüm: State veya Polymorphism

Burada yine polymorphism en uygun çözüm.

Alternatif olarak:

→ State Pattern

Eğer nesneler zaman içinde durum değiştiriyorsa:

Idle

Attack

Dead

Patrol

gibi davranışlar State Pattern ile yönetilebilir.

5. Gevşek Genişletilebilirlik Problemi

Şu an sisteme yeni bir tip eklemek:

enum değiştirme

tüm if-else bloklarını değiştirme

testleri güncelleme

gerektiriyor.

Çözüm: Open/Closed Principle + Polymorphism

Yeni sınıf eklenir:

class Boss : public OyunNesnesi

Mevcut kod değişmeden sistem çalışır.
