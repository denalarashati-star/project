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


void loadJadwal(){
    FILE *file = fopen("jadwal.txt","r");
    if(file == NULL){
        return;
    }
    while(true){
        Jadwal *baru = new Jadwal;
        if(fscanf(file,"%[^|]|%[^\n]\n", baru->jam, baru->judulFilm) == EOF){

            delete baru;
            break;
        }
        
        baru->next = NULL;
        baru->prev = NULL;

        if(headJadwal == NULL){
            headJadwal = tailJadwal = baru;
        } else{
            tailJadwal->next = baru;
            baru->prev = tailJadwal;
            tailJadwal = baru;
        }
    }

    fclose(file);
}


void simpanJadwal(){
    FILE *file = fopen("jadwal.txt","w");
    if(file == NULL){
        return;
    }

    Jadwal *temp = headJadwal;

    while(temp != NULL){fprintf(file,"%s|%s\n", temp->jam, temp->judulFilm);
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


void hapusFilm(){
    if(headFilm == NULL){ 
        cout << "\nData kosong!\n";
        return;
    }

    char hapus[50];

    cin.ignore();
    cout << "\nMasukkan Judul Film : ";
    cin.getline(hapus,50);

    Film *temp = headFilm; 
    Film *prev = NULL; 

    while(temp != NULL){ 
        if(strcmp(temp->judul,hapus) == 0){ 
			
			Jadwal *j = headJadwal;

			while(j != NULL){
				Jadwal *hapusNode = j;

				j = j->next;

				if(strcmp(hapusNode->judulFilm, hapus) == 0){
					if(hapusNode == headJadwal)
						headJadwal = hapusNode->next;
					if(hapusNode == tailJadwal)
						tailJadwal = hapusNode->prev;
					if(hapusNode->prev != NULL)
						hapusNode->prev->next = hapusNode->next;
					if(hapusNode->next != NULL)
						hapusNode->next->prev = hapusNode->prev;

					delete hapusNode;
				}
			}

			simpanJadwal();
			
            simpanJadwal();
			
            if(prev == NULL){ 
                headFilm = temp->next;  
            }else{
                prev->next = temp->next; 
            }

            delete temp; 

            simpanFilm(); 
            cout << "\nFilm berhasil dihapus!\n";
            return;
        }

        prev = temp; 
        temp = temp->next; 
    }
    cout << "\nFilm tidak ditemukan!\n";
}


void tambahJadwal(){
	if(headFilm == NULL){
        cout << "\nData film kosong!\n";
        return;
    }
	
    Jadwal *baru = new Jadwal; 

    cin.ignore();
    cout << "\n===== TAMBAH JADWAL STUDIO =====\n";
    cout << "Jam Tayang   : ";
    cin.getline(baru->jam,10);
    cout << "\nDAFTAR FILM :\n";
    
    Film *lihat = headFilm;
    
    int no = 1;
    while(lihat != NULL){
        cout << no++ << ". " << lihat->judul << endl;
        lihat = lihat->next;
    }
    cout << "\nJudul Film   : ";
    cin.getline(baru->judulFilm,50);
    
    Film *cek = headFilm;
    
    bool ketemu = false;

    while(cek != NULL){
        if(strcmp(cek->judul, baru->judulFilm) == 0){
            ketemu = true;
            break;
        }
        cek = cek->next;
    }

    if(!ketemu){
        cout << "\nFilm tidak tersedia!\n";
        delete baru;
        return;
    }

    baru->next = NULL; 
    baru->prev = NULL; 

    if(headJadwal == NULL){ 
        headJadwal = tailJadwal = baru; 
    }else{
        tailJadwal->next = baru; 
        baru->prev = tailJadwal; 
        tailJadwal = baru; 
    }
    
    simpanJadwal();
    cout << "\nJadwal berhasil ditambahkan!\n";
}


void tampilJadwal(){
    if(headJadwal == NULL){ 
        cout << "\nJadwal kosong!\n";
        return;
    }

    Jadwal *temp = headJadwal; 
    
    int no = 1;
    cout << "\n===============================================================\n";
    cout << left << setw(5) << "No" << setw(20) << "Jam" << setw(30) << "Film" << endl;
    cout << "===============================================================\n";

    while(temp != NULL){ 
        cout << left << setw(5)  << no++ << setw(20) << temp->jam << setw(30) << temp->judulFilm << endl;
        temp = temp->next; 
    }
    cout << "===============================================================\n";
}


void navigasiJadwal(){
    if(headJadwal == NULL){ 
        cout << "\nJadwal kosong!\n";
        return;
    }

    Jadwal *current = headJadwal; 

    int pilih;
    do{
        cout << "\n====================================\n";
        cout << "JAM TAYANG : " << current->jam << endl;
        cout << "FILM       : " << current->judulFilm << endl;
        cout << "====================================\n";
        cout << "1. Next\n";
        cout << "2. Previous\n";
        cout << "3. Keluar\n";
        cout << "Pilih : ";
        cin >> pilih;

        if(pilih == 1){ 
            if(current->next != NULL){ 
                current = current->next; 
            }else{ 
                cout << "\nSudah jadwal terakhir!\n";
            }
        }
        else if(pilih == 2){ 
            if(current->prev != NULL){ 
                current = current->prev; 
            }else{
                cout << "\nSudah jadwal pertama!\n";
            }
        }
    }while(pilih != 3); 
}


int main(){
    loadFilm(); 
    loadJadwal();
    int pilih;
    
    do{
        cout << "\n====================================\n";
        cout << "     SISTEM MANAJEMEN DATA FILM\n";
        cout << "====================================\n";
        cout << "1. Tambah Film\n";
        cout << "2. Tampilkan Film\n";
        cout << "3. Cari Film\n";
        cout << "4. Sorting Film\n";
        cout << "5. Hapus Film\n";
        cout << "6. Tambah Jadwal Studio\n";
        cout << "7. Tampilkan Jadwal Studio\n";
        cout << "8. Navigasi Jadwal Studio\n";
        cout << "9. Keluar\n";
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

            case 5:
                hapusFilm();
                break;

            case 6:
                tambahJadwal();
                break;

            case 7:
                tampilJadwal();
                break;

            case 8:
                navigasiJadwal();
                break;

            case 9:
                cout << "\nProgram selesai.\n";
                break;
                
            default:
                cout << "\nMenu tidak tersedia!\n";
        }
    }while(pilih != 9);
    return 0;
}
