#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>

using namespace std;

// Struct Buku
struct Buku {
    string ISBN;
    string judul;
    string pengarang;
    int tahunTerbit;
};

// Stack untuk Riwayat Peminjaman
class Stack {
private:
    stack<Buku> s;
public:
    void push(Buku buku) {
        s.push(buku);
    }

    Buku pop() {
        if (!s.empty()) {
            Buku topBuku = s.top();
            s.pop();
            return topBuku;
        } else {
            cout << "Riwayat peminjaman kosong!\n";
            return Buku{"", "", "", 0};
        }
    }

    bool isEmpty() {
        return s.empty();
    }

    void tampilkanRiwayat() {
        stack<Buku> temp = s;
        cout << "\n--- Riwayat Peminjaman Buku ---\n";
        cout << "-----------------------------------------------------------------------------------------\n";   
        cout << left << setw(20) << "ISBN" 
             << setw(35) << "Judul" 
             << setw(25) << "Pengarang" 
             << setw(10) << "Tahun" << endl;
        cout << "-----------------------------------------------------------------------------------------\n";
        while (!temp.empty()) {
            Buku b = temp.top();
            cout << left << setw(20) << b.ISBN 
  				 << setw(35) << b.judul 
                 << setw(25) << b.pengarang 
                 << setw(10) << b.tahunTerbit << endl;
            temp.pop();
        }
		cout << "-----------------------------------------------------------------------------------------\n";   
    }
};

// Queue untuk Antrian Peminjaman
class Queue {
private:
    queue<Buku> q;
public:
    void enqueue(Buku buku) {
        q.push(buku);
    }

    Buku dequeue() {
        if (!q.empty()) {
            Buku b = q.front();
            q.pop();
            return b;
        } else {
            cout << "Antrian peminjaman kosong!\n";
            return Buku{"", "", "", 0};
        }
    }

    bool isEmpty() {
        return q.empty();
    }

    void tampilkanAntrian() {
        queue<Buku> temp = q;
        cout << "\n--- Antrian Peminjaman Buku ---\n";
	    cout << "-----------------------------------------------------------------------------------------\n";   
        cout << left << setw(20) << "ISBN" 
             << setw(35) << "Judul" 
             << setw(25) << "Pengarang" 
             << setw(10) << "Tahun" << endl;
        cout << "-----------------------------------------------------------------------------------------\n";
        while (!temp.empty()) {
            Buku b = temp.front();
            cout << left << setw(20) << b.ISBN 
				 << setw(35) << b.judul 
                 << setw(25) << b.pengarang 
                 << setw(10) << b.tahunTerbit << endl;
            temp.pop();
        }
		cout << "-----------------------------------------------------------------------------------------\n";   
    }
};

// Array of pointers untuk menyimpan data buku
const int MAX_BUKU = 100;
Buku* daftarBuku[MAX_BUKU];
int jumlahBuku = 0;

// Fungsi untuk menambah buku
void tambahBuku(string isbn, string judul, string pengarang, int tahun) {
    if (jumlahBuku < MAX_BUKU) {
        Buku* bukuBaru = new Buku{isbn, judul, pengarang, tahun};
        daftarBuku[jumlahBuku++] = bukuBaru;
        cout << "Buku '" << judul << "' berhasil ditambahkan.\n";
    } else {
        cout << "Kapasitas penyimpanan buku penuh!\n";
    }
}

// Fungsi untuk mencari buku berdasarkan ISBN
Buku* cariBuku(string isbn) {
    for (int i = 0; i < jumlahBuku; i++) {
        if (daftarBuku[i]->ISBN == isbn) {
            return daftarBuku[i];
        }
    }
    return nullptr;
}

