#include <bits/stdc++.h>
using namespace std;

class NhanVien
{
protected:
    string maNV;
    string hoTen;
    int tuoi;
    string sdt;
    string email;
    double luongCB;

public:
    virtual void Nhap()
    {
        cout << "Nhap ma nhan vien: ";
        cin >> maNV;
        cin.ignore();
        cout << "Nhap ho ten: ";
        getline(cin, hoTen);
        cout << "Nhap tuoi: ";
        cin >> tuoi;
        cin.ignore();
        cout << "Nhap so dien thoai: ";
        getline(cin, sdt);
        cout << "Nhap email: ";
        getline(cin, email);
        cout << "Nhap luong co ban: ";
        cin >> luongCB;
    }
    
    virtual void Xuat()
    {
        cout << "Ma NV: " << maNV << "\t" << "Ten: " << hoTen << "\t" 
             << "Tuoi: " << tuoi << "\t" << "SDT: " << sdt << "\t" 
             << "Email: " << email << "\t" << "Luong CB: " << fixed << setprecision(0) << luongCB << "\t";
    }
    
    virtual ~NhanVien() {}
    virtual int getLoai() = 0;
    virtual double TinhLuong() = 0;
};

class LapTrinhVien : public NhanVien
{
private:
    int gioOvertime;

public:
    void Nhap() override
    {
        NhanVien::Nhap();
        cout << "Nhap so gio overtime: ";
        cin >> gioOvertime;
    }
    
    void Xuat() override
    {
        NhanVien::Xuat();
        cout << "Gio OT: " << gioOvertime << "\t" 
             << "Tong Luong: " << fixed << setprecision(0) << TinhLuong() << "\n";
    }
    
    int getLoai() override
    {
        return 1;
    }
    
    double TinhLuong() override
    {
        return luongCB + (gioOvertime * 200000);
    }
};

class KiemChungVien : public NhanVien
{
private:
    int soLoi;

public:
    void Nhap() override
    {
        NhanVien::Nhap();
        cout << "Nhap so loi phat hien: ";
        cin >> soLoi;
    }
    
    void Xuat() override
    {
        NhanVien::Xuat();
        cout << "So loi: " << soLoi << "\t" 
             << "Tong Luong: " << fixed << setprecision(0) << TinhLuong() << "\n";
    }
    
    int getLoai() override
    {
        return 2;
    }
    
    double TinhLuong() override
    {
        return luongCB + (soLoi * 50000);
    }
};

class CongTy
{
private:
    vector<NhanVien *> ds;
    int SLLTV, SLKCV;

public:
    ~CongTy()
    {
        for (NhanVien *nv : ds)
        {
            delete nv;
        }
    }
    
    void NhapDanhSach()
    {
        cout << "Nhap so luong Lap Trinh Vien: ";
        cin >> SLLTV;
        cout << "Nhap so luong Kiem Chung Vien: ";
        cin >> SLKCV;
        
        cout << "\n--- NHAP THONG TIN LAP TRINH VIEN ---\n";
        for (int i = 0; i < SLLTV; i++)
        {
            NhanVien *nv = new LapTrinhVien();
            nv->Nhap();
            ds.push_back(nv);
        }
        
        cout << "\n--- NHAP THONG TIN KIEM CHUNG VIEN ---\n";
        for (int i = 0; i < SLKCV; i++)
        {
            NhanVien *nv = new KiemChungVien();
            nv->Nhap();
            ds.push_back(nv);
        }
    }
    
    void XuatDanhSach()
    {
        for (NhanVien *x : ds)
        {
            if (x->getLoai() == 1)
            {
                cout << "[LTV] ";
                x->Xuat();
            }
            else if (x->getLoai() == 2)
            {
                cout << "[KCV] ";
                x->Xuat();
            }
        }
    }

    void LuongThapHonTB()
    {
        if (ds.empty()) return;
        
        double tongLuong = 0;
        for (NhanVien *x : ds)
        {
            tongLuong += x->TinhLuong();
        }
        
        double trungBinh = tongLuong / ds.size();
        cout << "Muc luong trung binh cua cong ty: " << fixed << setprecision(0) << trungBinh << "\n";
        
        for (NhanVien *x : ds)
        {
            if (x->TinhLuong() < trungBinh)
            {
                x->Xuat();
            }
        }
    }

    void NhanVienLuongCaoNhat()
    {
        vector<NhanVien *> dsMax;
        double maxLuong = -1;
        
        for (NhanVien *x : ds)
        {
            if (x->TinhLuong() > maxLuong)
            {
                maxLuong = x->TinhLuong();
                dsMax.clear();
                dsMax.push_back(x);
            }
            else if (x->TinhLuong() == maxLuong)
            {
                dsMax.push_back(x);
            }
        }
        for (NhanVien *x : dsMax) x->Xuat();
    }

    void NhanVienLuongThapNhat()
    {
        vector<NhanVien *> dsMin;
        double minLuong = 1e18; 
        
        for (NhanVien *x : ds)
        {
            if (x->TinhLuong() < minLuong)
            {
                minLuong = x->TinhLuong();
                dsMin.clear();
                dsMin.push_back(x);
            }
            else if (x->TinhLuong() == minLuong)
            {
                dsMin.push_back(x);
            }
        }
        for (NhanVien *x : dsMin) x->Xuat();
    }

    void LTVLuongCaoNhat()
    {
        vector<NhanVien *> dsMax;
        double maxLuong = -1;
        
        for (NhanVien *x : ds)
        {
            if (x->getLoai() == 1)
            {
                if (x->TinhLuong() > maxLuong)
                {
                    maxLuong = x->TinhLuong();
                    dsMax.clear();
                    dsMax.push_back(x);
                }
                else if (x->TinhLuong() == maxLuong)
                {
                    dsMax.push_back(x);
                }
            }
        }
        for (NhanVien *x : dsMax) x->Xuat();
    }

    void KCVLuongThapNhat()
    {
        vector<NhanVien *> dsMin;
        double minLuong = 1e18; 
        
        for (NhanVien *x : ds)
        {
            if (x->getLoai() == 2)
            {
                if (x->TinhLuong() < minLuong)
                {
                    minLuong = x->TinhLuong();
                    dsMin.clear();
                    dsMin.push_back(x);
                }
                else if (x->TinhLuong() == minLuong)
                {
                    dsMin.push_back(x);
                }
            }
        }
        for (NhanVien *x : dsMin) x->Xuat();
    }
};

int main()
{
    CongTy hoanCau;
    
    hoanCau.NhapDanhSach();
    
    cout << "\n--- DANH SACH NHAN VIEN CONG TY HOAN CAU ---\n";
    hoanCau.XuatDanhSach();
    
    cout << "\n--- DANH SACH NHAN VIEN LUONG THAP HON TRUNG BINH ---\n";
    hoanCau.LuongThapHonTB();
    
    cout << "\n--- NHAN VIEN CO LUONG CAO NHAT CONG TY ---\n";
    hoanCau.NhanVienLuongCaoNhat();
    
    cout << "\n--- NHAN VIEN CO LUONG THAP NHAT CONG TY ---\n";
    hoanCau.NhanVienLuongThapNhat();
    
    cout << "\n--- LAP TRINH VIEN CO LUONG CAO NHAT ---\n";
    hoanCau.LTVLuongCaoNhat();
    
    cout << "\n--- KIEM CHUNG VIEN CO LUONG THAP NHAT ---\n";
    hoanCau.KCVLuongThapNhat();
    
    return 0;
}
