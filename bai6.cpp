#include <bits/stdc++.h>
using namespace std;

class KhachHang
{
protected:
    string ten;
    double soLuong;
    double donGia;

public:
    virtual void Nhap()
    {
        getline(cin, ten);
        cin >> soLuong >> donGia;
    }
    
    virtual void Xuat()
    {
        cout << ten << "\n";
        cout << (long long)TinhTien() << "\n";
    }
    
    virtual double TinhTien() = 0;
    virtual int getLoai() = 0;
    virtual ~KhachHang() {}
};

class KhachHangA : public KhachHang
{
public:
    void Nhap() override
    {
        KhachHang::Nhap();
        cin.ignore();
    }
    
    double TinhTien() override
    {
        double tien = soLuong * donGia;
        return tien + (tien * 0.1);
    }
    
    int getLoai() override { return 1; }
};

class KhachHangB : public KhachHang
{
private:
    int soNam;

public:
    void Nhap() override
    {
        KhachHang::Nhap();
        cin >> soNam;
        cin.ignore();
    }
    
    double TinhTien() override
    {
        double tien = soLuong * donGia;
        double phanTram = max(soNam * 0.05, 0.5); 
        double tienSauGiam = tien * (1.0 - phanTram);
        return tienSauGiam + (tienSauGiam * 0.1);
    }
    
    int getLoai() override { return 2; }
};

class KhachHangC : public KhachHang
{
public:
    void Nhap() override
    {
        KhachHang::Nhap();
        cin.ignore();
    }
    
    double TinhTien() override
    {
        double tien = soLuong * donGia;
        double tienSauGiam = tien * 0.5;
        return tienSauGiam + (tienSauGiam * 0.1);
    }
    
    int getLoai() override { return 3; }
};

class CongTy
{
private:
    vector<KhachHang *> ds;
    int x, y, z;

public:
    ~CongTy()
    {
        for (KhachHang *kh : ds)
        {
            delete kh;
        }
    }
    
    void NhapDanhSach()
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
    
    void XuatDanhSach()
    {
        cout << x << " " << y << " " << z << "\n";
        
        double tongThu = 0;
        for (KhachHang *x : ds)
        {
            x->Xuat();
            tongThu += x->TinhTien();
        }
        
        cout << (long long)tongThu << "\n";
    }
};

int main()
{  
    freopen("XYZ.INP", "r", stdin);
    freopen("XYZ.OUT", "w", stdout);
    
    CongTy cty;
    cty.NhapDanhSach();
    cty.XuatDanhSach();
    
    return 0;
}
