#include <iostream>
using namespace std;

// Định nghĩa cấu trúc Ngay để lưu trữ ngày, tháng, năm sinh
struct Ngay {
    int ngay;
    int thang;
    int nam;
};

// Định nghĩa cấu trúc SinhVien để lưu trữ thông tin sinh viên
struct SinhVien {
    char maSV[10];       // Mã sinh viên
    char hoTen[50];     // Họ tên
    int gioiTinh;       // Giới tính (0: Nữ, 1: Nam)
    Ngay ngaySinh;      // Ngày sinh
    char diaChi[100];   // Địa chỉ
    char lop[20];       // Lớp
    char khoa[10];       // Khoa
};

// Định nghĩa cấu trúc Node để tạo danh sách liên kết đơn
struct Node {
    SinhVien data;  // Dữ liệu của sinh viên
    Node *link;     // Con trỏ trỏ đến nút tiếp theo trong danh sách
};

// Hàm tạo một nút mới
Node* createNode(SinhVien sv) {
    Node* newNode = new Node; // Cấp phát bộ nhớ cho nút mới
    newNode->data = sv; // Gán dữ liệu sinh viên cho nút mới
    newNode->link = NULL; // Khởi tạo liên kết của nút mới là NULL
    return newNode; // Trả về con trỏ đến nút mới
}

// Hàm so sánh hai chuỗi ký tự
int stringCompare(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

// Hàm sao chép chuỗi ký tự
void stringCopy(char *dest, const char *src) {
    while ((*dest++ = *src++));
}

// Hàm chèn một sinh viên vào danh sách đã sắp xếp
void insertSorted(Node** head, SinhVien sv) {
    Node* newNode = createNode(sv); // Tạo một nút mới với dữ liệu sinh viên
    if (*head == NULL || stringCompare((*head)->data.maSV, sv.maSV) > 0) {
        newNode->link = *head; // Thêm sinh viên mới vào đầu danh sách nếu danh sách rỗng hoặc mã sinh viên nhỏ hơn mã sinh viên đầu
        *head = newNode;
    } else {
        Node* current = *head; // Khởi tạo con trỏ current để duyệt danh sách từ đầu.
        while (current->link != NULL && stringCompare(current->link->data.maSV, sv.maSV) < 0) {
            current = current->link; // Tìm vị trí thích hợp để chèn sinh viên mới
        }
        newNode->link = current->link; // Chèn sinh viên mới vào danh sách tại vị trí tìm được.
        current->link = newNode;
    }
}

// Hàm in danh sách sinh viên
void printList(Node* head) {
    Node* current = head; // Khởi tạo con trỏ current để duyệt danh sách từ đầu.
    while (current != NULL) {
        cout << "MaSV: " << current->data.maSV 
             << ", HoTen: " << current->data.hoTen 
             << ", GioiTinh: " << current->data.gioiTinh 
             << ", NgaySinh: " << current->data.ngaySinh.ngay << "/" 
             << current->data.ngaySinh.thang << "/" 
             << current->data.ngaySinh.nam 
             << ", DiaChi: " << current->data.diaChi 
             << ", Lop: " << current->data.lop 
             << ", Khoa: " << current->data.khoa << endl;
        current = current->link; // Chuyển con trỏ current sang nút tiếp theo
    }
}

// Hàm tìm và in các sinh viên có cùng ngày sinh
void findSameBirthDate(Node* head, Ngay date) {
    Node* current = head;
    bool found = false;
    while (current != NULL) {
        if (current->data.ngaySinh.ngay == date.ngay &&
            current->data.ngaySinh.thang == date.thang &&
            current->data.ngaySinh.nam == date.nam) {
            cout << "MaSV: " << current->data.maSV 
                 << ", HoTen: " << current->data.hoTen 
                 << ", GioiTinh: " << current->data.gioiTinh 
                 << ", NgaySinh: " << current->data.ngaySinh.ngay << "/" 
                 << current->data.ngaySinh.thang << "/" 
                 << current->data.ngaySinh.nam 
                 << ", DiaChi: " << current->data.diaChi 
                 << ", Lop: " << current->data.lop 
                 << ", Khoa: " << current->data.khoa << endl;
            found = true;
        }
        current = current->link;
    }
    if (!found) {
        cout << "Khong tim thay sinh vien cung ngay sinh" << endl;
    }
}

// Hàm loại bỏ các sinh viên có cùng ngày sinh
void removeSameBirthDate(Node** head, Ngay date) {
    Node* current = *head;
    Node* prev = NULL;
    while (current != NULL) {
        if (current->data.ngaySinh.ngay == date.ngay &&
            current->data.ngaySinh.thang == date.thang &&
            current->data.ngaySinh.nam == date.nam) {
            if (prev == NULL) {
                *head = current->link;
            } else {
                prev->link = current->link;
            }
            delete current; // Giải phóng bộ nhớ
            current = (prev == NULL) ? *head : prev->link;
        } else {
            prev = current;
            current = current->link;
        }
    }
}

int main() {
    Node* ListSV = NULL;

    // Ví dụ sử dụng
    SinhVien sv1 = {"20224420", "Nguyen Duy Hai Long", 1, {7, 3, 2004}, "Hai Duong", "ETE902", "DTVT"};
    SinhVien sv2 = {"20224449", "Nguyen Tran Phong", 1, {10, 10, 2004}, "Vinh", "ETE902", "DTVT"};
    SinhVien sv3 = {"20224461", "Nguyen An Khanh", 1, {1, 1, 2004}, "Hai Phong", "ETE902", "DTVT"};
    SinhVien sv4 = {"20224430", "Hoang Thi Ha", 0, {1, 1, 2000}, "Hai Duong", "ETE902", "DTVT"};
    SinhVien sv5 = {"20224437", "Tong Quang Hiep", 0, {1, 1, 2006}, "Ha Noi", "ETE902", "DTVT"};

    insertSorted(&ListSV, sv1);
    insertSorted(&ListSV, sv2);
    insertSorted(&ListSV, sv3);
    insertSorted(&ListSV, sv4);
    insertSorted(&ListSV, sv5);

    cout << "Danh sach sinh vien:" << endl;
    printList(ListSV);

    cout << "\nSinh vien cung ngay sinh 01/01/2000:" << endl;
    findSameBirthDate(ListSV, (Ngay){1, 1, 2000});

    cout << "\nLoai bo sinh vien cung ngay sinh 01/01/2000:" << endl;
    removeSameBirthDate(&ListSV, (Ngay){1, 1, 2000});
    printList(ListSV);

    return 0;
}