// Fungsi untuk menampilkan semua buku
void tampilkanSemuaBuku() {
    cout << "\n--- Daftar Buku Perpustakaan ---\n";
    cout << "-----------------------------------------------------------------------------------------\n";   
    cout << left << setw(20) << "ISBN" 
         << setw(35) << "Judul" 
         << setw(25) << "Pengarang" 
         << setw(10) << "Tahun" << endl;
    cout << "-----------------------------------------------------------------------------------------\n";
    for (int i = 0; i < jumlahBuku; i++) {
        cout << left << setw(20) << daftarBuku[i]->ISBN 
             << setw(35) << daftarBuku[i]->judul 
             << setw(25) << daftarBuku[i]->pengarang 
             << setw(10) << daftarBuku[i]->tahunTerbit << endl;
    }
    cout << "-----------------------------------------------------------------------------------------\n";
}

// Fungsi untuk peminjaman buku
void pinjamBuku(string isbn, Stack &riwayat, Queue &antrian) {
    Buku* buku = cariBuku(isbn);
    if (buku != nullptr) {
        antrian.enqueue(*buku);
        riwayat.push(*buku);
        cout << "Buku dengan ISBN " << isbn << " telah dipinjam dan ditambahkan ke antrian peminjaman.\n";
    } else {
        cout << "Buku tidak ditemukan!\n";
    }
}

// Fungsi untuk pengembalian buku (menghapus dari antrian)
void kembalikanBuku(Queue &antrian) {
    Buku bukuDikembalikan = antrian.dequeue();
    if (!bukuDikembalikan.ISBN.empty()) {
        cout << "Buku dengan ISBN " << bukuDikembalikan.ISBN << " telah dikembalikan.\n";
    }
}

int main() {
    Stack riwayatPeminjaman;
    Queue antrianPeminjaman;

    // Tambah beberapa buku awal untuk contoh
    tambahBuku("978-1-23456-789-0", "Belajar C++", "John Doe", 2021);
    tambahBuku("978-1-98765-432-1", "Pemrograman Dasar", "Jane Smith", 2020);
    tambahBuku("978-1-11223-344-5", "Algoritma dan Struktur Data", "Alice Johnson", 2019);

    int pilihan;
    do {
        cout << "\nMenu Perpustakaan:\n";
        cout << "1. Menambah Buku\n";
        cout << "2. Mencari Buku\n";
        cout << "3. Menampilkan Daftar Buku\n";
        cout << "4. Meminjam Buku\n";
        cout << "5. Mengembalikan Buku\n";
        cout << "6. Tampilkan Riwayat Peminjaman\n";
        cout << "7. Tampilkan Antrian Peminjaman\n";
        cout << "8. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                string ISBN, judul, pengarang;
                int tahun;
                cout << "Input ISBN: ";
                cin >> ISBN;
                cout << "Input Judul Buku: ";
                cin.ignore();
                getline(cin, judul);
                cout << "Input Pengarang: ";
                getline(cin, pengarang);
                cout << "Input Tahun Terbit: ";
                cin >> tahun;
                tambahBuku(ISBN, judul, pengarang, tahun);
                break;
            }
            case 2: {
                string ISBN;
                cout << "Input ISBN buku yang dicari: ";
                cin >> ISBN;
                Buku* buku = cariBuku(ISBN);
                if (buku != nullptr) {
                    cout << "Buku ditemukan: " << buku->judul << " oleh " << buku->pengarang << endl;
                } else {
                    cout << "Buku tidak ditemukan.\n";
                }
                break;
            }
            case 3:
                tampilkanSemuaBuku();
                break;
            case 4: {
                string ISBN;
                cout << "Input ISBN buku yang akan dipinjam: ";
                cin >> ISBN;
                pinjamBuku(ISBN, riwayatPeminjaman, antrianPeminjaman);
                break;
            }
            case 5:
                kembalikanBuku(antrianPeminjaman);
                break;
            case 6:
                riwayatPeminjaman.tampilkanRiwayat();
                break;
            case 7:
                antrianPeminjaman.tampilkanAntrian();
                break;
            case 8:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Opsi tidak valid. Silakan coba lagi.\n";
                break;
        }
    } while (pilihan != 8);

    // Menghapus memori yang dialokasikan untuk buku
    for (int i = 0; i < jumlahBuku; i++) {
        delete daftarBuku[i];
    }

    return 0;
}
