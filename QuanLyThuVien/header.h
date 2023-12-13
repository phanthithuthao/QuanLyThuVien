#include <fstream>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

#define MAX 1000

// khai báo kiểu dữ liệu tránh bị lỗi
struct Date;
struct Sach;
struct NodeSach;
struct DocGia;
struct NodeDocGia;
struct LoaiSach;
struct NodeLoaiSach;
struct PhieuMuonTra;
struct NodePhieuMuonTra;

// các typedef
typedef struct NodeDocGia* NodeDocGiaPtr;
typedef struct NodeLoaiSach* NodeLoaiSachPtr;
typedef struct NodeSach* NodeSachPtr;
typedef struct NodePhieuMuonTra* NodePhieuMuonTraPtr;

// kiểu dữ liệu ngày tháng năm
struct Date {
    int ngay;
    int thang;
    int nam;
};

// Kiểu dữ liệu độc giả
struct DocGia {
    string maDocGia;
    string tenDocGia;
    string lop;
    string nganh;
    Date hanThe;
};
struct DSDocGia {
    int n;
    DocGia data[MAX];
};
struct NodeDocGia {
    DocGia data;
    NodeDocGia* link;
};

// Kiểu dữ liệu loại sách
struct LoaiSach {
    string maLoai;
    string tenLoai;
    NodeSachPtr dsSach;
};
struct DSLoaiSach {
    int n;
    LoaiSach data[MAX];
};
struct NodeLoaiSach {
    LoaiSach data;
    NodeLoaiSach* link;
};
// Danh mục sách
struct DanhMucSach {
    string maDanhMuc;
    string tenDanhMuc;
    NodeSachPtr dsSach; // Danh sách liên kết các sách thuộc danh mục này
};
// Kiểu dữ liệu sách
struct Sach {
    string maDauSach;
    string tenSach;
    LoaiSach loai;
    Date NXB;
    string tacGia;
    string moTa;
    bool trangThai;
    int soLuong;
};
struct KhoSach {
    Sach data[MAX];
    int n;
};
struct NodeSach {
    Sach data;
    NodeSach* link;
};

// Kiểu dữ liệu phiếu mượn trả
struct PhieuMuonTra {
    string maPhieu;
    string maDG;
    string maDauSach;
    Date ngayMuon;
    Date ngayTra;
    bool trangThai;
};
struct DSPhieuMuonTra {
    int n;
    PhieuMuonTra data[MAX];
};
struct NodePhieuMuonTra {
    PhieuMuonTra data;
    NodePhieuMuonTra* link;
};

// xóa màn hình không nhấp nháy
void cls(HANDLE hConsole);

// đọc file
void readFile(const char* filename); // chỉ để đọc giao diện, tiêu đề giao diện
void docFile(NodeDocGiaPtr& list, const string& filename);
void DocDSDG(ifstream& filein, NodeDocGiaPtr& list);
void GhiTTDG(ofstream& fileout, const DocGia& dg);
void GhiDSDG(ofstream& fileout, const NodeDocGiaPtr& list);
void ghiFile(const NodeDocGiaPtr& list, const string& filename);
void GhiTTSach(ofstream& fileout, const Sach& sach);
void GhiDSSach(ofstream& fileout, const NodeSachPtr& list);
void docFileSach(NodeSachPtr& list, const string& filename);
void DocDSSach(ifstream& filein, NodeSachPtr& list);
void ghiFileSach(const NodeSachPtr& list, const string& filename);

// giao diện
void xuatTieuDe(const char* filePath);
void menuQLTV();
void menuSach();
void menuThe();
void menuThueTraSach();

// chức năng thẻ độc giả
void nhapDocGia(DocGia& dg);
void xuatDocGia(DocGia dg);
NodeDocGiaPtr tao_Node_DocGia(DocGia dg);
int isEmpty(NodeDocGiaPtr list);
void khoiTao(NodeDocGiaPtr& list);
void giaiPhongBoNho(NodeDocGiaPtr& list);
bool kiemTra_TrungMa(NodeDocGiaPtr& list, const string& ma);
bool check(int d, int m, int y);
int getday(int m);
NodeDocGiaPtr them_Dau(NodeDocGiaPtr& list, DocGia dg);
NodeDocGiaPtr Them_Cuoi(NodeDocGiaPtr& list, DocGia dg);
void nhap_DSDG(NodeDocGiaPtr& list, DocGia& dg);
void xuat_DSDG(NodeDocGiaPtr list);
void xoaTheDocGia(NodeDocGiaPtr& list, string maDocGia);
void capNhatThongTin(NodeDocGiaPtr& list, string maDocGia);

// chức năng quản lý sách
void khoiTao(NodeSachPtr& list);
int isEmpty(NodeSachPtr list);
NodeSachPtr tao_Node_Sach(Sach sach);
NodeSachPtr them_Dau(NodeSachPtr& list, Sach sach);
void giaiPhongBoNho(NodeSachPtr& list);
void nhapSach(Sach& sach);
void xuatSach(Sach sach);
void nhap_DSSach(NodeSachPtr& list, Sach& sach);
void xuat_DSSach(NodeSachPtr list);
bool kiemTra_TrungMaSach(NodeSachPtr& list, const string& ma);
void xoaSach(NodeSachPtr& list, string maSach);
void capNhatThongTinSach(NodeSachPtr& list, string maSach);
NodeSachPtr timKiemSachTheoMa(NodeSachPtr list, string maSach);

// chức năng quản lý loại
