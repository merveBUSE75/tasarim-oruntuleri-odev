#include <iostream>
#include <string>
#include <vector>

enum class NesneTipi { OYUNCU, DUSMAN, ESYA, ADAPTER };

class OyunNesnesi {
public:
    std::string isim;
    int can;

    OyunNesnesi(std::string i, int c) : isim(i), can(c) {}
    virtual ~OyunNesnesi() {}

    virtual void guncelle() = 0;
    virtual void etkilesimYap() = 0;
};

class Oyuncu : public OyunNesnesi {
public:
    Oyuncu(std::string i, int c) : OyunNesnesi(i, c) {}
    void guncelle() override {
        std::cout << "[OYUNCU] " << isim << " hareket ediyor.\n";
    }
    void etkilesimYap() override {
        std::cout << isim << " envanterini açtı.\n";
    }
};

class Dusman : public OyunNesnesi {
public:
    Dusman(std::string i, int c) : OyunNesnesi(i, c) {}
    void guncelle() override {
        std::cout << "[DUSMAN] " << isim << " devriye geziyor.\n";
    }
    void etkilesimYap() override {
        std::cout << isim << " oyuncuya saldırdı!\n";
    }
};

class EskiSesSistemi {
public:
    void eskiSesiCal(std::string dosyaAdi) {
        std::cout << "[DIŞ KÜTÜPHANE] '" << dosyaAdi << "' isimli eski 8-bit ses dosyası çalınıyor...\n";
    }
};

class SesSistemiAdapter : public OyunNesnesi {
private:
    EskiSesSistemi* hariciSes; // Sıkı bağlılığı önlemek için nesne referansı tutuyoruz
public:
    SesSistemiAdapter(std::string i) : OyunNesnesi(i, 0) {
        hariciSes = new EskiSesSistemi();
    }
    ~SesSistemiAdapter() {
        delete hariciSes;
    }
    void guncelle() override {
        // Ses sisteminin her karede yapması gereken işlem
        std::cout << "[ADAPTER] Ses motoru arka planda senkronize ediliyor.\n";
    }
    void etkilesimYap() override {
        // Sistem bizim etkilesimYap metodumuzu çağırdığında, biz arka plandaki eski metodu tetikliyoruz
        hariciSes->eskiSesiCal(isim + "_efekt.wav");
    }
};

class NesneDecorator : public OyunNesnesi {
protected:
    OyunNesnesi* sarilanNesne; // İçine süslenecek asıl nesneyi alır
public:
    NesneDecorator(OyunNesnesi* nesne) : OyunNesnesi(nesne->isim, nesne->can), sarilanNesne(nesne) {}
    
    void guncelle() override {
        sarilanNesne->guncelle();
    }
    void etkilesimYap() override {
        sarilanNesne->etkilesimYap();
    }
};


class KalkanDecorator : public NesneDecorator {
public:
    KalkanDecorator(OyunNesnesi* nesne) : NesneDecorator(nesne) {
        // Süslenen nesnenin canını kalkan kadar arttırıyoruz
        sarilanNesne->can += 50; 
    }
    void guncelle() override {
        NesneDecorator::guncelle(); // Asıl nesne görevini yapsın
        std::cout << " --> [SÜS] " << sarilanNesne->isim << " üzerinde aktif Mavi Kalkan parlıyor!\n";
    }
};

class ZehirDecorator : public NesneDecorator {
public:
    ZehirDecorator(OyunNesnesi* nesne) : NesneDecorator(nesne) {}
    void etkilesimYap() override {
        NesneDecorator::etkilesimYap(); // Asıl nesne etkileşime girsin
        std::cout << " --> [SÜS] " << sarilanNesne->isim << " etrafındakilere ekstra Zehir Hasarı veriyor!\n";
    }
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

    OyunNesnesi* kahraman = NesneFabrikasi::nesneOlustur(NesneTipi::OYUNCU, "Savaşçı", 100);
    OyunNesnesi* canavar = NesneFabrikasi::nesneOlustur(NesneTipi::DUSMAN, "Ork", 50);
    OyunNesnesi* sesMotoru = NesneFabrikasi::nesneOlustur(NesneTipi::ADAPTER, "ArkaPlanMuzigi", 0);

    OyunNesnesi* kalkanliKahraman = new KalkanDecorator(kahraman);
    
    OyunNesnesi* zehirliCanavar = new ZehirDecorator(canavar);

    oyunDunyasi.push_back(kalkanliKahraman);
    oyunDunyasi.push_back(zehirliCanavar);
    oyunDunyasi.push_back(sesMotoru);

    std::cout << "--- Oyun Basliyor (Faz 2 - Structural) ---\n";
    for (OyunNesnesi* mevcutNesne : oyunDunyasi) {
        if (mevcutNesne != nullptr) mevcutNesne->guncelle();
    }

    std::cout << "\n--- Etkilesimler (Faz 2 - Structural) ---\n";
    for (OyunNesnesi* mevcutNesne : oyunDunyasi) {
        if (mevcutNesne != nullptr) mevcutNesne->etkilesimYap();
    }
    delete kalkanliKahraman;
    delete kahraman;
    delete zehirliCanavar;
    delete canavar;
    delete sesMotoru;
    oyunDunyasi.clear();

    return 0;
}
