/*
=====================================================================
ĐỀ TÀI: QUẢN LÝ THU – CHI CÁ NHÂN (C++ – LẬP TRÌNH HƯỚNG ĐỐI TƯỢNG)
=====================================================================

==================== 1. GIỚI THIỆU ĐỀ TÀI ====================

- Lý do chọn đề tài:
Trong cuộc sống hằng ngày, đặc biệt là đối với sinh viên, việc quản lý
thu nhập và chi tiêu cá nhân là rất cần thiết để kiểm soát tài chính,
tránh chi tiêu không hợp lý và hướng tới các mục tiêu tài chính cụ thể.
Do đó, đề tài “Quản lý thu – chi cá nhân” mang tính thực tiễn cao và
phù hợp để áp dụng kiến thức lập trình hướng đối tượng (OOP).

- Mục tiêu thực hiện:
+ Áp dụng các nguyên lý lập trình hướng đối tượng (OOP):
  đóng gói, kế thừa, đa hình.
+ Sử dụng interface và lớp trừu tượng.
+ Xây dựng chương trình quản lý thu – chi bằng menu console.
+ Mở rộng sáng tạo với chức năng mục tiêu tài chính cá nhân.
+ Lưu và đọc dữ liệu từ file để tránh mất dữ liệu khi thoát chương trình.

==================== 2. PHÂN TÍCH BÀI TOÁN ====================

- Xác định đối tượng:
+ Giao dịch tài chính (GiaoDich)
+ Giao dịch thu (Thu)
+ Giao dịch chi (Chi)
+ Bộ quản lý thu – chi (QuanLyThuChi)
+ Mục tiêu tài chính cá nhân (MucTieuTaiChinh)

- Ràng buộc và yêu cầu đặc biệt:
+ Chương trình phải áp dụng OOP.
+ Dữ liệu giao dịch được lưu bằng vector.
+ Sử dụng đa hình để xử lý các loại giao dịch.
+ Số tiền phải hiển thị rõ ràng theo định dạng VND .
+ Dữ liệu phải được lưu và đọc lại từ file.

==================== 3. PHÂN TÍCH THIẾT KẾ ====================

- Nhiệm vụ chương trình:
+ Thêm, sửa, xóa giao dịch thu – chi.
+ Hiển thị danh sách giao dịch.
+ Sắp xếp giao dịch theo số tiền.
+ Tính số dư hiện tại.
+ Nhập mục tiêu tài chính và đánh giá mức độ hoàn thành.
+ Lưu và đọc dữ liệu từ file text.

- Thiết kế tổng thể:
+ Interface IDisplay: chuẩn hóa hàm hiển thị.
+ Lớp trừu tượng GiaoDich: chứa thông tin chung.
+ Lớp Thu và Chi: kế thừa GiaoDich và override phương thức.
+ Lớp QuanLyThuChi: quản lý danh sách giao dịch.
+ Lớp MucTieuTaiChinh: mở rộng sáng tạo.

==================== 4. THỰC HIỆN PHÂN TÍCH ====================

- Mô tả lớp:
+ GiaoDich:
  Thuộc tính: ngay, moTa, soTien
  Phương thức ảo: getSoTien(), loai(), hienThi()

+ Thu:
  Tiền được cộng vào số dư.

+ Chi:
  Tiền được trừ khỏi số dư.

+ QuanLyThuChi:
  Quản lý vector<GiaoDich*>, thực hiện thêm, sửa, xóa, sắp xếp,
  tính số dư, ghi và đọc file.

+ MucTieuTaiChinh:
  Lưu tên mục tiêu và số tiền cần đạt, đánh giá kết quả.

- Luồng xử lý chương trình:
+ Khi chạy: đọc dữ liệu từ file.
+ Người dùng thao tác qua menu.
+ Khi thoát: ghi dữ liệu ra file.

==================== MENU ====================
1. Nhập mục tiêu tài chính
2. Thêm thu
3. Thêm chi
4. Sửa giao dịch
5. Xóa giao dịch
6. Sắp xếp giao dịch
7. Hiển thị danh sách
8. Đánh giá mục tiêu
0. Thoát chương trình
=====================================================================
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

/* ====================================================
   HÀM ĐỊNH DẠNG TIỀN: x0.000.000 VND
==================================================== */
string formatTien(long long tien) {
    string s = to_string(tien);
    string res = "";
    int cnt = 0;

    for (int i = s.size() - 1; i >= 0; i--) {
        res = s[i] + res;
        cnt++;
        if (cnt % 3 == 0 && i != 0)
            res = "." + res;
    }
    return res + " VND";
}

/* ================= INTERFACE ================= */
class IDisplay {
public:
    virtual void hienThi() const = 0;
    virtual ~IDisplay() {}
};

/* ================= LỚP TRỪU TƯỢNG ================= */
class GiaoDich : public IDisplay {
protected:
    string ngay;
    string moTa;
    long long soTien;

public:
    virtual long long getSoTien() const = 0;
    virtual string loai() const = 0;

    virtual void nhap() {
        cout << "Ngay: ";
        getline(cin >> ws, ngay);
        cout << "Mo ta: ";
        getline(cin, moTa);
        cout << "So tien: ";
        cin >> soTien;
    }

