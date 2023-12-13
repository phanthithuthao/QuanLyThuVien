#include"header.h"
// HÀM XÓA MÀN HÌNH
void cls(HANDLE hConsole)
{
    // Lấy thông tin về bộ đệm màn hình console hiện tại.
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;

    // Kiểm tra xem có lấy được thông tin không.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    // Thiết lập hình chữ nhật cần cuộn.
    scrollRect.Left = 0;
    scrollRect.Top = 0; // Góc trái trên của hình chữ nhật cuộn, có thể thay đổi nếu cần.
    scrollRect.Right = csbi.dwSize.X;
    scrollRect.Bottom = csbi.dwSize.Y;

    // Thiết lập mục tiêu cuộn của hình chữ nhật.
    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);// Cuộn lên trên cùng với độ lớn bằng chiều cao của bộ đệm.

    // Thiết lập ký tự điền vào không gian cuộn.
    fill.Char.UnicodeChar = TEXT(' '); // Ký tự điền là khoảng trắng.
    fill.Attributes = csbi.wAttributes; // Thuộc tính văn bản của ký tự điền là giống như thuộc tính của bộ đệm hiện tại.

    // Thực hiện cuộn màn hình console.
    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

    // Đặt con trỏ văn bản về góc trái trên của màn hình.
    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;

    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

