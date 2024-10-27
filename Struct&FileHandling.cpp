#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Peralatan {
    string kode;
    string nama;
    int jumlah;
    string kondisi;
};

// Fungsi untuk menambah data peralatan
void tambahPeralatan(vector<Peralatan> &inventaris) {
    Peralatan p;
    cout << "Masukkan kode peralatan: ";
    cin >> p.kode;
    cout << "Masukkan nama peralatan: ";
    cin.ignore();
    getline(cin, p.nama);
    cout << "Masukkan jumlah peralatan: ";
    cin >> p.jumlah;
    cout << "Masukkan kondisi peralatan: ";
    cin.ignore();
    getline(cin, p.kondisi);
    inventaris.push_back(p);
    cout << "Data peralatan berhasil ditambahkan!\n";
}

// Fungsi untuk mengubah data peralatan
void ubahPeralatan(vector<Peralatan> &inventaris) {
    string kode;
    cout << "Masukkan kode peralatan yang ingin diubah: ";
    cin >> kode;

    bool ditemukan = false;
    for (auto &p : inventaris) {
        if (p.kode == kode) {
            cout << "Data saat ini:\n";
            cout << "Nama: " << p.nama << ", Jumlah: " << p.jumlah << ", Kondisi: " << p.kondisi << endl;
            cout << "Masukkan data baru:\n";
            cout << "Nama peralatan: ";
            cin.ignore();
            getline(cin, p.nama);
            cout << "Jumlah peralatan: ";
            cin >> p.jumlah;
            cout << "Kondisi peralatan: ";
            cin.ignore();
            getline(cin, p.kondisi);
            cout << "Data berhasil diubah!\n";
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        cout << "Peralatan dengan kode " << kode << " tidak ditemukan.\n";
    }
}

// Fungsi untuk menghapus data peralatan
void hapusPeralatan(vector<Peralatan> &inventaris) {
    string kode;
    cout << "Masukkan kode peralatan yang ingin dihapus: ";
    cin >> kode;

    auto it = remove_if(inventaris.begin(), inventaris.end(), [kode](Peralatan &p) {
        return p.kode == kode;
    });

    if (it != inventaris.end()) {
        inventaris.erase(it, inventaris.end());
        cout << "Data peralatan berhasil dihapus!\n";
    } else {
        cout << "Peralatan dengan kode " << kode << " tidak ditemukan.\n";
    }
}

// Fungsi untuk menyimpan data ke file
void simpanKeFile(const vector<Peralatan> &inventaris, const string &namaFile) {
    ofstream file(namaFile);
    if (file.is_open()) {
        for (const auto &p : inventaris) {
            file << p.kode << "|" << p.nama << "|" << p.jumlah << "|" << p.kondisi << endl;
        }
        file.close();
        cout << "Data berhasil disimpan ke file " << namaFile << ".\n";
    } else {
        cout << "Gagal membuka file untuk menulis.\n";
    }
}

// Fungsi untuk membaca data dari file
void bacaDariFile(vector<Peralatan> &inventaris, const string &namaFile) {
    ifstream file(namaFile);
    if (file.is_open()) {
        inventaris.clear();
        Peralatan p;
        while (getline(file, p.kode, '|')) {
            getline(file, p.nama, '|');
            file >> p.jumlah;
            file.ignore(); // Mengabaikan karakter pemisah '|'
            getline(file, p.kondisi);
            inventaris.push_back(p);
        }
        file.close();
        cout << "Data berhasil dibaca dari file " << namaFile << ".\n";
    } else {
        cout << "Gagal membuka file untuk membaca.\n";
    }
}

// Fungsi untuk menampilkan laporan inventaris peralatan
void tampilkanLaporan(const vector<Peralatan> &inventaris) {
    if (inventaris.empty()) {
        cout << "Tidak ada data peralatan.\n";
        return;
    }

    // Mengurutkan inventaris berdasarkan kode peralatan
    vector<Peralatan> salinan = inventaris;
    sort(salinan.begin(), salinan.end(), [](const Peralatan &a, const Peralatan &b) {
        return a.kode < b.kode;
    });

    // Menampilkan tabel laporan
    cout << "--------------------------------------------------------------\n";
	cout << left << setw(10) << "Kode"
         << setw(20) << "Nama"
         << setw(10) << "Jumlah"
         << setw(20) << "Kondisi" << endl;
    cout << "--------------------------------------------------------------\n";
    for (const auto &p : salinan) {
        cout << left << setw(10) << p.kode
             << setw(20) << p.nama
             << setw(10) << p.jumlah
             << setw(20) << p.kondisi << endl;
    }
    cout << "--------------------------------------------------------------\n";
}

int main() {
    vector<Peralatan> inventaris;
    string namaFile = "inventaris.txt";
    int pilihan;

    // Membaca data dari file saat program dimulai
    bacaDariFile(inventaris, namaFile);

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Tambah Peralatan\n";
        cout << "2. Ubah Peralatan\n";
        cout << "3. Hapus Peralatan\n";
        cout << "4. Tampilkan Laporan\n";
        cout << "5. Simpan ke File\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPeralatan(inventaris);
                break;
            case 2:
                ubahPeralatan(inventaris);
                break;
            case 3:
                hapusPeralatan(inventaris);
                break;
            case 4:
                tampilkanLaporan(inventaris);
                break;
            case 5:
                simpanKeFile(inventaris, namaFile);
                break;
            case 6:
                cout << "Terima kasih, program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 6);

    return 0;
}
