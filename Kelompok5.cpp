#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


// Penggunaan Fungsi Class
class siswa {
    int nim;
    char nama[50];
    int indo, math, science, eng, vocation;
    double nilai;
    char grade;
    void perhitungan();             // Function Untuk Menghitung Grade
public:
    void getdata();                 // Function Untuk Menerima Data Dari User
    void showdata() const;         // Function Untuk Memperlihatkan Data Di Layar
    void show_tabular() const;     // Function Untuk Memperlihatkan Data Secara Tabular
    int retnim() const;
};

// Perhitungan Nilai
void siswa::perhitungan() {
    nilai = (indo + math + science + eng + vocation) / 5.0;
        if (nilai >= 85)
        grade = 'A';
        
        else if (nilai >= 75 && nilai < 85)
        grade = 'B';
            
        else if (nilai >= 65 && nilai < 75) 
        grade = 'C';
                
        else if (nilai >= 55 && nilai < 65) 
        grade = 'D';
                    
        else 
        grade = 'E';     
}

// Input Data Siswa
void siswa::getdata() {
    cout << "\nMasukan NIM Siswa : ";
    cin >> nim;
    cout << "\n\nMasukan Nama Siswa : ";
    cin.ignore ();
    cin.getline (nama, 50);
    cout << "\nMasukan Nilai Bahasa Indonesia Skala Nilai Dari 100	: ";
    cin >> indo;
    cout << "\nMasukan Nilai Matematika Skala Nilai Dari 100		: ";
    cin >> math;
    cout << "\nMasukan Nilai Sains Skala Nilai Dari 100				: ";
    cin >> science;
    cout << "\nMasukan Nilai Bahasa Inggris Skala Nilai Dari 100	: ";
    cin >> eng;
    cout << "\nMasukan Nilai Kejuruan Skala Nilai Dari 100     		: ";
    cin >> vocation;
    perhitungan ();
}

// Display Data Siswa
void siswa::showdata() const {
    cout << "\nNIM Siswa 		: " << nim;
    cout << "\nNama Siswa 		: " << nama;
    cout << "\nNilai Bahasa Indonesia 	: " << indo;
    cout << "\nNilai Matematika       	: " << math;
    cout << "\nNilai Science          	: " << science;
    cout << "\nNilai Bahasa Inggris   	: " << eng;
	cout << "\nNilai Kejuruan   		: " << vocation;
    cout << "\nTotal Nilai            	: " << nilai;
    cout << "\nPredikat Nilai         	: " << grade;
}

// Display Data Siswa Dalam Bentuk Tabular
void siswa::show_tabular() const {
    cout<<nim<<setw(6)<<" "<<nama<<setw(10)<<indo<<setw(4)<<math<<setw(4)<<science<<setw(4)<<eng<<setw(4)<<vocation<<setw(8)<<nilai<<setw(6)<<grade<<endl;
}


// Pengembalian Nilai NIM & Penetapan Nilai Yang Tak Dapat Dirubah
int siswa::retnim() const {
    return nim;
}
// End Class

// Deklarasi Function
void input_siswa ();				// Pemanggilan Function Input Data Siswa
void lihat_data_semua ();			// Pemanggilan Function Display Seluruh Data Siswa
void lihat_spesifik_data (int);		// Pemanggilan Function Display Spesifik Data Siswa
void edit_siswa(int);				// Pemanggilan Function Edit Data Siswa
void hapus_siswa (int);				// Pemanggilan Function Hapus Data Siswa
void hasil_tabular();				// Pemanggilan Function Display Tabular Data Siswa
void result ();						// Pemanggilan Function Menu Utama Data Siswa
void tampilan_awal ();				// Pemanggilan Function Tampilan Utama Data Siswa
void entry_menu();					// Pemanggilan Function Buat, Edit, Hapus, dll  Data Siswa


// Main Function Program
int main () {
    char u;
    cout.setf (ios::fixed | ios::showpoint);
    cout << setprecision (2);
    tampilan_awal ();
        do
        {
            system("cls");
            cout << "Menu Utama Student Report \n";
            cout << "1. Menu Hasil \n";
            cout << "2. Menu Input/Edit Data \n";
            cout << "3. Exit \n";
            cout << "Silahkan Pilih Menu : ";
            cin >> u;
                switch (u)
                {
                case '1' : result();
                    break;
                
                case '2' : entry_menu();
                    break;

                case '3' : 
                    break;

                default: cout << "\a";
                }
        } while (u != '3');
        return 0;
}

// Function Untuk Input Data Siswa
void input_siswa () {
    siswa ss;
    ofstream outFile;
    outFile.open ("Siswa.dat", ios :: binary | ios:: app);
    ss.getdata();
    outFile.write (reinterpret_cast<char *> (&ss), sizeof(siswa));
    outFile.close ();
        cout << "\n\nInput Data Siswa Telah Berhasil Di Record";
    cin.ignore();
    cin.get();
}

// Function Untuk Display Data Siswa
void lihat_data_semua () {
    siswa ss;
    ifstream inFile;
    inFile.open ("Siswa.dat", ios::binary);
        if (!inFile) {
            cout<<"File Tidak Bisa Dibuka. Klik Tombol Mana Saja...";
		    cin.ignore();
		    cin.get();
		    return;
        }
    cout << "Tampilkan Record Data\n";
        while(inFile.read (reinterpret_cast < char *> (&ss), sizeof(siswa))) {
			ss.showdata();
			cout<<"\n\n====================================\n";
	    }
	inFile.close();
	cin.ignore();
	cin.get();
}

