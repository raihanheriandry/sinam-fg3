# Kontrol Deteksi Air dan Kelembapan
### Focus Group 3 — Sistem Tertanam, Fakultas Ilmu Komputer, Universitas Indonesia (2026)

## Deskripsi Proyek

Proyek ini mengembangkan sistem **irigasi otomatis (*smart irrigation*)** berbasis Arduino Mega 2560 untuk mendeteksi kelembapan tanah, ketersediaan air, dan kondisi hujan. Informasi dari sensor diproses oleh mikrokontroler untuk mengendalikan servo motor sebagai pengatur katup air dan water pump sebagai pemompa air.

Proyek ini juga mempelajari karakteristik sensor dan aktuator, koneksi antarkomponen, pemrosesan sinyal analog dan digital, serta penerapan kendali otomatis berdasarkan kondisi lingkungan.

## Anggota Kelompok

Focus Group 3 terdiri atas:

1. **Khansa Dinda Arya Putri (2406496063)**
2. **Raihan Maulana Heriandry (2406351024)**
3. **Rayyan Emir Muhammad (2406345375)**

## Tujuan Proyek

- Memahami prinsip kerja sensor dan aktuator dalam sistem tertanam.
- Menghubungkan sensor dan aktuator dengan Arduino Mega 2560.
- Membaca dan mengolah nilai sensor menggunakan program Arduino.
- Menerapkan kendali otomatis berdasarkan kelembapan tanah, ketersediaan air, dan kondisi hujan.
- Melakukan pengujian dan karakterisasi komponen serta mengamati respons sistem.

## Komponen yang Digunakan

| Komponen | Fungsi |
|---|---|
| Arduino Mega 2560 | Pengendali utama sistem |
| Soil Moisture Sensor FC-28 | Mendeteksi kelembapan tanah |
| Raindrop Module | Mendeteksi kondisi basah atau hujan |
| Water Level Sensor | Mendeteksi ketersediaan air |
| Servo Motor SG90 | Mengatur posisi buka dan tutup katup air |
| Water Pump R385 | Memompa air untuk penyiraman |
| Relay Module | Mengendalikan daya pompa melalui sinyal Arduino |
| Breadboard dan kabel jumper | Menghubungkan komponen dalam rangkaian |

## Struktur Repository

```text
.
├── README.md
├── Laporan_FG3.pdf
├── Slide_Presentasi_FG3.pdf
├── source_code/
├── datasheet/
└── documentation/
```
