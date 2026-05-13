1. Single Responsibility Principle (SRP - Tek Sorumluluk Prensibi) İhlali
   Neden sorun? OyunNesnesi sınıfı hem oyuncu hareketini, hem düşman yapay zekasını, hem de eşya toplama mantığını barındırıyor.
   Açıklama: Bir sınıfta yapılacak bir değişiklik (örneğin düşman hasarını değiştirmek), tamamen alakasız olan oyuncu mantığını bozma riski taşıyor.
   Sınıfın değişmek için birden fazla nedeni var.
3. Open/Closed Principle (OCP - Açık/Kapalı Prensibi) İhlali
   Neden sorun? Yeni bir nesne tipi (örneğin Engel) eklemek için mevcut guncelle ve etkilesimYap fonksiyonlarının içine yeni if-else blokları eklemek zorundayız.
   Açıklama: Kod genişletilmeye açık değil; yeni özellik eklemek için çalışan kodu değiştirmek (modifiye etmek) zorunda kalıyoruz.
5. Liskov Substitution Principle (LSP - Liskov'un Yerine Geçme Prensibi) İhlali
   Neden sorun? Şu an tüm nesneler tek bir sınıfta toplandığı için sorun gizli duruyor ama ESYA tipi için can değişkeni anlamsızdır.
   Açıklama: Eğer bunları alt sınıflara ayırırsak ve Esya sınıfı OyunNesnesi'nden türetilirse, "can" özelliğini kullanamayan bir nesne, üst sınıfın tüm özelliklerini karşılayamaz hale gelir.
6. Interface Segregation Principle (ISP - Arayüz Ayrımı Prensibi) İhlali
   Neden sorun? Her nesne, ihtiyaç duymadığı davranışları (metotları) barındırmak zorunda kalıyor.
   Açıklama: Örneğin bir ESYA (iksir), guncelle metoduna ihtiyaç duymaz ama mevcut yapıda bu metodu boş da olsa taşımak zorunda kalıyor.
   Nesneler kullanmadıkları metotlara bağımlı kılınmış durumda.
8. Dependency Inversion Principle (DIP - Bağımlılıkların Tersine Çevrilmesi Prensibi) İhlali
   Neden sorun? Üst seviye mantık (oyun döngüsü), alt seviye detaylara (nesne tiplerine) doğrudan bağımlı.
   Açıklama: main fonksiyonu, somut nesne tiplerini (NesneTipi::OYUNCU) bilmek zorunda.
   Oysa sistem soyutlamalara (interface) bağımlı olmalıydı.
