#include <bits/stdc++.h>
using namespace std;

class NgayGiaoDich
{
private:
    int ngay, thang, nam;

public:
    void Nhap()
    {
        cout << "Nhap ngay thang nam (cach nhau boi dau cach): ";
        cin >> ngay >> thang >> nam;
    }
    void Xuat()
    {
        cout << ngay << "/" << thang << "/" << nam;
    }
    int getThang() { return thang; }
    int getNam() { return nam; }
};

class GiaoDich
{
protected:
    string maGiaoDich;
    NgayGiaoDich day;

public:
    GiaoDich() {};
    virtual ~GiaoDich() {}
    virtual void Nhap()
    {
        cout << "Nhap ma giao dich: ";
        getline(cin, maGiaoDich);
        day.Nhap();
    }
    virtual void Xuat()
    {
        cout << "Ma GD: " << maGiaoDich << " | Ngay GD: ";
        day.Xuat();
    }
    virtual double tinhThanhTien() = 0;
    virtual int getLoai() = 0;
    
    int getThangGD() { return day.getThang(); }
    int getNamGD() { return day.getNam(); }
};

class GiaoDichDat : public GiaoDich
{
private:
    double donGia;
    string type;
    double dienTich;

public:
    void Nhap() override
    {
        GiaoDich::Nhap();
        cout << "Nhap don gia: ";
        cin >> donGia;
        cin.ignore();
        cout << "Nhap loai dat (A, B, C): ";
        getline(cin, type);
        cout << "Nhap dien tich: ";
        cin >> dienTich;
        cin.ignore();
    }
    void Xuat() override
    {
        GiaoDich::Xuat();
        cout << " | Don gia: " << donGia << " | Loai dat: " << type << " | Dien tich: " << dienTich;
    }
    double tinhThanhTien() override
    {
        if (type == "A")
        {
            return dienTich * donGia * 1.5;
        }
        else if (type == "B" || type == "C")
        {
            return dienTich * donGia;
        }
        return 0;
    }
    int getLoai() override
    {
        return 1;
    }
};

class GiaoDichNhaPho : public GiaoDich
{
private:
    double donGia;
    string type;
    string address;
    double dienTich;

public:
    void Nhap() override
    {
        GiaoDich::Nhap();
        cout << "Nhap don gia: ";
        cin >> donGia;
        cin.ignore();
        cout << "Nhap loai nha pho (thuong, cao cap): ";
        getline(cin, type);
        cout << "Nhap dia chi: ";
        getline(cin, address);
        cout << "Nhap dien tich: ";
        cin >> dienTich;
        cin.ignore();
    }
    void Xuat() override
    {
        GiaoDich::Xuat();
        cout << " | Don gia: " << donGia << " | Loai: " << type << " | Dia chi: " << address << " | Dien tich: " << dienTich;
    }
    double tinhThanhTien() override
    {
        if (type == "thuong")
        {
            return dienTich * donGia * 0.9;
        }
        else if (type == "cao cap")
        {
            return dienTich * donGia;
        }
        return 0;
    }
    int getLoai() override
    {
        return 2;
    }
};

class GiaoDichChungCu : public GiaoDich
{
private:
    double donGia;
    string maCan;
    int viTri;
    double dienTich;

public:
    void Nhap() override
    {
        GiaoDich::Nhap();
        cout << "Nhap don gia: ";
        cin >> donGia;
        cin.ignore();
        cout << "Nhap ma can: ";
        getline(cin, maCan);
        cout << "Nhap vi tri tang: ";
        cin >> viTri;
        cout << "Nhap dien tich: ";
        cin >> dienTich;
        cin.ignore();
    }
    void Xuat() override
    {
        GiaoDich::Xuat();
        cout << " | Don gia: " << donGia << " | Ma can: " << maCan << " | Vi tri tang: " << viTri << " | Dien tich: " << dienTich;
    }
    double tinhThanhTien() override
    {
        if (viTri == 1)
        {
            return dienTich * donGia * 2;
        }
        else if (viTri >= 15)
        {
            return dienTich * donGia * 1.2;
        }
        else
            return dienTich * donGia;
        return 0;
    }
    int getLoai() override
    {
        return 3;
    }
};