// GIAO DIỆN
// Hiển thị giao diện quản lý thư viện
void menuQLTV() {
    HANDLE hStdout;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    cls(hStdout);
    // Đọc file giao diện chính
    readFile("File/QuanLyThuVien.txt");
    int chon;
    do
    {
        cout << "\nLua chon cua ban ? ";
        cin >> chon;
        switch (chon)
        {
        case 1:
            menuThe();
            break;
        case 2:
            menuSach();
            break;
        case 3:
            cout << "Thoat chuong trinh.\n";
            exit(0);
            break;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai.\n";
        }
    } while (chon != 3);
}
// Hiển thị giao diện sách
void menuSach() {
    HANDLE hStdout;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    cls(hStdout);
    readFile("File/QuanLySachThuVien.txt");
    int n;
    Sach sach;
    NodeSachPtr dsSach = nullptr;
    NodeSachPtr sachTimThay = nullptr;
    do {
        cout << "\nLua chon cua ban ? ";
        cin >> n;

        // Xử lý lựa chọn
        switch (n) {
        case 1:
            menuThueTraSach();
            break;
        case 2:
            docFileSach(dsSach, "FileData/DauSach.txt");
            nhap_DSSach(dsSach, sach);
            ghiFileSach(dsSach, "FileData/DauSach.txt");
            cout << "Danh sach vua them vao: " << endl;
            cout << "-----------------------------------------------------------------" << endl;
            xuat_DSSach(dsSach);
            giaiPhongBoNho(dsSach);
            break;
        case 3:
            docFileSach(dsSach, "FileData/DauSach.txt");
            cout << "Nhap ma sach can xoa: ";
            cin >> sach.maDauSach;
            xoaSach(dsSach, sach.maDauSach);
            ghiFileSach(dsSach, "FileData/DauSach.txt");
            giaiPhongBoNho(dsSach);
            break;
        case 4:
            docFileSach(dsSach, "FileData/DauSach.txt");
            cout << "Nhap ma sach can xoa: ";
            cin >> sach.maDauSach;
            capNhatThongTinSach(dsSach, sach.maDauSach);
            ghiFileSach(dsSach, "FileData/DauSach.txt");
            giaiPhongBoNho(dsSach);
            break;
        case 5:
            docFileSach(dsSach, "FileData/DauSach.txt");
            cout << "Nhap ma sach can tim: ";
            cin >> sach.maDauSach;
            dsSach = timKiemSachTheoMa(dsSach, sach.maDauSach);
            if (dsSach != NULL) {
                cout << "Thong tin ve sach co ma " << sach.maDauSach << " la:" << endl;
                xuatSach(dsSach->data);
            }
            else {
                cout << "Khong tim thay sach co ma " << sach.maDauSach << endl;
            }
            giaiPhongBoNho(dsSach);
            break;
        case 6:
            docFileSach(dsSach, "FileData/DauSach.txt");
            cout << "-----------------------------------------------------------------" << endl;
            xuat_DSSach(dsSach);
            giaiPhongBoNho(dsSach);
            break;
        case 7:
            menuQLTV();
            break;
        default:
            cout << "Lua chon khong hop le. Vui long nhap lai.\n";
            break;
        }

    } while (n != 7);
}
// Hiển thị giao diện thẻ
void menuThe() {
    HANDLE hStdout;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    cls(hStdout);
    readFile("File/QuanLyTheThuVien.txt");
    int n;
    DocGia dg;
    NodeDocGiaPtr dsDocGia = nullptr;
    do {
        cout << "\nLua chon cua ban ? ";
        cin >> n;

        // Xử lý lựa chọn
        switch (n) {
        case 1:
            docFile(dsDocGia, "FileData/DSDocGia.txt");
            cout << "\nNhap ma the doc gia: ";
            cin >> dg.maDocGia;
            if (kiemTra_TrungMa(dsDocGia,dg.maDocGia))
            {
                NodeDocGiaPtr current = dsDocGia;
                while (current != NULL && current->data.maDocGia != dg.maDocGia) {
                    current = current->link;
                }
                if (current != NULL) {
                    xuatDocGia(current->data);
                }
                else {
                    cout << "\nKhong tim thay doc gia co ma " << dg.maDocGia << endl;
                }
            }
            else {
                cout << "\nMa chua ton tai trong thu vien";
            }
            giaiPhongBoNho(dsDocGia);
            
            break;
        case 2:
            docFile(dsDocGia, "FileData/DSDocGia.txt");
            nhap_DSDG(dsDocGia, dg);
            ghiFile(dsDocGia, "FileData/DSDocGia.txt");
            cout << "Danh sach doc gia vua them vao la: " << endl;
            xuat_DSDG(dsDocGia);
            giaiPhongBoNho(dsDocGia);
            break;
        case 3:
            docFile(dsDocGia, "FileData/DSDocGia.txt");
            cout << "\nNhap ma doc gia can huy: ";
            cin >> dg.maDocGia;
            xoaTheDocGia(dsDocGia, dg.maDocGia);
            ghiFile(dsDocGia, "FileData/DSDocGia.txt");
            giaiPhongBoNho(dsDocGia);
            break;
        case 4:
            docFile(dsDocGia, "FileData/DSDocGia.txt");
            cout << "\nNhap ma doc gia: ";
            cin >> dg.maDocGia;
            capNhatThongTin(dsDocGia, dg.maDocGia);
            ghiFile(dsDocGia, "FileData/DSDocGia.txt");
            giaiPhongBoNho(dsDocGia);
            break;
        case 5:
            cout << "Danh sach the doc gia: " << endl;
            cout << "-----------------------------------------------------------------" << endl;
            docFile(dsDocGia, "FileData/DSDocGia.txt");
            xuat_DSDG(dsDocGia);
            giaiPhongBoNho(dsDocGia);
            break;
        case 6:
            menuQLTV();
            break;
        default:
            cout << "Lua chon khong hop le. Vui long nhap lai.\n";
        }

    } while (n != 6);
}
// Hiển thị giao diện phiếu thuê
void menuThueTraSach() {
    HANDLE hStdout;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    cls(hStdout);
    readFile("File/QuanLyThueTraSach.txt");
    int n;
    do {
        // Hiển thị menu
        cout << "\nLua chon cua ban ? ";
        cin >> n;

        // Xử lý lựa chọn
        switch (n) {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:
            menuSach();
            break;
        default:
            cout << "Lua chon khong hop le. Vui long nhap lai.\n";
        }

    } while (n != 5);
}
// Hàm hiển thị giao diện các tiêu đề
void xuatTieuDe(const char* filePath)
{
    HANDLE hStdout;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    cls(hStdout);
    readFile(filePath);
}

