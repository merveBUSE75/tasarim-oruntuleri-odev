# PATTERNS.md - Faz 1

## Uygulanan Örüntü: Factory Method (Fabrika Metodu)

### 1. Nerede Kullanıldı?
Projenin nesne yaratma kısmında kullandım. Daha önce `main.cpp` içerisinde elle oluşturulan **Oyuncu**, **Düşman** ve **Eşya** nesneleri, artık merkezi bir `NesneFabrikasi` sınıfı üzerinden üretilmektedir.Sınıfları somut nesnelere bağımlı olmaktan kurtarmak için.

### 2. Neden Seçildi?
* **Bağımlılıkların Tersine Çevrilmesi :** `main` fonksiyonunun somut sınıflara olan doğrudan bağımlılığını kesmek için.Kodun esnek olması için .
* **Açık/Kapalı Prensibi:** Yeni bir nesne tipi eklemek istediğimizde mevcut oyun döngüsü koduna dokunmadan,yeni sınıf ekliyebiliyoruz . Yeni sınıf eklerken mevcut kodun bozulmaması gerekiyor bu yüzden.

### 3. Ne Kazandırdı?
* **Tek Sorumluluk:** Nesne yaratma sorumluluğu tek bir merkezde toplandı.
* **Esneklik:** Kodun okunabilirliği arttı ve hata payı azaldı.
* **Soyutlama:** İstemci kod (main), nesnelerin nasıl yaratıldığıyla değil, sadece ne iş yaptıklarıyla ilgilenir hale geldi.
