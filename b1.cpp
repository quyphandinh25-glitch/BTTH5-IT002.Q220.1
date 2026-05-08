#include <iostream>
#include <string>
#include <vector>

using namespace std;

class NgaySinh {
private:
    int ngay, thang, nam;

public:
    void Nhap() {
        cin >> ngay >> thang >> nam;
    }
    void Xuat() {
        cout << ngay << "/" << thang << "/" << nam;
    }
    int getNam() {
        return nam;
    }
    int getThang() {
        return thang;
    }
    int getNgay() {
        return ngay;
    }
};

class NhanVien {
protected: 
    string name;
    NgaySinh ns;

public:
    NhanVien() {}
    virtual ~NhanVien() {} 

    virtual void Nhap() {
        cin.ignore(); 
        cout << "- Nhap ho ten: ";
        getline(cin, name);
        cout << "- Nhap ngay sinh (ngay thang nam): ";
        ns.Nhap();
    }

    virtual void Xuat() {
        cout << "Ho ten: " << name << " | Ngay sinh: ";
        ns.Xuat();
    }

    virtual double tinhLuong() = 0; 
    
    int getNamSinh() {
        return ns.getNam();
    }
    int getThangSinh() {
        return ns.getThang();
    }
    int getNgaySinh() {
        return ns.getNgay();
    }

    virtual int getLoai() = 0; 
};

class NhanVienVP : public NhanVien {
private:
    int soNgayLamViec;

public:
    void Nhap() override {
        NhanVien::Nhap(); 
        cout << "- Nhap so ngay lam viec: ";
        cin >> soNgayLamViec;
    }

    void Xuat() override {
        NhanVien::Xuat();
        cout << " | Loai: NV Van Phong | Ngay lam: " << soNgayLamViec 
             << " | Luong: " << (long long)tinhLuong() << endl;
    }

    double tinhLuong() override {
        return soNgayLamViec * 100000.0;
    }

    int getLoai() override {
        return 1;
    }
};

class NhanVienSX : public NhanVien {
private:
    double luongCanBan;
    int soSanPham;

public:
    void Nhap() override {
        NhanVien::Nhap();
        cout << "- Nhap luong can ban: ";
        cin >> luongCanBan;
        cout << "- Nhap so san pham: ";
        cin >> soSanPham;
    }

    void Xuat() override {
        NhanVien::Xuat();
        cout << " | Loai: NV San Xuat | Luong CB: " << (long long)luongCanBan 
             << " | So SP: " << soSanPham 
             << " | Luong: " << (long long)tinhLuong() << endl;
    }

    double tinhLuong() override {
        return luongCanBan + (soSanPham * 5000.0);
    }

    int getLoai() override {
        return 2;
    }
};

class CongTy {
private:
    vector<NhanVien*> dsNhanVien;

public:
    ~CongTy() {
        for (NhanVien* nv : dsNhanVien) {
            delete nv;
        }
    }

    void NhapDanhSach() {
        int n_vp, n_sx;
        
        cout << "--- NHAP DANH SACH NHAN VIEN VAN PHONG ---\n";
        cout << "Nhap so luong NVVP: ";
        cin >> n_vp;
        for (int i = 0; i < n_vp; i++) {
            cout << "Nhap thong tin NVVP thu " << i + 1 << ":\n";
            NhanVien* nv = new NhanVienVP();
            nv->Nhap();
            dsNhanVien.push_back(nv);
        }

        cout << "\n--- NHAP DANH SACH NHAN VIEN SAN XUAT ---\n";
        cout << "Nhap so luong NVSX: ";
        cin >> n_sx;
        for (int i = 0; i < n_sx; i++) {
            cout << "Nhap thong tin NVSX thu " << i + 1 << ":\n";
            NhanVien* nv = new NhanVienSX();
            nv->Nhap();
            dsNhanVien.push_back(nv);
        }
    }

    void XuatDanhSach() {
        cout << "\n--- DANH SACH THONG TIN NHAN VIEN ---\n";
        for (NhanVien* nv : dsNhanVien) {
            nv->Xuat(); 
        }
    }

    double TinhTongLuong() {
        double tong = 0;
        for (NhanVien* nv : dsNhanVien) {
            tong += nv->tinhLuong();
        }
        return tong;
    }

    void NVSX_LuongThapNhat() {
        double minLuong = -1;
        NhanVien* nvsx_min = nullptr;

        for (NhanVien* nv : dsNhanVien) {
            if (nv->getLoai() == 2) { 
                if (minLuong == -1 || nv->tinhLuong() < minLuong) {
                    minLuong = nv->tinhLuong();
                    nvsx_min = nv;
                }
            }
        }

        if (nvsx_min != nullptr) {
            cout << "NVSX co luong thap nhat la:\n";
            nvsx_min->Xuat();
        } else {
            cout << "Khong co Nhan vien san xuat nao.\n";
        }
    }

    void NVVP_TuoiCaoNhat() {
        int minNam = 9999, minThang = 99, minNgay = 99;
        NhanVien* nvvp_maxTuoi = nullptr;

        for (NhanVien* nv : dsNhanVien) {
            if (nv->getLoai() == 1) { 
                bool isOlder = false;
                
                if (nv->getNamSinh() < minNam) {
                    isOlder = true;
                } else if (nv->getNamSinh() == minNam) {
                    if (nv->getThangSinh() < minThang) {
                        isOlder = true;
                    } else if (nv->getThangSinh() == minThang) {
                        if (nv->getNgaySinh() < minNgay) {
                            isOlder = true;
                        }
                    }
                }

                if (isOlder) {
                    minNam = nv->getNamSinh();
                    minThang = nv->getThangSinh();
                    minNgay = nv->getNgaySinh();
                    nvvp_maxTuoi = nv;
                }
            }
        }

        if (nvvp_maxTuoi != nullptr) {
            cout << "NVVP co tuoi cao nhat la:\n";
            nvvp_maxTuoi->Xuat();
        } else {
            cout << "Khong co Nhan vien van phong nao.\n";
        }
    }
};

int main() {
    CongTy cty;
    
    cty.NhapDanhSach();
    cty.XuatDanhSach();
    
    cout << "\n=> TONG LUONG CONG TY PHAI TRA: " << (long long)cty.TinhTongLuong() << "\n";
    
    cout << "\n--- KET QUA THONG KE ---\n";
    cty.NVSX_LuongThapNhat();
    cty.NVVP_TuoiCaoNhat();

    return 0;
}
