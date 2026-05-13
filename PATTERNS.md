# PATTERNS.md - Faz 1

## Uygulanan Örüntü: Factory Method (Fabrika Metodu)

### 1. Nerede Kullanıldı?
Projenin nesne yaratma kısmında kullanıldı. Daha önce `main.cpp` içerisinde manuel (elle) oluşturulan **Oyuncu**, **Düşman** ve **Eşya** nesneleri, artık merkezi bir `NesneFabrikasi` sınıfı üzerinden üretilmektedir.

### 2. Neden Seçildi?
* **Bağımlılıkların Tersine Çevrilmesi (DIP):** `main` fonksiyonunun somut sınıflara olan doğrudan bağımlılığını kesmek için.
* **Açık/Kapalı Prensibi (OCP):** Yeni bir nesne tipi eklemek istediğimizde mevcut oyun döngüsü koduna dokunmadan, sadece fabrikaya yeni bir kural ekleyerek sistemi genişletebilmek için.

### 3. Ne Kazandırdı?
* **Tek Sorumluluk (SRP):** Nesne yaratma sorumluluğu tek bir merkezde toplandı.
* **Esneklik:** Kodun okunabilirliği arttı ve hata payı azaldı.
* **Soyutlama:** İstemci kod (main), nesnelerin nasıl yaratıldığıyla değil, sadece ne iş yaptıklarıyla ilgilenir hale geldi.
