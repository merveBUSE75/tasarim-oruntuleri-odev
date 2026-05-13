
     BENİM GÖRDÜĞÜM SORUNLAR 
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

