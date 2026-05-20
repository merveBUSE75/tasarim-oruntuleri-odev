# AI Log - Faz 2 (Structural Patterns)

### 1. AI'a Sorulan Zorunlu Soru
"Adapter pattern burada uygun mu, yoksa Facade mı? Farkını açıkla."

### 2. AI Yanıtının Özeti
AI, bizim durumumuzda kesinlikle **Adapter** örüntüsünün uygun olduğunu belirtti. Çünkü:
- **Adapter (Adaptör):** Uyumsuz iki farklı arayüzü (interface) birbiriyle çalışabilir hale getirir. Mevcut `OyunNesnesi` yapımıza dışarıdan eski bir kütüphane bağlamak istiyorsak araya bir çevirici (adaptör) koymalıyız.
- **Facade (Yüzey/Cephe):** Karmaşık ve çok sayıda sınıftan oluşan bir alt sistemi (subsystem) tek bir basitleştirilmiş sınıf arkasına gizler. 

### 3. Kritik Değerlendirme & Benim Kararım
Bizim amacımız sistemin karmaşıklığını gizlemek değil, sisteme tamamen yabancı/eski bir sınıfı mevcut `OyunNesnesi` yapımıza uydurmaktır. Bu yüzden Facade burada anlamsız kalırdı. AI'ın bu tespiti tamamen doğrudur ve projemizde dış kütüphane entegrasyonu için Adapter örüntüsü kullanılmasına karar verilmiştir.
