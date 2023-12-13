#pragma once
#include "header.h"
#define MAX 100
// kiểu dữ liệu độc giả
struct DocGia
{
    string maDocGia;
    string tenDocGia;
    string lop;
    string nganh;
};
// danh sách độc giả
struct DSDocGia {
    int n;
    DocGia data[MAX];
};
// danh sách liên kết đơn
typedef struct NodeDocGia* NodeDocGiaPtr;
struct NodeDocGia
{
    DocGia data;
    NodeDocGiaPtr link;
};
void nhapDocGia(DocGia& dg);
void xuatDocGia(DocGia dg);
//void nhapDanhSachDG(DSDocGia& ds);
//void xuatDanhSachDG(DSDocGia ds);



