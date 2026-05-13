#include <bits/stdc++.h>
using namespace std;

class KhachHang
{
protected:
    string ten;
    double soLuong;
    double donGia;

public:
    virtual void Nhap();
    virtual void Xuat();
    virtual double TinhTien() = 0;
    virtual int getLoai() = 0;
    virtual ~KhachHang();
};

class KhachHangA : public KhachHang
{
public:
    void Nhap() override;
    double TinhTien() override;
    int getLoai() override;
};

class KhachHangB : public KhachHang
{
private:
    int soNam;

public:
    void Nhap() override;
    double TinhTien() override;
    int getLoai() override;
};

class KhachHangC : public KhachHang
{
public:
    void Nhap() override;
    double TinhTien() override;
    int getLoai() override;
};

class CongTy
{
private:
    vector<KhachHang *> ds;
    int x, y, z;

public:
    ~CongTy();
    void NhapDanhSach();
    void XuatDanhSach();
};

void KhachHang::Nhap()
{
    getline(cin, ten);
    cin >> soLuong >> donGia;
}

void KhachHang::Xuat()
{
    cout << ten << "\n";
    cout << (long long)TinhTien() << "\n";
}

KhachHang::~KhachHang() {}

void KhachHangA::Nhap()
{
    KhachHang::Nhap();
    cin.ignore();
}

double KhachHangA::TinhTien()
{
    double tien = soLuong * donGia;
    return tien + (tien * 0.1);
}

int KhachHangA::getLoai()
{
    return 1;
}

void KhachHangB::Nhap()
{
    KhachHang::Nhap();
    cin >> soNam;
    cin.ignore();
}

double KhachHangB::TinhTien()
{
    double tien = soLuong * donGia;
    double phanTram = max(soNam * 0.05, 0.5); 
    double tienSauGiam = tien * (1.0 - phanTram);
    return tienSauGiam + (tienSauGiam * 0.1);
}

int KhachHangB::getLoai()
{
    return 2;
}

void KhachHangC::Nhap()
{
    KhachHang::Nhap();
    cin.ignore();
}

double KhachHangC::TinhTien()
{
    double tien = soLuong * donGia;
    double tienSauGiam = tien * 0.5;
    return tienSauGiam + (tienSauGiam * 0.1);
}

int KhachHangC::getLoai()
{
    return 3;
}

CongTy::~CongTy()
{
    for (KhachHang *kh : ds)
    {
        delete kh;
    }
}

void CongTy::NhapDanhSach()
{
    cin >> x >> y >> z;
    cin.ignore();
    
    for (int i = 0; i < x; i++)
    {
        KhachHang *kh = new KhachHangA();
        kh->Nhap();
        ds.push_back(kh);
    }
    
    for (int i = 0; i < y; i++)
    {
        KhachHang *kh = new KhachHangB();
        kh->Nhap();
        ds.push_back(kh);
    }
    
    for (int i = 0; i < z; i++)
    {
        KhachHang *kh = new KhachHangC();
        kh->Nhap();
        ds.push_back(kh);
    }
}

void CongTy::XuatDanhSach()
{
    cout << x << " " << y << " " << z << "\n";
    
    double tongThu = 0;
    for (KhachHang *kh : ds)
    {
        kh->Xuat();
        tongThu += kh->TinhTien();
    }
    
    cout << (long long)tongThu << "\n";
}

int main()
{  
    freopen("XYZ.INP", "r", stdin);
    freopen("XYZ.OUT", "w", stdout);
    
    CongTy cty;
    cty.NhapDanhSach();
    cty.XuatDanhSach();
    
    return 0;
}
