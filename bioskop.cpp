#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>
using namespace std;

struct Jadwal{ 
    char jam[10];
    char judulFilm[50];

    Jadwal *next; 
    Jadwal *prev; 
};
Jadwal *headJadwal = NULL; 
Jadwal *tailJadwal = NULL; 


struct Film{ 
    char judul[50];
    char genre[30];
    int durasi;
    int stokTiket;
	
    Film *next; 
};
Film *headFilm = NULL;


void loadFilm(){ 
    FILE *file = fopen("film.txt","r"); 
    if(file == NULL){
        return; 
    }
    while(true){ 
        Film *baru = new Film; 
        if(fscanf(file,"%[^|]|%[^|]|%d|%d\n",
					baru->judul, baru->genre, &baru->durasi, &baru->stokTiket) == EOF){
            delete baru; 
            break; 
        }
        
        baru->next = NULL; 

        if(headFilm == NULL){ 
            headFilm = baru; 
        }else{ 
            Film *temp = headFilm; 
            while(temp->next != NULL){ 
                temp = temp->next; 
            }
            
            temp->next = baru; 
        }
    }

    fclose(file); 
}


void simpanFilm(){ 
    FILE *file = fopen("film.txt","w"); 
    Film *temp = headFilm; 
    while(temp != NULL){ 
        fprintf(file,"%s|%s|%d|%d\n",
                temp->judul, temp->genre, temp->durasi, temp->stokTiket);

        temp = temp->next; 
    }

    fclose(file); 
}


void tambahFilm(){ 
    Film *baru = new Film; 

    cin.ignore();
    cout << "\n===== TAMBAH FILM =====\n";
    cout << "Judul Film   : ";
    cin.getline(baru->judul,50);
    cout << "Genre Film   : ";
    cin.getline(baru->genre,30);
    cout << "Durasi Film  : ";
    cin >> baru->durasi;
    cout << "Stok Tiket   : ";
    cin >> baru->stokTiket;

    baru->next = NULL; 

    if(headFilm == NULL){ 
        headFilm = baru; 
    }else{ 
        Film *temp = headFilm; 
        while(temp->next != NULL){ 
            temp = temp->next; 
        }
        
        temp->next = baru; 
    }
    
    simpanFilm(); 
    cout << "\nFilm berhasil ditambahkan!\n";
}


void tampilFilm(){
    if(headFilm == NULL){ 
        cout << "\nData film kosong!\n";
        return;
    }

    Film *temp = headFilm; 

    int no = 1;
    cout << "\n====================================================================================\n";
    cout << left << setw(5)  << "No" << setw(30) << "Judul Film" << setw(20) << "Genre" << setw(15) << "Durasi" << setw(15) << "Stok Tiket" << endl;
    cout << "====================================================================================\n";

    while(temp != NULL){ 
        cout << left << setw(5)  << no++ << setw(30) << temp->judul << setw(20) << temp->genre << setw(15) << temp->durasi << setw(15) << temp->stokTiket << endl;

        temp = temp->next; 
    }
    cout << "====================================================================================\n";
}


void cariFilm(){ 
    if(headFilm == NULL){ 
        cout << "\nData kosong!\n";
        return;
    }

    char cari[50];

    cin.ignore();
    cout << "\nCari Judul Film : ";
    cin.getline(cari,50);

    Film *temp = headFilm; 
    
    bool ketemu = false; 
  
    while(temp != NULL){ 
        if(strcmp(temp->judul,cari) == 0){ 
            cout << "\nFilm ditemukan!\n";
            cout << "====================================\n";
            cout << "Judul        : " << temp->judul << endl;
            cout << "Genre        : " << temp->genre << endl;
            cout << "Durasi(menit): " << temp->durasi << endl;
            cout << "Stok Tiket   : " << temp->stokTiket << endl;
            cout << "====================================\n";

            ketemu = true; 
        }

        temp = temp->next; 
    }

    if(!ketemu){ 
        cout << "\nFilm tidak ditemukan!\n";
    }
}


void sortingFilm(){ 
    if(headFilm == NULL){ 
        return;
    }

    bool tukar; 

    Film *ptr1; 
    Film *lptr = NULL; 

    do{
        tukar = false; 

        ptr1 = headFilm; 

        while(ptr1->next != lptr){ 
            if(ptr1->stokTiket > ptr1->next->stokTiket){ 
                swap(ptr1->judul, ptr1->next->judul); 
                swap(ptr1->genre, ptr1->next->genre);
                swap(ptr1->durasi, ptr1->next->durasi);
                swap(ptr1->stokTiket, ptr1->next->stokTiket);

                tukar = true; 
            }

            ptr1 = ptr1->next; 
        }

        lptr = ptr1; 

    }while(tukar); 

    simpanFilm(); 
    cout << "\nData berhasil diurutkan berdasarkan stok tiket!\n";
}

int main(){
    loadFilm(); 
    int pilih;
    
    do{
        cout << "\n====================================\n";
        cout << "     SISTEM MANAJEMEN DATA FILM\n";
        cout << "====================================\n";
        cout << "1. Tambah Film\n";
        cout << "2. Tampilkan Film\n";
        cout << "3. Cari Film\n";
        cout << "4. Sorting Film\n";
        cout << "====================================\n";
        cout << "Pilih Menu : ";
        cin >> pilih;

        switch(pilih){
            case 1:
                tambahFilm();
                break;

            case 2:
                tampilFilm();
                break;

            case 3:
                cariFilm();
                break;

            case 4:
                sortingFilm();
                tampilFilm();
                break;
            default:
                cout << "\nMenu tidak tersedia!\n";
        }
    }while(pilih != 9);
    return 0;
}
