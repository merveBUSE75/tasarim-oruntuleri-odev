#include <iostream>
#include <string>
#include <vector>

enum class NesneTipi { OYUNCU, DUSMAN, ESYA };

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
        std::cout << "[OYUNCU] " << isim << " hareket ediyor. Klavye girdisi bekleniyor...\n";
    }

    void etkilesimYap() override {
        std::cout << isim << " envanterini açtı.\n";
    }
};

class Dusman : public OyunNesnesi {
public:
    Dusman(std::string i, int c) : OyunNesnesi(i, c) {}

    void guncelle() override {
        std::cout << "[DUSMAN] " << isim << " devriye geziyor. Oyuncu aranıyor...\n";
    }

    void etkilesimYap() override {
        std::cout << isim << " oyuncuya saldırdı!\n";
    }
};

class Esya : public OyunNesnesi {
public:
    Esya(std::string i, int c) : OyunNesnesi(i, c) {}

    void guncelle() override {
        std::cout << "[ESYA] " << isim << " parlıyor. Toplanmak için hazır.\n";
    }

    void etkilesimYap() override {
        std::cout << isim << " çantaya eklendi.\n";
    }
};

class NesneFabrikasi {
public:
    static OyunNesnesi* nesneOlustur(NesneTipi tip, std::string isim, int can) {
        if (tip == NesneTipi::OYUNCU) {
            return new Oyuncu(isim, can);
        } 
        else if (tip == NesneTipi::DUSMAN) {
            return new Dusman(isim, can);
        } 
        else if (tip == NesneTipi::ESYA) {
            return new Esya(isim, can);
        }
        return nullptr;
    }
};

int main() {
    std::vector<OyunNesnesi*> oyunDunyasi;

    oyunDunyasi.push_back(NesneFabrikasi::nesneOlustur(NesneTipi::OYUNCU, "Savaşçı", 100));
    oyunDunyasi.push_back(NesneFabrikasi::nesneOlustur(NesneTipi::DUSMAN, "Ork", 50));
    oyunDunyasi.push_back(NesneFabrikasi::nesneOlustur(NesneTipi::ESYA, "Can İksiri", 0));

    std::cout << "--- Oyun Basliyor (Faz 1 - Factory) ---\n";
    for (OyunNesnesi* mevcutNesne : oyunDunyasi) {
        if (mevcutNesne != nullptr) {
            mevcutNesne->guncelle();
        }
    }

    std::cout << "\n--- Etkilesimler (Faz 1 - Factory) ---\n";
    for (OyunNesnesi* mevcutNesne : oyunDunyasi) {
        if (mevcutNesne != nullptr) {
            mevcutNesne->etkilesimYap();
        }
    }

    // Bellek Temizliği (Hafıza sızıntısını önlemek için amatör el ile delete)
    for (OyunNesnesi* mevcutNesne : oyunDunyasi) {
        delete mevcutNesne;
    }
    oyunDunyasi.clear();

    return 0;
}
