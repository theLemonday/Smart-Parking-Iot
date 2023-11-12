# Phần lập trình nhúng của bãi đỗ xe thông minh
Sử dụng mqtt để truyền dữ liệu

## Các thành phần

### Khu vực bên phải cổng ra vào

- Màn hình OLED hiển thị nội dung chào mừng và chào tạm biệt:
    - D1: SCL
    - D2: SDA
- Rào chắn điều khiển đóng mở cho phép xe đi qua (D3)
- Cảm biến hồng ngoại phát hiện xe đi vào (D4)
- Cảm biến hồng ngoại phát hiện xe đi ra (D5)

### Khu vực bên trái cổng ra vào

- Đèn LED đỏ (D1)
- Đèn LED xanh (D2)
- Module đọc thẻ RFID:

|Pin |Trên RFID Reader|
| -- | ------ |
| D4 | SDA/SS |
| D5 | SCK    |
| D7 | MOSI   |
| D6 | MISO   |
| D3 | RST    |