#include <iostream>
#include <windows.h>

int main() {
    HANDLE fileHandle;
    fileHandle = CreateFile(TEXT("data.txt"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        std::cout << "Không thể tạo file." << std::endl;
        return 1;
    }
    std::cout << "write file " << std::endl;

    const char* data = "Hello world!\naabcdefgh";
    DWORD byteWritten;
    WriteFile(fileHandle, data, strlen(data), &byteWritten, NULL);

    OVERLAPPED overlapped;
    memset(&overlapped, 0, sizeof(overlapped));
    LockFileEx(fileHandle, LOCKFILE_EXCLUSIVE_LOCK, 0, MAXDWORD, MAXDWORD, &overlapped);
    std::cout << "lock file" << std::endl;
    Sleep(20000);
    std::cout << "unlock file" << std::endl;
    UnlockFileEx(fileHandle, 0, MAXDWORD, MAXDWORD, &overlapped);

    CloseHandle(fileHandle);
    getchar();
    return 0;
}