class DanhSachGiaoDich
{
private:
    vector<GiaoDich *> ds;
    int slGDDat, slGDNhaPho, slGDCanho;

public:
    ~DanhSachGiaoDich()
    {
        for (GiaoDich *GD : ds)
        {
            delete GD;
        }
    }
    void NhapDanhSach()
    {
        cout << "So luong giao dich dat: ";
        cin >> slGDDat;
        cout << "So luong giao dich nha pho: ";
        cin >> slGDNhaPho;
        cout << "So luong giao dich can ho chung cu: ";
        cin >> slGDCanho;
        cin.ignore();
        for (int i = 0; i < slGDDat; i++)
        {
            cout << "\n--- Nhap Giao Dich Dat thu " << i + 1 << " ---\n";
            GiaoDich *GD = new GiaoDichDat();
            GD->Nhap();
            ds.push_back(GD);
        }
        for (int i = 0; i < slGDNhaPho; i++)
        {
            cout << "\n--- Nhap Giao Dich Nha Pho thu " << i + 1 << " ---\n";
            GiaoDich *GD = new GiaoDichNhaPho();
            GD->Nhap();
            ds.push_back(GD);
        }
        for (int i = 0; i < slGDCanho; i++)
        {
            cout << "\n--- Nhap Giao Dich Chung Cu thu " << i + 1 << " ---\n";
            GiaoDich *GD = new GiaoDichChungCu();
            GD->Nhap();
            ds.push_back(GD);
        }
    }
    
    void XuatGiaoDichThang12Nam2024()
    {
        cout << "\n================ DANH SACH GIAO DICH THANG 12/2024 ================\n";
        bool coGiaoDich = false; 
        
        for (GiaoDich *GD : ds)
        {
            if (GD->getThangGD() == 12 && GD->getNamGD() == 2024)
            {
                if (GD->getLoai() == 1) cout << "[DAT] ";
                else if (GD->getLoai() == 2) cout << "[NHA PHO] ";
                else if (GD->getLoai() == 3) cout << "[CHUNG CU] ";
                
                GD->Xuat();
                cout << " | Thanh tien: " << fixed << setprecision(0) << GD->tinhThanhTien() << "\n";
                coGiaoDich = true; 
            }
        }
        
        if (!coGiaoDich)
        {
            cout << "-> Khong co giao dich nao hop le trong thang 12 nam 2024.\n";
        }
        cout << "===================================================================\n";
    }
    
    int tongSoLuonglLoaiGDDat()
    {
        return slGDDat;
    }
    int tongSoLuonglLoaiGDNhaPho()
    {
        return slGDNhaPho;
    }
    int tongSoLuonglLoaiGDCanHo()
    {
        return slGDCanho;
    }
    double tbThanhTienGDChungCu()
    {
        if (slGDCanho == 0) return 0;
        double tongTien = 0;
        for (GiaoDich *GD : ds)
        {
            if (GD->getLoai() == 3)
            {
                tongTien += GD->tinhThanhTien();
            }
        }
        return tongTien / slGDCanho;
    }
    void GDRICH()
    {
        GiaoDich *GD = nullptr;
        double maxMoney = -1;
        for (GiaoDich *DS : ds)
        {
            if (DS->getLoai() == 2)
            {
                if (DS->tinhThanhTien() > maxMoney)
                {
                    maxMoney = DS->tinhThanhTien();
                    GD = DS;
                }
            }
        }
        if (GD != nullptr)
        {
            cout << "[NHA PHO] ";
            GD->Xuat();
            cout << " | Thanh tien: " << fixed << setprecision(0) << GD->tinhThanhTien() << "\n";
        }
        else
        {
            cout << "Khong co giao dich nha pho nao.\n";
        }
    }
};

int main()
{
    DanhSachGiaoDich allGD;
    cout << "--- KHOI TAO DANH SACH GIAO DICH ---\n";
    allGD.NhapDanhSach();
    
    allGD.XuatGiaoDichThang12Nam2024();
    
    cout << "\n--- THONG KE GIAO DICH ---\n";
    cout << "Tong so luong cho loai giao dich Dat la: " << allGD.tongSoLuonglLoaiGDDat() << "\n";
    cout << "Tong so luong cho loai giao dich Nha Pho la: " << allGD.tongSoLuonglLoaiGDNhaPho() << "\n";
    cout << "Tong so luong cho loai giao dich Can ho chung cu la: " << allGD.tongSoLuonglLoaiGDCanHo() << "\n";
    cout << "Trung binh thanh tien cua giao dich Can ho chung cu la: " << fixed << setprecision(0) << allGD.tbThanhTienGDChungCu() << "\n";
    
    cout << "\n--- GIAO DICH NHA PHO CO GIA TRI CAO NHAT ---\n";
    allGD.GDRICH();
    
    return 0;
}
