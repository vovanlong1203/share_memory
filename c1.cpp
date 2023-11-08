#include <iostream>
#include <windows.h>

int main() {
    HANDLE fileHandle = INVALID_HANDLE_VALUE;

    while (fileHandle == INVALID_HANDLE_VALUE) {
        fileHandle = CreateFile(TEXT("data.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (fileHandle == INVALID_HANDLE_VALUE) {
            std::cout << "khong the mo file ..." << std::endl;
            Sleep(1000); 
        }
    }
    if (fileHandle == INVALID_HANDLE_VALUE) {
            std::cout << "khong the mo file " << std::endl;
            return 1;
        }
    // Đọc nội dung từ file
    std::cout << "doc file " << std::endl;
    const int bufferSize = 1024;
    char buffer[bufferSize];
    DWORD byteRead;
    while (ReadFile(fileHandle, buffer, bufferSize - 1, &byteRead, NULL) && byteRead != 0) {
        std::cout << buffer;
        memset(buffer, 0, bufferSize);
    }

    // Đóng file
    CloseHandle(fileHandle);
    getchar();
    return 0;
}