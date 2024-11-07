#include <iostream>
#include <cstring>
using namespace std;

// Định nghĩa cấu trúc Ngay để lưu trữ ngày, tháng, năm sinh
struct Ngay {
    int ngay;
    int thang;
    int nam;
};

// Định nghĩa cấu trúc SinhVien để lưu trữ thông tin sinh viên
struct SinhVien {
    char MSSV[10];          // Mã sinh viên
    char Name[50];          // Họ tên
    int Sex;                // Giới tính (0: Nữ, 1: Nam)
    Ngay DoB;               // Ngày sinh
    char Address[100];      // Địa chỉ
    char Class[20];         // Lớp
    char grade[10];         // grade
};

// Định nghĩa cấu trúc Node để tạo danh sách liên kết đơn
struct Node {
    SinhVien data;  // Dữ liệu của sinh viên
    Node* link;     // Con trỏ trỏ đến nút tiếp theo trong danh sách
};

// Hàm tạo một nút mới
Node* createNode(const SinhVien& sv) {
    Node* newNode = new Node;
    newNode->data = sv;
    newNode->link = nullptr;
    return newNode;
}

// Hàm chèn một sinh viên vào danh sách đã sắp xếp
void insertSorted(Node** head, const SinhVien& sv) {
    Node* newNode = createNode(sv);
    if (*head == nullptr || strcmp((*head)->data.MSSV, sv.MSSV) > 0) {
        newNode->link = *head;
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->link != nullptr && strcmp(current->link->data.MSSV, sv.MSSV) < 0) {
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
    }
}

// Hàm in danh sách sinh viên
void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << "MSSV: " << current->data.MSSV 
             << ", Name: " << current->data.Name 
             << ", Sex: " << (current->data.Sex ? "Nam" : "Nu")
             << ", DoB: " << current->data.DoB.ngay << "/" 
             << current->data.DoB.thang << "/" 
             << current->data.DoB.nam 
             << ", Address: " << current->data.Address 
             << ", Class: " << current->data.Class 
             << ", grade: " << current->data.grade << endl;
        current = current->link;
    }
}

// Hàm tìm và in các sinh viên có cùng ngày sinh
void findSameBirthDate(Node* head, const Ngay& date) {
    Node* current = head;
    bool found = false;
    while (current != nullptr) {
        if (current->data.DoB.ngay == date.ngay &&
            current->data.DoB.thang == date.thang &&
            current->data.DoB.nam == date.nam) {
            cout << "MSSV: " << current->data.MSSV 
                 << ", Name: " << current->data.Name 
                 << ", Sex: " << (current->data.Sex ? "Nam" : "Nu")
                 << ", DoB: " << current->data.DoB.ngay << "/" 
                 << current->data.DoB.thang << "/" 
                 << current->data.DoB.nam 
                 << ", Address: " << current->data.Address 
                 << ", Class: " << current->data.Class 
                 << ", grade: " << current->data.grade << endl;
            found = true;
        }
        current = current->link;
    }
    if (!found) {
        cout << "Khong tim thay sinh vien cung ngay sinh" << endl;
    }
}

// Hàm loại bỏ các sinh viên có cùng ngày sinh
void removeSameBirthDate(Node** head, const Ngay& date) {
    Node* current = *head;
    Node* prev = nullptr;
    while (current != nullptr) {
        if (current->data.DoB.ngay == date.ngay &&
            current->data.DoB.thang == date.thang &&
            current->data.DoB.nam == date.nam) {
            if (prev == nullptr) {
                *head = current->link;
            } else {
                prev->link = current->link;
            }
            delete current;
            current = (prev == nullptr) ? *head : prev->link;
        } else {
            prev = current;
            current = current->link;
        }
    }
}

// Hàm nhập thông tin sinh viên từ bàn phím
SinhVien inputSinhVien() {
    SinhVien sv;
    cout << "Nhap ma sinh vien: ";
    cin >> sv.MSSV;
    cin.ignore(); // Loại bỏ ký tự newline còn lại trong bộ đệm
    cout << "Nhap ho ten: ";
    cin.getline(sv.Name, 50);
    cout << "Nhap gioi tinh (0: Nu, 1: Nam): ";
    cin >> sv.Sex;
    cout << "Nhap ngay sinh (ngay thang nam): ";
    cin >> sv.DoB.ngay >> sv.DoB.thang >> sv.DoB.nam;
    cin.ignore();
    cout << "Nhap dia chi: ";
    cin.getline(sv.Address, 100);
    cout << "Nhap Class: ";
    cin.getline(sv.Class, 20);
    cout << "Nhap grade: ";
    cin.getline(sv.grade, 10);
    return sv;
}

int main() {
    Node* ListSV = nullptr;
    int n;
    
    cout << "Nhap so luong sinh vien: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << "\nNhap thong tin sinh vien thu " << i + 1 << ":\n";
        SinhVien sv = inputSinhVien();
        insertSorted(&ListSV, sv);
    }

    cout << "\nDanh sach sinh vien:" << endl;
    printList(ListSV);

    Ngay date;
    cout << "\nNhap ngay sinh can tim (ngay thang nam): ";
    cin >> date.ngay >> date.thang >> date.nam;

    cout << "\nSinh vien cung ngay sinh " << date.ngay << "/" << date.thang << "/" << date.nam << ":" << endl;
    findSameBirthDate(ListSV, date);

    cout << "\nLoai bo sinh vien cung ngay sinh " << date.ngay << "/" << date.thang << "/" << date.nam << ":" << endl;
    removeSameBirthDate(&ListSV, date);
    printList(ListSV);

    return 0;
}