// Hàm đọc nội dung của file txt giao diện và hiển thị nó trên màn hình console.
void readFile(const char* filename) {
    // Mở tệp với tên được chỉ định để đọc.
    fstream f(filename);
    // Chuỗi để lưu trữ từng dòng đọc từ tệp.
    string line;
    // Kiểm tra xem tệp có mở thành công hay không.
    if (f.is_open()) {
        getline(f, line);
        // Đọc và hiển thị nội dung từng dòng của tệp cho đến khi hết dữ liệu.
        // Lặp qua từng dòng trong tệp và hiển thị nó trên màn hình console.
        while (f)
        {
            cout << line << endl;
            getline(f, line);
        }
        // Đóng tệp sau khi đọc xong.
        f.close();
    }
}

// ĐỌC, GHI FILE ĐỘC GIẢ
// Hàm ghi thông tin một độc giả vào file
void GhiTTDG(ofstream& fileout, const DocGia& dg)
{
    fileout << dg.maDocGia << ",";
    fileout << dg.tenDocGia << ",";
    fileout << dg.lop << ",";
    fileout << dg.nganh << ",";
    fileout << dg.hanThe.ngay << "/" << dg.hanThe.ngay << "/" << dg.hanThe.nam << endl;
}
// Hàm ghi danh sách độc giả vào file
void GhiDSDG(ofstream& fileout, const NodeDocGiaPtr& list)
{
    NodeDocGiaPtr current = list;
    while (current != nullptr)
    {
        // Ghi thông tin một độc giả vào file
        GhiTTDG(fileout, current->data);

        // Di chuyển đến nút tiếp theo trong danh sách liên kết
        current = current->link;
    }
}
// Hàm ghi danh sách độc giả vào file
void ghiFile(const NodeDocGiaPtr& list, const string& filename)
{
    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        cout << "Khong the mo file de ghi." << endl;
        return;
    }
    else
    {
        GhiDSDG(outFile, list);
    }
    outFile.close();
}
// hàm đọc file .txt của danh sách độc giả và xuất ra danh sách
void docFile(NodeDocGiaPtr& list, const string& filename) {
    
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Khong the mo file de doc." << endl;
        return;
    }
    else
    {
        DocDSDG(inFile, list);
    }
    inFile.close();
}
// hàm đọc danh sách độc giả
void DocDSDG(ifstream& filein, NodeDocGiaPtr& list)
{
    DocGia dg;
    string line;
    while (getline(filein, line))
    {
        istringstream iss(line);

        // Sử dụng getline để đọc từng phần tử trong dòng
        getline(iss, dg.maDocGia, ',');
        getline(iss, dg.tenDocGia, ',');
        getline(iss, dg.lop, ',');
        getline(iss, dg.nganh, ',');
        string temp;
        getline(iss, temp, '/');
        stringstream(temp) >> dg.hanThe.ngay;
        getline(iss, temp, '/');
        stringstream(temp) >> dg.hanThe.thang;
        getline(iss, temp, ',');
        stringstream(temp) >> dg.hanThe.nam;

        // Thêm độc giả vào đầu danh sách liên kết
        them_Dau(list, dg);
    }
}

// ĐỌC, GHI FILE SÁCH
void GhiTTSach(ofstream& fileout, const Sach& sach) {
    fileout << sach.maDauSach << ",";
    fileout << sach.tenSach << ",";
    fileout << sach.loai.maLoai << ",";
    fileout << sach.tacGia << ",";
    fileout << sach.NXB.ngay << "/" << sach.NXB.thang << "/" << sach.NXB.nam << ",";
    fileout << sach.moTa << ",";
    fileout << sach.trangThai << ",";
    fileout << sach.soLuong << endl;
}
void GhiDSSach(ofstream& fileout, const NodeSachPtr& list) {
    NodeSachPtr current = list;
    while (current != nullptr) {
        // Ghi thông tin một quyển sách vào file
        GhiTTSach(fileout, current->data);

        // Di chuyển đến nút tiếp theo trong danh sách liên kết
        current = current->link;
    }
}
void docFileSach(NodeSachPtr& list, const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Khong the mo file de doc." << endl;
        return;
    }
    else {
        DocDSSach(inFile, list);
    }
    inFile.close();
}
void DocDSSach(ifstream& filein, NodeSachPtr& list) {
    Sach sach;
    string line;
    while (getline(filein, line)) {
        istringstream iss(line);

        // Sử dụng getline để đọc từng phần tử trong dòng
        getline(iss, sach.maDauSach, ',');
        getline(iss, sach.tenSach, ',');
        getline(iss, sach.loai.maLoai, ',');
        getline(iss, sach.tacGia, ',');
        string temp;
        getline(iss, temp, '/');
        stringstream(temp) >> sach.NXB.ngay;
        getline(iss, temp, '/');
        stringstream(temp) >> sach.NXB.thang;
        getline(iss, temp, ',');
        stringstream(temp) >> sach.NXB.nam;
        getline(iss, sach.moTa, ',');
        getline(iss, temp, ',');
        stringstream(temp) >> sach.trangThai;
        getline(iss, temp, ',');
        stringstream(temp) >> sach.soLuong;
        // Thêm sách vào đầu danh sách liên kết
        them_Dau(list, sach);
    }
}
void ghiFileSach(const NodeSachPtr& list, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Khong the mo file de ghi." << endl;
        return;
    }
    else {
        GhiDSSach(outFile, list);
    }
    outFile.close();
}