// Function Untuk Display Data Secara Spesifik
void lihat_spesifik_data (int n) {
    siswa ss;
	ifstream inFile;
	inFile.open("Siswa.dat", ios::binary);
	
	if(!inFile) {
		cout<<"File Tidak Bisa Dibuka. Klik Tombol Mana Saja...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag = false;
	while(inFile.read(reinterpret_cast<char *> (&ss), sizeof(siswa))) {
		
		if(ss.retnim()==n) {
	  		 ss.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag == false)
		cout<<"\n\n Data Tidak Ada";
	cin.ignore();
	cin.get();
}

// Function Untuk Edit Data Siswa
void edit_siswa (int n) {
	bool found =  false;
	siswa ss;
	fstream File;
	File.open("Siswa.dat", ios::binary | ios::in | ios::out);
	
	if(!File) {
		cout<<"File Tidak Bisa Dibuka. Klik Tombol Mana Saja...";
		cin.ignore();
		cin.get();
		return;
	}
    	while (!File.eof() && found == false) {
		File.read(reinterpret_cast<char *> (&ss), sizeof(siswa));
		
		if(ss.retnim() == n) {
			ss.showdata();
			cout<<"\n\nMasukan Data Baru Siswa"<<endl;
			ss.getdata();
		    	int pos=(-1) * static_cast<int> (sizeof(ss));
		    	File.seekp(pos, ios::cur);
		    	File.write(reinterpret_cast<char *> (&ss), sizeof(siswa));
		    	cout<<"\n\n Data Berhasil Di Update";
		    	found = true;
		}
	}
	File.close();
	if(found == false)
		cout<<"\n\n Data Tidak Ditemukan";
	cin.ignore();
	cin.get();
}


// Function Delete Data Siswa
void hapus_siswa (int n) {
	siswa ss;
	ifstream inFile;
	inFile.open("Siswa.dat", ios::binary);
	if (!inFile) {
		cout<<"File Tidak Bisa Dibuka. Klik Tombol Mana Saja...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat", ios::out);
	inFile.seekg(0, ios::beg);
	while(inFile.read (reinterpret_cast <char *> (&ss), sizeof(siswa))) {
		if(ss.retnim () !=n) {
			outFile.write(reinterpret_cast <char *> (&ss), sizeof(siswa));
		}
	}
	outFile.close ();
	inFile.close ();
	remove("Siswa.dat");
	rename("Temp.dat", "Siswa.dat");
	cout<<"\n\n\t Data Telah Dihapus ...";
	cin.ignore ();
	cin.get ();
}

// Function Display Data Siswa Secara Tabular
void hasil_tabular () {
	siswa ss;
	ifstream inFile;
	inFile.open("Siswa.dat", ios::binary);
	if(!inFile) {
		cout<<"File Tidak Bisa Dibuka. Klik Tombol Mana Saja...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tHasil Seluruh Siswa\n\n";
	cout<<"==========================================================\n";
	cout<<"NIM       Name        I   M   E   S   K   %mark   Grade"<<endl;
	cout<<"==========================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ss), sizeof(siswa))) {
		ss.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}

// Function Untuk Display Menu Hasil
void result() {
	char ch;
	int rno;
	system("cls");
	cout<<"\n\n\n\t Menu Hasil";
	cout<<"\n\n\n\t1. Hasil Kelas";
	cout<<"\n\n\t2. Kartu Laporan Siswa";
	cout<<"\n\n\t3. Kembali Ke Menu";
	cout<<"\n\n\n\tMasukan Pilihan Anda (1/2/3)? ";
	cin>>ch;
	system("cls");
	switch (ch) {
	case '1' :	hasil_tabular(); 
        break;
	case '2' :	cout<<"\n\n\tMasukan NIM Siswa : "; cin>>rno;
				lihat_spesifik_data(rno); 
    break;
	case '3' :	
        break;
	default:	cout<<"\a";
	}
}

//START     Tampilan Awal
void tampilan_awal ()  {
    cout << "\t\tStudent Report\n\n\n";
    cout << "\t\tProject\n\n\n";
    cout << "\t\tDibuat Oleh : Kelompok 5";
    cin.get();
}

// Function Menu Input/Edit Data
void entry_menu () {
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1. Buat Data Siswa";
	cout<<"\n\n\t2. Tampilkan Seluruh Data";
	cout<<"\n\n\t3. Cari Data Siswa ";
	cout<<"\n\n\t4. Edit Data Siswa";
	cout<<"\n\n\t5. Hapus Data Siswa";
	cout<<"\n\n\t6. Kembali";
	cout<<"\n\n\tPilih Menu Anda... ";
	cin>>ch;
	system("cls");
	switch(ch) {
	case '1':	input_siswa(); 
        break;
	case '2':	lihat_data_semua(); 
        break;
	case '3':	cout<<"\n\n\tMasukan NIM Siswa "; cin >> num;
			    lihat_spesifik_data(num); 
        break;
	case '4':	cout<<"\n\n\tMasukan NIM Siswa "; cin >> num;
			    edit_siswa(num);
        break;
	case '5':	cout<<"\n\n\tMasukan NIM Siswa "; cin >> num;
			    hapus_siswa(num);
        break;
	case '6':	
        break;
	default:	
	cout << "\a"; 
    entry_menu();
	}
}