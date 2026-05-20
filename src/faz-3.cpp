#include <iostream>
#include <string>
#include <vector>

enum class NesneTipi { OYUNCU, DUSMAN, ADAPTER };

// =================================================================
// 1. BEHAVIORAL PATTERN - 1: OBSERVER (GÖZLEMCİ)
// =================================================================
// Oyun içindeki olayları dinleyecek olanların (Gözlemcilerin) arayüzü
class OlayDinleyici {
public:
    virtual ~OlayDinleyici() {}
    virtual void onOlayGerceklesti(std::string olayTipi, std::string nesneIsmi) = 0;
};

// Somut Gözlemci: Başarı Sistemi (Achievement System)
class BasariSistemi : public OlayDinleyici {
public:
    void onOlayGerceklesti(std::string olayTipi, std::string nesneIsmi) override {
        if (olayTipi == "OLUM") {
            std::cout << "[BAŞARI SİSTEMİ BİLDİRİMİ] -> '" << nesneIsmi << "' öldü! 'İlk Kan' başarısı kazanıldı!\n";
        }
    }
};

// =================================================================
// 2. BEHAVIORAL PATTERN - 2: STRATEGY (STRATEJİ)
// =================================================================
// Hareket davranışlarının ortak arayüzü
class HareketStratejisi {
public:
    virtual ~HareketStratejisi() {}
    virtual void hareketEt(std::string isim) = 0;
};

// Somut Strateji 1: Yürüyerek Hareket
class YuruyerekHareket : public HareketStratejisi {
public:
    void hareketEt(std::string isim) override {
        std::cout << "[HAREKET] " << isim << " yavaşça yürüyerek ilerliyor.\n";
    }
};

// Somut Strateji 2: Uçarak Hareket (OCP İSPATI: Mevcut kodu bozmadan eklenen yeni davranış)
class UcarakHareket : public HareketStratejisi {
public:
    void hareketEt(std::string isim) override {
        std::cout << "[HAREKET] " << isim << " kanatlarını açtı ve uçarak hızla ilerliyor! (OCP aktif)\n";
    }
};

// =================================================================
// 3. EN BAŞTAN BERİ GELEN TEMEL OYUN NESNESİ VE ALT SINIFLARI
// =================================================================
class OyunNesnesi {
protected:
    // Observer için dinleyicileri tutan liste
    std::vector<OlayDinleyici*> dinleyiciler;
public:
    std::string isim;
    int can;

    OyunNesnesi(std::string i, int c) : isim(i), can(c) {}
    virtual ~OyunNesnesi() {}

    virtual void guncelle() = 0;
    virtual void etkilesimYap() = 0;

    // Observer Metotları
    void dinleyiciEkle(OlayDinleyici* d) {
        dinleyiciler.push_back(d);
    }
    void olayYayinla(std::string olayTipi) {
        for (OlayDinleyici* d : dinleyiciler) {
            if (d != nullptr) d->onOlayGerceklesti(olayTipi, isim);
        }
    }
};

class Oyuncu : public OyunNesnesi {
private:
    HareketStratejisi* mevcutHareket; // Strateji nesnesi pointer'ı
public:
    Oyuncu(std::string i, int c) : OyunNesnesi(i, c) {
        mevcutHareket = new YuruyerekHareket(); // Varsayılan olarak yürür
    }
    ~Oyuncu() {
        delete mevcutHareket;
    }
    
    // Çalışma zamanında hareketi değiştirmeyi sağlayan metot (Strategy Setter)
    void hareketStratejisiDegistir(HareketStratejisi* yeniStrateji) {
        if (mevcutHareket != nullptr) delete mevcutHareket;
        mevcutHareket = yeniStrateji;
    }

    void guncelle() override {
        std::cout << "[OYUNCU] " << isim << " için güncelleniyor...\n";
        mevcutHareket->hareketEt(isim); // Davranışı strateji sınıfına devrediyoruz
    }
    void etkilesimYap() override {
        std::cout << isim << " envanterini kontrol etti.\n";
    }
};