// ĐỌC, GHI FILE LOẠI SÁCH


// CÁC HÀM KIỂM TRA
// hàm kiểm tra trùng mã độc giả
bool kiemTra_TrungMa(NodeDocGiaPtr& list, const string& ma) {
    NodeDocGiaPtr p = list;
    while (p != NULL) {
        if (p->data.maDocGia == ma) // So sánh chuỗi trực tiếp
            return true;
        p = p->link;
    }
    return false;
}
// hàm kiểm tra trùng mã sách
bool kiemTra_TrungMaSach(NodeSachPtr& list, const string& ma) { 
    NodeSachPtr p = list;
    while (p != NULL) {
        if (p->data.maDauSach == ma) // So sánh chuỗi trực tiếp
            return true;
        p = p->link;
    }
    return false;
}
// hàm kiểm tra trùng mã loại sách
bool kiemTra_TrungMaLoaiSach(NodeLoaiSachPtr& list, const string& ma) {
    NodeLoaiSachPtr p = list;
    while (p != NULL) {
        if (p->data.maLoai == ma) // So sánh chuỗi trực tiếp
            return true;
        p = p->link;
    }
    return false;
}


// hàm lấy ngày đúng theo tháng
int getday(int m) {
    switch (m) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
        break;

    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
        break;

    case 2:
        return 28;
        break;

    default:
        return 0;
        break;
    }
}
// hàm kiểm tra ngày tháng năm đúng
bool check(int d, int m, int y) {

    if (d < 1 || d > 31 || m < 1 || m > 12 || y < 1800 || y > 9999) {
        return false;
    }

    // Kiểm tra năm nhuận
    bool isLeapYear = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);

    // Kiểm tra tháng 2 cho năm nhuận
    if (m == 2 && isLeapYear) {
        return (d >= 1 && d <= 29);
    }

    // Kiểm tra tháng 2 cho năm không nhuận
    if (m == 2) {
        return (d >= 1 && d <= 28);
    }

    // Kiểm tra các tháng khác
    return (d >= 1 && d <= getday(m));
}