    virtual ~GiaoDich() {}

    friend class QuanLyThuChi;
};

/* ================= LỚP THU ================= */
class Thu : public GiaoDich {
public:
    long long getSoTien() const override {
        return soTien;
    }

    string loai() const override {
        return "Thu";
    }

    void hienThi() const override {
        cout << "[THU] " << ngay << " | " << moTa
             << " | +" << formatTien(soTien) << endl;
    }
};

/* ================= LỚP CHI ================= */
class Chi : public GiaoDich {
public:
    long long getSoTien() const override {
        return -soTien;
    }

    string loai() const override {
        return "Chi";
    }

    void hienThi() const override {
        cout << "[CHI] " << ngay << " | " << moTa
             << " | -" << formatTien(soTien) << endl;
    }
};

/* ================= MỤC TIÊU TÀI CHÍNH ================= */
class MucTieuTaiChinh {
private:
    string ten;
    long long mucTieu;

public:
    void nhap() {
        cout << "Ten muc tieu: ";
        getline(cin >> ws, ten);
        cout << "So tien can dat: ";
        cin >> mucTieu;
    }

    void danhGia(long long soDu) const {
        cout << "\n===== DANH GIA MUC TIEU =====\n";
        cout << "Muc tieu: " << ten << endl;
        cout << "Can dat: " << formatTien(mucTieu) << endl;
        cout << "So du hien tai: " << formatTien(soDu) << endl;

        if (soDu >= mucTieu)
            cout << ">> DA HOAN THANH MUC TIEU <<\n";
        else
            cout << ">> CHUA HOAN THANH MUC TIEU <<\n";
    }
};

/* ================= QUẢN LÝ THU – CHI ================= */
class QuanLyThuChi {
private:
    vector<GiaoDich*> ds;

public:
    ~QuanLyThuChi() {
        for (auto p : ds) delete p;
    }

    void themThu() {
        GiaoDich* p = new Thu();
        p->nhap();
        ds.push_back(p);
    }

    void themChi() {
        GiaoDich* p = new Chi();
        p->nhap();
        ds.push_back(p);
    }

    void sua(int idx) {
        if (idx >= 0 && idx < ds.size())
            ds[idx]->nhap();
    }

    void xoa(int idx) {
        if (idx >= 0 && idx < ds.size()) {
            delete ds[idx];
            ds.erase(ds.begin() + idx);
        }
    }

    void hienThi() const {
        for (int i = 0; i < ds.size(); i++) {
            cout << i << ". ";
            ds[i]->hienThi();
        }
    }

    void sapXep() {
        sort(ds.begin(), ds.end(),
             [](GiaoDich* a, GiaoDich* b) {
                 return a->getSoTien() > b->getSoTien();
             });
    }

    long long tinhSoDu() const {
        long long tong = 0;
        for (auto p : ds)
            tong += p->getSoTien();
        return tong;
    }

    /* ===== GHI FILE ===== */
    void ghiFile(const string& file) const {
        ofstream fout(file);
        for (auto p : ds) {
            fout << p->loai() << "|"
                 << p->ngay << "|"
                 << p->moTa << "|"
                 << llabs(p->soTien) << endl;
        }
        fout.close();
    }

    /* ===== ĐỌC FILE ===== */
    void docFile(const string& file) {
        ifstream fin(file);
        if (!fin) return;

        string loai, ngay, moTa;
        long long tien;

        while (getline(fin, loai, '|')) {
            getline(fin, ngay, '|');
            getline(fin, moTa, '|');
            fin >> tien;
            fin.ignore();

            GiaoDich* p;
            if (loai == "Thu") p = new Thu();
            else p = new Chi();

            p->ngay = ngay;
            p->moTa = moTa;
            p->soTien = tien;

            ds.push_back(p);
        }
        fin.close();
    }
};

/* ================= MAIN ================= */
int main() {
    QuanLyThuChi ql;
    MucTieuTaiChinh mt;

    ql.docFile("data.txt");

    int chon, idx;
    do {
        cout << "\n MENU \n";
        cout << "1. Nhap muc tieu\n";
        cout << "2. Them THU\n";
        cout << "3. Them CHI\n";
        cout << "4. Sua giao dich\n";
        cout << "5. Xoa giao dich\n";
        cout << "6. Sap xep\n";
        cout << "7. Hien danh sach\n";
        cout << "8. Danh gia muc tieu\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> chon;

        switch (chon) {
        case 1: mt.nhap(); break;
        case 2: ql.themThu(); break;
        case 3: ql.themChi(); break;
        case 4:
            cout << "Nhap index: ";
            cin >> idx;
            ql.sua(idx);
            break;
        case 5:
            cout << "Nhap index: ";
            cin >> idx;
            ql.xoa(idx);
            break;
        case 6:
            ql.sapXep();
            cout << "Da sap xep!\n";
            break;
        case 7:
            ql.hienThi();
            break;
        case 8:
            mt.danhGia(ql.tinhSoDu());
            break;
        case 0:
            ql.ghiFile("data.txt");
            cout << "Da luu du lieu. Thoat chuong trinh.\n";
            break;
        }
    } while (chon != 0);

    return 0;
}