class Dusman : public OyunNesnesi {
public:
    Dusman(std::string i, int c) : OyunNesnesi(i, c) {}
    void guncelle() override {
        std::cout << "[DUSMAN] " << isim << " devriye geziyor.\n";
    }
    void etkilesimYap() override {
        std::cout << isim << " oyuncuya saldırdı! Canı azaldı.\n";
        this->can = 0; // Test amaçlı canı sıfırlıyoruz
        std::cout << isim << " öldü!\n";
        olayYayinla("OLUM"); // Olayı tüm gözlemcilere duyuruyoruz
    }
};

// =================================================================
// FAZ 2'DEN GELEN ADAPTER PATTERN
// =================================================================
class EskiSesSistemi {
public:
    void eskiSesiCal(std::string dosyaAdi) {
        std::cout << "[DIŞ KÜTÜPHANE] '" << dosyaAdi << "' çalınıyor...\n";
    }
};

class SesSistemiAdapter : public OyunNesnesi {
private:
    EskiSesSistemi* hariciSes;
public:
    SesSistemiAdapter(std::string i) : OyunNesnesi(i, 0) {
        hariciSes = new EskiSesSistemi();
    }
    ~SesSistemiAdapter() { delete hariciSes; }
    void guncelle() override { std::cout << "[ADAPTER] Ses motoru aktif.\n"; }
    void etkilesimYap() override { hariciSes->eskiSesiCal(isim + ".wav"); }
};

// =================================================================
// FAZ 1'DEN GELEN FABRİKA
// =================================================================
class NesneFabrikasi {
public:
    static OyunNesnesi* nesneOlustur(NesneTipi tip, std::string isim, int can) {
        if (tip == NesneTipi::OYUNCU) return new Oyuncu(isim, can);
        if (tip == NesneTipi::DUSMAN) return new Dusman(isim, can);
        if (tip == NesneTipi::ADAPTER) return new SesSistemiAdapter(isim);
        return nullptr;
    }
};

// =================================================================
// MAIN - İSTEMCİ KODU
// =================================================================
int main() {
    std::vector<OyunNesnesi*> oyunDunyasi;
    
    // Başarı sistemi (Gözlemci) nesnesi oluşturuluyor
    OlayDinleyici* basariTakipçisi = new BasariSistemi();

    // Nesneler fabrikadan alınıyor
    OyunNesnesi* kahraman = NesneFabrikasi::nesneOlustur(NesneTipi::OYUNCU, "Savaşçı", 100);
    OyunNesnesi* canavar = NesneFabrikasi::nesneOlustur(NesneTipi::DUSMAN, "Ork", 50);

    // Düşmanın ölüm olayını başarı sistemine bağlıyoruz (Observer Kayıt)
    canavar->dinleyiciEkle(basariTakipçisi);

    oyunDunyasi.push_back(kahraman);
    oyunDunyasi.push_back(canavar);

    std::cout << "--- Oyun Basliyor (Faz 3 - Behavioral) ---\n";
    
   
    kahraman->guncelle();
    
    // STRATEGY VE OCP İSPATI: 
    // Oyuncu sınıfının kodunu hiç değiştirmeden, çalışma zamanında hareket stratejisini değiştiriyoruz
    Oyuncu* asilOyuncu = dynamic_cast<Oyuncu*>(kahraman);
    if (asilOyuncu != nullptr) {
        asilOyuncu->hareketStratejisiDegistir(new UcarakHareket());
    }
    
    // 2. Durum: Kahraman artık yeni eklenen stratejiyle (Uçarak) hareket eder
    std::cout << "\n--- Strateji Degistikten Sonra ---\n";
    kahraman->guncelle();

    // OBSERVER İSPATI: Düşman etkileşime girdiğinde ölecek ve başarı sistemi otomatik tetiklenecek
    std::cout << "\n--- Etkilesimler ve Tetiklenen Olaylar ---\n";
    canavar->etkilesimYap();

    // Temizlik
    delete kahraman;
    delete canavar;
    delete basariTakipçisi;
    oyunDunyasi.clear();

    return 0;
}
