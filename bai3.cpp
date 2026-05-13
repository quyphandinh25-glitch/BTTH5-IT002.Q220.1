#include <bits/stdc++.h>
using namespace std;
class SinhVien
{
protected:
    int mssv;
    string name;
    string address;
    int tongTinChi;
    double dTB;

public:
    virtual void Nhap()
    {
        cout << "Nhap ma so sinh vien: ";
        cin >> mssv;
        cin.ignore();
        cout << "Nhap ten sinh vien: ";
        getline(cin, name);
        cout << "Nhap dia chi cua sinh vien: ";
        getline(cin, address);
        cout << "Nhap tong tin chi da hoc: ";
        cin >> tongTinChi;
        cout << "Nhap diem trung binh 4 nam hoc: ";
        cin >> dTB;
    }
    virtual void Xuat()
    {
        cout << "MSSV: " << mssv << "\t" << "NAME: " << name << "\t" << "Dia chi: " << address << "\t" << "Tong tin chi: " << tongTinChi << "\t" << "DTB: " << dTB << "\t";
    }
    virtual ~SinhVien() {}
    virtual int getLoai() = 0;
    virtual bool DSDTN() = 0;
    virtual double getDTB() = 0;
};
class SinhVienDH : public SinhVien
{
private:
    double diemTN;

public:
    void Nhap() override
    {
        SinhVien ::Nhap();
        cout << "Nhap diem tot nghiep: ";
        cin >> diemTN;
    }
    void Xuat() override
    {
        SinhVien ::Xuat();
        cout << "Diem TN:" << diemTN << "\n";
    }
    bool DSDTN()
    {
        return (tongTinChi >= 120 && dTB >= 5 && diemTN >= 5);
    }
    int getLoai() override
    {
        return 1;
    }
    double getDTB() override
    {
        return dTB;
    }
};
class SinhVienCD : public SinhVien
{
private:
    string tenLuanVan;
    double diemLV;

public:
    void Nhap() override
    {
        SinhVien ::Nhap();
        cin.ignore();
        cout << "Nhap ten luan van: ";
        getline(cin, tenLuanVan);
        cout << "Nhap diem luan van: ";
        cin >> diemLV;
    }
    void Xuat() override
    {
        SinhVien ::Xuat();
        cout << "Ten luan van: ";
        cout << tenLuanVan << "\t";
        cout << "Diem luan van: ";
        cout << diemLV << "\n";
    }
    bool DSDTN()
    {
        return (tongTinChi >= 120 && dTB >= 5 && diemLV >= 5);
    }
    int getLoai() override
    {
        return 2;
    }
    double getDTB() override
    {
        return dTB;
    }
};
class DSSV
{
private:
    vector<SinhVien *> ds;
    int SLSVDH, SLSVCD;

public:
    ~DSSV()
    {
        for (SinhVien *sv : ds)
        {
            delete sv;
        }
    }
    void NhapSinhVien()
    {
        cout << "Nhap so luong sinh vien dai hoc: ";
        cin >> SLSVDH;
        cout << "Nhap so luong sinh vien cao dang: ";
        cin >> SLSVCD;
        for (int i = 0; i < SLSVDH; i++)
        {
            SinhVien *sv = new SinhVienDH();
            sv->Nhap();
            ds.push_back(sv);
        }
        for (int i = 0; i < SLSVCD; i++)
        {
            SinhVien *sv = new SinhVienCD();
            sv->Nhap();
            ds.push_back(sv);
        }
    }
    void XuatSinhVien()
    {
        for (SinhVien *x : ds)
        {
            if (x->getLoai() == 1)
            {
                cout << "DH ";
                x->Xuat();
            }
            else if (x->getLoai() == 2)
            {
                cout << "CD ";
                x->Xuat();
            }
        }
    }
    void DSSVDTN()
    {
        for (SinhVien *x : ds)
        {
            if (x->getLoai() == 1)
            {
                if (x->DSDTN() == true)
                {
                    x->Xuat();
                }
            }
            else if (x->getLoai() == 2)
            {
                if (x->DSDTN() == true)
                {
                    x->Xuat();
                }
            }
        }
    }
    void DSSVKDTN()
    {
        for (SinhVien *x : ds)
        {
            if (x->getLoai() == 1)
            {
                if (x->DSDTN() == false)
                {
                    x->Xuat();
                }
            }
            else if (x->getLoai() == 2)
            {
                if (x->DSDTN() == false)
                {
                    x->Xuat();
                }
            }
        }
    }
    void SVGIOI()
    {
        vector<SinhVien *> dsdhgioi;
        vector<SinhVien *> dscdgioi;
        double maxdh = -1;
        double maxcd = -1;
        for (SinhVien *x : ds)
        {
            if (x->getLoai() == 1)
            {
                if (x->getDTB() > maxdh)
                {
                    maxdh = x->getDTB();
                    dsdhgioi.clear();
                    dsdhgioi.push_back(x);
                }
                else if (x->getDTB() == maxdh)
                {
                    dsdhgioi.push_back(x);
                }
            }
            else if (x->getLoai() == 2)
            {
                if (x->getDTB() > maxcd)
                {
                    maxcd = x->getDTB();
                    dscdgioi.clear();
                    dscdgioi.push_back(x);
                }
                else if (x->getDTB() == maxcd)
                {
                    dscdgioi.push_back(x);
                }
            }
        }
        cout << "Sinh vien thuoc he dai hoc:\n";
        for (SinhVien *sv : dsdhgioi)
        {
            sv->Xuat();
        }
        cout << "Sinh vien thuoc he cao dang:\n";
        for (SinhVien *sv : dscdgioi)
        {
            sv->Xuat();
        }
    }
    void SVDHKDTN()
    {
        for (SinhVien *x : ds)
        {
            if (x->getLoai() == 1)
            {
                if (x->DSDTN() == false)
                {
                    x->Xuat();
                }
            }
        }
    }
    void SVCDKDTN()
    {
        for (SinhVien *x : ds)
        {
            if (x->getLoai() == 2)
            {
                if (x->DSDTN() == false)
                {
                    x->Xuat();
                }
            }
        }
    }
};
int main()
{
    DSSV ds;
    cout << "Nhap danh sach tac ca cac sinh vien thuoc he dai hoc va cao dang\n";
    ds.NhapSinhVien();
    cout << "\nDanh sach cac sinh vien thuoc dai hoc va cao dang\n";
    ds.XuatSinhVien();
    cout << "\n----Danh sach sinh vien du dieu kien tot nghiep----\n";
    ds.DSSVDTN();
    cout << "\n----Danh sach sinh vien khong dieu kien tot nghiep----\n";
    ds.DSSVKDTN();
    cout << "\n---Danh sach sinh vien thuoc he dai hoc va cao dang co hoc luc xuat sac---\n";
    ds.SVGIOI();
    cout << "\nDanh sach sinh vien dai hoc khong dat tot nghiep\n";
    ds.SVDHKDTN();
    cout << "\nDanh sach sinh vien cao dang khong dat tot nghiep\n";
    ds.SVCDKDTN();
    return 0;
}