// HÀM CHỨC NĂNG CỦA QUẢN LÝ THẺ ĐỘC GIẢ
void khoiTao(NodeDocGiaPtr& list) {
    list = NULL;
}
int isEmpty(NodeDocGiaPtr list) {
    return list == NULL ? 1 : 0;
}
NodeDocGiaPtr tao_Node_DocGia(DocGia dg) {
    NodeDocGiaPtr p;
    p = new NodeDocGia;
    p->data = dg;
    p->link = NULL;
    return p;
}
NodeDocGiaPtr them_Dau(NodeDocGiaPtr& list, DocGia dg)
{
    NodeDocGiaPtr p = tao_Node_DocGia(dg);
    p->link = list;
    list = p;
    return p;
}
NodeDocGiaPtr Them_Cuoi(NodeDocGiaPtr& list, DocGia dg)
{
    if (isEmpty(list)) {
        them_Dau(list, dg);
    }
    else {
        //tìm cuối
        NodeDocGiaPtr q = list;
        while (q->link != NULL) q = q->link;
        NodeDocGiaPtr p = tao_Node_DocGia(dg);
        q->link = p;
    }
    return list;
}
// Hàm giải phóng
void giaiPhongBoNho(NodeDocGiaPtr& list) {
    NodeDocGiaPtr current = list;
    NodeDocGiaPtr next;

    while (current != NULL) {
        next = current->link;
        delete current;
        current = next;
    }

    list = NULL; // Đảm bảo danh sách trở về trạng thái ban đầu
}
// Nhập, xuất độc giả
void nhapDocGia(DocGia& dg) {
    cout << "Nhap ma doc gia: ";
    cin >> dg.maDocGia;
    cout << "Nhap ten doc gia: ";
    cin.ignore();
    getline(cin, dg.tenDocGia);
    cout << "Nhap lop: ";
    cin >> dg.lop;
    cout << "Nhap nganh: ";
    cin.ignore();
    getline(cin, dg.nganh);

}
void xuatDocGia(DocGia dg) {
    cout << "Ma doc gia: " << dg.maDocGia << endl;
    cout << "Ten doc gia: " << dg.tenDocGia << endl;
    cout << "Lop doc gia: " << dg.lop << endl;
    cout << "Nganh doc gia: " << dg.nganh << endl;
}
// Nhập, xuất danh sách độc giả
void nhap_DSDG(NodeDocGiaPtr& list, DocGia& dg) {
    do {
        cout << "(NHAP 0 DE THOAT):" << endl;
        cout << "Nhap ma DG: ";
        cin >> dg.maDocGia;
        while (kiemTra_TrungMa(list, dg.maDocGia)) {
            cout << "\nMa so dg bi trung";
            cout << "\nNhap lai ma so dg:";
            cin >> dg.maDocGia;
        }
        if (dg.maDocGia == "0")
        {
            break;
        }
        cout << "Nhap ten doc gia: ";
        cin.ignore();
        getline(cin, dg.tenDocGia);
        cout << "Nhap lop: ";
        cin >> dg.lop;
        cout << "Nhap nganh: ";
        cin.ignore();
        getline(cin, dg.nganh);
        do {
            cout << "Nhap ngay het han: ";
            cin >> dg.hanThe.ngay;
            cout << "Nhap thang het han: ";
            cin >> dg.hanThe.thang;
            cout << "Nhap nam het han: ";
            cin >> dg.hanThe.nam;

            if (!check(dg.hanThe.ngay, dg.hanThe.thang, dg.hanThe.nam)) {
                cout << "Ngay thang nam khong hop le. Vui long nhap lai." << endl;
            }
            else break;
        } while (1);
        them_Dau(list, dg);
    } while (1);
}
void xuat_DSDG(NodeDocGiaPtr list)
{
    NodeDocGiaPtr current = list;
    while (current != NULL)
    {
        cout << "Ma doc gia: " << current->data.maDocGia << endl;
        cout << "Ho va Ten: " << current->data.tenDocGia << endl;
        cout << "Lop: " << current->data.nganh << endl;
        cout << "Nganh: " << current->data.lop << endl;
        cout << "Han the: " << current->data.hanThe.ngay << "/"
            << current->data.hanThe.thang << "/"
            << current->data.hanThe.nam << endl;
        cout << "-----------------------------------------------------------------" << endl;
        current = current->link;

    }
}
// Hàm xóa thẻ độc giả theo mã
void xoaTheDocGia(NodeDocGiaPtr& list, string maDocGia) {
    NodeDocGiaPtr current = list;
    NodeDocGiaPtr previous = NULL;

    // Duyệt danh sách để tìm thẻ có mã cần xóa
    while (current != NULL && current->data.maDocGia != maDocGia) {
        previous = current;
        current = current->link;
    }

    // Nếu thẻ được tìm thấy
    if (current != NULL) {
        // Nếu thẻ là thẻ đầu danh sách
        if (previous == NULL) {
            list = current->link;
        }
        else {
            previous->link = current->link;
        }
        delete current; // Xóa thẻ
        cout << "Da xoa thong tin doc gia co ma " << maDocGia << endl;
    }
    else {
        cout << "Khong tim thay doc gia co ma " << maDocGia << endl;
    }
}
// Hàm cập nhật thông tin thẻ độc giả theo mã
void capNhatThongTin(NodeDocGiaPtr& list, string maDocGia) {
    NodeDocGiaPtr current = list;

    // Duyệt danh sách để tìm thẻ có mã cần cập nhật
    while (current != NULL && current->data.maDocGia != maDocGia) {
        current = current->link;
    }

    // Nếu thẻ được tìm thấy
    if (current != NULL) {
        cout << "Nhap thong tin moi cho doc gia co ma " << maDocGia << ":" << endl;
        cout << "Nhap ten doc gia: ";
        cin.ignore();
        getline(cin, current->data.tenDocGia);
        cout << "Nhap lop: ";
        cin >> current->data.lop;
        cout << "Nhap nganh: ";
        cin.ignore();
        getline(cin, current->data.nganh);
        do {
            cout << "Nhap ngay het han: ";
            cin >> current->data.hanThe.ngay;
            cout << "Nhap thang het han: ";
            cin >> current->data.hanThe.thang;
            cout << "Nhap nam het han: ";
            cin >> current->data.hanThe.nam;

            if (!check(current->data.hanThe.ngay, current->data.hanThe.thang, current->data.hanThe.nam)) {
                cout << "Ngay thang nam khong hop le. Vui long nhap lai." << endl;
            }
            else {
                cout << "Cap nhat thong tin thanh cong." << endl;
                break;
            }
        } while (1);
    }
    else {
        cout << "Khong tim thay doc gia co ma " << maDocGia << endl;
    }
}

