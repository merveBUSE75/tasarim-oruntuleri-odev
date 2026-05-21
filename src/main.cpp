#include <iostream>
#include <string>
#include <vector>

enum class NesneTipi { OYUNCU, DUSMAN, ADAPTER };

class OlayDinleyici {
public:
    virtual ~OlayDinleyici() {}
    virtual void onOlayGerceklesti(std::string olayTipi, std::string nesneIsmi) = 0;
};

class BasariSistemi : public OlayDinleyici {
public:
    void onOlayGerceklesti(std::string olayTipi, std::string nesneIsmi) override {
        if (olayTipi == "OLUM") {
            std::cout << "[BAŞARI SİSTEMİ BİLDİRİMİ] -> '" << nesneIsmi << "' öldü! 'İlk Kan' başarısı kazanıldı!\n";
        }
    }
};


class HareketStratejisi {
public:
    virtual ~HareketStratejisi() {}
    virtual void hareketEt(std::string isim) = 0;
};
class YuruyerekHareket : public HareketStratejisi {
public:
    void hareketEt(std::string isim) override {
        std::cout << "[HAREKET] " << isim << " yavaşça yürüyerek ilerliyor.\n";
    }
};
class UcarakHareket : public HareketStratejisi {
public:
    void hareketEt(std::string isim) override {
        std::cout << "[HAREKET] " << isim << " kanatlarını açtı ve uçarak hızla ilerliyor! (OCP aktif)\n";
    }
};

class OyunNesnesi {
protected:
    std::vector<OlayDinleyici*> dinleyiciler;
public:
    std::string isim;
    int can;

    OyunNesnesi(std::string i, int c) : isim(i), can(c) {}
    virtual ~OyunNesnesi() {}

    virtual void guncelle() = 0;
    virtual void etkilesimYap() = 0;

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


class NesneFabrikasi {
public:
    static OyunNesnesi* nesneOlustur(NesneTipi tip, std::string isim, int can) {
        if (tip == NesneTipi::OYUNCU) return new Oyuncu(isim, can);
        if (tip == NesneTipi::DUSMAN) return new Dusman(isim, can);
        if (tip == NesneTipi::ADAPTER) return new SesSistemiAdapter(isim);
        return nullptr;
    }
};


int main() {
    std::vector<OyunNesnesi*> oyunDunyasi;
    OlayDinleyici* basariTakipçisi = new BasariSistemi();

    OyunNesnesi* kahraman = NesneFabrikasi::nesneOlustur(NesneTipi::OYUNCU, "Savaşçı", 100);
    OyunNesnesi* canavar = NesneFabrikasi::nesneOlustur(NesneTipi::DUSMAN, "Ork", 50);
    canavar->dinleyiciEkle(basariTakipçisi);

    oyunDunyasi.push_back(kahraman);
    oyunDunyasi.push_back(canavar);

    std::cout << "--- Oyun Basliyor (Faz 3 - Behavioral) ---\n";
    
    kahraman->guncelle();
    
     Oyuncu* asilOyuncu = dynamic_cast<Oyuncu*>(kahraman);
    if (asilOyuncu != nullptr) {
        asilOyuncu->hareketStratejisiDegistir(new UcarakHareket());
    }
 
    std::cout << "\n--- Strateji Degistikten Sonra ---\n";
    kahraman->guncelle();

    std::cout << "\n--- Etkilesimler ve Tetiklenen Olaylar ---\n";
    canavar->etkilesimYap();

    delete kahraman;
    delete canavar;
    delete basariTakipçisi;
    oyunDunyasi.clear();

    return 0;
}
