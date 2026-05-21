#include <iostream>
#include <string>
#include <vector>

enum class NesneTipi { OYUNCU, DUSMAN, ESYA };

class OyunNesnesi {
public:
    NesneTipi tip;
    std::string isim;
    int can;

    OyunNesnesi(NesneTipi t, std::string i, int c) : tip(t), isim(i), can(c) {}

    void guncelle() {
        if (tip == NesneTipi::OYUNCU) {
            std::cout << "[OYUNCU] " << isim << " hareket ediyor. Klavye girdisi bekleniyor...\n";
        } 
        else if (tip == NesneTipi::DUSMAN) {
            std::cout << "[DUSMAN] " << isim << " devriye geziyor. Oyuncu aranıyor...\n";
        } 
        else if (tip == NesneTipi::ESYA) {
            std::cout << "[ESYA] " << isim << " parlıyor. Toplanmak için hazır.\n";
        }
    }

    void etkilesimYap() {
        if (tip == NesneTipi::OYUNCU) {
            std::cout << isim << " envanterini açtı.\n";
        } 
        else if (tip == NesneTipi::DUSMAN) {
            std::cout << isim << " oyuncuya saldırdı!\n";
        } 
        else if (tip == NesneTipi::ESYA) {
            std::cout << isim << " çantaya eklendi.\n";
        }
    }
};

int main() {
    
    OyunNesnesi kahraman(NesneTipi::OYUNCU, "Savaşçı", 100);
    OyunNesnesi canavar(NesneTipi::DUSMAN, "Ork", 50);
    OyunNesnesi iksir(NesneTipi::ESYA, "Can İksiri", 0);

    std::cout << "--- --OYUN BASLİYOR-- ---" << std::endl;
    
    kahraman.guncelle();
    canavar.guncelle();
    iksir.guncelle();

    std::cout << "\n--- -- ETKİLEŞİMLER -- ---" << std::endl;
    
    kahraman.etkilesimYap();
    canavar.etkilesimYap();
    iksir.etkilesimYap();

    return 0;
}