// HÀM CHỨC NĂNG CỦA QUẢN LÝ SÁCH
void khoiTao(NodeSachPtr& list) {
    list = NULL;
}
int isEmpty(NodeSachPtr list) {
    return list == NULL ? 1 : 0;
}
NodeSachPtr tao_Node_Sach(Sach sach) {
    NodeSachPtr p;
    p = new NodeSach;
    p->data = sach;
    p->link = NULL;
    return p;
}
NodeSachPtr them_Dau(NodeSachPtr& list, Sach sach) {
    NodeSachPtr p = tao_Node_Sach(sach);
    p->link = list;
    list = p;
    return p;
}
void giaiPhongBoNho(NodeSachPtr& list) {
    NodeSachPtr current = list;
    NodeSachPtr next;

    while (current != NULL) {
        next = current->link;
        delete current;
        current = next;
    }

    list = NULL;
}
void nhapSach(Sach& sach) {
    cout << "Nhap ma dau sach: ";
    cin >> sach.maDauSach;
    cout << "Nhap ten sach: ";
    cin.ignore();
    getline(cin, sach.tenSach);
    cout << "Nhap ma loai sach: ";
    cin >> sach.loai.maLoai;
    cout << "Nhap tac gia: ";
    cin.ignore();
    getline(cin, sach.tacGia);
    cout << "Nhap mo ta: ";
    getline(cin, sach.moTa);
    cout << "Nhap ngay xuat ban (ngay thang nam cach nhau boi dau cach): ";
    cin >> sach.NXB.ngay >> sach.NXB.thang >> sach.NXB.nam;
    cout << "Nhap so luong: ";
    cin >> sach.soLuong;
}
void xuatSach(Sach sach) {
    cout << "Ma dau sach: " << sach.maDauSach << endl;
    cout << "Ten sach: " << sach.tenSach << endl;
    cout << "Ma loai sach: " << sach.loai.maLoai << endl;
    cout << "Tac gia: " << sach.tacGia << endl;
    cout << "Ngay xuat ban: " << sach.NXB.ngay << "/" << sach.NXB.thang << "/" << sach.NXB.nam << endl;
    cout << "Mo ta: " << sach.moTa << endl;
    cout << "So luong: " << sach.soLuong << endl;
    if (sach.soLuong == 0) {
        cout << "Trang thai: " << "sach da het" << endl;
    }
    else
    {
        cout << "Trang thai: " << "sach con tren ke" << endl;
    }
    
    
}
void nhap_DSSach(NodeSachPtr& list, Sach& sach) {
    do {
        cout << "(NHAP 0 DE THOAT):" << endl;
        cout << "Nhap ma dau sach: ";
        cin >> sach.maDauSach;
        while (kiemTra_TrungMaSach(list, sach.maDauSach)) {
            cout << "\nMa so dg bi trung";
            cout << "\nNhap lai ma so dg:";
            cin >> sach.maDauSach;
        }
        if (sach.maDauSach == "0")
        {
            break;
        }
        cout << "Nhap ten sach: ";
        cin.ignore();
        getline(cin, sach.tenSach);
        cout << "Nhap ma loai sach: ";
        cin >> sach.loai.maLoai;
        cout << "Nhap ten tac gia: ";
        cin.ignore();
        getline(cin, sach.tacGia);
        do {
            cout << "Nhap NXB: ";
            cin >> sach.NXB.ngay >> sach.NXB.thang >> sach.NXB.nam;

            if (!check(sach.NXB.ngay, sach.NXB.thang, sach.NXB.nam)) {
                cout << "Ngay thang nam khong hop le. Vui long nhap lai." << endl;
            }
            else break;
        } while (1);
        cout << "Nhap mo ta: ";
        cin.ignore();
        getline(cin, sach.moTa);
        cout << "Nhap trang thai (0: da duoc muon, 1: con tren ke): ";
        cin >> sach.trangThai;
        cout << "Nhap so luong: ";
        cin >> sach.soLuong;
        them_Dau(list, sach);
    } while (1);
}
void xuat_DSSach(NodeSachPtr list) {
    NodeSachPtr current = list;
    while (current != NULL) {
        xuatSach(current->data);
        current = current->link;
    }
}
void xoaSach(NodeSachPtr& list, string maSach) {
    NodeSachPtr current = list;
    NodeSachPtr previous = NULL;

    // Duyệt danh sách để tìm thẻ có mã cần xóa
    while (current != NULL && current->data.maDauSach != maSach) {
        previous = current;
        current = current->link;
    }

    // Nếu thẻ được tìm thấy
    if (current != NULL) {
        // Nếu thẻ là thẻ đầu danh sách
        if (previous == NULL) {
            list = current->link;
        }
        else {
            previous->link = current->link;
        }
        delete current; // Xóa thẻ
        cout << "Da xoa thong tin doc gia co ma " << maSach << endl;
    }
    else {
        cout << "Khong tim thay doc gia co ma " << maSach << endl;
    }
}
void capNhatThongTinSach(NodeSachPtr& list, string maSach) {
    NodeSachPtr current = list;

    // Duyệt danh sách để tìm thẻ có mã cần cập nhật
    while (current != NULL && current->data.maDauSach != maSach) {
        current = current->link;
    }

    // Nếu thẻ được tìm thấy
    if (current != NULL) {
        cout << "Nhap thong tin moi cho sach co ma " << maSach << ":" << endl;
        cout << "Nhap ten sach: ";
        cin.ignore();
        getline(cin, current->data.tenSach);
        cout << "Nhap loai sach : ";
        cin >> current->data.loai.maLoai;
        cout << "Nhap tac gia: ";
        cin.ignore();
        getline(cin, current->data.tacGia);
        do {
            cout << "Nhap NXB: ";
            cin >> current->data.NXB.ngay >> current->data.NXB.thang >> current->data.NXB.nam;

            if (!check(current->data.NXB.ngay , current->data.NXB.thang , current->data.NXB.nam)) {
                cout << "Ngay thang nam khong hop le. Vui long nhap lai." << endl;
            }
            else {
                break;
            }
        } while (1);
        cout << "Nhap so luong: ";
        cin >> current->data.soLuong;
        cout << "Cap nhat thong tin sach thanh cong";
    }
    else {
        cout << "Khong tim thay doc gia co ma " << maSach << endl;
    }
}
NodeSachPtr timKiemSachTheoMa(NodeSachPtr list, string maSach) {
    NodeSachPtr current = list;

    // Duyệt danh sách để tìm sách có mã cần tìm
    while (current != NULL && current->data.maDauSach != maSach) {
        current = current->link;
    }

    // Nếu sách được tìm thấy, trả về con trỏ đến sách đó
    // Nếu không tìm thấy, trả về NULL
    return current;
}

// CHỨC NĂNG LOẠI SÁCH