#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct Pelanggan {
    string nomorAntrian;
    int waktuLayanan;  // Waktu layanan dalam menit
};

class Queue {
private:
    queue<Pelanggan> q;
public:
    void enqueue(Pelanggan p) {
        q.push(p);
    }

    Pelanggan dequeue() {
        if (!q.empty()) {
            Pelanggan p = q.front();
            q.pop();
            return p;
        } else {
            cout << "Antrian kosong, tidak ada yang dapat di-dequeue.\n";
            return Pelanggan{ "", 0 }; // Nomor antrian kosong berarti antrian kosong
        }
    }

    bool isEmpty() {
        return q.empty();
    }

    int size() {
        return q.size();
    }
};

// Simulasi proses antrian dengan 3 loket
void simulasiAntrian(Queue &antrian) {
    int waktuLoket[3] = {0, 0, 0};  // Waktu layanan di masing-masing loket
    int totalWaktuTunggu = 0;
    int pelangganTerlayani = 0;
    int totalWaktu = 0;
    
    while (!antrian.isEmpty() || waktuLoket[0] > 0 || waktuLoket[1] > 0 || waktuLoket[2] > 0) {
        for (int i = 0; i < 3; ++i) {
            if (waktuLoket[i] == 0 && !antrian.isEmpty()) {
                Pelanggan p = antrian.dequeue();
                waktuLoket[i] = p.waktuLayanan;

                cout << "Pelanggan dengan nomor antrian " << p.nomorAntrian 
                     << " dilayani di loket " << i + 1 
                     << " dengan waktu layanan " << p.waktuLayanan << " menit.\n";

                pelangganTerlayani++;
            }
        }

        // Mengurangi waktu layanan di setiap loket
        for (int i = 0; i < 3; ++i) {
            if (waktuLoket[i] > 0) {
                waktuLoket[i]--;
            }
        }

        totalWaktu++;
    }

    // Menampilkan statistik
    cout << "\n--- Statistik ---\n";
    cout << "Total pelanggan terlayani: " << pelangganTerlayani << endl;
    cout << "Rata-rata waktu tunggu: " << (pelangganTerlayani > 0 ? (totalWaktu / pelangganTerlayani) : 0) << " menit\n";
    cout << "Sisa antrian: " << antrian.size() << endl;
}

int main() {
    Queue antrian;
    int jumlahPelanggan, waktuLayanan;
    string nomorAntrian;

    // Input jumlah pelanggan dan waktu layanan
    cout << "Masukkan jumlah pelanggan: ";
    cin >> jumlahPelanggan;
    for (int i = 1; i <= jumlahPelanggan; ++i) {
        cout << "Masukkan nomor antrian " << i << ": ";
        cin >> nomorAntrian;
        cout << "Masukkan waktu layanan untuk pelanggan dengan nomor antrian " << nomorAntrian << " (dalam menit): ";
        cin >> waktuLayanan;
        antrian.enqueue(Pelanggan{nomorAntrian, waktuLayanan});
    }

    simulasiAntrian(antrian);

    return 0;
}