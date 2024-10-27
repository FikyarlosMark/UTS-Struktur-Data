#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Mahasiswa {
    string NIM;
    string nama;
    float IPK;
};

// Fungsi untuk menambah data mahasiswa
void tambahMahasiswa(Mahasiswa* arr[], int &jumlah) {
    if (jumlah < 10) {
        arr[jumlah] = new Mahasiswa;
        cout << "Masukkan NIM: ";
        cin >> arr[jumlah]->NIM;
        cout << "Masukkan Nama: ";
        cin.ignore();
        getline(cin, arr[jumlah]->nama);
        cout << "Masukkan IPK: ";
        cin >> arr[jumlah]->IPK;
        jumlah++;
        cout << "Data mahasiswa berhasil ditambahkan, Pilih menu 4 untuk melihat!\n";
    } else {
        cout << "Data penuh, tidak dapat menambah mahasiswa lagi.\n";
    }
}

// Fungsi untuk menghapus data mahasiswa berdasarkan NIM
void hapusMahasiswa(Mahasiswa* arr[], int &jumlah) {
    string nim;
    cout << "Masukkan NIM mahasiswa yang ingin dihapus: ";
    cin >> nim;
    
    int index = -1;
    for (int i = 0; i < jumlah; i++) {
        if (arr[i]->NIM == nim) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        delete arr[index];
        for (int i = index; i < jumlah - 1; i++) {
            arr[i] = arr[i + 1];
        }
        jumlah--;
        cout << "Data mahasiswa berhasil dihapus, Pilih menu 4 untuk melihat!\n";
    } else {
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
    }
}

// Fungsi untuk menampilkan data mahasiswa dalam bentuk tabel
void tampilkanMahasiswa(Mahasiswa* arr[], int jumlah) {
    if (jumlah == 0) {
        cout << "Tidak ada data mahasiswa yang tersimpan.\n";
        return;
    }

    // Header Tabel
    cout << "-------------------------------------------------------------\n";
    cout << left << setw(15) << "NIM" 
         << setw(30) << "Nama" 
         << setw(10) << "IPK" << endl;
    cout << "-------------------------------------------------------------\n";

    // Isi Tabel
    for (int i = 0; i < jumlah; i++) {
        cout << left << setw(15) << arr[i]->NIM
             << setw(30) << arr[i]->nama
             << setw(10) << fixed << setprecision(2) << arr[i]->IPK << endl;
    }
    cout << "-------------------------------------------------------------\n";
}

// Fungsi untuk mengurutkan data mahasiswa berdasarkan IPK menggunakan bubble sort
void urutkanMahasiswa(Mahasiswa* arr[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (arr[j]->IPK < arr[j + 1]->IPK) {
                Mahasiswa* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    cout << "Data mahasiswa telah diurutkan berdasarkan IPK, Pilih menu 4 untuk melihat!\n";
}

int main() {
    Mahasiswa* dataMahasiswa[10];
    int jumlah = 0;
    int pilihan;

    // Input awal untuk data mahasiswa
    cout << "Berapa jumlah mahasiswa yang ingin dimasukkan? (maks 10): ";
    cin >> jumlah;
    if (jumlah > 10) jumlah = 10;

    for (int i = 0; i < jumlah; i++) {
        dataMahasiswa[i] = new Mahasiswa;
        cout << "Masukkan data untuk mahasiswa " << (i + 1) << ":\n";
        cout << "NIM: ";
        cin >> dataMahasiswa[i]->NIM;
        cout << "Nama: ";
        cin.ignore();
        getline(cin, dataMahasiswa[i]->nama);
        cout << "IPK: ";
        cin >> dataMahasiswa[i]->IPK;
        cout << endl;
    }

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Tambah Data Mahasiswa\n";
        cout << "2. Hapus Data Mahasiswa\n";
        cout << "3. Urutkan Data Mahasiswa Berdasarkan IPK\n";
        cout << "4. Tampilkan Data Mahasiswa\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahMahasiswa(dataMahasiswa, jumlah);
                break;
            case 2:
				hapusMahasiswa(dataMahasiswa, jumlah);
				break;    
            case 3:
                urutkanMahasiswa(dataMahasiswa, jumlah);
                break;
            case 4:
                tampilkanMahasiswa(dataMahasiswa, jumlah);
                break;
            case 5:
                cout << "Terima kasih, program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 5);

    // Membersihkan memori yang dialokasikan
    for (int i = 0; i < jumlah; i++) {
        delete dataMahasiswa[i];
    }

    return 0;
}
