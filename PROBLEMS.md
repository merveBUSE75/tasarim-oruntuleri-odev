# FAZ-1
   ##  BENİM GÖRDÜĞÜM SORUNLAR## 
1.	Single Responsibility Principle (SRP - Tek Sorumluluk Prensibi) İhlali
Bu kısımda bir sınıfın sadece bir sorumluluğu olmalıdır ama kodda OyunNesnesi sınıfının birden fazla sorumluluğu olduğu için tek sorumluluk prensibini ihlal ediyor .
SORUN:OyunNesnesi sınıfı hem oyuncu hareketini, hem düşman yapay zekasını, hem de eşya toplama mantığını barındırıyor.Bu yüzden kod karmaşıklaşır.
DOĞRUSU: Her sınıfın sadece tek amacı olmalı düzeltme olarak hepsi için yeni sınıf oluşturup onun içinde yazabiliriz. 

2.	Open/Closed Principle (OCP - Açık/Kapalı Prensibi) İhlali 
Bu prensip de kod geliştirilmeye açık ama değiştirilmeye kapalı olmalıdır .
SORUN:Ama kodumuzda Yeni bir nesne tipi (örneğin Engel) eklemek için mevcut guncelle ve etkilesimYap fonksiyonlarının içine yeni if-else blokları eklemek zorundayız.
Kod genişletilmeye açık değil; yeni özellik eklemek için çalışan kodu değiştirmek (modifiye etmek) zorunda kalıyoruz.


3.	Liskov Substitution Principle (LSP - Liskov'un Yerine Geçme Prensibi) İhlali
Bu prensip de alt sınıflar,türetikleri üst sınıfların davranışını bozmamalıdır.Üst sınıfın kullandığı her yerde alt sınıfda sorunsuz çalışmalıdır .
SORUN? Şu an tüm nesneler tek bir sınıfta toplandığı için sorun gizli duruyor ama ESYA tipi için can değişkeni anlamsızdır.AÇIKLAMA: Eğer bunları alt sınıflara ayırırsak ve Esya sınıfı OyunNesnesi'nden türetilirse, "can" özelliğini kullanamayan bir nesne, üst sınıfın tüm özelliklerini karşılayamaz hale gelir.

4.	Interface Segregation Principle (ISP - Arayüz Ayrımı Prensibi) İhlali
Bu prensip de istemciler ,kullanmadıkları metodlara sahip arayüzler uygulamaya zorlanmamalıdır .
Devasa arayüzlere yerine ,daha küçük ve amaca yönelik arayüzler tanımlanmalıdır.
SORUN: Her nesne, ihtiyaç duymadığı davranışları (metotları) barındırmak zorunda kalıyor.
AÇIKLAMA: Örneğin bir ESYA (iksir), guncelle metoduna ihtiyaç duymaz ama mevcut yapıda bu metodu boş da olsa taşımak zorunda kalıyor. Nesneler kullanmadıkları metotlara bağımlı kılınmış durumda.

5.	Dependency Inversion Principle (DIP - Bağımlılıkların Tersine Çevrilmesi Prensibi) İhlali
Bu prensip de yüksek seviyeli modüller, düşük seviye modüllere bağımli olmalıdır .Her ikiside soyutlamalra  yani arayüzlere bağımlı olmalıdır. SORUN: Üst seviye mantık (oyun döngüsü), alt seviye detaylara (nesne tiplerine) doğrudan bağımlı.AÇIKLAMA: main fonksiyonu, somut nesne tiplerini (NesneTipi::OYUNCU) bilmek zorunda. Oysa sistem soyutlamalara (interface) bağımlı olmalıydı.


          AL'IN GÖRDÜĞÜ SORUNLAR
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


     Ben Ne Gördüm, AI Ne Gördü? Aralarındaki Farklar?
     Yapay zeka ile yaptığım analiz sonucunda kendi gözlemlerim ve AI önerileri arasındaki benzerlikleri ve farkları şu şekilde özetleyebilirim:

1. Ortak Tespitler (Benzerlikler)
SOLID İhlalleri: Hem ben hem de AI, kodun Single Responsibility (SRP) ve Open/Closed (OCP) prensiplerini ağır şekilde ihlal ettiği konusunda hemfikiriz.

If-Else Karmaşası: Her iki analiz de if-else yapısının genişletilebilirliği engellediğini ve "Spagetti Kod" riskini artırdığını vurguladı.

Nesne Oluşturma: Nesnelerin main içinde elle oluşturulmasının (Hardcoding) bir tasarım sorunu olduğu her iki tarafta da belirtildi.

2. AI'ın Eklediği Teknik Derinlik (Farklar)
Pattern Önerileri: Ben sorunu "yeni sınıf oluşturma" olarak tanımlarken, AI bu sorunu çözmek için Strategy, Factory Method ve State gibi spesifik tasarım örüntülerini önerdi.

LSP ve ISP Detayları: Ben daha çok kodun genel yapısına odaklanırken, AI nesne hiyerarşisindeki Liskov Substitution ve Interface Segregation gibi daha ince SOLID detaylarını ortaya çıkardı.

Mimari Yaklaşım: AI, oyun motorlarında yaygın olan Component-Based Design (Bileşen Tabanlı Tasarım) kavramını tanıtarak, sadece sınıf ayırmanın ötesinde bir mimari vizyon sundu.

3. Sonuç ve Yol Haritası
Bu karşılaştırma sonucunda, sadece sınıfları ayırmanın yeterli olmayacağını, nesne üretimini Factory Method ile merkezileştirmem ve davranışları Polymorphism ile dağıtmam gerektiğini anladım. Faz 1 aşamasında öncelikle nesne üretimindeki karmaşayı çözmeye odaklanacağım.

